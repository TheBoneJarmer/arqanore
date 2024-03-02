# Arqanore
## About
Arqanore is a 2D and 3D OpenGL game library written in C++ for Windows and Linux desktop.

## Requirements
### 3rd party libs
Arqanore uses GLFW for window and input handling, FreeType for fonts and SoLoud for audio. I created a fork of every dependency which I highly recommend you use since Arqanore is being built and tested with those. For soloud I created a wrapper with only the stuff I needed as that was easier to build and maintain. You can find the urls to my forks below.

* [GLFW](https://github.com/thebonejarmer/glfw)
* [FreeType](https://github.com/thebonejarmer/freetype)
* [SoloudW](https://github.com/thebonejarmer/soloudw)

## Building
### Linux
```
mkdir build
cd build
cmake -S .. -DBUILD_SHARED_LIBS=ON
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
* [Fonts](./src/examples/fonts/main.cpp)

## Contributing
At this moment I do not accept pull requests from anyone but contributors until I release the first major version. You can however open up issues or ask questions in the discussions forum.

## License
[MIT](./LICENSE)
