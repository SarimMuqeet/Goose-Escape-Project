#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"
#include "gooseEscapeMain.cpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/
	
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/

// print the game board function
void printBoard(int map[GAME_ROWS][GAME_COL])
{
    for(int rowCount = 0; rowCount < 21; rowCount++)
    {
    	for(int colCount = 0; colCount < 80; colCount++)
    	{
    		if(map[rowCount][colCount] == 1)
    		{
    			terminal_put(colCount, rowCount, WALL_CHAR);
			}
			if(map[rowCount][colCount == 2])
			{
				terminal_put(colCount, rowCount, WIN_CHAR);
			}
		}
	}
}

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

bool hasWon(Actor const & player, const int WINNER)
{
    return (player.get_x() == WINNER_X 
         && player.get_y() == WINNER_Y;
}

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/

void movePlayer(int key, Actor & player, int map[GAME_ROWS][GAME_COL])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    if (player.can_move(xMove, yMove)  && 
	map[player.get_y() + yMove][player.get_x() + xMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/

void gooseChase(Actor & goose, Actor & player, int map[GAME_ROWS][GAME_COL])
{
	int distX = goose.get_x() - player.get_x();
	int distY = goose.get_y() - player.get_y();
	
	int moveX = distX/(abs(distX));
	int moveY = distY/(abs(distY));
	
	goose.update_location(moveX, moveY);
	terminal_refresh();
}


