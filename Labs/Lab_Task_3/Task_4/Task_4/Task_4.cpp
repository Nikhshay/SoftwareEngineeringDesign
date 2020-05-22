// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "pch.h"  // For VS17 (must be first). For older version of VS use: "stdafx.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <cstdlib>
#include <string.h>


using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

void WritePortB(unsigned int val)
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
	//unsigned int portb = (unsigned int)atoi(line);
	//return portb;
}


void WritePWM()
{
	char line[255] = {};
	FILE *fpipe;
	char command[255] = { "ousb pwm-freq 1 46" };

	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{

		}
		_pclose(fpipe);
	}
}


void SetDutyCycle(unsigned int val)
{
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb pwm 1 " }; // Need to have a extra space after PORTB
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
	//unsigned int portb = (unsigned int)atoi(line);
	//return portb;
}

int ReadPortA(unsigned int val)
{

	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r adc " }; // Need to have a extra space after PORTB
	char val_string[4] = {};
	_itoa_s(val, val_string, 10);
	strcat_s(command, val_string);
	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{

		}
		_pclose(fpipe);
	}
	// convert value from char array to int	
	int portvalue = (int)atoi(line);
	return portvalue;
}

bool CheckRange(int val, char which)
{
	if (val >= 0 && val <= 100 && which == 'P')
	{
		return true;
	}
	else if (val >= 0 && val <= 7 && which == 'A')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool validarg(string line)
{
	for (int i = 0; i < line.length(); i++)
	{
		if (isdigit(line[i]))
		{

		}
		else
		{
			return false;
		}
	}
	return true;
}



int main(int argc, char* argv[])
{
	cout << "Task 4" << endl;
	
	if (argc != 3)
	{
		cout << "Brah, too many/little arguments" << endl;
		return 0;
	}
	else
	{
		if (argv[1][0] == 'P' && argv[1][1] == '\0')
		{
			WritePWM();
			if (validarg(argv[2]))
			{
				int num = stoi(argv[2]);
				if (CheckRange(num, 'P'))
				{
					SetDutyCycle(num);
					cout << "Done bra, I wrote " << num << " to the duty cycle as per your command ;)" << endl;
					return 0;
				}
				else
				{
					cout << "Brah, out of range" << endl;
					return 0;
				}
			}
			else
			{
				cout << "Brah, incorrect Argument 2" << endl;
				return 0;
			}
		}
		else if (argv[1][0] == 'A' && argv[1][1] == '\0')
		{
			if (validarg(argv[2]))
			{
				int num = stoi(argv[2]);
				if (CheckRange(num, 'A'))
				{
					int portval = ReadPortA(num);
					cout << "Value of analogue port number " << num << " is = " << portval << endl;
					return 0;
				}
				else
				{
					cout << "Brah, out of range" << endl;
					return 0;
				}
			}
			else
			{
				cout << "Brah, incorrect Argument 2" << endl;
				return 0;
			}
		}
		else
		{
			cout << "Brah, incorrect 1st argument" << endl;
		}
	}

	return 0;
}

