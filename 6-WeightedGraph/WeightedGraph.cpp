#include "WeightedGraph.h"
// arrayIndex = row * maxSize + col

/** Constructor
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
WeightedGraph::WeightedGraph( int maxNumber )
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[ maxSize ];
	adjMatrix = new int[ maxSize * maxSize ];
	pathMatrix = new int[ maxSize * maxSize ];

	// Initialize adjacency matrix
	for( int i = 0; i < (maxSize * maxSize); i++ )
	{
		adjMatrix[ i ] = INFINITE_EDGE_WT;
	}
}

/** Copy Constructor
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
WeightedGraph::WeightedGraph( const WeightedGraph& other )
{
	maxSize  = other.maxSize;
	size = other.size;
	vertexList = new Vertex[ maxSize ];
	adjMatrix = new int[ maxSize * maxSize ];
	*this = other;
}

/** Overloaded Assignment Operator
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
WeightedGraph& WeightedGraph::operator=( const WeightedGraph& other )
{
	if( this != &other )
	{
		int i, j;

		// Reallocate if necessary
		if( maxSize != other.maxSize )
		{
			delete []vertexList;
			delete []adjMatrix;
			delete []pathMatrix;
			maxSize = other.maxSize;
			vertexList = new Vertex[ maxSize ];
			adjMatrix = new int[ maxSize * maxSize ]; 
			pathMatrix = new int[ maxSize * maxSize ];
		}
		size = other.size;

		// Copy data
		for( i = 0; i < size; i++ )
		{
			// Copy vertices
			vertexList[ i ] = other.vertexList[ i ];
			// Copy adjacency matrix
			for( j = 0; j < size; j++ )
			{
				adjMatrix[ i * maxSize + j ] = adjMatrix[ i * maxSize + j ];
				pathMatrix[ i * maxSize + j ] = adjMatrix[ i * maxSize + j ];
			}
		}

	}

	return *this;
}

/** Destructor
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
WeightedGraph::~WeightedGraph()
{
	clear();
	if( vertexList != NULL )
	{
		delete []vertexList;
		vertexList = NULL;
	}
	if( adjMatrix != NULL )
	{
		delete []adjMatrix;
		adjMatrix = NULL;
	}
	if( pathMatrix != NULL )
	{
		delete []pathMatrix;
		pathMatrix = NULL;
	}
	size = 0;
	maxSize = 0;
}

/** Insert Vertex
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::insertVertex( const Vertex& newVertex ) throw ( logic_error )
{
	if( isFull() )
	{
		throw logic_error( "Graph is full" );
	}

	bool found = false;
	int i = getIndex( newVertex.getLabel() );
	if( i < size )
	{
		vertexList[ i ] = newVertex;

		// Update edges to infinite
		for( int j = 0; j < size; j++ )
		{
			adjMatrix[ j * maxSize + i ] = INFINITE_EDGE_WT;
			adjMatrix[ i * maxSize + j ] = INFINITE_EDGE_WT;
		}
		
	}
	else
	{
		vertexList[ size ] = newVertex;

		// Edge to itself is 0
		setEdge( size, size, 0 );
		size++;

	}
}

/** Insert Edge
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::insertEdge( const string& v1, const string& v2, int wt ) throw ( logic_error )
{
	// Look for v1 and v2
	int index1, index2;
	index1 = getIndex( v1 );
	index2 = getIndex( v2 );

	// if not found, throw logic error
	if( index1 >= size || index2 >= size )
	{
		throw logic_error( "Graph does not include vertices" );
	}

	// update edge weight
	setEdge( index1, index2, wt );
	setEdge( index2, index1, wt );
}

/** Retrieve Vertex
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
bool WeightedGraph::retrieveVertex( const string& v, Vertex& vData ) const
{
	int i = getIndex( v );
	if( i >= size )
	{
		return false;
	}
	vData = vertexList[ i ];
	return true; 
}

/** Get Edge Weight
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
bool WeightedGraph::getEdgeWeight( const string& v1, const string& v2, int& wt ) const throw ( logic_error )
{
	// Look for v1 and v2
	int index1, index2;
	index1 = getIndex( v1 );
	index2 = getIndex( v2 );

	// if not found, throw logic error
	if( index1 >= size || index2 >= size )
	{
		throw logic_error( "Graph does not include vertices" );
	}
	if( getEdge( index1, index2 ) == INFINITE_EDGE_WT )
	{
		return false;
	}
	wt = getEdge( index1, index2 );
	return true;
}

/** Remove Vertex
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::removeVertex( const string& v ) throw ( logic_error )
{
	int i = getIndex( v );
	int row, col,j;
	if( i >= size )
	{
		throw logic_error( "Graph does not include vertex" );
	}
	// Shift adjacency matrix
	for( j = i; j < size - 1; j++ )
	{
		vertexList[ j ] = vertexList[ j + 1 ];
	}
	// Shift up rows
	for( col = 0; col < size; col++ )
	{
		for( row = i; row < size - 1; row++ )
		{
			adjMatrix[ row * maxSize + col ] = adjMatrix[ (row + 1) * maxSize + col ];
		}
	}
	// Shift over columns
	for( row = 0; row < size; row++ )
	{
		for( col = i; col < size - 1; col++ )
		{
			adjMatrix[ row * maxSize + col ] = adjMatrix[ row * maxSize + (col+1) ];
		}
	}
	size--;
}

/** Remove Edge
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::removeEdge( const string& v1, const string& v2 ) throw ( logic_error )
{ 
	// Look for v1 and v2
	int index1, index2;
	index1 = getIndex( v1 );
	index2 = getIndex( v2 );

	// if not found, throw logic error
	if( index1 >= size || index2 >= size )
	{
		throw logic_error( "Graph does not include vertices" );
	}
	setEdge( index1, index2, INFINITE_EDGE_WT );
	setEdge( index2, index1, INFINITE_EDGE_WT );
}

/** Clear
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::clear()
{
	size = 0;
	for( int i = 0; i < maxSize * maxSize; i++ )
	{
		adjMatrix[ i ] = INFINITE_EDGE_WT;
	}
}

/** Is Empty
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
bool WeightedGraph::isEmpty() const
{
	return( size == 0 );
}

/** Is Full
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
bool WeightedGraph::isFull() const
{
	return( size == maxSize );
}

/** Show Structure
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph:: showStructure () const
// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.
{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
#if LAB12_TEST2
		<< vertexList[row].getColor()
#endif
		<< endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}

/** Show Shortest Paths
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::showShortestPaths() const
{
	int i;
	int jm, mk, jk;
	// Copy adjacencu matrix to path matrix
	for( i = 0; i < maxSize * maxSize; i++ )
	{
		pathMatrix[ i ] = adjMatrix[ i ];
	}

	// Set diagonals to zero
	for( i = 0; i < maxSize; i++ )
	{
		setPath( i, i, 0 );
	}
	for( int m = 0; m < size; m++ )
	{
		for( int j = 0; j < size; j++ )
		{
			for( int k = 0; k < size; k++ )
			{
				jm = getPath( j, m );
				mk = getPath( m, k );

				if( jm != INFINITE_EDGE_WT && 
					mk != INFINITE_EDGE_WT )
				{
					jk = getPath( j, k );
					if( jm + mk < jk && jk != 0 )
					{
						setPath( j, k, jm + mk );
					}
				}
			}
		}
	}

	cout << endl << "Path matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
}

/** Has Proper Coloring
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
bool WeightedGraph::hasProperColoring() const
{
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size; j++ )
		{
			// Find connection
			if( adjMatrix[ i * maxSize + j ] != 0 && adjMatrix[ i * maxSize + j ] == INFINITE_EDGE_WT )
			{
				if( vertexList[ i ].getColor() == vertexList[ j ].getColor() )
				{
					return false;
				}
			}
		}
	}
	return true;
}

/** Are All Even
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
bool WeightedGraph::areAllEven() const
{

}

/** Get Index
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
int WeightedGraph::getIndex( const string& v ) const
// Returns the adjacency matrix index for vertex v. Returns size if
// the vertex does not exist.
{
    int j;  // Loop counter

    for ( j = 0 ;
          j < size  &&  strcmp(vertexList[j].getLabel().c_str(), v.c_str() ) != 0 ;
          j++ );
    return j;
}

/** Get Edge
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
int WeightedGraph::getEdge( int row, int col ) const
{
	if( row < maxSize && col < maxSize )
	{
		return ( adjMatrix[ row * maxSize + col ] );
	}
}

/** Set Edge
*
* Description
* @b Algorithm
* -#
* -#
* @param
* @pre
* -#
* @post
* -#
* @return
* @exception
*/
void WeightedGraph::setEdge( int row, int col, int wt )
{
	if( row < maxSize && col < maxSize )
	{
		adjMatrix[ row * maxSize + col ] = wt;
	}
}


int WeightedGraph::getPath( int row, int col ) const
{
	return pathMatrix[ row * maxSize + col ];
}

void WeightedGraph::setPath( int row, int col, int wt ) const
{
	if( row < maxSize && col < maxSize )
	{
		pathMatrix[ row * maxSize + col ] = wt;
	}
}

