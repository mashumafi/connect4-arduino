#include "piece.h"

#include <Arduino.h>

class Board
{
public:
    void reset()
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                board[x][y] = None;
            }
        }
    }

    int next(int selection)
    {
        return selection % width + 1;
    }

    void drop(int &selection, Piece &piece)
    {
        if (selection > 0)
        {
            int slot = selection - 1;
            if (board[slot][0] != None)
            {
                Serial.println("Column full.");
                return;
            }
            int y = 1;
            for (; y < height; y++)
            {
                if (board[slot][y] != None)
                {
                    break;
                }
            }
            board[slot][y - 1] = piece;
            if (piece == Red)
            {
                piece = Black;
            }
            else if (piece == Black)
            {
                piece = Red;
            }
            Serial.println("Dropped.");
            selection = 0;
        }
    }

    void draw(byte output[8], bool showBlack) const
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                bitWrite(output[y + 2], x + 1, board[x][y].draw(showBlack));
            }
        }
    }

private:
    static const int width = 7;
    static const int height = 6;
    Piece board[width][height];
};
