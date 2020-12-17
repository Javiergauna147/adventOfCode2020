#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct RangeOfValues{
	int min;
	int max;
};

struct FieldOfTicket{
	string name;
	vector<RangeOfValues> ranges;
};

int main(int argc, char const *argv[]){

	string lineNoFormat;
	while(getline(cin, lineNoFormat)){
		cout << lineNoFormat << endl;

		FieldOfTicket field;

		//take name of field.
		string nameOfField = lineNoFormat.substr(0, lineNoFormat.find(":"));
		cout << "name: " << nameOfField << endl;
		field.name = nameOfField;

		string range1NoFormat = lineNoFormat.substr(lineNoFormat.find(":")+2, (lineNoFormat.find("or") - lineNoFormat.find(":"))-3);
		cout << "range 1: " << range1NoFormat << endl;

		//take values of tange 1.
		RangeOfValues range;
		string range1Min = range1NoFormat.substr(0, range1NoFormat.find("-"));
		stringstream range1MinString(range1Min);
		int range1MinNumber;
		range1MinString >> range1MinNumber;
		range.min = range1MinNumber;
		cout << "range 1 min: " << range1Min << endl;
		string range1Max = range1NoFormat.substr(range1NoFormat.find("-")+1, range1NoFormat.length());
		stringstream range1MaxString(range1Max);
		int range1MaxNumber;
		range1MaxString >> range1MaxNumber;
		range.max = range1MaxNumber;
		cout << "range 1 max: " << range1Max << endl;
		field.ranges.push_back(range);

		//take values of range 2.
		string range2Noformat = lineNoFormat.substr(lineNoFormat.find("or")+3, lineNoFormat.length());
		cout << "range 2: " << range2Noformat << endl;
		string range2Min = range2Noformat.substr(0, range2Noformat.find("-"));
		cout << "range 2 min: " << range2Min << endl;
		string range2Max = range2Noformat.substr(range2Noformat.find("-")+1, range2Noformat.length());
		cout << "range 2 max: " << range2Max << endl;
		break;
	}

}