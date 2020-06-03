#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <sstream>
#include "Part.h"
#include "CarPart.h"
#include "InteriorCarPart.h"
#include "Engine.h"
#include "Accessories.h"


vector<Part*> engines;
vector<Part*> carParts;
vector<Part*> accessories;
vector<int> matcher;
string pattern = "";

//Merge sort algorithm
void merge(vector<Part*> &a, vector<Part*> tmpArray, int leftPos, int rightPos, int rightEnd) {
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	while (leftPos <= leftEnd && rightPos <= rightEnd)   // Main loop
		if (a[leftPos]->GetPrice() <= a[rightPos]->GetPrice())
			tmpArray[tmpPos++] = a[leftPos++];
		else
			tmpArray[tmpPos++] = a[rightPos++];

	while (leftPos <= leftEnd)   // Copy rest of first half
		tmpArray[tmpPos++] = a[leftPos++];

	while (rightPos <= rightEnd)   // Copy rest of right half
		tmpArray[tmpPos++] = a[rightPos++];

	for (int i = 0; i < numElements; i++, rightEnd--)   // Copy tmpArray back
		a[rightEnd] = tmpArray[rightEnd];
}

void mergeSort(vector<Part*>& a, vector<Part*> tmpArray, int left, int right)
{
	if (left < right) {
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}

void mergeSort(vector<Part*>& a)
{
	vector<Part*> tmpArray(a.size());
	mergeSort(a, tmpArray, 0, a.size() - 1);
}
//------------------------------------------------------

//Fill the array with processesed values for bad matches occurance -> to calculate the needed shift
void badCharHeuristic(string str, int size, int badchar[256]) {
	int i;

	for (i = 0; i < 256; i++)
		badchar[i] = -1;

	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}


//The actual search BM algorithm which uses the array with the bad heuristics
vector<int> search(string txt, string pat)
{
	int m = pat.size();
	int n = txt.size();
	vector<int> positions;      //create a vector to store all the current occurences of the pattern
	int badchar[256];


	badCharHeuristic(pat, m, badchar);

	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;

		while (j >= 0 && pat[j] == txt[s + j])
			j--;

		if (j < 0)
		{
			positions.push_back(s);
			if ((s + m) < n) {
				s += m - badchar[txt[s + m]];
			}
			else {
				s += 1;
			}

		}
		else
			s += max(1, j - badchar[txt[s + j]]);
	}

	return positions;
}

//function to check the validity of different variable
//for the Color enum
int validateColor() {
	int number;
	

	while (true) {
		while (!(cin >> number)) {
			cout << "Invalid input! Try again: ";
			cin.clear();
			cin.ignore(10000, '\n');
		}
		if (number >= 0 && number <= 5)
			return number;
		else
			cout << "Invalid input! Try again: ";
		
	}
	//return number;
}

//for the boolean variables
int validateBoolean() {
	int number;
	while (true) {
		while (!(cin >> number)) {
			cout << "Invalid input! Try again: ";
			cin.clear();
			cin.ignore(10000, '\n');
		}
		if (number == 0 || number == 1)
			return number;
		else
			cout << "Invalid input! Try again: ";
	}
}

//for numbers
double validateNumber() {
	double number;
	while (!(cin >> number)) {
		cout << "Invalid input! Try again: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	
	return number;
}

//function to insert new item to the shop which accepts the choice of the user as int
void insertNewItem(int choice) {
	system("CLS");  //clearing the console
	ofstream out;   //creating an output stream

	string description, name, material;
	int id, amount, horsePower, color;
	double price;
	bool isNew;
	double hourlyRate, hours, wagePercent, percenDiscount;
	//char color;

	if (choice == 1) {
		out.open("Engines.txt", ios_base::app);   //if the choice is 1 open the file containing engines
		if (out.fail()) {
			cerr << "Error with opening the file!" << endl;
		}
		cout << "\tAdding new engine to the shop!" << "\n--------------------------------------------\n";
		cout << "Enter description: ";
		cin.ignore();
		getline(cin, description);
		cout << "Enter name: ";
		getline(cin, name);
		cout << "Enter unique ID: "; id = (int) validateNumber();
		cout << "Enter amount: "; amount = (int) validateNumber();
		cout << "Is the engine new? (1 - Yes| 0 - No): "; isNew = (bool)validateBoolean();
		cout << "Enter price: "; price = validateNumber();
		cout << "Enter hourly rate: "; hourlyRate = validateNumber();
		cout << "Enter hours: "; hours = validateNumber();
		cout << "Enter the horse power of the engine: "; horsePower = (int)validateNumber();

		//write into the file the needed variables for the constructor
		if (out.is_open()) {
			out << description << " " << name << " " << id << " " << amount << " " << isNew << " " << price << " " << hourlyRate << " " << hours << " " << horsePower << endl;
			cout << "Engine item added successfully" << endl;
		}
		else 
			cout << "Error with adding the item!" << endl;
		
		//close
		out.close();

	} //repeat the same proccess for the other two opitons
	else if (choice == 2) {
		out.open("InteriorCarPart.txt", ios_base::app);   //for the Intirior car part
		if (out.fail()) {
			cerr << "Error with opening the file!" << endl;
		}
		cout << "\tAdding new interirour car part to the shop!" << "\n--------------------------------------------\n";
		cout << "Enter description: ";
		cin.ignore();
		getline(cin, description);
		cout << "Enter name: ";
		getline(cin, name);
		cout << "Enter unique ID: "; id = (int)validateNumber();
		cout << "Enter amount: "; amount = (int)validateNumber();
		cout << "Is the part new? (1 - Yes| 0 - No): "; isNew = validateBoolean();
		cout << "Enter price: "; price = validateNumber();
		cout << "Enter wage percent: "; wagePercent = validateNumber();
		cout << "Enter the material: "; cin >> material;
		cout << "Enter the color of the part: \n|0 - Red, 1 - Green, 2 - Blue, 3 - Yellow, 4- White, 5 - Black|: "; color = validateColor();

		//--------------FOR TESTING------------------
		//carParts.push_back(new InteriorCarPart(description, name, id, amount, isNew, price, wagePercent, material, (Color)color));
		//carParts[0]->display();
		if (out.is_open()) {
			out << description << " " << name << " " << id << " " << amount << " " << isNew << " " << price << " " << wagePercent << " " << material << " " << color << endl;
			cout << "Interior car part item added successfully" << endl;
		}else
			cout << "Error with adding the item!" << endl;

		out.close();
	}
	else if (choice == 3) {  
		out.open("Accessories.txt", ios_base::app);   //for the accessories
		if (out.fail()) {
			cerr << "Error with opening the file!" << endl;
			return;
		}
		cout << "\tAdding new accessory to the shop!" << "\n--------------------------------------------\n";
		cout << "Enter description: ";
		cin.ignore();
		getline(cin, description);
		cout << "Enter name: ";
		getline(cin, name);
		cout << "Enter unique ID: "; id = (int)validateNumber();
		cout << "Enter amount: "; amount = (int)validateNumber();
		cout << "Enter price: "; price = validateNumber();
		cout << "Enter the percent disount of the accessory: "; percenDiscount = validateNumber();

		if (out.is_open()) {
			out << description << " " << name << " " << id << " " << amount << " " << price << " " << percenDiscount << endl;
			cout << "Accessory item added successfully" << endl;
		}
		else
			cout << "Error with adding the item!" << endl;


		out.close();
	}

	Sleep(2500); //delay the return to the main menu so the user can see that they added the item succesfully
}

//function to view the items available in the shop which accepts the choice of user and one integer value to decide the functionality
void viewItems(int choice, int func) {
	system("CLS");  //clearing the console
	ifstream in;  //opening the in stream
	string line;
	if (choice == 1) {       
		cout << "\tAvailable Engines in the shop" << "\n--------------------------------------------\n";
		string description, name;
		int id, amount, horsePower;
		bool isNew;
		double price, hourlyRate, hours;

		in.open("Engines.txt");   //opening the Engines file
		if (in.fail()) {
			cerr << "Error with opening the file!" << endl;    //displaying a message if there is an error with the opening of the file
		}

		if (in.is_open()) {    
			while (getline(in, line)) {   //getting every line in the file
				
				istringstream is(line);        //separating the string by spaces and saving the information into the variables
				is >> description >> name >> id >> amount >> isNew >> price >> hourlyRate >> hours >> horsePower;   
				engines.push_back(new Engine(description, name, id, amount, isNew, price, hourlyRate, hours, horsePower));  //adding the object of type Engine in the vector
			}
		}
		else {
			cout << "Error with the file!" << endl;
		}

		mergeSort(engines);   //sorting the items in the engines vector

		if (func == 0) {    //if the custom functionality is  0
			for (int i = 0; i < engines.size(); i++) {   //just display every item in the vector
				engines[i]->display();
			}
		}
		else if (func == 1) {   //if it is 1
			cout << "Engines containing (" << pattern << ") in their names" << endl;    //use the String pattern matching algorithm to 
			for (int i = 0; i < engines.size(); i++) {
				matcher = search(engines[i]->GetName(), pattern);
				if (!matcher.empty()) {
					for (int j = 0; j < matcher.size(); j++)
						engines[i]->display();
				}
			}
		}

		in.close();

	}
	else if (choice == 2) {   //repeating the same proccess for the other two opitons
		cout << "\tAvailable Interior Car Parts in the shop" << "\n--------------------------------------------\n";   //for the Interior Car Parts
		string description, name, material;
		int id, amount, color;
		double price, wagePercent;
		bool isNew;

		in.open("InteriorCarPart.txt");
		if (in.fail()) {
			cerr << "Error with opening the file!" << endl;
		}
				
		if (in.is_open()) {
			while (getline(in, line)) {
				istringstream is(line);
				is >> description >> name >> id >> amount >> isNew >> price >> wagePercent >> material >> color;
				carParts.push_back(new InteriorCarPart(description, name, id, amount, isNew, price, wagePercent, material, (Color)color));
			}
		}
		else {
			cout << "Error with the file!" << endl;
		}

		mergeSort(carParts);

		if (func == 0) {
			for (int i = 0; i < carParts.size(); i++) {
				carParts[i]->display();
			}
		}
		else if (func == 1) {
			cout << "Car parts containing (" << pattern << ") in their names" << endl;
			for (int i = 0; i < carParts.size(); i++) {
				matcher = search(carParts[i]->GetName(), pattern);
				if (!matcher.empty()) {
					for (int j = 0; j < matcher.size(); j++)
						carParts[i]->display();
				}
				
			}
		}
		in.close();
	}
	else if (choice == 3) {       //for the Accessories
		cout << "\tAvailable Accessories in the shop" << "\n--------------------------------------------\n";
		string description, name;
		int id, amount;
		double price, percentDiscount;

		in.open("Accessories.txt");
		if (in.fail()) {
			cerr << "Error with opening the file!" << endl;
		}

		if (in.is_open()) {
			while (getline(in, line)) {
				istringstream is(line);
				is >> description >> name >> id >> amount >> price >> percentDiscount;
				accessories.push_back(new Accessories(description, name, id, amount, price, percentDiscount));

			}
		}
		else {
			cout << "Error with the file!" << endl;
		}

		mergeSort(accessories);

		if (func == 0) {
			for (int i = 0; i < accessories.size(); i++) {
				accessories[i]->display();
			}
		}
		else if (func == 1) {
			cout << "Accessories containing (" << pattern << ") in their names" << endl;
			for (int i = 0; i < accessories.size(); i++) {
				matcher = search(accessories[i]->GetName(), pattern);
				if (!matcher.empty()) {
					for (int j = 0; j < matcher.size(); j++) 
						accessories[i]->display();
				}
			}
			
		}
		in.close();
	}




	//----FOR GOING BACK---------
	int answer;
	while (1) {
		cout << "Do you want to exit - |1- Yes|: ";
		answer = validateNumber();
		if (answer == 1) {
			engines.clear();
			carParts.clear();
			accessories.clear();
			ids.clear();
			break;
		}
	}
}

//function to search for an item
void searchForItem(int choice) {
	system("CLS");
	//the function just saves the pattern in a string variables and invokes the viewItems() function with the needed functionality
	if (choice == 1) {
		cout << "\tSearching for Engines" << "\n--------------------------------------------\n";
		cout << "Enter the search keyword (name of the Engine): ";
		cin >> pattern;
		viewItems(1, 1);
	}
	else if (choice == 2) {
		cout << "\tSearching for Interior car parts" << "\n--------------------------------------------\n";
		cout << "Enter the search keyword (name of the Part): ";
		cin >> pattern;
		viewItems(2, 1);
	}
	else if (choice == 3) {
		cout << "\tSearching for Accessories" << "\n--------------------------------------------\n";
		cout << "Enter the search keyword (name of the Accessory): ";
		cin >> pattern;
		viewItems(3, 1);
	}

	
}

//main function which displays the main men
bool menuChoice() {
	int number;   //displaying the main menu
	cout << "\tPart Shop" << "\n----------------------------\n";
	cout << "1 - Insert new item " << endl << "2 - View available items" << endl << "3 - Search for an item" << endl << "\n9 - Exit\n----------------------------" << endl << "Enter the number corresponding to your choice: ";
	number = validateNumber();
	
	//always have an option to return to the main menu or exit the program which is bound to 9

	if (number == 1) {  //implement functionallity for different options
		int choice;
		while (true) {
			system("CLS");
			cout << "\tInserting new item" << "\n----------------------------\n";
			cout << "1 - Engine" << "\n2 - Interiour car part" << "\n3 - Accessory"<< "\n\n9 - Go back\n----------------------------\n" << "Enter the number corresponding to your choice: ";
			choice = validateNumber();
			
			
			if (choice >= 1 && choice <= 3) {
				insertNewItem(choice);
				return true;
			}
			else if (choice == 9)  
				break;
			else
				continue;
		}
	}
	else if (number == 2) {
		int choice;
		

		while (true) {
			system("CLS");
			cout << "\tViewing items" << "\n----------------------------\n";
			cout << "Which items would like to view?" << endl;
			cout << "1 - Engines" << "\n2 - Interiour car parts" << "\n3 - Accessories" << "\n\n9 - Go back\n----------------------------\n" << "Enter the number corresponding to your choice: ";
			choice = validateNumber();

			if (choice >= 1 && choice <= 3) {
				viewItems(choice, 0);
				return true;
			}
			else if (choice == 9)
				break;
			else
				continue;
		}
	}
	else if (number == 3) {
		int choic;
		while (true) {
			system("CLS");
			cout << "\tSearching for an item" << "\n---------------------------------\n";
			cout << "Would like to search for a\an: " << endl;
			cout << "1 - Engine" << "\n2 - Interior car part" << "\n3 - Accessory" << "\n\n9 - Go back\n---------------------------------\n" << "Enter the number corresponding to your choice : ";
			choic = validateNumber();
			if (choic >= 1 && choic <= 3) {
				searchForItem(choic);
				return true;
			}
			else if (choic == 9)
				break;
			else
				continue;
		}
	}
	else if (number == 9)
		return false;
	else
		return true;

}


int main() {
	
	while (menuChoice()) {   //looping the main menu
		system("CLS");  //clearing the console on every itereation
	}
	
	return 0;
}