/**

@file rush.cpp

@author Renee Iinuma

*/

/**
* @mainpage PC2 - Rush Hour
* This program takes input from the console to solve any number of scenarios of rush hour. 
* The number of moves required to solve each scenario is then displayed. 
* This program caps the maximum number of moves to 10.
* @n @n
* The main program works as follows (Loops while number of cars is not 0):
* -# Initializes arrays with car information.
* -# Calls readIn function to read in car information.
* -# Calls solvePuzzle function to determine minimum number of moves.
* -# Outputs results of current scenario.
* -# Resets values and gets number of cars for the next scenario.
*/

// Header Files
#include <string>
#include <queue>
#include <map>
#include <iostream>
using namespace std;

/**
* @struct car
* @brief Car struct contains integer data members of the car's number, length, row and column location, and a character of the car's orientation.
* @var car::number 
* Integer data member 'number' designates the number of the car which is determined from input.
* @var car::length
* Integer data member 'length' designates the length of the car, which is either 2 or 3 units.
* @var car::orientation
* Character data member 'orientation' designates the orientation of the car, which is either 'H' for horizontal or 'V' for vertical.
* @var car::row
* Integer data member 'row' designates the row of the north most unit of the car.
* @var car::column
* Integer data member 'column' designates the column of the west most unit of the car.
*/
struct car{
	public:
	int number;
	int length;
	char orientation;
	int row;
	int column;

};

// Global variables
/**
* @var minMoves
* Integer variable 'minMoves' is a global variable indicating the current minimum number of moves required to solve the current puzzle.
* @var numCars
* Integer variable 'numCars' is a global variable indicating the number of cars for the current puzzle. This is updated each time a new scenario is input.
*/
int numCars;

// Function Prototypes
void readIn( int lot[ 6 ][ 6 ], car* carArray );

int solvePuzzle( int lot[ 6 ][ 6 ], car* carArray );

bool moveCar( char dir, int lot[ 6 ][ 6 ], car &currentCar );

void boardToString( int lot[ 6 ][ 6 ], string &boardstr );

void stringToBoard( string boardstr, int lot[ 6 ][ 6 ], car* carArray );


// Main Function
int main()
{
	// Initialize variables
	int index, row, col, minMoves;
	int carLot[6][6];
	int scenarioNum = 1;
	car* carArray;

	// Read in number of cars
	cin >> numCars;

	while( numCars != 0 )
	{

		// Initialize array
		for( row = 0; row < 6; row++ )
		{
			for( col = 0; col < 6; col++ )
			{
				carLot[ row ][ col ] = -1;
			}
		}
		carArray = new car[numCars + 1];

		// Read in cars
		readIn( carLot, carArray );

		// Solve puzzle
		minMoves = solvePuzzle( carLot, carArray );

		// Ouput results
		if( minMoves == -1 )
		{
			cout << "Scenario " << scenarioNum << " is unsolvable." << endl;
		}
		else
		{
			cout << "Scenario " << scenarioNum << " requires " << minMoves << " moves" << endl;
		}
		// Get number of cars for next scenario
		cin >> numCars;

		// Update or reset variable values
		scenarioNum++;
		delete []carArray;
	}

	return 0;
}

/**
* Function reads in information from the console and stores information.
*
* Function loops for each car based on number of cars from input. Information for each car is stored in the array of car structs, and then placed in the lot array.
@param lot Integer array parameter contains the layout of all of the cars for the current puzzle, with numbers designating the cars and -1 designating an empty space. This is updated in the function.
@param carArray Array of car structs which contains all of the information for each car. This is updated in the function.
@pre 
* -# Lot must be declared and cleared (all -1). 
* -# carArray must have memory allocated of the proper size.
@post 
* -# Lot array and car array will be updated with all of the input cars' information.
* -# Lot array and car array will still have memory allocated.
@code
@endcode
*/

void readIn( int lot[ 6 ][ 6 ], car* carArray )
{
	int currentNum = 0;
	int size, xVal, yVal, index;
	char orient;

	while( currentNum < numCars )
	{
		// Get car information from input
		cin >> size >> orient >> yVal >> xVal;

		// Set values of current car
		carArray[ currentNum ].number = currentNum;
		carArray[ currentNum ].length = size;
		carArray[ currentNum ].orientation = orient;
		carArray[ currentNum ].row = yVal;
		carArray[ currentNum ].column = xVal;

		// Place in array
		if( orient == 'H' )
		{
			for( index = 0; index < size; index++ )
			{
				lot[ yVal ][ xVal ] = currentNum;
				xVal++;
			}
		}
		else
		{
			for( index = 0; index < size; index++ )
			{
				lot[ yVal ][ xVal ] = currentNum;
				yVal++;
			}
		}
		currentNum++;
	}

}


/**
* Recursive function solvePuzzle which calculates minimum number of moves required to solve the current puzzle.
*
* Function determines whether the winning condition has been met. This means that the location of Car0 is in the right-most side of the array. If not, function determines whether the minimum moves have been met. Function recursively calls itself until game is solved or bound (current minimum number of moves) is reached.
@param lot Integer array parameter contains the layout of all of the cars for the current puzzle, with numbers designating the cars and -1 designating an empty space. 
@param carArray Array of car structs which contains all of the information for each car. 
@param numMoves Integer which contains the current number of moves which have been made while attempting to solve the puzzle.
@pre 
* -# Lot must be declared and car locations designated in array.
* -# carArray must have memory allocated of the proper size. Information for each car in the puzzle must be stored.
* -# minMoves must have a current value less than or equal to 10.
@post 
* -# minMoves may be updated if puzzle was solved with a fewer number of moves.
@code
@endcode
*/

int solvePuzzle( int lot[ 6 ][ 6 ], car* carArray )
{
	queue<string> carQ;
	map<string, int> dejavu;
	string boardstring, temp;
	bool solved = false;
	map<string, int>::iterator itr;
	int moves = 0;

	boardToString( lot, boardstring );
	carQ.push( boardstring );

	while( !solved && !carQ.empty() )
	{
				
		temp = carQ.front();
		carQ.pop();
		stringToBoard( temp, lot, carArray );

		for( int row = 0; row < 6; row++ )
		{
			if( lot[row][5] == 0 )
			{
				itr = dejavu.find( temp );
				moves = dejavu[ temp ];
				solved = true;	
			}
		}
		for( int row = 0; row < 6; row++ )
				{
					for( int col = 0; col < 6; col++ )
					{
						cout << lot[row][col];
					}
					cout << endl;
				}
		boardToString( lot, temp );
		//itr = dejavu.find( temp );

		// If not seen
		if( dejavu.count( temp ) == 0 )
		{

			for( int i = 0; i < numCars; i ++ )
			{
				
				if( moveCar( 'F', lot, carArray[i] ) )
				{
					moves++;
					boardToString( lot, boardstring );
					carQ.push( boardstring );
					dejavu[ boardstring] = moves;
					moveCar( 'R', lot, carArray[i] );

				}

				if( moveCar( 'R', lot, carArray[i] ) )
				{
					moves++;
					boardToString( lot, boardstring );
					carQ.push( boardstring );
					dejavu[ boardstring] = moves;
					moveCar( 'F', lot, carArray[i] );

				}
			}

		}

	}
	
	if( !solved )
		moves = -1;

	return moves;

}

/**
* Function moveCar moves the designated car in the designated direction.
*
* Function updates the integer lot array and information of car object if a move is possible. First checks orientation of the given car. Then checks if moving it in the given direction will make any unit of the car go out of bounds of the lot. Then checks if there is a different car in the way. Returns false for these conditions. If not, then lot array and car information is updated and car is moved in the designated direction.
@param dir Character parameter which designates the desired direction of movement for the car. 'F' corresponds to a forward movement and 'R' corresponds to a reverse movement.
@param lot Integer array parameter contains the layout of all of the cars for the current puzzle, with numbers designating the cars and -1 designating an empty space. 
@param carA Current car which is to be moved, passed by reference so location information (row and column) may be updated. 
@pre 
* -# Lot must be declared and car locations designated in array.
* -# Given direction should be either 'F' or 'R'.
* -# Given car must have accurate information of orientation, length, row, and column.
@post 
* -# If successful, lot will be updated with car's movement. Row or column of car will also be updated to reflect movement.
* -# If not successful, lot and car should be unchanged after function call. 
@returns 
* -# True if move was completed successfully.
* -# False if car would go out of bounds or there was a different car in the way.
@code
@endcode
*/

bool moveCar( char dir, int lot[ 6 ][ 6 ], car &carA )
{
	// If car is horizontal
	if( carA.orientation == 'H' )
	{
		// If direction is 'Forward' then check if it will go out of bounds
		if( dir == 'F' && carA.column + carA.length < 6  )
		{
			// If not out of bounds, check if the next space is empty
			if( lot[ carA.row ][ carA.column + carA.length ] == -1 )
			{
				// If next space to the right is empty, then move car by updating lot array and car object
				lot[ carA.row ][ carA.column + carA.length ] = carA.number;
				lot[ carA.row ][ carA.column ] = -1;
				carA.column += 1;
				return true;
			}
			// Otherwise, there is a car in the way, return false
			return false;
		}
		// Otherwise, if direction is 'Reverse' then check if it will go out of bounds
		else if( dir == 'R' && carA.column - 1 >= 0 )
		{
			// If not out of bounds, check if the next space is empty
			if( lot[ carA.row ][ carA.column - 1 ] == -1 )
			{
				// If next space to the left is empty, then move car by updating lot array and car object
				lot[ carA.row ][ carA.column - 1 ] = carA.number;
				lot[ carA.row ][carA.column + carA.length - 1 ] = -1;
				carA.column -= 1;
				return true;
			}
			// Otherwise, there is a car in the way, return false
			return false;
		}
		// Otherwise, car would go out of bounds, return false
		return false;

	}
	// Otherwise, if car is vertical
	else if( carA.orientation == 'V' )
	{
		// If direction is 'Forward' then check if it will go out of bounds
		if( dir == 'F' && carA.row + carA.length < 6 )
		{
			// If not out of bounds, check if the next space is empty
			if( lot[ carA.row + carA.length ][ carA.column ] == -1 )
			{
				// If next space down is empty, then move car by updating lot array and car object
				lot[ carA.row + carA.length ][ carA.column ] = carA.number;
				lot[ carA.row ][ carA.column ] = -1;
				carA.row++;
				return true;
			}
			// Otherwise, there is a car in the way, return false
			return false;
		}
		// Otherwise, if direction is 'Reverse' then check if it will go out of bounds
		else if( dir == 'R' && carA.row - 1 >= 0 )
		{
			// If not out of bounds, check if the next space is empty
			if( lot[ carA.row - 1 ][ carA.column ] == -1 )
			{
				// If next space to up is empty, then move car by updating lot array and car object
				lot[ carA.row - 1 ][ carA.column ] = carA.number;
				lot[ carA.row + carA.length - 1 ][ carA.column ] = -1;
				carA.row -= 1;
				return true;
			}
			// Otherwise, there is a car in the way, return false
			return false;
		}
		// Otherwise, car would go out of bounds, return false
		return false;
		
	}
}

void boardToString( int lot[ 6 ][ 6 ], string &boardstr )
{// arrayIndex = row * maxSize + col
	char temp[ 37 ];
	for( int row = 0; row < 6; row++ )
	{
		for( int col = 0; col < 6; col++ )
		{
			temp[ row * 6 + col ] =  lot[row][col] + '0';
		}
	}
	temp[ 36 ] = '\0';

	string str( temp );
	boardstr = str;
}

void stringToBoard( string boardstr, int lot[ 6 ][ 6 ], car* carArray )
{
	const char* temp = boardstr.c_str();
	bool found = false;
	int row, col;
	for( row = 0; row < 6; row++ )
	{
		for( col = 0; col < 6; col++ )
		{
			lot[row][col] = temp[ row * 6 + col ] - '0';
		}
	}
	row = 0;
	col = 0;
	for( int cnum = 0; cnum < numCars; cnum++ )
	{
		for( row = 0; row < 6; row++ )
		{
			for( col = 0; col < 6; col++ )
			{
				if( !found )
				{
					if( lot[row][col] == cnum )
					{
						carArray[ cnum ].row = row;
						carArray[ cnum ].column = col;
						found = true;
					}
				}
			
			}
		}
		found = false;
	}
	
/*
	for( int row = 0; row < 6; row++ )
	{
		for( int col = 0; col < 6; col++ )
		{
			cout << lot[row][col];
		}
		cout << endl;
	}
*/
}
