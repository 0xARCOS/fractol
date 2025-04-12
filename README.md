<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/fract-ol-light.png#gh-light-mode-only" alt="Banner (claro)" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/fract-ol-dark.png#gh-dark-mode-only" alt="Banner (oscuro)" />
    <a href='https://profile.intra.42.fr/users/aarcos' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Madrid-black?style=flat&logo=42&logoColor=white'/>
    </a>
    <img src="https://img.shields.io/badge/120%20%2F%20100-success?color=%2312bab9&style=flat" />
    <img src="https://api.visitorbadge.io/api/visitors?user=0xARCOS&repo=fractol_42&label=visitas&countColor=%2385e3ff&style=flat&labelStyle=none"/>
</div>

Explora el mundo de los fractales con este visualizador interactivo desarrollado con **MiniLibX** (42). Sumérgete en las complejidades matemáticas y visuales de los conjuntos Mandelbrot, Julia y el atractor de Lorenz.

---

## 🌌 Fractales Soportados

- **Mandelbrot**
- **Julia** (con parámetros dinámicos)
- **Lorenz Attractor**

---

## 📸 Capturas de Pantalla

Visualizaciones renderizadas directamente con Fract-ol.

---

### 🌪 Lorenz Attractor

| Variante 1 | Variante Compleja |
|------------|-------------------|
| <img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-28%2002-19-26.png" width="340"/> | <img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-20%2000-36-21.png" width="340"/> |

---

### 🌊 Conjuntos de Julia

| Zoom Central | Reverse |
|--------------|---------|
| <img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-24%2006-13-12.png" width="340"/> | <img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-24%2007-00-57.png" width="340"/> |

---

### 🕳 Conjunto de Mandelbrot

| Vista Principal | Ampliación Lateral |
|-----------------|--------------------|
| <img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-20%2005-07-50.png" width="340"/> | <img src="https://github.com/0xARCOS/fractol_42/blob/main/img/Screenshot%20from%202025-03-28%2004-05-28.png" width="340"/> |

---
## ⚙️ Requisitos del Sistema

Asegúrate de tener instaladas las siguientes dependencias:

- `gcc`
- `make`
- MiniLibX (versión Linux de 42)
- X11 (Xlib, Xext)
- `git`

---

## 🚀 Instalación y Ejecución

```bash
# Clona el repositorio
git clone https://github.com/tu_usuario/fract-ol.git
cd fract-ol

# Clona la MiniLibX (versión Linux)
git clone https://github.com/42Paris/minilibx-linux.git

# Compila el proyecto
make
```
---


## 📘 Aprende más sobre MiniLibX

¿Nuevo con MiniLibX? Consulta la guía completa con explicaciones detalladas de cada función y cómo se comunica con tu sistema operativo:

👉 [Guía Completa de MiniLibX](./MiniLibX_GuiaCompleta.md)

---

### 🧪 Ejercicios de Aprendizaje con MiniLibX

Esta serie de ejercicios sirve como preparación y entrenamiento para dominar MiniLibX. Desde la creación de ventanas hasta animaciones simples, cada uno te familiarizará con los fundamentos necesarios para `fract-ol`.

| Nº | Archivo                                | Descripción                                                |
|----|----------------------------------------|------------------------------------------------------------|
| 1  | [Ex_1.c](./ejers_minilibx/Ex_1.c)      | Inicialización básica y creación de una ventana            |
| 2  | [Ex_2.c](./ejers_minilibx/Ex_2.c)      | Captura de la tecla `ESC` para cerrar ventana              |
| 3  | [Ex_3.c](./ejers_minilibx/Ex_3.c)      | Dibujo de píxeles usando `my_mlx_pixel_put()`              |
| 4  | [Ex_4.c](./ejers_minilibx/Ex_4.c)      | Uso directo de `mlx_pixel_put()`                           |
| 5  | [Ex_5.c](./ejers_minilibx/Ex_5.c)      | Dibujo de líneas con el algoritmo de Bresenham             |
| 6  | [Ex_6.c](./ejers_minilibx/Ex_6.c)      | Generación de un degradado de color horizontal             |
| 7  | [Ex_7.c](./ejers_minilibx/Ex_7.c)      | Movimiento de un cuadrado con las teclas de dirección      |
| 8  | [Ex_8.c](./ejers_minilibx/Ex_8.c)      | Animación de rebote automático de un cuadrado              |

---

## 🧠 Objetivo

Este proyecto es una oportunidad para explorar gráficos generativos, matemáticas visuales y el control de bajo nivel sobre píxeles en pantalla. ¡Sumérgete y descubre la belleza oculta de los fractales!

---
## 📚 Créditos

Desarrollado como parte del programa de la escuela 42.  
Inspirado por la belleza matemática del caos.

