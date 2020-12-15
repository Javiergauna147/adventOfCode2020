#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;

//global memory
map<string, long long> memory;


void shifting_in_vector(int number, vector<bool> &_myVector){
	_myVector.push_back(number);
	_myVector.erase(_myVector.begin());
}

vector<bool> convert_decimal_to_binary(long long _number){
	vector<bool> numberInBinary = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	vector<bool> aux;
	while(_number > 1){
		aux.push_back(_number % 2);
		_number = _number / 2;
	}
	aux.push_back(_number);
	for(int i = aux.size()-1; i >= 0; i--){
		shifting_in_vector(aux[i], numberInBinary);
	}
	return numberInBinary;
}

vector<string> convert_bool_binary_to_string_binary(vector<bool> &_numberInBinary){
	vector<string> numberInBinaryString;
	for(size_t i = 0; i < _numberInBinary.size(); i++){
		if(_numberInBinary[i] == 0){
			numberInBinaryString.push_back("0");
		}else{
			numberInBinaryString.push_back("1");
		}
	}
	return numberInBinaryString;
}

void apply_mask(vector<string> &_memoryInBinaryString, vector<string> &_mask){
	for(size_t i = 0; i < _memoryInBinaryString.size(); i++){
		if(_mask[i] != "0"){
			_memoryInBinaryString[i] = _mask[i];
		}
	}
}

vector<string> parse_mask(string _maskNoFormat){
	vector<string> maskParsed;
	for(size_t i = 0; i < _maskNoFormat.length(); i++){
		maskParsed.push_back(_maskNoFormat.substr(i,1));
	}
	return maskParsed;
}

auto find_memories_directions_and_save_value(vector<string> _memoryInBinaryString, int itr, long long &_valueToSave){ //memory should be already masked
	if(itr == _memoryInBinaryString.size()){
		string memoryInOneLine = "";
		for(auto & element : _memoryInBinaryString){
			memoryInOneLine += element;
		}
		//save value in memory direction
		memory[memoryInOneLine] = _valueToSave;
		return;
	}

	if(_memoryInBinaryString[itr] != "X"){
		find_memories_directions_and_save_value(_memoryInBinaryString, itr+1, _valueToSave);
	}else{
		_memoryInBinaryString[itr] = "1";
		find_memories_directions_and_save_value(_memoryInBinaryString, itr+1, _valueToSave);
		_memoryInBinaryString[itr] = "0";
		find_memories_directions_and_save_value(_memoryInBinaryString, itr+1, _valueToSave);
	}
}

int main(int argc, char const *argv[]) {
	

	vector<string> mask;
	vector<string> memoryInBinaryString;
	vector<bool> memoryInBinaryBool;
	string dataNoFormat;
	long long numberReceived;
	long long memoryDirection;

	while(getline(cin, dataNoFormat)){
		if(dataNoFormat.find("mask") != -1){
			mask = parse_mask(dataNoFormat.substr(dataNoFormat.find("=")+2, dataNoFormat.length()));
		}else{
			stringstream memory(dataNoFormat.substr(dataNoFormat.find("[")+1, (dataNoFormat.find("]") - dataNoFormat.find("["))-1));
			memory >> memoryDirection;
			memoryInBinaryBool = convert_decimal_to_binary(memoryDirection);
			memoryInBinaryString = convert_bool_binary_to_string_binary(memoryInBinaryBool);
			apply_mask(memoryInBinaryString, mask);

			stringstream number(dataNoFormat.substr(dataNoFormat.find("=")+2, dataNoFormat.length()));
			number >> numberReceived; //number to save in memory

			find_memories_directions_and_save_value(memoryInBinaryString, 0, numberReceived);
		}
	}

	long long answer = 0;
	for(auto & element : memory){
		//cout << "direction: " << element.first << " value: " << element.second << endl;
		answer += element.second;
	}
	cout << "answer to part two: " << answer << endl;
	
}
