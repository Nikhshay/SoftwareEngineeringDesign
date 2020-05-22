#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> 
#include <cmath>     

using namespace std; // Please do not remove this line
					 // optional: your choice if you want to use/modify these definitions for MAX-MIN-Range
const double MAXRANGE = 255;
const double MINRANGE = 0;

class OUSB 			// Do NOT change class name
{
private:
	int PORTA;
	int ADCchannel;
	int PORTB;
	int PORTC;
	int PORTD;

public:
	OUSB() { PORTA = ADCchannel = PORTB = PORTC = PORTD = 0; }  // Constructor: Remember to define this else it won't compile
	//OUSB() { ; }
	~OUSB() { ; }
	 // Interface functions (These can be changed....)
	void read_write_port(string r_w, char portname[]);

	int getPORTAvalue() { return PORTA; }
	int getPORTBvalue() { return PORTB; }
	int getPORTCvalue() { return PORTC; }
	int getPORTDvalue() { return PORTD; }
	void setADCchannelvalue(int val) { ADCchannel = val; }
	void setPORTBvalue(int val) { PORTB = val; }
	void setPORTDvalue(int val) { PORTD = val; }

	void operator<<(const unsigned short &val);
	void operator>>(unsigned short &val);
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
	else if (r_w == "r")
	{
		if (portnamestring == "PORTA")
		{
			strcpy_s(command,"ousb -r adc");
			val = ADCchannel;
			strcat_s(command, " ");
			//Convert integer (in base 10) to character
			_itoa_s(val, val_string, 10);
			// append the value to the Command string
			strcat_s(command, val_string);
		}
		else;
	}
	else;

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
	if (portnamestring == "PORTA")
	{
		PORTA = portvalue;
	}
	else if (portnamestring == "PORTB")
	{
		PORTB = portvalue;
	}
	else if (portnamestring == "PORTC")
	{
		PORTC = portvalue;
	}
	else if (portnamestring == "PORTD")
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

	void redOn(bool redStatus) { redLamp = redStatus; }
	bool isREDon() { return redLamp; } // Accessor function	

	void yellowOn(bool yellowStatus) { yellowLamp = yellowStatus; };
	bool isYELLOWon() { return yellowLamp; } // Accessor function

	void greenOn(bool greenStatus) { greenLamp = greenStatus; }
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
	}

}

int main(int argc, char *argv[])
{
	

	if (argc == 3)
	{
		OUSB board;
		TrafficLight Shibuya_crossing;
		unsigned short value = 200;
		board << value;//write value to portb
		board >> value;//reading from portb
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
		int lightval = 0;

		
		char argument1 = *argv[1];// fix this shit doesnt give out para1 error
		int argument2 = atoi(argv[2]); 

		if ((argument1 == 'G' || argument1 == 'R' || argument1 == 'Y') && argv[1][1] =='\0')
		{
			if (argument2 >= 0 && argument2 <= 50)
			{
				for (int i = 0; i <= argument2; i++)
				{
					int light = Shibuya_crossing.changeTrafficLightState(argument1);
					switch (argument1)
					{
					case 'G':
						board.read_write_port("r", charportb);
						currentportbvalue = board.getPORTBvalue();
						light = (currentportbvalue & 240) + light;
						board.setPORTBvalue(light);
						board.read_write_port("w", charportb); //done this state for portb 


						board.read_write_port("r", charportd);
						lightval = board.getPORTDvalue();
						lightval = (lightval&207);
						board.setPORTDvalue(lightval);
						board.read_write_port("w", charportd);//done this state for portd
						
						
						currentportbvalue = board.getPORTBvalue(); 
						cout << "Green, which is " << currentportbvalue << " in port B" << endl;
						argument1 = 'Y';
						Sleep(1000);
						break;
					case 'Y':
						board.read_write_port("r", charportb);
						currentportbvalue = board.getPORTBvalue();
						light = (currentportbvalue & 240) + light;
						board.setPORTBvalue(light);
						board.read_write_port("w", charportb);


						board.read_write_port("r", charportd);
						lightval = board.getPORTDvalue();
						lightval = (lightval & 207) + 32;
						board.setPORTDvalue(lightval);
						board.read_write_port("w", charportd);//done this state for portd


						currentportbvalue = board.getPORTBvalue();
						cout << "Yellow, which is " << currentportbvalue << " in port B" << endl;
						argument1 = 'R';
						Sleep(1000);
						break;
					case 'R':
						board.read_write_port("r", charportb);
						currentportbvalue = board.getPORTBvalue();
						light = (currentportbvalue & 240) + light;
						board.setPORTBvalue(light);
						board.read_write_port("w", charportb);//done this state for portb


						board.read_write_port("r", charportd);
						lightval = board.getPORTDvalue();
						lightval = (lightval & 207) + 16;
						board.setPORTDvalue(lightval);
						board.read_write_port("w", charportd);//done this state for portd


						currentportbvalue = board.getPORTBvalue();
						cout << "Red, which is " << currentportbvalue << " in port B" << endl;
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
		cout << "Incorrect parameter but for this case writing or reading from port" << endl;

		//reading porta

		/*OUSB ob; 
		char charporta[] = { "PORTA" };
		ob.setADCchannelvalue(0);
		ob.read_write_port("r", charporta);
		int val = ob.getPORTAvalue();
		cout << val << endl;*/

		//reading pinc

		/*OUSB ob; 
		char charportc[] = { "PORTC" };
		ob.read_write_port("r", charportc);
		int val = ob.getPORTCvalue();
		cout << val << endl;*/

		 //writing portb then reading the value

		/*OUSB ob;
		char charportb[] = { "PORTB" };
		board.setPORTBvalue(255);
		board.read_write_port("w", charportb);
		int currentportbvalue = board.getPORTBvalue();
		cout << val << endl;*/
	}
	return(0);
}



