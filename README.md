# Arqanore
## About
Arqanore is a 2D OpenGL game library written in C++ for Windows and Linux desktop.

## Requirements
### 3rd party libs
Arqanore uses GLFW for window and input handling, FreeType for fonts and SoLoud for audio. I created a fork of GLFW and FreeType which I highly recommend you use as Arqanore is being built and tested with those. 

For soloud however I created a wrapper with only the stuff I needed as that was easier to build and maintain. You can find the urls to my forks below.

* [GLFW](https://gitlab.com/arqanore/glfw)

* [FreeType](https://gitlab.com/arqanore/freetype)

* [SoloudW](https://gitlab.com/arqanore/soloudw)

## Building
### Linux
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Windows
> I use MinGW as compiler on Windows. You can pull the latest version from [winlibs](https://winlibs.com/).

```
mkdir build
cd build
cmake -S .. -G "MinGW Makefiles"
cmake --build .
``` 

## Examples
* [Basic Window](./src/examples/window/main.cpp)
* [Sprites](./src/examples/sprites/main.cpp)
* [Polygons](./src/examples/polygons/main.cpp)
* [Shaders](./src/examples/shaders/main.cpp)
* [Fonts](./src/examples/fonts/main.cpp)