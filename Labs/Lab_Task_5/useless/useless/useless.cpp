#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> 
#include <cmath>     
// Do NOT Add or remove any #include statements to this project!!
// All library functions required should be covered by the above
// include list. Do not add a *.h file for this project as all your
// code should be included in this file.

using namespace std; // Please do not remove this line

					 // optional: your choice if you want to use/modify these definitions for MAX-MIN-Range
const double MAXRANGE = 255;
const double MINRANGE = 0;

// optional: It is your choice if you want to write class method and function prototypes here.
//           They should be defined above the OUSB and TrafficLight Class definitions
//           if they are going to be used by the classes themselves as all code must
//           contained in this file (ie. no separate *.h files for autotester)

// optional: The class data members and methods within the provided OUSB and TrafficLight are provided
//           as examples. The names of the data members and methods can be changed. The requirement is
//           that the class tag names (i.e. OUSB  and  TrafficLight) are not changed.

class OUSB 			// Do NOT change class tag name
{
private:
	// Example of data members (These can be changed....)
	unsigned short PORTA;
	unsigned short PORTB;
	unsigned short PORTC;
	unsigned short PORTD;

	// Example of class Interface methods (These can be changed....)
	unsigned short runOUSBcommand(const char *command);

public:
	OUSB() { ; }  // Constructor: Remember to define this else it won't compile

	 // Example of Interface methods (These can be changed....)
	void writePORTB(unsigned short newValue);
	void writePORTD(unsigned short newValue);

	unsigned short readPORTA(unsigned short pinNumber);
	unsigned short readPORTB();
	unsigned short readPORTC();
	unsigned short readPORTD();


	// you may choose to implement operator overloaded functions for read and write functions for portb
	void operator<<(const unsigned short &val); // write portb
	void operator>>(unsigned short &val);       // read portb	
};

void OUSB::operator>>(unsigned short &val)
{
	val = readPORTB();
}

void OUSB::operator<<(const unsigned short &val)
{
	writePORTB(val);
}

unsigned short OUSB::runOUSBcommand(const char *command)
{
	FILE *fpipe;
	char line[256];

	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	unsigned short PORTvalue;

	PORTvalue = atoi(line);
	return PORTvalue;
}

void OUSB::writePORTB(unsigned short newValue)
{
	char command[255] = { "ousb -r io PORTB " };
	char val_string[4] = {};
	_itoa_s(newValue, val_string, 10);
	strcat_s(command, val_string);

	runOUSBcommand(command);
}

void OUSB::writePORTD(unsigned short newValue)
{
	char command[255] = { "ousb -r io PORTD " };
	char val_string[4] = {};
	_itoa_s(newValue, val_string, 10);
	strcat_s(command, val_string);

	runOUSBcommand(command);
}

unsigned short OUSB::readPORTA(unsigned short pinNumber)
{
	char command[255] = { "ousb -r io PORTA " };
	PORTA = runOUSBcommand(command);
	return PORTA;
}

unsigned short OUSB::readPORTB()
{
	char command[255] = { "ousb -r io PORTB " };
	PORTB = runOUSBcommand(command);
	return PORTB;
}

unsigned short OUSB::readPORTC()
{
	char command[255] = { "ousb -r io PORTC " };
	PORTC = runOUSBcommand(command);
	return PORTC;
}

unsigned short OUSB::readPORTD()
{
	char command[255] = { "ousb -r io PORTD " };
	PORTD = runOUSBcommand(command);
	return PORTD;
}


int main(int argc, char *argv[])
{
	OUSB board;
	int val = board.readPORTD();
	cout << val << endl;
	return 0;
}