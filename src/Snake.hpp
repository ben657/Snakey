#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED

#include <prg_interactive.hpp>
#include "Entity.hpp"
#include "Position.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

class GameState;
class Fruit;
class SnakeController;

struct TurnPoint
{
    Position pos;
    int exitDirection;
};

class Snake:public Entity
{

public:
    Snake(int x, int y, prg::Colour c);
    ~Snake();

    void setDirection(int pDirection);
    int getDirection()
    {
        return direction;
    };

    bool hitEdge();

    void setController(SnakeController* c)
    {
        controller = c;
    };
    SnakeController* getController()
    {
        return controller;
    };

    int getLength()
    {
        return length;
    };
    void setLength(int pLength);
    void addLength(int toAdd)
    {
        setLength(length + toAdd);
    };

    void setSpeed(float pSpeed)
    {
        speed = pSpeed;
    };

    int getPartCount()
    {
        return bodyParts.size();
    };
    Rect getPart(int index)
    {
        return bodyParts[index];
    };
    Rect getHeadRect();

    bool collides(Fruit* pFruit);
    bool collides(Snake* snake);
    bool collides(Position pos);
    bool collidesSelf();
    void update();

    void draw(prg::Canvas& canvas);

private:
    GameState* gs;
    SnakeController* controller;
    std::vector<TurnPoint> turnPoints;
    std::vector<Rect> bodyParts;

    prg::Colour colour;
    int sinceTurn = 0;
    int direction = 0;
    int length = 20;
    int maxLength;
    int width = 10;
    float speed = 3;

    bool colorRising = false;

};

class SnakeController
{
public:
    SnakeController(Snake& snake):s(snake) {};
    virtual void update() {};
    virtual void fruitEaten(Fruit* eaten) {};
    virtual int directionChange(int newDir){ return newDir; };

    std::string getTag()
    {
        return tag;
    };
    void setTag(std::string pTag)
    {
        tag = pTag;
    };

protected:
    std::string tag = "";
    Snake& s;

};

class PlayerController:public SnakeController, public prg::IKeyEvent
{

public:
    PlayerController(Snake& snake);
    bool onKey(const prg::IKeyEvent::KeyEvent &e);

};

class AIController:public SnakeController
{
public:
    AIController(Snake& snake, GameState& gameState);
    void update();
    void fruitEaten(Fruit* eaten);
    int directionChange(int newDir);

private:
    GameState& gs;
    Fruit* targetFruit;
    void newTarget();
    void turnTowards(int direction);

};

#endif // SNAKE_HPP_INCLUDED
