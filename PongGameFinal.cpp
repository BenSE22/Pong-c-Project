/* --------------------------------------------------------
 *    File: PongGameFinal.cpp
 *  Author: Benjamin Castro
 *   Class: Your Class
 * Purpose: This in the final and completed version of the pong game.
 * -------------------------------------------------------- */

#include  "pong_defs.h"


direction processInput();
void setup(Ball &ball ,Borders &theWalls, Moving_block &user,Moving_block &aiPlayer,Paddle userSpecs );
bool update(direction &input, Ball &ball, Borders theWalls,Moving_block &user,Moving_block &aiPlayer,Paddle userSpecs,bool &started,bool &game_Over, float delta);
void render(sf::RenderWindow &window, Ball &ball, Borders theWalls,Moving_block &user,Moving_block &aiPlayer,Paddle &userSpecs, float delta);
bool checkCollision(Ball checkBall, Block checkingTheWalls);
bool checkingPaddlesCollision(Moving_block checkUser,Block checkWall);
bool startCollisionChecking(Ball &ball,Borders &theWalls,Moving_block &user,Moving_block &aiPlayer,bool game_Over);


/**
 * The main application
 * @return OS status message (0=Success)
 */


int main() {
    // create a 2d graphics window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HelloSFML");
    window.clear(WINDOW_COLOR);


    // declare a ball variable
    Ball theBall;
    Ball ball;

    // declaring for borders
    Borders theWall;
    Borders theWalls;

    // declare Moving Block
    Moving_block user;

    //declaring for paddle
    Paddle userSpecs;

    //declaring for ai paddle
    Moving_block aiPlayer;

    setup(theBall, theWall, user,aiPlayer, userSpecs);


    // timing variables for the main game loop
    sf::Clock clock;
    sf::Time startTime = clock.getElapsedTime();
    sf::Time stopTime = startTime;
    float delta = 0.0;

    bool started{false};
    bool game_Over{false};
    bool gameOver{false};
    while (!gameOver)
    {
        // calculate frame time
        stopTime = clock.getElapsedTime();
        delta += (stopTime.asMilliseconds() - startTime.asMilliseconds());
        startTime = stopTime;


        // process events
        sf::Event event;
        while (!gameOver && window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                gameOver = true;
        }

        // Process user input
        // ------------------------------------------------
        direction userInput = processInput();
        if (userInput == -1)
            gameOver = true;
        // Process Updates
        // ------------------------------------------------
        if (delta >= FRAME_RATE) {    // if we have made it at least a full frame time

            gameOver = update(userInput, theBall, theWall,user,aiPlayer,userSpecs,started,game_Over, delta);
            // subtract the frame-rate from the current frame-time
            // for each full frame covered by this update
            while (delta >= FRAME_RATE)
                delta -= FRAME_RATE;
        }
        // Render the window
        // ------------------------------------------------
        render(window,theBall,theWall,user,aiPlayer,userSpecs,delta);
    } // end main game loop
    // game ending, close the graphics window
    window.close();
    return 0;   // return success to the OS
} // end main

/**
 *
 * @param ball
 * @param Block
 * @param player
 */

void setup(Ball &ball,Borders &theWalls,Moving_block &user,Moving_block &aiPlayer,Paddle userSpecs){


    // <initialize the ball structure properties here>(old code)

    // ball.radius = BALL_RADIUS;
    // ball.coordinateX = WINDOW_WIDTH/2.0;
    // ball.coordinateY = WINDOW_HEIGHT / 2.0;
    //ball.velocityX = 0.0;
    // ball.velocityY =0.0;
    // ball.Color = BALL_COLOR;

    //declare Blocks

    theWalls.leftWall.left = 0.0;
    theWalls.leftWall.top = 0.0;
    theWalls.leftWall.width = Block_Thickness;
    theWalls.leftWall.height = WINDOW_HEIGHT;
    theWalls.leftWall.rectangle.setSize(sf::Vector2(theWalls.leftWall.width, theWalls.leftWall.height));
    theWalls.leftWall.rectangle.setPosition(theWalls.leftWall.left, theWalls.leftWall.top);
    theWalls.leftWall.rectangle.setFillColor(Block_Color);

    theWalls.rightWall.left = WINDOW_WIDTH - Block_Thickness;
    theWalls.rightWall.top = 0.0;
    theWalls.rightWall.width = Block_Thickness;
    theWalls.rightWall.height = WINDOW_HEIGHT;
    theWalls.rightWall.rectangle.setSize(sf::Vector2(theWalls.rightWall.width, theWalls.rightWall.height));
    theWalls.rightWall.rectangle.setPosition(theWalls.rightWall.left, theWalls.rightWall.top);
    theWalls.rightWall.rectangle.setFillColor(Block_Color);

    theWalls.topWall.left =0.0;
    theWalls.topWall.top = 0.0;
    theWalls.topWall.width = WINDOW_WIDTH;
    theWalls.topWall.height = Block_Thickness;
    theWalls.topWall.rectangle.setSize(sf::Vector2(theWalls.topWall.width, theWalls.topWall.height));
    theWalls.topWall.rectangle.setPosition(theWalls.topWall.left, theWalls.topWall.top);
    theWalls.topWall.rectangle.setFillColor(Block_Color);

    theWalls.bottomWall.left =0.0;
    theWalls.bottomWall.top = WINDOW_HEIGHT-Block_Thickness;
    theWalls.bottomWall.width = WINDOW_WIDTH;
    theWalls.bottomWall.height = Block_Thickness;
    theWalls.bottomWall.rectangle.setSize(sf::Vector2(theWalls.bottomWall.width, theWalls.bottomWall.height));
    theWalls.bottomWall.rectangle.setPosition(theWalls.bottomWall.left, theWalls.bottomWall.top);
    theWalls.bottomWall.rectangle.setFillColor(Block_Color);

    // users paddle


    user.usersPaddle.left = userSpecs.PaddleThickness;
    user.usersPaddle.top = (WINDOW_HEIGHT - userSpecs.PaddleHeight) / 2.0f;
    user.usersPaddle.width = userSpecs.PaddleThickness;
    user.usersPaddle.height = userSpecs.PaddleHeight;
    user.usersPaddle.Color = userSpecs.paddleColor;
    user.usersPaddle.rectangle.setSize(sf::Vector2(user.usersPaddle.width, user.usersPaddle.height));
    user.usersPaddle.rectangle.setFillColor(userSpecs.paddleColor);
    user.velocityX = 0.0;
    user.velocityY = 0.0;


    //aiPaddle
    aiPlayer.usersPaddle.left = theWalls.rightWall.left - 2 * userSpecs.PaddleThickness;
    aiPlayer.usersPaddle.top = (WINDOW_HEIGHT - userSpecs.PaddleHeight) / 2.0;
    aiPlayer.usersPaddle.width = userSpecs.PaddleThickness;
    aiPlayer.usersPaddle.height = userSpecs.PaddleHeight;
    aiPlayer.usersPaddle.Color = userSpecs.paddleColor;
    aiPlayer.usersPaddle.rectangle.setSize(sf::Vector2(aiPlayer.usersPaddle.width, aiPlayer.usersPaddle.height));
    aiPlayer.usersPaddle.rectangle.setFillColor(userSpecs.paddleColor);
    aiPlayer.velocityX = 0.0f;
    aiPlayer.velocityY = 0.0f;


    //ball
    ball.radius = BALL_RADIUS;
    //ball.coordinateX = WINDOW_WIDTH / 2.0;
    //ball.coordinateY = WINDOW_HEIGHT / 2.0;
    ball.coordinateX = user.usersPaddle.left + userSpecs.PaddleThickness + BALL_RADIUS + 1.0;
    ball.coordinateY = user.usersPaddle.top + (userSpecs.PaddleHeight / 2.0);
    ball.velocityX = 0.0;
    ball.velocityY = 0.0;
    ball.Color = BALL_COLOR;
}

/**
 * convert user keyboard input into recognized integer values
 * for left=1/up=2/right=3/down=4
 * @return int - user input (default no-input=0, quit=-1)
 */


direction processInput() {
    direction input = None;  // no input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        input = LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        input = Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        input = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        input = DOWN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        input = EXIT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        input = Start;
    }
    return input;
}
/**
 * update the state of game objects
 * @param input - user keyboard input
 * @param ball  - update ball position and speed
 * @param delta - current frame time
 * @param aiPlayer- ai player paddle
 * @param Blocks - Borders for ball to stay in
 */
bool update(direction &input, Ball &ball, Borders theWalls,Moving_block &user,Moving_block &aiPlayer,Paddle userSpecs,bool &started,bool &game_Over, float delta) {
    // adjust velocity directions for user input
    game_Over = false;
    if (input) {
        switch (input) {
            case LEFT: // Left
                //<ball's velocityX here>
                //ball.velocityX -= BALL_SPEED_X;
                break;
            case Up: // Up
                user.velocityY -= userSpecs.PaddleSpeed;
                //<ball's velocityY here>
                //ball.velocityY -= BALL_SPEED_Y;
                break;
            case RIGHT: // Right
                //<ball's velocityX here>
                //ball.velocityX += BALL_SPEED_X;
                break;
            case DOWN: // Down
                user.velocityY += userSpecs.PaddleSpeed;
                break;

            case Start://started
                if(!started){
                    ball.velocityX = BALL_SPEED_X;
                    ball.velocityY = BALL_SPEED_Y;
                    //ball will go down if odd
                    if ((int(delta * 10)&1)% 2){
                        ball.velocityX *= -1;
                    }
                    started = true;
                }
                break;

                //ball.velocityY += BALL_SPEED_Y;
        }
        // clear input
        input = None;
    }


    // adjust the location of the ball for speed * time
    //ball.coordinateX += ball.velocityX * delta;
    //ball.coordinateY += ball.velocityY * delta;

    user.usersPaddle.top += user.velocityY * delta;
    aiPlayer.usersPaddle.top += aiPlayer.velocityY *delta;
    //started ball movement once user move
    if(started){
        ball.coordinateX += ball.velocityX * delta;
        ball.coordinateY += ball.velocityY * delta;
        if(ball.coordinateY < aiPlayer.usersPaddle.top + aiPlayer.usersPaddle.height / 2.0f){
            aiPlayer.velocityY -= userSpecs.PaddleSpeed;
        }
        else if(ball.coordinateY > aiPlayer.usersPaddle.top + aiPlayer.usersPaddle.height / 2.0f) {
            aiPlayer.velocityY += userSpecs.PaddleSpeed;
        }
    }
        //Won't be started unless there is movement
    else{
        ball.coordinateX  = user.usersPaddle.left + userSpecs.PaddleThickness + BALL_RADIUS + 1.0;
        ball.coordinateY = user.usersPaddle.top + (userSpecs.PaddleHeight/2.0);
    }
    startCollisionChecking(ball,theWalls,user,aiPlayer,game_Over);

}
// end update


/**
 * draw the ball on the graphics window
 * @param window - handle to open graphics window
 * @param ball   - structure variable with properties for the ball
 * @param Blocks   -  the 4 borders
 * @param Paddle - the players paddle
 * @param delta  - amount of frame time plus lag (in ms)
 */

void render(sf::RenderWindow &window, Ball &ball, Borders theWalls,Moving_block &user,Moving_block &aiPlayer,Paddle &userSpecs, float delta) {    // Render drawing objects
    // ------------------------------------------------
    // clear the window with the background color
    window.clear(WINDOW_COLOR);
    // draw the ball
    // ------------------------------------------------

    sf::CircleShape circle;
    circle.setFillColor(BALL_COLOR);
    circle.setRadius(ball.radius);

    // set screen coordinates relative to the center of the circle
    circle.setOrigin(ball.radius ,ball.radius );


    // calculate current drawing location relative to speed and frame-time
    float xPosition  = ball.coordinateX + ball.velocityX * delta;
    float yPosition = ball.coordinateY + ball.velocityY * delta;
    circle.setPosition(xPosition, yPosition);


    // draw users paddle
    float xPaddlePosition = user.usersPaddle.left + user.velocityX * delta +10.0f;
    float yPaddlePosition = user.usersPaddle.top + user.velocityY * delta +10.0f;
    user.usersPaddle.rectangle.setPosition(xPaddlePosition, yPaddlePosition);
    window.draw(user.usersPaddle.rectangle);

    //draw ai paddle
    float x_usersPaddlePosition = aiPlayer.usersPaddle.left + aiPlayer.velocityX * delta + 0.0f;
    float y_usersPaddlePosition = aiPlayer.usersPaddle.top + aiPlayer.velocityY * delta + 0.0f;
    aiPlayer.usersPaddle.rectangle.setPosition(x_usersPaddlePosition, y_usersPaddlePosition);
    window.draw(aiPlayer.usersPaddle.rectangle);


//draw walls
    window.draw(circle);
    window.draw(theWalls.leftWall.rectangle);
    window.draw(theWalls.topWall.rectangle);
    window.draw(theWalls.rightWall.rectangle);
    window.draw(theWalls.bottomWall.rectangle);
    // show the new window
    // ------------------------------------------------
    window.display();
} // end render


/**
 *check for intersection of ball and a rectangle
 *@param ball - bounding a box around circle
 *@param Block i rectangle to check hit against
 *@return bool returns
 */


bool checkCollision(Ball checkBall, Block checkingTheWall){
    // = false
    bool collision {false};

    float ballLeft = checkBall.coordinateX - checkBall.radius;
    float ballTop = checkBall.coordinateY - checkBall.radius;
    float ballRight = checkBall.coordinateX + checkBall.radius;
    float ballBottom = checkBall.coordinateY + checkBall.radius;

    float boxLeft = checkingTheWall.left;
    float boxTop = checkingTheWall.top;
    float boxRight = checkingTheWall.left + checkingTheWall.width;
    float boxBottom = checkingTheWall.top + checkingTheWall.height;


    if (ballLeft < boxRight &&
        ballRight > boxLeft &&
        ballTop < boxBottom &&
        ballBottom > boxTop){
        collision = true;
        // or use = true;
    }

    return collision;
}// end checkCollision

bool checkingPaddlesCollision(Moving_block checkUser,Block checkWall){
    bool collision {false};
    if(checkUser.usersPaddle.left < checkWall.left + checkWall.width &&
       checkUser.usersPaddle.left + checkUser.usersPaddle.width > checkWall.left &&
       checkUser.usersPaddle.top < checkWall.top + checkWall.height &&
       checkUser.usersPaddle.top + checkUser.usersPaddle.height > checkWall.top){
        collision = true;
    }
    return collision;
}

bool startCollisionChecking(Ball &ball,Borders &theWalls,Moving_block &user,Moving_block &aiPlayer,bool game_Over){
    game_Over = false;
    // shows the collision for paddle and Ball
    if(checkCollision(ball, user.usersPaddle)){
        //ball.velocityX *= -1;
        //ball.coordinateX = user.usersPaddle.left + user.usersPaddle.width + ball.radius + 1;
        if(ball.coordinateY > user.usersPaddle.top + user.usersPaddle.height * 0.2){
            ball.velocityX *= -1.0;
            ball.velocityY *= +1.2;
        }
        else if(ball.coordinateY == user.usersPaddle.top + user.usersPaddle.height / 1.5 && ball.coordinateY == user.usersPaddle.top + user.usersPaddle.height / 2.5){
            ball.velocityX *= -2.0;
            ball.velocityY *= -1.0;
        }
        else if(ball.coordinateY < aiPlayer.usersPaddle.top + aiPlayer.usersPaddle.height * 0.8){
            ball.velocityX *= -1.0;
            ball.velocityY *= +1.2;
        }

    }

        //shows collision with ai_paddle and bal
    else if(checkCollision(ball, aiPlayer.usersPaddle)){
        ball.velocityX *= -1.1;
        //ball.coordinateX + aiPlayer.usersPaddle.left + aiPlayer.usersPaddle.width + ball.radius + 1;
    }

        // checks the ball and walls collision
    else if(checkCollision(ball, theWalls.leftWall)){
        ball.velocityX *= -1;
        ball.coordinateX = theWalls.leftWall.left + theWalls.leftWall.width + ball.radius + 1;
        game_Over = true;
    }
    else if(checkCollision(ball, theWalls.rightWall)){
        ball.velocityX *= -1;
        ball.coordinateX =  theWalls.rightWall.left - ball.radius - 1;
        game_Over = true;
    }
    else if (checkCollision(ball, theWalls.topWall)) {
        ball.velocityY *= - 1;
        ball.coordinateY = theWalls.topWall.top + theWalls.topWall.height + ball.radius + 1;
    }
    else if(checkCollision(ball, theWalls.bottomWall)){
        ball.velocityY *= - 1;
        ball.coordinateY = theWalls.bottomWall.top - ball.radius - 1;
    }

    //checks paddle and wall collision
    if (checkingPaddlesCollision(user, theWalls.topWall)){
        user.velocityY = 0.0f;
        user.usersPaddle.top = theWalls.topWall.top + theWalls.topWall.height;
    }
    else if (checkingPaddlesCollision(user, theWalls.bottomWall)){
        user.velocityY = 0.0f;
        user.usersPaddle.top  =     theWalls.bottomWall.top - user.usersPaddle.height;
    }

    //Shows the ai collision with eall
    if (checkingPaddlesCollision(aiPlayer, theWalls.topWall)){
        aiPlayer.velocityY = 0.0f;
        aiPlayer.usersPaddle.top = theWalls.topWall.top + theWalls.topWall.height;
    }
    else if (checkingPaddlesCollision(aiPlayer, theWalls.bottomWall)){
        aiPlayer.velocityY = 0.0f;
        aiPlayer.usersPaddle.top  = theWalls.bottomWall.top - aiPlayer.usersPaddle.height;
    }

    return game_Over;
}