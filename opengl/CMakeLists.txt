cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Generate compile_commands.json for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Set include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/include/glad
    ${CMAKE_SOURCE_DIR}/external/include/GLFW
    ${CMAKE_SOURCE_DIR}/external/include/KHR
)

# Set library directories
link_directories(${CMAKE_SOURCE_DIR}/external/lib)

# Add source files
set(SOURCES
    src/glad.c
    # Add your source files here, for example:
    src/main.cpp
    # src/shader.cpp
    # etc.
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw3
    # Add other libraries as needed
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    target_link_libraries(${PROJECT_NAME} opengl32)
elseif(APPLE)
    # macOS-specific settings
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    # Linux-specific settings
    target_link_libraries(${PROJECT_NAME} GL X11 Xrandr Xinerama Xi Xxf86vm Xcursor)
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
