#include "HashTable.h"
#include <iostream>
using namespace std;
/* Name
*
* Description
*
* @b Algorithm
 -#
* @pre
 -#
* @post
 -#
* @param
* @return
*/
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable( int initTableSize )
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType>[ tableSize ];
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
{
	tableSize = other.tableSize;
	dataTable = new BSTree<DataType, KeyType>[ tableSize ];
	*this = other;
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
{
	if( this != &other )
	{
		clear();
		if( tableSize == other.tableSize )
		{
			for( int i = 0; i < tableSize; i++ )
			{
				dataTable[i] = other.dataTable[i];
			}
		}
		else
		{
			delete []dataTable;
			tableSize = other.tableSize;
			dataTable = new BSTree<DataType, KeyType>[ tableSize ];
			for( int i = 0; i < tableSize; i++ )
			{
				dataTable[i] = other.dataTable[i];
			}
		}
	}
	return *this;
}

template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
{
	clear();

	delete []dataTable;
	dataTable = NULL;
	tableSize = 0;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
{
	int i = ( newDataItem.hash( newDataItem.getKey() ) % tableSize );
	dataTable[i].insert( newDataItem );

}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	if( !isEmpty() )
	{
		int i = DataType::hash( deleteKey ) % tableSize;
		return( dataTable[i].remove( deleteKey ) );
	}
	return false;
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
{
	if( !isEmpty() )
	{
		unsigned int i = DataType::hash( searchKey ) % tableSize;
		return( dataTable[i].retrieve( searchKey, returnItem ) );
	}
	return false;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
{
	if( !isEmpty() )
	{
		for( int i = 0; i < tableSize; i++ )
		{
			dataTable[i].clear();
		}
	}
}

template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty() const
{
	for( int i = 0; i < tableSize; i++ )
	{
		if( !dataTable[i].isEmpty() )
		{
			return false;
		}
	}
	return true;
}

template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) 
	{
		cout << i << ": ";
		dataTable[i].writeKeys();
    }
}


template <typename DataType, typename KeyType>
double HashTable<DataType, KeyType>::standardDeviation() const
{
	// Not assigned
}




