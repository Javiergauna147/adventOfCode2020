#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Bus{
	int id;
	int nextDepart = 0;
};

vector<Bus> alist_buses(){
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
			Bus bus;
			bus.id = busId;
			buses.push_back(bus);
		}

		if(availableBusesNoFormat.find(",") != -1){
			availableBusesNoFormat.erase(0, availableBusesNoFormat.find(",")+1);
		}else{
			break;
		}
	}
	return buses;
}


int main(int argc, char const *argv[]){
	
	//take first line of input
	size_t departTimeStamp;
	cin >> departTimeStamp;
	//take second line of input
	vector<Bus> buses = alist_buses();

	//find my bus
	size_t actualTime = 0;
	int ableToDepartTime = -1;
	bool readyToGo = false;
	size_t myBusId;

	/*
	for(auto & bus : buses){
		cout << bus.id << "-";
	}
	cout << endl;
	cout << "------------------" << endl;
	*/
	while(ableToDepartTime == -1){
		if(actualTime == departTimeStamp){
			readyToGo = true;
		}
		for(auto & bus : buses){
			if(bus.nextDepart == actualTime){
				//cout << "D-";
				if(readyToGo){
					myBusId = bus.id;
					ableToDepartTime = actualTime;
				}
				bus.nextDepart += bus.id;
			}else{
				//cout << ".-";
			}
		}
		//cout << " " << actualTime << endl;
		actualTime++;
	}
	size_t timeToWait = ableToDepartTime - departTimeStamp;
	cout << "My next bus id: " << myBusId << " time to depart: " << ableToDepartTime << endl;
	cout << "is needed to wait: " << timeToWait << " minutes" << endl;
	cout << "answer: " << timeToWait * myBusId << endl;
}