#include <iostream>

using namespace std;

// Function Prototypes
int gardRows, gardCols;
int locatePatches( char**, int**, int&, int&, int& );

// Main Function
int main()
{
	// Initialize variables

	char vegetable;
	int gardNum = 1, patchNum;
	int numPatchesFound = 0, currentPatchSize = 0;
	int row, col;
	// Get first garden dimensions
	cin >> gardRows >> gardCols;

	// Loop until end of gardens
	while( gardRows != 0 && gardCols != 0 )
	{

		// Create two arrays for garden

		// Create two dimensional array containing vegetable characters
		char** garden = new char*[gardRows];
		for( row = 0; row < gardRows; row++ )
			garden[row] = new char[ gardCols ];
		
		// Create two dimensional array containing integers
		int** patchMap = new int*[gardRows];
		for( row = 0; row < gardRows; row++ )
			patchMap[row] = new int[gardCols];

			// Loop through both dimensions
			for( row = 0; row < gardRows; row++ )
			{
				for( col = 0; col < gardCols; col++ )
				{
					// Read in vegetable characters
					cin >> garden[row][col];
					cout << garden[row][col];

					// Initialize values in patch map to -1, corresponding to not checked
					patchMap[row][col] = -1;
				}
				cout << endl;

			}

		row = col = 0;
		// Determine patches
		locatePatches( garden, patchMap, row, col, numPatchesFound );

		// Create array for patch size
		// Size is plus 1 because patch numbers start at 1
		int patchSizes[numPatchesFound+1];

		// Loop through each patch number
		for( patchNum = 1; patchNum <= numPatchesFound; patchNum++ )
		{
			// Loop through both dimensions
			for( int row = 0; row < gardRows; row++ )
			{
				for( int col = 0; col < gardCols; col++ )
				{
					// Count number in patch
					if( patchMap[row][col] == patchNum )
						currentPatchSize++;

				}

			}
			patchSizes[ patchNum ] = currentPatchSize;
			currentPatchSize = 0;
			
		}

		// Output information
		cout << "Garden # " << gardNum << ": ";
		cout << numPatchesFound << " patches, sizes: ";
		for( int i = 1; i <= numPatchesFound; i++ )
		{
			cout << patchSizes[i] << ' ';
		}
		cout << endl;

		// Get height and width of next garden
		delete []garden;
		gardNum++;
		cin >> gardRows >> gardCols;

	}

	// Return success
	return 0;
}

int locatePatches( char** garden, int** patches, int &yVal, int &xVal, int &numPatches )
{
	if( yVal < gardRows && xVal < gardCols )
	{
		// If home location is a pumpkin
		if( garden[yVal][xVal] == 'p' )
		{


		}
		// If at end of row, go to start of next row
		else if( xVal == gardCols - 1 )
		{
			xVal = 0;
			yVal++;
		}
	}
	
	if( yVal == gardRows && xVal == gardCols )
		return 0;
}

