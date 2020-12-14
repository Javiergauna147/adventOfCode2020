#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Code solution based on: https://www.reddit.com/r/adventofcode/comments/kcb3bb/2020_day_13_part_2_can_anyone_tell_my_why_this/

// Utility function to find 
// GCD of 'a' and 'b' 
long long gcd(long long a, long long b){ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 
  
// Returns LCM of vector elements 
long long findlcm(vector<int> arr){ 
    // Initialize result 
    long long ans = arr[0]; 
  
    // ans contains LCM of arr[0], ..arr[i] 
    // after i'th iteration, 
    for (int i = 1; i < arr.size(); i++) 
        ans = (((arr[i] * ans)) / 
                (gcd(arr[i], ans))); 
  
    return ans; 
} 


struct Bus{
	int id = 0;
};

vector<Bus> alist_buses_and_find_lower_id(int &_lowestIdBus){
	vector<Bus> buses;
	string availableBusesNoFormat;
	cin >> availableBusesNoFormat;
	string busIdString;
	int busId;
	while(true){
		busIdString = availableBusesNoFormat.substr(0, availableBusesNoFormat.find(","));
		if(busIdString != "x"){
			stringstream number(busIdString);
			number >> busId;
			if(busId > _lowestIdBus){
				_lowestIdBus = busId;
			}
			Bus bus;
			bus.id = busId;
			buses.push_back(bus);
		}else{
			Bus bus;
			bus.id = -1;
			buses.push_back(bus);
		}

		if(availableBusesNoFormat.find(",") != -1){
			availableBusesNoFormat.erase(0, availableBusesNoFormat.find(",")+1);
		}else{
			break;
		}
	}
	for(auto & bus : buses){
		if(bus.id < _lowestIdBus && bus.id != -1){
			_lowestIdBus = bus.id;
		}
	}
	return buses;
}

vector<long long> find_jumps(vector<Bus> &_buses, int _firstJump){
	vector<long long> jumps;
	vector<int> positivesIds;
	jumps.push_back(_firstJump);
	long long jump;
	for(size_t i = 0; i < _buses.size(); i++){
		if(_buses[i].id != -1){
			positivesIds.push_back(_buses[i].id);
			if(positivesIds.size() > 1){
				jumps.push_back(findlcm(positivesIds));
			}
		}
	}
	return jumps;
}

bool find_subsequent(long long curTimeStamp, vector<Bus> &_buses, int &_curItrJump){
	size_t joker = 0;
	size_t itr = 0;
	long long earlyTimeStamp = curTimeStamp;
	int secuenceFinded = 0;
	while(itr != _buses.size()){
		if(_buses[itr].id != -1){
			//cout << "analizing id: " << _buses[itr].id << " on " << curTimeStamp << endl;
			if(curTimeStamp % _buses[itr].id != 0 && joker == 0){
				_curItrJump = secuenceFinded-1;
				return false;
			}else if(joker > 0){
				joker--; //use joker margin
				curTimeStamp++;
			}else{
				itr++;
				joker = 0;
				curTimeStamp++;
				secuenceFinded++;
			}
		}else{
			itr++;
			joker++;
		}
	}
	cout << "The event happens on: " << earlyTimeStamp << endl;
	return true;
}

int main(int argc, char const *argv[]){
	//take first line of input
	size_t departTimeStamp;
	cin >> departTimeStamp;


	//take second line of input
	int lowestIdBus;
	vector<Bus> buses = alist_buses_and_find_lower_id(lowestIdBus);

	vector<long long> jumps = find_jumps(buses, lowestIdBus);
	
	for(auto & jump : jumps){
		cout << "jump: " << jump << endl;
	}
	
	long long curTimeStamp = lowestIdBus;
	bool subsequentFinded = false;
	int curItrJump = 0;
	while(!subsequentFinded){
		subsequentFinded = find_subsequent(curTimeStamp, buses, curItrJump);
		curTimeStamp += jumps[curItrJump];
	}

}