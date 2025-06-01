/*
 A class representing the command for translating a sprite in the x or y direction.
 */
#pragma once
#include "StateCommand.hpp"
#include "Sprite.hpp"

class TranslateCommand : public StateCommand {
    
public:
    void update(Sprite* sprite) override;
};
