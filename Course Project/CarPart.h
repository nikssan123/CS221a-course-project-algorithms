#pragma once
#ifndef _CARPART_
#define _CARPART_
#include "Part.h"

//vector ids

class CarPart : public Part {

private:
	//Properties
	string description = "", name;  
	double price;
	int amount;
	int idnr;
	bool isNew;

	//method to check if the id is available
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

	//method to set the price discount if available
	double setPriceDiscount(bool isNew, double price) {
		if (price > 0) {
			if (!isNew) {
				return price - (price * 0.1);
			}
			else
				return price;
		}
		else
			return 0;
	}

public:


	//Constructors
	CarPart(): description(""), name(""), price(0), amount(0){}
	CarPart(string description1, string name1, int idnr1, int amount1, bool isNew1, double price1) : description(description1), name(name1), amount(amount1), isNew(isNew1) {
		if (isIDFree(idnr1)) {
			ids.push_back(idnr1);
			idnr = idnr1;
		}

		price = setPriceDiscount(isNew1, price1);

	}

	CarPart(string description1, string name1, int idnr1, int amount1, double price1) : description(description1), name(name1), amount(amount1), price(price1) {
		if (isIDFree(idnr1)) {
			ids.push_back(idnr1);
			idnr = idnr1;
		}
	}

	CarPart(string name1, int idnr1, int amount1, bool isNew1, double price1) : name(name1), amount(amount1), isNew(isNew1), price(price1) {
		if (isIDFree(idnr1)) {
			ids.push_back(idnr1);
			idnr = idnr1;
		}
	}

	//Getters
	//Overriding the abstract functions
	string GetName() {
		return  name;
	}

	double GetPrice() const {
		return price * amount;
	}

	int getAmount() {
		return amount;
	}

	string getDescription() {
		return description;
	}

	bool IsNew() {

		return isNew;

	}



};

#endif // !_CARPART_

