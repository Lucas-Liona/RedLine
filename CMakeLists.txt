cmake_minimum_required(VERSION 3.10)
project(redline)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add compiler flags for SDL
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2")

# Create executable
add_executable(redline ${SOURCE_FILES})

# Set linker flags
set(LINK_FLAGS "--preload-file assets -sALLOW_MEMORY_GROWTH=1 -O2")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/shell.html")
  set(LINK_FLAGS "${LINK_FLAGS} --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell.html")
endif()

set_target_properties(redline PROPERTIES LINK_FLAGS "${LINK_FLAGS}")

# Copy JavaScript files to the build directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/responsive_canvas.js")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/responsive_canvas.js ${CMAKE_CURRENT_BINARY_DIR}/responsive_canvas.js COPYONLY)
endif()
