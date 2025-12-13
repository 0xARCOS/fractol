# 🚀 Guía de Deployment

## Netlify (Recomendado)

### Opción 1: Deploy desde GitHub

1. **Conecta tu repositorio a Netlify:**
   - Ve a [Netlify](https://netlify.com)
   - Click en "New site from Git"
   - Selecciona tu repositorio
   - Configura:
     ```
     Base directory: mobile-fractal-3d
     Publish directory: mobile-fractal-3d/public
     Build command: (dejar vacío)
     ```

2. **Deploy automático:**
   - Netlify detectará automáticamente el archivo `netlify.toml`
   - Cada push a la rama principal desplegará automáticamente

### Opción 2: Deploy Manual con Netlify CLI

```bash
# Instalar Netlify CLI
npm install -g netlify-cli

# Login
netlify login

# Deploy
cd mobile-fractal-3d
netlify deploy --prod --dir=public
```

### Opción 3: Drag & Drop

1. Ve a [Netlify Drop](https://app.netlify.com/drop)
2. Arrastra la carpeta `mobile-fractal-3d/public`
3. ¡Listo!

---

## Vercel

```bash
# Instalar Vercel CLI
npm install -g vercel

# Deploy
cd mobile-fractal-3d
vercel --prod
```

**Configuración vercel.json** (crear en mobile-fractal-3d/):
```json
{
  "buildCommand": "",
  "outputDirectory": "public",
  "framework": null
}
```

---

## GitHub Pages

1. **Habilitar GitHub Pages:**
   - Ve a Settings > Pages
   - Source: Deploy from a branch
   - Branch: main
   - Folder: /mobile-fractal-3d/public

2. **O usando GitHub Actions:**

Crear `.github/workflows/deploy.yml`:
```yaml
name: Deploy to GitHub Pages

on:
  push:
    branches: [ main ]

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Deploy
        uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./mobile-fractal-3d/public
```

---

## Cloudflare Pages

1. Ve a [Cloudflare Pages](https://pages.cloudflare.com)
2. Conecta tu repositorio
3. Configuración:
   ```
   Build command: (dejar vacío)
   Build output directory: mobile-fractal-3d/public
   Root directory: mobile-fractal-3d
   ```

---

## Firebase Hosting

```bash
# Instalar Firebase CLI
npm install -g firebase-tools

# Login
firebase login

# Inicializar
cd mobile-fractal-3d
firebase init hosting

# Configurar public directory como: public

# Deploy
firebase deploy --only hosting
```

---

## Render

1. Ve a [Render](https://render.com)
2. New > Static Site
3. Conecta tu repositorio
4. Configuración:
   ```
   Build Command: (dejar vacío)
   Publish Directory: mobile-fractal-3d/public
   ```

---

## Servidor Local para Testing

### Python (Recomendado)

```bash
cd mobile-fractal-3d
python3 -m http.server 8080 --directory public

# Abre http://localhost:8080
```

### Node.js

```bash
# Instalar http-server
npm install -g http-server

cd mobile-fractal-3d/public
http-server -p 8080

# Abre http://localhost:8080
```

### PHP

```bash
cd mobile-fractal-3d/public
php -S localhost:8080
```

---

## Dominio Personalizado

Una vez desplegado en Netlify/Vercel/Cloudflare:

1. Compra un dominio (ej: fractal3d.com)
2. En tu plataforma de hosting:
   - Ve a Domain Settings
   - Add custom domain
   - Sigue las instrucciones para configurar DNS

3. **SSL/HTTPS:**
   - Se configura automáticamente en Netlify, Vercel, Cloudflare
   - Let's Encrypt gratuito incluido

---

## Testing antes del Deploy

```bash
# Ejecutar tests
cd mobile-fractal-3d
npm test

# Test en móvil local:
# 1. Encuentra tu IP local
ifconfig | grep "inet " | grep -v 127.0.0.1

# 2. Inicia servidor
python3 -m http.server 8080 --directory public

# 3. En tu móvil, abre: http://TU_IP:8080
# Ej: http://192.168.1.100:8080
```

---

## Optimizaciones Post-Deploy

### 1. PWA (Progressive Web App)

El `manifest.json` ya está incluido. Para habilitar instalación:

- Netlify/Vercel automáticamente sirven el manifest
- Los usuarios pueden "Agregar a pantalla de inicio"

### 2. CDN y Caché

Ya configurado en `netlify.toml`:
- JavaScript: cache 1 año
- CSS: cache 1 año
- HTML: sin cache (siempre fresco)

### 3. Compresión

Netlify/Vercel/Cloudflare automáticamente comprimen con:
- Gzip
- Brotli

### 4. Analytics (Opcional)

**Netlify Analytics:**
```bash
# Habilitar en dashboard de Netlify
# Settings > Analytics
```

**Google Analytics:**
Agregar a `public/index.html` antes de `</head>`:
```html
<script async src="https://www.googletagmanager.com/gtag/js?id=GA_MEASUREMENT_ID"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());
  gtag('config', 'GA_MEASUREMENT_ID');
</script>
```

---

## Troubleshooting

### Problema: Pantalla blanca

**Solución:**
1. Abre DevTools (F12)
2. Mira la consola
3. Si hay error "CORS" o "importmap":
   - Verifica que Three.js se carga desde CDN
   - Verifica que el servidor permite ES modules

### Problema: No funciona en móvil

**Solución:**
1. Verifica HTTPS (requerido para muchas features)
2. Verifica viewport meta tag
3. Prueba en Chrome/Safari móvil
4. Revisa permisos de pantalla completa

### Problema: Bajo rendimiento

**Solución:**
La app auto-detecta y ajusta calidad, pero puedes:
1. Reducir partículas en app.js
2. Bajar complejidad de geometrías
3. Desactivar antialiasing en móviles antiguos

---

## URLs de Ejemplo

Una vez desplegado:

- **Netlify**: `https://your-site-name.netlify.app`
- **Vercel**: `https://your-site-name.vercel.app`
- **GitHub Pages**: `https://username.github.io/repo-name`
- **Cloudflare**: `https://your-site-name.pages.dev`

---

## Checklist Pre-Deploy

- [ ] Tests pasan (`npm test`)
- [ ] Funciona en servidor local
- [ ] Funciona en móvil local
- [ ] manifest.json configurado
- [ ] netlify.toml presente
- [ ] .gitignore actualizado
- [ ] README con instrucciones

---

## Soporte

Para problemas:
1. Revisa la consola del navegador (F12)
2. Verifica que Three.js se carga correctamente
3. Prueba en modo incógnito
4. Verifica compatibilidad del navegador

**Navegadores compatibles:**
- Chrome/Edge 90+
- Safari 14+
- Firefox 88+
- Chrome Android 90+
- Safari iOS 14+

---

¡Listo para compartir tu experiencia fractal 3D con el mundo! 🌀✨
