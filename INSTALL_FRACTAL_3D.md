# 🌀 Guía Completa de Instalación - Fractal 3D Mobile

Esta guía te llevará paso a paso para instalar y desplegar la aplicación Fractal 3D Mobile tanto en local como en Netlify.

---

## 📋 Requisitos Previos

### Para Testing Local:
- **Python 3** (ya viene instalado en Mac y Linux)
- Un navegador web moderno (Chrome, Firefox, Safari, Edge)
- Conexión a internet (para cargar Three.js desde CDN)

### Para Deploy en Netlify:
- Cuenta de GitHub (gratuita)
- Cuenta de Netlify (gratuita) - [Regístrate aquí](https://netlify.com)

---

## 🏠 Instalación y Testing Local

### Paso 1: Clonar el Repositorio

```bash
# Si aún no lo has clonado
git clone https://github.com/0xARCOS/fractol.git
cd fractol
```

### Paso 2: Navegar a la Carpeta de la Aplicación

```bash
cd mobile-fractal-3d
```

### Paso 3: Iniciar Servidor Local

**Opción A - Con Python (Recomendado):**
```bash
python3 -m http.server 8080 --directory public
```

**Opción B - Con Node.js (si lo tienes instalado):**
```bash
# Instalar http-server (solo la primera vez)
npm install -g http-server

# Iniciar servidor
cd public
http-server -p 8080
```

**Opción C - Con PHP (si lo tienes instalado):**
```bash
cd public
php -S localhost:8080
```

### Paso 4: Abrir en el Navegador

1. Abre tu navegador
2. Ve a: **http://localhost:8080**
3. Deberías ver la pantalla de carga y luego la aplicación 🎉

### Paso 5: Probar en Móvil (Opcional)

Para probar en tu móvil en la misma red WiFi:

1. **Encuentra tu IP local:**
   ```bash
   # En Mac/Linux:
   ifconfig | grep "inet " | grep -v 127.0.0.1

   # En Windows:
   ipconfig
   ```

2. **Anota tu IP** (ej: `192.168.1.100`)

3. **En tu móvil:**
   - Asegúrate de estar en la misma red WiFi
   - Abre el navegador
   - Ve a: `http://TU_IP:8080` (ej: `http://192.168.1.100:8080`)

---

## 🚀 Deploy en Netlify - Opción 1 (Desde GitHub - Recomendado)

Esta es la forma más fácil y mantiene tu sitio actualizado automáticamente.

### Paso 1: Preparar el Repositorio

Asegúrate de que tu repositorio esté actualizado:

```bash
git pull origin main
```

### Paso 2: Configurar Netlify

1. **Ve a [Netlify](https://app.netlify.com)**
2. **Inicia sesión** con tu cuenta de GitHub
3. **Click en "Add new site"** → "Import an existing project"
4. **Selecciona "GitHub"**
5. **Autoriza Netlify** para acceder a tu cuenta de GitHub
6. **Busca y selecciona** el repositorio `fractol`

### Paso 3: Configuración del Build

**🚨 IMPORTANTE:** Deja TODOS los campos VACÍOS, el archivo `netlify.toml` se encargará de todo:

- **Base directory:** (dejar vacío)
- **Build command:** (dejar vacío)
- **Publish directory:** (dejar vacío)
- **Branch to deploy:** `main` o tu rama principal

### Paso 4: Deploy

1. **Click en "Deploy site"**
2. Espera 1-2 minutos mientras Netlify despliega
3. **¡Listo!** Netlify te dará una URL como: `https://tu-sitio-random.netlify.app`

### Paso 5: Personalizar el Nombre (Opcional)

1. En Netlify, ve a **Site settings** → **General**
2. Click en **Change site name**
3. Elige un nombre único (ej: `fractol-3d`)
4. Tu nueva URL será: `https://fractol-3d.netlify.app`

---

## 🚀 Deploy en Netlify - Opción 2 (Manual con Netlify CLI)

### Paso 1: Instalar Netlify CLI

```bash
# Con npm (si tienes Node.js instalado)
npm install -g netlify-cli

# O con Homebrew en Mac
brew install netlify-cli
```

### Paso 2: Login en Netlify

```bash
netlify login
```

Esto abrirá tu navegador para que autorices la CLI.

### Paso 3: Ir a la Carpeta Correcta

```bash
cd mobile-fractal-3d
```

### Paso 4: Deploy

```bash
# Deploy directo a producción
netlify deploy --prod --dir=public
```

Netlify te preguntará:
1. **Create & configure a new site:** Selecciona esto si es la primera vez
2. **Team:** Selecciona tu equipo personal
3. **Site name:** Elige un nombre único (opcional)

### Paso 5: Ver tu Sitio

Netlify te dará dos URLs:
- **Draft URL:** Vista previa temporal
- **Production URL:** Tu sitio en vivo

¡Ya está desplegado! 🎉

---

## 🔧 Troubleshooting

### Problema: "Site not found" en Netlify

**Causa:** Configuración incorrecta del deploy.

**Solución:**
1. Ve a **Site settings** → **Build & deploy** → **Build settings**
2. Asegúrate de que TODO esté vacío (el `netlify.toml` maneja esto)
3. Si hay valores, bórralos
4. Haz un **Trigger deploy** → **Clear cache and deploy site**

### Problema: Pantalla en blanco o "Loading" infinito

**Causas posibles:**
- Three.js no se puede cargar desde el CDN
- Bloqueador de contenido activo
- Conexión lenta a internet

**Soluciones:**
1. **Abre la consola del navegador** (F12 o Cmd+Option+I)
2. Mira si hay errores rojos
3. Si ves error "net::ERR_BLOCKED_BY_CLIENT":
   - Desactiva bloqueadores de ads
   - Desactiva extensiones como uBlock, AdBlock, etc.
4. Si ves error de CORS o CDN:
   - Verifica tu conexión a internet
   - Intenta en modo incógnito
   - Prueba con otro navegador

### Problema: App muy lenta en móvil

**Solución:**
La app ya se ajusta automáticamente, pero si sigue lenta:
1. **Desactiva "Partículas"** en los controles
2. **Reduce velocidad** con el slider
3. **Cambia a fractal más simple** (Sierpinski es el más rápido)

### Problema: No se puede instalar Netlify CLI

**Solución:**
Si no tienes Node.js:
1. Usa la **Opción 1** (Deploy desde GitHub) - no requiere instalar nada
2. O instala Node.js desde [nodejs.org](https://nodejs.org)

### Problema: Error "python3: command not found"

**Solución en Mac:**
```bash
# Usar python sin el 3
python -m http.server 8080 --directory public
```

**Solución en Windows:**
1. Descarga Python desde [python.org](https://python.org)
2. Durante instalación, marca "Add Python to PATH"
3. O usa Node.js en su lugar

---

## ✅ Verificación de que Todo Funciona

### En Local:
- [ ] El servidor inicia sin errores
- [ ] Ves la pantalla de carga al abrir http://localhost:8080
- [ ] La aplicación carga en 5-10 segundos
- [ ] Puedes rotar el fractal con el mouse
- [ ] Los botones de UI funcionan
- [ ] El contador de FPS muestra 30+ FPS

### En Netlify:
- [ ] El deploy se completa sin errores
- [ ] Tu sitio está accesible desde la URL de Netlify
- [ ] La aplicación funciona igual que en local
- [ ] HTTPS está habilitado automáticamente (candado verde)
- [ ] Funciona en móvil

---

## 📱 Probar en Móvil

Una vez desplegado en Netlify:

1. **Abre la URL de Netlify** en tu móvil
2. **Toca "Comenzar Experiencia"**
3. **Prueba los controles:**
   - Un dedo para rotar
   - Pinch para zoom
   - Dos dedos para mover cámara
4. **Añade a pantalla de inicio** (opcional):
   - **iOS:** Tap en compartir → "Añadir a pantalla de inicio"
   - **Android:** Tap en menú (⋮) → "Añadir a pantalla de inicio"

---

## 📊 Estructura del Proyecto

```
fractol/
├── netlify.toml                    ← Configuración de Netlify (raíz)
└── mobile-fractal-3d/
    ├── public/                     ← Archivos a desplegar
    │   ├── index.html              ← HTML principal
    │   ├── app.js                  ← Lógica de la app
    │   ├── style.css               ← Estilos
    │   ├── manifest.json           ← PWA config
    │   ├── robots.txt
    │   └── _redirects
    ├── netlify.toml                ← Config adicional (opcional)
    ├── package.json                ← Metadata del proyecto
    └── README.md
```

---

## 🎯 Resumen Rápido

### Para Testing Rápido:
```bash
cd fractol/mobile-fractal-3d
python3 -m http.server 8080 --directory public
# Abrir http://localhost:8080
```

### Para Deploy Automático:
1. Push a GitHub
2. Conectar repo en Netlify
3. Dejar todo vacío en configuración
4. Deploy

### Para Deploy Manual:
```bash
cd fractol/mobile-fractal-3d
netlify login
netlify deploy --prod --dir=public
```

---

## 💡 Consejos

1. **Usa Chrome o Safari** para mejor rendimiento
2. **Prueba en modo incógnito** si hay problemas de cache
3. **El primer load es más lento** (carga Three.js), luego es rápido
4. **HTTPS es automático** en Netlify (necesario para PWA)
5. **Los cambios en GitHub** se despliegan automáticamente en Netlify (Opción 1)

---

## 🆘 Ayuda Adicional

Si sigues teniendo problemas:

1. **Revisa la consola del navegador** (F12) para ver errores
2. **Verifica que `netlify.toml` existe** en la raíz del proyecto
3. **Asegúrate de desplegar desde** `mobile-fractal-3d/public`
4. **Prueba con otro navegador** o dispositivo
5. **Revisa el log de deploy** en Netlify para errores

---

## 🎉 ¡Listo!

Si llegaste hasta aquí y todo funcionó, ¡felicidades! Tu aplicación Fractal 3D Mobile está lista para compartir con el mundo.

**Tu URL de Netlify es tu enlace permanente** - compártelo en redes sociales, con amigos, o donde quieras.

---

**Desarrollado por 0xARCOS** | **Licencia MIT** | [Ver Código en GitHub](https://github.com/0xARCOS/fractol)
