#ifndef CONNECT4_PIECE
#define CONNECT4_PIECE

enum Color
{
    NONE,
    RED,
    BLACK,
    BOTH
};

class Piece
{
public:
    Piece()
    {
        this->color = NONE;
    }

    Piece(Color color)
    {
        this->color = color;
    }

    Piece(const Piece &piece)
    {
        this->color = piece.color;
    }

    bool draw(bool showBlack) const
    {
        return showBlack ? color == Color::RED : color != Color::NONE;
    }

    bool operator==(const Piece &other) const
    {
        return color == other.color;
    }

    bool operator!=(const Piece &other) const
    {
        return color != other.color;
    }

    Piece opposite() const
    {
        switch (color)
        {
        case NONE:
            return Piece(BOTH);
        case RED:
            return Piece(BLACK);
        case BLACK:
            return Piece(RED);
        case BOTH:
            return Piece(NONE);
        }
    }

private:
    Color color;
};

const Piece Empty{NONE};
const Piece Red{RED};
const Piece Black{BLACK};
const Piece Draw{BOTH};

#endif
