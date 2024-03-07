#pragma once

#include <glm/glm.hpp>
#include <string>

#include <unordered_map>
#include <vector>




struct Turret {
    glm::vec2 position;
    std::string color;
    int cost;
    bool draggable = true;
    float radius = 50;
    bool set = false;
    bool scale = false;
    float scaleFactor = 1.0f;
    float starSpawnTimer = 0.0f;
    float starSpawnInterval = 1.5f;
   
};

struct GridSquare {
    bool occupied = false;
    glm::vec2 position;
    float radius = 50;
};

struct Star {
    glm::vec2 position;
    std::string color;
    float speed = 145 ;
    float radius = 35 ;
    float angle_rotation = 0.0f;
    bool collision = false;
    
};

struct Enemy {
    glm::vec2 position;
    std::string color;
    float speed = 70;
    int lifes = 3;
    float radius ;
    float scaleFactor = 1.0f;
    bool die = false;
    int hits = 3;
    int dead = 0;
};

struct Tank {
    glm::vec2 position;
    float speed = 300;
    float radius = 60;
    bool start = false;
};

struct Bonus {
    glm::vec2 position;
    glm::vec2 velocity;
    float speed = 125;
    float radius = 65;
    bool active = false;
    int direction = 1;
    float directionChangeTimer = 0.0f; 

};

struct Point {
    float x, y;
};

struct BonusLife {
    glm::vec2 position;
    glm::vec2 velocity;
    float speed = 300;
    float radius = 30;
    bool active = false;
    int direction = 1;
    float directionChangeTimer = 0.0f;
    float rotationSpeed;
    float rotationAngle;
    glm::vec2 initialPosition;
   
};

const std::unordered_map<char, std::vector<std::string>> characterMap = {
    {'P', {
        "####",
        "#  #",
        "####",
        "#",
        "#"
    }},
    {'A', {
        "####",
        "#  #",
        "####",
        "#  #",
        "#  #"
    }},
    {'U', {
        "#  #",
        "#  #",
        "#  #",
        "#  #",
        "####"
    }},
    {'S', {
        "####",
        "#",
        "####",
        "   #",
        "####"
    }},
    {'E', {
        "###",
        "#",
        "###",
        "#",
        "###"
    }},
    {'D', {
        "###",
        "#  #",
        "#  #",
        "#  #",
        "###"
    }},
    {'G', {
        "######",
        "#",
        "#  ###",
        "#    #",
        "######"
    }},
    {'M', {
        "#    #",
        "##  ##",
        "# ## #",
        "#    #",
        "#    #"
    }},
    {'O', {
        " ##",
        "#  #",
        "#  #",
        "#  #",
        " ##"
    }},
    {'V', {
        "#   #",
        "#   #",
        " # #",
        " # #",
        "  #"
    }},
    {'R', {
        "####",
        "#  #",
        "####",
        "# #",
        "#  #"
    }},
    {'0', {
        " ### ",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    }},
    {'1', {
        "  #  ",
        " ##  ",
        "  #  ",
        "  #  ",
        "###  "
    }},
    {'2', {
        " ##  ",
        "#  # ",
        "  #  ",
        " #   ",
        "#####"
    }},
    {'3', {
        "###  ",
        "   # ",
        " ### ",
        "   # ",
        "###  "
    }},
    {'4', {
        "#  # ",
        "#  # ",
        "#### ",
        "   # ",
        "   # "
    }},
    {'5', {
        "#### ",
        "#    ",
        "###  ",
        "   # ",
        "###  "
    }},
    {'6', {
        " ##  ",
        "#    ",
        "###  ",
        "#  # ",
        " ##  "
    }},
    {'7', {
        "#####",
        "   # ",
        "  #  ",
        " #   ",
        "#    "
    }},
    {'8', {
        " ### ",
        "#   #",
        " ### ",
        "#   #",
        " ### "
    }},
    {'9', {
        " ### ",
        "#   #",
        " ####",
        "    #",
        " ### "
    }},
    {'C', {
        " ### ",
        "#   #",
        "#    ",
        "#   #",
        " ### "
    }},
    { 'Q', {
        " ### ",
        "#   #",
        "#   #",
        "# # #",
        " ## #"
    }},
    { 'I', {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "#####"
    }},
    { 'T', {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  "
    }},
    { 'N', {
        "#   #",
        "##  #",
        "# # #",
        "#  ##",
        "#   #"
    }},
    { '?', {
    " ## ",
    "#  #",
    "  # ",
    "     ",
    "  # "
    }}, 
    { 'Y', {
        "#   #",
        " # # ",
        "  #  ",
        "  #  ",
        "  #  "
    }},
    { 'L', {
        "#    ",
        "#    ",
        "#    ",
        "#    ",
        "#####"
    }},
};


