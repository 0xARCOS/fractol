import * as THREE from 'three';

// ==================== APPLICATION STATE ====================
const state = {
    currentFractal: 'mandelbulb',
    currentColorScheme: 'rainbow',
    autoRotate: true,
    particlesEnabled: true,
    pulseEnabled: false,
    glitchEnabled: false,
    speed: 1.0,
    quality: 'auto' // auto, low, medium, high
};

// ==================== THREE.JS SETUP ====================
let scene, camera, renderer, fractalMesh, particleSystem;
let clock, time = 0;
let composer;

// Performance tracking
let fps = 60;
let lastTime = performance.now();
let frames = 0;

// Touch controls
let touchStartX = 0, touchStartY = 0;
let touchStartDistance = 0;
let isDragging = false;
let rotation = { x: 0, y: 0 };
let cameraDistance = 5;
let cameraOffset = { x: 0, y: 0 };
let lastTapTime = 0;

// ==================== INITIALIZATION ====================
async function init() {
    try {
        // Show loading screen
        updateProgress(5, 'Iniciando...');

        // Check if Three.js loaded
        if (typeof THREE === 'undefined') {
            throw new Error('Three.js no se pudo cargar. Verifica tu conexión a internet.');
        }

        updateProgress(10, 'Three.js cargado');

        // Setup Three.js
        setupThreeJS();
        updateProgress(30, 'Configurando escena 3D...');

        // Create initial fractal (simplified for faster load)
        await createFractal(state.currentFractal);
        updateProgress(60, 'Generando fractal...');

        // Create particle system
        createParticles();
        updateProgress(80, 'Añadiendo partículas...');

        // Setup controls
        setupTouchControls();
        setupUI();
        updateProgress(95, 'Configurando controles...');

        // Start animation loop
        animate();
        updateProgress(100, 'Listo!');

        // Hide loading screen after short delay
        setTimeout(() => {
            document.getElementById('loading-screen').classList.add('fade-out');
            setTimeout(() => {
                document.getElementById('loading-screen').style.display = 'none';
            }, 500);
        }, 300);

    } catch (error) {
        console.error('Error durante la inicialización:', error);
        showError('Error: ' + error.message + '\n\nRecarga la página o verifica tu conexión.');
    }
}

function showError(message) {
    const errorEl = document.getElementById('error-message');
    const loadingText = document.getElementById('loading-text');
    if (errorEl && loadingText) {
        loadingText.textContent = '❌ Error al cargar';
        errorEl.textContent = message;
        errorEl.style.display = 'block';
    }
}

function setupThreeJS() {
    // Scene
    scene = new THREE.Scene();
    scene.fog = new THREE.Fog(0x000000, 8, 20);

    // Camera
    camera = new THREE.PerspectiveCamera(
        75,
        window.innerWidth / window.innerHeight,
        0.1,
        1000
    );
    camera.position.z = cameraDistance;

    // Renderer
    const canvas = document.getElementById('fractal-canvas');
    renderer = new THREE.WebGLRenderer({
        canvas,
        antialias: window.innerWidth < 768 ? false : true,
        alpha: true,
        powerPreference: 'high-performance'
    });
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
    renderer.toneMapping = THREE.ACESFilmicToneMapping;
    renderer.toneMappingExposure = 1.5;

    // Lighting
    const ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
    scene.add(ambientLight);

    const pointLight1 = new THREE.PointLight(0xff0080, 2, 100);
    pointLight1.position.set(5, 5, 5);
    scene.add(pointLight1);

    const pointLight2 = new THREE.PointLight(0x00ffff, 2, 100);
    pointLight2.position.set(-5, -5, 5);
    scene.add(pointLight2);

    clock = new THREE.Clock();

    // Handle resize
    window.addEventListener('resize', onWindowResize, false);

    // Detect performance
    detectPerformance();
}

function detectPerformance() {
    // Auto-adjust quality based on device
    const isMobile = /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);
    const hasGoodGPU = renderer.capabilities.maxTextures > 16;

    if (isMobile && !hasGoodGPU) {
        state.quality = 'low';
    } else if (isMobile) {
        state.quality = 'medium';
    } else {
        state.quality = 'high';
    }
}

// ==================== FRACTAL GENERATION ====================
async function createFractal(type) {
    // Remove existing fractal
    if (fractalMesh) {
        scene.remove(fractalMesh);
        fractalMesh.geometry.dispose();
        fractalMesh.material.dispose();
    }

    // Create new fractal based on type
    switch(type) {
        case 'mandelbulb':
            fractalMesh = createMandelbulb();
            break;
        case 'julia3d':
            fractalMesh = createJulia3D();
            break;
        case 'sierpinski':
            fractalMesh = createSierpinski();
            break;
        case 'menger':
            fractalMesh = createMenger();
            break;
        case 'psychedelic':
            fractalMesh = createPsychedelicSphere();
            break;
        default:
            fractalMesh = createMandelbulb();
    }

    scene.add(fractalMesh);
    updateColorScheme(state.currentColorScheme);
}

function createMandelbulb() {
    // Reduced complexity for faster initial load
    const subdivisions = state.quality === 'high' ? 3 : state.quality === 'medium' ? 2 : 1;
    const geometry = new THREE.IcosahedronGeometry(2, subdivisions);

    // Apply mandelbulb deformation
    const positions = geometry.attributes.position.array;
    for (let i = 0; i < positions.length; i += 3) {
        let x = positions[i];
        let y = positions[i + 1];
        let z = positions[i + 2];

        const r = Math.sqrt(x*x + y*y + z*z);
        const theta = Math.atan2(Math.sqrt(x*x + y*y), z);
        const phi = Math.atan2(y, x);

        const power = 8;
        const newR = Math.pow(r, power);
        const newTheta = theta * power;
        const newPhi = phi * power;

        positions[i] = newR * Math.sin(newTheta) * Math.cos(newPhi);
        positions[i + 1] = newR * Math.sin(newTheta) * Math.sin(newPhi);
        positions[i + 2] = newR * Math.cos(newTheta);
    }

    geometry.attributes.position.needsUpdate = true;
    geometry.computeVertexNormals();

    const material = new THREE.MeshPhongMaterial({
        color: 0xffffff,
        shininess: 100,
        flatShading: false,
        wireframe: false
    });

    return new THREE.Mesh(geometry, material);
}

function createJulia3D() {
    const segments = state.quality === 'high' ? 48 : state.quality === 'medium' ? 32 : 24;
    const geometry = new THREE.SphereGeometry(2, segments, segments);

    const positions = geometry.attributes.position.array;
    for (let i = 0; i < positions.length; i += 3) {
        let x = positions[i];
        let y = positions[i + 1];
        let z = positions[i + 2];

        // Julia set transformation
        const c = { x: 0.4, y: 0.4, z: 0.2 };
        for (let j = 0; j < 3; j++) {
            const xNew = x*x - y*y - z*z + c.x;
            const yNew = 2*x*y + c.y;
            const zNew = 2*x*z + c.z;
            x = xNew; y = yNew; z = zNew;
        }

        const scale = 0.5;
        positions[i] += x * scale;
        positions[i + 1] += y * scale;
        positions[i + 2] += z * scale;
    }

    geometry.attributes.position.needsUpdate = true;
    geometry.computeVertexNormals();

    const material = new THREE.MeshPhongMaterial({
        color: 0xffffff,
        shininess: 100,
        flatShading: false
    });

    return new THREE.Mesh(geometry, material);
}

function createSierpinski() {
    const group = new THREE.Group();

    function addTetrahedron(x, y, z, size, depth) {
        if (depth === 0) {
            const geometry = new THREE.TetrahedronGeometry(size);
            const material = new THREE.MeshPhongMaterial({
                color: 0xffffff,
                shininess: 100
            });
            const mesh = new THREE.Mesh(geometry, material);
            mesh.position.set(x, y, z);
            group.add(mesh);
        } else {
            const newSize = size / 2;
            const offset = size / 2;

            addTetrahedron(x, y + offset, z, newSize, depth - 1);
            addTetrahedron(x - offset, y - offset, z + offset, newSize, depth - 1);
            addTetrahedron(x + offset, y - offset, z + offset, newSize, depth - 1);
            addTetrahedron(x, y - offset, z - offset, newSize, depth - 1);
        }
    }

    const maxDepth = state.quality === 'high' ? 3 : state.quality === 'medium' ? 2 : 1;
    addTetrahedron(0, 0, 0, 2, maxDepth);

    return group;
}

function createMenger() {
    const group = new THREE.Group();

    function addCube(x, y, z, size, depth) {
        if (depth === 0) {
            const geometry = new THREE.BoxGeometry(size, size, size);
            const material = new THREE.MeshPhongMaterial({
                color: 0xffffff,
                shininess: 100
            });
            const mesh = new THREE.Mesh(geometry, material);
            mesh.position.set(x, y, z);
            group.add(mesh);
        } else {
            const newSize = size / 3;
            for (let i = -1; i <= 1; i++) {
                for (let j = -1; j <= 1; j++) {
                    for (let k = -1; k <= 1; k++) {
                        const sum = Math.abs(i) + Math.abs(j) + Math.abs(k);
                        if (sum > 1) {
                            addCube(
                                x + i * newSize,
                                y + j * newSize,
                                z + k * newSize,
                                newSize,
                                depth - 1
                            );
                        }
                    }
                }
            }
        }
    }

    const maxDepth = state.quality === 'high' ? 2 : 1;
    addCube(0, 0, 0, 2, maxDepth);

    return group;
}

function createPsychedelicSphere() {
    const segments = state.quality === 'high' ? 64 : state.quality === 'medium' ? 48 : 32;
    const geometry = new THREE.SphereGeometry(2, segments, segments);

    const positions = geometry.attributes.position.array;
    for (let i = 0; i < positions.length; i += 3) {
        const x = positions[i];
        const y = positions[i + 1];
        const z = positions[i + 2];

        const noise = Math.sin(x * 3) * Math.cos(y * 3) * Math.sin(z * 3) * 0.3;
        const r = Math.sqrt(x*x + y*y + z*z);
        const scale = 1 + noise;

        positions[i] = x * scale / r * 2;
        positions[i + 1] = y * scale / r * 2;
        positions[i + 2] = z * scale / r * 2;
    }

    geometry.attributes.position.needsUpdate = true;
    geometry.computeVertexNormals();

    const material = new THREE.MeshPhongMaterial({
        color: 0xffffff,
        shininess: 100,
        flatShading: false
    });

    return new THREE.Mesh(geometry, material);
}

// ==================== PARTICLES ====================
function createParticles() {
    // Reduced particle count for better performance
    const particleCount = state.quality === 'high' ? 1000 : state.quality === 'medium' ? 500 : 300;
    const geometry = new THREE.BufferGeometry();
    const positions = new Float32Array(particleCount * 3);
    const colors = new Float32Array(particleCount * 3);
    const sizes = new Float32Array(particleCount);

    for (let i = 0; i < particleCount; i++) {
        const i3 = i * 3;

        // Random position in sphere
        const theta = Math.random() * Math.PI * 2;
        const phi = Math.acos(Math.random() * 2 - 1);
        const radius = 5 + Math.random() * 10;

        positions[i3] = radius * Math.sin(phi) * Math.cos(theta);
        positions[i3 + 1] = radius * Math.sin(phi) * Math.sin(theta);
        positions[i3 + 2] = radius * Math.cos(phi);

        // Random color
        colors[i3] = Math.random();
        colors[i3 + 1] = Math.random();
        colors[i3 + 2] = Math.random();

        sizes[i] = Math.random() * 2 + 1;
    }

    geometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
    geometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));
    geometry.setAttribute('size', new THREE.BufferAttribute(sizes, 1));

    const material = new THREE.PointsMaterial({
        size: 0.1,
        vertexColors: true,
        transparent: true,
        opacity: 0.6,
        blending: THREE.AdditiveBlending,
        sizeAttenuation: true
    });

    particleSystem = new THREE.Points(geometry, material);
    scene.add(particleSystem);
}

// ==================== COLOR SCHEMES ====================
function updateColorScheme(scheme) {
    if (!fractalMesh) return;

    const colorSchemes = {
        rainbow: [0xff0080, 0xff8c00, 0xffff00, 0x00ff00, 0x00ffff, 0x0080ff],
        galaxy: [0x000428, 0x004e92, 0x6a0dad, 0xff00ff],
        fire: [0xff0000, 0xff4500, 0xffa500, 0xffff00],
        ocean: [0x000080, 0x0000ff, 0x00ffff, 0x00ff00],
        neon: [0xff00ff, 0x00ffff, 0x00ff00, 0xffff00],
        sunset: [0xff6b6b, 0xfeca57, 0xee5a6f, 0xff9ff3]
    };

    const colors = colorSchemes[scheme] || colorSchemes.rainbow;

    if (fractalMesh.material) {
        fractalMesh.material.color.setHex(colors[Math.floor(Math.random() * colors.length)]);
    }

    // Update particle colors
    if (particleSystem) {
        const particleColors = particleSystem.geometry.attributes.color.array;
        for (let i = 0; i < particleColors.length; i += 3) {
            const color = new THREE.Color(colors[Math.floor(Math.random() * colors.length)]);
            particleColors[i] = color.r;
            particleColors[i + 1] = color.g;
            particleColors[i + 2] = color.b;
        }
        particleSystem.geometry.attributes.color.needsUpdate = true;
    }
}

// ==================== TOUCH CONTROLS ====================
function setupTouchControls() {
    const canvas = document.getElementById('fractal-canvas');

    canvas.addEventListener('touchstart', handleTouchStart, { passive: false });
    canvas.addEventListener('touchmove', handleTouchMove, { passive: false });
    canvas.addEventListener('touchend', handleTouchEnd, { passive: false });

    // Also support mouse for testing
    canvas.addEventListener('mousedown', (e) => {
        isDragging = true;
        touchStartX = e.clientX;
        touchStartY = e.clientY;
    });

    canvas.addEventListener('mousemove', (e) => {
        if (!isDragging) return;

        const deltaX = e.clientX - touchStartX;
        const deltaY = e.clientY - touchStartY;

        rotation.y += deltaX * 0.005;
        rotation.x += deltaY * 0.005;

        touchStartX = e.clientX;
        touchStartY = e.clientY;
    });

    canvas.addEventListener('mouseup', () => {
        isDragging = false;
    });

    canvas.addEventListener('wheel', (e) => {
        e.preventDefault();
        cameraDistance += e.deltaY * 0.01;
        cameraDistance = Math.max(2, Math.min(15, cameraDistance));
    }, { passive: false });
}

function handleTouchStart(e) {
    e.preventDefault();

    // Double tap detection
    const currentTime = Date.now();
    if (currentTime - lastTapTime < 300) {
        resetCamera();
    }
    lastTapTime = currentTime;

    if (e.touches.length === 1) {
        isDragging = true;
        touchStartX = e.touches[0].clientX;
        touchStartY = e.touches[0].clientY;
    } else if (e.touches.length === 2) {
        const dx = e.touches[0].clientX - e.touches[1].clientX;
        const dy = e.touches[0].clientY - e.touches[1].clientY;
        touchStartDistance = Math.sqrt(dx * dx + dy * dy);
        touchStartX = (e.touches[0].clientX + e.touches[1].clientX) / 2;
        touchStartY = (e.touches[0].clientY + e.touches[1].clientY) / 2;
    }
}

function handleTouchMove(e) {
    e.preventDefault();

    if (e.touches.length === 1 && isDragging) {
        const deltaX = e.touches[0].clientX - touchStartX;
        const deltaY = e.touches[0].clientY - touchStartY;

        rotation.y += deltaX * 0.01;
        rotation.x += deltaY * 0.01;
        rotation.x = Math.max(-Math.PI / 2, Math.min(Math.PI / 2, rotation.x));

        touchStartX = e.touches[0].clientX;
        touchStartY = e.touches[0].clientY;
    } else if (e.touches.length === 2) {
        // Pinch to zoom
        const dx = e.touches[0].clientX - e.touches[1].clientX;
        const dy = e.touches[0].clientY - e.touches[1].clientY;
        const distance = Math.sqrt(dx * dx + dy * dy);

        const delta = touchStartDistance - distance;
        cameraDistance += delta * 0.01;
        cameraDistance = Math.max(2, Math.min(15, cameraDistance));

        touchStartDistance = distance;

        // Pan
        const centerX = (e.touches[0].clientX + e.touches[1].clientX) / 2;
        const centerY = (e.touches[0].clientY + e.touches[1].clientY) / 2;

        const panDeltaX = centerX - touchStartX;
        const panDeltaY = centerY - touchStartY;

        cameraOffset.x += panDeltaX * 0.01;
        cameraOffset.y -= panDeltaY * 0.01;

        touchStartX = centerX;
        touchStartY = centerY;
    }
}

function handleTouchEnd(e) {
    if (e.touches.length === 0) {
        isDragging = false;
    } else if (e.touches.length === 1) {
        touchStartX = e.touches[0].clientX;
        touchStartY = e.touches[0].clientY;
    }
}

function resetCamera() {
    rotation.x = 0;
    rotation.y = 0;
    cameraDistance = 5;
    cameraOffset.x = 0;
    cameraOffset.y = 0;
}

// ==================== UI SETUP ====================
function setupUI() {
    // Fractal buttons
    document.querySelectorAll('.fractal-btn').forEach(btn => {
        btn.addEventListener('click', async () => {
            document.querySelectorAll('.fractal-btn').forEach(b => b.classList.remove('active'));
            btn.classList.add('active');

            const fractalType = btn.dataset.fractal;
            state.currentFractal = fractalType;
            await createFractal(fractalType);

            document.getElementById('fractal-name').textContent =
                fractalType.charAt(0).toUpperCase() + fractalType.slice(1);
        });
    });

    // Color buttons
    document.querySelectorAll('.color-btn').forEach(btn => {
        btn.addEventListener('click', () => {
            const colorScheme = btn.dataset.color;
            state.currentColorScheme = colorScheme;
            updateColorScheme(colorScheme);
        });
    });

    // Effect toggles
    document.getElementById('rotation-toggle').addEventListener('click', function() {
        state.autoRotate = !state.autoRotate;
        this.classList.toggle('active');
    });

    document.getElementById('particles-toggle').addEventListener('click', function() {
        state.particlesEnabled = !state.particlesEnabled;
        this.classList.toggle('active');
        if (particleSystem) {
            particleSystem.visible = state.particlesEnabled;
        }
    });

    document.getElementById('pulse-toggle').addEventListener('click', function() {
        state.pulseEnabled = !state.pulseEnabled;
        this.classList.toggle('active');
    });

    document.getElementById('glitch-toggle').addEventListener('click', function() {
        state.glitchEnabled = !state.glitchEnabled;
        this.classList.toggle('active');
    });

    // Speed slider
    document.getElementById('speed-slider').addEventListener('input', (e) => {
        state.speed = e.target.value / 100;
    });

    // Toggle UI
    document.getElementById('toggle-ui').addEventListener('click', () => {
        document.querySelector('.bottom-controls').classList.toggle('collapsed');
    });

    // Reset button
    document.getElementById('reset-btn').addEventListener('click', resetCamera);

    // Fullscreen button
    document.getElementById('fullscreen-btn').addEventListener('click', toggleFullscreen);

    // Start button
    document.getElementById('start-btn').addEventListener('click', () => {
        document.getElementById('instructions').classList.add('hidden');
        document.getElementById('ui-container').classList.remove('hidden');
    });
}

function toggleFullscreen() {
    if (!document.fullscreenElement) {
        document.documentElement.requestFullscreen();
    } else {
        if (document.exitFullscreen) {
            document.exitFullscreen();
        }
    }
}

// ==================== ANIMATION LOOP ====================
function animate() {
    requestAnimationFrame(animate);

    const delta = clock.getDelta();
    time += delta * state.speed;

    // Update FPS
    frames++;
    const currentTime = performance.now();
    if (currentTime >= lastTime + 1000) {
        fps = Math.round((frames * 1000) / (currentTime - lastTime));
        document.getElementById('fps-counter').textContent = fps + ' FPS';
        frames = 0;
        lastTime = currentTime;
    }

    // Update fractal
    if (fractalMesh) {
        if (state.autoRotate) {
            fractalMesh.rotation.x = rotation.x + time * 0.2;
            fractalMesh.rotation.y = rotation.y + time * 0.3;
        } else {
            fractalMesh.rotation.x = rotation.x;
            fractalMesh.rotation.y = rotation.y;
        }

        // Pulse effect
        if (state.pulseEnabled) {
            const scale = 1 + Math.sin(time * 2) * 0.1;
            fractalMesh.scale.set(scale, scale, scale);
        } else {
            fractalMesh.scale.set(1, 1, 1);
        }

        // Glitch effect
        if (state.glitchEnabled && Math.random() < 0.05) {
            fractalMesh.position.x = (Math.random() - 0.5) * 0.1;
            fractalMesh.position.y = (Math.random() - 0.5) * 0.1;
        } else {
            fractalMesh.position.x = 0;
            fractalMesh.position.y = 0;
        }
    }

    // Update particles
    if (particleSystem && state.particlesEnabled) {
        particleSystem.rotation.y = time * 0.1;
        particleSystem.rotation.x = Math.sin(time * 0.5) * 0.2;
    }

    // Update camera
    camera.position.x = Math.sin(rotation.y) * cameraDistance + cameraOffset.x;
    camera.position.y = Math.sin(rotation.x) * cameraDistance + cameraOffset.y;
    camera.position.z = Math.cos(rotation.y) * Math.cos(rotation.x) * cameraDistance;
    camera.lookAt(0, 0, 0);

    renderer.render(scene, camera);
}

// ==================== WINDOW RESIZE ====================
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}

// ==================== PROGRESS ====================
function updateProgress(percent, text) {
    const progressFill = document.getElementById('progress-fill');
    const loadingText = document.getElementById('loading-text');
    if (progressFill) {
        progressFill.style.width = percent + '%';
    }
    if (loadingText && text) {
        loadingText.textContent = text;
    }
}

// ==================== LOADING TIMEOUT ====================
let loadTimeout;

// ==================== START APPLICATION ====================
window.addEventListener('DOMContentLoaded', () => {
    // Set timeout for loading
    loadTimeout = setTimeout(() => {
        if (typeof THREE === 'undefined') {
            showError('La carga está tardando demasiado. Posibles causas:\n\n' +
                      '1. Conexión lenta a internet\n' +
                      '2. CDN de Three.js no disponible\n' +
                      '3. Bloqueador de contenido activo\n\n' +
                      'Intenta:\n' +
                      '- Recargar la página\n' +
                      '- Verificar tu conexión\n' +
                      '- Desactivar bloqueadores de contenido');
        }
    }, 10000); // 10 seconds timeout

    init().then(() => {
        clearTimeout(loadTimeout);
    });
});
