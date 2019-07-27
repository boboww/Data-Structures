#ifndef CALCLIST_H
#define CALCLIST_H

#include <string>

#include "CalcListInterface.hpp"

typedef std::string Elem;  

class DNode{							//mostly copied from slides
	public:	
		char operation;					//add values for operation, and stored numbers
		double oper;
		double oldNum = 0;
		double newNum = 0;
		DNode* next;					//Doubly linked list variables
		DNode* prev;
		Elem elem;		
		friend class DList;				//friend for accessing
};

class DList{							//copied from slides with extra added	
	public:						
		DList();
		~DList();
		bool empty() const;
		void add(DNode* v, const Elem& e);
		void addBack(const Elem& e);
		void removeFront();		
		DNode* head;					//header and trailer for DL list
		DNode* tail;
};

class CalcList : public CalcListInterface{
	public:
		double total() const;			//copied from Interface
		void newOperation(const FUNCTIONS func, const double operand);
		void removeLastOperation();
		std::string toString(unsigned short precision) const;		
	private:	
		DList newList;				
		DNode* header;
		double totalFin = 0;			//keep total variable here
};

#endif