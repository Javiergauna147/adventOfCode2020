#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

struct instruction {
	string comand;
	int steps;
};

int find_the_bug_in_the_test(vector<instruction> &_instructions, set<int> &_instructionsToChange, int _itrInstructionToChange){
	set<int> instructionsDone;
	vector<instruction> instructionsCopy = _instructions;
	int finalInstructionPos = instructionsCopy.size();
	int iteratorPosition = 0;
	int acumulator = 0;


	int instructionToChange = *next(_instructionsToChange.begin(),_itrInstructionToChange);
	if(instructionsCopy[instructionToChange].comand == "jmp"){
		instructionsCopy.at(instructionToChange).comand = "nop";
	}else{
		instructionsCopy[instructionToChange].comand = "jmp";
	}

	while(true){
		//cout << instructionsCopy[iteratorPosition].comand << " " << instructionsCopy[iteratorPosition].steps << endl;
		if(instructionsCopy[iteratorPosition].comand == "acc"){ //acc case	
			acumulator += instructionsCopy[iteratorPosition].steps;
			iteratorPosition ++;
		}else if(instructionsCopy[iteratorPosition].comand == "jmp"){ //jmp case
			iteratorPosition += instructionsCopy[iteratorPosition].steps;
		}else{ //nop case
			iteratorPosition ++;
		}

		if(instructionsDone.find(iteratorPosition) != instructionsDone.end()){
			//code to execute when star infite loop
			return find_the_bug_in_the_test(_instructions, _instructionsToChange, _itrInstructionToChange + 1);
		}else{
			instructionsDone.insert(iteratorPosition);
		}

		if(iteratorPosition == finalInstructionPos){
			// code to execute when last position is finded
			return acumulator;
		}
	}
}


int main(int argc, char const *argv[]){

	vector<instruction> instructions;
	string comand;
	int steps;
	int globalAcumulator = 0;

	set<int> instructionsToChange;

	while(cin >> comand >> steps){
		instruction myInstruction;
		myInstruction.comand = comand;
		myInstruction.steps = steps;
		instructions.insert(instructions.end(), myInstruction);
		if(comand == "jmp"){
			instructionsToChange.insert(instructionsToChange.end(), instructions.size()-1);
		}else if(comand == "nop"){
			instructionsToChange.insert(instructionsToChange.end(), instructions.size()-1);
		}
	}


	globalAcumulator = find_the_bug_in_the_test(instructions, instructionsToChange, 0);
	cout << "Global Acumulator: " << globalAcumulator << endl;
}