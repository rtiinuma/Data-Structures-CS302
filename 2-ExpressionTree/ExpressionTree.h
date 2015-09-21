//--------------------------------------------------------------------
//
//  Laboratory 8                                     ExpressionTree.h
//
//  Class declarations for the linked implementation of the
//  Expression Tree ADT -- including the recursive helpers for the
//  public member functions
//
//  Instructor copy with the recursive helper function declarations.
//  The student version does not have those, but has a place to write
//  the declarations in the private section.
//
//--------------------------------------------------------------------

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdexcept>
#include <iostream>

using namespace std;

template <typename DataType>
class ExprTree {
  public:

    // Constructor
    ExprTree ();
    ExprTree(const ExprTree& source);

    ExprTree& operator=(const ExprTree& source);

    // Destructor
    ~ExprTree ();

    // Expression tree manipulation operations
    void build ();
    void expression () const;
    DataType evaluate() const throw (logic_error);
    void clear ();              // Clear tree
    void commute();
    bool isEquivalent(const ExprTree& source) const;

	bool isEmpty() const;

    // Output the tree structure -- used in testing/debugging
    void showStructure () const;

  private:

    class ExprTreeNode {
      public:
        // Constructor
        ExprTreeNode ( char elem,
                       ExprTreeNode *leftPtr, ExprTreeNode *rightPtr );

        // Data members
        char dataItem;          // Expression tree data item
        ExprTreeNode *left,     // Pointer to the left child
                     *right;    // Pointer to the right child
    };

    // Recursive helper functions for the public member functions -- insert
    // prototypes of these functions here.
	void showHelper( ExprTreeNode *p, int level ) const;
	void buildHelper( ExprTreeNode* &ptr );
	DataType evaluateHelper( const ExprTreeNode* ptr ) const;
	void commuteHelper( ExprTreeNode* &ptr );
	void copyHelper( const ExprTreeNode* src, ExprTreeNode* &dest );
	void clearHelper( ExprTreeNode* &ptr );
	void expressionHelper( ExprTreeNode* ptr ) const;
	bool isEquivalentHelper( ExprTreeNode* one, ExprTreeNode* other ) const;

    // Data member
    ExprTreeNode *root;   // Pointer to the root node
};

#endif		// #ifndef EXPRESSIONTREE_H
