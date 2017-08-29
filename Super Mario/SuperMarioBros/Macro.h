#pragma once

#include <string>

const float MAX_HEIGHT_BOARD = 600;
const float MAX_WIDTH_BOARD = 800;


enum class Direction { up, right, left, down};
enum class Music { sound1, sound2, sound3, sound4, sound5, sound6 };


const std::string Levels("Level.txt"); 

const std::string View1("Pictures/View1.png");

const std::string MarioPath ("Pictures/Mario.png");

const std::string BrickPath("Pictures/Brick.png");

const std::string TurtlPath("Pictures/Turtle.png");

const std::string PipePath("Pictures/Pipe.png");

const std::string CoinsPath("Pictures/Coins.png");

const std::string FlagPath("Pictures/Flag.png");

const std::string GiftPath("Pictures/Gift.png");

const std::string TransperantPath("Pictures/Transperant.png");

//					font path
const std::string FontPath("Pictures/MAIAN.TTF");

//                  sound path
const std::string SoundPath1("Sound/Super_Mario_Bros_-_Full.wav");

const std::string SoundPath2("Sound/coincollect.wav");

const std::string SoundPath3("Sound/smb_jump-small.wav");

const std::string SoundPath4("Sound/hithard.wav");

const std::string SoundPath5("Sound/applise.wav");

const std::string SoundPath6("Sound/KillMario.wav");


//					Menu path
const std::string Mario2Path("Pictures/Mario2.png");

const std::string PlayPath("Pictures/1.png");

const std::string HelpPath("Pictures/2.png");

const std::string ExitPath("Pictures/3.png");

const std::string InstructionsPath("Pictures/4.png");

const std::string BackPath("Pictures/5.png");

const std::string DisquaPath("Pictures/6.png");

const std::string OverPath("Pictures/7.png");

const std::string DonePath("Pictures/8.png");

const std::string ThankPath("Pictures/9.png");



// num of pixel in each step
const unsigned int Step = 2;

// pixel to move for enemies
const unsigned int StepEnemies = 2;

// num of moves in each jump
const unsigned int StepJump = 30;

// size of each object
const unsigned int SizeOfObject = 30;

// time to move enemies
const float MoveEnemies = 0.3;

// size of the backgoung rect
const unsigned int BackgroundRectX = 1.5 * MAX_WIDTH_BOARD;
const unsigned int BackgroundRectY = MAX_HEIGHT_BOARD + 2 * StepJump * Step ;

// how much Pixel let down
const unsigned int LetPixelsUnderFloor = 30;

// how much pixel befor end will be the flag
const unsigned int LetPixelsForFlag = 50;

// mario position when game start
const int StartMarioPosition = MAX_WIDTH_BOARD / 4;
