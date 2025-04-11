// Responsive canvas scaling for Redline game
(function() {
    // Reference to the canvas element
    var canvas = document.getElementById('canvas');
    // Reference to the game container
    var gameContainer = document.querySelector('.game-container');
    
    // Original game dimensions
    var originalWidth = 600;
    var originalHeight = 800;
    
    // Function to resize the canvas while maintaining aspect ratio
    function resizeCanvas() {
        var windowWidth = window.innerWidth;
        var windowHeight = window.innerHeight;
        
        // Calculate maximum dimensions that fit the window
        var maxWidth = Math.min(windowWidth * 0.95, originalWidth);
        var maxHeight = Math.min(windowHeight * 0.95, originalHeight);
        
        // Determine scale based on which dimension is more constraining
        var scaleWidth = maxWidth / originalWidth;
        var scaleHeight = maxHeight / originalHeight;
        var scale = Math.min(scaleWidth, scaleHeight);
        
        // Set new dimensions
        var newWidth = Math.floor(originalWidth * scale);
        var newHeight = Math.floor(originalHeight * scale);
        
        // Update container size
        gameContainer.style.width = newWidth + 'px';
        gameContainer.style.height = newHeight + 'px';
        
        // Update canvas size
        canvas.style.width = newWidth + 'px';
        canvas.style.height = newHeight + 'px';
        
        // Center the game container
        gameContainer.style.margin = '0 auto';
    }
    
    // Initial resize
    window.addEventListener('load', resizeCanvas);
    
    // Resize on window size change
    window.addEventListener('resize', resizeCanvas);
})();