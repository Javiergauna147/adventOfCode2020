#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[]){

	vector<int> adapters;
	int adapter;
	while(cin >> adapter){
		adapters.push_back(adapter);
	}
	sort(adapters.begin(), adapters.end());
	adapters.push_back(adapters.back() + 3); // we add the built-in device adapter

	/* we have two possible gaps between adapters 1 or 3, if we format the entire amount of adapters by gap of jolts it would be
	something like this [1,1,1],[3,3],[1],[3],[1,1,1,1] we cant move out the 3 gap adapters because  allways gonna be a diference
	of at least 4 jolts whit the next adapter, so we only can take off the 1 gap adapters, knowing that, the idea is realize how many
	diferent posibilites of conections haves a 1 gap group and then multiply the number of posibilities from all groups.
	knowing this:
	 [1]: only 1 combination
	 [1,1]: 2 combinations
	 [1,1,1]: 4 combinations
	 [1,1,1,1]: 7 combinations
	 obviusly we check that we dont have a bigger gruop of 1 gaps in the input that the 7 combination´s group.
	the example of above would be 4*1*7 = 28 combinations.
	*/

	//lastaAdapter adopt 0 as first value because is jolt from the conector.
	int lastAdapter = 0;
	int gapOneCounter = 0;
	long long answer = 1;

	for(size_t i = 0; i < adapters.size(); i++){
		cout << "adapter jolts: " << adapters[i] << endl;
		if(adapters[i] - lastAdapter == 1){ //we calculate the gap beetween to followed adapters.
			//cout << "gap: 1" << endl;
			gapOneCounter++;
		}else{
			//cout << "gap: 3" << endl;
			cout << "gap one counter: " << gapOneCounter << endl;
			switch(gapOneCounter){
				case 1: answer *= 1; break;
				case 2: answer *= 2; break;
				case 3: answer *= 4; break;
				case 4: answer *= 7; break;
				default: break;
			}
			gapOneCounter = 0;
		}
		lastAdapter = adapters[i];
	}


	cout << "amount of possible connections: " << answer << endl;
}