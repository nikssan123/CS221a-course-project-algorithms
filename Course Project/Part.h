#pragma once
#ifndef _PART_
#define _PART_
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> ids;

enum Color {Red = 0, Green, Blue, Yellow, White, Black};


class Part {   //the abstract base class

protected:

	string getColor(Color color) {   //function to convert from enum to string
		switch (color) {
		case 0:
			return "Red";
		case 1:
			return "Green";
		case 2:
			return "Blue";
		case 3:
			return "Yellow";
		case 4:
			return "White";
		case 5:
			return "Black";
		}
	}



public:
	virtual string GetName() = 0;
	virtual double GetPrice() const = 0;    //abstract methods
	virtual void display() = 0 {}
};


#endif // !1



