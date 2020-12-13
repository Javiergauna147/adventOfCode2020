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
	int north_south = 0;
	int east_west = 0;
};
struct WayPoint{
	int north_south = 1;
	int east_west = 10;
};

void move_way_point(WayPoint &_wayPoint, int &_units, string &_direction){
	if(_direction == "N"){
		_wayPoint.north_south += _units;
	}
	if(_direction == "E"){
		_wayPoint.east_west += _units;
	}
	if(_direction == "S"){
		_wayPoint.north_south -= _units;
	}
	if(_direction == "W"){
		_wayPoint.east_west -= _units;
	}
}
void rotate_way_point_90_degress(WayPoint &_wayPoint){
	int aux = _wayPoint.east_west;
	_wayPoint.east_west = _wayPoint.north_south;
	_wayPoint.north_south = aux * -1;
}
void turn_way_point(WayPoint &_wayPoint, int &_grades){
	int unitsToTurn = _grades/90;
	for(int i = 0; i < unitsToTurn; i++){
		rotate_way_point_90_degress(_wayPoint);
	}
}

void move_ferry(WayPoint &_wayPoint, FerryCoordinates &_actualFerryCoordinates, int &_units){
	int north_southMove = _wayPoint.north_south * _units;
	int east_westMove = _wayPoint.east_west * _units;

	_actualFerryCoordinates.north_south += north_southMove;
	_actualFerryCoordinates.east_west += east_westMove;
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
	WayPoint wayPoint;
	for(auto & action : actions){
		if(action.character == "F"){
			move_ferry(wayPoint, actualFerryCoordinates, action.value);
		}
		if(action.character == "R"){
			turn_way_point(wayPoint, action.value);
		}
		if(action.character == "L"){
			int grades = 360 - action.value;
			turn_way_point(wayPoint, grades);
		}
		if(action.character == "W" || action.character == "E" || action.character == "S" || action.character == "N"){
			move_way_point(wayPoint, action.value, action.character);
		}
	}
	cout << "north/south coordinate: " << actualFerryCoordinates.north_south << " east/west coordinate: " << actualFerryCoordinates.east_west << endl;
	cout << "Manhattan Distance: " << abs(actualFerryCoordinates.north_south) + abs(actualFerryCoordinates.east_west) << endl;
}