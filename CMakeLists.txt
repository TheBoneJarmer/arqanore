cmake_minimum_required(VERSION 3.16)
project(arqanore VERSION 1.0.0 DESCRIPTION "Arqanore is a 2D OpenGL game library")

set(CMAKE_CXX_STANDARD 23)

# Generate variables for all sources
set(ARQ_INCLUDE
        include/arqanore/audio.h
        include/arqanore/color.h
        include/arqanore/exceptions.h
        include/arqanore/font.h
        include/arqanore/joystick.h
        include/arqanore/keyboard.h
        include/arqanore/mathhelper.h
        include/arqanore/mouse.h
        include/arqanore/polygon.h
        include/arqanore/renderer.h
        include/arqanore/shader.h
        include/arqanore/shaders.h
        include/arqanore/sound.h
        include/arqanore/utils.h
        include/arqanore/window.h
        include/arqanore/texture.h
        include/arqanore/vector2.h
        include/arqanore/sprite.h
        include/arqanore/vector3.h
        include/arqanore/modelparser.h
        include/arqanore/model.h
        include/arqanore/mesh.h
        include/arqanore/matrix4.h
        include/arqanore/matrix3.h
        include/arqanore/material.h
        include/arqanore/light.h
        include/arqanore/camera.h
        include/arqanore/scene.h
        include/arqanore/collider.h
        include/arqanore/collisionbody.h
        include/arqanore/physics.h
        include/arqanore/rigidbody.h
        include/arqanore/quaternion.h)

set(ARQ_SRC
        src/arqanore/glad/gl.c
        src/arqanore/window.cpp
        src/arqanore/exceptions.cpp
        src/arqanore/utils.cpp
        src/arqanore/keyboard.cpp
        src/arqanore/mouse.cpp
        src/arqanore/joystick.cpp
        src/arqanore/audio.cpp
        src/arqanore/sound.cpp
        src/arqanore/mathhelper.cpp
        src/arqanore/shader.cpp
        src/arqanore/color.cpp
        src/arqanore/font.cpp
        src/arqanore/polygon.cpp
        src/arqanore/shaders.cpp
        src/arqanore/renderer.cpp
        src/arqanore/texture.cpp
        src/arqanore/vector2.cpp
        src/arqanore/sprite.cpp
        src/arqanore/camera.cpp
        src/arqanore/light.cpp
        src/arqanore/material.cpp
        src/arqanore/matrix3.cpp
        src/arqanore/matrix4.cpp
        src/arqanore/mesh.cpp
        src/arqanore/model.cpp
        src/arqanore/modelparser.cpp
        src/arqanore/vector3.cpp
        src/arqanore/scene.cpp
        src/arqanore/collider.cpp
        src/arqanore/collisionbody.cpp
        src/arqanore/rigidbody.cpp
        src/arqanore/physics.cpp
        src/arqanore/quaternion.cpp)

# Generate variables for the compiler and linker
set(ARQ_LIBRARIES glfw freetype soloudw reactphysics3d dl -Wl,-rpath='$ORIGIN:$ORIGIN/lib')

# Override variables for oparting systems other than Linux
if (WIN32)
    include_directories("C:/Include")
    link_directories("C:/Lib")

    set(ARQ_LIBRARIES glfw3 freetype soloudw reactphysics3d -Wl,-rpath='$ORIGIN:$ORIGIN/lib')
endif (WIN32)

# Configure arqanore
add_library(arqanore ${ARQ_INCLUDE} ${ARQ_SRC})
target_include_directories(arqanore PUBLIC include/)
target_link_libraries(arqanore PUBLIC ${ARQ_LIBRARIES})
set_target_properties(arqanore PROPERTIES PUBLIC_HEADER include/arqanore/arqanore.h)
set_target_properties(arqanore PROPERTIES OUTPUT_NAME "arqanore")

# Configure arqanore examples
add_executable(example_window ${ARQ_INCLUDE} ${ARQ_SRC} src/examples/window/main.cpp)
target_include_directories(example_window PUBLIC include/)
target_link_libraries(example_window PRIVATE ${ARQ_LIBRARIES})

add_executable(example_sprites ${ARQ_INCLUDE} ${ARQ_SRC} src/examples/sprites/main.cpp)
target_include_directories(example_sprites PUBLIC include/)
target_link_libraries(example_sprites PRIVATE ${ARQ_LIBRARIES})

add_executable(example_fonts ${ARQ_INCLUDE} ${ARQ_SRC} src/examples/fonts/main.cpp)
target_include_directories(example_fonts PUBLIC include/)
target_link_libraries(example_fonts PRIVATE ${ARQ_LIBRARIES})

add_executable(example_models ${ARQ_INCLUDE} ${ARQ_SRC}
        src/examples/models/main.cpp
        src/examples/models/game_assets.cpp
        src/examples/models/game_assets.h
        src/examples/models/tit.cpp
        src/examples/models/tit.h
        src/examples/models/game_scene.cpp
        src/examples/models/game_scene.h
        src/examples/models/floor.cpp
        src/examples/models/floor.h)
target_include_directories(example_models PUBLIC include/)
target_link_libraries(example_models PRIVATE ${ARQ_LIBRARIES})