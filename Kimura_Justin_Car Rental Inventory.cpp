/*
Justin Kimura CIS 5
Final Project: Car Rental Inventory
*/

/*Program Name : Rental Car Inventory

The program processes an input file named "carInventory.txt" Download carInventory.txtand loads each car's info into a struct.
The structures must be stored dynamically, as the Reservation Agent can add, rent, return, and remove cars without limit until no cars remain.
Validate menu selections and Reservation Agent input for appropriate boundaries.
The program writes an output file named currentCarInventory.txt that stores updated inventory info.
The program will not allow multiple quantities of any car(i.e., only one specific car[id, year, make, model] is allowed).*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> //this is used to clear the console.


using namespace std;

struct Car
{
	int id;
	int year;
	string make;
	string model;
	int cost;
	bool isAvailable;
	bool isRemoved;
};

//Program function prototypes
void greetReservationAgent();
void displayOptions(vector<Car*>&);
void viewInventory(vector<Car*>&, bool, bool);
void addCar(vector<Car*>&);
void rentCar(vector<Car*>&);
void returnCar(vector<Car*>&);
void removeCar(vector<Car*>&);

int main()
{
	vector<Car*>inventory;

	string strId;
	string strYear;
	string strCost;
	fstream inputFile;
	fstream outputFile;

	inputFile.open("carInventory.txt", ios::in);
	int index = 0;
	while (true)
	{
		if (getline(inputFile, strId, ','))
		{
			Car* newCar = new Car;
			inventory.push_back(newCar);
			inventory[index]->id = stoi(strId);
			getline(inputFile, strYear, ',');
			inventory[index]->year = stoi(strYear);
			getline(inputFile, newCar->make, ',');
			getline(inputFile, newCar->model, ',');
			getline(inputFile, strCost);
			inventory[index]->cost = stoi(strCost);
			inventory[index]->isAvailable = true;
			inventory[index]->isRemoved = false;
			index++;
		}
		else
		{
			break;
		}
		
	}
	inputFile.close();
	greetReservationAgent();

	displayOptions(inventory);

	outputFile.open("currentCarinventory.txt", ios::out);
	for (Car* car : inventory)
	{
		if (!car->isRemoved)
		{
			outputFile << car->id << "," << car->year << "," << car->make << "," << car->model << "," << car->cost << endl;
		}
	}
	outputFile.close();

	for (int index = 0; index < inventory.size(); index++)
	{
		delete inventory[index];
		inventory[index] = nullptr;
	}
	return 0;
}

void greetReservationAgent()
{
	cout << "Welcome Reservation Agent" << endl;
}

void displayOptions(vector<Car*>& inventory)
{
	string choice; //prevents character input from crashing program;
	while (true)
	{
		cout << "1. View inventory" << endl;
		cout << "2. Add car to inventory" << endl;
		cout << "3. Rent car to inventory" << endl;
		cout << "4. Return car to inventory" << endl;
		cout << "5. Remove car from inventory" << endl;
		cout << "6. Quit" << endl;
		cout << "Choose one of these options: ";
		cin >> choice;

		if (choice == "1")
		{
			system("cls");
			viewInventory(inventory, false, false);
			cout << "press enter to contiue." << endl;
			cin.ignore(1);
			cin.ignore(50, '\n');
			system("cls");
		}
		else if (choice == "2")
		{
			system("cls");
			addCar(inventory);
			system("cls");
		}
		else if (choice == "3")
		{
			system("cls");
			rentCar(inventory);
			system("cls");
		}
		else if (choice == "4")
		{
			system("cls");
			returnCar(inventory);
			system("cls");
		}
		else if (choice == "5")
		{
			system("cls");
			removeCar(inventory);
			system("cls");
		}
		else if (choice == "6")
		{
			break;
		}
		else
		{
			cout << "Must be one of the options listed." << endl;
		}
	}
}
//bools limmit output based on availability
void viewInventory(vector<Car*>&inventory, bool checkAvailability, bool invertAvailability)
{
	cout << "Car ID - Year, Make, Model - Cost" << endl;
	for (Car* car : inventory)
	{
		if (!car->isRemoved)
		{
			if (checkAvailability && !invertAvailability && car->isAvailable)
			{
				cout << car->id << " - " << car->year << " - " << car->make << ", " << car->model << " - " << car->cost << endl;
			}
			else if (checkAvailability && invertAvailability && !car->isAvailable)
			{
				cout << car->id << " - " << car->year << " - " << car->make << ", " << car->model << " - " << car->cost << endl;
			}
			else if (!checkAvailability)
			{
				string availability;
				if (car->isAvailable)
					availability = "available for rent";
				else
					availability = "Currently being rented";
				cout << car->id << " - " << car->year << " - " << car->make << ", " << car->model << " - " << car->cost << " :" << availability << endl;
			}
		}
	}
}

void addCar(vector<Car*>&inventory)
{
	int year;
	string make;
	string model;
	int cost;
	string infoChoice;

	while (true)
	{
		cout << "Enter new car info: Year, Make, and Model." << endl;
		cout << "(To go back enter -1)" << endl;
		cout << "Enter the year of the car: ";
		while (!(cin >> year)) //prevents character input from crashing program;
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "Please input a valid year: ";
		}
		if (year == -1)
			return;
		cout << "Enter the make of the car: ";
		cin >> make;
		cout << "Enter the model of the car: ";
		cin >> model;
		cout << "Enter the cost to rent the car: ";
		while (!(cin >> cost))
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "Please input a valid cost: ";
		}

		cout << "Does the information you inputted look correct? Yes or No: ";
		while (true)
		{
			cin >> infoChoice;
			if (infoChoice == "Yes" || infoChoice == "yes")
			{
				Car* car = new Car;
				car->year = year;
				car->make = make;
				car->model = model;
				car->cost = cost;
				car->isAvailable = true;
				car->isRemoved = false;
				bool invalid;
				for (int index = 0; index < inventory.size(); index++)
				{
					invalid = true;
					if (inventory[index]->year != car->year)
						invalid = false;
					if (inventory[index]->make != car->make)
						invalid = false;
					if (inventory[index]->model != car->model)
						invalid = false;

					if (invalid)
					{
						delete car;
						cout << "This is car is already in the system and cannot be added." << endl;
						cout << "Please press enter to continue back to the menu." << endl;
						cin.ignore(2);
						return;
					}
				}
				car->id = inventory[inventory.size() - 1]->id + 1;
				inventory.push_back(car);
				cout << "Please press enter: ";
				return;
			}
			else if (infoChoice == "No" || infoChoice == "no")
			{
				break;
			}
		}
	}

}

void rentCar(vector<Car*>& inventory)
{
	viewInventory(inventory, true, false);
	while(true)
	{
		int id;
		int days;
		int total;
		string infoChoice;

		cout << "Please enter the car ID to rent(Enter -1 to go back): ";
		while (!(cin >> id))
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "Please put in a valid ID: ";
		}
		if (id == -1)
		{
			return;
		}
		int targetIndex = 0;
		bool found = false;
		for (Car* car : inventory)
		{
			if (!car->isRemoved && car->id == id)
			{
				found = true;
				break;
			}
			targetIndex++;
		}
		if (!found)
		{
			cout << "This car id does not exist." << endl;
			cout << "Press enter to return." << endl;
			cin.ignore(2);
			return;
		}
		if (!inventory[targetIndex]->isAvailable)
		{
			cout << "This car id is not available!" << endl;
			cout << "Press enter to return." << endl;
			cin.ignore(2);
			return;
		}

		cout << inventory[targetIndex]->year << ", " << inventory[targetIndex]->make << ", " << 
		inventory[targetIndex]->model << " - " << inventory[targetIndex]->cost << endl;
		cout << "Does the information look correct? Yes or No: " << endl;
		while (true)
		{
			cin >> infoChoice;
			if (infoChoice == "yes" || infoChoice == "Yes")
			{
				cout << "How many days do you want to rent this car? ";
				while (!(cin >> days))
				{
					cin.clear();
					cin.ignore(50, '\n');
					cout << "Please put in a valid number: ";
				}
				total = days * inventory[targetIndex]->cost;
				cout << "Your total to rent the car for " << days << " days is " << total << "." << endl;
				inventory[targetIndex]->isAvailable = false;
				cout << "Press enter to return. ";
				cin.ignore(2);
				return;
			}
			else if (infoChoice == "no" || infoChoice == "No")
			{
				break;
			}
			else
			{
				cout << "please enter a valid response (Yes/No): ";
			}
		}
	}
}

void returnCar(vector<Car*>& inventory)
{
	viewInventory(inventory, true, true);
	while (true)
	{
		int id;
		string infoChoice;

		cout << "Please enter the car ID to return(Enter -1 to go back): ";
		while (!(cin >> id))
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "Please put in a valid ID: ";
		}
		if (id == -1)
		{
			return;
		}

		int targetIndex = 0;
		bool found = false;
		for (Car* car : inventory)
		{
			if (!car->isRemoved && car->id == id)
			{
				found = true;
				break;
			}
			targetIndex++;
		}
		if (!found)
		{
			cout << "This car id does not exist." << endl;
			cout << "Press enter to return." << endl;
			cin.ignore(2);
			return;
		}
		if (inventory[targetIndex]->isAvailable)
		{
			cout << "This car is still in the system!" << endl;
			cout << "Press enter to return." << endl;
			cin.ignore(2);
			return;
		}

		cout << inventory[targetIndex]->year << ", " << inventory[targetIndex]->make << ", " <<
			inventory[targetIndex]->model << " - " << inventory[targetIndex]->cost << endl;
		cout << "Does the information look correct? Yes or No: " << endl;
		while (true)
		{
			cin >> infoChoice;
			if (infoChoice == "yes" || infoChoice == "Yes")
			{
				cout << "This car has been returned." << endl;
				inventory[targetIndex]->isAvailable = true;
				cout << "Press enter to return. ";
				cin.ignore(2);
				return;
			}
			else if (infoChoice == "no" || infoChoice == "No")
			{
				break;
			}
			else
			{
				cout << "please enter a valid response(Yes or No): ";
			}
		}
	}
}

void removeCar(vector<Car*>&inventory)
{
	viewInventory(inventory, false, false);
	while (true)
	{
		int id;
		string infoChoice;

		cout << "Please enter the car ID to remove(Enter -1 to go back): ";
		if(!(cin >> id))
		{
			cin.clear();
			cin.ignore(50, '\n');
			cout << "Please put in a valid ID: ";
		}
		if (id == -1)
		{
			return;
		}

		int targetIndex = 0;
		bool found = false;
		for (Car* car : inventory)
		{
			if (!car->isRemoved && car->id == id)
			{
				found = true;
				break;
			}
			targetIndex++;
		}
		if (!found)
		{
			cout << "This car id does not exist." << endl;
			cout << "Press enter to return." << endl;
			cin.ignore(2);
			return;
		}

		cout << inventory[targetIndex]->year << ", " << inventory[targetIndex]->make << ", " <<
			inventory[targetIndex]->model << " - " << inventory[targetIndex]->cost << endl;
		cout << "Does the information look correct? Yes or No: " << endl;
		while (true)
		{
			cin >> infoChoice;
			if (infoChoice == "yes" || infoChoice == "Yes")
			{
				cout << "This car has been removed." << endl;
				inventory[targetIndex]->isRemoved = true;
				cout << "Press enter to return. ";
				cin.ignore(2);
				return;
			}
			else if (infoChoice == "no" || infoChoice == "No")
			{
				break;
			}
			else
			{
				cout << "please enter a valid response (Yes/No): ";
			}
		}
	}
}
