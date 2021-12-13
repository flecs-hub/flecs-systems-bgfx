![Flecs App](img.png)

# Flecs Systems BGFX

This is a sample app of a working bgfx + imgui system with flecs v2. It requires some of the flecs modules to run such as
[gui](https://github.com/flecs-hub/flecs-components-gui), [input](https://github.com/flecs-hub/flecs-components-input), and [sdl2](https://github.com/flecs-hub/flecs-systems-sdl2).
To manage BGFX with C it uses [bgfx.cmake](https://github.com/bkaradzic/bgfx.cmake)

# Requirements

This branch requires CMake installed with a working compiler. Also make sure you have SDL installed in your compiler. This was tested on Linux and Windows (**mingw64** with **gcc** compiler).

If you are using msys64 you can simply get SDL with
```
pacman -S mingw-w64-x86_64-SDL2
```

The rest of the dependencies: **bgfx.cmake**, **cimgui**, **flecs** and **flecs modules** are included within the repo.

## License
[MIT](https://choosealicense.com/licenses/mit/)
