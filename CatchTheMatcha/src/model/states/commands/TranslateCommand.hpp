/*
 A class representing the command for translating a sprite in the x or y direction.
 */
#pragma once
#include <cmath>
#include "StateCommand.hpp"
#include "../../sprite/Sprite.hpp"
#include "../../sprite/SpriteSheet.hpp"
#include "../../../utils/Posn.hpp"
#include "../../../utils/Timer.hpp"
#include "../../../utils/data_maps/NameStateSheetMap.hpp"

class TranslateCommand : public StateCommand {
    
public:
    TranslateCommand() {};
    void update(Sprite* sprite) override;
    void setTimer(Timer* t) { timer = t; };
    void resetStartTime() { startTime = 0; };
    float xWavePosn(float time, float currentX) { return currentX + (x_amplitude * sin(time / x_wave_rate)); }; // what wave function should we use?
    
protected:
    // for wave movement, set amplitudes/peaks
    float x_amplitude = 3;
    float x_wave_rate = 150;
    
    // timer
    float startTime = 0;
    Timer* timer;
};
