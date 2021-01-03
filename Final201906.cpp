// Final201806.cpp: 定義主控台應用程式的進入點。
//


//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include<stack>
#include<queue>
#include "BinarySearchTree.h"
#include "HashedDictionary.h" 

using namespace std;

void displayWordCount(BinaryNode<string>&  entry)
{
	cout << entry.getItem() << "(" << entry.getCount() << ")  ";
}

void displayWordCount(HashedEntry<string, string>&  entryPtr)
{
	cout << entryPtr.getItem() << "(" << entryPtr.getCount() << ")  ";
}

void input(string sMessage, string &sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());
}

void input(string sMessage, int &inputNum)
{
	do {
		cout << sMessage << endl;
		cin >> inputNum;
	} while (cin.fail());
}

void stringToTokens(queue<string>& aQueue, string aString)
{
	string token, theDelimters = ".,!?;: ";
	int end = 0;
	int start = aString.find_first_not_of(theDelimters, end);

	while (start != string::npos) {
		end = aString.find_first_of(theDelimters, start);
		token = aString.substr(start, end - start);
		aQueue.push(token);
		start = aString.find_first_not_of(theDelimters, end);
	}
}

// ================ Q1 Begins Here ==================
#define PQSIZE	10

void pqArrayInsert(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == PQSIZE)
		cout << "ARRAY Priority queue full!" << endl;
	for (int i = 0; i < size; i++)
	{
		if ( pqArray[i].getItem() > word) {
			for (int j = size; j > 0; j--)
			{
				pqArray[j] = pqArray[j-1];
			}
			pqArray[i] = word;
			size++;
			return;
		}
		if (pqArray[i].getItem() == word) {
			pqArray[i].countUp();
			return;
		}
	}
	pqArray[size].countUp();
	// add your code here
	pqArray[size] = word;
	size++;
}

int pqArrayDelete(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == 0) {
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}
	for (int i = 0; i < size; i++)
	{
		if (pqArray[i].getItem() == word && pqArray[i].getCount() > 1) {
			pqArray[i].countDown();
			return 1;
		}
		if (pqArray[i].getItem() == word && pqArray[i].getCount() == 1) {
			for (int j = i; j < size - 1; j++)
				pqArray[j] = pqArray[j + 1];
			size--;
			return 1;
		}
	}
	
	// add your code here
	//size--;
	return -1;
}

void doQ1()
{
	BinaryNode<string> pqItems[PQSIZE];
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	int i, size = 0;

	while (1) {
		input("\nEnter A to Add words, R to Remove a word, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty()) {
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				pqArrayInsert(pqItems, size, aWord);
			}

			for (i = 0; i < size; i++)
				displayWordCount(pqItems[i]);

			cout << endl;
		}
		else if (sInput == "R" || sInput == "r") {
			if (size == 0)
				cout << "PQ is empty!" << endl;
			else {
				input("Enter word: ", aWord);

				if (pqArrayDelete(pqItems, size, aWord) < 0)
					cout << "Not exist in PQ!" << endl;
				else if (size == 0)
					cout << "Last word deleted!" << endl;
				else {
					for (i = 0; i < size; i++)
						displayWordCount(pqItems[i]);

					cout << endl;
				}
			}
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// ================ Q2 Begins Here ==================
void showAdjMatrix(int** matrixGraph, int numVertices)
{
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			if (matrixGraph[i][j] == INT_MAX)
				cout << " - ";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}

int maxEdgeWeight(int** matrixGraph, int numVertices)
{
	int max = INT_MAX;
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			if (i == j)
				continue;
			if (matrixGraph[i][j] < max ) {
				max = matrixGraph[i][j];
			}
		}
	}
	//matrixGraph
	// add your code here


	return max;
}


void updateEdgeWeight(int** matrixGraph, int numVertices, int vertexNo1, int vertexNo2, int weight)
{

	if (matrixGraph[vertexNo1][vertexNo2] == INT_MAX || vertexNo1 > numVertices || vertexNo2 > numVertices)
		return;
	matrixGraph[vertexNo1][vertexNo2] = weight;
	matrixGraph[vertexNo2][vertexNo1] = weight;
	// add your code here


	return;
}


void BFS_Recu(int** matrixGraph, int numVertices, int vertexNo, bool* visited)
{
	queue <int> a;
	visited[vertexNo] = true;
	
	a.push(vertexNo);
	cout << " v" << vertexNo;
	for (int i = 0; i < numVertices; i++) {
		if (matrixGraph[vertexNo][i] < INT_MAX && visited[i] == false ) {
			BFS_Recu(matrixGraph, numVertices, i, visited);
			//break;
		}
	}
	// add your code here


	return;
}

void BFS_Iter(int** matrixGraph, int numVertices, int vertexNo, bool* visited)
{
	queue <int> que;
	que.push(vertexNo);
	visited[vertexNo] = true;
	while (!que.empty())
	{
		int num = que.front();
		cout << " v" << num;
		que.pop();
		for (int i = 0; i < numVertices; i++)
		{
			if (matrixGraph[num][i] < INT_MAX && visited[i] == false) {
				que.push(i);
				visited[i] = true;
			}
		}
	}
	// add your code here
	return;
}

void doBFS(int** matrixGraph, int numVertices, int vertexNo)
{
	bool* visited = new bool[numVertices];

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nRecursive BFS:";
	BFS_Recu(matrixGraph, numVertices, vertexNo, visited);

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	cout << "\nIterative BFS:";
	BFS_Iter(matrixGraph, numVertices, vertexNo, visited);
	cout << "\n";
	delete[] visited;

	return;
}


void doQ2()
{
	string sInput;
	int numVertices, u, v, weight, vertexNo, vertexStartNo;

	ifstream inFile("graph.txt");

	if (!inFile) {
		cerr << "Error: Failed to open " << "graph.txt" << " for input! \n";
		return;
	}

	if (inFile.peek() == EOF) {
		cerr << "Error: Empty input file! \n";
		return;
	}

	inFile >> numVertices;

	int **matrixGraph = new int*[numVertices];

	for (int i = 0; i < numVertices; i++) {
		matrixGraph[i] = new int[numVertices];

		for (int j = 0; j < numVertices; j++)
			matrixGraph[i][j] = INT_MAX;

		matrixGraph[i][i] = 0;
	}

	while (inFile.peek() != EOF) {
		inFile >> u >> v >> weight;

		if (inFile.fail())
			break;

		if (u < numVertices && v < numVertices)
			matrixGraph[u][v] = matrixGraph[v][u] = weight;
	}

	cout << "\nThe adjacency matrix:\n";
	showAdjMatrix(matrixGraph, numVertices);

	while (1) {
		input("\nEnter command: M for Maximum edge weight, U to update edge weight, B to do BFS, or X to Exit", sInput);

		if (sInput == "m" || sInput == "M") {
			cout << "The maximum edge weight is " << maxEdgeWeight(matrixGraph, numVertices) << endl;
		}
		else if (sInput == "u" || sInput == "U") {
			int vertexNo1, vertexNo2, weight;
			input("Enter vertex1 no: ", vertexNo1);
			input("Enter vertex1 no: ", vertexNo2);
			input("Enter new weight: ", weight);

			 updateEdgeWeight(matrixGraph, numVertices, vertexNo1, vertexNo2, weight);
			 cout << "The graph after updating edge weight:\r\n";

			showAdjMatrix(matrixGraph, numVertices);
		}
		else if (sInput == "b" || sInput == "B") {
			input("Enter start vertex no: ", vertexStartNo);

			if (vertexStartNo < numVertices)
				doBFS(matrixGraph, numVertices, vertexStartNo);
			else
				cerr << "Error: Vertex no. out of range! \r\n";
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r\n" << endl;
	}


	return;
}

// ================ Q3 Begins Here ==================
void display(BinaryNode<string>& aNode)
{
	cout << aNode.getItem() << "  ";
}

void doQ3()
{
	string sInput, aString, aLine;
	BinarySearchTree<string> myBST;

	while (1) {
		input("\nEnter command: A to Add, N to Count, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);

			string token, theDelimters = ".,!?;: ";
			int end = 0;
			int start = aLine.find_first_not_of(theDelimters, end);

			while (start != string::npos) {
				end = aLine.find_first_of(theDelimters, start);
				token = aLine.substr(start, end - start);
				myBST.add(token);
				start = aLine.find_first_not_of(theDelimters, end);
			}

			cout << endl << "The inoder traversal of the BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl << "The normal, mirrored, reverse levelorder traversal of the BST are " << endl;
			myBST.levelorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "N" || sInput == "n") {
			cout << endl << "The iterative non leaf count of the BST is " << myBST.countNonLeaves("i");
			cout << endl << "The recursive non leaf count of the BST is " << myBST.countNonLeaves("r") << endl;
		}
		else if (sInput == "C" || sInput == "c") {
			myBST.clear();
			cout << endl << "BST is empty." << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}

	return;

}

// ================ Q4 Begins Here ==================
void doQ4()
{
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	HashedEntry<string, string>* itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1) {
		input("\nEnter A to Add, R to Remove, Q to Query, D to Display, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty()) {
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				myHashTable.add(aWord, aWord);
			}
		}
		else if (sInput == "R" || sInput == "r") {
			input("Enter word: ", aWord);

			if (myHashTable.remove(aWord))
				cout << aWord << " is removed." << endl;
			else
				cout << "Word not found!" << endl;
		}
		else if (sInput == "Q" || sInput == "q") {
			input("Enter word: ", aWord);
			itemPtr = myHashTable.getEntry(aWord);

			if (itemPtr == nullptr)
				cout << "Word not found!" << endl;
			else {
				cout << "Retireved word is: ";
				displayWordCount(*itemPtr);
				cout << endl;
			}
		}
		else if (sInput == "D" || sInput == "d") {
			cout << "Words in buckets are: " << endl;

			int i, len = myHashTable.getTableSize();

			for (i = 0; i < len; i++) {
				cout << i << ": ";
				myHashTable.traverse(i, displayWordCount);
				cout << endl;
			}
		}
		else if (sInput == "C" || sInput == "c") {
			myHashTable.clear();
			cout << "Words in buckets are cleared." << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// =============== Main Begins Here =================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1) {
		cout << endl;
		cout << "1. Priroity queue operations" << endl;
		cout << "2. Graph operations" << endl;
		cout << "3. Binary search tree operations" << endl;
		cout << "4. Hash table operations" << endl;

		input("Enter Question Number( 1 ~ 4 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0') {
		case 0:
			return 0;
		case 1:
			doQ1();
			break;
		case 2:
			doQ2();
			break;
		case 3:
			doQ3();
			break;
		case 4:
			doQ4();
			break;
		}
	}
}
// ============== Main Program Ends Here ================

