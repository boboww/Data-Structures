#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"				//*****deque functions are merged DLL and deque from slides*****

using namespace std;

class Node { 											// doubly linked list node
	private:
		string elem; 									// node element value
		Node* prev; 									// previous node in list
		Node* next; 									// next node in list
		friend class Deque;
};

class Deque { 											// deque as doubly linked list
	public:
		Deque(); 										// constructor
		//~Deque();										// awful
		int size() const; 								// number of items in the deque
		bool empty() const; 							// is the deque empty?
		void addFront(string s); 						// add new first element
		void addBack(string s); 						// add new last element
		void removeFront(); 							// remove first element
		void removeBack(); 								// remove last element
		string front();				
		string back();
	private:	
		Node* head; 									// list sentinels
		Node* tail;
		int n = 0; 										// number of elements		
	protected:
		void add(Node* v, string s); 					// insert new node before v
		void remove(Node* v); 							// remove node v
};

class NotationConverter : public NotationConverterInterface{
	public:
		string postfixToInfix(string inStr);			// inherited functions
		string postfixToPrefix(string inStr);	
		string infixToPostfix(string inStr);
		string infixToPrefix(string inStr);
		string prefixToInfix(string inStr);
		string prefixToPostfix(string inStr);
		
		bool checkOp(char s);							// check functions
		bool checkCh(char s);
		int orderOp(string s);
};

#endif