// Ricky Shek
// Assignment 2
// Cafe Shek

// clear and appropriate problem statement
/* A cafe owner wishes to calculate the total bill of each customer.
Each customer can order one or more items off the menu.
If they are a member they will receive a discount.*/

// max clear description of appropriate solution in words

/* Assumptions:

*/

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Cafe
{
private:
	double item_price;
	int discount;
public:
	void getItemPrice(char item, double& price);
	void getCal_Discount(double subBill, double& finalBill);
	void Print_logo();
	void Print_menu();
};

void Cafe :: getItemPrice(char item, double& price)
{
if (item == '1')
{
	price = 2.50;
	cout << "You have chosen soup!" << endl;
}
else if (item == '2')
{
	price = 3.50;
	cout << "You have chosen sandwich!" << endl;
}
else if (item == '3')
{
	price = 3.20;
	cout << "You have chosen cake!" << endl;
}
else if (item == '4')
{
	price = 1.50;
	cout << "You have chosen tea!" << endl;
}
else if (item == '5')
{
	price = 1.80;
	cout << "You have chosen coffee!" << endl;
}
else if (item == '6')
{
	price = 1.40;
	cout << "You have chosen soft drink!" << endl;
}
}

void Cafe :: getCal_Discount(double subBill, double& finalBill)
{
	const double discount = 0.1;

	finalBill = subBill - (subBill * discount);
}

void getCal_Disc_NM(double subBill, double& fakeBill)
{
	const double discount = 0.1;

	fakeBill = subBill - (subBill * discount);
}

void inputCheck(char&);

int main()
{
	Cafe customer1;
	char menu_item;
	double menu_price = 0, sub_bill = 0, final_bill = 0, discount_value = 0, fake_bill = 0;
	char repeat, cafe_member;
	int member_code;
	string logo;
	ofstream receipt;

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	customer1.Print_logo();
	cout << "Welcome to Cafe Shek! Thank you for visiting." << endl;
	cout << "Here are a choice of items we have for today." << endl;
	customer1.Print_menu();
	cout << " " << endl;

	do {
		cout << "Please pick one by typing in the appropriate number and click enter." << endl;
		cout << " " << endl;

		// NEED THIS NEXT BIT ALL IN A LOOP SO THAT THEY CAN HAVE THE OPTION TO PICK ANOTHER ITEM

		// Customer chooses an item from the menu
		cin >> menu_item;

		// DATA IS SENT TO THE INPUT CHECKER TO MAKE SURE THEY HAVE INPUTTED AN INTEGER NUMBER FROM 1-6
		inputCheck(menu_item);

		cout << "You chose Item " << menu_item << ". Excellent choice!" << endl;
		cout << " " << endl;

		// Data inputted from customer is then sent to the getItemPrice function to get the price of the item
		cout << "*****************************************************" << endl;
		cout << "* Acquiring menu item price function getItemPrice() *" << endl;
		cout << "*****************************************************" << endl;
		cout << " " << endl;
		customer1.getItemPrice(menu_item, menu_price);
		cout << "Thank you. The price of this item is: \x9c " << menu_price << endl;

		sub_bill += menu_price;

		cout << "Your current total is: " << sub_bill << endl;

		cout << "Do you wish to choose another item? Press 'y' for yes or 'n' for no. \n";
		cin >> repeat;
	} while ((repeat == 'y') || (repeat == 'Y'));


	// Total bill then calculated
	cout << "Your total bill comes to: " << sub_bill << endl;
	cout << " " << endl;

	// Function should return the correct price depending on the menu choice by the customer
	// Program asks the customer if they want to choose another item

	// Program asks the customer if they are a member or not.
	// If they are then the calculation function is called upon

	cout << "Members of our loyalty scheme receive a discount of 10% off their final bill." << endl;
	cout << "Are you a member? Please enter 'y' for Yes and 'n' for no" << endl;
	cin >> cafe_member;

	switch (cafe_member)
	{
	case 'y':
		cout << "Please enter the membership code: " << endl;
		cin >> member_code;

		if (member_code == 101)
		{
			cout << "Thank you for the correct membership code!" << endl;
			customer1.getCal_Discount(sub_bill, final_bill);
			cout << "Your bill would have cost you: \x9c" << sub_bill << " " << endl;
			discount_value = sub_bill - final_bill;
			cout << "Your total saving is: \x9c" << discount_value << endl;
			cout << " " << endl;
			final_bill = sub_bill - discount_value;
			cout << "Your final bill comes to: \x9c" << final_bill << " \n" << endl;
		}
		else if (member_code != 101)
		{
			cout << "Sorry this code is incorrect." << endl;
		}
		break;
	default:
		final_bill = sub_bill;
		getCal_Disc_NM(sub_bill, fake_bill);
		discount_value = sub_bill - fake_bill;
		cout << "Your final bill comes to: \x9c" << final_bill << " \n" << endl;
		cout << "If you were a member, you would have saved: \x9c" << discount_value << ". \n and your final bill would have been: \x9c" << fake_bill << "\n";
		break;
	}

	cout << "Thank you for visiting Cafe Shek!\n";
	cout << " \n";
	customer1.Print_logo();

	// Final bill put in an output file in the form of a receipt
	receipt.open("receipt.txt");

	// receipt << customer1.Print_logo();    HOW TO OUTPUT A FUNCTION WITH THE LOGO

	ifstream logoImg("printlogoreceipt.txt");
	stringstream logoStream;
	logoStream << logoImg.rdbuf();
	logo = logoStream.str();
	logoImg.close();

	receipt << logo;
	receipt << "CAFE SHEK - RECEIPT\n";
	receipt << "Your final bill comes to: £" << final_bill << "\n";
	receipt.close();

	return 0;
}

void Cafe :: Print_logo()
{
	cout << "     ***************************************************" << endl;
	cout << "     *       ____        __                            *" << endl;
	cout << "     *      / ___|      / _|                /|         *" << endl;
	cout << "     *     | |     __ _| |_ ___       |||| { |  __     *" << endl;
	cout << "     *     | |    / _` |  _/ _ \\      |||| { | |  |    *" << endl;
	cout << "     *     | |___| (_| | ||  __/      \\  /  {| |__|    *" << endl;
	cout << "     *      \\_____\\__,_|_| \\___|       ||   ||  ||     *" << endl;
	cout << "     *     / ____| |        | |        ||   ||  ||     *" << endl;
	cout << "     *    | (___ | |___  ___| | __     ||   ||  ||     *" << endl;
	cout << "     *     \\___ \\| '_  |/ _ | |/ /     ||   ||  ||     *" << endl;
	cout << "     *     ____) | | | |  __|   <      ||   ||  ||     *" << endl;
	cout << "     *    |_____/|_| |_|\\___|_|\\_\\     ||   ||  ||     *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     ***************************************************" << endl;
	cout << " " << endl;
}

void Cafe :: Print_menu()
{
	cout << "     ***************************************************" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     *   Item 1  Soup = \x9c 2.50             Type in 1   *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     *   Item 2  Sandwich = \x9c 3.50         Type in 2   *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     *   Item 3  Cake = \x9c 3.20             Type in 3   *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     *   Item 4  Tea = \x9c 1.50              Type in 4   *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     *   Item 5  Coffee = \x9c 1.80           Type in 5   *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     *   Item 6  Soft Drink = \x9c 1.40       Type in 6   *" << endl;
	cout << "     *                                                 *" << endl;
	cout << "     ***************************************************" << endl;
}

void inputCheck(char& input)
{
	while ((input < '1') || (input > '6'))
	{
		cout << "Sorry there is no item associated with your choice!" << endl;
		cout << "Please type in the number associated with your choice." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}
}