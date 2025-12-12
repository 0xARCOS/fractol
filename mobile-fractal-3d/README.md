# 🌀 Fractal 3D Mobile Experience

Una experiencia inmersiva de fractales 3D psicodélicos optimizada para dispositivos móviles.

## ✨ Características

- 🎨 **Múltiples fractales 3D**: Mandelbulb, Julia Sets 3D, Sierpinski, y más
- 📱 **Optimizado para móvil**: Controles táctiles intuitivos y rendimiento optimizado
- 🌈 **Efectos psicodélicos**: Colores vibrantes, partículas, y transiciones suaves
- 🎮 **Interactivo**: Toca, arrastra, pellizca para explorar
- 🎵 **Audio reactivo**: Experiencia audiovisual sincronizada (opcional)
- ⚡ **Rendimiento**: Usa WebGL y Three.js para gráficos fluidos

## 🚀 Deployment en Netlify

### Opción 1: Deploy desde Git
1. Conecta tu repositorio a Netlify
2. Build settings:
   - Base directory: `mobile-fractal-3d`
   - Publish directory: `mobile-fractal-3d/public`
   - Build command: (dejar vacío)

### Opción 2: Deploy manual
```bash
cd mobile-fractal-3d
netlify deploy --prod --dir=public
```

## 🧪 Testing local

```bash
cd mobile-fractal-3d
npm run dev
# Abre http://localhost:8080 en tu navegador
```

## 📱 Controles Móviles

- **Un dedo**: Rotar el fractal
- **Dos dedos (pinch)**: Zoom in/out
- **Dos dedos (arrastrar)**: Mover cámara
- **Tap en UI**: Cambiar fractal, colores, efectos
- **Tap doble**: Reset cámara

## 🎨 Fractales Disponibles

1. **Mandelbulb**: El icónico fractal 3D
2. **Julia Set 3D**: Variaciones psicodélicas del conjunto de Julia
3. **Sierpinski Pyramid**: Fractal geométrico clásico
4. **Menger Sponge**: Cubo fractal infinito
5. **Psychedelic Sphere**: Esfera con distorsiones fractales

## 🔧 Tecnologías

- Three.js (WebGL)
- Vanilla JavaScript (ES6+)
- CSS3 con animaciones
- Web Audio API (opcional)

## 📄 Licencia

MIT License - Ver archivo LICENSE para más detalles
