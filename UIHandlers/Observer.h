#ifndef OBSERVER_H
#define OBSERVER_H


class Observer
{
public:
    Observer();
    virtual void render() = 0;
    virtual void gameOver() = 0;
    virtual ~Observer();
};

#endif // OBSERVER_H
