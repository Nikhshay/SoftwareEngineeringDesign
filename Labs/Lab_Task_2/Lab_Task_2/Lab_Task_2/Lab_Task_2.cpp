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

unsigned int WritePortB(unsigned int val)
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
	unsigned int portb = (unsigned int)atoi(line);
	return portb;
}

void checkrange(int i)
{
	if (i > 0 && i < 15)
	{
		cout << "in range" << endl;
		sleep_for(1s);
		WritePortB(i);
	}
	else
	{
		cout << "out of range" << endl;
	}
}

bool checkrangeTask5(int i)
{
	if (i > 0 && i < 15)
	{
		cout << "in range" << endl;
		return true;
	}
	else
	{
		cout << "out of range" << endl;
		return false;
	}
}

bool validarg(string storage)
{
	bool current = true;
	for (int i = 0; i < storage.length(); i++)
	{
		if (isdigit(storage[i]))
		{
			cout << storage[i] << " is digit ";
			current = true;
		}
		else
		{
			cout << " " << storage[i] << " is not digit";
			current = false;
			cout << endl;
			return false;
		}

	}
	cout << endl;
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect command line argument. Check it brah" << endl;
		return 0;
	}
	else
	{
		//Task 2 reading from text file
		cout << "Task 2" << endl;
		fstream infile(argv[1]);
		if (!infile)
		{
			cout << "Cannot open file test1.txt" << endl;
			return 0;
		}
		while (!infile.eof())
		{
			char storage[255];
			infile >> storage;
			cout << storage << endl;
		}
		infile.close();

		ifstream infile1(argv[1]);
		//Task 3 and 4 check range and output to portb 
		cout << endl << endl << "Task 3 and 4" << endl << endl;
		while (!infile1.eof())
		{
			string storage;
			getline(infile1, storage);
			if (storage.length() == 0)
			{

			}
			else if (validarg(storage))
			{
				int val = stoi(storage);
				cout << storage << " is a valid argument" << endl;
				checkrange(val);
			}
			else
			{
				cout << storage << " is not a valid argument" << endl;
			}

		}

		infile1.close();


		ifstream infile2(argv[1]);
		cout << "Task 5" << endl;
		int oldnumber = 0;
		cout << "Enter number between 16-255" << endl;
		cin >> oldnumber;
		WritePortB(oldnumber);

		while (!infile2.eof())
		{
			string storage;
			getline(infile2, storage);
			if (storage.length() == 0)
			{

			}
			else if (validarg(storage))
			{
				int val = stoi(storage);
				cout << storage << " is a valid argument" << endl;
				if (checkrangeTask5(val))
				{
					int retain = oldnumber & 240;
					retain |= val;
					WritePortB(retain);
					sleep_for(1s);
				}
			}
			else
			{
				cout << storage << " is not a valid argument" << endl;
			}

		}

		infile2.close();





		cout << "Task 6" << endl;
		ofstream outfile(argv[1], ios::app | ios::out);

		int A = 0;
		int B = 0;
		cout << "Variable A is: ";
		cin >> A;
		cout << "Variable B is: ";
		cin >> B;

		A = A ^ B;
		cout << "A = A ^ B = " << A << endl;
		outfile << A << endl;

		B = A ^ B;
		cout << "B = A ^ B = " << B << endl;
		outfile << B << endl;

		A = A ^ B;
		cout << "A = A ^ B = " << A << endl;
		outfile << A << endl;

		outfile.close();


		return 0;
	}

}

