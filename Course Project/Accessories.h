#include "Part.h"
#pragma once
#ifndef  _ACCESSORIES_
#define _ACCESSORIES_

//vector<int> idsA;

class Accessories : public Part {

private:

	//properties 
	string description, name;
	double percentDiscount;
	double price;
	int amount, idnr;

	//function to check availability of ids
	bool isIDFree(int id) {
		bool result;
		if (ids.size() == 0)
			result = true;
		else {
			for (int i = 0; i < ids.size(); i++) {
				if (ids[i] == id) {
					cout << "Error can't have a part with the same ID!" << endl;
					result = false;
				}
				else
					result = true;
			}
		}

		return result;
	}

public:

	//Constructors
	Accessories(string description1, string name1, int id, int amount1, double price1, double percentDiscount1) : description(description1), name(name1) {
		if (isIDFree(id)) {
			ids.push_back(id);
			idnr = id;
		}

		if (price1 > 0)
			price = price1;
		else
			price = 1;

		if (amount1 > 0)
			amount = amount1;
		else
			amount = 1;


		if (percentDiscount1 > 0 && percentDiscount1 < 50)
			percentDiscount = percentDiscount1;
		else
			percentDiscount = 0;
	}

	Accessories(string name1, int id, int amount1, double price1) : name(name1) {
		if (isIDFree(id)) {
			ids.push_back(id);
			idnr = id;
		}

		if (price1 > 0)
			price = price1;
		else
			price = 1;

		if (amount1 > 0)
			amount = amount1;
		else
			amount = 1;
	}

	//overriding abstract methods
	string GetName() {
		return "The name of the accessory is: " + name;
	}

	double GetPrice() const {
		double result;

		if (percentDiscount > 0)
			result = (price * amount) - ((price * amount) * (percentDiscount / 100));
		else
			result = price * amount;

		return result;
	}

	void display() {
		cout << "-------------" << endl;
		cout << "Accessory: " << name << "\nDescription: " << description << "\nPrice: " << GetPrice() << endl;
		cout << "-------------" << endl;
	}


};


#endif // ! _ACCESSORIES_

