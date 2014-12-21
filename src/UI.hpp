#ifndef UI_HPP_INCLUDED
#define UI_HPP_INCLUDED

#include <prg_interactive.hpp>
#include <string>
#include <iostream>
#include "Position.hpp"
#include "Entity.hpp"

class Button : public Entity, prg::IMouseEvent{
public:
    Button(Rect box, std::string text, prg::Colour bgColour, prg::Colour txtColour);
    ~Button();

    bool isPressed(){ return pressed; };
    bool isJustPressed(){ return (pressed == true && lastFramePressed == false); };

    void update();
    void draw(prg::Canvas& canvas);

    virtual bool onMotion(const prg::IMouseEvent::MouseEvent& e);
    virtual bool onButton(const prg::IMouseEvent::MouseEvent& e);

private:
    prg::Colour bgCol;
    prg::Colour txtCol;
    std::string txt;

    Position txtOffset;
    Position txtOffsetPressed;

    bool lastFramePressed = false;
    bool pressed = false;

    Rect hitBox;
};

#endif // UI_HPP_INCLUDED
