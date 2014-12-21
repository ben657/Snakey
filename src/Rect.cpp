#include "Position.hpp"

Rect::Rect(int x, int y, int pWidth, int pHeight):pos(Position(x,y)),width(pWidth),height(pHeight){

}

Rect::Rect(Position position, int pWidth, int pHeight):pos(position),width(pWidth),height(pHeight){

}

Rect::Rect(Position p1, Position p2){
    int minX = std::min(p1.getX(), p2.getX());
    int maxX = std::max(p1.getX(), p2.getX());
    int minY = std::min(p1.getY(), p2.getY());
    int maxY = std::max(p1.getY(), p2.getY());
    pos = Position(minX,minY);
    width = maxX - minX;
    height = maxY - minY;
}

Position Rect::getMidPoint(){
    int midX = pos.getX() + width/2;
    int midY = pos.getY() + height/2;
    return Position(midX,midY);
}

bool Rect::collides(Position other){
    if(other.getX() > pos.getX() &&
       other.getX() < pos.getX() + width &&
       other.getY() > pos.getY() &&
       other.getY() < pos.getY() + height){

        return true;
    }
    return false;
}

bool Rect::collides(Rect other){
    Position otherPos = other.getPos();
    if(otherPos.getX() < pos.getX() + width &&
       otherPos.getX() + other.getWidth() > pos.getX() &&
       otherPos.getY() < pos.getY() + height &&
       otherPos.getY() + other.getHeight() > pos.getY()){

        return true;
    }
    return false;
}
