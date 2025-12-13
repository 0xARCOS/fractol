#!/bin/bash

# 🚀 Script de Deployment Automático para Netlify
# Este script despliega tu app de fractales 3D a Netlify

set -e  # Exit on error

echo "🌀 Fractal 3D - Deployment Script"
echo "=================================="
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Check if we're in the right directory
if [ ! -f "netlify.toml" ]; then
    echo -e "${RED}❌ Error: netlify.toml no encontrado${NC}"
    echo "Por favor ejecuta este script desde mobile-fractal-3d/"
    exit 1
fi

echo -e "${GREEN}✅ Estructura de proyecto verificada${NC}"
echo ""

# Check if netlify CLI is installed
if ! command -v netlify &> /dev/null; then
    echo -e "${YELLOW}⚠️  Netlify CLI no está instalado${NC}"
    echo ""
    echo "Instalando Netlify CLI..."
    npm install -g netlify-cli

    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Error instalando Netlify CLI${NC}"
        echo ""
        echo "Intenta instalar manualmente:"
        echo "  npm install -g netlify-cli"
        echo ""
        echo "O sigue el método de Drag & Drop en:"
        echo "  https://app.netlify.com/drop"
        exit 1
    fi
fi

echo -e "${GREEN}✅ Netlify CLI disponible${NC}"
echo ""

# Check if logged in
echo "Verificando sesión de Netlify..."
if ! netlify status &> /dev/null; then
    echo -e "${YELLOW}⚠️  No estás logueado en Netlify${NC}"
    echo ""
    echo "Abriendo navegador para login..."
    netlify login

    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Error en login${NC}"
        exit 1
    fi
fi

echo -e "${GREEN}✅ Sesión de Netlify activa${NC}"
echo ""

# Run tests
echo "Ejecutando tests..."
if [ -f "test/test.js" ]; then
    node test/test.js

    if [ $? -ne 0 ]; then
        echo -e "${RED}❌ Tests fallaron${NC}"
        echo ""
        read -p "¿Quieres continuar de todas formas? (y/N): " continue
        if [[ ! $continue =~ ^[Yy]$ ]]; then
            exit 1
        fi
    else
        echo -e "${GREEN}✅ Todos los tests pasaron${NC}"
    fi
else
    echo -e "${YELLOW}⚠️  No se encontraron tests${NC}"
fi
echo ""

# Check public directory
if [ ! -d "public" ]; then
    echo -e "${RED}❌ Directorio public/ no encontrado${NC}"
    exit 1
fi

file_count=$(ls -1 public/ | wc -l)
echo -e "${GREEN}✅ Directorio public/ encontrado ($file_count archivos)${NC}"
echo ""

# List files to be deployed
echo -e "${BLUE}📦 Archivos a desplegar:${NC}"
ls -lh public/
echo ""

# Deployment options
echo "Opciones de deployment:"
echo "1) Deploy a producción (recomendado)"
echo "2) Deploy de prueba (draft)"
echo "3) Cancelar"
echo ""

read -p "Selecciona una opción (1-3): " option

case $option in
    1)
        echo ""
        echo -e "${BLUE}🚀 Desplegando a PRODUCCIÓN...${NC}"
        echo ""
        netlify deploy --prod --dir=public

        if [ $? -eq 0 ]; then
            echo ""
            echo -e "${GREEN}✅ ¡Deployment exitoso!${NC}"
            echo ""
            echo "Tu app está live en la URL mostrada arriba ☝️"
            echo ""
        else
            echo ""
            echo -e "${RED}❌ Error en deployment${NC}"
            echo ""
            echo "Intenta el método alternativo:"
            echo "1. Ve a https://app.netlify.com/drop"
            echo "2. Arrastra la carpeta 'public' a la página"
            exit 1
        fi
        ;;
    2)
        echo ""
        echo -e "${BLUE}🚀 Desplegando DRAFT (prueba)...${NC}"
        echo ""
        netlify deploy --dir=public

        if [ $? -eq 0 ]; then
            echo ""
            echo -e "${GREEN}✅ ¡Draft deployment exitoso!${NC}"
            echo ""
            echo "Revisa tu app en la URL de prueba mostrada arriba ☝️"
            echo ""
            echo "Si todo se ve bien, ejecuta:"
            echo "  netlify deploy --prod --dir=public"
        else
            echo ""
            echo -e "${RED}❌ Error en deployment${NC}"
            exit 1
        fi
        ;;
    3)
        echo ""
        echo "Deployment cancelado"
        exit 0
        ;;
    *)
        echo ""
        echo -e "${RED}❌ Opción inválida${NC}"
        exit 1
        ;;
esac

echo ""
echo -e "${GREEN}🎉 ¡Listo! Tu experiencia fractal 3D está online${NC}"
echo ""
