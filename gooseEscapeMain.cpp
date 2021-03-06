#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"
#include "gooseEscapeGamePlay.cpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/
 	
    //make the player
	Actor player(PLAYER_CHAR, 10,10);  // you probably don't want to start in the same place each time
	
	//make the monster
	Actor goose(MONSTER_CHAR, 70,20);
	
    // Declare the array that will hold the game board "map"
    const int GAME_ROWS = 21;
  	const int GAME_COL = 80;
	
	int map[GAME_ROWS][GAME_COL] = {0};
  	
/*
    Initiallize locations in the game board to have game features.  What if you
    have man things to add to the game board?  Should you use a loop?  Does it
    make sense to store this information in a file?  Should this code be a
    function as well?
*/
	/* game map location = SHALL_NOT_PASS*/;
	const int rowWall = 15;
	for(int colWall = 28; colWall <= 38; colWall++)
	{
		map[rowWall][colWall] = SHALL_NOT_PASS;
	}
    
    /* game map location = WINNER*/;
    const int WINNER_Y = 4;
    const int WINNER_X = 77;
  	map[WINNER_Y][WINNER_X] = WINNER;
  	
    // Call the function to print the game board
    printboard(map);
  	
	// Printing the instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  // can be any valid value that is not ESCAPE or CLOSE
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
		&& !captured(player, goose) && !hasWon(player, WINNER))
	{
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player, you can modify this function
    	    movePlayer(keyEntered,player,map); /* game board array and maybe other parameters*/

            // call the goose's chase function
            gooseChase(goose, player, map); 
            
            // call other functions to do stuff?	    
			terminal_refresh();
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    
        // output why:  did the goose get us, or did we get to the win location?
		if(!captured(player, goose))
		{
			out.writeLine("You have won!");
		}
		else
		{
			out.writeLine("You have been captured by the goose. That's rough buddy");
		}
		
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}
