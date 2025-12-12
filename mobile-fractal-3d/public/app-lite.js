// ULTRA-LIGHT FRACTAL ENGINE
// No dependencies, pure WebGL + GLSL shaders
// ~15KB vs 1.27MB (Three.js) = 98.8% smaller!

const state = {
    fractal: 'mandelbulb',
    colorScheme: 'rainbow',
    autoRotate: true,
    speed: 1.0,
    time: 0,
    rotation: { x: 0, y: 0 },
    zoom: 3.5,
    quality: 1.0
};

let gl, program, canvas;
let mouseDown = false;
let lastTouch = { x: 0, y: 0 };
let animationId;
let isVisible = true;

// Vertex Shader (simple fullscreen quad)
const vertexShaderSource = `
    attribute vec2 position;
    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
    }
`;

// Fragment Shader (GPU-based fractal raymarching)
const fragmentShaderSource = `
    precision highp float;
    uniform vec2 resolution;
    uniform float time;
    uniform vec2 rotation;
    uniform float zoom;
    uniform int fractalType;
    uniform int colorScheme;
    uniform int autoRotate;

    #define MAX_STEPS 64
    #define MAX_DIST 20.0
    #define SURF_DIST 0.001

    // Smooth minimum for blending
    float smin(float a, float b, float k) {
        float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
        return mix(b, a, h) - k * h * (1.0 - h);
    }

    // Rotation matrices
    mat2 rot2D(float angle) {
        float s = sin(angle);
        float c = cos(angle);
        return mat2(c, -s, s, c);
    }

    // Mandelbulb Distance Estimator
    float mandelbulb(vec3 pos) {
        vec3 z = pos;
        float dr = 1.0;
        float r = 0.0;
        float power = 8.0;

        for(int i = 0; i < 8; i++) {
            r = length(z);
            if(r > 2.0) break;

            float theta = acos(z.z / r);
            float phi = atan(z.y, z.x);
            dr = pow(r, power - 1.0) * power * dr + 1.0;

            float zr = pow(r, power);
            theta = theta * power;
            phi = phi * power;

            z = zr * vec3(sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
            z += pos;
        }
        return 0.5 * log(r) * r / dr;
    }

    // Menger Sponge
    float menger(vec3 p) {
        float d = length(max(abs(p) - vec3(1.0), 0.0)) - 0.01;

        float s = 1.0;
        for(int m = 0; m < 3; m++) {
            vec3 a = mod(p * s, 2.0) - 1.0;
            s *= 3.0;
            vec3 r = abs(1.0 - 3.0 * abs(a));
            float da = max(r.x, r.y);
            float db = max(r.y, r.z);
            float dc = max(r.z, r.x);
            float c = (min(da, min(db, dc)) - 1.0) / s;
            d = max(d, c);
        }
        return d;
    }

    // Julia Set 3D
    float julia(vec3 p) {
        vec4 c = vec4(0.4, 0.4, 0.2, 0.0);
        vec4 z = vec4(p, 0.0);
        float md2 = 1.0;
        float mz2 = dot(z, z);

        for(int i = 0; i < 8; i++) {
            md2 *= 4.0 * mz2;
            z = vec4(z.x*z.x - dot(z.yzw, z.yzw), 2.0 * z.x * z.yzw) + c;
            mz2 = dot(z, z);
            if(mz2 > 4.0) break;
        }

        return 0.25 * sqrt(mz2 / md2) * log(mz2);
    }

    // Sierpinski Tetrahedron
    float sierpinski(vec3 p) {
        float scale = 2.0;
        vec3 offset = vec3(1.0);

        for(int i = 0; i < 8; i++) {
            p = abs(p);
            if(p.x + p.y < 0.0) p.xy = -p.yx;
            if(p.x + p.z < 0.0) p.xz = -p.zx;
            if(p.y + p.z < 0.0) p.yz = -p.zy;
            p = p * scale - offset * (scale - 1.0);
        }

        return (length(p) - 2.0) * pow(scale, -8.0);
    }

    // Psychedelic Sphere
    float psychedelic(vec3 p) {
        float t = time * 0.5;
        float d = length(p) - 1.0;
        d += sin(p.x * 5.0 + t) * cos(p.y * 5.0 + t) * sin(p.z * 5.0 + t) * 0.15;
        d += sin(length(p) * 10.0 - t * 2.0) * 0.05;
        return d;
    }

    // Scene SDF
    float sceneSDF(vec3 p) {
        if(fractalType == 0) return mandelbulb(p);
        if(fractalType == 1) return julia(p);
        if(fractalType == 2) return sierpinski(p);
        if(fractalType == 3) return menger(p);
        if(fractalType == 4) return psychedelic(p);
        return mandelbulb(p);
    }

    // Raymarching
    float rayMarch(vec3 ro, vec3 rd) {
        float dO = 0.0;
        for(int i = 0; i < MAX_STEPS; i++) {
            vec3 p = ro + rd * dO;
            float dS = sceneSDF(p);
            dO += dS;
            if(dO > MAX_DIST || abs(dS) < SURF_DIST) break;
        }
        return dO;
    }

    // Normal calculation
    vec3 getNormal(vec3 p) {
        vec2 e = vec2(0.001, 0.0);
        float d = sceneSDF(p);
        vec3 n = d - vec3(
            sceneSDF(p - e.xyy),
            sceneSDF(p - e.yxy),
            sceneSDF(p - e.yyx)
        );
        return normalize(n);
    }

    // Color schemes
    vec3 getColor(vec3 p, vec3 n, float dist) {
        vec3 col;

        if(colorScheme == 0) { // Rainbow
            col = 0.5 + 0.5 * cos(6.28 * (p * 0.5 + time * 0.3 + vec3(0.0, 0.33, 0.67)));
        } else if(colorScheme == 1) { // Galaxy
            col = vec3(0.1, 0.3, 0.6) + vec3(0.3, 0.2, 0.5) * (1.0 + sin(p.y * 3.0 + time));
        } else if(colorScheme == 2) { // Fire
            float h = p.y * 0.5 + 0.5;
            col = vec3(1.0, h * 0.5, h * h * 0.2);
        } else if(colorScheme == 3) { // Ocean
            col = vec3(0.0, 0.3 + p.y * 0.3, 0.6 + sin(time + p.x * 5.0) * 0.3);
        } else if(colorScheme == 4) { // Neon
            col = vec3(
                0.5 + 0.5 * sin(time + p.x * 10.0),
                0.5 + 0.5 * cos(time + p.y * 10.0),
                0.5 + 0.5 * sin(time + p.z * 10.0)
            );
        } else { // Sunset
            col = vec3(1.0, 0.6, 0.4) * (0.5 + 0.5 * sin(time + length(p) * 2.0));
        }

        // Lighting
        vec3 lightPos = vec3(sin(time) * 5.0, 5.0, cos(time) * 5.0);
        vec3 lightDir = normalize(lightPos - p);
        float diff = max(dot(n, lightDir), 0.0);
        float amb = 0.2;

        col *= (amb + diff);

        // Fog
        col = mix(col, vec3(0.0), 1.0 - exp(-dist * 0.15));

        return col;
    }

    void main() {
        vec2 uv = (gl_FragCoord.xy - 0.5 * resolution) / resolution.y;

        // Camera
        vec3 ro = vec3(0.0, 0.0, zoom);
        vec3 rd = normalize(vec3(uv, -1.0));

        // Apply rotation
        rd.yz *= rot2D(rotation.x);
        rd.xz *= rot2D(rotation.y + time * 0.1 * float(autoRotate));
        ro.yz *= rot2D(rotation.x);
        ro.xz *= rot2D(rotation.y + time * 0.1 * float(autoRotate));

        // Raymarch
        float d = rayMarch(ro, rd);

        vec3 col = vec3(0.0);

        if(d < MAX_DIST) {
            vec3 p = ro + rd * d;
            vec3 n = getNormal(p);
            col = getColor(p, n, d);
        }

        // Gamma correction
        col = pow(col, vec3(0.4545));

        gl_FragColor = vec4(col, 1.0);
    }
`;

// Initialize WebGL
function initGL() {
    canvas = document.getElementById('fractal-canvas');
    gl = canvas.getContext('webgl', {
        alpha: false,
        antialias: false,
        powerPreference: 'high-performance'
    });

    if (!gl) {
        alert('WebGL no soportado en este dispositivo');
        return false;
    }

    // Detect quality
    const isMobile = /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);
    state.quality = isMobile ? 0.6 : 1.0;

    resize();
    window.addEventListener('resize', resize);

    return true;
}

function resize() {
    const dpr = Math.min(window.devicePixelRatio * state.quality, 2);
    canvas.width = window.innerWidth * dpr;
    canvas.height = window.innerHeight * dpr;
    canvas.style.width = window.innerWidth + 'px';
    canvas.style.height = window.innerHeight + 'px';
    gl.viewport(0, 0, canvas.width, canvas.height);
}

// Compile shaders
function createShader(type, source) {
    const shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        console.error('Shader compile error:', gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        return null;
    }
    return shader;
}

function createProgram() {
    const vertShader = createShader(gl.VERTEX_SHADER, vertexShaderSource);
    const fragShader = createShader(gl.FRAGMENT_SHADER, fragmentShaderSource);

    program = gl.createProgram();
    gl.attachShader(program, vertShader);
    gl.attachShader(program, fragShader);
    gl.linkProgram(program);

    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
        console.error('Program link error:', gl.getProgramInfoLog(program));
        return false;
    }

    gl.useProgram(program);

    // Create fullscreen quad
    const positions = new Float32Array([-1, -1, 1, -1, -1, 1, 1, 1]);
    const buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.bufferData(gl.ARRAY_BUFFER, positions, gl.STATIC_DRAW);

    const posLoc = gl.getAttribLocation(program, 'position');
    gl.enableVertexAttribArray(posLoc);
    gl.vertexAttribPointer(posLoc, 2, gl.FLOAT, false, 0, 0);

    return true;
}

// Render loop
function render() {
    if (!isVisible) return;

    state.time += 0.016 * state.speed;

    // Set uniforms
    gl.uniform2f(gl.getUniformLocation(program, 'resolution'), canvas.width, canvas.height);
    gl.uniform1f(gl.getUniformLocation(program, 'time'), state.time);
    gl.uniform2f(gl.getUniformLocation(program, 'rotation'), state.rotation.x, state.rotation.y);
    gl.uniform1f(gl.getUniformLocation(program, 'zoom'), state.zoom);
    gl.uniform1i(gl.getUniformLocation(program, 'autoRotate'), state.autoRotate ? 1 : 0);

    const fractalMap = { mandelbulb: 0, julia3d: 1, sierpinski: 2, menger: 3, psychedelic: 4 };
    gl.uniform1i(gl.getUniformLocation(program, 'fractalType'), fractalMap[state.fractal] || 0);

    const colorMap = { rainbow: 0, galaxy: 1, fire: 2, ocean: 3, neon: 4, sunset: 5 };
    gl.uniform1i(gl.getUniformLocation(program, 'colorScheme'), colorMap[state.colorScheme] || 0);

    // Draw
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

    animationId = requestAnimationFrame(render);
}

// Touch controls
function setupControls() {
    let touchStart = { x: 0, y: 0 };
    let touchDist = 0;

    canvas.addEventListener('touchstart', (e) => {
        e.preventDefault();
        if (e.touches.length === 1) {
            touchStart.x = e.touches[0].clientX;
            touchStart.y = e.touches[0].clientY;
        } else if (e.touches.length === 2) {
            const dx = e.touches[0].clientX - e.touches[1].clientX;
            const dy = e.touches[0].clientY - e.touches[1].clientY;
            touchDist = Math.sqrt(dx * dx + dy * dy);
        }
    });

    canvas.addEventListener('touchmove', (e) => {
        e.preventDefault();
        if (e.touches.length === 1) {
            const dx = e.touches[0].clientX - touchStart.x;
            const dy = e.touches[0].clientY - touchStart.y;
            state.rotation.y += dx * 0.01;
            state.rotation.x += dy * 0.01;
            touchStart.x = e.touches[0].clientX;
            touchStart.y = e.touches[0].clientY;
        } else if (e.touches.length === 2) {
            const dx = e.touches[0].clientX - e.touches[1].clientX;
            const dy = e.touches[0].clientY - e.touches[1].clientY;
            const dist = Math.sqrt(dx * dx + dy * dy);
            state.zoom += (touchDist - dist) * 0.01;
            state.zoom = Math.max(1, Math.min(8, state.zoom));
            touchDist = dist;
        }
    });

    // Mouse for desktop
    canvas.addEventListener('mousedown', (e) => {
        mouseDown = true;
        lastTouch = { x: e.clientX, y: e.clientY };
    });

    canvas.addEventListener('mousemove', (e) => {
        if (!mouseDown) return;
        const dx = e.clientX - lastTouch.x;
        const dy = e.clientY - lastTouch.y;
        state.rotation.y += dx * 0.01;
        state.rotation.x += dy * 0.01;
        lastTouch = { x: e.clientX, y: e.clientY };
    });

    canvas.addEventListener('mouseup', () => mouseDown = false);

    canvas.addEventListener('wheel', (e) => {
        e.preventDefault();
        state.zoom += e.deltaY * 0.01;
        state.zoom = Math.max(1, Math.min(8, state.zoom));
    }, { passive: false });
}

// UI bindings
function setupUI() {
    document.querySelectorAll('.fractal-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            document.querySelectorAll('.fractal-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            state.fractal = btn.dataset.fractal;
        });
    });

    document.querySelectorAll('.color-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            state.colorScheme = btn.dataset.color;
        });
    });

    document.getElementById('rotation-toggle').addEventListener('click', function() {
        state.autoRotate = !state.autoRotate;
        this.classList.toggle('active');
    });

    document.getElementById('speed-slider').addEventListener('input', (e) => {
        state.speed = e.target.value / 100;
    });

    document.getElementById('reset-btn').addEventListener('click', () => {
        state.rotation = { x: 0, y: 0 };
        state.zoom = 3.5;
    });
}

// Visibility API
document.addEventListener('visibilitychange', () => {
    isVisible = !document.hidden;
    if (isVisible) render();
});

// Initialize
async function init() {
    console.log('🚀 Ultra-Light Fractal Engine starting...');

    updateProgress(20);

    if (!initGL()) return;
    updateProgress(50);

    if (!createProgram()) return;
    updateProgress(70);

    setupControls();
    setupUI();
    updateProgress(100);

    // Hide loading screen
    setTimeout(() => {
        const loading = document.getElementById('loading-screen');
        loading.classList.add('fade-out');
        setTimeout(() => loading.remove(), 500);
    }, 200);

    // Start rendering
    render();

    console.log('✅ Ready! Bundle size: ~15KB (vs 1.27MB Three.js)');
}

function updateProgress(percent) {
    const fill = document.getElementById('progress-fill');
    if (fill) fill.style.width = percent + '%';
}

window.addEventListener('DOMContentLoaded', init);
