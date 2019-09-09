#ifndef CONNECT4_BOARD
#define CONNECT4_BOARD

#include "piece.h"

#include <Arduino.h>

class Board
{
public:
    void reset()
    {
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                board[x][y] = Empty;
            }
        }
    }

    int next(int selection)
    {
        return selection % WIDTH + 1;
    }

    void drop(int &selection, Piece &piece)
    {
        if (selection > 0)
        {
            int column = selection - 1;
            int y = getDropHeight(column);
            if (y == -1)
            {
                Serial.println("Column full!");
            }
            else
            {
                board[column][y] = piece;
                piece = piece.opposite();
                selection = 0;
                Serial.println("Dropped!");
            }
        }
    }

    void draw(byte output[8], bool showBlack) const
    {
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                bitWrite(output[y + 2], x + 1, board[x][y].draw(showBlack));
            }
        }
    }

    bool check4(int sx, int sy, int dx, int dy) const
    {
        for (int i = 1; i <= 3; i++)
        {
            int nx = sx + i * dx, ny = sy + i * dy;
            if (WIDTH <= nx)
                return false;
            if (ny < 0 || HEIGHT <= ny)
                return false;
            if (board[sx][sy] != board[nx][ny])
                return false;
        }
        return true;
    }

    Piece getWinner() const
    {
        int pieceCount = 0;
        for (int x = 0; x < WIDTH; x++)
        {
            for (int y = 0; y < HEIGHT; y++)
            {
                if (board[x][y] != Empty)
                {
                    pieceCount++;

                    bool hasWinner = false;
                    // horizontal
                    hasWinner |= check4(x, y, 1, 0);
                    // vertical
                    hasWinner |= check4(x, y, 0, 1);
                    // up-diagonal
                    hasWinner |= check4(x, y, 1, -1);
                    // down-diagonal
                    hasWinner |= check4(x, y, 1, 1);

                    if (hasWinner)
                        return board[x][y];
                }
            }
        }
        // is the board full
        if (pieceCount == WIDTH * HEIGHT)
            return Draw;
        return Empty;
    }

    // get the row the peice will fall into
    int getDropHeight(int column)
    {
        for (int y = 0; y < HEIGHT; y++)
            if (board[column][y] != Empty)
                return y - 1;
        return HEIGHT - 1;
    }

    int PlayOut = 0;
    int EVA = 0;

    int getBestMove(const Piece piece)
    {
        float chance[2] = {9999999, 0};
        for (int column = 0; column < WIDTH; column++)
        {
            PlayOut = 0;
            EVA = 0;
            int PlayNumber = getDropHeight(column);
            if (PlayNumber != -1)
            {
                board[column][PlayNumber] = piece;
                if (getWinner() == Draw)
                {
                    board[column][PlayNumber] = Empty;
                    return PlayNumber;
                }
                float temp = -(100 * NegaMax(1, piece));
                if (PlayOut != 0)
                    temp -= ((100 * EVA) / PlayOut);
                //if(-temp >= 100)
                //provocation = true;
                if (chance[0] > temp)
                {
                    chance[0] = temp;
                    chance[1] = column;
                }
                board[column][PlayNumber] = Empty;
            }
        }
        return chance[1];
    }

    int NegaMax(int Depth, const Piece piece)
    {
        Piece RB = piece;
        int PlayNumber[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // The values of the input[] for every column
        int chance = 0;
        if (Depth % 2 != 0)
            RB = piece.opposite();
        for (int column = 0; column < WIDTH; column++)
            PlayNumber[column] = getDropHeight(column);
        for (int column = 0; column < WIDTH; column++)
        {
            if (PlayNumber[column] != -1)
            {
                board[column][PlayNumber[column]] = RB;
                if (getWinner() != Empty)
                {
                    PlayOut++;
                    if (RB == piece)
                        EVA++;
                    else
                        EVA--;
                    board[column][PlayNumber[column]] = Empty;
                    return -1;
                }
                board[column][PlayNumber[column]] = Empty;
            }
        }
        if (Depth <= 3)
        {
            for (int column = 0; column < WIDTH; column++)
            {
                int temp = 0;
                if (PlayNumber[column] != 0)
                {
                    board[column][PlayNumber[column]] = RB;
                    if (getWinner() != Empty)
                    {
                        PlayOut++;
                        if (RB == piece)
                            EVA++;
                        else
                            EVA--;
                        board[column][PlayNumber[column]] = Empty;
                        return -1;
                    }
                    temp = NegaMax(Depth + 1, piece);
                    if (column == 1)
                        chance = temp;
                    if (chance < temp)
                        chance = temp;
                    board[column][PlayNumber[column]] = Empty;
                }
            }
        }
        return -chance;
    }

private:
    static const int WIDTH = 7;
    static const int HEIGHT = 6;
    Piece board[WIDTH][HEIGHT];
};

#endif
