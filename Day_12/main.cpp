#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
using namespace std;

struct Action{
	string character;
	int value;
};
struct FerryCoordinates{
	string curDirection = "E";
	int north_south = 0;
	int east_west = 0;
};
void turn_ferry(FerryCoordinates &_actualFerryCoordinates, int &_grades){
	int unitsToTurn = _grades/90;
	unitsToTurn -= 1;
	string nCase[3] = {"E", "S", "W"};
	string eCase[3] = {"S", "W", "N"};
	string sCase[3] = {"W", "N", "E"};
	string wCase[3] = {"N", "E", "S"};
	if(_actualFerryCoordinates.curDirection == "N"){
		_actualFerryCoordinates.curDirection = nCase[unitsToTurn];
	}else if(_actualFerryCoordinates.curDirection == "E"){
		_actualFerryCoordinates.curDirection = eCase[unitsToTurn];
	}else if(_actualFerryCoordinates.curDirection == "S"){
		_actualFerryCoordinates.curDirection = sCase[unitsToTurn];
	}else if(_actualFerryCoordinates.curDirection == "W"){
		_actualFerryCoordinates.curDirection = wCase[unitsToTurn];
	}
}
void move_ferry_to_front(FerryCoordinates &_actualFerryCoordinates, int &_units){
	if(_actualFerryCoordinates.curDirection == "N"){
		_actualFerryCoordinates.north_south += _units;
	}
	if(_actualFerryCoordinates.curDirection == "E"){
		_actualFerryCoordinates.east_west += _units;
	}
	if(_actualFerryCoordinates.curDirection == "S"){
		_actualFerryCoordinates.north_south -= _units;
	}
	if(_actualFerryCoordinates.curDirection == "W"){
		_actualFerryCoordinates.east_west -= _units;
	}
}
void slide_ferry(FerryCoordinates &_actualFerryCoordinates, int &_units, string &_direction){
	if(_direction == "N"){
		_actualFerryCoordinates.north_south += _units;
	}
	if(_direction == "E"){
		_actualFerryCoordinates.east_west += _units;
	}
	if(_direction == "S"){
		_actualFerryCoordinates.north_south -= _units;
	}
	if(_direction == "W"){
		_actualFerryCoordinates.east_west -= _units;
	}
}

int main(int argc, char const *argv[]){

	string dataNoFormat;
	vector<Action> actions;
	while(cin >> dataNoFormat){
		stringstream valueOfNumber(dataNoFormat.substr(1, dataNoFormat.length()));
		Action action;
		valueOfNumber >> action.value;
		action.character = dataNoFormat.substr(0,1);
		actions.push_back(action);
	}

	FerryCoordinates actualFerryCoordinates;
	for(auto & action : actions){
		if(action.character == "F"){
			move_ferry_to_front(actualFerryCoordinates, action.value);
		}
		if(action.character == "R"){
			turn_ferry(actualFerryCoordinates, action.value);
		}
		if(action.character == "L"){
			int grades = 360 - action.value;
			turn_ferry(actualFerryCoordinates, grades);
		}
		if(action.character == "W" || action.character == "E" || action.character == "S" || action.character == "N"){
			slide_ferry(actualFerryCoordinates, action.value, action.character);
		}
	}
	cout << "north/south coordinate: " << actualFerryCoordinates.north_south << " east/west coordinate: " << actualFerryCoordinates.east_west << endl;
	cout << "Manhattan Distance: " << abs(actualFerryCoordinates.north_south) + abs(actualFerryCoordinates.east_west) << endl;
}