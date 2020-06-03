#pragma once
#include "CarPart.h"
#ifndef  _ENGINE_
#define _ENGINE_


class Engine : public CarPart {


private:
	//adding properties for the engine class
	double hourlyRate;
	double hours;
	int horsePower;


public:
	//Constructors using the parent class constructor
	Engine(string description1, string name1, int idnr1, int amount1, bool isNew1, double price1, double hourlyRate1, double hours1, int horsePower1)
		: CarPart(description1, name1, idnr1, amount1, isNew1, price1), hourlyRate(hourlyRate1), horsePower(horsePower1) {
		if (hours1 > 0)
			hours = hours1;
		else
			hours = 0;

	}

	Engine(string name1, int idnr1, int amount1, bool isNew1, double price1, double hourlyRate1, double hours1, int horsePower1)
		: CarPart(name1, idnr1, amount1, isNew1, price1), hourlyRate(hourlyRate1), horsePower(horsePower1) {
		if (hours1 > 0)
			hours = hours1;
		else
			hours = 0;

	}

	//overriding the abstract methods
	//getters
	double GetPrice() const {
		double price;
		price = CarPart::GetPrice() * (hourlyRate * hours);
		if (price > 0 && price < 1000000)
			return price;
		else
			return 1;
	}
	
	int getHorsePower() {
		return horsePower;
	}

	//setters
	void setHourlyRate(double rate) {
		hourlyRate = rate;
	}

	void setHours(double hours1) {
		hours = hours1;
	}



	void display() {
		cout.precision(6);
		cout << "-------------" << endl;
		cout << "Engine: " << CarPart::GetName() << "\nDescription: " << getDescription() << "\nHorse Power: " << horsePower << "\nPrice: " << GetPrice() << endl;
		cout << "-------------" << endl;
	}




};
#endif // ! _ENGINE_

