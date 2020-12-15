#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <sstream>
using namespace std;

void shifting_in_vector(int number, vector<bool> &_myVector){
	_myVector.push_back(number);
	_myVector.erase(_myVector.begin());
}

vector<bool> convert_decimal_to_binary(long _number){
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

long long convert_binary_to_decimal(vector<bool> &_numberInBinary){
	long long result = 0;
	size_t auxItr = 0;
	for(int i = _numberInBinary.size()-1; i >= 0; i--){
		result += _numberInBinary[i] * pow(2,auxItr);
		auxItr++;
	}
	return result;
}

void apply_mask(vector<bool> &_numberInBinary, vector<string> &_mask){
	for(size_t i = 0; i < _numberInBinary.size(); i++){
		if(_mask[i] != "X"){
			if(_mask[i] == "1"){
				_numberInBinary[i] = 1;
			}else{
				_numberInBinary[i] = 0;
			}
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

int main(int argc, char const *argv[]) {
	
	map<string, long long> memory;
	vector<string> mask;

	long numberReceived;
	vector<bool> numberReceivedInBinary;
	string memoryDirection;
	long long numberToSaveInMemory;
	string dataNoFormat;
	while(getline(cin, dataNoFormat)){
		if(dataNoFormat.find("mask") != -1){
			mask = parse_mask(dataNoFormat.substr(dataNoFormat.find("=")+2, dataNoFormat.length()));
		}else{
			memoryDirection = dataNoFormat.substr(dataNoFormat.find("[")+1, (dataNoFormat.find("]") - dataNoFormat.find("["))-1);

			stringstream number(dataNoFormat.substr(dataNoFormat.find("=")+2, dataNoFormat.length()));
			number >> numberReceived;

			numberReceivedInBinary = convert_decimal_to_binary(numberReceived);
			apply_mask(numberReceivedInBinary, mask);
			numberToSaveInMemory = convert_binary_to_decimal(numberReceivedInBinary);
			memory[memoryDirection] = numberToSaveInMemory;
		}
	}

	long long answer = 0;
	for(auto & memoryDirection : memory){
		cout << "direction: " << memoryDirection.first << " value: " << memoryDirection.second << endl;
		answer += memoryDirection.second;
	}
	cout << "answer of part 1: " << answer << endl;
}
