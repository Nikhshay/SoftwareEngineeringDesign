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

// optional: your choice if you want to write class method and function prototypes here.
//           They should be defined above the OUSB and TrafficLight Class definitions
//           if they are going to be used by the classes themselves as all code must
//           contained in this file (ie. no separate *.h files for autotester)


class OUSB 			// Do NOT change class name
{
private:
	int PORTA;
	int PORTB;
	int PORTC;
	int PORTD;

public:
	OUSB() { PORTA = PORTB = PORTC = PORTD = 0; }  // Constructor: Remember to define this else it won't compile

	 // Interface functions (These can be changed....)
	void read_write_port(string r_w, char portname[]);

	int getPORTAvalue() { return PORTA; }
	int getPORTBvalue() { return PORTB; }
	int getPORTCvalue() { return PORTC; }
	int getPORTDvalue() { return PORTD; }
	void setPORTBvalue(int val) {PORTB = val; }
	void setPORTDvalue(int val) {PORTD = val; }

	void operator<<(const unsigned short &val);
	void operator>>(unsigned short &val);
	// you may choose to implement operator overloaded functions for read and write functions for portb
	// void operator<<(const int &val); // write portb
	// void operator>>(int &val);       // read portb	
};
void OUSB::operator<<(const unsigned short &val)
{
	setPORTBvalue(val);
	char portboperator[] = { "PORTB" };
	read_write_port("w", portboperator);
}

void OUSB::operator>>(unsigned short &val)
{
	setPORTBvalue(val);
	char portboperator[] = { "PORTB" };
	read_write_port("r", portboperator);
}

void OUSB::read_write_port(string r_w, char portname[])
{
	string portnamestring = portname;
	int val = 0;
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io " }; // Need to have a extra space after PORTB
	char val_string[4] = {};
	strcat_s(command, portname);

	if (r_w == "w")
	{
		if (portnamestring == "PORTB")
		{
			val = PORTB;
		}
		else if (portnamestring == "PORTD")
		{
			val = PORTD;
		}
		else
		{
			return;
		}
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

		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	unsigned int portvalue = (unsigned int)atoi(line);
	if (portname == "PORTA")
	{
		PORTA = portvalue;
	}
	else if (portname == "PORTB")
	{
		PORTB = portvalue;
	}
	else if (portname == "PORTC")
	{
		PORTC = portvalue;
	}
	else if (portname == "PORTD")
	{
		PORTD = portvalue;
	}
	else
	{
		return;
	}
}

// Traffic Light class
class TrafficLight // Do NOT change class name
{
private:
	bool redLamp;
	bool yellowLamp;
	bool greenLamp;
	int currentstate = 0;
public:
	TrafficLight() { redLamp = yellowLamp = greenLamp = false; } // Constructor: Remember to define this else it won't compile

	void redOn(bool state) { redLamp = state; }
	bool isREDon() { return redLamp; } // Accessor function	

	void yellowOn(bool state) { yellowLamp = state; };
	bool isYELLOWon() { return yellowLamp; } // Accessor function

	void greenOn(bool state) { greenLamp = state; }
	bool isGREENon() { return greenLamp; } // Accessor function

	int changeTrafficLightState(char state);
	int what_is_current_state() { return currentstate; }
	void setting_current_state(int val) { currentstate = val; }
};
// write all class methods and stand alone functions here below this line



int TrafficLight::changeTrafficLightState(char state)
{
	switch (state)
	{
	case 'R':
		greenOn(false);
		yellowOn(false);
		redOn(true);
		return 1;
	case 'Y':
		greenOn(false);
		yellowOn(true);
		redOn(false);
		return 6;
	case 'G':
		greenOn(true);
		yellowOn(false);
		redOn(false);
		return 8;
	default:
		greenOn(false);
		yellowOn(false);
		redOn(true);
		return 1;
	}

}

int main(int argc, char *argv[])
{
	OUSB board;
	TrafficLight Shibuya_crossing;
	OUSB myOBJ;
	unsigned short value = 255;
	myOBJ << value;//write value to portb
	myOBJ >> value;//reading from portb
	cout << "Value= " << value << endl;
	Sleep(1000);
	char charporta[] = { "PORTA" };
	char charportb[] = { "PORTB" };
	char charportc[] = { "PORTC" };
	char charportd[] = { "PORTD" };
	int currentportavalue = 0;
	int currentportbvalue = 0;
	int currentportcvalue = 0;
	int currentportdvalue = 0;

	board.setPORTBvalue(255);
	board.read_write_port("w", charportb);

	if (argc == 3)
	{
		char argument1 = *argv[1];
		int argument2 = atoi(argv[2]);

		if (argument1 == 'G' || argument1 == 'R' || argument1 == 'Y')
		{
			if (argument2 >= 0 && argument2 <= 50)
			{
				for (int i = 0; i < argument2; i++)
				{
					int light = Shibuya_crossing.changeTrafficLightState(argument1);

					switch (argument1)
					{
					case 'G':
						board.setPORTBvalue(light);
						board.read_write_port("w", charportb);
						currentportavalue = board.getPORTBvalue();
						cout << currentportavalue << endl;
						argument1 = 'Y';
						Sleep(1000);
						break;
					case 'Y':
						board.setPORTBvalue(light);
						board.read_write_port("w", charportb);
						currentportavalue = board.getPORTBvalue();
						cout << currentportavalue << endl;
						argument1 = 'R';
						Sleep(1000);
						break;
					case 'R':
						board.setPORTBvalue(light);
						board.read_write_port("w", charportb);
						currentportavalue = board.getPORTBvalue();
						cout << currentportavalue << endl;
						argument1 = 'G';
						Sleep(1000);
						break;
					}


				}

			}
			else
			{
				cout << "2nd argument above 50/below 0" << endl;
			}

		}

		else
		{
			cout << "Incorrect 1st argument" << endl;
		}

	}
	else
	{
		cout << "Incorrect parameter" << endl;
	}

	return(0); 
}



