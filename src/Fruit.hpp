#ifndef FRUIT_HPP_INCLUDED
#define FRUIT_HPP_INCLUDED

#include <prg_interactive.hpp>
#include "Snake.hpp"
#include "Entity.hpp"

class Fruit : public Entity{

public:
    Fruit(int x, int y);
    ~Fruit(){};
    virtual void onEaten(Snake& snake){};
    virtual int getScore(){ return 0; };

};

class Apple : public Fruit{

public:
    Apple(int x, int y);
    void onEaten(Snake& snake);
    virtual int getScore(){ return 1; };

};

class PoisonBerry : public Fruit{

public:
    PoisonBerry(int x, int y);
    void onEaten(Snake& snake);
    virtual int getScore(){ return -1; };
};

#endif // FRUIT_HPP_INCLUDED
