#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> 
#include <cmath>     


using namespace std;
const double MAXRANGE = 255;
const double MINRANGE = 0;

class OUSB
{
private:
	unsigned short PORTA;
	unsigned short PORTB;
	unsigned short PORTC;
	unsigned short PORTD;

	unsigned short runOUSBcommand(char *command);

public:
	//OUSB() {PORTA = PORTB = PORTC = PORTD = 0;}
	//~OUSB() { ; }
	void writePORTB(unsigned short val, string port);
	void writePORTD(unsigned short val, string port);

	unsigned short readPORTA(string port);
	unsigned short readPORTB(string port);
	unsigned short readPORTC(string port);
	unsigned short readPORTD(string port);

	void operator<<(const unsigned short &val); // write portb
	void operator>>(unsigned short &val);       // read portb	
};

void OUSB::operator<<(const unsigned short &val)
{
	readPORTB("PORTB");
}

void OUSB::operator>>(unsigned short &val)
{
	writePORTB(val, "PORTB");
}


unsigned short OUSB::runOUSBcommand(char *command)
{
	FILE *fpipe;
	char line[256];
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
		}
		_pclose(fpipe);
	}
	int ousbOP = (int)atoi(line);
	return ousbOP;
}
unsigned short OUSB::readPORTA(string port)
{
	int portval = 0;
	char line[255] = {};
	FILE *fpipe;
	//char val_string[4] = {};
	char port_string[255] = {};
	strcpy_s(port_string, port.c_str());
	//_itoa_s(val, val_string, 10);
	char command[256] = { "ousb -r io " };
	strcat_s(command, port_string);
	//strcat_s(command, val_string);
	PORTA = runOUSBcommand(command);

	return PORTA;
}
unsigned short OUSB::readPORTB(string port)
{
	int portval = 0;
	char line[255] = {};
	FILE *fpipe;
	//char val_string[4] = {};
	char port_string[255] = {};
	strcpy_s(port_string, port.c_str());
	//_itoa_s(val, val_string, 10);
	char command[256] = { "ousb -r io " };
	strcat_s(command, port_string);
	//strcat_s(command, val_string);
	PORTB = runOUSBcommand(command);

	return PORTB;
}
unsigned short OUSB::readPORTC(string port)
{
	int portval = 0;
	char line[255] = {};
	FILE *fpipe;
	//char val_string[4] = {};
	char port_string[255] = {};
	strcpy_s(port_string, port.c_str());
	//_itoa_s(val, val_string, 10);
	char command[256] = { "ousb -r io " };
	strcat_s(command, port_string);
	//strcat_s(command, val_string);
	PORTC = runOUSBcommand(command);

	return PORTC;
}

unsigned short OUSB::readPORTD(string port)
{
	int portval = 0;
	char line[255] = {};
	FILE *fpipe;
	//char val_string[4] = {};
	char port_string[255] = {};
	strcpy_s(port_string, port.c_str());
	//_itoa_s(val, val_string, 10);
	char command[256] = { "ousb -r io " };
	strcat_s(command, port_string);
	//strcat_s(command, val_string);
	PORTD = runOUSBcommand(command);

	return PORTD;
}

void OUSB::writePORTB(unsigned short val, string port)
{
	int portval = 0;
	char line[255] = {};
	FILE *fpipe;
	char val_string[4] = {};
	char port_string[255] = {};
	char space[4] = { " " };
	strcpy_s(port_string, port.c_str());
	_itoa_s(val, val_string, 10);
	char command[256] = { "ousb -r io " };
	strcat_s(command, port_string);
	strcat_s(command, space);
	strcat_s(command, val_string);
	runOUSBcommand(command);

	//return PORTB;
}
void OUSB::writePORTD(unsigned short val, string port)
{
	int portval = 0;
	char line[255] = {};
	FILE *fpipe;
	char val_string[4] = {};
	char port_string[255] = {};
	char space[4] = { " " };
	strcpy_s(port_string, port.c_str());
	_itoa_s(val, val_string, 10);
	char command[256] = { "ousb -r io " };
	strcat_s(command, port_string);
	strcat_s(command, space);
	strcat_s(command, val_string);
	runOUSBcommand(command);

	//return PORTD;
}

class TrafficLight
{
private:
	bool redLamp;
	bool yellowLamp;
	bool greenLamp;
public:
	//TrafficLight() { ; }
	//~TrafficLight() { ; }

	void redOn(bool redStatus) { redLamp = redStatus; }
	bool isREDon() { return redLamp; } // Accessor function	

	void yellowOn(bool yellowStatus) { yellowLamp = yellowStatus; };
	bool isYELLOWon() { return yellowLamp; } // Accessor function

	void greenOn(bool greenStatus) { greenLamp = greenStatus; }
	bool isGREENon() { return greenLamp; } // Accessor function

	char changeTrafficLightState(char state, int counter);
};


char TrafficLight::changeTrafficLightState(char state, int counter)
{
	OUSB ousb;
	int portbvalue = ousb.readPORTB("PORTB");
	int portdvalue = ousb.readPORTD("PORTD");
	if (counter == 6969) //no counter
	{
		portbvalue = portbvalue & 240;
		counter = 0;
	}
	else
	{
		portbvalue = 0;
	}

	switch (state)
	{
		case 'R':
		{
			redLamp = true;
			yellowLamp = false;
			greenLamp = false;

			portbvalue += 1;
			portbvalue += counter;
			ousb.writePORTB(portbvalue, "PORTB");
			portdvalue = (portdvalue & 207) + 16;
			ousb.writePORTD(portdvalue, "PORTD");
			state = 'G';
			return state;
		}
		case 'G':
		{
			redLamp = false;
			yellowLamp = false;
			greenLamp = true;

			portbvalue += 8;
			portbvalue += counter;
			ousb.writePORTB(portbvalue, "PORTB");
			portdvalue = (portdvalue & 207);
			ousb.writePORTD(portdvalue, "PORTD");
			state = 'Y';
			return state;
		}
		case 'Y':
		{
			redLamp = false;
			yellowLamp = true;
			greenLamp = false;

			portbvalue += 6;
			portbvalue += counter;
			ousb.writePORTB(portbvalue, "PORTB");
			portdvalue = (portdvalue & 207) + 32;
			ousb.writePORTD(portdvalue, "PORTD");
			state = 'R';
			return state;
		}
	}
}


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "3577887,s3577887@student.rmit.edu.au,Shenal_Perera" << endl;
		return(0);
	}

	else if (argc == 2)
	{
		if (argv[1][0] == 'B' && argv[1][1] == '\0')
		{
			OUSB ousb;
			int val = ousb.readPORTB("PORTB");
			cout << val << endl;
			return 0;

		}
		else if (argv[1][0] == 'D' && argv[1][1] == '\0')
		{
			OUSB ousb;
			int val = ousb.readPORTD("PORTD");
			cout << val << endl;
			return 0;

		}
		else
		{
			cout << "Arugment 1 error" << endl;
			return 0;
		}
	}
	else if (argc == 3)
	{
		if ((argv[1][0] == 'B' || argv[1][0] == 'D' || argv[1][0] == 'R' || argv[1][0] == 'Y' || argv[1][0] == 'G') && argv[1][1] == '\0');
		else if ((argv[1][0] == 'C') && (argv[1][1] == 'R' || argv[1][1] == 'Y' || argv[1][1] == 'G') && argv[1][2] == '\0');
		else
		{
			cout << "Argument 1 error" << endl;
			return 0;
		}
		string arg2 = argv[2]; //put to string for isdigit function

		for (int i = 0; i < arg2.length(); i++)//check arg2 
		{
			if (isdigit(arg2[i]));
			else
			{
				cout << "arguent 2 error" << endl;
				return 0;
			}
		}
		int num = atoi(argv[2]);

		OUSB ousb;

		if (argv[1][0] == 'B')
		{
			if (num >= 0 && num <= 255)
			{
				ousb.writePORTB(num, "PORTB");
				int val = ousb.readPORTB("PORTB");
				cout << val << endl;
				return 0;
			}
			else
			{
				cout << "Out of range 2nd arg << endl" << endl;
				return 0;
			}
		}
		else if (argv[1][0] == 'D')
		{
			if (num >= 0 && num <= 255)
			{
				ousb.writePORTD(num, "PORTD");
				int val = ousb.readPORTD("PORTD");
				cout << val << endl;
				return 0;
			}
			else
			{
				cout << "Out of range 2nd arg << endl" << endl;
				return 0;
			}
		}
		else;



		TrafficLight light;

		if (argv[1][0] != 'C')
		{
			char state = argv[1][0];
			if (num <= 15 && num >= 0)
			{
				for (int i = 0; i < num; i++)
				{
					state = light.changeTrafficLightState(state, 6969);
					Sleep(1000);
				}
				cout << "After " << num << " cycle, portb value is " << ousb.readPORTB("PORTB") << " and portd value is " << ousb.readPORTD("PORTD") << endl;
				return 0;
			}
			else
			{
				cout << "number out of range" << endl;
				return 0;
			}
		}
		else
		{
			char state = argv[1][1];
			int counter = 0;
			if (num <= 15 && num >= 0)
			{
				for (int i = 0; i <= num; i++)
				{
					Sleep(1000);
					state = light.changeTrafficLightState(state, counter);
					counter += 16;
				}
				cout << "After " << num << " cycle, portb value is " << ousb.readPORTB("PORTB") << " and portd value is " << ousb.readPORTD("PORTD") << endl;
				return 0;
			}
			else
			{
				cout << "number out of range" << endl;
				return 0;
			}
		}

	}
	else
	{
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}


	return(0);
}