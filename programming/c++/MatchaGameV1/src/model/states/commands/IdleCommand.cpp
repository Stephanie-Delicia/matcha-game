#include "IdleCommand.hpp"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"

/*
 A class representing the command for handling the idle state for a sprite.
 */

IdleCommand::IdleCommand() {
}

IdleCommand::~IdleCommand() {
}

void IdleCommand::update(Sprite *sprite) {
    STATE state = sprite->getState();
    sprite->resetSheet(state);
}
