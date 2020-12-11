#include <iostream>
#include <string>
#include <vector>
using namespace std;


size_t check_ocuppied_seats(int _coordenateX, int _coordenateY, vector<vector<string>> &_placesInFerry){
	size_t ocuppiedSeats = 0;
	int ferryWidth = _placesInFerry[0].size();
	int ferryHigh = _placesInFerry.size();
	//check right
	if(_coordenateY +1 < ferryWidth){
		if(_placesInFerry[_coordenateX][_coordenateY+1] == "#"){ocuppiedSeats++;}
	}
	//check left
	if(_coordenateY -1 > -1){
		if(_placesInFerry[_coordenateX][_coordenateY-1] == "#"){ocuppiedSeats++;}
	}
	//check top
	if(_coordenateX -1 > -1){
		if(_placesInFerry[_coordenateX-1][_coordenateY] == "#"){ocuppiedSeats++;}
	}
	//check button
	if(_coordenateX +1 < ferryHigh){
		if(_placesInFerry[_coordenateX+1][_coordenateY] == "#"){ocuppiedSeats++;}
	}
	//check top right
	if(_coordenateX -1 > -1 && _coordenateY +1 < ferryWidth){
		if(_placesInFerry[_coordenateX-1][_coordenateY+1] == "#"){ocuppiedSeats++;}
	}
	//check top left
	if(_coordenateX -1 > -1 && _coordenateY -1 > -1){
		if(_placesInFerry[_coordenateX-1][_coordenateY-1] == "#"){ocuppiedSeats++;}
	}
	//check button right
	if(_coordenateX +1 < ferryHigh && _coordenateY +1 < ferryWidth){
		if(_placesInFerry[_coordenateX+1][_coordenateY+1] == "#"){ocuppiedSeats++;}
	}
	//check button left
	if(_coordenateX +1 < ferryHigh && _coordenateY -1 > -1){
		if(_placesInFerry[_coordenateX+1][_coordenateY-1] == "#"){ocuppiedSeats++;}
	}

	return ocuppiedSeats;
}

void print_places_in_ferry(vector<vector<string>> &_placesInFerry){
	for(size_t i = 0; i < _placesInFerry.size(); i++){
		for(size_t j = 0; j < _placesInFerry[i].size(); j++){
			cout << _placesInFerry[i][j];
		}
		cout << endl;
	}
}

void predict_people_seats(vector<vector<string>> &_placesInFerry){
	vector<vector<string>> placesInFerryCopy = _placesInFerry;

	for(size_t i = 0; i < _placesInFerry.size(); i++){
		for(size_t j = 0; j < _placesInFerry[i].size(); j++){
			if(_placesInFerry[i][j] != "."){
				size_t adyacentOcuppiedSeats = check_ocuppied_seats(i, j, _placesInFerry);;
				if(_placesInFerry[i][j] == "L"){
					if(adyacentOcuppiedSeats == 0){placesInFerryCopy[i][j] = "#";}
				}else{
					if(adyacentOcuppiedSeats >= 4){placesInFerryCopy[i][j] = "L";}
				}
			}
		}
	}
	_placesInFerry = placesInFerryCopy;
}
size_t count_ocuppied_seats(vector<vector<string>> &_placesInFerry){
	size_t ocuppiedSeats = 0;
	for(size_t i = 0; i < _placesInFerry.size(); i++){
		for(size_t j = 0; j < _placesInFerry[i].size(); j++){
			if(_placesInFerry[i][j] == "#"){
				ocuppiedSeats++;
			}
		}
	}
	return ocuppiedSeats;
}

int main(int argc, char const *argv[]){
	string fileInString;
	vector<vector<string>> placesInFerry;
	while(cin >> fileInString){
		vector<string> y;
		for(size_t i = 0; i < fileInString.length(); i++){
			y.push_back(fileInString.substr(i,1));
		}
		placesInFerry.push_back(y);
	}

	int ocuppiedSeats = 0;
	int lastPredictOcuppiedSeats = ocuppiedSeats;
	while(true){
		//print_places_in_ferry(placesInFerry);
		predict_people_seats(placesInFerry);
		ocuppiedSeats = count_ocuppied_seats(placesInFerry);
		cout << "ocuppied seats: " << ocuppiedSeats << endl;
		cout << "/////////////////" << endl;
		if(ocuppiedSeats == lastPredictOcuppiedSeats){
			break;
		}
		lastPredictOcuppiedSeats = ocuppiedSeats;
	}

}