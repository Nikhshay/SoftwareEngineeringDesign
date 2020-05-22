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



void WritePortB(unsigned int val)
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB "); 
	FILE *fpipe;
	char line[250] = {}; 
	char val_string[4] = {};
	_itoa_s(val, val_string, 10); //convert int to string
	strcat_s(command, val_string); // copy the number to the command

	fpipe = (FILE*)_popen(command, "r");    
	if (fpipe != NULL)					  
	{
		while (fgets(line, sizeof(line), fpipe))
		{   

		}
		_pclose(fpipe);  
	}

}

int ReadPortB()
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB ");

	FILE *fpipe;
	char line[250] = {}; 

	fpipe = (FILE*)_popen(command, "r");   
	if (fpipe != NULL)					  
	{
		while (fgets(line, sizeof(line), fpipe))
		{  
			if (line[0] == 'F') // if Fatal Exception! detected
			{
				_pclose(fpipe); //close the pipe
				return 1000; //return 1000
			}
		}
		_pclose(fpipe); 
	}

	
	unsigned short portb = (unsigned short)atoi(line);
	return portb;
}

bool CheckRange(int val)
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


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		
		cout << "3616240,s3616240@student.rmit.edu.au,Nikhshay_Singh_Kukreja" << endl;
		return 0;
	}

	else if (argc == 2)
	{

		int oldportb = ReadPortB();
		if (oldportb == 1000) // check connection
		{
			cout << "Z" << endl;
			return 0;
		}
		else
		{
			//do nothing cuz ousb connection is fine
		}


		ifstream infile(argv[1]);
		if (!infile) //check valid file
		{
			cout << "F" << endl;
			return 0;
		}
		else
		{
			//do nothing cuz can open file
		}


		while (!infile.eof()) //not end of file
		{
			string line;
			getline(infile, line);
			if (line.length() == 0) // empty line
			{
				//do nothing cuz empty intput
			}
			else if (validarg(line)) //valid argument?
			{
				int val = stoi(line);
				if (CheckRange(val)) // valid argument in range? 
				{
					//cout << line << endl; // just for checking;
					int retain = oldportb & 240; //turn off lower 4 bit
					retain |= val; // turn on bottom 4 bit according to val
					WritePortB(retain); // write the number to portb
				}
				else
				{
					cout << "Y" << endl; // out of range
				}
			}
			else
			{
				cout << "Y" << endl; // invalid input
			}


		}


		return 0;
	}

	else
	{
		cout << "P" << endl; //too many argument
		return 0;
	}

	return 0;
}



