/*
 A class representing the command for handling the idle state for a sprite.
 */
#include "IdleCommand.hpp"
#include "Sprite.hpp"

void IdleCommand::update(Sprite *sprite) {
    STATE state = sprite->getState();
    sprite->resetSheet(state);
}
