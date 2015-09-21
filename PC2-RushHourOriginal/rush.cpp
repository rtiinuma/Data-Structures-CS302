#include <iostream>
using namespace std;

struct car{
	public:
	int carNumber;
	int length;
	char orientation;
	int row;
	int column;

};

// Global variable
int minMoves = 16;
int numCars;

// Function Prototypes
void readIn( int lot[ 6 ][ 6 ], car* carArray );

void solvePuzzle( int lot[ 6 ][ 6 ], car* carArray, int numMoves );

bool moveCar( char dir, int lot[ 6 ][ 6 ], car &currentCar );

// Main Function
int main()
{
	// Initialize variables
	int index, row, col, numMoves = 0;
	int carLot[6][6];
	int scenarioNum = 1;
	car* carArray;

	// Read in number of cars
	cin >> numCars;
	carArray = new car[numCars + 1];

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
		// Read in cars
		readIn( carLot, carArray );

		// Output to test
		for( row = 0; row < 6; row++ )
		{
			for( col = 0; col < 6; col++ )
			{
				if( carLot[ row ][ col ] != -1 )
					cout << ' ';
				cout << carLot[ row ][ col ];
				cout << ' ';
			}
			cout << endl;
		}
cout << endl;
		// Solve puzzle
		solvePuzzle( carLot, carArray, numMoves );

		// Output to test
		/*for( row = 0; row < 6; row++ )
		{
			for( col = 0; col < 6; col++ )
			{
				if( carLot[ row ][ col ] != -1 )
					cout << ' ';
				cout << carLot[ row ][ col ];
				cout << ' ';
			}
			cout << endl;
		}*/

		// Ouput results
		cout << "Scenario " << scenarioNum << " requires " << minMoves << " moves" << endl;

		// Get number of cars for next scenario
		cin >> numCars;
		scenarioNum++;
		numMoves = 0;
		minMoves = 10;
	}

	return 0;
}

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
		carArray[ currentNum ].carNumber = currentNum;
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

void solvePuzzle( int lot[ 6 ][ 6 ], car* carArray, int numMoves )
{

	car* temp = carArray;

	// If we have won
	if( (*temp).column == 4 )
	{

		if( numMoves < minMoves )
		{
			minMoves = numMoves;
		}
	}

	// Otherwise, if we have not reached the bound
	else if( numMoves < minMoves )
	{
		for( int i = 0; i < numCars; i++ )
		{
			temp = carArray;
			for( int j = 0; j < i; j++ )
			{
				temp++;
			}
			if( moveCar( 'F', lot, *temp ) )
			{

				solvePuzzle( lot, carArray, numMoves + 1 );
				moveCar( 'R', lot, *temp );

			}

			if( moveCar( 'R', lot, *temp ) )
			{

				solvePuzzle( lot, carArray, numMoves + 1 );
				moveCar( 'F', lot, *temp );
			}
		}
	}



}

bool moveCar( char dir, int lot[ 6 ][ 6 ], car &carA )
{
	// If car is horizontal
	if( carA.orientation == 'H' )
	{

		if( dir == 'F' && carA.column + carA.length < 6  )
		{
			if( lot[ carA.row ][ carA.column + carA.length ] == -1 )
			{
				lot[ carA.row ][ carA.column + carA.length ] = carA.carNumber;
				lot[ carA.row ][ carA.column ] = -1;
				carA.column += 1;
				return true;
			}
			return false;
		}
		else if( dir == 'R' && carA.column - 1 >= 0 )
		{
			if( lot[ carA.row ][ carA.column - 1 ] == -1 )
			{
				lot[ carA.row ][ carA.column - 1 ] = carA.carNumber;
				lot[ carA.row ][carA.column + carA.length - 1 ] = -1;
				carA.column -= 1;
				return true;
			}
			return false;
		}
		return false;

		
	}
	// Otherwise assume car is vertical
	else if( carA.orientation == 'V' )
	{

		if( dir == 'F' && carA.row + carA.length < 6 )
		{
			if( lot[ carA.row + carA.length ][ carA.column ] == -1 )
			{
				lot[ carA.row + carA.length ][ carA.column ] = carA.carNumber;
				lot[ carA.row ][ carA.column ] = -1;
				carA.row++;
				return true;
			}
			return false;
		}
		else if( dir == 'R' && carA.row - 1 >= 0 )
		{
			if( lot[ carA.row - 1 ][ carA.column ] == -1 )
			{
				lot[ carA.row - 1 ][ carA.column ] = carA.carNumber;
				lot[ carA.row + carA.length - 1 ][ carA.column ] = -1;
				carA.row -= 1;
				return true;
			}
			return false;
		}
		return false;
		
	}
	return false;
}
