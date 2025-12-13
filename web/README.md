# 🌐 Fract-ol Web Extensions

Extensiones web y contenido viral para el proyecto Fract-ol.

---

## 📱 Mobile Fractal 3D

Aplicación web progresiva (PWA) para visualizar fractales en dispositivos móviles.

**Características:**
- ✅ Funciona sin conexión (PWA)
- ✅ Optimizado para móviles
- ✅ Renderizado 3D interactivo
- ✅ Compatible con touch gestures

### Inicio Rápido

```bash
cd mobile-fractal-3d
# Abrir public/index.html en tu navegador
```

Para desarrollo:
```bash
# Si tienes un servidor local
python3 -m http.server 8000
# o
npx http-server public
```

---

## 🔥 Contenido Viral

### 🔮 Fractal Soul Generator

Genera fractales únicos basados en nombres y fechas de nacimiento.

```bash
cd ../mandatory
./fractol soul "Tu Nombre" 15 06 1995
```

### ⭐ Horóscopo Fractal

Predicciones diarias basadas en patrones fractales.

```bash
./fractol horoscope aries
```

### 👑 Fractales de Celebridades

Visualiza los fractales de personas famosas:

```bash
./fractol celebrity messi
./fractol celebrity einstein
./fractol celebrity badBunny
```

---

## 📚 Documentación

- [📖 Guía Viral Completa](./docs/VIRAL_README.md)
- [💡 Ideas Virales](./docs/VIRAL_IDEAS.md)
- [📱 Templates para Redes Sociales](./docs/SOCIAL_MEDIA_TEMPLATES.md)

---

## 🎯 Uso para Redes Sociales

### Instagram/TikTok

1. Genera tu fractal soul
2. Captura screenshot (automático)
3. Comparte con el hashtag #FractalSoul

### Share Codes

Cada fractal genera un código único que puedes compartir:

```
Código: FS-A8B2C4D6
```

---

## 🚀 Deploy (Netlify)

El archivo `netlify.toml` está configurado para deployment automático.

```bash
# El sitio se despliega desde mobile-fractal-3d/public/
```

---

## 📊 Estructura

```
web/
├── mobile-fractal-3d/      # PWA principal
│   ├── public/             # Archivos estáticos
│   │   ├── index.html
│   │   ├── app.js
│   │   ├── app-lite.js
│   │   ├── style.css
│   │   └── sw.js           # Service Worker
│   └── test/               # Tests
├── docs/                   # Documentación viral
│   ├── VIRAL_README.md
│   ├── VIRAL_IDEAS.md
│   └── SOCIAL_MEDIA_TEMPLATES.md
├── netlify.toml            # Config de deploy
└── README.md               # Este archivo
```

---

## 🛠️ Tecnologías

- HTML5 Canvas
- JavaScript (Vanilla)
- WebGL (para 3D)
- Service Workers (PWA)
- CSS3

---

## 🤝 Contribuciones

Las ideas virales son bienvenidas! Consulta [VIRAL_IDEAS.md](./docs/VIRAL_IDEAS.md) para inspiración.

---

## 🔗 Enlaces

- [Proyecto Principal](../)
- [Proyecto Mandatory](../mandatory/)
- [Documentación General](../docs/)

---

<div align="center">

**🌟 Comparte tus fractales con #FractalSoul 🌟**

</div>
