#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include <prg_interactive.hpp>
#include "Entity.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"
#include "UI.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

class HighScoreState;

class GameState : public prg::IAppState{

public:
    GameState(HighScoreState* pHs):hs(pHs){};
    bool onCreate();
    bool onDestroy();
    virtual void onEntry();
    void onExit();
    virtual void onUpdate();
    virtual void onRender(prg::Canvas &canvas);

    void reset();
    Snake* getLongest(Snake* s1, Snake* s2);

    int getFruitCount(){
        return fruit.size();
    }
    Fruit* getFruit(int index){
        return fruit[index];
    }

protected:

    HighScoreState* hs;

    int score = 0;
    int UIOffset = 100;

    std::vector<Snake*> snakes;
    std::vector<Fruit*> fruit;
    void spawnFruit(int amount);
    void removeFruit(int index);

};

class MainMenuState : public prg::IAppState{

public:
    MainMenuState(GameState* pGs):gs(pGs){};
    bool onCreate();
    bool onDestroy();
    void onEntry();
    void onExit();
    void onUpdate();
    void onRender(prg::Canvas &canvas);

private:
    GameState* gs;

    Button* playBtn;
    Button* exitBtn;

    Position titlePos;

};

class PauseState : public GameState{

public:
    PauseState(HighScoreState* pHs):GameState(pHs){};
    void onEntry();
    void onExit();
    void onUpdate();
    void onRender(prg::Canvas& canvas);

private:
    Position* pausePos;
    Button* resumeBtn;
    Button* endGameBtn;
};

class HighScoreState : public prg::IAppState{

public:
    bool onCreate();
    bool onDestroy();
    void onEntry();
    void onExit();
    void onUpdate();
    void onRender(prg::Canvas &canvas);

    void setData(std::string pWinner, int pScore);

private:

    Position* titlePos;
    Position* hsPos;
    Position* sPos;

    Button* mainMenuBtn;

    int loadScore();
    void saveScore(int toSave);

    std::string winner = "";
    std::string winText = "";
    int score = 0;
    int highScore = 0;

};

#endif // GAMESTATE_HPP_INCLUDED
