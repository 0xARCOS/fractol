#!/bin/bash

# 🚀 Script de Inicio Rápido - Fractal 3D Ultra-Light
# ===================================================

echo "🌀 Fractal 3D - Ultra-Light Version"
echo "===================================="
echo ""

# Colores
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Verificar que estamos en el directorio correcto
if [ ! -f "public/index.html" ]; then
    echo "❌ Error: Ejecuta este script desde mobile-fractal-3d/"
    exit 1
fi

echo -e "${GREEN}✅ Directorio correcto${NC}"
echo ""

# Verificar archivos
echo "📁 Verificando archivos ultra-light..."
if [ -f "public/app-lite.js" ]; then
    SIZE=$(du -h public/app-lite.js | cut -f1)
    echo -e "${GREEN}✅ app-lite.js encontrado ($SIZE)${NC}"
else
    echo -e "${YELLOW}⚠️  app-lite.js no encontrado${NC}"
fi

if [ -f "public/sw.js" ]; then
    echo -e "${GREEN}✅ Service Worker encontrado${NC}"
fi
echo ""

# Mostrar opciones
echo -e "${BLUE}Selecciona método de servidor:${NC}"
echo ""
echo "1) Python 3 (Recomendado - más simple)"
echo "2) Python 2 (Legacy)"
echo "3) Node.js (npx - sin instalación global)"
echo "4) Solo mostrar URL del puerto 8080"
echo ""
read -p "Opción [1]: " option
option=${option:-1}

PORT=8080

case $option in
    1)
        echo ""
        echo -e "${GREEN}🚀 Iniciando servidor Python 3 en puerto $PORT...${NC}"
        echo ""
        echo -e "${YELLOW}IMPORTANTE:${NC}"
        echo -e "Para evitar caché del navegador:"
        echo -e "  1. Abre: ${BLUE}http://localhost:$PORT${NC}"
        echo -e "  2. Presiona: ${YELLOW}Cmd+Shift+R${NC} (Mac) o ${YELLOW}Ctrl+Shift+R${NC} (Windows/Linux)"
        echo -e "  3. O abre DevTools (F12) → Network → marca 'Disable cache'"
        echo ""
        echo -e "${GREEN}En la consola deberías ver:${NC}"
        echo "  '🚀 Ultra-Light Fractal Engine starting...'"
        echo "  '✅ Ready! Bundle size: ~15KB (vs 1.27MB Three.js)'"
        echo ""
        echo "Presiona Ctrl+C para detener el servidor"
        echo ""
        python3 -m http.server $PORT --directory public
        ;;
    2)
        echo ""
        echo -e "${GREEN}🚀 Iniciando servidor Python 2 en puerto $PORT...${NC}"
        echo ""
        cd public && python -m SimpleHTTPServer $PORT
        ;;
    3)
        echo ""
        echo -e "${GREEN}🚀 Iniciando servidor con npx (sin instalación)...${NC}"
        echo ""
        npx http-server public -p $PORT
        ;;
    4)
        echo ""
        echo -e "${BLUE}Servidor ya corriendo en: http://localhost:$PORT${NC}"
        echo ""
        echo -e "${YELLOW}Para limpiar caché:${NC}"
        echo "  - Chrome: Cmd+Shift+R (Mac) o Ctrl+Shift+R (Windows)"
        echo "  - O: DevTools (F12) → Network → 'Disable cache' → Reload"
        ;;
    *)
        echo "Opción inválida"
        exit 1
        ;;
esac
