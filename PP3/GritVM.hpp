#ifndef GRITVM_H
#define GRITVM_H

#include <iterator>
#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "GritVMBase.hpp"

using namespace std;

class GritVM : public GritVMInterface{
	public:
		GritVM(){};		
		vector <long> getDataMem();		
		STATUS reset();
		STATUS load(const string filename, const vector <long> &initialMemory);
		STATUS run();		
		STATUS machineStatus = WAITING;
	
	private:		
		int accumulator = 0;	
		vector <long> dataMem;
		list <Instruction> instructMem;
		list <Instruction>::iterator currIns;
};

#endif 