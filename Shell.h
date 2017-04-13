#pragma once
#include "Sequence.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;


template<class T> class Shell
{
public:

		/*Postcondition: The header with information for user about program is displayed.
		  The white text framed by two lines of green asterisks.*/
	void displayHeader(string itemType)
	{
		changeTextColor(02);	// green text color
		cout << endl << setfill('*') << setw(105) << "*" << "\n\n";

		changeTextColor(15);	// white text color
		cout << "\t\t This program implements work with sequence of " << itemType
			<< "\n\n\t\t The sequence could be modified by commands from the control menu.\n\n";

		changeTextColor(02);	// green text color
		cout << setfill('*') << setw(105) << "*" << "\n\n\n";
		changeTextColor();	// light_gray text color (console default)
	}


		/*Postcondition: The different from console default color is applied to one element of output.
		  In displayed sequence the current item has color defined as parameter for this function*/
	void highlight(T msg, int color = 07)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);				// specified text color 
		cout << msg;
		SetConsoleTextAttribute(hConsole, 07);					// light_gray text color (console default)
	}


		/*Postcondition: All the output after this function call has color defined as its parameter.*/
	void changeTextColor(int color = 07)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);				// specified text color
	}


		/*Precondition: If sequence is not empty, s.size() != 0
		  Postcondition: The sequence is displayed in format { item_0,  item_1,  item_2, ..., item_n }.
		  If the sequence has full capacity, the warning message "The set is full." is displayed after the sequence.
		  If the sequence is empty, only the error message "The set is empty." is displayed.*/
	void display(Sequence<T>& s)
	{
		if (s.size() != 0)										// if the sequence is not empty
		{
			cout << "\n\t { ";
			for (int i = 0; i < s.size(); i++)				// step through the sequence
			{
				if (i == s.getCurrentIndex())
					highlight(s.getDataItem(i), 10);				// highlight the current item with light_green text color
				else
					cout << s.getDataItem(i);						// non current items are displayed in default text color
				if (i < s.size() - 1)						// don't print comma after the last item
					cout << ",  ";
			}
			cout << " }\n";
		}
		else
			errorMessage(EMPTY_SET);
	}


		/*Postcondition: The control menu in dark grey color, with numbered commands from 0 to 11, is displayed.
		  The menu is framed with two lines of dashes (dark grey color too).
		  The color of the following output is changed to default.*/
	void menu()
	{
		string menuOptions[12][2] = { { "FIRST", "set the first item as current" },
									{ "LAST", "set the last item as current" },
									{ "NEXT", "move to the next item" },
									{ "PREV", "move to the previous item" },
									{ "INSERT", "insert BEFORE the current item" },
									{ "ATTACH", "insert AFTER the current item" },
									{ "REMOVE", "remove the current item" },
									{ "SIZE", "number of items in the sequence" },
									{ "CURRENT", "display current item" },
									{ "DISPLAY", "display the sequence" },
									{ "MENU", "display menu" },
									{ "EXIT", "finish working with sequence" } };

		changeTextColor(8); // dark_grey text color
		cout << endl << setfill('-') << setw(105) << "-" << "\n" << setfill(' ') << left;

		// display menu commands from 0 to 11 -----------------------------------------------------------------------------
		for (int i = 0; i < 6; i++)
			cout << "   " << setw(4) << i << setw(9) << menuOptions[i][0] << setw(38) << menuOptions[i][1]
			<< "   " << setw(4) << i + 6 << setw(9) << menuOptions[i + 6][0] << setw(38) << menuOptions[i + 6][1] << endl;

		cout << setfill('-') << setw(105) << "-" << "\n" << setfill(' ');
		changeTextColor(); // light_gray text color (console default)
	}



		/*Postcondition: The appropriate error/warning message in red color is displayed.
		  The color of the following output is changed to default.*/
	void errorMessage(const string& msg)
	{
		changeTextColor(04);	// light_red text color
		cout << msg;
		changeTextColor();		// light_gray text color (console default)
	}


		/*Precondition: If user entered a valid number (not letter/other character, in range from 0 to 
		  CAPACITY) in request for number of multiple items to be added.
		  Postcondition: The range of n new items is added to sequence.
		  If the number of items n is invalid, display error message "Invalid value! Please try again."
		  and repeat prompt to enter n until the valid number is entered.*/
	void fill_range(Sequence<T>& s)
	{
		T item;
		int n = -1;

		while (n <= 0)	// if n is a number
		{
			cin.clear();							// clear cin buffer in order to avoid input errors
			cin.ignore(INT_MAX, '\n');

			cout << "\n\t\t\t how many items? n = ";
			cin >> n;

			if (n != -1 && n > 0)
			{
				cout << "\t\t\t enter the items (blank separated): ";
				for (int i = 0; i < n; i++)
				{
					cin >> item;
					s.attach(item);
				}
			}
			else
				errorMessage(INVALID_ENTRY);
		}// end while
	}
};
