#include "GameModel.hpp"
#include <string>

GameModel::GameModel() {
}

GameModel::GameModel(float w, float h, std::string name) {
    screenWidth = w;
    screenHeight = h;
    gameName = name;
}

GameModel::GameModel(float w, float h, std::string name, Sprite* mainSprite, NameStateSheetMap* map, ScreenNavigator* nav) {
    screenWidth = w;
    screenHeight = h;
    gameName = name;
    mPlayer = mainSprite;
    nameStateSheetMap = map;
    screenNav = nav;
}

float GameModel::getWidth() {
    return screenWidth;
}

float GameModel::getHeight() {
    return screenHeight;
}

std::string GameModel::getGameName() {
    return gameName;
}

Sprite* GameModel::getMainPlayer() {
    return mPlayer;
}

ScreenModel* GameModel::getActiveScreen() {
    return screenNav->getMainScreen();
}

ScreenNavigator* GameModel::getNavigator() {
    return screenNav;
}

NameStateSheetMap* GameModel::getNameToSheetMap() {
    return nameStateSheetMap;
}

void GameModel::update() {
    screenNav->getMainScreen()->update();
}

void GameModel::handleInput(const SDL_Event &event) {
    screenNav->getMainScreen()->handleInput(event);
}

void GameModel::setWidth(float w) {
    screenWidth = w;
}
void GameModel::setHeight(float h) {
    screenHeight = h;
}

void GameModel::setGameName(std::string name) {
    gameName = name;
}
void GameModel::setMainPlayer(Sprite* sprite) {
    mPlayer = sprite;
}

void GameModel::setScreenNav(ScreenNavigator* nav) {
    screenNav = nav;
}

void GameModel::setActiveScreen(ScreenModel* screen) {
    screenNav->setMainScreen(screen);
}

void GameModel::setNameToSheetMap(NameStateSheetMap* map) {
    nameStateSheetMap = map;
}

void GameModel::setNameToSpriteMap(NameSpriteMap* map) {
    nameSpriteMap = map;
}

void GameModel::delayFrameTimes(float gameDelay, float timeElapsed) {
    screenNav->getMainScreen()->delayFrameTimes(gameDelay, timeElapsed);
}
