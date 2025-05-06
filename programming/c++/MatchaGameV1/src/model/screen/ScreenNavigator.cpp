#include "ScreenNavigator.hpp"
#include <map>
#include <deque>
#include <string>
#include <queue>
#include <SDL3/SDL.h>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <fstream>
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

void ScreenNavigator::loadJSON(std::string filepath) {
    // open file
    std::ifstream file(filepath);
    // catch error
    if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
    
    // read in data from file
    nlohmann::json data;
    file >> data;
    file.close();
    
    // Recurring thru screen types
    for (auto i = screenTypeMap.begin(); i != screenTypeMap.end(); i++) {
        // cout << "i: " << i << "/n";
        std::string typeStr = i->first;
        SCREEN screen = screenTypeMap[typeStr];
        std::deque<Sprite*> bgQueue;
        std::deque<Sprite*> mQueue;
        int counter = 0;
        // background queue
        for (auto j = data[typeStr]["bgQueue"].begin(); j != data[typeStr]["bgQueue"].end(); j++) {
            // get each sprite from this queue
            std::string nameStr = (std::string) data[typeStr]["bgQueue"][counter];
            bgQueue.push_back(spriteMap[nameStr]);
            counter++;
        }
        // main queue
        counter = 0;
        for (auto j = data[typeStr]["mQueue"].begin(); j != data[typeStr]["mQueue"].end(); j++) {
            // get each sprite from this queue
            std::string nameStr = (std::string) data[typeStr]["mQueue"][counter];
            mQueue.push_back(spriteMap[nameStr]);
            counter++;
        }
        // add new screen to Nav map (WARNING: NEW KEYWORD AHHHHHHHHHHHHHHHHHHHHHH. Make sure to delete after.)
        ScreenModel* newScreen = new ScreenModel(bgQueue, mQueue, data[typeStr]["width"], data[typeStr]["height"]);
        addScreen(newScreen);
        if (data[typeStr]["active"]) {
            setMainScreen(newScreen);
        }
    }
}
