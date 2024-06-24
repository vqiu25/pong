#include "include/raylib.h"
#include "include/raymath.h"
#include <iostream>

using namespace std;

// Global variables
int playerScore = 0;
int cpuScore = 0;

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

  void draw() { DrawCircle(x, y, radius, WHITE); }

  void update() {
    x += speedX;
    y += speedY;

    // If the coordinates of the ball reach the very top, or bottom.
    // If the coordinates of the ball reach the very left, or right.
    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speedY *= -1;
    }

    // Update Scores
    if (x + radius >= GetScreenWidth()) {
      cpuScore++;
      resetBall();
    }

    if (x - radius <= 0) {
      playerScore++;
      resetBall();
    }
  }

  void resetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speedChoices[2] = {-1, 1};
    speedX *= speedChoices[GetRandomValue(0, 1)];
    speedY *= speedChoices[GetRandomValue(0, 1)];
  }

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
};

class Paddle {
private:
  float x, y;
  float width, height;
  int speed;

protected:
  void limitMovement() {
    // If the paddle goes beyond the screen
    if (y <= 0) {
      y = 0;
    }

    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
  }

public:
  Paddle(float initX, float initY, float initWidth, float initHeight,
         int initSpeed)
      : x(initX), y(initY), width(initWidth), height(initHeight),
        speed(initSpeed) {}

  void draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 100, 0, WHITE);
  }

  void update() {

    // If up and or bottom arrow key is pressed
    if (IsKeyDown(KEY_UP)) {
      y -= speed;
    }

    if (IsKeyDown(KEY_DOWN)) {
      y += speed;
    }

    limitMovement();
  }

  // Getters
  float getX() const { return x; }
  float getY() const { return y; }
  float getWidth() const { return width; }
  float getHeight() const { return height; }
  int getSpeed() const { return speed; }

  // Setters
  void setX(float newX) { x = newX; }
  void setY(float newY) { y = newY; }
};

class CpuPaddle : public Paddle {
public:
  // Use the same constructor as the super class
  using Paddle::Paddle;

  void update(int ballY) {
    if (getY() + getHeight() / 2 > ballY) {
      setY(getY() - getSpeed());
    }

    if (getY() + getHeight() / 2 <= ballY) {
      setY(getY() + getSpeed());
    }

    limitMovement();
  }
};

int main() {
  const int screenWidth = 1280;
  const int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "Pong");
  SetTargetFPS(60);

  Ball ball(screenWidth / 2, screenHeight / 2, 7, 7, 20);
  Paddle player(screenWidth - 25 - 10, screenHeight / 2 - 120 / 2, 25, 120, 6);
  CpuPaddle cpu(10, screenHeight / 2 - 120 / 2, 25, 120, 6);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Check for collisions
    if (CheckCollisionCircleRec(
            Vector2{ball.getX(), ball.getY()}, ball.getRadius(),
            Rectangle{player.getX(), player.getY(), player.getWidth(),
                      player.getHeight()})) {
      // If a collision occurs with the user paddle, we reverse the direction of
      // the ball
      ball.setSpeedX(ball.getSpeedX() * -1);
    }

    if (CheckCollisionCircleRec(Vector2{ball.getX(), ball.getY()},
                                ball.getRadius(),
                                Rectangle{cpu.getX(), cpu.getY(),
                                          cpu.getWidth(), cpu.getHeight()})) {
      // If a collision occurs with the cpu paddle, we reverse the direction of
      // the ball
      ball.setSpeedX(ball.getSpeedX() * -1);
    }

    // Centre Line
    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
    // Ball operations
    ball.draw();
    ball.update();
    // Paddles
    player.draw();
    player.update();
    cpu.draw();
    cpu.update(ball.getY());
    DrawText(TextFormat("%i", cpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20, 80,
             WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
