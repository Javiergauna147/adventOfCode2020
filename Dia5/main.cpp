/*
--- Day 5: Binary Boarding ---
You board your plane only to discover a new problem: you dropped your boarding pass! You aren't sure which seat is yours, and all of the flight attendants are busy with the flood of people that suddenly made it through passport control.

You write a quick program to use your phone's camera to scan all of the nearby boarding passes (your puzzle input); perhaps you can find your seat through process of elimination.

Instead of zones or groups, this airline uses binary space partitioning to seat people. A seat might be specified like FBFBBFFRLR, where F means "front", B means "back", L means "left", and R means "right".

The first 7 characters will either be F or B; these specify exactly one of the 128 rows on the plane (numbered 0 through 127). Each letter tells you which half of a region the given seat is in. Start with the whole list of rows; the first letter indicates whether the seat is in the front (0 through 63) or the back (64 through 127). The next letter indicates which half of that region the seat is in, and so on until you're left with exactly one row.

For example, consider just the first seven characters of FBFBBFFRLR:

Start by considering the whole range, rows 0 through 127.
F means to take the lower half, keeping rows 0 through 63.
B means to take the upper half, keeping rows 32 through 63.
F means to take the lower half, keeping rows 32 through 47.
B means to take the upper half, keeping rows 40 through 47.
B keeps rows 44 through 47.
F keeps rows 44 through 45.
The final F keeps the lower of the two, row 44.
The last three characters will be either L or R; these specify exactly one of the 8 columns of seats on the plane (numbered 0 through 7). The same process as above proceeds again, this time with only three steps. L means to keep the lower half, while R means to keep the upper half.

For example, consider just the last 3 characters of FBFBBFFRLR:

Start by considering the whole range, columns 0 through 7.
R means to take the upper half, keeping columns 4 through 7.
L means to take the lower half, keeping columns 4 through 5.
The final R keeps the upper of the two, column 5.
So, decoding FBFBBFFRLR reveals that it is the seat at row 44, column 5.

Every seat also has a unique seat ID: multiply the row by 8, then add the column. In this example, the seat has ID 44 * 8 + 5 = 357.

Here are some other boarding passes:

BFFFBBFRRR: row 70, column 7, seat ID 567.
FFFBBBFRRR: row 14, column 7, seat ID 119.
BBFFBBFRLL: row 102, column 4, seat ID 820.
As a sanity check, look through your list of boarding passes. What is the highest seat ID on a boarding pass?
--- Part Two ---
Ding! The "fasten seat belt" signs have turned on. Time to find your seat.

It's a completely full flight, so your seat should be the only missing boarding pass in your list. However, there's a catch: some of the seats at the very front and back of the plane don't exist on this aircraft, so they'll be missing from your list as well.

Your seat wasn't at the very front or back, though; the seats with IDs +1 and -1 from yours will be in your list.

What is the ID of your seat?
*/
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <set>
using namespace std;

string take_row_partition(string _binaryPartition){
    return _binaryPartition.substr(0,7);
}
string take_column_partition(string _binaryPartition){
    return _binaryPartition.substr(7,3);
}

bool validate_partition(string _binaryPartition){
    if(_binaryPartition.length() == 10){
        string rowPartition = take_row_partition(_binaryPartition);
        string columnPartition = take_column_partition(_binaryPartition);

        for(unsigned int i = 0; i < rowPartition.length(); i++){
            if(rowPartition[i] != 'B' && rowPartition[i] != 'F'){
                return false;
            }
        }
        for(unsigned int i = 0; i < columnPartition.length(); i++){
            if(columnPartition[i] != 'L' && columnPartition[i] != 'R'){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

int find_number_of_row(string _rowPartition){
    unsigned short minRow = 0;
    unsigned short maxRow = 127;
    unsigned short b = 0;
    for(unsigned int i = _rowPartition.length(); i > 0; i--){
        switch (i){
            case 1:
                if(_rowPartition[b] == 'F'){
                    return minRow;
                }else{
                    return maxRow;
                }
            break;
            case 2:
                if(_rowPartition[b] == 'F'){
                    maxRow -= pow(2, i-1);
                }else{
                    minRow += pow(2,i-1);
                }
            break;
            case 3:
                if(_rowPartition[b] == 'F'){
                    maxRow -= pow(2, i-1);
                }else{
                    minRow += pow(2,i-1);
                }
            break;
            case 4:
                if(_rowPartition[b] == 'F'){
                    maxRow -= pow(2, i-1);
                }else{
                    minRow += pow(2,i-1);
                }
            break;
            case 5:
                if(_rowPartition[b] == 'F'){
                    maxRow -= pow(2, i-1);
                }else{
                    minRow += pow(2,i-1);
                }
            break;
            case 6:
                if(_rowPartition[b] == 'F'){
                    maxRow -= pow(2, i-1);
                }else{
                    minRow += pow(2,i-1);
                }
            break;
            case 7:
                if(_rowPartition[b] == 'F'){
                    maxRow -= pow(2, i-1);
                }else{
                    minRow += pow(2,i-1);
                }
            break;
            default: return 255; break;
        }
        b++;
    }
    return 255;
}
int find_number_of_column(string _columnPartition){
    unsigned short minColumn = 0;
    unsigned short maxColumn = 7;
    unsigned short b = 0;
    for(unsigned int i = _columnPartition.length(); i > 0; i--){
        switch(i){
            case 1:
                if(_columnPartition[b] == 'L'){
                    return minColumn;
                }else{
                    return maxColumn;
                }
            break;
            case 2:
                if(_columnPartition[b] == 'L'){
                    maxColumn -= pow(2, i-1);
                }else{
                    minColumn += pow(2,i-1);
                }
            break;
            case 3:
                if(_columnPartition[b] == 'L'){
                    maxColumn -= pow(2, i-1);
                }else{
                    minColumn += pow(2,i-1);
                }
            break;
            default: return 255; break;
        }
        b++;
    }
    return 255;
}


int main(int argc, char const *argv[]) {

    int seatID;
    int maxSeatID = 0;
    set<int> seatsID;
    set<int> posiblesIDsOfYourSeat;
    int amountOfSeats = 0;
    int mySeatID;
    string binaryPartition;
    while(cin >> binaryPartition){
        if (validate_partition(binaryPartition)){
            seatID = find_number_of_row(take_row_partition(binaryPartition))*8+find_number_of_column(take_column_partition(binaryPartition));
            seatsID.insert(seatsID.end(), seatID);
            amountOfSeats++;
            if(seatID > maxSeatID){
                maxSeatID = seatID;
            }
        }else{
            cout << "INVALID PARTITION" << endl;
        }
    }
    for(auto &id : seatsID){
        if(seatsID.find(id+1) == seatsID.end()){
            if(seatsID.find(id+2) != seatsID.end()){
                mySeatID = id+1;
            }
        }
    }
    cout << "Max seat ID: " << maxSeatID << endl;
    cout << "My seat ID: " << mySeatID << endl;
}