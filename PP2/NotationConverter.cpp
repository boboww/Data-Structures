#include "NotationConverter.hpp"

using namespace std;									//*****deque functions are merged DLL and deque from slides******

Deque::Deque() { 										//constructor
	head = new Node; 									//create sentinels
	tail = new Node;
	head->next = tail; 									//have them point to each other
	tail->prev = head;
}

/*Deque::~Deque(){										//absolute pain
	while (!empty()){									//still don't know why it's an issue
		removeFront(); 									//spent a whole day looking for this one error (segfault)
	}													//couldn't even test anything else since this broke the whole catch program
	delete head; 										//valgrind also didn't help with finding this
	delete tail;
}*/

void Deque::add(Node* v, string s) {					//insert new node before v
	Node* u = new Node; 
	u->elem = s; 										//create new node for s
	u->next = v; 										//link u in between v
	u->prev = v->prev; 									//...and v->prev
	v->prev->next = v->prev;
	v->prev = u;
}

void Deque::remove(Node* v) { 							//remove node v
	Node* u = v->prev; 									//predecessor
	Node* w = v->next; 									//successor
	u->next = w; 										//unlink v from list
	w->prev = u;
	delete v;
}

int Deque::size() const {
	return n;
}

bool Deque::empty() const {
	return (head->next == tail);
}

void Deque::addFront(string s) {						//insert new first element
	add(head->next, s);
	n++;
}

void Deque::addBack(string s) {							//insert new last element
	add(tail, s);
	n++;
}

void Deque::removeFront(){								//remove first element
	if(empty()) { 
		throw (" remove front empty"); 
	}
	remove(head->next); 
	n--;
}

void Deque::removeBack(){								//remove last element
	if(empty()) { 
		throw ("remove back empty"); 
	}
	remove(tail->prev); 
	n--;
}

string Deque::front(){
	if(empty()) {
		throw ("front empty");
	}
	return head->next->elem; 							//list front is queue front
}

string Deque::back(){
	if(empty()){
		throw ("back empty");
	}
	return tail->prev->elem;
}

bool NotationConverter::checkOp(char s){							//check for valid operator
	if(s == '*' || s == '/' || s == '+' || s == '-'){
		return true;
	}else{
		return false;
	}
}

bool NotationConverter::checkCh(char s){							//check for valid character
	if(checkOp(s) || isalpha(s) || isdigit(s) || s == '(' || s == ')' || s == ' ') {
		return 1;
	}else{
		throw ("invalid character");
		return 0;
	}
}

int NotationConverter::orderOp(string s){							//set order of operations
	if(s == "*" || s == "/"){
		return 2;
	}if(s == "+" || s == "-"){
		return 1;
	}else{
		return 0;
	}
}

string NotationConverter::infixToPrefix(string inStr){				//in to pre
	return postfixToPrefix(infixToPostfix(inStr));					//call other functions	
}		

string NotationConverter::prefixToInfix(string inStr){				//pre to in
	Deque A;
	string temp1;	
	string temp2;
	string temp3;
	char t;	
	
	for(int i = (int)inStr.size() - 1; i >= 0 ; i--) {				//cast after using size() or get warning
		temp1 = t = inStr.at(i);					
		checkCh(t);
		
		if(t == ' ' || t == ')' || t == '('){ 						//case for spaces and parentheses 
			continue; 
		}if(checkOp(t)){											//check for operations
			temp2 = A.back();
			A.removeBack();  
			temp3 = A.back();  
			A.removeBack();
			A.addBack("(" + temp2 + " " + temp1 + " " + temp3 + ")");
		}else {
			A.addBack(temp1);
		}
	}
	return A.back();
}

string NotationConverter::postfixToInfix(string inStr){				//post to in
	Deque A;
	string temp1;	
	string temp2;
	string temp3;
	char t;	
	
	for(int i = 0; i < (int)inStr.size(); i++) {					//cast after using size() or get warning
		temp1 = t = inStr.at(i);					
		checkCh(t);
		
		if(t == ' ' || t == ')' || t == '('){ 						//case for spaces and parentheses 
			continue; 
		}if(checkOp(t)){											//check for operations
			temp2 = A.back();
			A.removeBack();  
			temp3 = A.back();  
			A.removeBack();
			A.addBack("(" + temp3 + " " + temp1 + " " + temp2 + ")");
		}else {
			A.addBack(temp1);
		}
	}
	return A.back();
}

string NotationConverter::prefixToPostfix(string inStr){			//pre to post
	Deque A;
	string temp1;
	string temp2;
	string temp3;
	char t;
	
	for(int i = (int)inStr.size() - 1; i >= 0; i--){ 				//cast after using size() or get warning
		temp1 = t = inStr.at(i);		
		checkCh(t);
		
		if(t == ' ' || t == ')' || t == '('){  						//case for spaces and parentheses
			continue; 
		}if(checkOp(t)){											//check for operations
			temp2 = A.back();
			A.removeBack();
			temp3 = A.back();
			A.removeBack();
			A.addBack(temp2 + " " + temp3 + " " + temp1);			//format then add to deque
		}else{
			A.addBack(temp1);
		}
   	}
   	return A.back();
}

string NotationConverter::postfixToPrefix(string inStr){			//post to pre
	Deque A;
	string temp1;
	string temp2;
	string temp3;
	char t;

   	for(int i = 0; i < (int)inStr.size(); i++){ 					//cast after using size() or get warning
		temp1 = t = inStr.at(i);		
		checkCh(t);
		
		if(t == ' ' || t == ')' || t == '('){ 
			continue; 
		}if(checkOp(t)){											//check for operations
			temp2 = A.back();
			A.removeBack();
			temp3 = A.back();
			A.removeBack();
			A.addBack(temp1 + " " + temp3 + " " + temp2);			//format then add to deque
		}else{
			A.addBack(temp1);
		}
   	}
   	return A.back();
}

string NotationConverter::infixToPostfix(string inStr){				//infixToPostfix
	Deque A;
	string temp;
	string result;	
	char t;

	for(int i = 0; i < (int)inStr.size(); i++){ 					//cast after using size() or get warning
		temp = t = inStr.at(i);	
		checkCh(t);
		
		if(t == ' '){ 												//case for spaces
			continue; 
		}if(isalpha(t)){ 
			result += temp + " ";									//not sure what is wrong here
		}if(t == '('){												//infix algorithm is too confusing
			A.addBack(temp);										//already rewrote this many times
		}if(t == ')'){ 												//close enough I guess
			while(!A.empty() && A.back() != "("){
				result += A.back() + " ";
				A.removeBack();
			}
		}if(checkOp(t)){											//check for operations
			while(orderOp(temp) <= orderOp(A.back())){				//check order of operations
				result += A.back() + " ";		
			}
			A.addBack(temp);
		}
	}
    return result;
}
