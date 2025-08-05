cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Generate compile_commands.json for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Platform-specific GLFW handling
if(WIN32)
    # Windows: Use static library (.a file)
    set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/external/lib/libglfw3.a)
    include_directories(${CMAKE_SOURCE_DIR}/external/include/GLFW)
elseif(APPLE)
    # macOS: Use dynamic library (.dylib file)
    set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/external/lib/libglfw.3.dylib)
    include_directories(${CMAKE_SOURCE_DIR}/external/include/GLFW)
else()
    # Linux: Use dynamic library
    set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/external/lib/libglfw.3.so)
    include_directories(${CMAKE_SOURCE_DIR}/external/include/GLFW)
endif()

# Set include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/include/glad
    ${CMAKE_SOURCE_DIR}/external/include/KHR
)

# Set library directories
link_directories(${CMAKE_SOURCE_DIR}/external/lib)

# Add source files
set(SOURCES
    src/glad.c
    src/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
if(WIN32)
    # Windows-specific linking
    target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw3
        opengl32
    )
elseif(APPLE)
    # macOS-specific linking
    target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        ${GLFW_LIBRARY}
        "-framework OpenGL" 
        "-framework Cocoa" 
        "-framework IOKit" 
        "-framework CoreVideo"
    )
else()
    # Linux-specific linking
    target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        ${GLFW_LIBRARY}
        GL X11 Xrandr Xinerama Xi Xxf86vm Xcursor
    )
endif()

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
