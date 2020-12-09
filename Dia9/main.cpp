#include <iostream>
#include <vector>
using namespace std;


bool check_XMAS_rule(vector<long long> &_inputNumbers, int _preambleBegin, int _preambleEnd){

	if(_preambleEnd+1 == _inputNumbers.size()){
		//code to execute when all entire set has been check and XMAS has not failed.
		return true;
	}

	long long numberToCheck = _inputNumbers[_preambleEnd+1]; // next number after the preamble.
	long long numberOne;
	long long numberToFind;

	for(int i = _preambleBegin; i <= _preambleEnd; i++){
		numberOne = _inputNumbers[i];
		numberToFind = numberToCheck - numberOne;
		for(int b = _preambleBegin; b <= _preambleEnd; b++){
			/*
			cout << "///////////////" << endl;
			cout << "number to check:" << numberToCheck << endl;
			cout << "number one: " << numberOne << endl;
			cout << "number to find: " << numberToFind << endl;
			cout << "number finded: " << _inputNumbers[b] << endl;
			*/
			if(_inputNumbers[b] == numberToFind && _inputNumbers[b] != numberOne){
				//code to execute when XMAS rule is ok.
				return check_XMAS_rule(_inputNumbers, _preambleBegin+1, _preambleEnd+1);
			}
		}
	}
	//code to execute when xmas rule have failed.
	cout << "Number that failed: " << numberToCheck << endl;
	return false;
}

int main(int argc, char const *argv[]) {

	vector<long long> inputNumbers;
	long long number;
	while(cin >> number){
		inputNumbers.insert(inputNumbers.end(), number);
	}

	int preambleSize = 25;
	int preambleBegin = 0;
	int preambleEnd = preambleSize-1;


	if(check_XMAS_rule(inputNumbers, preambleBegin, preambleEnd)){
		cout << "All entire set is ok" << endl;
	}
	
}