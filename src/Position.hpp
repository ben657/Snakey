#ifndef POSITION_HPP_INCLUDED
#define POSITION_HPP_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

class Position{

public:
    Position(float pX = 0, float pY = 0):x(pX),y(pY){};

    float getX() const { return x; };
    float getY() const { return y; };

    void setX(float pX){ x = pX; };
    void setY(float pY){ y = pY; };

    void set(float pX, float pY){
        x = pX;
        y = pY;
    };

    int distance(Position other){
        int xDiff = x - other.getX();
        int yDiff = y - other.getY();
        return abs(sqrt((xDiff * xDiff) + (yDiff * yDiff)));
    };

private:
    float x;
    float y;

};

class Rect{

public:
    Rect(int x, int y, int pWidth, int pHeight);
    Rect(Position position, int pWidth, int pHeight);
    Rect(Position p1, Position p2);
    bool collides(Position other);
    bool collides(Rect other);

    Position getPos(){ return pos; };
    int getWidth(){ return width; };
    int getHeight(){ return height; };

    Position getMidPoint();

private:
    Position pos;
    int width = 0;
    int height = 0;
};

#endif // POSITION_HPP_INCLUDED
