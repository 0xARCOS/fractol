# 🚀 Guía Paso a Paso: Deployment en Netlify

Esta guía te ayudará a desplegar tu experiencia fractal 3D en Netlify de la forma más sencilla.

## 📋 Requisitos Previos

- Una cuenta en Netlify (gratis): https://app.netlify.com/signup
- Node.js instalado (opcional para método CLI)
- Git instalado (opcional para método GitHub)

---

## 🎯 Método 1: Drag & Drop (MÁS FÁCIL - RECOMENDADO)

### Este método NO requiere terminal ni comandos

**Paso 1:** Ve a https://app.netlify.com/drop

**Paso 2:** Arrastra la carpeta `public` (que está dentro de `mobile-fractal-3d/`) a la página

**Paso 3:** ¡Listo! Netlify te dará una URL como:
```
https://random-name-123456.netlify.app
```

**Paso 4 (Opcional):** Cambia el nombre del sitio:
- Click en "Site settings"
- Click en "Change site name"
- Elige un nombre único (ej: `mi-fractal-3d`)
- Tu URL será: `https://mi-fractal-3d.netlify.app`

---

## 🎯 Método 2: Desde GitHub (Automático)

### Deployment automático cada vez que hagas push

**Paso 1:** Asegúrate de que tu código está en GitHub (ya lo está ✅)

**Paso 2:** Ve a https://app.netlify.com

**Paso 3:** Click en "Add new site" → "Import an existing project"

**Paso 4:** Selecciona "GitHub"

**Paso 5:** Autoriza Netlify para acceder a tus repos

**Paso 6:** Busca y selecciona tu repo: `0xARCOS/fractol`

**Paso 7:** Configura el build:
```
Branch to deploy: claude/fractal-3d-mobile-app-01RuUiySZ5Bk9p4xmnySrD4C
Base directory: mobile-fractal-3d
Publish directory: mobile-fractal-3d/public
Build command: (dejar vacío)
```

**Paso 8:** Click en "Deploy site"

**Paso 9:** Espera 30 segundos... ¡Listo!

### Ventaja:
- Cada push a GitHub actualizará automáticamente el sitio
- No necesitas volver a desplegar manualmente

---

## 🎯 Método 3: CLI (Para desarrolladores)

### Usando la terminal

**Paso 1:** Instala Netlify CLI
```bash
npm install -g netlify-cli
```

**Paso 2:** Navega al directorio
```bash
cd mobile-fractal-3d
```

**Paso 3:** Login en Netlify
```bash
netlify login
```
Se abrirá tu navegador para autorizar.

**Paso 4:** Deploy
```bash
netlify deploy --prod --dir=public
```

**Paso 5:** Sigue las instrucciones:
- "Create & configure a new site" → Enter
- Team: Selecciona tu team → Enter
- Site name: (opcional) → Enter
- Confirm → Enter

**Paso 6:** ¡Listo! Verás tu URL en la terminal.

---

## 🎯 Método 4: Script Automático

### Usa el script que he creado

**Paso 1:** Da permisos de ejecución
```bash
chmod +x deploy.sh
```

**Paso 2:** Ejecuta el script
```bash
./deploy.sh
```

**Paso 3:** Sigue las instrucciones en pantalla

El script:
- ✅ Verifica la estructura
- ✅ Instala Netlify CLI si es necesario
- ✅ Ejecuta los tests
- ✅ Te guía en el deployment
- ✅ Maneja errores automáticamente

---

## ❓ Troubleshooting

### Problema: "npm: command not found"

**Solución:** Instala Node.js
- **Ubuntu/Debian:**
  ```bash
  curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -
  sudo apt-get install -y nodejs
  ```
- **macOS:**
  ```bash
  brew install node
  ```
- **Windows:** Descarga de https://nodejs.org

Luego usa el **Método 1 (Drag & Drop)** que no requiere Node.js.

---

### Problema: "netlify: command not found"

**Solución:** Usa el **Método 1 (Drag & Drop)** que no requiere CLI.

O instala manualmente:
```bash
npm install -g netlify-cli
```

Si sigue sin funcionar:
```bash
sudo npm install -g netlify-cli
```

---

### Problema: "Permission denied" al instalar

**Solución:**
```bash
sudo npm install -g netlify-cli
```

O usa el **Método 1 (Drag & Drop)**.

---

### Problema: "Not authorized"

**Solución:**
```bash
netlify logout
netlify login
```

---

### Problema: El sitio carga pero está en blanco

**Causas posibles:**

1. **Archivos no están en public/**

   **Verificar:**
   ```bash
   ls -la mobile-fractal-3d/public/
   ```

   Debes ver:
   - index.html
   - app.js
   - style.css
   - manifest.json

2. **Error en consola del navegador**

   **Verificar:**
   - Abre el sitio desplegado
   - Presiona F12
   - Ve a la pestaña "Console"
   - Copia el error aquí

3. **Desplegaste la carpeta incorrecta**

   **Solución:** Asegúrate de arrastrar `mobile-fractal-3d/public/`, NO `mobile-fractal-3d/`

---

### Problema: Three.js no carga (error CORS)

**Solución:** Ya está configurado para usar CDN de jsDelivr. Si hay error:

1. Abre `public/index.html`
2. Verifica que contenga:
   ```html
   <script type="importmap">
   {
       "imports": {
           "three": "https://cdn.jsdelivr.net/npm/three@0.159.0/build/three.module.js"
       }
   }
   </script>
   ```

---

## 🎨 Personalización Post-Deployment

### Cambiar nombre del sitio

1. Ve a tu dashboard: https://app.netlify.com
2. Selecciona tu sitio
3. Site settings → General → Site details
4. Click "Change site name"
5. Ingresa: `tu-nombre-elegido`
6. Tu URL será: `https://tu-nombre-elegido.netlify.app`

### Agregar dominio personalizado

1. En Site settings → Domain management
2. Click "Add custom domain"
3. Ingresa tu dominio (ej: `fractales3d.com`)
4. Sigue instrucciones para configurar DNS
5. SSL se configura automáticamente ✅

---

## 📱 Verificar Deployment

Una vez desplegado, verifica:

1. **Accede desde tu móvil** a la URL
2. **Toca la pantalla** - debe mostrar instrucciones
3. **Click en "Comenzar Experiencia"**
4. **Prueba los gestos:**
   - Un dedo → rotar
   - Pinch → zoom
   - Doble tap → reset

Si todo funciona: **¡ÉXITO!** 🎉

---

## 🆘 ¿Sigues con problemas?

**Opción A:** Usa el **Método 1 (Drag & Drop)**
- Es el más simple
- No requiere terminal
- Funciona siempre

**Opción B:** Comparte el error exacto:
1. ¿Qué método estás usando?
2. ¿Qué comando ejecutaste?
3. ¿Qué error apareció?
4. Screenshot si es posible

---

## ✅ Checklist Pre-Deployment

Marca cada item:

- [ ] Archivos están en `mobile-fractal-3d/public/`
- [ ] `index.html` existe en `public/`
- [ ] `app.js` existe en `public/`
- [ ] `style.css` existe en `public/`
- [ ] Tests pasan: `node test/test.js`
- [ ] Tienes cuenta en Netlify
- [ ] Estás logueado (si usas CLI)

---

## 🎯 URLs Importantes

- **Netlify Drop:** https://app.netlify.com/drop
- **Netlify Dashboard:** https://app.netlify.com
- **Documentación Netlify:** https://docs.netlify.com
- **Tu repo en GitHub:** https://github.com/0xARCOS/fractol

---

¡Tu experiencia fractal 3D estará online en menos de 5 minutos! 🌀✨
