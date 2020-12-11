#include <iostream>
#include <string>
#include <vector>
using namespace std;


size_t check_ocuppied_seats(int _coordenateX, int _coordenateY, vector<vector<string>> &_placesInFerry){
	size_t ocuppiedSeats = 0;
	int ferryWidth = _placesInFerry[0].size();
	int ferryHigh = _placesInFerry.size();
	int coordenateItr;
	//check right
	coordenateItr = 1;
	while(_coordenateY + coordenateItr < ferryWidth){
		if(_placesInFerry[_coordenateX][_coordenateY + coordenateItr] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX][_coordenateY + coordenateItr] == "L"){break;}
		coordenateItr++;
	}
	//check left
	coordenateItr = 1;
	while(_coordenateY - coordenateItr > -1){
		if(_placesInFerry[_coordenateX][_coordenateY - coordenateItr] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX][_coordenateY - coordenateItr] == "L"){break;}
		coordenateItr++;
	}
	//check top
	coordenateItr = 1;
	while(_coordenateX - coordenateItr > -1){
		if(_placesInFerry[_coordenateX - coordenateItr][_coordenateY] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX - coordenateItr][_coordenateY] == "L"){break;}
		coordenateItr++;
	}
	//check button
	coordenateItr = 1;
	while(_coordenateX + coordenateItr < ferryHigh){
		if(_placesInFerry[_coordenateX + coordenateItr][_coordenateY] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX + coordenateItr][_coordenateY] == "L"){break;}
		coordenateItr++;
	}
	//check top right
	coordenateItr = 1;
	while(_coordenateX - coordenateItr > -1 && _coordenateY + coordenateItr < ferryWidth){
		if(_placesInFerry[_coordenateX - coordenateItr][_coordenateY + coordenateItr] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX - coordenateItr][_coordenateY + coordenateItr] == "L"){break;}
		coordenateItr++;
	}
	//check top left
	coordenateItr = 1;
	while(_coordenateX - coordenateItr > -1 && _coordenateY - coordenateItr > -1){
		if(_placesInFerry[_coordenateX - coordenateItr][_coordenateY - coordenateItr] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX - coordenateItr][_coordenateY - coordenateItr] == "L"){break;}
		coordenateItr++;
	}
	//check button right
	coordenateItr = 1;
	while(_coordenateX + coordenateItr < ferryHigh && _coordenateY + coordenateItr < ferryWidth){
		if(_placesInFerry[_coordenateX + coordenateItr][_coordenateY + coordenateItr] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX + coordenateItr][_coordenateY + coordenateItr] == "L"){break;}
		coordenateItr++;
	}
	//check button left
	coordenateItr = 1;
	while(_coordenateX + coordenateItr < ferryHigh && _coordenateY - coordenateItr > -1){
		if(_placesInFerry[_coordenateX + coordenateItr][_coordenateY - coordenateItr] == "#"){ocuppiedSeats++;break;}
		if(_placesInFerry[_coordenateX + coordenateItr][_coordenateY - coordenateItr] == "L"){break;}
		coordenateItr++;
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
					if(adyacentOcuppiedSeats >= 5){placesInFerryCopy[i][j] = "L";}
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