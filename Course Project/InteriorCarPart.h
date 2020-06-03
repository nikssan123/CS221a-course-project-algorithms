#pragma once
#include "CarPart.h"
#ifndef _INTERIORCARPART_
#define _INTERIORCARPART_


class InteriorCarPart : public CarPart {

private:
	//new properties
	double wagePercent;
	string material;
	Color color;




public:

	//Constructors, using the parent class constructor
	InteriorCarPart(string description1, string name1, int idnr1, int amount1, bool isNew1, double price1, double wagePercent1, string material1, Color color1) 
		: CarPart(description1, name1, idnr1, amount1, isNew1,  price1), color(color1), material(material1) {
		if (CarPart::IsNew()) {
			wagePercent = wagePercent1 / 100;
		}
		else {
			wagePercent = wagePercent1 / 110; //The employee is less paid if the part is second hand
		}

	}

	//overriding the functions of the base class
	double GetPrice() const {
		return (CarPart::GetPrice() * wagePercent) + CarPart::GetPrice();
	}

	string getMaterial() {
		return material;
	}

	Color getColor() {
		return color;
	}


	void display() {
		cout.precision(4);
		cout << "-------------" << endl;
		cout << "Interior Car part: " << CarPart::GetName()  << "\nDescription: " << getDescription() <<"\nMaterial: " << material << "\nColor: " << Part::getColor(color) << "\nPrice: " << GetPrice() << endl;
		cout << "-------------" << endl;
	}

};


#endif // !_INTERIORCARPART_

