#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <prg_interactive.hpp>
#include "Position.hpp"
#include <string>

class Entity{

public:
    Entity(Position* pPosition = new Position()):position(pPosition){};

    virtual void update();
    virtual void draw(prg::Canvas &canvas);

    void setImage(prg::Image* pImage){
        image = pImage;
        width = image->getWidth();
        height = image->getHeight();
    };
    void setImage(int width, int height, prg::Colour c);

    void loadImage(std::string filePath);

    void drawRect(prg::Image& canvas, Position p1, Position p2, prg::Colour c);

    int getWidth(){ return width; };
    int getHeight(){ return height; };
    Rect getRect(){ return Rect(*position, width, height); };

    const Position getPosition(){ return *position; };
    void setPosition(Position p){ position = &p; };
    void setX(int x){ position->setX(x); };
    void setY(int y){ position->setY(y); };

protected:
    int width = 0;
    int height = 0;
    prg::Image* image = nullptr;
    Position* position;

};

#endif // ENTITY_HPP_INCLUDED
