#include "ListLinked.h"
#include <stdexcept>
#include <iostream>

// default constructor for node
// initializes the data in node to given data and next pointer to given pointer
template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}


// default constructor for list
// integer is for purpose of array based and is ignored in node based list
template <typename DataType>
List<DataType>::List(int ignored)
{
	// set head pointer and cursor to null
	head = NULL;
	cursor = NULL;

}

// copy constructor for list
template <typename DataType>
List<DataType>::List(const List& other)
{
	if( other.isEmpty() )
	{
		head = NULL;
		cursor = NULL;
	}
	else
	{
		head = new ListNode( other.head->dataItem, other.head->next );
		if( other.cursor == other.head )
		{
			cursor = head;
		}
		ListNode* othertmp = other.head->next;
		ListNode* tmp = head;
		while( othertmp != NULL )
		{
			tmp->next = new ListNode( othertmp->value, NULL );
			tmp = tmp->next;
			if( othertmp == other.cursor )
			{
				cursor = tmp;
			}
			othertmp = othertmp->next;
		}
	}
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{

}

template <typename DataType>
List<DataType>::~List()
{
	clear();
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{

}

template <typename DataType>
void List<DataType>::remove() throw (logic_error)
{
	ListNode* temp = cursor;
	gotoPrior();
	cursor->next = temp->next;
	if( cursor->next != NULL )
	{
		gotoNext();
	}
	else
	{
		
	}
	delete temp;
	temp = NULL;
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{

}

template <typename DataType>
void List<DataType>::clear()
{
	while( !isEmpty() )
	{
		remove();
	}
}

template <typename DataType>
bool List<DataType>::isEmpty() const
// returns true if list is empty
// list is empty when head pointer is null
{
	return ( head == NULL );
}
    
template <typename DataType>
bool List<DataType>::isFull() const
// returns true if list is full
// for this assignment, we assume list will never be full
{
	return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	if( !isEmpty() )
		cursor = head;
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	if( !isEmpty() )
	{
		while( cursor->next != NULL )
		{
			cursor = cursor->next;
		}
	}
}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	if( !isEmpty() )
	{
		if( cursor->next != NULL )
		{
			cursor = cursor->next;
			return true;
		}
	}
	return false;
}

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	if( !isEmpty() )
	{
		ListNode* temp = cursor;
		cursor = head;
		while( cursor->next != temp )
		{
			cursor = cursor->next;
		}
		temp = NULL;
		return true;
	}
	return false;
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
	if( !isEmpty() )
	{
		return cursor->dataItem;
	}
}

// Programming exercise 2
template <typename DataType>
void List<DataType>::moveToBeginning () throw (logic_error)
{

}

// Programming exercise 3
template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{

}
  
// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only. 
template <typename DataType>
void List<DataType>::showStructure() const
{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}

