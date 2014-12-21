#include "Fruit.hpp"

Fruit::Fruit(int x, int y):Entity(new Position(x,y)){}

Apple::Apple(int x, int y):Fruit(x,y){
    setImage(15,15,prg::Colour::GREEN);
}

void Apple::onEaten(Snake& snake){
    snake.addLength(10);
}

PoisonBerry::PoisonBerry(int x, int y):Fruit(x,y){
    setImage(15,15,prg::Colour::BLUE);
}

void PoisonBerry::onEaten(Snake& snake){
    snake.addLength(-10);
}
