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


void SetFrequency()
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





int main(int argc, char* argv[])
{
	cout << "Task 2" << endl;
	SetFrequency();
	cout << "What is the duty cycle you want in percent? (enter between 0-100)" << endl;
	int dc = 0;
	cin >> dc;
	if (dc >= 0 && dc <= 100)
	{
		SetDutyCycle(dc);
	}
	else
	{
		cout << "Brah, read the instruction" << endl;
		return 0;
	}

	cout << "Task 3" << endl;
	cout << "Which Port do you want to read from? (Enter number 0-7 Below)" << endl;
	cout << "0-4 Available for use" << endl;
	cout << "5 Board trim-pot" << endl;
	cout << "6 Light Dependent Resistor (LDR)" << endl;
	cout << "7 Piezo Buzzer of a user adjestable link" << endl;
	//example commnad from reference
	//ousb adc 5 # read the trim pot value.
	//ousb adc 6 # read the LDR value.
	int val;
	cin >> val;
	if (val >= 0 && val <= 7)
	{
		int port = ReadPortA(val);
		cout << "Value from port number " << val << " is " << port << endl;
	}
	else
	{
		cout << "Brah, read the instruction" << endl;
		return 0;
	}


	return 0;
}

