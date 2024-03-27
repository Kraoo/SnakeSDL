# Snake Game with SDL

## Overview
This is just a simple snake game with SDL. It doesn't work very well, but I'm mainly happy to have SDL working. So, there are issues. Feel free to do whatever you want with this project. I will probably never come back to it.

## Installation
To run the Snake Game, you need to have SDL installed on your system. You can install SDL by following the instructions on the [SDL website](https://www.libsdl.org/download-2.0.php).

Once SDL is installed, you can compile the code using a C++ compiler that supports C++11 or later standards. For example, you can compile the code using g++ with the following command:

```
g++ -o snake_game snake_game.cpp -lSDL2
```

## How to Run
After compiling the code, you can run the Snake Game executable. Upon running the game, a window will open displaying the game interface. Use the arrow keys or the WASD keys to control the movement of the snake. The objective is to eat the food (red blocks) to grow the snake's length without colliding with the boundaries of the window or with the snake itself.

## Code Structure
- `snake_game.cpp`: Contains the source code for the Snake Game.
- `SDL.h`: SDL library header file.
- `std::deque`: Standard template library for implementing the snake's body.
- `std::random`: Standard template library for generating random numbers.
