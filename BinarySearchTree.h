//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// Listing 16-4.

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
//#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include <queue>
#include <stack>

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
   BinaryNode<ItemType>* rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
   BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,
                                       BinaryNode<ItemType>* newNode);
   
   // Removes the given target value from the tree while maintaining a
   // binary search tree.
   BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
                                     const ItemType target,
                                     bool& success);
   
   // Removes a given node from a tree while maintaining a
   // binary search tree.
   BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderSuccessor);

   void inorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const;
   void levelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const;
   void mirroredLevelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const;
   void reverseLevelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const;
   bool isLeafNode_Iter(BinaryNode<ItemType>* subTreePtr, const ItemType target);
   bool isLeafNode_Recu(BinaryNode<ItemType>* subTreePtr, const ItemType target);
   int nonLeafCount_Iter(BinaryNode<ItemType>* subTreePtr);
   int nonLeafCount_Recu(BinaryNode<ItemType>* subTreePtr);
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinarySearchTree();
   BinarySearchTree(const ItemType& rootItem);
   BinarySearchTree(const BinarySearchTree<ItemType>& tree);
   virtual ~BinarySearchTree();
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   //int getHeight() const;
   //int getNumberOfNodes() const;
   //ItemType getRootData() const throw(PrecondViolatedExcep);
   //void setRootData(const ItemType& newData) const  throw(PrecondViolatedExcep);
   bool add(const ItemType& newEntry);
   bool remove(const ItemType& anEntry);
   void clear();
//   ItemType getEntry(const ItemType& anEntry) const;
//   throw(NotFoundException);
//   bool contains(const ItemType& anEntry) const;
   
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   void inorderTraverse(void visit(BinaryNode<ItemType>&)) const;
   void levelorderTraverse(void visit(BinaryNode<ItemType>&)) const;
   bool isLeaf(const ItemType target, string str);
   int countNonLeaves(string str);

   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);   
}; // end BinarySearchTree

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
   rootPtr = new BinaryNode<ItemType>( rootItem, nullptr, nullptr );
}  // end constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
   rootPtr = copyTree( treePtr.rootPtr );
}  // end copy constructor

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
   this->destroyTree( rootPtr );
}  // end destructor

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const
{
	if ( subtreePtr != nullptr )
   {
		inorder( visit, subtreePtr->getLeftChildPtr() );
		visit( *subtreePtr );
		inorder( visit, subtreePtr->getRightChildPtr() );
   }  // end if
}  // end inorder

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////


template<class ItemType>
void BinarySearchTree<ItemType>:: clear(){
	this->destroyTree( rootPtr );
	rootPtr = nullptr;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
   return ( rootPtr == nullptr ) ;
} 

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
   BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
   rootPtr = insertInorder(rootPtr, newNodePtr);
   return true;
}  // end add

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,
                                                            BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;

	if ( subTreePtr->getItem() == newNodePtr->getItem() ) {
		

		// add some code here


		return subTreePtr;
	}

	BinaryNode<ItemType>* tempPtr;


	if ( subTreePtr->getItem() > newNodePtr->getItem() ) {
		tempPtr = insertInorder( subTreePtr->getLeftChildPtr(), newNodePtr );
		subTreePtr->setLeftChildPtr( tempPtr );
	}
	else {
		tempPtr = insertInorder( subTreePtr->getRightChildPtr(), newNodePtr );
		subTreePtr->setRightChildPtr( tempPtr );
	}
	
	return subTreePtr;
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(BinaryNode<ItemType>&)) const
{
   inorder(visit, rootPtr);
}   

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry)
{
	bool success = false;
	rootPtr = removeValue( rootPtr, anEntry, success );

	return success;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
                                     const ItemType target,
                                     bool& success)
{
	if ( subTreePtr == nullptr ) {
		success = false;
		return nullptr;
	}
	
	if ( subTreePtr->getItem() == target ) {

		
		// add some code here


		return subTreePtr;
	}
	
	BinaryNode<ItemType>* tempPtr;

	if ( subTreePtr->getItem() > target ) {


		// add some code here


	}
	else {


		// add some code here


	}

	return subTreePtr;
}
   
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr)
{
	if ( nodePtr->isLeaf() ) {
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	} 

	if ( nodePtr->getLeftChildPtr() == nullptr || nodePtr->getRightChildPtr() == nullptr ) {
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightChildPtr();

		if ( nodeToConnectPtr == nullptr )
			nodeToConnectPtr = nodePtr->getLeftChildPtr();

		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}

	BinaryNode<ItemType>* tempPtr;
	ItemType newNodeValue;

	tempPtr = removeLeftmostNode( nodePtr->getRightChildPtr(), newNodeValue );
	nodePtr->setRightChildPtr( tempPtr );
	nodePtr->setItem( newNodeValue );

	return nodePtr;
}
   
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderSuccessor)
{
	if ( nodePtr->getLeftChildPtr() == nullptr ) {
		inorderSuccessor = nodePtr->getItem();
		return removeNode( nodePtr );
	} 
	else {
		BinaryNode<ItemType>* tempPtr;
		tempPtr = removeLeftmostNode( nodePtr->getLeftChildPtr(), inorderSuccessor );
		nodePtr->setLeftChildPtr( tempPtr );
		return nodePtr;
	}
}

template<class ItemType>
void BinarySearchTree<ItemType>::levelorderTraverse(void visit(BinaryNode<ItemType>&)) const
{
	levelorder( visit, rootPtr );
	mirroredLevelorder(visit, rootPtr);
	reverseLevelorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::levelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const
{
	// the data structures that may be useful
	queue<BinaryNode<ItemType>*> nodeQueue;
	stack<BinaryNode<ItemType>*> nodeStack;
	BinaryNode<ItemType> *tmpPtr = subtreePtr;
	cout << "\n\n";
	if (subtreePtr) {
		nodeQueue.push(subtreePtr);
	}
	while (!nodeQueue.empty())
	{
		visit(*nodeQueue.front());
		if (nodeQueue.front()->getLeftChildPtr())
			nodeQueue.push(nodeQueue.front()->getLeftChildPtr());
		if (nodeQueue.front()->getRightChildPtr())
			nodeQueue.push(nodeQueue.front()->getRightChildPtr());
		nodeQueue.pop();
	}

	// add your code here


}  // end levelorder

template<class ItemType>
void BinarySearchTree<ItemType>::mirroredLevelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const
{
	// the data structures that may be useful
	queue<BinaryNode<ItemType>*> nodeQueue;
	stack<BinaryNode<ItemType>*> nodeStack;
	BinaryNode<ItemType> *tmpPtr = subtreePtr;
	cout << "\n\n";
	if (subtreePtr) {
		nodeQueue.push(subtreePtr);
	}
	while (!nodeQueue.empty())
	{
		if (nodeQueue.front()->getRightChildPtr())
			nodeQueue.push(nodeQueue.front()->getRightChildPtr());
		if (nodeQueue.front()->getLeftChildPtr())
			nodeQueue.push(nodeQueue.front()->getLeftChildPtr());
		visit(*nodeQueue.front());
		nodeQueue.pop();
	}
	
	// add your code here

}  // end levelorder

template<class ItemType>
void BinarySearchTree<ItemType>::reverseLevelorder(void visit(BinaryNode<ItemType>&), BinaryNode<ItemType>* subtreePtr) const
{
	cout << "\n\n";
	// the data structures that may be useful
	/*queue<BinaryNode<ItemType>*> nodeQueue;
	stack<BinaryNode<ItemType>*> nodeStack;
	BinaryNode<ItemType> *tmpPtr = subtreePtr;

	do {
		while (tmpPtr != NULL) {
			nodeQueue.push(tmpPtr);
			tmpPtr = tmpPtr->getLeftChildPtr();
		}
		if (!nodeQueue.empty()) {
			tmpPtr = nodeQueue.front();
			visit(*tmpPtr);
			nodeQueue.pop();
			tmpPtr = tmpPtr->getRightChildPtr();
		}
	} while (!nodeQueue.empty() || tmpPtr != NULL);*/
	// the data structures that may be useful
	queue<BinaryNode<ItemType>*> nodeQueue;
	stack<BinaryNode<ItemType>*> nodeStack;
	BinaryNode<ItemType>* tmpPtr = subtreePtr;
	nodeQueue.push(subtreePtr);
	for (;;)
	{
		if (nodeQueue.empty() == true)
			break;
		tmpPtr = nodeQueue.front();
		nodeStack.push(tmpPtr);
		if (tmpPtr->getLeftChildPtr() != nullptr)
			nodeQueue.push(tmpPtr->getLeftChildPtr());
		if (tmpPtr->getRightChildPtr() != nullptr)
			nodeQueue.push(tmpPtr->getRightChildPtr());
		nodeQueue.pop();
	}
	for (;;)
	{
		if (nodeStack.empty() == true)
			break;
		visit(*nodeStack.top());
		nodeStack.pop();
	}
	// add your code here
	// add your code here


}  // end levelorder

template<class ItemType>
bool BinarySearchTree<ItemType>::isLeaf(const ItemType target, string str)
{
	if (str == "i")
		return isLeafNode_Iter(rootPtr, target);
	if (str == "r")
		return isLeafNode_Recu(rootPtr, target);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isLeafNode_Iter(BinaryNode<ItemType>* subtreePtr, const ItemType target)
{


	// add your code here


	return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isLeafNode_Recu(BinaryNode<ItemType>* subtreePtr, const ItemType target)
{


	// add your code here


	return false;
}

template<class ItemType>
int BinarySearchTree<ItemType>::countNonLeaves(string str)
{
	if ( str == "i")
		return nonLeafCount_Iter(rootPtr);
	if (str == "r")
		return nonLeafCount_Recu(rootPtr);

	return 0;
}

template<class ItemType>
int BinarySearchTree<ItemType>::nonLeafCount_Iter(BinaryNode<ItemType>* subtreePtr)
{

	int a, b, c, count = 0;
	queue<BinaryNode<ItemType>*> q;
	q.push(subtreePtr);
	BinaryNode<ItemType>* tmpptr;
	//subtreePtr->getLeftChildPtr();
	while(1)
	{
		if (q.empty() == true)
			return count;
		tmpptr = q.front();
		q.pop();
		if (tmpptr->getLeftChildPtr() != nullptr || tmpptr->getRightChildPtr() != nullptr)
			count++;
		if (tmpptr->getLeftChildPtr())
			q.push(tmpptr->getLeftChildPtr());
		if (tmpptr->getRightChildPtr())
			q.push(tmpptr->getRightChildPtr());
	}
	// add your code here


	return 0;
}


template<class ItemType>
int BinarySearchTree<ItemType>::nonLeafCount_Recu(BinaryNode<ItemType>* subtreePtr)
{
	int r, l;
	if (subtreePtr->getLeftChildPtr() == nullptr && subtreePtr->getRightChildPtr() == nullptr) {
		return 0;
	}
	else
	{
		if (subtreePtr->getLeftChildPtr() != nullptr)
			l = nonLeafCount_Recu(subtreePtr->getLeftChildPtr());
		if (subtreePtr->getRightChildPtr() != nullptr)
			r = nonLeafCount_Recu(subtreePtr->getRightChildPtr());
		return l + r + 1;
	}
	// add your code here


	return 0;
}
#endif
