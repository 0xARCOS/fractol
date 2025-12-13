#!/usr/bin/env node

/**
 * Simple test suite for Fractal 3D Mobile Experience
 * Tests basic file structure and configuration
 */

const fs = require('fs');
const path = require('path');

// ANSI color codes
const colors = {
    green: '\x1b[32m',
    red: '\x1b[31m',
    yellow: '\x1b[33m',
    blue: '\x1b[34m',
    reset: '\x1b[0m'
};

let passedTests = 0;
let failedTests = 0;

function test(description, callback) {
    try {
        callback();
        console.log(`${colors.green}✓${colors.reset} ${description}`);
        passedTests++;
    } catch (error) {
        console.log(`${colors.red}✗${colors.reset} ${description}`);
        console.log(`  ${colors.red}Error: ${error.message}${colors.reset}`);
        failedTests++;
    }
}

function fileExists(filePath) {
    if (!fs.existsSync(filePath)) {
        throw new Error(`File not found: ${filePath}`);
    }
}

function fileContains(filePath, content) {
    const fileContent = fs.readFileSync(filePath, 'utf8');
    if (!fileContent.includes(content)) {
        throw new Error(`File ${filePath} does not contain: ${content}`);
    }
}

console.log(`\n${colors.blue}Running Fractal 3D Mobile Tests...${colors.reset}\n`);

// Test file structure
test('netlify.toml exists', () => fileExists('netlify.toml'));
test('package.json exists', () => fileExists('package.json'));
test('README.md exists', () => fileExists('README.md'));
test('LICENSE exists', () => fileExists('LICENSE'));
test('.gitignore exists', () => fileExists('.gitignore'));

// Test public directory
test('public/index.html exists', () => fileExists('public/index.html'));
test('public/style.css exists', () => fileExists('public/style.css'));
test('public/app.js exists', () => fileExists('public/app.js'));

// Test HTML structure
test('HTML contains viewport meta tag', () =>
    fileContains('public/index.html', 'viewport')
);
test('HTML contains fractal-canvas', () =>
    fileContains('public/index.html', 'fractal-canvas')
);
test('HTML loads Three.js', () =>
    fileContains('public/index.html', 'three')
);

// Test CSS
test('CSS contains mobile-optimized styles', () =>
    fileContains('public/style.css', 'touch-action')
);
test('CSS contains animations', () =>
    fileContains('public/style.css', '@keyframes')
);

// Test JavaScript
test('app.js imports Three.js', () =>
    fileContains('public/app.js', "import * as THREE from 'three'")
);
test('app.js contains fractal generation', () =>
    fileContains('public/app.js', 'createMandelbulb')
);
test('app.js contains touch controls', () =>
    fileContains('public/app.js', 'handleTouchStart')
);
test('app.js contains animation loop', () =>
    fileContains('public/app.js', 'requestAnimationFrame')
);

// Test configuration
test('netlify.toml has correct publish directory', () =>
    fileContains('netlify.toml', 'publish = "public"')
);

// Test package.json
test('package.json has correct name', () =>
    fileContains('package.json', 'fractal-3d-mobile')
);
test('package.json has dev script', () =>
    fileContains('package.json', '"dev"')
);

// Summary
console.log(`\n${colors.blue}Test Summary:${colors.reset}`);
console.log(`${colors.green}Passed: ${passedTests}${colors.reset}`);
console.log(`${colors.red}Failed: ${failedTests}${colors.reset}`);

if (failedTests === 0) {
    console.log(`\n${colors.green}✓ All tests passed!${colors.reset}\n`);
    process.exit(0);
} else {
    console.log(`\n${colors.red}✗ Some tests failed${colors.reset}\n`);
    process.exit(1);
}
