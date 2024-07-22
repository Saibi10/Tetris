/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

 /*
 Muhammad Sohaib
 22I-0879
 Section K
 PF-Project
 */

#include <SFML/Graphics.hpp> // Main App Library
#include <SFML/Audio.hpp>    // Main Music Library
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace sf;

int delta_x = 0;

int main()
{

    // Here I asked user for his Name...

    char playerName[10];

    std::cout << "Enter a Player Name...\t";
    std::cin >> playerName;

    /*

    // Here I am going to start play some music during the game...

    Music gameMusic;
    gameMusic.openFromFile("Sounds/gameMusic.wav");
    gameMusic.play();

    */

    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);

    Texture obj1, obj2, obj3, obj4;

    obj1.loadFromFile("img/tiles.png");      // Loading Blocks
    obj2.loadFromFile("img/background.png"); // Loading BackGround
    obj3.loadFromFile("img/frame.png");      // Loading Fram
    obj4.loadFromFile("img/bombs.png");      // Loading Bombs

    Sprite sprite(obj1), background(obj2), frame(obj3), bombs(obj4);
    int colorNum = 1;
    float timer = 0, delay = 0.3;
    bool rotate = 0;

    // My variables

    bool rightMove = false;
    bool leftMove = false;

    int rowFull;

    int rotationTimes = 0;

    int scores = 0;
    int checkScore;
    int bars = 0;
    int clearedRows = 0;

    // These are special variables for bomb...

    bool makeBomb = false;
    float timerOfBomb = 0, delayOfBomb = 0.3;
    int colorNumOfBomb = 1;
    int randBombPosi = (1 + (rand() % 9));

    bool checkGameOver = false;

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        timerOfBomb += time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                                // Event is occurring - until the game is in running state
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // Opened window disposes
            if (e.type == Event::KeyPressed)
            { // If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)
                { // Check if the other key pressed is UP key
                    rotate = true;
                } // Rotation gets on
                else if (e.key.code == Keyboard::Left)
                { // Check if the other key pressed is LEFT key
                    leftMove = true;
                } // Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)
                { // Check if the other key pressed is RIGHT key
                    rightMove = true;
                } // Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) // Just another way to detect key presses without event listener
            delay = 0.05;                           // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        else
            delay = 0.3;

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

        // Here the Block is falling making its color also...

        fallingPiece(timer, delay, colorNum, delta_x, checkGameOver, clearedRows);

        // This value is watching if the colums are still left for the block to move right or not...

        if (delta_x < 10)
        {
            moveR(rightMove, delta_x); // Moving Block Right
        }
        // This value is watching if the colums are still left for the block to move left or not...
        if (delta_x > 0)
        {
            moveL(leftMove, delta_x); // Moving Block Left
        }
        // resetVals(delay, delta_x, rotate);								//Values Reset after every even

        doRotation(rotate);
        rotate = false;

        // This will first see if a row is full then it will remove all the blocks in the specific row...

        clearFullRow(scores, bars, clearedRows);

        // Now this is a gameOver Function which is actually closing the window if game is OVer...

        if (checkGameOver == true)
        {
            if (scores >= checkScore)
            {
                std::cout << "\n\nHurray...You made a new High Score...\n"
                    << "Name\tScores\n"
                    << playerName << "\t" << scores << std::endl;
            }
            else
            {
                std::cout << "\n\nOhh...You can't get to the High Scores...\nBetter Luck Next Time\n"
                    << "Name\tScores\n"
                    << playerName << "\t" << scores << std::endl;
            }

            window.close();
        }

        // Now here we are call Bomb Functions...

        if (makeBomb == true) // This will only be true if makeBomb is true in Prob function...
        {
            fallingBoom(timerOfBomb, delayOfBomb, makeBomb, colorNumOfBomb, scores);
        }

        // Here is the function that is defining some specific probability of Making a Bomb...
        bombFallingProb(makeBomb, colorNumOfBomb);

        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }

        // This loop is for falling Piece or Blocks...it contains 18 pixels from tiles.

        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }

        // This loop is for falling Bombs or making bombs...it contains 18 pixels from tiles.

        if (makeBomb == true)
        {
            for (int i = 0; i < 4; i++)
            {
                bombs.setTextureRect(IntRect(colorNumOfBomb * 18, 0, 18, 18));
                bombs.setPosition(boom_1[i][0] * 18, boom_1[i][1] * 18);
                bombs.move(28, 31);
                window.draw(bombs);
            }
        }
        else
        {
            for (int m = 0; m < 4; m++)
            {
                boom_1[m][1] = 0;
            }
        }

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();

        std::ifstream filer;
        filer.open("scoreBoard.txt");
        filer >> checkScore;
        filer.close();

        if (scores >= checkScore)
        {
            std::ofstream filer;
            filer.open("scoreBoard.txt");
            filer << scores;
            filer.close();
        }
    }
    return 0;
}
