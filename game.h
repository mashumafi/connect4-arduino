#include "board.h"

#include <Arduino.h>

class Game
{
  Board board;
  int selection;
  Piece nextPiece;
  unsigned long blackTimer;

public:
  Game()
  {
    reset();
  }
  void reset()
  {
    selection = 0;
    nextPiece = Red;
    blackTimer = millis();
    board.reset();
  }
  void next()
  {
    selection = board.next(selection);
    Serial.println(selection);
  }
  void drop()
  {
    board.drop(selection, nextPiece);
  }
  void update()
  {
    int diff = millis() - blackTimer;
    if (diff >= 600)
      blackTimer = millis();
  }
  void draw(byte output[8]) const
  {
    int diff = millis() - blackTimer;
    bool showBlack = diff < 300;
    bitWrite(output[0], selection, nextPiece.draw(showBlack));
    board.draw(output, showBlack);
  }
};
