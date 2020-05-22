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
int portbval = 0;
int portdval = 0;
char charportb[] = { "PORTB" };
char charportd[] = { "PORTD" };

// optional: The class data members and methods within the provided OUSB and TrafficLight are provided
//           as examples. The names of the data members and methods can be changed. The requirement is
//           that the class tag names (i.e. OUSB  and  TrafficLight) are not changed.

class OUSB 			// Do NOT change class tag name
{
private:
	// Example of data members (These can be changed....)
	int PORTB;
	int PORTD;


public:
	OUSB() { PORTB = PORTD = false; }  // Constructor: Remember to define this else it won't compile
	int read_write_ports(string r_w, char port[], int val);

};

int OUSB::read_write_ports(string r_w, char port[], int val)
{
	char command[255] = {};
	strcpy_s(command, "ousb -r io "); // command to write 20 to OUSB board
	strcat_s(command, port);
	strcat_s(command, " ");

	string portname = port;
	char val_string[4] = {};
	if (r_w == "w")
	{
		_itoa_s(val, val_string, 10);
		strcat_s(command, val_string);
	}

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				return 9999;
			}
		}
		_pclose(fpipe);   // close pipe
	}


	// do something with the value returned by the OUSB board, eg:
	int portval = (int)atoi(line); // convert from char array to int
	if (portname == "PORTB")
	{
		PORTB = portval;
		return PORTB;
	}
	else if (portname == "PORTD")
	{
		PORTD = portval;
		return PORTD;
	}
	else;

	return 0;
}



// Traffic Light class
class TrafficLight // Do NOT change class tag name
{
private:
	// Example of class data members (These can be changed....)
	bool redLamp;
	bool yellowLamp;
	bool greenLamp;

public:
	TrafficLight() { redLamp = yellowLamp = greenLamp = false; } // Constructor: Remember to define this else it won't compile
	int clear = 240;
	int counter = 0;
	void changeTrafficLightState(char *state);
};

void TrafficLight::changeTrafficLightState(char *state)
{
	OUSB board;
	//read portb and d here 
	if (*state == 'R')
	{
		redLamp = true;
		yellowLamp = false;
		greenLamp = false;

		portdval = board.read_write_ports("r", charportd, 0);
		portdval = (portdval & 207) + 16;
		board.read_write_ports("w", charportd, portdval);


		portbval = board.read_write_ports("r", charportb, 0);
		portbval = (portbval & clear) + 1 + counter;
		board.read_write_ports("w", charportb, portbval);

		*state = 'G';

	}
	else if (*state == 'Y')
	{
		redLamp = false;
		yellowLamp = true;
		greenLamp = false;

		portdval = board.read_write_ports("r", charportd, 0);
		portdval = (portdval & 207) + 32;
		board.read_write_ports("w", charportd, portdval);


		portbval = board.read_write_ports("r", charportb, 0);
		portbval = (portbval & clear) + 6 + counter;
		board.read_write_ports("w", charportb, portbval);

		*state = 'R';
	}
	else
	{
		redLamp = false;
		yellowLamp = false;
		greenLamp = true;

		portdval = board.read_write_ports("r", charportd, 0);
		portdval = (portdval & 207);
		board.read_write_ports("w", charportd, portdval);


		portbval = board.read_write_ports("r", charportb, 0);
		portbval = (portbval & clear) + 8 + counter;
		board.read_write_ports("w", charportb, portbval);

		*state = 'Y';
	}
}



int main(int argc, char *argv[])
{
	//--- When no parameters MUST print id string in CSV format. 
	if (argc == 1)  // no parameters print this line.
	{
		cout << "3616240,s3616240@student.rmit.edu.au,NikhshaySingh_Kukreja"
			<< endl;
		// Any errors in the line above,  or the naming of the file
		//  will result in 10% being deducted from your mark.
		return(0);
	}
	else;

	//check arg1

	if ((argv[1][0] == 'B' || argv[1][0] == 'D' || argv[1][0] == 'R' || argv[1][0] == 'Y' || argv[1][0] == 'G') && argv[1][1] == '\0');
	else if (argv[1][0] == 'C' && (argv[1][1] == 'R' || argv[1][1] == 'Y' || argv[1][1] == 'G') && argv[1][2] == '\0');
	else
	{
		cout << "I" << endl;
		return 0;
	}
	//'I' - Incorrect input command line argument for first operand(second parameter)
	//	'P' - Incorrect number of input command line arguments
	//	'N' - Invalid numerical command line argument(second operand or third parameter)
	//	'R' - The second operand argument is a numerical value that is out of range
	//	'Z' - MURPHY'S LAW (undefined error)


	if (argc == 2)
	{
		OUSB board;
		if (argv[1][0] == 'B')
		{
			int val = board.read_write_ports("r", charportb, 0);
			if (val == 9999)
			{
				cout << "Z" << endl;
				return 0;
			}
			else
			{
				cout << val << endl;
				return 0;
			}

		}
		else if (argv[1][0] == 'D')
		{
			int val = board.read_write_ports("r", charportd, 0);
			if (val == 9999)
			{
				cout << "Z" << endl;
				return 0;
			}
			else
			{
				cout << val << endl;
				return 0;
			}
		}
		else
		{
			cout << "P" << endl;
			return 0;
		}
	}
	else if (argc == 3)
	{
		string arg2 = argv[2];
		for (int i = 0; i < arg2.length(); i++)
		{
			if (isdigit(arg2[i]));
			else
			{
				cout << "N" << endl;
				return 0;
			}
		}

		int argument2 = atoi(argv[2]);

		OUSB board;
		if (argv[1][0] == 'B')
		{
			if (argument2 >= 0 && argument2 <= 255)
			{
				board.read_write_ports("w", charportb, argument2);
				int val = board.read_write_ports("r", charportb, 0);
				if (val == 9999)
				{
					cout << "Z" << endl;
					return 0;
				}
				else
				{
					cout << val << endl;
					return 0;
				}
			}
			else
			{
				cout << "R" << endl;
				return 0;
			}
		}
		else if (argv[1][0] == 'D')
		{
			if (argument2 >= 0 && argument2 <= 255)
			{
				board.read_write_ports("w", charportd, argument2);
				int val = board.read_write_ports("r", charportd, 0);
				if (val == 9999)
				{
					cout << "Z" << endl;
					return 0;
				}
				else
				{
					cout << val << endl;
					return 0;
				}
			}
			else
			{
				cout << "R" << endl;
				return 0;
			}
		}
		else if (argv[1][0] != 'C')
		{
			TrafficLight Shibuya;
			if (argument2 >= 0 && argument2 <= 15)
			{
				for (int i = 0; i <= argument2; i++)
				{
					Shibuya.changeTrafficLightState(&argv[1][0]);
				}

				portbval = board.read_write_ports("r", charportb, 0);
				portdval = board.read_write_ports("r", charportd, 0);
				if (portbval == 9999)
				{
					cout << "Z" << endl;
					return 0;
				}
				else;
				cout << portbval << "," << portdval << endl;
				return 0;
			}
			else
			{
				cout << "R" << endl;
				return 0;
			}
		}
		else
		{
			TrafficLight Shibuya;
			if (argument2 >= 0 && argument2 <= 15)
			{
				Shibuya.clear = 0;
				for (int i = 0; i <= argument2; i++)
				{
					Shibuya.changeTrafficLightState(&argv[1][1]);
					Shibuya.counter += 16;
				}
				portbval = board.read_write_ports("r", charportb, 0);
				portdval = board.read_write_ports("r", charportd, 0);
				if (portbval == 9999)
				{
					cout << "Z" << endl;
					return 0;
				}
				else;
				cout << portbval << "," << portdval << endl;
				return 0;
			}
			else
			{
				cout << "R" << endl;
				return 0;
			}
		}
	}
	else
	{
		cout << "P" << endl;
		return 0;
	}



	return(0); // The convention is to return Zero to signal NO ERRORS, if you change it 
			   // the AutoTester will assume you have made some major error.  
			   // Leave it as zero.
}