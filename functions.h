#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <climits>
#include<ctype.h>

using namespace std;

// Include custom headers
#include "gameSpecs.h"
#include "enemyAI.h"


/**
 * Displays random battleship coordinates in quick succession to make the
 * illusion that the computer/enemy is thinking about which coordinate to shoot
 * at.
 *
 * After the function returns the last random coordinate is still on the screen,
 * but the cursor is back up so that it can be overwritten with something new.
 */
void randomCoordinatesAnimation();

/**
 *  Wipes the gameboard and both boards with a default Tile value of water.
 */
void wipeBoard(Tile board[][BOARD_LENGTH], Tile = WATER);

/**
 *  Displays two boards to the screen. 
 */
void displayBoards(const Tile playerFleet[][BOARD_LENGTH], const Tile enemyFleet[][BOARD_LENGTH], bool showAll = false);

/**
 *  Verifies that location input is valid and then places a ship horizontally.
 */
bool placeShipHorizontally(Tile input, int shipSize, int rowOrigin, int colOrigin, Tile board[][BOARD_LENGTH]);

/**
 *  Verifies that location input is valid and then places a ship vertically.
 */
bool placeShipVertically(Tile input, int shipSize, int rowOrigin, int colOrigin, Tile board[][BOARD_LENGTH]);

/**
 *  Randomly calls placeShipHorizontally or Vertically to place all ships on
 *  the game board. 
 */
void placeShipsRandomly(Tile input[][BOARD_LENGTH]);

/**
 *  Places the player ships randomly until the player 
 *  approves of the given gameboard.
 */
void placePlayersShips(Tile playerFleet[][BOARD_LENGTH]);

/**
 *  Prompts the player to select a position to shoot and verifies it.
 */
string playersTurn(Tile enemyBoard[][BOARD_LENGTH], int enemyHitsRemaining[numOfPlayableBoats]);

/**
 *  Keeps track of the remaining hits on each ship.
 */
bool isAllZero(int enemyHitsRemaining[]);

void displayAsIfTyped(const string& message, int msecs = 1000, int pause = 500);

void singlePlayer();

void multiplayer();

void wipeBoard(Tile board[][BOARD_LENGTH], Tile defaultTile /* = WATER */ )
{
	
	for (int rowIndex = 0; rowIndex < BOARD_LENGTH; ++rowIndex)
	{
		for (int colIndex = 0; colIndex < BOARD_LENGTH; ++colIndex)
		{
			board[rowIndex][colIndex] = defaultTile;	
		}
	}
}

void displayBoards(const Tile playerFleet[][BOARD_LENGTH], const Tile enemyFleet[][BOARD_LENGTH], bool showAll)
{
	cout << fixed << left << setw(22) << "  Enemy's Fleet" 
		<< setw(22) << setw(2) << " " << "  Your Fleet" << endl;
	cout << "   1 2 3 4 5 6 7 8 910" << setw(5) << " " << "1 2 3 4 5 6 7 8 910" << endl;
	
	char rowLetter = 'A';

	for (int rowIndex = 0; rowIndex < BOARD_LENGTH; ++rowIndex)
	{
		// Output row letters
		cout << " " << rowLetter;
	
		for (int colIndex = 0; colIndex < BOARD_LENGTH; ++colIndex)
		{
			if (showAll)
			{
				// Display enemy fleet (showAll = false) w/ symbol conversion.
				cout << right << setw(2) << tileToSymbol(enemyFleet[rowIndex][colIndex]);
			}
			else if (enemyFleet[rowIndex][colIndex] == MISS)
			{
				cout << right << setw(2) << '~';
			}
			else if (enemyFleet[rowIndex][colIndex] > MISS)
			{
				cout << right << setw(2) << 'X';
			}

			// If the enemy board position doesn't reflect any of the above
			// Show it as a '.' to represent water.
			else
			{
				cout << right << setw(2) << '.';
			}
			
		}

		// Output the space between the two boards.
		cout << setw(2) << " ";
		cout << " " << rowLetter; 

		// Output the players board.
		for (int colIndex = 0; colIndex < BOARD_LENGTH; ++colIndex)
		{
			// Display player fleet (showAll = false) w/ symbol conversion.
			cout << right << setw(2) << tileToSymbol(playerFleet[rowIndex][colIndex]);
		}
		// Increase rowLetter by 1. 
		++rowLetter;
		cout << endl;
	}	
}

bool placeShipHorizontally(Tile input, int shipSize, int rowOrigin, int colOrigin, Tile board[][BOARD_LENGTH])
{
	// Check if selection lies on the game board.
	if ((colOrigin + shipSize - 1 < BOARD_LENGTH && colOrigin >= 0) && 
			(rowOrigin >= 0 && rowOrigin < BOARD_LENGTH))
	{
		/* If selection lies on gameboard, check if 
		 * selection collides with other ships.
		 */
		for (int colIndex = colOrigin; colIndex < colOrigin + shipSize; ++colIndex)
		{
			// If current location isn't water... validSelection is false. 
			if (board[rowOrigin][colIndex] != WATER)
			{
				return false;
			}
		}

		for (int colIndex = colOrigin; colIndex < colOrigin + shipSize;
		++colIndex)
		{
			board[rowOrigin][colIndex] = input;
		}
		
		return true;
	}
	else
	{
		return false;
	}
}


bool placeShipVertically(Tile input, int shipSize, int rowOrigin, int colOrigin, Tile board[][BOARD_LENGTH])
{
	// Check if selection lies on the game board.
	if ((rowOrigin + shipSize - 1 < BOARD_LENGTH && rowOrigin >= 0) && 
			(colOrigin >= 0 && colOrigin < BOARD_LENGTH))
	{
		/* If selection lies on gameboard, check if 
		 * selection collides with other ships.
		 */
		for (int rowIndex = rowOrigin; rowIndex < rowOrigin + shipSize; ++rowIndex)
		{
			// If current location isn't water... validSelection is false. 
			if (board[rowIndex][colOrigin] != WATER)
			{
				return false;
			}
		}

		for (int rowIndex = rowOrigin; rowIndex < rowOrigin + shipSize; ++rowIndex)
		{
			board[rowIndex][colOrigin] = input;
		}
		
		return true;
	}
	else
	{
		return false;
	}
}


void placeShipsRandomly(Tile input[][BOARD_LENGTH])
{
	Tile defaultTile;
	
	// Set entire board to water.
	wipeBoard(input, WATER);

	for (Tile ship = AIRCRAFT_CARRIER; ship < MISS; ship = static_cast<Tile>(ship + 1))
	{
		bool shipPlaced = false;

		do
		{
			int randX = (rand() % 10);		
			int randY = (rand() % 10);

			// Place ship vertically.
			if (rand() % 2 == 1)
			{
				shipPlaced = placeShipVertically(ship, SHIP_SIZE[ship], randY, randX, input);
				//placeShipVertically(static_cast<Tile>(ship), SHIP_SIZE[sizeIndex], randY, randX, input);
			}
			// Place ship horizontally. 
			else
			{
				shipPlaced = placeShipHorizontally(ship, SHIP_SIZE[ship], randY, randX, input);
			}
		}
		while (!shipPlaced);	
	}
}


void placePlayersShips(Tile playerFleet[][BOARD_LENGTH])
{
	char input;
	bool approvedBoard;

	
	do
	{
		placeShipsRandomly(playerFleet);
		displayBoards(playerFleet, playerFleet);

		cout << "Do you want to play with this board? (y/n): ";
		cin >> input;
		cout << '\n';
		cin.ignore(INT_MAX, '\n');

		while (input != 'y' && input != 'Y' && input != 'n' && input != 'N')
		{
			cout << "Please enter 'y' or 'n': ";
			cin >> input;
			cout << endl;
			cin.ignore(INT_MAX, '\n');
		}

	} while (input == 'n' || input == 'N');	
}


string playersTurn(Tile enemyBoard[][BOARD_LENGTH], int enemyHitsRemaining[numOfPlayableBoats])
{
	// Vars to hold the user input shot location.
	Tile shot;
	string input;
	char row;
	int col;
	bool validSelection = false;

	int rowIndex;
	int colIndex;

	do
	{
		validSelection = true;

		cout << "Enter the coordinates for your shot (e.g. B2): ";
		cin >> row >> col;

		row = toupper(row);

		rowIndex = row - 'A';
		colIndex = col - 1;

		shot = enemyBoard[rowIndex][colIndex];

		if (cin.fail())
		{
			cin.clear();
			cout << "";
			validSelection = false;
		}
		else if ((rowIndex >= BOARD_LENGTH || rowIndex < 0) || 
			(colIndex < 0 || colIndex >= BOARD_LENGTH))
		{
			cout << "That selection isn't in the bounds of the game board. Try again.\n";
			validSelection = false;
		}
		else if (enemyBoard[rowIndex][colIndex] >= MISS)
		{
			cout << "You've already shot there! Try again.\n";
			validSelection = false;
		}

		cin.ignore(INT_MAX, '\n');
	
	} while (!validSelection);
	
	const Tile HITTILE = enemyBoard[rowIndex][colIndex];
	enemyBoard[rowIndex][colIndex] = static_cast<Tile>(HITTILE + MISS);
	string message = row + to_string(colIndex + 1);
	
	if (enemyBoard[rowIndex][colIndex] == MISS)
	{
		//validSelection = false;
		message += " Miss.\n";
		
	}
	else
	{
		message += " Hit!\n";

		enemyHitsRemaining[HITTILE]--;
		
		if (enemyHitsRemaining[HITTILE] == 0)
		{
			message += "  You sunk the enemy's " + shipToString(HITTILE) +
				"!\n";
		}
		//validSelection = false;
		
	}

	return message;
}


bool isAllZero(int enemyHitsRemaining[])
{
	bool isAllZero = true;

	for (int index = 0; index < 6; ++index)
	{	
		if (enemyHitsRemaining[index] != 0)
		{
			isAllZero = false;
		}
	}

	return isAllZero;
}

void displayAsIfTyped(const string& message, int msecs, int pause)
{
	msecs = 160;
	pause = 200;
	for (int current = 0; current < message.length(); ++current)
	{
		cout << message[current] << flush;

		// Wait the alloted time
		this_thread::sleep_for(chrono::milliseconds(msecs));
	}
	// Backup for next output.
		cout << "\b\b\b";

}

void randomCoordinatesAnimation()
{
	// Variables to hold random coordinates to print
	int colNumber;
	char rowLetter;

	cout << left; // left align columns

	// Repeatedly output a random coordinate, then wait, then backup to overwrite
	// The pauses increase in time exponentially until it is >= 160 msecs
	for (int msecs = 10; msecs < 160; msecs = static_cast<int>(msecs * 1.1))
	{
		// Get random numbers
		rowLetter = rand() % BOARD_LENGTH + 'A';
		colNumber = rand() % (BOARD_LENGTH) + 1;

		// Output numbers
		cout << rowLetter << setw(2) << colNumber << flush;

		// Wait the alloted time
		this_thread::sleep_for(chrono::milliseconds(msecs));

		// Backup for next output.
		cout << "\b\b\b";
	}

	cout << right; // reset alignment back to the default
}

void singlePlayer()
{
    bool validSelection;
	bool gameOver = false;
	bool playerWins;
	bool enemyWins;
	string message;

	// Player and enemy fleet data.
	Tile playerFleet[BOARD_LENGTH][BOARD_LENGTH] {WATER};
	Tile enemyFleet[BOARD_LENGTH][BOARD_LENGTH] {WATER};

	// Ship Health.
	int enemyHitsRemaining[6] = { 0, 5, 4, 3, 3, 2 };
	int playerHitsRemaining[6] = { 0, 5, 4, 3, 3, 2 };

	// Random Number Gen
	unsigned int seed = static_cast<unsigned int>(time(nullptr));
	srand(seed);

	// Initial ship placement.
	placeShipsRandomly(enemyFleet);
	placePlayersShips(playerFleet);

    do
	{
		displayBoards(playerFleet, enemyFleet);

		string currentShot = playersTurn(enemyFleet, enemyHitsRemaining);

		cout << "Your shot: ";
		displayAsIfTyped(currentShot, 1000, 1000);
		
		
		// Check if all enemy ship health has been depleated.
		if (isAllZero(enemyHitsRemaining) == true)
		{
			playerWins = true;
			gameOver;
			break;
		}
		

		// Display board and call enemy's turn.
		cout << "\b\b\b";
		displayBoards(playerFleet, enemyFleet);
		cout << "Enemy's shot: "; 
		randomCoordinatesAnimation();
		cout << EnemyAI::enemyTurn(playerFleet, playerHitsRemaining);
		
		// Check if all player ship health has been depleated. 
		
		if (isAllZero(playerHitsRemaining) == true)
		{
			enemyWins = true;
			gameOver;
			break;
		}
		
		
	
	} while (!gameOver);

	if (playerWins == true)
	{
		cout << "You've sunk all of the enemy battleships! You win!\n";
	}
	else if (enemyWins == true)
	{
		cout << "All of your battleships have sunk. You lose...\n";
	}
}

void multiplayer()
{
    bool validSelection;
	bool gameOver = false;
	bool playerWins;
	bool enemyWins;
	string message;
    string input; 

	// Player and enemy fleet data.
	Tile player1Fleet[BOARD_LENGTH][BOARD_LENGTH] {WATER};
	Tile player2Fleet[BOARD_LENGTH][BOARD_LENGTH] {WATER};

	// Ship Health.
	int player2HitsRemaining[6] = { 0, 5, 4, 3, 3, 2 };
	int player1HitsRemaining[6] = { 0, 5, 4, 3, 3, 2 };

	// Random Number Gen
	unsigned int seed = static_cast<unsigned int>(time(nullptr));
	srand(seed);

	// Initial ship placement.
    cout << "Player one, press Enter when you are ready to select your game board. (Player two, look away)";
    cin >> input;
	placePlayersShips(player1Fleet);
    cout << "Player two, press Enter when you are ready to select your game board. (Player one, look away)";
    cin >> input;
	placePlayersShips(player2Fleet);

    do
	{
        
		displayBoards(player1Fleet, player2Fleet);

		string currentShot = playersTurn(player2Fleet, player2HitsRemaining);

		cout << "Your shot: ";
		displayAsIfTyped(currentShot, 1000, 1000);
		
		
		// Check if all enemy ship health has been depleated.
		if (isAllZero(player2HitsRemaining) == true)
		{
			playerWins = true;
			gameOver;
			break;
		}
		

		// Display board and call enemy's turn.
		cout << "\b\b\b";
		displayBoards(player1Fleet, player2Fleet);
		cout << "Enemy's shot: "; 
		randomCoordinatesAnimation();
		cout << EnemyAI::enemyTurn(player1Fleet, player1HitsRemaining);
		
		// Check if all player ship health has been depleated. 
		
		if (isAllZero(player1HitsRemaining) == true)
		{
			enemyWins = true;
			gameOver;
			break;
		}
		
		
	
	} while (!gameOver);

	if (playerWins == true)
	{
		cout << "You've sunk all of the enemy battleships! You win!\n";
	}
	else if (enemyWins == true)
	{
		cout << "All of your battleships have sunk. You lose...\n";
	}
}

