// LIST: TYPE 2 (Node)
#include "list2.h"

list::list( int ignore )
{
	head = NULL;
	cursor = NULL;
}

list::list( const list &rhs )
{

}

list::~list()
{
	clear();
}

bool list::goToBeginning()
{
	if( !isEmpty() )
	{
		cursor = head;
		return true;
	}
	return false;
}

bool list::goToEnd()
{
	if( !isEmpty() )
	{
		while( cursor->next != NULL )
		{
			cursor = cursor->next;
		}
		return true;
	}
	return false;
}

bool list::goToNext()
{
	if( !isEmpty() )
	{
		cursor = cursor->next;
	}
}

bool list::goToPrior()
{
	if( !isEmpty() )
	{
		node* temp = cursor;
		cursor = head;
		while( cursor->next != temp )
		{
			cursor = cursor->next;
		}
		return true;
	}
	return false;
}

bool list::insertAfter( char givenChar )
{
	if( isEmpty() )
	{
	}
	else
	{
	}
}

bool list::insertBefore( char givenChar )
{

}

bool list::remove( char &returned )
{
	// SI // CHANGE ///////////////////////////
	if( !isEmpty() )
	{
		returned = cursor->value;
		node* temp = head;
		if( cursor == head )
		{
			cursor = cursor->next;
			delete head;
			head = cursor;
		}
		else
		{
			while( temp->next != cursor )
			{
				temp = temp->next;
			}
			temp->next = cursor->next;
			delete cursor;
			cursor = temp;
			temp = NULL;
			if( isEmpty() )
			{
				head = NULL;
			}
		}
		return true;
	}
	return false;
}

bool list::replace( char given )
{

}

bool list::getCursor( char &returned ) const
{

}

bool list::isEmpty() const
{
	if( head == NULL )
	{
		return true;
	}
	return false;
}

bool list::isFull() const
{
	return false;
}

bool list::clear()
{
	//SI CHANGE /////////////////////////////
	if( !isEmpty() )
	{
		cursor = head;
		while( head->next != NULL )
		{
			head = head->next;
			delete cursor;
			cursor = head;
		}
		delete cursor;
		cursor = head = NULL;
		return true;
	}
	return false;
}

void list::operator=( const list &rhs )
{

}

bool list::operator==( const list &given ) const
{

}


ostream& operator<<( ostream &out, const list &rhs )
{

}

