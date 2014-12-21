#include "Snake.hpp"
#include "GameState.hpp"
#include "Fruit.hpp"
#include <iostream>

//{ Base Snake
Snake::Snake(int x, int y, prg::Colour c): colour(c), maxLength(length){
    position->set(x,y);
    turnPoints.push_back(TurnPoint{*position,direction});
    Rect initBody(*position, width, width);
    bodyParts.push_back(initBody);
}

Snake::~Snake(){

}

void Snake::setLength(int pLength){
    length = pLength;
}

void Snake::setDirection(int pDirection){
    if(pDirection == direction){
        return;
    }
    switch(pDirection){
    case 0:
        if(direction == 2){ return; }
        break;
    case 1:
        if(direction == 3){ return; }
        break;
    case 2:
        if(direction == 0){ return; }
        break;
    case 3:
        if(direction == 1){ return; }
        break;
    }
    if(sinceTurn > 11){
        direction = controller->directionChange(pDirection);
        turnPoints.push_back(TurnPoint{*position,pDirection});
        sinceTurn = 0;
    }
}

Rect Snake::getHeadRect(){
    Position pos = *position;
    pos.set(pos.getX() - (width/2), pos.getY() - (width/2));
    return Rect(pos,width,width);
}

bool Snake::collides(Fruit* pFruit){
    return getHeadRect().collides(pFruit->getRect());
}

bool Snake::collides(Snake* snake){
    for(int i = 0; i < snake->getPartCount(); i++){
        if(snake->getPart(i).collides(getHeadRect())){
            return true;
        }
    }
    return false;
}

bool Snake::collidesSelf(){
    for(int i = 2; i < bodyParts.size(); i++){
        if(bodyParts[i].collides(getHeadRect())){
            return true;
        }
    }
    return false;
}

bool Snake::collides(Position pos){
    for(int i = 0; i < bodyParts.size(); i++){
        if(bodyParts[i].collides(pos)){
            return true;
        }
    }
    return false;
}

bool Snake::hitEdge(){
    if(position->getY() + (width/2) > prg::application.getScreenHeight() ||
        position->getX() + (width/2) > prg::application.getScreenWidth() ||
        position->getY() - (width/2) < 100 ||
        position->getX() - (width/2) < 0){
        return true;
    }
    return false;
}

void Snake::update(){

    controller->update();
    switch(direction){
    case 0:
        position->setY(position->getY() + speed);
        break;
    case 1:
        position->setX(position->getX() + speed);
        break;
    case 2:
        position->setY(position->getY() - speed);
        break;
    case 3:
        position->setX(position->getX() - speed);
        break;
    }
    sinceTurn += speed;
}

void Snake::draw(prg::Canvas& canvas){
    colour = prg::Colour(rand() % 254,rand() % 254,rand() % 254);
    bodyParts.clear();
    TurnPoint from{*position,direction};
    TurnPoint to;
    int cLength = 0;
    for(int i = turnPoints.size()-1; i >= 0; i--){
        to = turnPoints[i];
        Position toPos = to.pos;
        cLength += from.pos.distance(to.pos);

        bool isEnd = false;
        if(cLength > length){
            isEnd = true;
            int amountLess = cLength - length;
            switch(to.exitDirection){
            case 0:
                toPos.setY(toPos.getY() + amountLess);
                break;
            case 1:
                toPos.setX(toPos.getX() + amountLess);
                break;
            case 2:
                toPos.setY(toPos.getY() - amountLess);
                break;
            case 3:
                toPos.setX(toPos.getX() - amountLess);
                break;
            }
        }

        switch(to.exitDirection){
        case 0:
            toPos.set(toPos.getX() - (width/2), toPos.getY() - (width/2));
            from.pos.set(from.pos.getX() + (width/2), from.pos.getY() + (width/2));
            break;
        case 2:
            toPos.set(toPos.getX() - (width/2), toPos.getY() + (width/2));
            from.pos.set(from.pos.getX() + (width/2), from.pos.getY() - (width/2));
            break;
        case 1:
            toPos.set(toPos.getX() - (width/2), toPos.getY() + (width/2));
            from.pos.set(from.pos.getX() + (width/2), from.pos.getY() - (width/2));
            break;
        case 3:
            toPos.set(toPos.getX() + (width/2), toPos.getY() + (width/2));
            from.pos.set(from.pos.getX() - (width/2), from.pos.getY() - (width/2));
            break;
        }

        drawRect(canvas, from.pos, toPos, colour);
        bodyParts.push_back(Rect(from.pos, toPos));
        if(isEnd){ return; };
        from = to;
    }
}
//}

//{ Player Controller
PlayerController::PlayerController(Snake& snake):SnakeController(snake){
    setTag("Player");
    prg::application.addKeyListener(*this);
}

bool PlayerController::onKey(const prg::IKeyEvent::KeyEvent &e){
    if(e.key_state == KeyEvent::KB_UP){
        return true;
    }

    Position nextPos = s.getPosition();
    int newDir = -1;
    switch(e.key){
    case KeyEvent::KB_UP_KEY:
        newDir = 0;
        nextPos.setY(nextPos.getY() + 20);
        break;
    case KeyEvent::KB_RIGHT_KEY:
        newDir = 1;
        break;
    case KeyEvent::KB_DOWN_KEY:
        newDir = 2;
        break;
    case KeyEvent::KB_LEFT_KEY:
        newDir = 3;
        break;
    case KeyEvent::KB_SPC_KEY:
        prg::application.setState("PauseState");
        break;
    case KeyEvent::KB_ESC_KEY:
        prg::application.exit();
        break;
    default:
        return true;
        break;
    }
    if(newDir > -1)
        s.setDirection(newDir);
    return true;
}
//}

//{ AI Controller
AIController::AIController(Snake& snake,GameState& gameState):SnakeController(snake),gs(gameState){
    setTag("AI");
    s.setSpeed(2.75);
    newTarget();
}

int AIController::directionChange(int newDir){

    Position newPos = s.getPosition();
    switch(newDir){
    case 0:
        newPos.setY(newPos.getY() + 7);
        break;
    case 1:
        newPos.setX(newPos.getX() + 7);
        break;
    case 2:
        newPos.setY(newPos.getY() - 7);
        break;
    case 3:
        newPos.setX(newPos.getX() - 7);
        break;
    }
    if(s.collides(newPos)){
        int random = rand() % 2;
        if(random == 0)
            return newDir + 1;
        else
            return newDir - 1;
    }
    return newDir;
}

void AIController::newTarget(){
    int index = 0;
    if(gs.getFruitCount() > 0) {index = rand() % (gs.getFruitCount()); }
    targetFruit = gs.getFruit(index);
}

void AIController::fruitEaten(Fruit* eaten){
    if(targetFruit == eaten){
        newTarget();
    }
}

void AIController::turnTowards(int direction){
    int newDir = direction;
    int random  = rand() % 2;
    random = 0;

    switch(s.getDirection()){
    case 0:
        if(direction == 2){
            if(random == 0){ newDir = 3; }
            else if(random == 1){ newDir = 1; }
        }
        break;
    case 1:
        if(direction == 3){
            if(random == 0){ newDir = 0; }
            else if(random == 1){ newDir = 2; }
        }
        break;
    case 2:
        if(direction == 0){
            if(random == 0){ newDir = 1; }
            else if(random == 1){ newDir = 3; }
        }
        break;
    case 3:
        if(direction == 1){
            if(random == 0){ newDir = 2; }
            else if(random == 1){ newDir = 0; }
        }
        break;
    }
    s.setDirection(newDir);
}

void AIController::update(){

    Position pos = s.getPosition();
    Position targetPos = targetFruit->getPosition();
    if(pos.getX() < targetPos.getX()){
        turnTowards(1);
    }
    else if(pos.getX() > targetPos.getX() + targetFruit->getWidth()){
        turnTowards(3);
    }
    if(pos.getY() < targetPos.getY()){
        turnTowards(0);
    }
    else if(pos.getY() > targetPos.getY() + targetFruit->getHeight()){
        turnTowards(2);
    }

}
//}

