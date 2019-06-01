#include "button.h"
#include "game.h"
#include "matrix.h"

#include <Arduino.h>

Game game;
Button<A4> next;
Button<A5> drop;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  for (byte i = 2; i <= 13; i++)
    pinMode(i, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  next.init();
  drop.init();
}

void loop()
{
  next.update();
  if (next.pressed())
  {
    game.next();
  }
  drop.update();
  if (drop.pressed())
  {
    game.drop();
  }
  game.update();
  byte matrix[8] = {0};
  game.draw(matrix);
  drawScreen(matrix);
}
