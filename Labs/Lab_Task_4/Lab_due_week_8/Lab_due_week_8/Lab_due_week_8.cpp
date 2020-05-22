
#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> 
#include <cmath>     

using namespace std;

//check range
//check valid arg
//set freq
//write duty cycle
//read adc

void SetFrequency()
{
	char command[256] = { "ousb pwm-freq 1 46" };
	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{
		}
		_pclose(fpipe);   // close pipe
	}

}

void WriteDutyCycle(int val)
{
	char command[256] = { "ousb pwm 1 " };
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
		}
		_pclose(fpipe);   // close pipe
	}
}

int ReadADC(int val)
{
	char command[256] = { "ousb -r adc " };
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
		}
		_pclose(fpipe);   // close pipe
	}

	// do something with the value returned by the OUSB board, eg:
	int portvalue = (int)atoi(line); // convert from char array to unsigned short
	return portvalue;
}

bool checkrange(int num, string when)
{
	if (when == "Here" && num >= 0 && num <= 1023)
	{
		return true;
	}
	else if (when == "Now Here" && num >= 0 && num <= 100)
	{
		return true;
	}
	else if (when == "Then Here" && num >= 0 && num <= 7)
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
		if (isdigit(line[i]));
		else
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{

	if (argc == 3)
	{
		if ((argv[1][0] == 'P' || argv[1][0] == 'A' || argv[1][0] == 'L' || argv[1][0] == 'M') && argv[1][1] == '\0');
		else
		{
			cout << "Invalid Argument 1" << endl;
			return (0);
		}
		int secondparameter = 0;
		if (validarg(argv[2]))
		{
			secondparameter = atoi(argv[2]);
		}
		else
		{
			secondparameter = 6666;
		}
		if (checkrange(secondparameter, "Here"));
		else
		{
			cout << "Invalid Second Argument" << endl;
			return (0);
		}


		if (argv[1][0] == 'P')
		{
			if (checkrange(secondparameter, "Now Here"))
			{
				cout << "Doing P command" << endl;
				SetFrequency();
				WriteDutyCycle(secondparameter);
				cout << "DONE!" << endl;
				return (0);
			}
			else
			{
				cout << "Invalid P range" << endl;
				return (0);
			}
		}
		else if (argv[1][0] == 'A')
		{
			if (checkrange(secondparameter, "Then Here"))
			{
				cout << "Doing A command" << endl;
				int portvalue = ReadADC(secondparameter);
				cout << "The valud read from port number " << secondparameter << " is " << portvalue << endl;
				return (0);
			}
			else
			{
				cout << "Invalid A range" << endl;
				return (0);
			}
		}
		else if (argv[1][0] == 'L')
		{
			cout << "Doing L command" << endl;
			SetFrequency();
			int currentpwm = 50;
			WriteDutyCycle(currentpwm);
			int targetadc = secondparameter;
			int currentadc = ReadADC(0);
			for (int i = 0; i < 60; i++)
			{
				cout << "Target ADC is " << targetadc << " Current ADC is " << currentadc << " Next PWM is " << currentpwm << endl;
				if (targetadc > currentadc && currentpwm > 0)
				{
					currentpwm--;
				}
				else if (targetadc < currentadc && currentpwm < 100)
				{
					currentpwm++;
				}
				else;
				WriteDutyCycle(currentpwm);
				currentadc = ReadADC(0);
			}
			cout << currentpwm << endl;
			return(0);

		}
		else if (argv[1][0] == 'M')
		{
			cout << "Doing M command" << endl;
			SetFrequency();
			int currentpwm = 50;
			WriteDutyCycle(currentpwm);
			int targetadc = secondparameter;
			int currentadc = ReadADC(0);
			for (int i = 1; i > 0; i++)
			{
				cout << "Target ADC is " << targetadc << " Current ADC is " << currentadc << " Next PWM is " << currentpwm << endl;
				if (targetadc > currentadc && currentpwm > 0)
				{
					currentpwm--;
				}
				else if (targetadc < currentadc && currentpwm < 100)
				{
					currentpwm++;
				}
				else;
				WriteDutyCycle(currentpwm);
				currentadc = ReadADC(0);
			}
			cout << currentpwm << endl;
		}
		else;


	}//end of 2 argument

	else// if not 2 argument
	{
		cout << "Please only put 2 argument" << endl;
		return(0);
	}

	return(0);
}








