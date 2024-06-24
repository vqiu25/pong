# Pong

<p align="center">
  <img width="400" alt="pong-logo" src="https://github.com/vqiu25/pong/assets/109129209/bf8ddada-9539-45a2-b281-8c955a2c4890">
</p>

## About
A simple implementation of Pong, using C++ and the raylib library.

## Images
<p align="center">
  <img width="450" alt="image" src="https://github.com/vqiu25/pong/assets/109129209/72be237a-e01b-44f5-898d-2fc1453e06ab">
</p>

## Compilation
Using raylib, the following command can be used to compile on MacOS:

`clang++ *.cpp -L lib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a -std=c++17 -o pong`

## Running
`./pong`
