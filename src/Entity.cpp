#include "Entity.hpp"

void Entity::update()
{

}

void Entity::loadImage(std::string filePath)
{
    prg::Image* img = new prg::Image();
    prg::ImageFile(filePath).load(*img);
    setImage(img);
}

void Entity::setImage(int width, int height, prg::Colour c)
{
    prg::Image* i = new prg::Image();
    i->resize(width,height);
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            i->setPixel(x,y,c);
        }
    }
    setImage(i);
}

void Entity::drawRect(prg::Image& canvas, Position p1, Position p2, prg::Colour c)
{
    int minX = std::min(p1.getX(), p2.getX());
    int maxX = std::max(p1.getX(), p2.getX());
    int minY = std::min(p1.getY(), p2.getY());
    int maxY = std::max(p1.getY(), p2.getY());

    for(int x = minX; x <= maxX; x++)
    {
        for(int y = minY; y <= maxY; y++)
        {
            canvas.setPixel(x,y,c);
        }
    }
}

void Entity::draw(prg::Canvas &canvas)
{
    canvas.blit(*image
                , position->getX()
                , position->getY());
}
