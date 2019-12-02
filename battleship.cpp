/**
 *  Battleships
 *  A game that involves trying to guess the location of
 *  and sink all enemy ships before your ships are destroyed.
 * 
 *  By Mason C. Bradford and Dr. Hayes
 */

// Include headers
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
#include "functions.h"

int main()
{
	int input; 


    // Display Main Menu
	cout << endl;
    cout << setw(40) << "      Welcome to ASCIIships! An ASCII game of navel war!\n\n";


	cout << "                         |>\n";
	cout << "                    _____|__\n";
	cout << "                   |_______/\n";
	cout << "         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << setw(40) << "Choose an option below. (input the corresponding number)\n\n";

    cout << "1. - Single player\n";
    cout << "2. - Local Multiplayer\n";
    cout << "3. - Settings\n";
    cout << "4. - Quit\n";

	cin >> input;

    // Get User Input
    switch (input)
    {
        case 1: 
			singlePlayer();
		case 2: 
			multiplayer();
		//case 3: 
		//	settings();
		//case 4; 
		//	return 0;
		default:
			cout << "Please choose an option 1-4";
    }
	

	return 0;

}

