#include "GritVM.hpp"

vector <long> GritVM::getDataMem(){			// returns a copy of the current dataMem
    return dataMem;
}

STATUS GritVM::reset(){						// set the accumulator to 0, clears the dataMem/instructMem, 
    accumulator = 0; 						// and sets the machineStatus to WAITING. 
    dataMem.clear(); 						
    instructMem.clear(); 					
	machineStatus = WAITING; 				
    return machineStatus;
}

STATUS GritVM::load(const string filename, const vector <long> &initialMemory){	
	dataMem = initialMemory;				// copy vector to dataMem
	string in;	
	ifstream file;
	file.open(filename);					// open file
		
	if(file.is_open()){						// check for valid file		
		machineStatus = READY;		
		while(getline(file, in)){ 			// read file	
			if(in[0] != '#' && !in.empty()){// check for empty lines and comments
				if(GVMHelper::parseInstruction(in).operation == UNKNOWN_INSTRUCTION){
					machineStatus = ERRORED;
					break;
				}
			}else{
				continue;
			}
			instructMem.push_back(GVMHelper::parseInstruction(in)); // push instruction
		}	
		file.close();		
	}else{
		throw("Bad file"); 					// throw if file error
	}
	return machineStatus;		
}

STATUS GritVM::run(){						// starts the evaluation of the instructions
	currIns = instructMem.begin(); 			// then returns the current machine status.
	int i = 0;
	
	if(machineStatus == READY){
		machineStatus = RUNNING;
	}else{
		return machineStatus;
	}if(instructMem.size() == 0)	{
		machineStatus = WAITING;
	}if(currIns == instructMem.end()){ 		// use list::end() method
		machineStatus = HALTED;
	}
	
	while(machineStatus == RUNNING){	
		switch(currIns->operation){		
			case CLEAR:
				accumulator = 0;
				break;
			case AT:
				accumulator = dataMem.at(currIns->argument); 
				break;
			case SET: 
				dataMem.at(currIns->argument) = accumulator;	
				break;
			case INSERT:
				dataMem.insert(dataMem.begin() + currIns->argument, accumulator);				
				break;
			case ERASE:		
				dataMem.erase(dataMem.begin() + currIns->argument);	
				break;
			case ADDCONST:
				accumulator = accumulator + currIns->argument; 
				break;
			case SUBCONST:
				accumulator = accumulator - currIns->argument; 
				break;
			case MULCONST:
				accumulator = accumulator * currIns->argument; 
				break;	
			case DIVCONST:
				accumulator = accumulator / currIns->argument; 
				break;
			case ADDMEM:
				accumulator = accumulator + dataMem.at(currIns->argument); 
				break;
			case SUBMEM:
				accumulator = accumulator - dataMem.at(currIns->argument); 
				break;
			case MULMEM:
				accumulator = accumulator * dataMem.at(currIns->argument);
				break;
			case DIVMEM:
				accumulator = accumulator / dataMem.at(currIns->argument); 
				break;	
			case JUMPREL:
				if(currIns->argument > 0){
					for(i = currIns->argument; i >= 0; i--){
						currIns++;
					}
				}else{	
					for(i = currIns->argument; i <= 0; i++){
						currIns--;
					}	
				}
				break;				
			case JUMPZERO:
				if(accumulator == 0){
					if(currIns->argument > 0){					
						for(i = currIns->argument; i > 0; i--){
							currIns++;
						}
					}else{
						for(i = currIns->argument; i < 0; i++){
							currIns--;
						}						
					}
					currIns--;
				}
				break;			
			case JUMPNZERO:
				if(accumulator != 0){
					if(currIns->argument > 0){
						for(i = currIns->argument; i > 0; i--){
							currIns++;
						}
					}else{						
						for(i = currIns->argument; i < 0; i++){
							currIns--;
						}						
					}
					currIns--;
				}
				break;
			case NOOP: 
				break;	
			case HALT:				
				machineStatus = HALTED;
				break;
			case OUTPUT:
				cout << accumulator << endl;
				break;
			case CHECKMEM:
				if((int) dataMem.size() < currIns->argument){	// cast to signed int or warning
					machineStatus = ERRORED;
				}
				break;
			default: 
				break;					
		}			
		currIns++;	
	}
	return machineStatus;
}
