#include "pch.h"
#include <iostream>


using namespace std;

unsigned int ReadPinC()
{
	int pinc = 0;
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io PINC" };

	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			//do nothing, or print out debug data
			//cout << "Debug line: " << line; // print out OUSB data
		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	pinc = (unsigned int)atoi(line);
	// Mask pinc value for bottom 8-bit only.
	pinc = pinc & 0x00FF;
	return pinc;
}

unsigned int WritePortB(unsigned int val)
{
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io PORTB " }; // Need to have a extra space after PORTB
	char val_string[4] = {};

	//Convert integer (in base 10) to character
	_itoa_s(val, val_string, 10);
	// append the value to the Command string
	strcat_s(command, val_string);

	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			// do nothing, or print out debug data
			//cout << "Debug line: " << line; // print out OUSB data
		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	unsigned int portb = (unsigned int)atoi(line);
	return portb;
}

int ReadPortB()
{
	int portb_val = 0;
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io PORTB" };

	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			//do nothing, or print out debug data
			//cout << "Debug line: " << line; // print out OUSB data
		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	portb_val = (unsigned int)atoi(line);
	// Mask pinc value for bottom 8-bit only.

	return portb_val;
}

int CombinedFunction(char r_w[], char portname[], unsigned int val)
{

	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io " }; // Need to have a extra space after PORTB
	char val_string[4] = {};
	strcat_s(command, portname);

	if (strcmp(r_w, "w") == 0)
	{
		strcat_s(command, " ");
		//Convert integer (in base 10) to character
		_itoa_s(val, val_string, 10);
			// append the value to the Command string
			strcat_s(command, val_string);
	}
	

	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				return false;
			}
		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	unsigned int portvalue = (unsigned int)atoi(line);
	return portvalue;
}

bool connectOUSB()
{
	bool logic = false;
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io PORTB" };
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				return false;
			}
		}
		_pclose(fpipe);
	}
	return true;
	// pipe code that sends out the current Command stored in the command variable
	
}

bool checkRange(int value)
{
	if (value > 255 || value < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int main(int argc, char *argv[])
{
	//TASK 1

	//Task 2
	cout << "task 2, connect to OUSB" << endl;
	bool logic = connectOUSB();
	if (logic == true)
	{
		cout << "no problem with ousb" << endl;
	}
	else
	{
		cout << "check ousb connection" << endl;
		return 0;
	}


	//Task 3
	cout << "Task 3, reading from PORTB" << endl;
	int portb_val = ReadPortB();
	cout << "PortB value is = " << portb_val << endl;

	//Task 4
	cout << "Task 4, reading from other ports such as PINC" << endl;
	int pinc_val = ReadPinC();
	cout << "Pinc value is = " << pinc_val << endl;

	//Task 5
	cout << "Task 5, send a new value to portb, read the portb and print the value on the screen" << endl;
	WritePortB(4);
	portb_val = ReadPortB();
	bool range = checkRange(portb_val);
	if (range = true)
	{
		cout << "New PortB value is = " << portb_val << endl;
	}
	

	//Task 6
	cout << "Task 6 combined everything into one function" << endl;
	cout << "Do you want to read or write data to/from ousb? (r for read and w for write)" << endl;
	char r_w[] = { "        " };
	cin >> r_w;
	if (strcmp(r_w, "r") == 0)
	{
		cout << "Which port do you want to read from?" << endl;
		char portname[] = { "      " };
		cin >> portname;
		int value = 0;
		value = CombinedFunction(r_w, portname, value);
		cout << "Value of " << portname << " is " << value << endl;
		return 0;
	}
	else if (strcmp(r_w, "w") == 0)
	{
		cout << "Which port do you want to write to?" << endl;
		char portname[] = { "     " };
		cin >> portname;
		cout << "What value do you want to write?" << endl;
		int value = 0;
		cin >> value;
		if (checkRange(value))
		{
		CombinedFunction(r_w, portname, value);
		cout << "Done" << endl;
		}
		else
		{
			cout << "out of range" << endl;
			return 0;
		}

		return 0;
	}
	else
	{
		cout << "Do you even read the instruction?" << endl;
	}
	
	return 0;
}




