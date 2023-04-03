/* --------------------------------------------------------
 *    File: block.cpp
 *  Author: Benjamin Castro
 *   Class: Your Class
 * Purpose: Making definitions for the  final pong game.
 * -------------------------------------------------------- */


#include <SFML/Graphics.hpp>


#ifndef block_CPP_PONG_DEFS_H
#define block_CPP_PONG_DEFS_H


// Ball properties
float BALL_RADIUS = 10.00;


const float Block_Thickness = 10.0;
const sf::Color Block_Color = sf::Color::Green;


// window properties
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const sf::Color WINDOW_COLOR = sf::Color::White;

// drawing properties
const float FRAME_RATE = (3.0/1000.0) * 10000.0;       // FPS in ms
const sf::Color BALL_COLOR = sf::Color::Blue;


// These are just for fun
// speed that the can accelerate at to span window in
// n-seconds (in ms) broken up for each frame
const float SPEED_TIME = (3.0 * 1000.0) * 30.0;     //
const float BALL_SPEED_X = BALL_RADIUS * 10/1000.0 ;    // speed horizontally
const float BALL_SPEED_Y = BALL_RADIUS * 8.5/1000.0;   // span  vertically
// Type definitions

//enum
enum direction{
    EXIT = -1,
    None = 0,
    LEFT = 1,
    Up = 2,
    RIGHT = 3,
    DOWN = 4,
    Start = 5,
};

// --------------------------------------------------------



// ball properties
struct Ball {
    // <define structure properties here>
    float radius;
    float coordinateX;
    float coordinateY;
    float velocityX;
    float velocityY;
    sf:: Color Color;
};
// block borders for walls
struct Block {
    float left;
    float top;
    float width;
    float height;
    sf:: Color Color;
    sf::RectangleShape rectangle;

};

// border for walls
struct Borders{
    Block leftWall ;
    Block topWall ;
    Block rightWall ;
    Block bottomWall;

};


struct Moving_block {
    Block usersPaddle;
    float velocityX;
    float velocityY;


};


struct Paddle{
    const float PaddleHeight = 80.0;
    const float PaddleThickness = 10.0;
    sf:: Color paddleColor = sf::Color::Blue;
    const float PaddleSpeed = PaddleHeight /10.0/100.0;

};



#endif //HELLOSFML_PONG_DEFS_H