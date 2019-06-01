#include <Arduino.h>

template <byte P>
class Button
{
public:
    Button()
    {
    }

    void init() const
    {
        pinMode(P, INPUT);
    }

    void update()
    {
        if (digitalRead(P))
        {
            if (state == Up)
            {
                state = Pressed;
            }
            else
            {
                state = Down;
            }
        }
        else
        {
            state = Up;
        }
    }

    bool pressed() const
    {
        return state == Pressed;
    }

private:
    enum
    {
        Up,
        Pressed,
        Down
    } state;
};
