#include "ScreenNavigator.hpp"
#include <map>
#include <string>
#include <queue>
#include <iostream>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SCREEN.h"
#include "SpriteSheet.hpp"
#include "ScreenModel.hpp"
#include "NameStateSheetMap.hpp"

ScreenNavigator::ScreenNavigator(ScreenModel* mainScreen) {
    mScreen = mainScreen;
}

ScreenNavigator::ScreenNavigator(std::map<ScreenModel*, bool> screens) {
    screenMap = screens;
}

ScreenNavigator::ScreenNavigator(std::map<ScreenModel*, bool> screens, ScreenModel* mainScreen) {
    screenMap = screens;
    mScreen = mainScreen;
}

ScreenModel* ScreenNavigator::getMainScreen() {
    return mScreen;
}

std::map<ScreenModel*, bool> ScreenNavigator::getScreens() {
    return screenMap;
}

bool ScreenNavigator::isActive(ScreenModel* screen) {
    return screenMap[screen];
}

bool ScreenNavigator::containsScreen(ScreenModel* screen) {
    return screenMap.count(screen);
}

void ScreenNavigator::setMainScreen(ScreenModel* screen) {
    // make old main screen inactive and new screen active in map
    mScreen->deactivate();
    screenMap[mScreen] = false;
    screen->activate();
    screenMap[screen] = true;
    // reassign
    mScreen = screen;
}

void ScreenNavigator::addScreen(ScreenModel* screen) {
    screen->deactivate();
    screenMap[screen] = false; // by default, new screen is not activated
}
