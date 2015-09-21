void LL::insertAtEnd(int a)
{

	if( cursor == NULL )
	{
		head = cursor = new node( a, NULL );
	}
	else if( cursor->next == NULL )
	{
		cursor->next = new node( a, NULL );
		cursor = cursor->next;
	}
	else
	{
		cursor = cursor->next;
		insertAtEnd( a );
	}

}
