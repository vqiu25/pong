#include "include/raylib.h"
#include "include/raymath.h"
#include <iostream>

using namespace std;

class Ball {
private:
  float x, y;
  int speedX, speedY;
  int radius;

public:
  // Constructor to initialise the ball properties
  Ball(float initX, float initY, int initSpeedX, int initSpeedY, int initRadius)
      : x(initX), y(initY), speedX(initSpeedX), speedY(initSpeedY),
        radius(initRadius) {}

  // Getters
  float getX() const { return x; }
  float getY() const { return y; }
  int getSpeedX() const { return speedX; }
  int getSpeedY() const { return speedY; }
  int getRadius() const { return radius; }

  // Setters
  void setX(float newX) { x = newX; }
  void setY(float newY) { y = newY; }
  void setSpeedX(int newSpeedX) { speedX = newSpeedX; }
  void setSpeedY(int newSpeedY) { speedY = newSpeedY; }
  void setRadius(int newRadius) { radius = newRadius; }

  void draw() { DrawCircle(x, y, radius, WHITE); }

  void update() {
    x += speedX;
    y += speedY;

    // If the coordinates of the ball reach the very top, or bottom.
    // If the coordinates of the ball reach the very left, or right.
    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speedY *= -1;
    }

    if (x + radius >= GetScreenWidth() || x - radius <= 0) {
      speedX *= -1;
    }
  }
};

class Paddle {
private:
  float x, y;
  float width, height;
  int speed;

public:
  Paddle(float initX, float initY, float initWidth, float initHeight,
         int initSpeed)
      : x(initX), y(initY), width(initWidth), height(initHeight),
        speed(initSpeed) {}

  void draw() { DrawRectangle(x, y, width, height, WHITE); }

  void update() {

    // If up and or bottom arrow key is pressed
    if (IsKeyDown(KEY_UP)) {
      y -= speed;
    }

    if (IsKeyDown(KEY_DOWN)) {
      y += speed;
    }

    // If the paddle goes beyond the screen
    if (y <= 0) {
      y = 0;
    }

    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
  }
};

int main() {
  const int screenWidth = 1280;
  const int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "Pong");
  SetTargetFPS(60);

  Ball ball(screenWidth / 2, screenHeight / 2, 7, 7, 20);
  Paddle player(screenWidth - 25 - 10, screenHeight / 2 - 120 / 2, 25, 120, 6);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Centre Line
    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
    // Ball operations
    ball.draw();
    ball.update();
    // Paddles
    DrawRectangle(10, screenHeight / 2 - 60, 25, 120, WHITE);
    player.draw();
    player.update();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
