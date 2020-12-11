#include <iostream>
#include <set>
using namespace std;

int main(int argc, char const *argv[]){

	set<int> adapters;
	int adapter;
	while(cin >> adapter){
		adapters.insert(adapter);
	}

	int lastAdapter = 0;
	int diferencesOfOne = 0;
	//considering device's built-in adapter allways will be 1 diference of three at least
	int diferencesOfThree = 1;
	for(auto & adapter : adapters){
		if(adapter-1 == lastAdapter){
			diferencesOfOne++;
		}else{
			diferencesOfThree++;
		}
		cout << "adapter jolts: " << adapter << endl;
		lastAdapter = adapter;
	}

	cout << "diferences of one: " << diferencesOfOne <<" diferences of three: " << diferencesOfThree << endl;
	cout << "result of part One: " << diferencesOfOne * diferencesOfThree << endl;
}