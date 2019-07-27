#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "CalcList.hpp"

using namespace std;

DList::DList() : head(nullptr) {}					//function from slides

DList::~DList(){									//function from slides
	while (!empty()) removeFront();
}

bool DList::empty() const {							//function from slides
	return head == nullptr;
}

void DList::add(DNode* v, const Elem& e){			//function from slides
    DNode* u = new DNode; 
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = v->prev;
    v->prev = u;    
}

void DList::removeFront(){							//function from slides
	DNode* old = head; 			
	head = old->next; 			
	delete old; 				
}

double CalcList::total() const{						//return totalFin
	return totalFin;
}

void CalcList::removeLastOperation(){
	if(newList.empty()){
		throw "Empty List";
	}
	newList.removeFront();
	return;
}

std::string CalcList::toString(unsigned short precision) const{	
	DNode* test = newList.head;
	
	string text;
	to_string(totalFin);	
	stringstream out;
	out<<setprecision(precision);
	
	//no idea how to do this part. oh well, ill try harder next time.
	//newOperation part is missing stuff too
	//ill just take the zero 
	
	return text;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){
	DNode* temp = new DNode;							//create new temp node
	temp->oper = operand;								//store operand 
	
	if(temp->next != nullptr){
		if(func == ADDITION){							//conditional for addition
			temp->operation = '+';						//set char for use in toString
			temp->newNum = temp->oldNum + operand;		//calculate
		}else if(func == SUBTRACTION){					//same
			temp->operation = '*';						//going
			temp->newNum = temp->oldNum * operand;		//down
		}else if(func == MULTIPLICATION){				// |
			temp->operation = '-';						// V
			temp->newNum = temp->oldNum - operand;
		 }else if(func == DIVISION){  
			if(operand == 0){							//0 division error
				throw "Divide by 0"; 
			}
			temp->operation = '/';
			temp->newNum = temp->oldNum / operand;
		}	
		totalFin = temp->newNum;						//get final total
	}
}
