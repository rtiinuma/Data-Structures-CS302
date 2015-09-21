// LIST: TYPE 2 (Node)
#include "list2.h"

list::list( int ignore )
{
	head = NULL;
	cursor = NULL;
}

list::list( const list &rhs )
{
	if( rhs.isEmpty() )
	{
		head = NULL;
		cursor = NULL;
	}
	else
	{
		head = new node( rhs.head->value, NULL );
		if( rhs.head == rhs.cursor )
		{
			cursor = head;
		}
		node* rhstmp = rhs.head->next;
		node* tmp = head;
		while( rhstmp != NULL )
		{
			tmp->next = new node( rhstmp->value, NULL );
			tmp = tmp->next;
			if( rhstmp == rhs.cursor )
			{
				cursor = tmp;
			}
			rhstmp = rhstmp->next;
		}
	}
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
		if( cursor->next != NULL )
		{
			cursor = cursor->next;
			return true;
		}
	}
	return false;
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
		temp = NULL;
		return true;
	}
	return false;
}

bool list::insertAfter( char givenChar )
{
	if( isEmpty() )
	{
		head = new node( givenChar, NULL );
		cursor = head;
	}
	else
	{
		node* temp = new node( givenChar, cursor->next );
		cursor->next = temp;
		cursor = temp;
		temp = NULL;
	}
	// will not be full, so insert will always return true
	return true;
}

bool list::insertBefore( char givenChar )
{
	if( isEmpty() )
	{
		head = new node( givenChar, NULL );
		cursor = head;
	}
	else
	{
		node* temp = new node( cursor->value, cursor->next );
		cursor->next = temp;
		cursor->value = givenChar;
		temp = NULL;
	}
	// will not be full, so insert will always return true
	return true;
}

bool list::remove( char &returned )
{
	// SI
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
			cursor = temp->next;
			if( cursor == NULL )
			{
				cursor = head;
			}
			temp = NULL;
			if( isEmpty() )
			{
				head = NULL;
			}
			temp = NULL;
		}
		return true;
	}
	return false;
}

bool list::replace( char given )
{
	if( !isEmpty() )
	{
		cursor->value = given;
		return true;
	}
	return false;
}

bool list::getCursor( char &returned ) const
{
	if( !isEmpty() )
	{
		returned = cursor->value;
		return true;
	}
	return false;
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
	//SI
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
	if( this != &rhs )
	{
		if( !rhs.isEmpty() )
		{
			if( isEmpty() )
				head = new node( rhs.head->value, NULL );
			else
				head->value = rhs.head->value;
			if( rhs.head == rhs.cursor )
			{
				cursor = head;
			}

			node* rhstmp = rhs.head->next;
			node* tmp = head;
			while( rhstmp != NULL )
			{

				if( tmp->next == NULL )
				{
					tmp->next = new node( rhstmp->value, NULL );
					tmp = tmp->next;
				}
				else
				{
					tmp = tmp->next;
					tmp->value =rhstmp->value;
				}
				if( rhstmp == rhs.cursor )
				{
					cursor = tmp;
				}
				rhstmp = rhstmp->next;
			}
		}
	}
}

bool list::operator==( const list &given ) const
{
	node* gtemp = given.head;
	node* temp = head;
	if( given.head->value != head->value || given.cursor->value != cursor->value )
		return false;
	while( gtemp != NULL && temp != NULL )
	{
		if( gtemp->value != temp->value )
		{
			return false;
		}
		gtemp = gtemp->next;
		temp = temp->next;
	}
	if( gtemp != NULL || temp != NULL )
		return false;

	return true;
}


ostream& operator<<( ostream &out, const list &rhs )
{

	if( !rhs.isEmpty() )
	{
		node* temp = rhs.head;
		while( temp != NULL )
		{
			if( temp == rhs.cursor )
			{
				out << '[' << temp->value << "] ";
			}
			else
			{
				out << temp->value << ' ';
			}
			temp = temp->next;
		}
	}
	else
	{
		out << "Empty";
	}
	out << endl;

}

