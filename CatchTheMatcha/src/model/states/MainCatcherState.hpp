/*
 A concrete class that handles the states of a character sprite (one that can be moved with keyboard arrows).
 */
#pragma once
#include "CharacterState.hpp"

class MainCatcherState : public CharacterState {
public:
    MainCatcherState(float width, float height) : CharacterState(width, height) {
        screenWidth = width;
        screenHeight = height;
        walkingC.setScreenWidth(screenWidth);
        runningC.setScreenWidth(screenWidth);
        jumpingC.setScreenWidth(screenWidth);
    };
    void update(Sprite* sprite) override;
    void draw(Sprite* sprite, SDL_Surface *windowSrfc) override;
    void handleInput(Sprite* sprite, const SDL_Event &input) override;
    void setWidth(float width)   { screenWidth  = width; };
    void setJumpingCommand() {
        loseC.setTimer(gameController->getGameplayTimer());
        victoryC.setTimer(gameController->getGameplayTimer());
        jumpingC.setTimer(gameController->getGameplayTimer());
        speedBoostC.setTimer(gameController->getGameplayTimer());
        isTimerSetUp = true;
    };
    void setHeight(float height) { screenHeight = height; };
    void setGameController(GameController* controller) { gameController = controller; } ;
    LoseCommand getLoseCmd() {return loseC;};
    SpeedBoostCommand getSpeedBoostCmd() { return speedBoostC; };
    
    void resetCommands(Sprite* sprite) override;
    
private:
    // commands
    float screenWidth;
    float screenHeight;
    bool isTimerSetUp = false;
    IdleCommand idleC = IdleCommand();
    WalkingCommand walkingC = WalkingCommand();
    JumpingCommand jumpingC = JumpingCommand();
    RunningCommand runningC = RunningCommand();
    VictoryCommand victoryC = VictoryCommand();
    LoseCommand loseC = LoseCommand();
    
    // for speed boosts, there will be a command as well as a draw method for the images
    SpeedBoostCommand speedBoostC = SpeedBoostCommand();
    void drawBoostImages(Sprite* sprite, SDL_Surface* windowSrfc);
    
    // controller for obtaining model info
    GameController* gameController; // to send scene requests to if needed.
};

