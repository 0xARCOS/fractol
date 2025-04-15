
# 🧠 Guía Visual de MiniLibX

Una introducción clara, visual y profunda a la biblioteca gráfica utilizada en 42 para manipular píxeles, eventos y animaciones.

---

## 📘 Índice Rápido

- [Introduccion](#introduccion)
- [Funciones Basicas](#funciones-basicas)
- [Como Funciona MiniLibX](#como-funciona-minilibx)
- [Nivel Maquina: Dibujo y Memoria](#nivel-maquina-dibujo-y-memoria)
- [Buenas Practicas](#buenas-practicas)
- [Tareas por Nivel](#tareas-por-nivel)
- [Recursos Recomendados](#recursos-recomendados)
- [Ejemplos Visuales y Diagramas](#ejemplos-visuales-y-diagramas)



---

## 🔰 Introducción

**MiniLibX** es una biblioteca gráfica ligera que permite:
- Crear ventanas
- Dibujar imágenes y píxeles
- Capturar eventos del teclado y ratón
- Controlar el flujo de ejecución gráfica en Linux (X11) o macOS

Ideal para aprender sobre:
- Framebuffers
- Acceso a memoria
- Interacción con servidores gráficos

---

## 🛠 Funciones Básicas

### 🔹 Inicialización y Ventana

| Función | Propósito |
|--------|-----------|
| `mlx_init()` | Conecta con el servidor gráfico |
| `mlx_new_window()` | Crea una ventana (X11/macos) |

### 🔹 Imagen y Píxeles

| Función | Propósito |
|--------|-----------|
| `mlx_new_image()` | Crea una imagen en memoria RAM |
| `mlx_get_data_addr()` | Accede al buffer de memoria para escribir píxeles |
| `mlx_put_image_to_window()` | Envía la imagen a la ventana para dibujarla |

### 🔹 Colores

- Formato hexadecimal: `0xRRGGBB`
- Se escriben manualmente en la memoria de la imagen

### 🔹 Eventos

| Función | Evento |
|--------|--------|
| `mlx_hook()` | Eventos generales |
| `mlx_key_hook()` | Eventos de teclado |
| `mlx_loop()` | Inicia el bucle principal de eventos |

---

## ⚙️ Cómo Funciona MiniLibX

### 🧩 Comunicación con el Servidor X (Linux)

- `mlx_init()` crea un **contexto gráfico** comunicándose con **X11**
- `mlx_new_window()` solicita a X11 que cree una ventana y le asigna memoria

### 💾 Escritura en Memoria

```c
mlx_pixel_put(mlx, win, x, y, 0xFF0000);
```

➡️ Ineficiente para muchos píxeles.  
✅ Mejor: modificar una imagen en RAM → `mlx_put_image_to_window()`.

---

## 🚀 Nivel Máquina: Dibujo y Memoria

### 📦 Memoria con `mlx_get_data_addr`

```c
addr = mlx_get_data_addr(img, &bpp, &line_length, &endian);
*(unsigned int*)(addr + (y * line_length + x * (bpp / 8))) = 0xFFFFFF;
```

- Modifica la RAM directamente
- Mucho más rápido que `mlx_pixel_put()`

---

## 💡 Buenas Prácticas

⚠️ Evita dibujar píxel por píxel con `mlx_pixel_put()` en bucles  
✅ Usa imágenes en memoria intermedia y transfórmalas con `mlx_put_image_to_window()`

---

## 🧪 Tareas por Nivel

### 🟢 Nivel 1: Básico

- 🪟 Crear una ventana con `mlx_init()` + `mlx_new_window()`
- ⌨️ Capturar tecla `Esc` y cerrar ventana
- 🎨 Limpiar ventana y dibujar fondo

### 🟡 Nivel 2: Imágenes y dibujo

- 🧱 Dibujar un píxel manualmente (RAM)
- 📏 Dibujar línea con algoritmo de **Bresenham**
- 🌈 Crear un degradado de color horizontal

### 🔴 Nivel 3: Animaciones y Movimiento

- 🕹 Mover cuadrado con teclas (eventos + redibujo)
- ⏱ Crear animación continua (`mlx_loop_hook()`)
- 🟠 Dibujar círculos con el algoritmo de Midpoint

---

## 📚 Recursos Recomendados

- [MiniLibX Source (42 Paris)](https://github.com/42Paris/minilibx-linux)
- [Servidor Gráfico X11](https://en.wikipedia.org/wiki/X_Window_System)
- [Algoritmo de Bresenham](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Algoritmo de Midpoint (círculos)](https://en.wikipedia.org/wiki/Midpoint_circle_algorithm)

---



---

## 🖼️ Ejemplos Visuales y Diagramas

### 🧱 Framebuffer: Representación Simplificada

Cada píxel en la ventana corresponde a un bloque en memoria RAM:

```
Ventana de 4x2 píxeles (cada letra = 1 píxel de color)
+----+----+----+----+
| R  | G  | B  | Y  |   ← fila 0
+----+----+----+----+
| C  | M  | W  | K  |   ← fila 1
+----+----+----+----+

Memoria lineal (addr):
[ R ][ G ][ B ][ Y ][ C ][ M ][ W ][ K ]
```

Cada píxel ocupa 4 bytes (RGBA). Para modificar un píxel:
```
posición = (y * line_length) + (x * (bpp / 8))
```

---

### 💾 Mapa de Estructura `t_data` en RAM

```
struct t_data {
  void *mlx;
  void *win;
  void *img;
  char *addr;
  int   bpp;
  int   line_length;
  int   endian;
};
```

```
RAM Layout

| Dirección     | Campo         | Descripción                       |
|---------------|---------------|-----------------------------------|
| 0x1000        | mlx           | puntero a conexión X11            |
| 0x1008        | win           | puntero a ventana                 |
| 0x1010        | img           | puntero a imagen en memoria       |
| 0x1018        | addr          | puntero al buffer de píxeles      |
| 0x1020        | bpp           | bits por píxel (ej. 32)           |
| 0x1024        | line_length   | bytes por fila de imagen          |
| 0x1028        | endian        | orden de los bytes (0 o 1)        |
```

---

### 🎮 Diagrama de Flujo de Eventos con `mlx_hook()`

```
        ┌─────────────┐
        │ mlx_loop()  │
        └─────┬───────┘
              │ (espera eventos)
              ▼
       ┌─────────────┐
       │ tecla pres. │
       └─────┬───────┘
             ▼
   ┌────────────────────┐
   │ mlx_hook(KEY, ...) │
   └────────┬───────────┘
            ▼
   ┌────────────────────┐
   │ ejecuta función C  │
   └────────────────────┘
```

---

### 🌀 Color en Hexadecimal

```
Color 0xFF00FF = Magenta

0x |  FF  |  00 |  FF
    └─R──┘ └G──┘ └B──┘
```

Prueba diferentes valores de color para experimentar con tonos personalizados.

---
