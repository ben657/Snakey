#include "src/GameState.hpp"
#include "src/Entity.hpp"
#include "src/Snake.hpp"

#include <iostream>
#include <prg_interactive.hpp>

using namespace std;

int main()
{
    HighScoreState hs;
    PauseState ps(&hs);
    GameState gs(&hs);
    MainMenuState ms(&gs);

    prg::application.addState("MainMenuState", ms);
    prg::application.addState("HighScoreState", hs);
    prg::application.addState("PauseState", ps);
    prg::application.addState("GameState", gs);
    prg::application.setClearColour(prg::Colour(128,128,128));
    prg::application.run(960,640,"Snake","n3049036");
    return 0;
}
