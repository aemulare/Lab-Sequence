/***************************************************************************************************
									CSC 326 Information Structures
												Lab #1B
												Sequence
										Student: Maria Romanova

***************************************************************************************************/

#include <iostream>
#include <cmath>
#include "Sequence.h"
#include "ErrorMessages.h"
#include "Shell.h"
using namespace std;

/* ----------------------------------------------------------------------------------------------
NOTE: This program could work with different data types: double, float, int, char, string
To change data type make changes in two following lines of code

double:		#define _DOUBLE_

float:		#define _FLOAT_

int:		   #define _INT_

char:		   #define _CHAR_

string:		#define _CHAR_SET_
-----------------------------------------------------------------------------------------------*/

#define _CHAR_SET_
#define CAPACITY 10


int main()
{
#if defined _DOUBLE_
	double entry;						// item for enter by user
	Sequence<double> s1(CAPACITY);		// to create sequence
	Shell<double> shell;				// to format output
	const double INVALID_VALUE = NAN;
	const string ITEM_TYPE = "REAL NUMBERS";

#elif defined _FLOAT_
	float entry;						// item for enter by user
	Sequence<float> s1(CAPACITY);		// to create sequence
	Shell<float> shell;					// to format output
	const float INVALID_VALUE = NAN;
	const string ITEM_TYPE = "REAL NUMBERS";

#elif defined _INT_
	int entry;							// item for enter by user
	Sequence<int> s1(CAPACITY);			// to create sequence
	Shell<int> shell;					// to format output
	const int INVALID_VALUE = INT_MIN;
	const string ITEM_TYPE = "INTEGER NUMBERS";

#elif defined _CHAR_SET_
	string entry;						// item for enter by user
	Sequence<string> s1(CAPACITY);		// to create sequence
	Shell<string> shell;				// to format output
	const string INVALID_VALUE = "\0";
	const string ITEM_TYPE = "CHARACTER SETS (eng keyboard)";

#elif defined _CHAR_
	char entry;							// item for enter by user
	Sequence<char> s1(CAPACITY);		// to create sequence
	Shell<char> shell;					// to format output
	const char INVALID_VALUE = '\0';
	const string ITEM_TYPE = "SINGLE CHARACTERS";

#endif

	shell.displayHeader(ITEM_TYPE);	// comment for user about program

	// Choice to fill in the sequence with multiple items -----------------------------------------------
	char ans;
	cout << "   Would you like to create your sequence by entering multiple items? (y/n): ";
		cin >> ans;

	if (ans == 'y' || ans == 'Y')
	{
		shell.fill_range(s1);
	}
	else
		cout << "\n   Please start entering items one by one with #4 INSERT or #5 ATTACH commands.\n\n";
	// End Choice to fill in the sequence with multiple items--------------------------------------------

	
	shell.menu();								// display menu
	shell.display(s1);

	int userChoice = -1;

	while (userChoice != 11)
	{	
		userChoice = -1;						// assign invalid value in order to avoid input errors
		entry = INVALID_VALUE;

		cin.clear();							// clear cin buffer in order to avoid input errors
		cin.ignore(INT_MAX, '\n');

		shell.changeTextColor(8);				// dark_grey text color
		cout << "\n\t command #";
			cin >> userChoice;
		shell.changeTextColor();				// light_gray text color (console default)
		

		// Work with menu commands
		switch (userChoice)
		{
		case 0:									// 0 - FIRST
			s1.first();
			shell.display(s1);
			break;

		case 1:									// 1 - LAST
			s1.last();
			shell.display(s1);
			break;

		case 2:									// 2 - NEXT = current_index + 1
			if (s1.getCurrentIndex() < s1.size() - 1)
				s1.next();
			else if (s1.size() > 0)
				shell.errorMessage(NO_NEXT);
			shell.display(s1);
			break;

		case 3:									// 3 - PREVIOUS = current_index - 1
			if (s1.getCurrentIndex() > 0)
				s1.previous();
			else if (s1.size() > 0)
				shell.errorMessage(NO_PREV);
			shell.display(s1);
			break;

		case 4:									// 4 - INSERT BEFORE CURRENT ITEM
			cout << "\t enter value: ";
			cin >> entry;
			if (entry != INVALID_VALUE)
			{
				s1.insert(entry);
				shell.display(s1);
			}
			else
				shell.errorMessage(INVALID_ENTRY);
			break;

		case 5:									// 5 - ATTACH/INSERT AFTER CURRENT ITEM
			cout << "\t enter value: ";
			cin >> entry;
			if (entry != INVALID_VALUE)
			{
				s1.attach(entry);
				shell.display(s1);
			}
			else
				shell.errorMessage(INVALID_ENTRY);
			break;
		
		case 6:									// 6 - REMOVE CURRENT ITEM
			if (s1.current() != INVALID_VALUE)
			{
				cout << "\n\t The item '" << s1.current() << "' has been removed.\n";
				s1.remove_current();
				shell.display(s1);
			}
			else
				shell.errorMessage(NOTHING_TO_REMOVE);
			break;

		case 7:									// 7 - SIZE
			cout << "\n\t number of items = " << s1.size() << endl;
			break;

		case 8:									// 8- DISPLAY CURRENT ITEM
			if (s1.current() != INVALID_VALUE)
			{
				cout << "\n\t current index = " << s1.getCurrentIndex()
					<< ", current item '" << s1.current() << "'\n";
			}
			else
				shell.errorMessage(NO_CURRENT);
			break;

		case 9:									// 9 - DISPLAY SEQUENCE
			shell.display(s1);
			break;

		case 10:								// 10 - DISPLAY MENU
			shell.menu();
			break;

		case 11:								// 11 - EXIT
			break;

		default:								
			shell.errorMessage(WRONG_COMMAND);
			break;
		}// End switch
	}// End while

	
	// pause screen
	cout << "\n\n\t";
	system("pause");
	return 0;

} // End main()
