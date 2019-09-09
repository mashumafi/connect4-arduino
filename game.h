#include "board.h"
#include "timer.h"

#include <Arduino.h>

class Game
{
  Board board;
  int selection;
  Piece nextPiece;
  BoolTimer<300> blackTimer;

public:
  Game()
  {
    reset();
    Serial.println(board.getBestMove(Black));
  }
  void reset()
  {
    selection = 0;
    nextPiece = Red;
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
    Serial.println(board.getBestMove(Black));
  }
  void update()
  {
    Piece winner = board.getWinner();
    if (winner != Empty)
    {
      reset();
    }
    blackTimer.update();
  }
  void draw(byte output[8]) const
  {
    bitWrite(output[0], selection, nextPiece.draw(blackTimer));
    board.draw(output, blackTimer);
  }
};
