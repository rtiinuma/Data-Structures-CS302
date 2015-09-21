/*
* 

*/ 


#include "Heap.h"

/** Default Constructor
*
* Default constructor which creats an empty heap. Allocates memory for heap of given size.
*
* @b Algorithm
* -# Set maxSize equal to maxNumber.
* -# Set size to 0 to designate empty heap.
* -# Allocate array of size maxSize and assign dataItems to point to this array.
*
* @pre
* -# Function must be called with valid integer for maxNumber.
*
* @post
* -# All data members will be updated.
* -# dataItems will now have memory allocated to it.
*
* @param maxNumber Integer variable designating size of heap. This integer has a default value of Default_Max_Heap_Size = 10.
*
* @return None
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType,KeyType,Comparator>::Heap( int maxNumber )
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[ maxSize ];
}

/** Copy Constructor
*
* Copy constructor initializes a heap which will be set to a deep copy of the given heap from the parameter.
*
* @b Algorithm
* -# Set all data members equal to equivalent data members of other heap.
* -# Allocate memory for dataItems of array of DataType with size maxSize.
* -# Assign current heap to other heap.
*
* @pre
* -# Function must be called with valid heap as parameter.
*
* @post
* -# All data members of current heap will be updated.
* -# dataItems will have memory allocated to it.
* -# Contents of dataItems will be equivalent to dataitems of other heap.
*
* @param other Heap object to be copied to current heap.
*
* @return None
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType,KeyType,Comparator>::Heap( const Heap &other )
{
	maxSize = other.maxSize;
	size = other.size;
	dataItems = new DataType[ maxSize ];
	*this = other;
}

/** Overloaded assignment operator
*
* Overloaded assignment operator which sets the current heap to be a deep copy of the other heap. Returns current heap object.
*
* @b Algorithm
* -# Check if current object has the same address of other heap.
* -# If not, check if maxSize of current heap is different from other maxSize.
* -# If it is, then set maxSize equal to maxSize of other heap.
* -# Deallocate memory allocated to dataItems.
* -# Reallocate memory of new size.
* -# Set actual size equal to actual size of other heap.
* -# Iterate through other heap and copy contents to current heap.
* -# Return current heap.
*
* @pre
* -# Function must be called with valid heap object as parameter.
* -# Other heap object must be previously initialized and have memory allocated to it.
* -# Current heap object must be previously initialized and have memory allocated to it.
*
* @post
* -# Current heap will be updated to be a deep copy of other heap.
* -# Other heap will be unchanged.
*
* @param other Heap object to be copied to current heap.
*
* @return Heap object of current heap.
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=( const Heap &other )
{
	if( this != &other )
	{
		if( maxSize != other.maxSize )
		{
			maxSize = other.maxSize;
			delete []dataItems;
			dataItems = new DataType[ maxSize ];
		}
		size = other.size;
		for( int i = 0; i < size; i++ )
		{
			dataItems[i] = other.dataItems[i];
		}
	}
	return *this;
}

/** Destructor
*
* Deallocates the memory used to store the heap. Resets other data members to indicate an empty heap.
*
* @b Algorithm
* -# If dataItems has memory allocated to it, deallocate this memory.
* -# Set maxSize and actual size to zero.
*
* @pre
* -# Heap must be initialized and should have memory allocated to it.
*
* @post
* -# Heap will no longer have memory allocated to it.
* -# Data members will be updated to indicate empty heap.
*
* @param None
*
* @return None
*
* @exception None
*/

template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
	if( dataItems != NULL )
	{
		delete []dataItems;
		dataItems = NULL;
	}
	maxSize = 0;
	size = 0;
}


/** Insert
*
* Function inserts the given data item into the heap and rearranges the heap if necessary. 
*
* @b Algorithm
* -# Checks if heap is full. If it is, throw logic error indicating a full heap.
* -# Otherwise, places new item at the next empty space of the heap.
* -# Finds the parent of this element.
* -# Loop while the priority of the item is greater than its parent.
* -# If it is, then swap the parent and the child. Set the parent index to be the child index. Find the new parent index for this child.
* -# Increment size to indicate the successful addition of the new data item.
*
* @pre
* -# Heap must be declared and have memory allocated to it.
* -# Functions isFull, parent, and comparator must be properly functioning.
*
* @post
* -# Heap will be updated with new data item in the correct location in the heap.
* -# Other elements in the heap may be rearranged to maintain the qualities of the heap.
*
* @param newDataitem Parameter of DataType to be added into the heap.
*
* @return None
*
* @exception logic_error Throws exception if trying to insert the new data item into a full heap.
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert( const DataType &newDataItem ) throw( logic_error )
{
	if( !isFull() )
	{
		int index = size;

		// Place in array at bottom of heap
		dataItems[ index ] = newDataItem;
		int pIndex = parent( index );

		// If not the first elemet
		if( pIndex != -1 )
		{
			// Loop while the parent is less than the child
			while( comparator( dataItems[ index ].getPriority(), dataItems[ pIndex ].getPriority() ) )
			{
				// Swap parent and child
				DataType temp = dataItems[ pIndex ];
				dataItems[ pIndex ] = dataItems[ index ];
				dataItems[ index ] = temp;

				index = pIndex;
				pIndex = parent( index );
				// Set parent and child to the same so comparison will fail and loop will end
				if( pIndex == -1 )
				{
					pIndex = index;
				}
			}
		}
		size++;
	}
	else
	{
		throw logic_error( "Heap is Full" );
	}
}


/** Remove
*
* Function removes the item with the largest priority from the heap. The heap is then rearranged so that the next largest item is at the top of the heap, and the other elements in the heap maintain the proper relationships.
*
* @b Algorithm
* -# Check if heap is empty. If it it is, then throw logic error indicating empty heap.
* -# Otherwise, then set the return item as the first (highest priority) element in the heap.
* -# Overwrite the first item with the last item.
* -# Decrement the size to indicate an item has been removed.
* -# Get the indicies of the parent, right, and left child.
* -# Loop while swap flag is high.
* -# If left and right children are out of bounds, parent is a leaf and no swapping is necessary.
* -# Otherwise, if the right child is out of bounds, parent only has left child. Find the larger priority of left child and parent and set item's index as index of largest.
* -# Otherwise, both are in bounds and parent has two children. First find larger of left and right children. Then find larger between this child and the parent. Set this item's index as index of the largest.
* -# Swap the parent with the item at largest index.
* -# If the largest index is the index of the parent, then set swap flag low. Further swapping is not necessary.
* -# Return the item with the original highest priority.
*
* @pre
* -# Heap must be declared and have memory allocated to it.
* -# Functions isEmpty, rchild, lchild, and comparator must be properly functioning.
*
* @post
* -# Largest priority item will be removed from the heap.
* -# Heap will then be rearranged to maintain qualities of the heap.
*
* @param None
*
* @return Item of DataType with the highest priority is returned.
*
* @exception logic_error Exception is thrown if trying to remove a data item from an empty list
*/
template <typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove () throw ( logic_error )
{
	// Initialize variables
	int rIndex, lIndex, largest;
	int pIndex = size;
	DataType temp;
	bool swap = true;

	if( !isEmpty() )
	{
		// Set return item as first item
		DataType returnItem = dataItems[0];

		// Overwrite first item with last item
		dataItems[ 0 ] = dataItems[ size - 1];
		size--;

		pIndex = 0;
		rIndex = rchild( pIndex );
		lIndex = lchild( pIndex);

		while( swap == true )
		{
			// Find index of largest
			// If no children in bounds
			if( rIndex >= size && lIndex >=size )
			{
				largest = pIndex;
				swap = false;
			}
			// If only left child
			else if( rIndex >= size )
			{
				largest = pIndex;
				// If parent is larger
				if( comparator( dataItems[ lIndex ].getPriority(), dataItems[ pIndex ].getPriority() ) )
				{
					largest = lIndex;
				}
			}
			// If left and right child
			else
			{
				// Set largest as left child
				largest = lIndex;
				// If right child is greater, then change largest to right
				if( comparator( dataItems[ rIndex ].getPriority(), dataItems[ lIndex ].getPriority() ) )
				{
					largest = rIndex;
				}
				if( comparator( dataItems[ pIndex ].getPriority(), dataItems[ largest ].getPriority() ) )
				{
					largest = pIndex;
				}
			}
			// Swap parent and largest
			temp = dataItems[ largest ];
			dataItems[ largest ] = dataItems[ pIndex ];
			dataItems[ pIndex ] = temp;

			// Stop looping if parent is the largest
			if( largest == pIndex )
				swap = false;
			pIndex = largest;
			rIndex = rchild( pIndex );
			lIndex = lchild( pIndex);
		}

		return returnItem;

	}
	else
	{
		throw logic_error( "Heap is Empty" );
	}
}

/** Clear
*
* Removes all data items from the heap.
*
* @b Algorithm
* -# Set number of actual data items to zero.
*
* @pre
* -# Heap must be declared and have memory allocated to it.
*
* @post
* -# Number of actual items will be set to 0.
*
* @param None
*
* @return None
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{
	size = 0;
}


/** IsEmpty
*
* Function determines whether heap is empty. Returns true if heap is empty.
*
* @b Algorithm
* -# Determine whether actual size is equal to zero.
* -# Returns true if it is.
*
* @pre
* -# Heap must be initialized.
*
* @post
* -# Heap will be unchanged.
*
* @param None
*
* @return Boolean value. Returns true is heap is empty. Otherwise, returns false.
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	return( size == 0 );
}


/** IsFull
*
* Function determines whether heap is full. Returns true if heap is full.
*
* @b Algorithm
* -# Determine whether actual size is equal to maxSize.
* -# Returns true if it is.
*
* @pre
* -# Heap must be initialized.
*
* @post
* -# Heap will be unchanged.
*
* @param None
*
* @return Boolean value. Returns true is heap is full. Otherwise, returns false.
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
	return( maxSize == size );
}

/** Show Structure
*
* Outputs the priorities of the data items in a heap in both array and tree form. If the heap is empty, outputs "Empty heap". This operation is intended for testing/debugging purposes only.
*
* @b Algorithm
* -# Initialize variables.
* -# Output array form.
* -# Output tree form.
*
* @pre
* -# Heap must be initialized.
* -# showSubtree function must be declared and properly functioning.
* -# getPriority function must be declared and properly functioning.
*
* @post
* -# Heap will be unchanged.
*
* @param None
*
* @return None
*
* @exception
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::showStructure () const
{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

/** writeLevels
*
* Function displays the heap separated by level
*
* @b Algorithm
* -# Initialize variables for the first element in the heap.
* -# Loop through the heap.
* -# If the current index is equal to the index of the left child of the previous left child, then output an endline.
* -# Output the priority of the element in the heap.
*
* @pre
* -# Heap must be declared.
* -# Function lchild must be properly functioning.
*
* @post
* -# Heap will be unchanged.
*
* @param None
*
* @return None
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::writeLevels() const
{
	if( !isEmpty() )
	{

		// Initialize for first element
		int i = 0;
		int lIndex = lchild( i );

		// Loop through heap
		for( i = 0; i < size; i++ )
		{
			if( i == lIndex )
			{
				cout << endl;
				lIndex = lchild( i );
			}
			cout << dataItems[i].getPriority() << ' ';
		}
		cout << endl;
	}
}

// - - - - - - Show Helper Function - - - - - - //


/** Show Subtree Helper Function
*
* Helper function for the showStructure() function. Outputs the subtree (subheap) whose root is stored in dataItems[index]. Argument level is the level of this dataItems within the tree.
*
* @b Algorithm
* -# Check if index is less than size.
* -# Output right subtree.
* -# Tab over to level.
* -# Output dataItem's priority.
* -# Output connector character.
* -# output left subtree.
*
* @pre
* -# Heap must be initialized.
* -# getPriority function must be declared and properly functioning.
*
* @post
* -# Heap will be unchanged.
*
* @param index Integer of index of item to be displayed.
* @param level Integer of level of item to be displayed
*
* @return None
*
* @exception None
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const
{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

/** Parent
*
* Function calculates and returns the index of the parent of the given index, if index is valid.
This assumes that any error checking for out of bounds is handled outside of the function.
*
* @b Algorithm
* -# If index is valid (greater than or equal to zero and within array), calculate parent index. This index is the child index minus one, all divided by two.
* -# Otherwise, set the parent index equal to negative one to designate an out of bounds index.
* -# Return parent index.
*
* @pre
* -# Function must be called with valid integer for parameter. This parameter does not have to be within bounds of the array, but should be.
*
* @post
* -# The heap will be unchanged.
* -# The calculated value will be returned to the calling function.
*
* @param pIndex Integer value indicating the index of the child item which is used to calculate the parent index.
*
* @return Integer value of the index of the parent, if it exists. Otherwise, negative one.
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::parent( int cIndex ) const
{
	int parentIndex = ( cIndex - 1 ) / 2;
	return parentIndex;
}

/** lchild
*
* Function calculates and returns the index of the left child of the given index, if index is valid.
This assumes that any error checking for out of bounds is handled outside of the function.
*
* @b Algorithm
* -# If index is valid (greater than or equal to zero), calculate left child index. This index is twice the parent index plus one.
* -# Otherwise, set the left child index equal to negative one to designate an out of bounds index.
* -# Return left child index.
*
* @pre
* -# Function must be called with valid integer for parameter. This parameter does not have to be within bounds of the array, but should be.
*
* @post
* -# The heap will be unchanged.
* -# The calculated value will be returned to the calling function.
*
* @param pIndex Integer value indicating the index of the parent item which is used to calculate the left child index.
*
* @return Integer value of the index of the right child, if it exists. Otherwise, negative one.
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::lchild( int pIndex ) const
{
	int leftChild;
    if( pIndex >= 0 && pIndex < maxSize )
    {
        leftChild = ( 2 * pIndex ) + 1;
    }
    else
    {
        leftChild = -1;
    }
	return leftChild;
}

/** rchild
*
* Function calculates and returns the index of the right child of the given index, if index is valid.
This assumes that any error checking for out of bounds is handled outside of the function.
*
* @b Algorithm
* -# If index is valid (greater than or equal to zero), calculate right child index. This index is twice the parent index plus two.
* -# Otherwise, set the right child index equal to negative one to designate an out of bounds index.
* -# Return right child index.
*
* @pre
* -# Function must be called with valid integer for parameter. This parameter does not have to be within bounds of the array, but should be.
*
* @post
* -# The heap will be unchanged.
* -# The calculated value will be returned to the calling function.
*
* @param pIndex Integer value indicating the index of the parent item which is used to calculate the right child index.
*
* @return Integer value of the index of the right child, if it exists. Otherwise, negative one.
*
* @exception None
*/
template <typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator>::rchild( int pIndex ) const
{
	int rightChild;
    if( pIndex >= 0 && pIndex < maxSize )
    {
        rightChild = ( 2 * pIndex ) + 2;
    }
    else
    {
        rightChild = -1;
    }
	return rightChild;
}
