#ifndef CONNECT4_TIMER
#define CONNECT4_TIMER

template <unsigned long INTERVAL>
class Timer
{
public:
    Timer()
    {
        m_millis = millis();
    }

    void update()
    {
        unsigned long time = millis();
        if (time - m_millis >= INTERVAL)
        {
            increment();
            m_millis = time;
        }
    }

private:
    virtual void increment() = 0;
    unsigned long m_millis;
};

template <unsigned long INTERVAL>
class BoolTimer : public Timer<INTERVAL>
{
public:
    BoolTimer(bool initial = false)
    {
        value = initial;
    }

    operator bool() const
    {
        return value;
    }

private:
    virtual void increment()
    {
        value = !value;
    }
    bool value;
};

template <unsigned long INTERVAL, typename TYPE, TYPE MIN, TYPE MAX>
class IntTimer : public Timer<INTERVAL>
{
public:
    IntTimer(TYPE initial = MIN)
    {
        value = initial;
    }

private:
    virtual void increment()
    {
    }
    TYPE value;
};

#endif