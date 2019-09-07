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

private:
    Color color;
};

const Piece Empty{NONE};
const Piece Red{RED};
const Piece Black{BLACK};
const Piece Draw{BOTH};
