# 🚀 Instalación de FRACTAL SOUL

Guía paso a paso para instalar y ejecutar FRACTAL SOUL en tu sistema.

---

## 📋 Requisitos del Sistema

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install -y \
    gcc \
    make \
    git \
    libx11-dev \
    libxext-dev \
    libbsd-dev
```

### Linux (Fedora/RHEL)
```bash
sudo dnf install -y \
    gcc \
    make \
    git \
    libX11-devel \
    libXext-devel \
    libbsd-devel
```

### macOS
```bash
# MiniLibX ya viene con la versión de 42
# No se necesitan dependencias adicionales
brew install git
```

---

## 📥 Instalación

### 1. Clonar el Repositorio

```bash
git clone https://github.com/0XARCOS/fract-ol.git
cd fract-ol
```

### 2. Clonar MiniLibX

```bash
# Para Linux
git clone https://github.com/42Paris/minilibx-linux.git

# Para macOS (si estás en 42)
# La MiniLibX ya debería estar en tu sistema
```

### 3. Compilar el Proyecto

```bash
make
```

Si todo está bien, verás:
```
✅ Compilation successful!
✅ Executable: ./fractol
```

---

## 🎮 Uso Rápido

### Genera TU Fractal Soul

```bash
./fractol soul "Tu Nombre" 15 06 1995
```

Ejemplo:
```bash
./fractol soul "Maria Garcia" 24 03 1998
```

### Horóscopo Fractal del Día

```bash
./fractol horoscope
```

### Ver Fractales de Celebridades

```bash
# Listar todas las celebridades disponibles
./fractol celebs

# Cargar el fractal de una celebridad específica
./fractol celeb messi
./fractol celeb "bad bunny"
./fractol celeb einstein
```

### Usar un Share Code

```bash
./fractol soul MESSI10
./fractol soul A7K9M2PQ
```

### Fractales Clásicos

```bash
# Conjunto de Mandelbrot
./fractol mandelbrot

# Conjunto de Julia (con parámetros opcionales)
./fractol julia
./fractol julia -0.7 0.27015

# Atractor de Lorenz
./fractol lorenz
```

---

## ⌨️ Controles en la Ventana

Una vez que el fractal se abre:

| Tecla/Acción | Función |
|--------------|---------|
| `Mouse Scroll` | Zoom in/out |
| `↑ ↓ ← →` | Mover la vista |
| `C` | Cambiar paleta de colores |
| `R` | Reset a la vista original |
| `ESC` | Cerrar programa |

---

## 🐛 Resolución de Problemas

### Error: "mlx.h: No such file or directory"

**Solución:**
```bash
# Asegúrate de haber clonado minilibx-linux
git clone https://github.com/42Paris/minilibx-linux.git
```

### Error: "cannot find -lbsd"

**Solución (Ubuntu/Debian):**
```bash
sudo apt-get install libbsd-dev
```

**Solución (Fedora/RHEL):**
```bash
sudo dnf install libbsd-devel
```

### Error: "cannot open display"

Esto significa que no tienes un servidor X corriendo.

**Solución 1 - Si estás en un servidor remoto:**
```bash
# Usa X11 forwarding
ssh -X usuario@servidor
```

**Solución 2 - Si estás en WSL2:**
```bash
# Instala un servidor X en Windows:
# - VcXsrv (recomendado)
# - Xming

# Luego en WSL:
export DISPLAY=:0
```

### Error: "Segmentation fault"

**Posibles causas:**
1. MiniLibX no está correctamente instalada
2. Falta alguna dependencia X11

**Solución:**
```bash
# Reinstala dependencias
sudo apt-get install --reinstall libx11-dev libxext-dev

# Recompila todo
make fclean
make
```

---

## 🔄 Actualizar

Para obtener las últimas features:

```bash
git pull origin main
make fclean
make
```

---

## 🧹 Desinstalación

```bash
make fclean
cd ..
rm -rf fract-ol
```

---

## 💻 Compilación Manual (Avanzado)

Si `make` no funciona, puedes compilar manualmente:

```bash
# Compilar MiniLibX
cd minilibx-linux
make
cd ..

# Compilar objetos
cc -Wall -Wextra -Werror -Iincludes -Iminilibx-linux -c src/*.c

# Linkear
cc *.o -o fractol -Lminilibx-linux -lmlx -lXext -lX11 -lm
```

---

## 🌐 Entornos Especiales

### Docker

```dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc make git \
    libx11-dev libxext-dev libbsd-dev

WORKDIR /app
COPY . .

RUN git clone https://github.com/42Paris/minilibx-linux.git
RUN make

CMD ["./fractol", "horoscope"]
```

### GitHub Codespaces

MiniLibX requiere X11, que no está disponible en Codespaces.
Recomendamos clonar el repo localmente o usar una máquina virtual.

---

## 🎓 Para Estudiantes de 42

Si estás haciendo este proyecto en 42:

1. **No necesitas instalar dependencias** - ya están en los Macs
2. **Usa la MiniLibX de tu campus** - puede tener una ruta diferente
3. **Ajusta el Makefile** si es necesario para tu configuración

---

## 📱 Próximamente: Web Version

Estamos trabajando en una versión web que no requiere instalación!

Mantente atento a: [Tu URL aquí]

---

## ❓ Ayuda Adicional

- 📖 [Guía completa FRACTAL SOUL](./VIRAL_README.md)
- 🎨 [Templates para redes sociales](./SOCIAL_MEDIA_TEMPLATES.md)
- 💡 [Ideas virales](./VIRAL_IDEAS.md)
- 🐛 [Reportar un bug](https://github.com/0XARCOS/fract-ol/issues)

---

<div align="center">

**¿Listo para descubrir tu Fractal Soul?** ✨

```bash
./fractol soul "Tu Nombre" DD MM YYYY
```

</div>
