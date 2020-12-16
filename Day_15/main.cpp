#include <iostream>
#include <map>
#include <vector>
using namespace std;

void play_game(vector<unsigned int> &_input, long long &_turns){
	map<unsigned int, unsigned int> numbers_turns; //first number, second turn.


	unsigned int curTurn;
	unsigned int nextTurn;
	for(long long i = 0; i < _turns; i++){
		if(i < _input.size()){
			numbers_turns[_input[i]] = i+1;
			//cout << "say: " << _input[i] << " turn: " << i+1 << endl;
			curTurn = _input[i];
		}else{
			if(numbers_turns.find(curTurn) == numbers_turns.end()){
				numbers_turns[curTurn] = i;
			}
			if(numbers_turns.find(curTurn)->second == i){
				nextTurn = 0;
				//cout << "say: " << nextTurn << " turn: " << i+1 << endl;
				curTurn = nextTurn;
			}else{
				nextTurn = (i) - numbers_turns.find(curTurn)->second;
				//cout << "say: " << nextTurn << " turn: " << i+1 << endl;
				numbers_turns[curTurn] = i;
				curTurn = nextTurn;
			}
		}
	}
	cout << "last turn: " << curTurn << endl;
}


int main(int argc, char const *argv[]){

	vector<unsigned int> input = {0, 13, 1, 16, 6, 17};
	long long iterations = 30000000;

	play_game(input, iterations);

}