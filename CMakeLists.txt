cmake_minimum_required(VERSION 3.10)
project(redline)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Emscripten-specific settings
if(EMSCRIPTEN)
    # Create executable
    add_executable(redline ${SOURCE_FILES})
    
    # Set Emscripten-specific compiler and linker flags
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    # Set SDL2 and SDL2_image as Emscripten ports
    set(USE_SDL2 "-s USE_SDL=2")
    set(USE_SDL2_IMAGE "-s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"png\"]'")
    
    # Memory settings
    set(MEMORY_SETTINGS "-s INITIAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s TOTAL_STACK=4194304")
    
    # Optimization level for release build
    set(OPTIMIZATION "-O3")
    
    # Export main function to be called from JavaScript
    set(EXPORTED_FUNCTIONS "-s EXPORTED_RUNTIME_METHODS=['cwrap'] -s EXPORTED_FUNCTIONS='[\"_main\"]'")
    
    # Preload assets
    set(PRELOAD "--preload-file assets")
    
    # Shell file (HTML template)
    set(SHELL_FILE "--shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell.html")
    
    # Combine all flags
    set(EMSCRIPTEN_LINK_FLAGS "${USE_SDL2} ${USE_SDL2_IMAGE} ${MEMORY_SETTINGS} ${OPTIMIZATION} ${EXPORTED_FUNCTIONS} ${PRELOAD} ${SHELL_FILE}")
    
    # Apply the flags
    set_target_properties(redline PROPERTIES LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}")
else()
    # Native build settings
    add_executable(redline ${SOURCE_FILES})
    
    # Find and link SDL2 and SDL2_image
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(redline ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()
