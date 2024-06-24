#include "include/raylib.h"
#include "include/raymath.h"
#include <iostream>

using namespace std;

int main() {

  const int screenWidth = 1280;
  const int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "Pong");
  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    BeginDrawing();

    // Pong Ball
    DrawCircle(screenWidth / 2, screenHeight / 2, 20, WHITE);
    // Paddles
    DrawRectangle(10, screenHeight / 2 - (120 / 2), 25, 120, WHITE);
    DrawRectangle(screenWidth - 25 - 10, screenHeight / 2 - (120 / 2), 25, 120,
                  WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
