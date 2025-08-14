cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Generate compile_commands.json for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/include/glad
    ${CMAKE_SOURCE_DIR}/external/include/KHR
)

# Set library directories
link_directories(${CMAKE_SOURCE_DIR}/external/lib)

# Add source files
set(SOURCES
    src/main.cpp
    src/EBO.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/shaderClass.cpp
)

# Add header files to the target (this helps with IDE support)
set(HEADERS
    include/shaderClass.h
    include/VBO.h
    include/EBO.h
    include/VAO.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add glad.c separately and compile it as C
target_sources(${PROJECT_NAME} PRIVATE src/glad.c)
set_source_files_properties(src/glad.c PROPERTIES LANGUAGE C)

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
