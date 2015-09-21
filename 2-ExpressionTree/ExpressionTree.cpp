#include "ExpressionTree.h"


template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr )
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;

}

template <typename DataType>
ExprTree<DataType>::ExprTree()
{
	root = NULL;

}

template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
	// vvvvvv why need this vvvvv
	/* why need this >>> */ root = NULL; /* <<<< why need this */
	// ^^^^^^ why need this ^^^^^

	*this = source;
}

template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source)
{
	if( this != &source )
	{
		if( root != NULL )
		{
			clear();
		}
		if( source.root != NULL )
		{
			copyHelper( source.root, root );
		}

	}
	return *this;
}


template <typename DataType>
ExprTree<DataType>::~ExprTree ()
{
	clear();
}

template <typename DataType>
void ExprTree<DataType>::build()
{
	buildHelper( root );
}

template <typename DataType>
void ExprTree<DataType>::expression () const
{
	expressionHelper( root );
}

template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
	if( isEmpty() )
	{
		throw logic_error( "Empty List" );
	}
	return evaluateHelper( root );
}

template <typename DataType>
void ExprTree<DataType>::clear ()
{
	clearHelper( root );
}

template <typename DataType>
void ExprTree<DataType>::commute()
{
	commuteHelper( root );
}


template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
	//return isEquivalentHelper( root, &source );
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	return( root == NULL );
		
}
// Output the tree structure -- used in testing/debugging
template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if ( isEmpty() )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

/*------------------------------------- Helper Functions----------------------------------*/

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}

template <typename DataType>
void ExprTree<DataType>::buildHelper( ExprTreeNode* &ptr )
{
	char input;
	cin >> input;
	
	if( input >= '0' && input <= '9' )
	{
		ptr = new ExprTreeNode( input, NULL, NULL );

	}
	else if( input == '+' || input == '-' || input == '*' || input == '/' )
	{
		ptr = new ExprTreeNode( input, NULL, NULL );
		buildHelper( ptr->left );
		buildHelper( ptr->right );
	}

}

template <typename DataType>
DataType ExprTree<DataType>::evaluateHelper( const ExprTreeNode* ptr ) const
{
	switch( ptr->dataItem )
	{
		case '+':
			return( evaluateHelper( ptr->left ) + evaluateHelper( ptr->right ) );
			break;
		case '-':
			return( evaluateHelper( ptr->left ) - evaluateHelper( ptr->right ) );
			break;
		case '*':
			return( evaluateHelper( ptr->left ) * evaluateHelper( ptr->right ) );
			break;
		case '/':
			return( evaluateHelper( ptr->left ) / evaluateHelper( ptr->right ) );
			break;
		default:
			return( ptr->dataItem - '0' );
			break;

	}
}

template <typename DataType>
void ExprTree<DataType>::commuteHelper( ExprTreeNode* &ptr )
{
	if( ptr != NULL )
	{
		commuteHelper( ptr->left );
		commuteHelper( ptr->right );
		ExprTreeNode* temp;
		temp = ptr->left;
		ptr->left = ptr->right;
		ptr->right = temp;
	}
}

template <typename DataType>
void ExprTree<DataType>::copyHelper( const ExprTreeNode* src, ExprTreeNode* &dest )
{
	if( src != NULL )
	{
		dest = new ExprTreeNode( src->dataItem, NULL, NULL );
		copyHelper( src->left, dest->left );
		copyHelper( src->right, dest->right );
	}


}

template <typename DataType>
void ExprTree<DataType>::clearHelper( ExprTreeNode* &ptr )
{
	if( ptr != NULL )
	{
		if( ptr->left != NULL )
		{
			clearHelper( ptr->left );
		}
		if( ptr->right != NULL )
		{
			clearHelper( ptr->right );
		}
		delete ptr;
		ptr = NULL;
	}
}

template <typename DataType>
void ExprTree<DataType>::expressionHelper( ExprTreeNode* ptr ) const
{
	char value = ptr->dataItem;

	if( value >= '0' && value <= '9' )
	{
		cout << value;
	}
	else if( value == '+' || value == '-' || value == '*' || value == '/' )
	{
		cout << "( ";
		expressionHelper( ptr->left );
		cout << ' ' << value << ' ';
		expressionHelper( ptr->right );
		cout << " )";
	}
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper( ExprTreeNode* one, ExprTreeNode* other ) const
{/*
	if( one == NULL && other == NULL )
	{
		return true;
	}
	else if( one != NULL && other != NULL )
	{
		if( one->dataItem == other->dataItem  )
		{
			if( one->dataItem >= '0' && one->dataItem <= '9' )
			{
				return true;
			}
			else if( one->dataItem == '-' || one->dataItem == '/' )
			{
				return( isEquivalentHelper( one->left, other->left ) && isEquivalentHelper( one->right, other->right ) );
			}
			else if( one->dataItem == '+' || one->dataItem == '*' )
			{
				if( isEquivalentHelper( one->left, other->left ) && isEquivalentHelper( one->right, other->right ) )
				{
					return true;
				}
				else if( !isEquivalentHelper( one->left, other->left ) && !isEquivalentHelper( one->right, other->right ) )
				{
					ExprTree temp = *other;
					temp.commute();
					return ( isEquivalentHelper( one, &temp ) );
				}
			}
		}

	}*/

}
