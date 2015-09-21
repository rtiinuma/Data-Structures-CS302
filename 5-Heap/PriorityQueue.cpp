#include "PriorityQueue.h"
using namespace std;


template <typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue( int maxNumber ) : Heap<DataType, KeyType, Comparator>::Heap( maxNumber )
{

}

template <typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue( const DataType &newDataItem )
{
	if( Heap<DataType, KeyType, Comparator>::isFull() )
	{
		throw logic_error( "Priority Queue is Full " );
	}
	else
	{
		Heap<DataType, KeyType, Comparator>::insert( newDataItem );
	}
}

template <typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
{
	if( Heap<DataType, KeyType, Comparator>::isEmpty() )
	{
		throw logic_error( "Priority Queue is Empty" );
	}
	else
	{
		return Heap<DataType, KeyType, Comparator>::remove();
	}
}
