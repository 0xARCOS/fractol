<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/fract-ol-light.png#gh-light-mode-only" alt="Banner (claro)" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/fract-ol-dark.png#gh-dark-mode-only" alt="Banner (oscuro)" />
    <a href='https://profile.intra.42.fr/users/aarcos' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Madrid-black?style=flat&logo=42&logoColor=white'/>
    </a>
    <img src="https://img.shields.io/badge/120%20%2F%20100-success?color=%2312bab9&style=flat" />
    <img src="https://api.visitorbadge.io/api/visitors?user=0xARCOS&repo=fractol_42&label=visitas&countColor=%2385e3ff&style=flat&labelStyle=none"/>
</div>

---

# 🎨 Fract-ol Project

Un proyecto de visualización de fractales desarrollado para **42 School**, con extensiones virales para redes sociales.

---

## 📁 Estructura del Proyecto

Este repositorio está organizado en tres secciones principales:

### 📘 `mandatory/` - Proyecto Obligatorio 42

La implementación base del proyecto Fract-ol con visualización de fractales usando MiniLibX.

**Características:**
- ✅ Conjunto de Mandelbrot
- ✅ Conjunto de Julia (con parámetros dinámicos)
- ✅ Atractor de Lorenz
- ✅ Zoom y navegación interactiva
- ✅ Sistema de colores personalizables

**[👉 Ver documentación completa](./mandatory/README.md)**

---

### 🌐 `web/` - Extensión Viral/Web

Implementaciones web y contenido viral para redes sociales.

**Incluye:**
- 📱 **Mobile Fractal 3D** - Aplicación web progresiva (PWA)
- 🔮 **Fractal Soul Generator** - Genera fractales únicos basados en nombres y fechas
- ⭐ **Horóscopo Fractal** - Predicciones diarias con fractales
- 👑 **Fractales de Celebridades** - Messi, Einstein, Bad Bunny...
- 📸 Screenshots optimizados para Instagram/TikTok

**[👉 Ver documentación viral](./web/docs/VIRAL_README.md)**

---

### 📚 `docs/` - Documentación General

Guías y documentación del proyecto.

**Contenido:**
- 📖 [Guía de Instalación](./docs/INSTALL.md)
- 📘 [Guía Completa de MiniLibX](./docs/MiniLibX_GuiaCompleta.md)

---

## 🚀 Inicio Rápido

### Proyecto Obligatorio (Mandatory)

```bash
# Clonar repositorio
git clone https://github.com/0XARCOS/fract-ol.git
cd fract-ol

# Clonar MiniLibX
git clone https://github.com/42Paris/minilibx-linux.git

# Compilar y ejecutar
cd mandatory
make
./fractol mandelbrot
```

### Extensión Web

```bash
# Navegar a la carpeta web
cd web/mobile-fractal-3d

# Abrir en navegador
# Simplemente abre public/index.html en tu navegador
```

---

## 📸 Galería

### Mandelbrot
<img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-20%2005-07-50.png" width="500"/>

### Julia
<img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-24%2006-13-12.png" width="500"/>

### Lorenz Attractor
<img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-28%2002-19-26.png" width="500"/>

---

## 🎮 Controles (Mandatory)

- **Zoom**: Rueda del mouse
- **Movimiento**: Teclas de dirección
- **Cambiar colores**: `C`
- **Reset**: `R`
- **Salir**: `ESC`

---

## 🔥 Características Virales (Web)

### Fractal Soul Generator

Cada persona tiene un fractal único:

```bash
cd mandatory
./fractol soul "Tu Nombre" 15 06 1995
```

### Share Codes

Comparte tu fractal único con amigos usando códigos cortos.

**[Ver más ideas virales](./web/docs/VIRAL_IDEAS.md)**

---

## ⚙️ Requisitos

### Para el proyecto Mandatory:
- GCC
- Make
- MiniLibX (Linux)
- X11 (Xlib, Xext)

### Para la extensión Web:
- Navegador web moderno
- (Opcional) Servidor web para desarrollo

---

## 🧪 Ejercicios de Práctica

Incluye 8 ejercicios progresivos para aprender MiniLibX desde cero:

| Ejercicio | Descripción |
|-----------|-------------|
| Ex_1 | Ventana básica |
| Ex_2 | Captura de teclas |
| Ex_3 | Píxeles básicos |
| Ex_4 | Píxeles directos |
| Ex_5 | Líneas (Bresenham) |
| Ex_6 | Degradados |
| Ex_7 | Movimiento con teclado |
| Ex_8 | Animaciones |

**[Ver ejercicios](./mandatory/exercises/)**

---

## 📊 Proyecto

- **Calificación**: 120/100
- **Escuela**: 42 Madrid
- **Lenguaje**: C
- **Gráficos**: MiniLibX

---

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

---

## 📝 Licencia

Este proyecto es de código abierto y está disponible bajo la licencia MIT.

---

## 👤 Autor

**0xARCOS**
- GitHub: [@0xARCOS](https://github.com/0xARCOS)
- 42 Intra: [aarcos](https://profile.intra.42.fr/users/aarcos)

---

## 🌟 Agradecimientos

- 42 Madrid por el proyecto base
- La comunidad de 42 por el soporte
- Todos los que han contribuido con ideas virales

---

<div align="center">

**⭐ Si te gusta este proyecto, dale una estrella en GitHub ⭐**

</div>
