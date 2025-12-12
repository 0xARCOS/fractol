// Service Worker for Fractal 3D Experience
// Version 1.0.0 - Optimized for performance

const CACHE_VERSION = 'fractal-3d-v1.0.0';
const RUNTIME_CACHE = 'fractal-3d-runtime';

// Assets to cache immediately
const PRECACHE_ASSETS = [
    '/',
    '/index.html',
    '/app.js',
    '/style.css',
    '/manifest.json'
];

// CDN assets to cache on first use
const CDN_CACHE = 'fractal-3d-cdn';

// Install event - cache critical assets
self.addEventListener('install', (event) => {
    console.log('Service Worker installing...');
    event.waitUntil(
        caches.open(CACHE_VERSION)
            .then((cache) => {
                console.log('Caching app shell');
                return cache.addAll(PRECACHE_ASSETS);
            })
            .then(() => self.skipWaiting())
    );
});

// Activate event - clean up old caches
self.addEventListener('activate', (event) => {
    console.log('Service Worker activating...');
    event.waitUntil(
        caches.keys().then((cacheNames) => {
            return Promise.all(
                cacheNames.map((cacheName) => {
                    if (cacheName !== CACHE_VERSION &&
                        cacheName !== RUNTIME_CACHE &&
                        cacheName !== CDN_CACHE) {
                        console.log('Deleting old cache:', cacheName);
                        return caches.delete(cacheName);
                    }
                })
            );
        }).then(() => self.clients.claim())
    );
});

// Fetch event - serve from cache, fallback to network
self.addEventListener('fetch', (event) => {
    const { request } = event;
    const url = new URL(request.url);

    // Handle CDN requests (Three.js)
    if (url.hostname === 'cdn.jsdelivr.net') {
        event.respondWith(
            caches.open(CDN_CACHE).then((cache) => {
                return cache.match(request).then((response) => {
                    if (response) {
                        return response;
                    }
                    return fetch(request).then((networkResponse) => {
                        // Cache successful responses
                        if (networkResponse && networkResponse.status === 200) {
                            cache.put(request, networkResponse.clone());
                        }
                        return networkResponse;
                    });
                });
            })
        );
        return;
    }

    // Handle app assets - Cache First strategy
    if (url.origin === location.origin) {
        event.respondWith(
            caches.match(request).then((response) => {
                if (response) {
                    return response;
                }

                return fetch(request).then((networkResponse) => {
                    // Cache successful responses
                    if (networkResponse && networkResponse.status === 200) {
                        const responseToCache = networkResponse.clone();
                        caches.open(RUNTIME_CACHE).then((cache) => {
                            cache.put(request, responseToCache);
                        });
                    }
                    return networkResponse;
                }).catch(() => {
                    // Return offline page if available
                    return caches.match('/index.html');
                });
            })
        );
        return;
    }

    // For everything else, network first
    event.respondWith(fetch(request));
});

// Message handler for cache updates
self.addEventListener('message', (event) => {
    if (event.data && event.data.type === 'SKIP_WAITING') {
        self.skipWaiting();
    }
});
