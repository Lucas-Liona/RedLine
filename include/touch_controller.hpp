#pragma once

#include "SDL2/SDL.h"
#include "game.hpp"
#include "ecs.hpp"
#include "transform_component.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

class TouchController {
public:
    static void init() {
#ifdef __EMSCRIPTEN__
        // Add touch controls to the canvas using JavaScript
        EM_ASM(
            // Virtual control dimensions
            var controlSize = 100;
            var buttonSize = 50;
            
            // Create control overlay container
            var controlsContainer = document.createElement('div');
            controlsContainer.id = 'touch-controls';
            controlsContainer.style.position = 'absolute';
            controlsContainer.style.bottom = '20px';
            controlsContainer.style.left = '50%';
            controlsContainer.style.transform = 'translateX(-50%)';
            controlsContainer.style.display = 'flex';
            controlsContainer.style.justifyContent = 'space-between';
            controlsContainer.style.width = '90%';
            controlsContainer.style.maxWidth = '600px';
            controlsContainer.style.pointerEvents = 'none';
            
            // Create D-pad container
            var dpadContainer = document.createElement('div');
            dpadContainer.style.width = controlSize + 'px';
            dpadContainer.style.height = controlSize + 'px';
            dpadContainer.style.position = 'relative';
            dpadContainer.style.pointerEvents = 'all';
            
            // Create buttons container
            var buttonsContainer = document.createElement('div');
            buttonsContainer.style.width = controlSize + 'px';
            buttonsContainer.style.height = controlSize + 'px';
            buttonsContainer.style.position = 'relative';
            buttonsContainer.style.pointerEvents = 'all';
            
            // Create D-pad buttons
            var directions = [
                { id: 'up', x: 35, y: 0, key: 38 },      // Up arrow
                { id: 'right', x: 70, y: 35, key: 39 },  // Right arrow
                { id: 'down', x: 35, y: 70, key: 40 },   // Down arrow
                { id: 'left', x: 0, y: 35, key: 37 }     // Left arrow
            ];
            
            for (var i = 0; i < directions.length; i++) {
                var dir = directions[i];
                var btn = document.createElement('div');
                btn.id = 'touch-' + dir.id;
                btn.style.width = buttonSize + 'px';
                btn.style.height = buttonSize + 'px';
                btn.style.position = 'absolute';
                btn.style.left = dir.x + 'px';
                btn.style.top = dir.y + 'px';
                btn.style.backgroundColor = 'rgba(255, 255, 255, 0.3)';
                btn.style.borderRadius = '50%';
                btn.style.display = 'flex';
                btn.style.justifyContent = 'center';
                btn.style.alignItems = 'center';
                
                btn.dataset.key = dir.key;
                
                // Touch event handlers for D-pad
                btn.addEventListener('touchstart', function(e) {
                    e.preventDefault();
                    this.style.backgroundColor = 'rgba(255, 0, 0, 0.5)';
                    // Simulate keydown event
                    var keyEvent = new KeyboardEvent('keydown', {
                        keyCode: parseInt(this.dataset.key),
                        which: parseInt(this.dataset.key)
                    });
                    document.dispatchEvent(keyEvent);
                });
                
                btn.addEventListener('touchend', function(e) {
                    e.preventDefault();
                    this.style.backgroundColor = 'rgba(255, 255, 255, 0.3)';
                    // Simulate keyup event
                    var keyEvent = new KeyboardEvent('keyup', {
                        keyCode: parseInt(this.dataset.key),
                        which: parseInt(this.dataset.key)
                    });
                    document.dispatchEvent(keyEvent);
                });
                
                dpadContainer.appendChild(btn);
            }
            
            // Create action buttons
            var actions = [
                { id: 'jump', x: 35, y: 0, key: 32, label: 'Jump' },  // Space
                { id: 'light', x: 0, y: 35, key: 74, label: 'L' },    // J
                { id: 'heavy', x: 70, y: 35, key: 75, label: 'H' },   // K
                { id: 'special', x: 35, y: 70, key: 76, label: 'S' }  // L
            ];
            
            for (var i = 0; i < actions.length; i++) {
                var act = actions[i];
                var btn = document.createElement('div');
                btn.id = 'touch-' + act.id;
                btn.style.width = buttonSize + 'px';
                btn.style.height = buttonSize + 'px';
                btn.style.position = 'absolute';
                btn.style.left = act.x + 'px';
                btn.style.top = act.y + 'px';
                btn.style.backgroundColor = 'rgba(255, 255, 255, 0.3)';
                btn.style.borderRadius = '50%';
                btn.style.display = 'flex';
                btn.style.justifyContent = 'center';
                btn.style.alignItems = 'center';
                btn.style.color = 'white';
                btn.style.fontFamily = 'Arial, sans-serif';
                btn.style.fontSize = '14px';
                btn.style.fontWeight = 'bold';
                btn.textContent = act.label;
                
                btn.dataset.key = act.key;
                
                // Touch event handlers for action buttons
                btn.addEventListener('touchstart', function(e) {
                    e.preventDefault();
                    this.style.backgroundColor = 'rgba(0, 0, 255, 0.5)';
                    // Simulate keydown event
                    var keyEvent = new KeyboardEvent('keydown', {
                        keyCode: parseInt(this.dataset.key),
                        which: parseInt(this.dataset.key)
                    });
                    document.dispatchEvent(keyEvent);
                });
                
                btn.addEventListener('touchend', function(e) {
                    e.preventDefault();
                    this.style.backgroundColor = 'rgba(255, 255, 255, 0.3)';
                    // Simulate keyup event
                    var keyEvent = new KeyboardEvent('keyup', {
                        keyCode: parseInt(this.dataset.key),
                        which: parseInt(this.dataset.key)
                    });
                    document.dispatchEvent(keyEvent);
                });
                
                buttonsContainer.appendChild(btn);
            }
            
            // Add toggle button for mobile controls
            var toggleBtn = document.createElement('div');
            toggleBtn.id = 'touch-toggle';
            toggleBtn.style.position = 'absolute';
            toggleBtn.style.top = '10px';
            toggleBtn.style.right = '10px';
            toggleBtn.style.width = '40px';
            toggleBtn.style.height = '40px';
            toggleBtn.style.backgroundColor = 'rgba(255, 255, 255, 0.3)';
            toggleBtn.style.borderRadius = '5px';
            toggleBtn.style.display = 'flex';
            toggleBtn.style.justifyContent = 'center';
            toggleBtn.style.alignItems = 'center';
            toggleBtn.style.pointerEvents = 'all';
            toggleBtn.style.cursor = 'pointer';
            toggleBtn.textContent = '👆';
            
            // Add containers to DOM
            controlsContainer.appendChild(dpadContainer);
            controlsContainer.appendChild(buttonsContainer);
            
            // Hide controls by default
            controlsContainer.style.display = 'none';
            
            // Function to detect mobile devices
            function isMobileDevice() {
                return /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);
            }
            
            // Toggle controls visibility
            toggleBtn.addEventListener('click', function() {
                if (controlsContainer.style.display === 'none') {
                    controlsContainer.style.display = 'flex';
                } else {
                    controlsContainer.style.display = 'none';
                }
            });
            
            // Append controls to game container
            document.querySelector('.game-container').appendChild(controlsContainer);
            document.querySelector('.game-container').appendChild(toggleBtn);
            
            // Show controls automatically if on mobile
            if (isMobileDevice()) {
                controlsContainer.style.display = 'flex';
            }
        );
    }
#else
        // No special handling needed for native builds
    }
#endif
};