# 📦 Guía de Instalación - Fractal 3D Experience

Guía completa para instalar, desarrollar y desplegar la aplicación de fractales 3D optimizada.

---

## 📋 Tabla de Contenidos

1. [Requisitos Previos](#-requisitos-previos)
2. [Instalación Local](#-instalación-local)
3. [Desarrollo Local](#-desarrollo-local)
4. [Deployment a Netlify](#-deployment-a-netlify)
5. [Verificación de Optimizaciones](#-verificación-de-optimizaciones)
6. [Troubleshooting](#-troubleshooting)

---

## 🔧 Requisitos Previos

### Necesarios:
- ✅ **Git** - Para clonar el repositorio
- ✅ **Navegador moderno** - Chrome, Firefox, Safari, Edge (con soporte WebGL)
- ✅ **Editor de código** - VSCode, Sublime, Atom, etc. (opcional)

### Para desarrollo local:
- ✅ **Python 3** (ya incluido en Mac/Linux) o
- ✅ **Node.js** (alternativa) o
- ✅ **Cualquier servidor HTTP estático**

### Para deployment:
- ✅ **Cuenta de Netlify** (gratuita) o
- ✅ **Cuenta de Vercel/GitHub Pages** (alternativas)

---

## 💻 Instalación Local

### Paso 1: Clonar el Repositorio

```bash
# Opción A: HTTPS
git clone https://github.com/0xARCOS/fractol.git

# Opción B: SSH (si tienes configurado SSH)
git clone git@github.com:0xARCOS/fractol.git

# Entrar al directorio
cd fractol/mobile-fractal-3d
```

### Paso 2: Verificar Archivos

```bash
# Listar archivos del proyecto
ls -la public/

# Deberías ver:
# - index.html
# - app-lite.js (14KB - versión ultra-ligera)
# - app.js (24KB - versión Three.js)
# - style.css
# - sw.js (Service Worker)
# - manifest.json
```

### Paso 3: Verificar Tamaños

```bash
# Verificar que app-lite.js es pequeño
ls -lh public/app-lite.js

# Debería mostrar ~14KB
```

---

## 🚀 Desarrollo Local

Hay varias formas de ejecutar la app localmente:

### Método 1: Python 3 (Recomendado - Más Simple)

```bash
# Desde el directorio mobile-fractal-3d
python3 -m http.server 8080 --directory public

# O usar el comando npm definido:
npm run dev
```

**Abrir en navegador:**
```
http://localhost:8080
```

### Método 2: Node.js + http-server

```bash
# Instalar http-server globalmente (solo una vez)
npm install -g http-server

# Ejecutar servidor
cd public
http-server -p 8080
```

**Abrir en navegador:**
```
http://localhost:8080
```

### Método 3: VSCode Live Server

1. Instalar extensión **Live Server** en VSCode
2. Abrir `mobile-fractal-3d/public/index.html`
3. Click derecho → "Open with Live Server"
4. Se abrirá automáticamente en el navegador

### Método 4: Python 2 (Legacy)

```bash
# Si solo tienes Python 2
python -m SimpleHTTPServer 8080
```

---

## 🌐 Deployment a Netlify

### Opción A: Deploy desde GitHub (Recomendado)

#### 1. Push a GitHub

```bash
# Si aún no has pusheado el código
git add .
git commit -m "Ready for deployment"
git push origin main
```

#### 2. Conectar con Netlify

1. **Ve a [Netlify](https://www.netlify.com/)**
2. **Sign up / Login** (puedes usar tu cuenta de GitHub)
3. Click en **"Add new site"** → **"Import an existing project"**
4. Selecciona **GitHub** y autoriza
5. Selecciona el repositorio **fractol**

#### 3. Configurar Build Settings

```yaml
Base directory: mobile-fractal-3d
Publish directory: mobile-fractal-3d/public
Build command: echo 'No build needed - static site'
```

#### 4. Deploy!

- Click **"Deploy site"**
- Netlify generará una URL como: `https://random-name-123.netlify.app`
- ✅ **¡Listo!** Tu app está en vivo

#### 5. Personalizar Dominio (Opcional)

1. En Netlify → **Site settings** → **Domain management**
2. Click **"Add custom domain"**
3. Puedes usar un dominio gratuito de Netlify o tu propio dominio

---

### Opción B: Deploy Manual (Drag & Drop)

#### 1. Preparar carpeta

```bash
# Asegúrate de estar en mobile-fractal-3d/public
cd mobile-fractal-3d/public
ls

# Deberías ver todos los archivos
```

#### 2. Deploy en Netlify

1. Ve a [Netlify](https://www.netlify.com/)
2. **Arrastra la carpeta `public`** directamente a Netlify
3. ✅ **¡Deployado!** Obtendrás una URL instantáneamente

---

### Opción C: Netlify CLI

```bash
# Instalar Netlify CLI
npm install -g netlify-cli

# Login
netlify login

# Deploy desde mobile-fractal-3d
cd mobile-fractal-3d
netlify deploy --dir=public

# Para deploy en producción
netlify deploy --prod --dir=public
```

---

## 🔍 Verificación de Optimizaciones

### 1. Verificar Carga Rápida

#### Chrome DevTools:

1. Abre **Chrome DevTools** (F12)
2. Ve a la pestaña **Network**
3. **Recarga la página** (Cmd+R / Ctrl+R)
4. Verifica:
   - ✅ **Total size**: ~20-30 KB (no 1.3MB)
   - ✅ **DOMContentLoaded**: <500ms
   - ✅ **Load time**: <1s

#### Ejemplo de salida esperada:
```
app-lite.js     14 KB    200ms
style.css       12 KB    150ms
index.html      9 KB     100ms
sw.js           3 KB     80ms
manifest.json   1 KB     50ms
─────────────────────────────
Total:          ~39 KB   <1s
```

---

### 2. Lighthouse Audit

#### Ejecutar Lighthouse:

1. Abre **Chrome DevTools** (F12)
2. Ve a la pestaña **Lighthouse**
3. Selecciona:
   - ✅ Performance
   - ✅ Best Practices
   - ✅ SEO
   - ✅ PWA
4. Click **"Analyze page load"**

#### Scores Esperados:
```
Performance:     95-100 🟢
Best Practices:  95-100 🟢
SEO:             95-100 🟢
PWA:             90-95  🟢
```

#### Métricas Esperadas:
```
First Contentful Paint:  <0.5s  🟢
Largest Contentful Paint: <1.0s  🟢
Time to Interactive:      <1.0s  🟢
Total Blocking Time:      <100ms 🟢
Cumulative Layout Shift:  <0.1   🟢
```

---

### 3. Verificar Service Worker

#### Chrome DevTools:

1. Abre **Chrome DevTools** (F12)
2. Ve a **Application** → **Service Workers**
3. Verifica:
   - ✅ Estado: **Activated and running**
   - ✅ Source: `/sw.js`

#### Verificar Caché:

1. En **Application** → **Cache Storage**
2. Deberías ver:
   - `fractal-3d-v2.0.0` (caché de la app)
   - `fractal-3d-runtime` (caché de runtime)

#### Probar Offline:

1. En **Application** → **Service Workers**
2. Marca **"Offline"**
3. **Recarga la página**
4. ✅ **Debería funcionar perfectamente sin conexión**

---

### 4. Verificar WebGL

#### Abrir consola del navegador:

```javascript
// Pega esto en la consola
console.log('WebGL supported:', !!document.createElement('canvas').getContext('webgl'));

// Debería mostrar: WebGL supported: true
```

#### Verificar que usa app-lite.js:

```javascript
// En la consola deberías ver:
// "🚀 Ultra-Light Fractal Engine starting..."
// "✅ Ready! Bundle size: ~15KB (vs 1.27MB Three.js)"
```

---

### 5. Test de Rendimiento Móvil

#### Throttling en Chrome:

1. **DevTools** → **Network**
2. Cambia "No throttling" a **"Slow 3G"**
3. Recarga la página
4. ✅ Debería cargar en **<2 segundos** incluso en 3G

#### Lighthouse Mobile:

1. En **Lighthouse**, selecciona **"Mobile"**
2. Run audit
3. ✅ Score debería ser **>90**

---

## 🎨 Personalización

### Cambiar Colores

Edita `public/style.css`:

```css
:root {
    --primary-color: #ff0080;    /* Color principal */
    --secondary-color: #00ffff;  /* Color secundario */
    --bg-dark: #000000;          /* Fondo */
}
```

### Añadir Nuevo Fractal

Edita `public/app-lite.js` y añade una nueva función SDF:

```javascript
// Añadir en la sección de SDFs
float myFractal(vec3 p) {
    // Tu ecuación de fractal aquí
    return distance;
}

// Añadir en sceneSDF()
if(fractalType == 5) return myFractal(p);
```

### Cambiar Configuración Inicial

Edita `public/app-lite.js`:

```javascript
const state = {
    fractal: 'mandelbulb',      // Fractal inicial
    colorScheme: 'rainbow',      // Esquema de color inicial
    autoRotate: true,            // Auto-rotación activada
    speed: 1.0,                  // Velocidad de animación
    zoom: 3.5                    // Zoom inicial
};
```

---

## 🐛 Troubleshooting

### Problema 1: "No se ve nada en pantalla"

**Solución:**

```bash
# 1. Verifica que WebGL esté soportado
# Abre consola del navegador y ejecuta:
console.log(document.createElement('canvas').getContext('webgl'));

# Si es null, tu navegador/GPU no soporta WebGL
```

**Fix:** Actualiza tu navegador o prueba en otro dispositivo

---

### Problema 2: "Service Worker no se registra"

**Solución:**

```bash
# 1. Verifica que estés usando HTTPS o localhost
# Service Workers solo funcionan en conexiones seguras

# 2. Limpia el Service Worker anterior
# DevTools → Application → Service Workers → Unregister

# 3. Hard refresh
# Cmd+Shift+R (Mac) o Ctrl+Shift+R (Windows)
```

---

### Problema 3: "Sigue cargando Three.js"

**Solución:**

```bash
# Verifica que index.html use app-lite.js
grep "app-lite.js" mobile-fractal-3d/public/index.html

# Debería mostrar:
# <script src="app-lite.js"></script>

# Si muestra app.js, edita index.html y cambia a app-lite.js
```

---

### Problema 4: "Error 404 en archivos"

**Solución:**

```bash
# Verifica que estés sirviendo desde el directorio correcto
pwd  # Deberías estar en mobile-fractal-3d/

# Sirve desde public/
python3 -m http.server 8080 --directory public
```

---

### Problema 5: "La app no funciona offline"

**Solución:**

```bash
# 1. Verifica que el Service Worker esté registrado
# DevTools → Application → Service Workers

# 2. Visita la página al menos una vez online

# 3. Verifica la caché
# DevTools → Application → Cache Storage
# Deberías ver: fractal-3d-v2.0.0

# 4. Intenta offline mode
# DevTools → Application → Service Workers → Offline checkbox
```

---

### Problema 6: "Bajo FPS en móvil"

**Solución:**

La app ya tiene detección automática de calidad, pero puedes forzar baja calidad:

```javascript
// Edita app-lite.js, línea ~255
state.quality = 0.5;  // Reduce resolución (0.5 = 50%)
```

---

### Problema 7: "Netlify no procesa archivos"

**Verifica `netlify.toml`:**

```toml
[build]
  base = "mobile-fractal-3d"
  publish = "public"

[build.processing]
  skip_processing = false

[build.processing.js]
  minify = true
```

---

## 📊 Benchmarks Esperados

### Desktop (MacBook Pro / Windows PC moderno):
- **Carga inicial**: 200-400ms
- **FPS**: 60 estable
- **Tamaño total**: ~20KB transferido

### Mobile (iPhone 12 / Samsung S21):
- **Carga inicial**: 400-800ms
- **FPS**: 60 estable
- **Tamaño total**: ~20KB transferido

### Mobile Low-End (iPhone 7 / Android mid-range):
- **Carga inicial**: 600-1000ms
- **FPS**: 45-60 (auto-ajustado)
- **Tamaño total**: ~20KB transferido

### 3G Connection:
- **Carga inicial**: 500-1500ms
- **FPS**: Según dispositivo
- **Tamaño total**: ~20KB transferido

---

## 🎯 Checklist de Deployment

Antes de hacer deployment a producción:

- [ ] ✅ Probado localmente en Chrome
- [ ] ✅ Probado localmente en Safari/Firefox
- [ ] ✅ Probado en móvil (Chrome/Safari)
- [ ] ✅ Service Worker funciona
- [ ] ✅ Funciona offline
- [ ] ✅ Lighthouse score >90
- [ ] ✅ Throttling 3G carga <2s
- [ ] ✅ No hay errores en consola
- [ ] ✅ Todos los fractales funcionan
- [ ] ✅ Controles táctiles funcionan
- [ ] ✅ `netlify.toml` configurado
- [ ] ✅ Documentación actualizada

---

## 📚 Recursos Adicionales

### Documentación del Proyecto:
- [`ULTRA_LIGHT_VERSION.md`](./ULTRA_LIGHT_VERSION.md) - Detalles técnicos de optimización
- [`PERFORMANCE_OPTIMIZATIONS.md`](./PERFORMANCE_OPTIMIZATIONS.md) - Optimizaciones implementadas
- [`README.md`](../README.md) - Información general del proyecto

### Herramientas Útiles:
- [Lighthouse](https://developers.google.com/web/tools/lighthouse)
- [WebPageTest](https://www.webpagetest.org/)
- [Chrome DevTools](https://developer.chrome.com/docs/devtools/)
- [Can I Use - WebGL](https://caniuse.com/webgl)

### Hosting Alternatives:
- [Netlify](https://www.netlify.com/) ⭐ Recomendado
- [Vercel](https://vercel.com/)
- [GitHub Pages](https://pages.github.com/)
- [Cloudflare Pages](https://pages.cloudflare.com/)

---

## 🆘 Soporte

### ¿Problemas?

1. **Revisa la sección [Troubleshooting](#-troubleshooting)**
2. **Verifica la consola del navegador** (F12) para errores
3. **Abre un issue** en GitHub con:
   - Navegador y versión
   - Sistema operativo
   - Mensaje de error (si hay)
   - Pasos para reproducir

### ¿Mejoras?

¡Pull requests son bienvenidos! 🎉

---

## ✅ ¡Todo Listo!

Si seguiste esta guía, ahora tienes:

- ✅ App corriendo localmente
- ✅ Deployment en Netlify (o similar)
- ✅ Service Worker funcionando
- ✅ Optimizaciones verificadas
- ✅ Lighthouse score >90

**¡Disfruta tu aplicación de fractales 3D ultra-optimizada!** 🚀✨

---

**Última actualización:** Diciembre 2024
**Versión:** 2.0.0 (Ultra-Light)
