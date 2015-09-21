/**

@file BSTree.cpp

@author Renee Iinuma
@date October 30, 2013

*/

/**
* @mainpage Lab 9 - Binary Search Tre
* This is the implementation to create a binary search tree, with basic functions.
*/

#include "BSTree.h"

/**
* Default Constructor for the binary seach tree node
*
* Default parameterized constructor which sets the binary seach tree node values to the given values.
@param[in] nodeDataItem. The data item in the node will be set to this value.
@param[in] leftPtr Given binary seach tree node pointer for the left branch of the tree. The left pointer of the node will be set to this value.
@param[in] rightPtr Given binary seach tree node pointer for the right branch of the tree. The right pointer of the node will be set to this value.
*
@pre 
 -# Binary seach tree must be declared.
@post 
 -# All data members of the binary seach tree node will be updated.
*/

/*
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
	// Update node items
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}
*/
/**
* Default Constructor for the binary seach tree
*
* Default constructor which sets the root pointer of the binary seach tree to NULL.
*
@pre 
* None
@post 
 -# The root pointer will now be pointing to NULL.
*/
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree()
{
	// Initialize root to null
	root = NULL;
}

/**
* Copy Constructor for the binary seach tree
*
* Copy constructor sets root to NULL. The overloaded assignment operator is then called to create a copy of the given binary seach tree.
@param[in] source Given binary seach tree to be copied. This is constant and will not be changed.
*
@pre 
 -# Function must be called with a valid binary seach tree as the parameter.
@post 
 -# Tree will be created.
 -# Tree will be updated to be a deep copy of the given source binary seach tree.
*/
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree( const BSTree<DataType,KeyType>& other )
{
	// Initialize root to null
	root = NULL;
	// Assign given tree to current tree
	*this = other;
}

/**
* Overloaded Assignment Operator
*
* Function overloads assignment operator so that one binary seach tree may be assigned to another explicitly. First clears the current tree if necessary and then copies over given tree.
@param[in] source Given binary seach tree to be copied.
*
@pre 
 -# Binary seach tree must be declared.
 -# Source must be valid binary seach tree.
@post 
 -# Tree will become a deep copy of given source tree.
@return Updated tree object.
@detail @bAlgorithm
-# Clear tree if necessary.
-# Call copy helper function with root binary search trees.
*/

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator=( const BSTree<DataType,KeyType>& other )
{
	// Clear current tree if necessary
	if( root != NULL )
	{
		clear();
	}
	// Call copy helper with root
	copyHelper( root, other.root );

	// Return tree object
	return *this;
}

/**
* Destructor
*
* Destructor calls clear function to clear tree.
@pre 
 -# Binary seach tree must be declared.
@post 
 -# Tree will have nodes deleted.
 -# Root will be pointing to null.
*/
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree()
{
	// Clear tree
	clear();
}

/**
*Insert
*
* Insert function which calls insert helper function to insert the given data item into the tree.
@pre
-# Binary tree must be declared.
-# Function must be called with valid data item of DataType.
@post
-# Tree will be updated including the new value to insert.
@param[in] newDataItem Data item of DataType to be inserted in the proper location in the tree.
*/
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert( const DataType& newDataItem )
{
	insertHelper( root, newDataItem );
}

/**
*Retrieve
*
* Retrieve function which calls retrieve helper function with root pointer to retrieve the search data item of the search key.
@pre
-# Binary tree must be declared.
-# Function must be called with valid parameters for search key and data item.
@post
-# Tree will be unchanged.
-# searchDataItem will be updated with the data item of the search key, if found.
@param[in] searchKey Given search key to be searched for in the binary tree.
@param[out] searchDataItem Search data item will be updated with the data item in the tree if found.
@return Boolean value. Return true if key is found. False otherwise.
*/
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve( const KeyType& searchKey, DataType& searchDataItem ) const
{
	return( retrieveHelper( root, searchKey, searchDataItem ) );
}

/**
*Remove
*
* Remove function which calls remove helper function with root pointer to remove the data item of the given key.
@pre
-# Binary tree must be declared.
-# Function must be called with valid parameter for delete key.
@post
-# Tree will be updated, with the given key deleted.
@param[in] deleteKey Constant key value of the key to be deleted.
@return Boolean value. Returned true if key is found and deleted. Returned false if key is not found.
*/
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove( const KeyType& deleteKey )
{
	return( removeHelper( root, deleteKey ) );
}

/**
* Write Keys
*
* Write Keys function will display the keys of the binary search tree in order. If tree is empty, there will be no output. This function calls the write keys helper function with the root pointer to display keys of entire tree.
@pre
-# Binary tree must be declared.
@post
-# Tree will be unchanged.
*/
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys() const
{
	writeHelper( root );
	cout << endl;
}

/**
*Clear
*
* Clear function calls clear helper function with root pointer which will clear and deallocate the entire tree.
@pre
-# Binary tree must be declared.
@post
-# Tree will be cleared. Root pointer will be pointing to null.
*/
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear()
{
	clearHelper( root );
}

/**
*isEmpty
*
* Is Empty function determines whether the tree is empty, meaning the root pointer is null.
@pre
-# Binary tree must be declared.
@post
-# Tree will be unchanged.
@return Boolean value. Returned true if root is null and tree is empty. Return false otherwise.
*/
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const
{
	return( root == NULL );
}

/**
*getHeight
*
* Get Height function determines the height of the binary search tree. If the tree is empty, the height returned is zero. This function calls the get height helper function with the root pointer which recursively determines the height of the tree.
@pre
-# Binary tree must be declared.
@post
-# Tree will be unchanged.
@return Integer value of the height of the binary search tree.
*/
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight() const
{
	return( heightHelper( root ) );
}

/**
* getCount
*
* Get Count function determines the number of data items in the binary search tree. This function calls the get count helper function with the root pointer, which will return the numbe of items in the entire tree.
@pre
-# Binary tree must be declared.
@post
-# Tree will be unchanged.
@return Integer value of the number of items in the tree.
*/
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount() const
{
	return( countHelper( root ) );
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan( const KeyType& searchKey ) const
{
	// Not asssigned
}

/**
* showStructure
*
* Function shows structure of the entire tree. Designates empty if tree is empty. This function calls the show structure helper function.
* Outputs the keys in a binary search tree. The tree is output
* rotated counterclockwise 90 degrees from its conventional
* orientation using a "reverse" inorder traversal. This operation is
* intended for testing and debugging purposes only.
@pre
-# Binary tree must be declared.
@post
-# Tree will be unchanged.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const



{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

/* - - - - - - - - - - - - // Helper Functions // - - - - - - - - - - - - - -*/

/**
* showHelper
*
* Show structure helper function recursively displays the structure of the binary search tree.
* Recursive helper for showStructure. 
* Outputs the subtree whose root node is pointed to by p. 
* Parameter level is the level of this node within the tree.
@pre
-# Binary tree must be declared.
-# Binary tree will not be empty.
-# Function must be called with a valid binary search tree pointer.
@post
-# Tree will be unchanged.
@param p Binary search tree node pointer of node to be displayed
@param level Integer designating level
@detail @bAlgorithm
-# Initialize.
-# Output right subtree.
-# Tab over to level.
-# Output key.
-# Output connector character.
-# Output left subtree.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const
{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}

/**
* copyHelper
*
* Copy Helper function recursively copies nodes of the source tree to the destination tree. Upon completion, the entire source tree will be copied to the destination tree.
@pre
-# Binary trees must be declared.
-# Binary source tree must contain valid data.
@post
-# Source tree will be unchanged.
-# Destination binary tree will be a deep copy of the source tree.
@param dest Binary tree node pointer pointing to a node of the destination tree. Pointer is passed by reference because it is updated within the function.
@param src Binary tree node pointer pointing to a node of the source tree. This pointer is unchanged.
@detail @bAlgorithm
-# Check if source is null.
-# If it is not, update destination pointer to a new node containing source's data item. Left and right pointers are initialized to null.
-# Call copy helper to recursively copy on left and right children nodes.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::copyHelper( BSTreeNode* &dest, BSTreeNode* src )
{
	if( src != NULL )
	{
		// Create new node with source data
		dest = new BSTreeNode( src->dataItem, NULL, NULL );

		// Copy left and right nodes recursively
		copyHelper( dest->left, src->left );
		copyHelper( dest->right, src->right );
	}
}

/**
* clearHelper
*
* Clear Helper function recursively clears the tree from the given pointer. Upon completion, the entire tree from the given node will be cleared.
@pre
-# Binary tree must be declared.
-# Function must be called with a valid binary search tree pointer.
@post
-# Binary tree will be cleared. 
-# All nodes from this pointer on will be deallocated.
-# Given pointer will be null.
@param ptr Binary search tree node pointer pointing to the tree to be cleared.
@detail @bAlgorithm
-# Check if ptr is null.
-# If it is not, clear subtrees on the left and right by recursively calling the clear helper function.
-# Delete node which pointer is pointing to.
-# Set pointer to null.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clearHelper( BSTreeNode* &ptr )
{
	if( ptr != NULL )
	{
		// Clear left and right nodes
		clearHelper( ptr->left );
		clearHelper( ptr->right );

		// Delete current pointer and set to null
		delete ptr;
		ptr = NULL;
	}
}

/**
* insertHelper
*
* Insert helper function recursively inserts the given data item in the correct location of the tree by checking the relative key value.
@pre
-# Binary tree must be declared.
-# Function must be called with a valid binary search tree pointer and data item of DataType.
@post
-# Binary search tree may be updated to include the new data item.
@param ptr Binary search tree pointer pointing to the node to be checked.
@param newDataItem Item of DataType which is to be inserted into the tree.
@detail @bAlgorithm
-# If pointer is null, create a new node containing the given data item. The left and right children pointers will be set to null.
-# Otherwise, if key of new data is less than key of current node data, recursively call insert helper function with the left subtree.
-# Otherwise, if key of new data is greater than key of current node data, recursively call insert helper function with the right subtree.
-# Otherwise, the key of new data must equal the key of the current node data. Set the current node data to the new data.
*/
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insertHelper( BSTreeNode* &ptr, const DataType& newDataItem)
{
	if( ptr == NULL )
	{
		ptr = new BSTreeNode( newDataItem, NULL, NULL );
	}
	else if( newDataItem.getKey() < ptr->dataItem.getKey() )
	{
		insertHelper( ptr->left, newDataItem );
	}
	else if( newDataItem.getKey() > ptr->dataItem.getKey() )
	{
		insertHelper( ptr->right, newDataItem );
	}
	else
	{
		ptr->dataItem = newDataItem;
	}
}

/**
* retrieveHelper
*
* Retrieve helper function recursively retrieves the data item of the given key, if found.
@pre
-# Binary tree must be declared.
-# Function must be called with parameters of a valid binary search tree pointer, search key of KeyType, and search data item of DataType.
@post
-# Binary search tree will be unchanged.
-# searchDataItem will be updated with data from the tree, if key is found.
@param ptr Binary search tree pointer pointing to the node to be checked.
@param searchKey Key of KeyType containing value to search for in tree. 
@param searchDataItem Item of DataType which is passed by reference. This will be updated with data from the tree at the given key, if key is found.
@detail @bAlgorithm
-# If pointer is null, return false.
-# Otherwise, if key of search data is less than key of current node data, recursively call retrieve helper function with the left subtree. The same searchDataItem and searchKey are passed to this function.
-# Otherwise, if key of search data is greater than key of current node data, recursively call retrieve helper function with the right subtree. The same searchDataItem and searchKey are passed to this function.
-# Otherwise, the key of new data must equal the key of the current node data. Set the searchDataItem to the current dataItem.
*/
template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper( BSTreeNode* ptr, const KeyType& searchKey, DataType& searchDataItem ) const
{
	if( ptr == NULL )
	{
		return false;
	}
	else if( searchKey < ptr->dataItem.getKey() )
	{
		return( retrieveHelper( ptr->left, searchKey, searchDataItem ));
	}
	else if( searchKey > ptr->dataItem.getKey() )
	{
		return( retrieveHelper( ptr->right, searchKey, searchDataItem ));
	}
	else
	{
		searchDataItem = ptr->dataItem;
		return true;
	}
}

/**
* removeHelper
*
* Remove helper function recursively removes the binary search tree node containing the given key, if key is found. 
@pre
-# Binary tree must be declared.
-# Function must be called with parameters of a valid binary search tree pointer and key of keyType.
@post
-# Binary search tree may be updated if key is found. 
-# If found, the node of given key will be deleted. 
-# The rest of the tree will remain in order.
@param ptr Binary search tree pointer pointing to the node to be checked.
@param deleteKey Key of keyType containing the key to search for and delete if found.
*
@detail @bAlgorithm
-# If pointer is null, return false.
-# Otherwise, if delete key is less than key of current node data, recursively call remove helper function with the left subtree. The same delete key is passed to this function.
-# Otherwise, if delete key is greater than key of current node data, recursively call remove helper function with the right subtree. The same delete key is passed to this function.
-# Otherwise, the key of new data must equal the key of the current node data. @n
*
-# In this case, check if node is a leaf. If it is, delete current node and set pointer to null.
-# Otherwise, check if there is only one child on the left. If it is, move pointer to left child node. Delete parent node.
-# Otherwise, check if there is only one child on the right. If it is, move pointer to left right node. Delete parent node.
-# Otherwise, there must be two child nodes. Find predecessor by going to the left child, and then to the far right child from there. Recursively call remove helper function with the left subtree and key of current item.
*/
template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper( BSTreeNode* &ptr, const KeyType& deleteKey )
{
	BSTreeNode* temp;
	if( ptr == NULL )
	{
		return false;
	}
	else if( deleteKey < ptr->dataItem.getKey() )
	{
		return( removeHelper( ptr->left, deleteKey ) );
	}
	else if( deleteKey > ptr->dataItem.getKey() )
	{
		return( removeHelper( ptr->right, deleteKey ) );
	}
	else
	{
		if( ptr->left == NULL && ptr->right == NULL )
		{
			delete ptr;
			ptr = NULL;
			return true;
		}
		else if( ptr->left != NULL && ptr->right == NULL )
		{
			temp = ptr;
			ptr = ptr->left;
			delete temp;
			return true;
		}
		else if( ptr->left == NULL && ptr->right != NULL )
		{
			temp = ptr;
			ptr = ptr->right;
			delete temp;
			return true;
		}
		else
		{
			temp = ptr->left;
			while( temp->right != NULL )
			{
				temp = temp->right;
			}
			ptr->dataItem = temp->dataItem;
			removeHelper( ptr->left, temp->dataItem.getKey() );
		}
	}
}

template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeHelper( BSTreeNode* ptr ) const
{
	if( ptr != NULL )
	{
		writeHelper( ptr->left );
		cout << (ptr->dataItem).getKey() << ' ';
		writeHelper( ptr->right );
	}
}

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::countHelper( BSTreeNode* ptr ) const
{
	if( ptr == NULL )
	{
		return 0;
	}
	else
	{
		return( 1 + countHelper( ptr->left ) + countHelper( ptr->right ) );
	}
}

template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::heightHelper( BSTreeNode* ptr ) const
{
	if( ptr == NULL )
	{
		return 0;
	}
	else
	{
		if( heightHelper( ptr->left ) > heightHelper( ptr->right ) )
		{
			return( 1 + heightHelper( ptr->left ) );
		}
		else
		{
			return( 1 + heightHelper( ptr->right ) );
		}
	}
}
