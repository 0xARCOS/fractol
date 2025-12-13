# 🌟 Características de Fractal 3D Mobile Experience

## 🎨 Fractales Disponibles

### 1. Mandelbulb 🔮
- El fractal 3D más icónico
- Basado en el conjunto de Mandelbrot extendido a 3D
- Deformación con power 8 para máximo detalle
- Geometría adaptativa según rendimiento del dispositivo

### 2. Julia Set 3D ✨
- Variación 3D del conjunto de Julia
- Transformaciones iterativas complejas
- Parámetros: c = (0.4, 0.4, 0.2)
- 3 iteraciones para balance rendimiento/calidad

### 3. Sierpinski Pyramid 🔺
- Fractal geométrico clásico recursivo
- Tetraedros anidados
- Profundidad adaptativa (1-3 niveles según dispositivo)
- Autosimilaridad perfecta

### 4. Menger Sponge 🧊
- Cubo fractal infinito
- Basado en el conjunto de Cantor 3D
- Profundidad 1-2 según rendimiento
- 20 cubos por iteración

### 5. Psychedelic Sphere 🌈
- Esfera con distorsiones fractales
- Función de ruido: sin(x*3) * cos(y*3) * sin(z*3)
- Alta densidad de vértices para suavidad
- Perfecto para efectos psicodélicos

## 🎨 Esquemas de Color

### Rainbow 🌈
Colores vibrantes del arcoíris:
- Rosa (#ff0080)
- Naranja (#ff8c00)
- Amarillo (#ffff00)
- Verde (#00ff00)
- Cyan (#00ffff)
- Azul (#0080ff)

### Galaxy 🌌
Espacio profundo:
- Azul oscuro (#000428)
- Azul medio (#004e92)
- Púrpura (#6a0dad)
- Magenta (#ff00ff)

### Fire 🔥
Llamas ardientes:
- Rojo (#ff0000)
- Rojo-naranja (#ff4500)
- Naranja (#ffa500)
- Amarillo (#ffff00)

### Ocean 🌊
Profundidades marinas:
- Azul marino (#000080)
- Azul (#0000ff)
- Cyan (#00ffff)
- Verde agua (#00ff00)

### Neon 💡
Luces de neón:
- Magenta (#ff00ff)
- Cyan (#00ffff)
- Verde lima (#00ff00)
- Amarillo (#ffff00)

### Sunset 🌅
Atardecer cálido:
- Rosa coral (#ff6b6b)
- Dorado (#feca57)
- Rosa fuerte (#ee5a6f)
- Rosa claro (#ff9ff3)

## ✨ Efectos Disponibles

### Auto-Rotación 🔄
- Rotación automática suave del fractal
- Velocidad ajustable (0-200%)
- Se combina con rotación manual
- Eje X: 0.2 rad/s
- Eje Y: 0.3 rad/s

### Partículas ⭐
- Sistema de partículas 3D inmersivo
- Cantidad adaptativa: 500-2000 partículas
- Colores que coinciden con el esquema actual
- Movimiento orbital suave
- Blending aditivo para efecto brillante
- Tamaños variables (1-3 unidades)

### Pulso 💓
- Efecto de pulsación rítmica
- Escala oscila entre 0.9x y 1.1x
- Frecuencia: 2 Hz (120 BPM)
- Sincronizado con animación

### Glitch 📺
- Efecto glitch aleatorio
- Probabilidad 5% por frame
- Desplazamiento máximo: ±0.1 unidades
- Vuelve a posición original suavemente

## 🎮 Controles Móviles

### Gestos Táctiles

#### Un Dedo 👆
- **Acción**: Rotar fractal
- **Sensibilidad**: 0.01 rad/pixel
- **Límites**: Pitch limitado a ±90°

#### Dos Dedos - Pinch 🤏
- **Acción**: Zoom in/out
- **Rango**: 2-15 unidades
- **Sensibilidad**: 0.01 unidades/pixel

#### Dos Dedos - Arrastrar ✌️
- **Acción**: Pan (mover cámara)
- **Sensibilidad**: 0.01 unidades/pixel
- **Sin límites de desplazamiento

#### Tap Doble 👇👇
- **Acción**: Reset cámara
- **Timeout**: 300ms entre taps
- **Restaura**: posición, rotación, zoom

### Controles de Ratón (Desktop)

#### Click + Arrastrar
- Rotar fractal
- Sensibilidad: 0.005 rad/pixel

#### Rueda del Ratón
- Zoom in/out
- Sensibilidad: 0.01 unidades/scroll

## 📊 Optimización de Rendimiento

### Detección Automática de Calidad

#### High Quality (Desktop/Tablets modernos)
- Geometrías: IcosahedronGeometry nivel 4
- Partículas: 2000
- Antialiasing: Activado
- Sierpinski: 3 niveles
- Menger: 2 niveles

#### Medium Quality (Móviles modernos)
- Geometrías: IcosahedronGeometry nivel 3
- Partículas: 1000
- Antialiasing: Desactivado
- Sierpinski: 2 niveles
- Menger: 1 nivel

#### Low Quality (Móviles antiguos)
- Geometrías: IcosahedronGeometry nivel 2
- Partículas: 500
- Antialiasing: Desactivado
- Sierpinski: 1 nivel
- Menger: 1 nivel

### Criterios de Detección
```javascript
const isMobile = /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);
const hasGoodGPU = renderer.capabilities.maxTextures > 16;
```

### Optimizaciones Adicionales
- PixelRatio limitado a 2x
- Geometry sharing cuando es posible
- Dispose correcto de geometrías/materiales
- requestAnimationFrame para animaciones
- Fog para reducir draw calls lejanos

## 📱 Progressive Web App (PWA)

### Características PWA

#### Instalable
- Manifest.json incluido
- Puede agregarse a pantalla de inicio
- Funciona como app nativa

#### Fullscreen
- Modo display: fullscreen
- Sin barras de navegación
- Experiencia inmersiva completa

#### Offline-Ready
- Assets estáticos cacheados por navegador
- Funciona sin conexión después de primera carga

#### Icono Personalizado
- SVG adaptativo
- Gradient rosa-cyan
- Diseño fractal minimalista
- Sizes: 192x192, 512x512

## 🎯 Características Técnicas

### Three.js Setup
- **Renderer**: WebGLRenderer
- **Camera**: PerspectiveCamera (FOV 75°)
- **Lights**:
  - AmbientLight (0.5 intensidad)
  - PointLight rosa (#ff0080, intensidad 2)
  - PointLight cyan (#00ffff, intensidad 2)
- **Tone Mapping**: ACESFilmic
- **Exposure**: 1.5

### Materiales
- MeshPhongMaterial
- Shininess: 100
- Smooth shading (excepto donde se especifica flatShading)
- Color dinámico según esquema

### Geometrías
- IcosahedronGeometry (esferas subdivididas)
- SphereGeometry (julia, psychedelic)
- TetrahedronGeometry (sierpinski)
- BoxGeometry (menger)

## 📐 Sistema de Coordenadas

### Cámara
- **Posición inicial**: (0, 0, 5)
- **Target**: (0, 0, 0)
- **Up**: (0, 1, 0)

### Fractales
- **Escala**: 2 unidades de radio
- **Centro**: (0, 0, 0)
- **Rotación**: Controlada por usuario

### Partículas
- **Distribución**: Esférica uniforme
- **Radio**: 5-15 unidades
- **Centro**: (0, 0, 0)

## 🔊 Audio (Preparado para expansión)

El código está preparado para añadir:
- Web Audio API
- Análisis de frecuencias
- Sincronización con efectos visuales
- Música de fondo

Para activar (futuro):
```javascript
// En app.js, descomentar y añadir:
const audioContext = new AudioContext();
const analyser = audioContext.createAnalyser();
// ... conectar con efectos
```

## 🌐 Compatibilidad

### Navegadores Soportados
- ✅ Chrome 90+ (Desktop/Mobile)
- ✅ Safari 14+ (Desktop/iOS)
- ✅ Firefox 88+
- ✅ Edge 90+
- ✅ Samsung Internet 14+
- ✅ Opera 76+

### Tecnologías Utilizadas
- ES6+ Modules
- WebGL 1.0/2.0
- Touch Events API
- Pointer Events
- ResizeObserver
- RequestAnimationFrame
- CSS3 Transforms
- CSS Grid/Flexbox
- CSS Custom Properties
- Backdrop Filter

### Requerimientos Mínimos
- WebGL habilitado
- JavaScript habilitado
- 512MB RAM mínimo
- GPU compatible con WebGL

## 🎨 Paleta de Colores del UI

### Primarios
- Primary: #ff0080 (Rosa)
- Secondary: #00ffff (Cyan)

### Fondos
- Dark: #000000
- Overlay: rgba(0, 0, 0, 0.85)
- Panel: rgba(20, 20, 40, 0.95)

### Efectos
- Glow: rgba(255, 0, 128, 0.5)
- Border: rgba(255, 255, 255, 0.1)
- Backdrop Blur: 10px-20px

## 📏 Dimensiones y Espaciado

### Border Radius
- Botones: 10-15px
- Paneles: 15px
- Toggle UI: 50% (circular)

### Padding
- Paneles: 20-30px
- Botones: 12-18px
- Container: 15-20px

### Gaps
- Grid: 10px
- Flex: 5-15px

## ⚡ Rendimiento en Números

### FPS Target
- Desktop: 60 FPS
- Mobile High-end: 60 FPS
- Mobile Mid-range: 30-60 FPS
- Mobile Low-end: 30 FPS

### Draw Calls (aprox)
- Mandelbulb: 1
- Sierpinski (depth 3): 85
- Menger (depth 2): 400
- Partículas: 1
- Lights: 3
- **Total típico**: 5-500 draw calls

### Vértices (aprox)
- Mandelbulb (high): 10,242
- Julia 3D (high): 16,384
- Psychedelic (high): 65,536
- Partículas: 500-2000
- **Total máximo**: ~70,000 vértices

## 🎯 Próximas Características (Roadmap)

- [ ] Audio reactivo
- [ ] Más fractales (Koch Snowflake 3D, Dragon Curve 3D)
- [ ] Modo VR/AR (WebXR)
- [ ] Grabación de video/screenshot
- [ ] Parámetros personalizables por usuario
- [ ] Modo "viaje" automático
- [ ] Multiplayer (compartir sesión)
- [ ] Galería de presets guardados

---

## 📝 Notas de Desarrollo

### Estructura Modular
El código está organizado en secciones:
1. State management
2. Three.js setup
3. Fractal generation
4. Particle system
5. Color schemes
6. Touch controls
7. UI setup
8. Animation loop
9. Window resize
10. Progress tracking

### Extensibilidad
Fácil de extender:
- Nuevos fractales: añadir función create*()
- Nuevos colores: añadir en colorSchemes
- Nuevos efectos: añadir en animate()

### Performance Monitoring
- FPS counter en tiempo real
- Auto-ajuste de calidad
- Dispose correcto para evitar memory leaks

---

¡Disfruta explorando las dimensiones fractales! 🌀✨
