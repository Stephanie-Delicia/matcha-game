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

ScreenModel* ScreenNavigator::getScreen(SCREEN type) {
    for (const auto& [key, value] : getScreens()) {
        if (key->screenType() == type) {
            return key;
        }
    }
    return nullptr;
}
 
void ScreenNavigator::setMainScreen(ScreenModel* screen) {
    // make old main screen inactive and new screen active in map
    if (mScreen != nullptr) {
        mScreen->deactivate();
        screenMap[mScreen] = false;
    }
    // do this regardless
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
    int screenCounter = 0;
    for (auto i = data["ls"].begin(); i != data["ls"].end(); i++) {
        std::string typeStr = data["ls"][screenCounter]["type"];
        SCREEN screenT = screenTypeMap[typeStr];
        std::deque<Sprite*> bgQueue;
        std::deque<Sprite*> mQueue;
        int queueCounter = 0;
        // background queue
        for (auto j = data["ls"][screenCounter]["bgQueue"].begin();
                  j != data["ls"][screenCounter]["bgQueue"].end();
                  j++) {
            // get each sprite from this queue
            std::string nameStr = (std::string) data["ls"][screenCounter]["bgQueue"][queueCounter];
            NAME name = strNameMap[nameStr];
            bgQueue.push_back(nameSpriteMap->getSprite(name));
            queueCounter++;
        }
        // main queue
        queueCounter = 0;
        for (auto j = data["ls"][screenCounter]["mQueue"].begin();
                  j != data["ls"][screenCounter]["mQueue"].end();
                  j++) {
            // get each sprite from this queue
            std::string nameStr = (std::string) data["ls"][screenCounter]["mQueue"][queueCounter];
            NAME name = strNameMap[nameStr];
            mQueue.push_back(nameSpriteMap->getSprite(name));
            queueCounter++;
        }
        // add new screen to Nav map (WARNING: NEW KEYWORD AHHHHHHHHHHHHHHHHHHHHHH. Make sure to delete after.)
        ScreenModel* newScreen = new ScreenModel(bgQueue,
                                                 mQueue,
                                                 data["ls"][screenCounter]["width"],
                                                 data["ls"][screenCounter]["height"]);
        newScreen->setType(screenT); // set type
        addScreen(newScreen);        // add the screen to this navigator
        if (data["ls"][screenCounter]["active"]) {
            setMainScreen(newScreen);
        }
        screenCounter++;
    }
}
