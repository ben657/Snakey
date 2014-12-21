#include "GameState.hpp"

//{ Game State
bool GameState::onCreate(){
    reset();
    return true;
}

bool GameState::onDestroy(){
    return true;
}

void GameState::onEntry(){

}

void GameState::onExit(){

}

void GameState::removeFruit(int index){
    fruit.erase(fruit.begin()+index);
}

void GameState::spawnFruit(int amount){

    for(int i = 0; i < amount; i++){
        int rFruit = rand() % 10;
        int x = (rand() % (prg::application.getScreenWidth() - 10 - UIOffset)) + UIOffset;
        int y = (rand() % (prg::application.getScreenHeight() - 10 - UIOffset)) + UIOffset;
        switch(rFruit){
        case 0:
            fruit.push_back(new PoisonBerry(x,y));
            break;
        default:
            fruit.push_back(new Apple(x,y));
            break;
        }
        for(Snake* s : snakes){
            if(s->collides(fruit[fruit.size()-1])){
                removeFruit(fruit.size()-1);
                spawnFruit(1);
            }
        }
    }
}

void GameState::reset(){
    srand(time(nullptr));
    fruit.clear();
    spawnFruit(3);

    snakes.clear();
    Snake* aiS = new Snake(500,500, prg::Colour::BLUE);
    aiS->setController(new AIController(*aiS, *this));
    snakes.push_back(aiS);

    Snake* s = new Snake(200,200, prg::Colour::RED);
    s->setController(new PlayerController(*s));
    snakes.push_back(s);

    score = 0;
}

Snake* GameState::getLongest(Snake* s1, Snake* s2){
    if(s1->getLength() > s2->getLength())
        return s1;
    else if(s1->getLength() < s2->getLength())
        return s2;
    else return nullptr;
}

void GameState::onUpdate(){
    for(int i = 0; i < snakes.size(); i++){
        Snake* s = snakes[i];
        s->update();

        for(int j = 0; j < fruit.size(); j++){
            if(s->collides(fruit[j])){
                fruit[j]->onEaten(*s);
                Fruit* old = fruit[j];
                removeFruit(j);
                spawnFruit(1);
                for(Snake* s2 : snakes)
                    s2->getController()->fruitEaten(old);
                if(s->getController()->getTag() == "Player"){
                    score += old->getScore();
                }
                delete old;
            }
        }

        for(int j = 0; j < snakes.size(); j++){
            if(i != j){
                if(s->collides(snakes[j])){
                    std::string winner = snakes[j]->getController()->getTag();

                    switch(s->getDirection()){
                    case 0:
                        if(snakes[j]->getDirection() == 2){
                            Snake* winSnake = getLongest(s, snakes[j]);
                            if(winSnake == nullptr)
                                winner = "Draw";
                            else
                                winner = winSnake->getController()->getTag();
                        }
                        break;
                    case 1:
                        if(snakes[j]->getDirection() == 3){
                            Snake* winSnake = getLongest(s, snakes[j]);
                            if(winSnake == nullptr)
                                winner = "Draw";
                            else
                                winner = winSnake->getController()->getTag();
                        }
                        break;
                    case 2:
                        if(snakes[j]->getDirection() == 0){
                            Snake* winSnake = getLongest(s, snakes[j]);
                            if(winSnake == nullptr)
                                winner = "Draw";
                            else
                                winner = winSnake->getController()->getTag();
                        }
                        break;
                    case 3:
                        if(snakes[j]->getDirection() == 1){
                            Snake* winSnake = getLongest(s, snakes[j]);
                            if(winSnake == nullptr)
                                winner = "Draw";
                            else
                                winner = winSnake->getController()->getTag();
                        }
                        break;
                    }

                    hs->setData(winner, score);
                    prg::application.setState("HighScoreState");
                }
            }
        }
        if(s->hitEdge()){
            std::string winner = "Player";
            if(s->getController()->getTag() == "Player"){
                winner = "AI";
            }
            hs->setData(winner, score);
            prg::application.setState("HighScoreState");
        }

        if((s->collidesSelf() || score < 0) && s->getController()->getTag() == "Player"){
            hs->setData("AI", score);
            prg::application.setState("HighScoreState");
        }
        if(s->getLength() < 10){
            std::string winner = "Player";
            if(s->getController()->getTag() == "Player"){
                winner = "AI";
            }
            hs->setData(winner, score);
            prg::application.setState("HighScoreState");
        }
    }
}

void GameState::onRender(prg::Canvas &canvas){
    for(Snake* s : snakes){
        s->draw(canvas);
    }
    for(Fruit* f : fruit){
        f->draw(canvas);
    }

    canvas.drawLine(0,100,prg::application.getScreenWidth(), 100, prg::Colour::BLACK);

    std::stringstream scoreStr;
    scoreStr << score;
    prg::Font::SMALL.print(canvas, 100, 50, prg::Colour::BLACK, "Score: " + scoreStr.str());
}
//}

//{ Main Menu State
bool MainMenuState::onCreate(){
    return true;
}

bool MainMenuState::onDestroy(){
    return true;
}

void MainMenuState::onEntry(){
    gs->reset();

    Position playBtnPos(prg::application.getScreenWidth()/2 - 50, prg::application.getScreenHeight()/2 - 50);
    playBtn = new Button(Rect(playBtnPos, 100,50), "Play", prg::Colour::RED, prg::Colour::BLACK);

    Position exitBtnPos(playBtnPos.getX(), playBtnPos.getY() - 75);
    exitBtn = new Button(Rect(exitBtnPos, 100, 50), "Exit", prg::Colour::RED, prg::Colour::BLACK);

    prg::uint titleSize[2];
    prg::Font::LARGE.computePrintDimensions(titleSize, "SNAAAAAAaaaaakkkkeeee!!!");
    titlePos.set(prg::application.getScreenWidth()/2 - titleSize[0]/2, prg::application.getScreenHeight()/2 + 50);
}

void MainMenuState::onExit(){
    delete playBtn;
    delete exitBtn;
}

void MainMenuState::onUpdate(){
    playBtn->update();
    exitBtn->update();

    if(playBtn->isPressed()){
        prg::application.setState("GameState");
    }
    if(exitBtn->isPressed()){
        prg::application.exit();
    }
}

void MainMenuState::onRender(prg::Canvas &canvas){
    prg::Font::LARGE.print(canvas, titlePos.getX(), titlePos.getY(), prg::Colour::RED, "SNAAAAAAaaaaakkkkeeee!!!");
    playBtn->draw(canvas);
    exitBtn->draw(canvas);
}
//}

//{ Pause State
void PauseState::onEntry(){
    prg::uint pauseTxtSize[2];
    prg::Font::LARGE.computePrintDimensions(pauseTxtSize, "Paused");
    pausePos = new Position(prg::application.getScreenWidth()/2 - pauseTxtSize[0]/2, prg::application.getScreenHeight()/2);

    Position resumeBtnPos(prg::application.getScreenWidth()/2 - 50, prg::application.getScreenHeight()/2 - 100);
    resumeBtn = new Button(Rect(resumeBtnPos, 100,50), "Resume", prg::Colour::RED, prg::Colour::BLACK);

    Position endGameBtnPos(resumeBtnPos.getX(), resumeBtnPos.getY() - 75);
    endGameBtn = new Button(Rect(endGameBtnPos, 100,50), "End Game", prg::Colour::RED, prg::Colour::BLACK);

    fruit.clear();
    spawnFruit(3);

    snakes.clear();
    Snake* aiS = new Snake(300,300, prg::Colour::BLUE);
    aiS->setController(new AIController(*aiS, *this));
    snakes.push_back(aiS);
}

void PauseState::onExit(){
    delete resumeBtn;
    delete endGameBtn;
}

void PauseState::onUpdate(){
    GameState::onUpdate();
    resumeBtn->update();
    endGameBtn->update();

    if(resumeBtn->isPressed()){
        prg::application.setState("GameState");
    }
    if(endGameBtn->isPressed()){
        prg::application.setState("MainMenuState");
    }
}

void PauseState::onRender(prg::Canvas& canvas){
    for(Snake* s : snakes){
        s->draw(canvas);
    }
    for(Fruit* f : fruit){
        f->draw(canvas);
    }

    prg::Font::LARGE.print(canvas, pausePos->getX(),pausePos->getY(), prg::Colour::RED, "Paused");
    resumeBtn->draw(canvas);
    endGameBtn->draw(canvas);
}
//}

//{ High Score State

void HighScoreState::setData(std::string pWinner, int pScore){
    winner = pWinner;
    score = pScore;
}

int HighScoreState::loadScore(){
    int hScore = 0;
    std::ifstream hsFile;
    hsFile.open("highScore.dat", std::ios::binary);

    if(hsFile.is_open()){
        hsFile.read((char*)&hScore, sizeof(hScore));
    }
    hsFile.close();
    return hScore;
}

void HighScoreState::saveScore(int toSave){
    std::ofstream hsFile;
    hsFile.open("highScore.dat", std::ios::binary);

    if(hsFile.is_open()){
        hsFile.write((char*)&toSave, sizeof(toSave));
    }
    hsFile.close();
}

bool HighScoreState::onCreate(){
    return true;
}

bool HighScoreState::onDestroy(){
    return true;
}

void HighScoreState::onEntry(){
    highScore = loadScore();
    if(highScore < score){
        highScore = score;
        saveScore(highScore);
    }

    prg::uint textDims[2];
    winText = "The " + winner + " won!";
    if(winner == "Draw")
        winText = "You drew!";
    prg::Font::LARGE.computePrintDimensions(textDims, winText);
    titlePos = new Position(prg::application.getScreenWidth()/2 -textDims[0]/2, prg::application.getScreenHeight()/2 + 100);

    std::stringstream scoreStr;
    scoreStr << highScore;
    prg::Font::MEDIUM.computePrintDimensions(textDims, "High score: " + scoreStr.str());
    hsPos = new Position(prg::application.getScreenWidth()/2 -textDims[0]/2, titlePos->getY() - 50);

    std::stringstream scoreStr2;
    scoreStr2 << score;
    prg::Font::MEDIUM.computePrintDimensions(textDims, "Your score: " + scoreStr2.str());
    sPos = new Position(prg::application.getScreenWidth()/2 -textDims[0]/2, titlePos->getY() - 100);

    Position mainMenuBtnPos(prg::application.getScreenWidth()/2 - 50, titlePos->getY() - 200);
    mainMenuBtn = new Button(Rect(mainMenuBtnPos, 100,50), "Main Menu", prg::Colour::RED, prg::Colour::BLACK);
}

void HighScoreState::onExit(){

}

void HighScoreState::onUpdate(){
    mainMenuBtn->update();
    if(mainMenuBtn->isPressed()){
        prg::application.setState("MainMenuState");
    }
}

void HighScoreState::onRender(prg::Canvas &canvas){
    prg::Colour printCol = prg::Colour::BLACK;
    prg::Font::LARGE.print(canvas, titlePos->getX(), titlePos->getY(), printCol, winText);

    std::stringstream scoreStr;
    scoreStr << highScore;
    prg::Font::MEDIUM.print(canvas, hsPos->getX(), hsPos->getY(), printCol, "High score: " + scoreStr.str());

    std::stringstream scoreStr2;
    scoreStr2 << score;
    prg::Font::MEDIUM.print(canvas, sPos->getX(), sPos->getY(), printCol, "Your score: " + scoreStr2.str());

    mainMenuBtn->draw(canvas);
}
//}

