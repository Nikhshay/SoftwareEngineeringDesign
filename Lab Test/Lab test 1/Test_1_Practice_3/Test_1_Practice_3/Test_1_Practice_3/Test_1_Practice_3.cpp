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

using namespace std;
// optional: your choice if you want to use these definitions for MAX-MIN-Range

const double MAXRANGE = 255;
const double MINRANGE = 0;

// All functions to be defined below and above main()  - NO Acceptations !!!  Do NOT
// define function below main() as your code will fail to compile in the auto-tester.

void WritePortB(unsigned int val)
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB "); // command to write 20 to OUSB board
	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command
	char val_string[4] = {};
	_itoa_s(val, val_string, 10);
	strcat_s(command, val_string);


	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			cout << line << endl;
		}
		_pclose(fpipe);   // close pipe
	}

}

int ReadPortB()
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB "); // command to write 20 to OUSB board

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				return 1000;
			}

		}
		_pclose(fpipe);   // close pipe
	}

	// do something with the value returned by the OUSB board, eg:
	unsigned short portb = (unsigned short)atoi(line); // convert from char array to unsigned short
	return portb;
}

bool validargument(string line)
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

bool checkrange(int val)
{
	if (val >= 0 && val <= 15)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// all function definitions and prototypes to be defined above this line
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		// no parameters on command line just the program name
		//---  edit string below: eg: "studentNumber,student_email,student_name"

		cout << "3616240,s3616240@student.rmit.edu.au,Nikhshay_Singh_Kukreja" << endl;

		//--- When run with just the program name, meaning without parameters
		// your code  MUST print student ID string in CSV format.
		// i.e. simply running "lab1_1234567.exe
		// the output MUST print student ID string in Comma Separated Version (CSV)
		// format, such as (NOTE the two commas !):
		//          "studentNumber,student_email,student_name"
		//      eg: "1234567,s1234567@student.rmit.edu.au,Tara-Louise_Brown"

		// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will
		//assume you have made some major error.  Leave it as zero.
		return 0;
	}


	//--- START YOUR CODE HERE - After you have modified the above cout statement with your details.

	else if (argc == 2)
	{
		int oldportb_value = ReadPortB();
		if (oldportb_value == 1000)
		{
			cout << "check connection" << endl;
			return 0;
		}

		ifstream infile(argv[1]);
		if (infile)
		{
			while (!infile.eof())
			{
				string each_line;
				getline(infile, each_line);
				if (each_line.length() == 0)
				{

				}
				else if (validargument(each_line))
				{
					int number = stoi(each_line);
					if (checkrange(number))
					{
						cout << number << endl;
						int retain = oldportb_value & 240;
						retain = retain | number;
						WritePortB(retain);
					}
					else
					{
						cout << "Out of range" << endl;
					}
				}
				else
				{
					cout << "invalid argument" << endl;
				}
			}
		}
		else
		{
			cout << "error opening file" << endl;
			return 0;
		}
		return 0;
	}
	else
	{
		cout << "Too many argc" << endl;
		return 0;
	}




	// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will
	//assume you have made some major error.  Leave it as zero.
	return 0;
}
// do NOT put any functions after this closing bracket, if you use functions add them before main()
// End of File  - DO NOT Modify this line or anything below this line


