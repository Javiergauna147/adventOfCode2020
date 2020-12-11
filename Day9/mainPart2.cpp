#include <iostream>
#include <vector>
#include <set>
using namespace std;


long long check_XMAS_rule(vector<long long> &_inputNumbers, int _preambleBegin, int _preambleEnd){

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
	return numberToCheck;
}

long long break_XMAS_encryption(vector<long long> &_inputNumbers, long long &_numberToEqual, int _itrPositionBegin){

	set<long long> numbersUsed;
	long long acumulator = 0;
	int itr = _itrPositionBegin;
	while(true){
		acumulator += _inputNumbers[itr];
		numbersUsed.insert(numbersUsed.end(), _inputNumbers[itr]);
		if(acumulator > _numberToEqual){
			//acumulator passed the number
			return break_XMAS_encryption(_inputNumbers, _numberToEqual, _itrPositionBegin+1);
		}else if(acumulator == _numberToEqual){
			//sequence of numbers finded
			auto lessNumber = numbersUsed.begin();
			auto lastNumber = numbersUsed.end();
			lastNumber--;
			return *lessNumber + *lastNumber;
		}else{
			//acumulator is less than the number
			itr++;
		}
	}
}


int main(int argc, char const *argv[]){

	vector<long long> inputNumbers;
	long long number;
	while(cin >> number){
		inputNumbers.insert(inputNumbers.end(), number);
	}

	int preambleSize = 25;
	int preambleBegin = 0;
	int preambleEnd = preambleSize-1;
	long long numberThatFailed = 0;

	numberThatFailed = check_XMAS_rule(inputNumbers, preambleBegin, preambleEnd);
	cout << "number that failed: " << numberThatFailed << endl;

	cout << "Breaking the encryption: " << break_XMAS_encryption(inputNumbers, numberThatFailed, 0) << endl;
}