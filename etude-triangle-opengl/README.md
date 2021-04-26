# etude-triangle-opengl

This is a replica of `etude-triangle-cpu` except that it is written in openGL.

Although it is a replica, the logic varies a lot because of the characteristics of openGL.

The main code is in `etude-triangle-cuda/main.cc` , which is referred to [this](https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/1.getting_started/3.2.shaders_interpolation/shaders_interpolation.cpp).

## Testing Environment:

- Microsoft Windows 10, 19042.928
- Intel(R) Xeon(R) CPU E3-1505M v5 @ 2.80GHz
- 16GBs of RAM, running at 2133 MHz
- NVIDIA Quadro M1000M
- `gcc.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0`
- `g++ --std=c++11 -Ietude-triangle-opengl -Letude-triangle-opengl/lib-static-ucrt-x64 etude-triangle-opengl/main.cc etude-triangle-opengl/glad.c -lglfw3dll -o main`

## Testing Result:

```
duration: 0.0000000ms
```