#include "UI.hpp"

Button::Button(Rect box, std::string text, prg::Colour bgColour, prg::Colour txtColour):
    hitBox(box), Entity(new Position(box.getPos().getX(),box.getPos().getY())),
    txt(text), bgCol(bgColour), txtCol(txtColour)
{
    setImage(box.getWidth(),box.getHeight(), bgCol);

    prg::application.addMouseListener(*this);

    prg::uint txtSize[2];
    prg::Font::SMALL.computePrintDimensions(txtSize, txt);
    txtOffset.set((getWidth()/2) - (txtSize[0]/2), (getHeight()/2) - (txtSize[1]/2));
    txtOffsetPressed = txtOffset;
    txtOffsetPressed.set(txtOffsetPressed.getX() - 5, txtOffsetPressed.getY() - 5);
}

Button::~Button()
{
    prg::application.removeMouseListener(*this);
}

bool Button::onMotion(const prg::IMouseEvent::MouseEvent& e)
{
    return true;
}

bool Button::onButton(const prg::IMouseEvent::MouseEvent& e)
{
    if(e.button == MouseEvent::LM_BTN)
    {
        if(e.button_state == MouseEvent::MB_DOWN)
        {
            if(hitBox.collides(Position(e.pos_x,e.pos_y)))
            {
                pressed = true;
            }
        }
        else if(e.button_state == MouseEvent::MB_UP)
        {
            pressed = false;
        }
    }
    return true;
}

void Button::update()
{
    lastFramePressed = pressed;
}

void Button::draw(prg::Canvas& canvas)
{
    canvas.blit(*image, position->getX(),position->getY());

    Position txtDraw = txtOffset;
    if(pressed)
        txtDraw = txtOffsetPressed;

    prg::Font::SMALL.print(canvas, position->getX() + txtDraw.getX(), position->getY() + txtDraw.getY(), txtCol, txt);
}
