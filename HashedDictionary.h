 //  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

// PARTIALLY COMPLETE
#include <string>
#include "HashedEntry.h"

template<class KeyType, class ItemType>
class HashedDictionary 
{
private:
	HashedEntry<KeyType, ItemType> ** hashTable;
	static const int DEFAULT_SIZE = 1;
	HashedEntry<KeyType, ItemType>* nextPtr;
	int hashTableSize;
   
public:
   HashedDictionary();
   HashedDictionary(int size);
   void add(const KeyType& searchKey, const ItemType& newItem);
   bool remove(const KeyType& searchKey);
   HashedEntry<KeyType, ItemType>* getEntry(const KeyType& searchKey);
   void traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType>&)) const;
   void clear();
   bool isEmpty();
   int getTableSize();

protected:
	int getHashIndex(const KeyType& searchKey);
}; // end HashedDictionary

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	hashTableSize = DEFAULT_SIZE;
	hashTable = new HashedEntry<KeyType, ItemType>*[hashTableSize];
	
	for ( int i = 0; i < hashTableSize; i++ )
		hashTable[ i ] = nullptr;
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int size)
{
	hashTableSize = size;
	hashTable = new HashedEntry<KeyType, ItemType>*[hashTableSize];

	for ( int i = 0; i < hashTableSize; i++ )
		hashTable[ i ] = nullptr;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType>&)) const
{
	HashedEntry<KeyType, ItemType> *itemPtr = hashTable[ itemHashIndex ];

	while ( itemPtr != nullptr ) {
		visit( *itemPtr );
		itemPtr = itemPtr->getNext();
	}
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	HashedEntry<KeyType, ItemType> *nextPtr, *curPtr;

   for ( int i = 0; i < hashTableSize; i++ ) {
	   curPtr = hashTable[ i ];

	   while (curPtr != nullptr) {
		   nextPtr = curPtr->getNext();
           delete curPtr;
		   curPtr = nextPtr;
	   } // end while

	   hashTable[ i ] = nullptr;
   } // end if
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getTableSize()
{
	return hashTableSize ;
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty()
{
	for (int i = 0; i < hashTableSize; i++) {
		if ( hashTable[i] != nullptr )
			return false;
	}

	return true;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType& searchKey)
{
	int strLen =  searchKey.length();

	if ( strLen == 0 )
		return 0;

	return  ( (unsigned char) searchKey[0] ) % hashTableSize;
}


template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	
	HashedEntry<string, string>* itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	HashedEntry<string, string>* entryToAddPtr = new HashedEntry<string, string>(newItem,searchKey);
	
	if (hashTable[itemHashIndex] == nullptr) {
		hashTable[itemHashIndex] = entryToAddPtr;
	}
	else
	{
			HashedEntry<string, string>* cur = hashTable[itemHashIndex];
			while (cur->getItem() != newItem ) {
				cur = cur->getNext();
				if (cur == nullptr)
					break;
			}
			if (cur != nullptr) {
				if (cur->getCount() > 0) {
					cur->countUp();
					return;
				}
			}
				entryToAddPtr->setNext(hashTable[itemHashIndex]);
				hashTable[itemHashIndex] = entryToAddPtr;
	} // end if

	// add your code here


} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)  // a abc a asddd a agvssef a a a asddd
{
	bool itemFound = false;

	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	if (hashTable[itemHashIndex] != nullptr)
	{
		// Special case - first node has target
		if (searchKey == hashTable[itemHashIndex]->getKey())
		{
			if (hashTable[itemHashIndex]->getCount() > 1) {
				hashTable[itemHashIndex]->countDown();
			}

			else {
				HashedEntry<KeyType, ItemType>
					* entryToRemovePtr = hashTable[itemHashIndex];

				hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
				delete entryToRemovePtr;
				entryToRemovePtr = nullptr; // For safety
			}
			itemFound = true;
		}
		else // Search the rest of the chain
		{
			HashedEntry<KeyType, ItemType>* prevPtr = hashTable[itemHashIndex];
			HashedEntry<KeyType, ItemType>* curPtr = prevPtr->getNext();
			while ((curPtr != nullptr) && !itemFound)
			{
				// Found item in chain so remove that node
				if (searchKey == curPtr->getKey())
				{
					if (curPtr->getCount() > 1) {
						curPtr->countDown();
					}
					else {
						prevPtr->setNext(curPtr->getNext());
						delete curPtr;
						curPtr = nullptr; // For safety
					}
					itemFound = true;
					break;
				}
				else // Look at next entry in chain
				{
					prevPtr = curPtr;
					curPtr = curPtr->getNext();
				} // end if
			} // end while
		} // end if
	} // end if

	return itemFound;
} // end remove



template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedDictionary<KeyType, ItemType>::getEntry(const KeyType& searchKey)
{
	bool itemFound = false;

	// Compute the hashed index into the array

	int itemHashIndex = getHashIndex(searchKey);
	HashedEntry<string, string>* cur = hashTable[itemHashIndex];
	while (cur != nullptr)
	{
		if (cur->getKey() == searchKey) {
			itemFound = true;
			return cur;
		}
		cur = cur->getNext();
	}
	// add your code here


	return nullptr;
}

