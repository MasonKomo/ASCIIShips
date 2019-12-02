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