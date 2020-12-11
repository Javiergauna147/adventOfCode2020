#include <iostream>
#include <string>
#include <vector>
using namespace std;

void find_shortest_answer(vector<string> &_groupAnswer, string &_shortestAnswer){
	_shortestAnswer = _groupAnswer[0];
	for(auto & answer : _groupAnswer){
		if(_shortestAnswer.length() > answer.length()){
			_shortestAnswer = answer;
		}
	}
}
int calculate_sum_of_a_group(vector<string> &_groupAnswer){
	string shortestAnswer;
	int sum = 0;
	int answerInTheGroup = 0;

	find_shortest_answer(_groupAnswer, shortestAnswer);


	for(unsigned int i = 0; i < shortestAnswer.length(); i++){
		answerInTheGroup = 0;
		for(auto & answer : _groupAnswer){
			if(answer.find(shortestAnswer[i]) != -1){
				answerInTheGroup++;
			}
		}
		if(answerInTheGroup == _groupAnswer.size()){
			sum++;
		}
	}
	_groupAnswer.clear();
	return sum;
}

int main(int argc, char const *argv[]){
	
	vector<string> groupAnswer;
	string personAnswers;
	int resultPartTwo = 0;

	while(getline(cin, personAnswers)){
		if(personAnswers == ""){
			resultPartTwo += calculate_sum_of_a_group(groupAnswer);
		}
		if(personAnswers != ""){
			groupAnswer.insert(groupAnswer.end(), personAnswers);
		}
	}
	resultPartTwo += calculate_sum_of_a_group(groupAnswer);
	cout << "Sum of Part two: " << resultPartTwo << endl;
}