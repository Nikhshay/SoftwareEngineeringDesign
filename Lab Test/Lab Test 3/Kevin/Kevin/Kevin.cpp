
	/*==============  Proforma : EEET2250 Lab Test 3 OUSB class and traffic light state machine ============

	File version: 2016_v01.0

	PURPOSE:
	This file is a proforma for the EEET2250 Lab Test 3: OUSB class and traffic light state machine operations with the OUSB board.
	This file defines the assignment - there is no other documentation. You must extend this C++ program to cope with the functionality identified below.

	In the labs you will given OUSB boards to practice on. However if you may also want to purchase one for $60, the details are available on Blackboard.


	BACKGROUND:
	The assignment will be a command line program that reads parameters from the command line and prints out a well defined result, and nothing else.
	No additional keyboard user input should be required for the process.


	GOAL:
	You are to write a program that implements access to the OUSB board using classes ('B' command).
	Your program will implement a traffic light software state machine ('R', 'Y', 'G' commands), using PORTB of the OUSB board to indicate the current traffic light state.
	The program should perform error checking.



	General info:
	Use debug mode and a breakpoint at the return statement prior to program finish in main.

	To avoid losing 10% follow the instructions below:

	Rename your file NOW to lab3_1234567.cpp, where 1234567 is your student number.
	Your filename MUST NEVER EVER contain any spaces.  _under_score_is_Fine.
	Do not include the 's' in front of your student number.

	You MUST run this file as part of a Project.

	DO NOT use system wide pre-defined variables because systems differ
	and what is defined in your system may not be be defined in another system.


	SPECIFICATIONS:
	OUSB CLASS: Your program must access the OUSB board using a class (including read from/write to PORTB).
	Ensure that you have private class variables to store the current value of PORTB. Include appropriate accessor functions and functions to read from and write to PORTB.

	Your program should accept the following command line parameters:
	- 'B' command: 'B' is the first parameter and the optional second parameter is the number to write to PORTB.
	Print the current value (only the numeric value) read from PORTB to the command line.

	e.g., 	lab3_1234567.exe B    // Read from PORTB and write the number read from PORTB to the console screen
			lab3_1234567.exe B 10 // Write 10 to PORTB and write the number 10 to the console screen


	TRAFFIC LIGHT STATE MACHINE: Your program must use the OUSB class to implement a single traffic light state machine, where the command line parameters indicate
	the starting state of the traffic light and the number of state transitions the program should run for.

	The traffic light is composed of three lamps: Red, Yellow, and Green. The only lamp sequence possible is
	Green-->Yellow-->Red (then back to Green and repeat). Only one lamp can be on at a time.

	Ensure that you have private class variables to store the current state of the traffic light (either as a single state to represent all three lamps, or three lamp states).
	Include appropriate accessor functions and functions to change the traffic light state in the class.

	Use PORTB to indicate the current state of the traffic light. Assume that the red, yellow and green lamps are represented by the
	following PORTB combinations (only the first two bits of PORTB are used):
	- Red ON: turn on bit 0 only (bit 1 off)
	- Yellow ON: turn on both bits 0 and 1
	- Green ON: turn on bit 1 only (bit 0 off)

	Your program should accept the following command line parameters:
	- 'R', 'Y' or 'G': one letter only as the first parameter to indicate which state to start the traffic light in
	- The second parameter is a number to indicate the number of state transitions to run the traffic light for (not including the initial starting state)

	e.g.,	lab3_1234567 R 3 // Start the traffic light on Red and run for three transitions  i.e., R-->G-->Y-->R
			lab3_1234567 Y 2 // Start the traffic light on Yellow and run for two transitions i.e., Y-->R-->G
			lab3_1234567 G 5 // Start the traffic light on Green and run for five transitions i.e., G-->Y-->R-->G-->Y-->R

	Upon completing all the state transitions, the program should print out the last value of PORTB (i.e., the current state of the traffic light) and exit.


	Your program MUST use pipes to communicate with the OUSB board, system calls are NOT allowed:
	 system("ousb -r io portb 127");   // not allowed

	System calls take longer and automatically echo the result to the command shell window. If you use system calls in your code it is likely the code will not work properly.
	You will most likely lose all marks for this lab.

	Therefore, you MUST use the code using pipes. See the code fragments given to you and explained in lectures and on Blackboard.
	Code to access the OUSB board will be provided in the Lab Test.

	You MUST close the pipe using '_pclose(<pipename>); ' after every 'fgets()' command in your loop. Before exiting your program
	call '_pclose(<pipename>); ' one last time. Failure to not do this will result in your code being highly unreliable and you could lose a lot of marks.

	************  IMPORTANT !!!  *********   IMPORTANT !!!   *******************************
	***
	***  IN LAB TEST 3 YOU WILL AUTOMATICALLY LOSE 20% OF YOUR MARK IF YOU
	***  DO NOT HAVE MATCHING _popen(...) and _pclose(...) - this will be checked!!!
	***
	***  IN LAB TEST 3 YOU MUST IMPLEMENT A CLASS to access the OUSB board - this
	***  will be checked - your maximum score will be capped at 40% if you do not use
	***  an OUSB class!!!
	***
	************  IMPORTANT !!!  *********   IMPORTANT !!!   *******************************

	About pipes and _popen:
	http://www.cplusplus.com/forum/windows/1341/
	http://www.cplusplus.com/forum/windows/10766/

	------------------------------

	OUSB OUTPUT FORMATS: AS FOR A COMMAND SHELL WINDOW.

	The OUSB board outputs commands sent to it in a default format. You will be required to change the default setting.

	Testple: if the command given is: "ousb.exe io portb 128"
	The DEFAULT response from the OUSB board is: PORTB = 128     this is NOT what you should produce.

	Your code should display ONLY the number 128
	The method of how to make the OUSB board respond with just the number as output can easily be found out by:
	1) opening a command window in Windows: START -> RUN -> "cmd"
	2) typing 'ousb' on the command line. This will bring up a help menu
	3) see the option for 'raw (decimal)' output.

	If you use _popen and a file pipeline do not add EXTRA newlines, do not add extra blank
	spaces or any other characters. Output must be as it would be for a standard command line window.

	The only text in the command shell window should be:
	- text returned from the OUSB board in response to your code or an error condition
	- NO debug code should appear in the command shell window. This means: any of your debug comments must be turned off for the final submitted copy.

	------------------------------

	ERRORS:
	The following text lists errors you must detect and a priority of testing.  NB: order of testing is important. All outputs are a single character followed by a
	newline ( endl or \n).

	DO NOT add more than what is specified, do NOT add additional information, simply and only the output as required.

	DO NOT use 'cin', do NOT ask for user input. All input MUST be read in from the command line and from file.

	The closing } of the main statement must be the last closing brace in the file. The last line containing "main()" must be the main statement where execution is started.
	In other words: ALL your functions MUST be between the start of the file and the
	int main(int argc, char *argv[]) function. Do NOT put any functions after the main function, if you use functions add them BEFORE the 'main' function

	You should use the Integrated debugging environment. In the lab tests the command line window will not be available.

	When your code exits the 'main' function using the 'return' command then you MUST use zero as the return value. This requirement is for exiting the 'main' function ONLY.


	ERROR CHECK 1:   NUMBER OF PARAMETERS
	NB: the name of the program counts as the 1st parameter (0th value in the array).

	If the number of parameters is 1: the program MUST print student ID string in CSV format and then exit. That is, when the
	program is run without any operands i.e. simply the name of the executable such as:
				lab3_1234567.exe

				the program MUST print student ID string in Comma Separated Values (CSV)
				format, Testple:
					"studentNumber,student_email,student_name"
				eg: "1234567,s1234567@student.rmit.edu.au,FirstName_LastName"
				There are three fields in CSV strings: student number, email, name.
				You need to output all THREE, separated by commas.

	If the number of parameters is 2-3: the second parameter can only be 'B', 'R', 'Y' or 'G'. For any other letter, the output shall be 'I' which signals an input parameter
	error and then exit.

	If a number is not entered as the third parameter as required for all commands but 'B', the output shall be 'N' which signals a numerical parameter error and then exit.

	That is, following the program name, the command line can take two or three parameters only:
					ProgramName.exe  Operand1 Operand2
					Testples:
						lab3_1234567.exe B 128
						lab3_1234567.exe B
						lab3_1234567.exe R 16
						lab3_1234567.exe Y 5
						lab3_1234567.exe G 21

	If the number of parameters is 4 or more: the output shall be 'P' which signals a parameter error and then exit.


	ERROR CHECK 2:   VALID NUMBER RANGE
	If the number entered as the third parameter on the command line is not within an accepted range or they are not numerical characters, then the  output shall be 'Y' and then exit. The accepted number ranges are:
	- 'B' command: the number entered must be between 0 and 255 (inclusive)
	- 'R', 'Y' or 'G' commands: the number entered must be between 0 and 50 (inclusive)


	ERROR CHECK 3:   ANYTHING ELSE THAT CAN GO WRONG (MURPHY'S LAW TEST)
	If there are any other kinds of errors not covered here, the output shall be 'Z'. That is:  anything else that can possibly go wrong and has not be explicitly tested for
	or covered under the tests above, for Testple:
	- no connection,                 (This will not be tested for by the auto-tester)
	- disconnection during operation (This will not be tested for by the auto-tester)
	- HW dead.
	- ???? anything else Murphy can dream up.
	- everything that has not been covered elsewhere is Murphy's domain.

	Note: The OUSB.exe will give a message "Fatal Exception" if the board is not connected or is disconnected during normal operation. This message should NOT be returned by
	your code. The only output your code should give is the single character: 'Z'

	However: Murphy's laws are hard to test for. Very hard to test for with autotester.

	Suggestion: only worry about this test if you have clearly covered ALL preceding tests !

	Common error: Zero and the capital letter 'O' may look the same/similar but are not the same in ASCII.

	ERROR CHECKING: The basic programming rules are simple (as covered in lectures):
	1) check that the input is valid.
	2) check that the output is valid.
	3) if any library function returns an error code USE IT !!! CHECK FOR IT !!! If that means more than 50% of your code is error checking, then that's the way it has to be.


	GENERAL REQUIREMENTS & INFORMATION
	  * This program must be in one file named lab3_1234567.cpp where 1234567 is your
		student number.
		For Testple : lab3_1234567.cpp or lab3_3987654.cpp

	 * The format of the student id line is CSV (Comma Separated Variables) with NO SPACES-
		  student_id,student_email,student_name
		  When the program is run without any operands i.e. simply the name of the executable such as:
		  lab3_1234567.exe
		  the program MUST print student ID string in Comma Separated Values (CSV)
		  format, Testple:  - NO spaces are allowed
			"studentNumber,student_email,student_name"
		  eg: "1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

		REMEMBER: Do not include the 's' in front of the student number!

	  * A plagiarism detector will be used on all student code so don't bother copying.
		The end of semester Test will focus on laboratory work so copying is a stupid idea because you wont be able to do the Test.

	  * What string conversion routines do you know (string to number)?
		Look carefully as they will be needed to convert characters to a number and also check for errors.

	  * Your mark will result from testing your program against a whole range of inputs. The secret to getting a good mark is to carefully analyse all possible errors and odd
		situations BEFORE you write the code so read the proforma VERY carefully.  Ensure in each circumstance you can detect the error or condition and report the appropriate result.
		Hint: write test cases before you write any code.

	  * When text output is required you must generate EXACTLY that
		output and no other output.  For Testple-
		Specified output: "RX"    Actual program output: "rx"      Result: zero marks.
		Specified output: "RX"    Actual program output: "Got RX"  Result: zero marks.
		Specified output: "RX"    Actual program output: " RX"     Result: zero marks.

	  *	The following code is an Testple of the syntax required to open a pipe to the device.
		It may / may not include all of the necessary code to complete the task.

		//----Start of Testple standalone ccp file--------------------------------------------
		#include "stdafx.h"
		#include <iostream>
		using namespace std;
		int main(int argc, char* argv[])
		{
			char command[256] = {};
			strcpy_s(command, "ousb -r io PORTB 20"); // command to write 20 to OUSB board

			FILE *fpipe;
			char line[250] = {}; // size of Line should be smaller than command

			fpipe = (FILE*)_popen(command,"r");    // attempt to open pipe and execute a command
			if( fpipe != NULL )					   // check that the pipe opened correctly
			{
				while( fgets(line, sizeof(line), fpipe) )
				{   // do nothing here, or print out debug data
					cout << line; // print out OUSB data for debug purposes
				}
				_pclose(fpipe);   // close pipe
			}
			else cout << "Error, problems with pipe!\n";

			// do something with the value returned by the OUSB board, eg:
			unsigned short portb = (unsigned short)atoi(line); // convert from char array to unsigned short
			cout << "value = " << portb << endl;

			return 0;
		}
		//----End of Testple standalone ccp file----------------------------------------------
	*/

#include "pch.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> // keep it here, just in case.
#include <cmath> // keep it here, just in case.

	using namespace std; // Please do not remove this line

	// optional: your choice if you want to use these definitions for MAX-MIN-Range

class OUSB 			// Do not change class name
{
private:
	unsigned short PORTB;

public:
	int ReadPortB();
	void WritePortB(int val);

	// you may choose to implement operator overloaded funcitons for read and write functions for portb
	// void operator<<(const unsigned short &val); // write portb
	// void operator>>(unsigned short &val);       // read portb
};

int OUSB::ReadPortB()
{
	int portb = 0;
	char *command = "ousb -r io PORTB ";
	FILE *fpipe;
	char line[256];

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command    
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";
	portb = (int)atoi(line);
	return portb;


}

void OUSB::WritePortB(int val)
{
	char command[255] = { "ousb -r io PORTB " };
	char val_string[4] = {};
	_itoa_s(val, val_string, 10);
	strcat_s(command, val_string);
	FILE *fpipe;
	char line[256];

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command    
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";


}

// Traffic Light class
class TrafficLight // Do not change class name
{
private:
	bool redLamp;
	bool yellowLamp;
	bool greenLamp;
public:
	OUSB writefunction; // Interface functions
	TrafficLight() { redLamp = 0; yellowLamp = 0; greenLamp = 0; } // Constructor

	void redOn()
	{
		redLamp = 1; yellowLamp = 0; greenLamp = 0;
		writefunction.WritePortB(1);
	}

	void yellowOn()
	{
		redLamp = 0; yellowLamp = 1; greenLamp = 0;
		writefunction.WritePortB(3);
	}

	void greenOn()
	{
		redLamp = 0; yellowLamp = 0; greenLamp = 1;
		writefunction.WritePortB(2);
	}
	void changeTrafficLightState()
	{
		if (redLamp == 1)
		{
			greenOn();
		}
		else if (yellowLamp == 1)
		{
			redOn();
		}
		else if (greenLamp == 1)
		{
			yellowOn();
		}
	}

	bool isREDon() // Accessor function 
	{
		if (redLamp == 1)
		{
			return true;
		}
		else return false;
	}

	bool isYELLOWon() // Accessor function 
	{
		if (yellowLamp == 1)
		{
			return true;
		}
		else return false;
	}

	bool isGREENon() // Accessor function 
	{
		if (greenLamp == 1)
		{
			return true;
		}
		else return false;
	}


};

int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		// no parameters on command line just the program name
		//---  edit string below: eg: "studentNumber,student_email,student_name"

		cout << "3601377,s3601377@student.rmit.edu.au, Kevin_Totikidis" << endl;

		//--- When run with just the program name, meaning without parameters
		// your code  MUST print student ID string in CSV format.
		// i.e. simply running "lab1_1234567.exe
		// the output MUST print student ID string in Comman Separated Version (CSV)
		// format, such as:                  (NOTE the two commas !)
		//          "studentNumber,student_email,student_name"
		//      eg: "1234567,s1234567@student.rmit.edu.au,Tara-Louise_Brown"


		return(0); 	// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will 
		// assume you have made some major error.  Leave it as zero.
	}


	//--- START YOUR CODE HERE.
	if (argc == 2)
	{
		if ((string)argv[1] == "B")
		{
			OUSB readfunction;
			cout << readfunction.ReadPortB() << endl;
		}
		if ((string)argv[1] == "R" || (string)argv[1] == "Y" || (string)argv[1] == "G")
		{
			cout << "N" << endl;
			return 0;
		}
		if ((string)argv[1] != "B" && (string)argv[1] != "R" && (string)argv[1] != "Y" && (string)argv[1] != "G")
		{
			cout << "I" << endl;
			return 0;
		}
		return 0;
	}

	if (argc == 3)
	{
		if ((string)argv[1] != "B" && (string)argv[1] != "R" && (string)argv[1] != "Y" && (string)argv[1] != "G")
		{
			cout << "I" << endl;
			return 0;
		}
		if ((string)argv[1] == "B")
		{
			OUSB readfunction;
			OUSB writefunction;
			int argv2 = 0;
			argv2 = atoi(argv[2]);
			if (argv2 >= 0 && argv2 <= 255)
			{
				writefunction.WritePortB(argv2);
				cout << readfunction.ReadPortB() << endl;
			}
			else cout << "Y" << endl;
			return 0;
		}

		TrafficLight TFL;
		{
			int argv2 = 0;
			argv2 = atoi(argv[2]);
			if (argv2 < 0 || argv2 > 50)
			{
				cout << "Y" << endl;
				return 0;
			}
			if (isalpha(*argv[2]))
			{
				cout << "Y" << endl;
				return 0;
			}
			else
			{
				if ((string)argv[1] == "R")
				{
					TFL.redOn();
				}
				else if ((string)argv[1] == "Y")
				{
					TFL.yellowOn();
				}
				else if ((string)argv[1] == "G")
				{
					TFL.greenOn();
				}
				else cout << "I" << endl;

				int i = 0;
				for (i = atoi(argv[2]); i > 0; i--)
				{
					TFL.changeTrafficLightState();
				}

				if (TFL.isREDon())
				{
					cout << "1" << endl;
				}
				if (TFL.isYELLOWon())
				{
					cout << "3" << endl;
				}
				if (TFL.isGREENon())
				{
					cout << "2" << endl;
				}
			}
		}
	}
	else cout << "P" << endl;

	return(0); 	// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will 
			// assume you have made some major error. Leave it as zero.
}

// do NOT put any functions after this closing bracket, if you use functions add them before main


// End of File




#include "pch.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> // keep it here, just in case.
#include <cmath> // keep it here, just in case.

	using namespace std; // Please do not remove this line

	// optional: your choice if you want to use these definitions for MAX-MIN-Range

class OUSB 			// Do not change class name
{
private:
	//unsigned short PORTA;
	int PORTB;
	//unsigned short PORTC;

public:
	OUSB();  // Remember to define this else it won't compile
	int ousbcommand(string *str);
	int readPORTB() { string read = "ousb -r io portb"; PORTB = ousbcommand(&read); return(PORTB); };
	int writePORTB(string newValue) { string write = "ousb -r io portb"; write.append(newValue); PORTB = ousbcommand(&write); return(PORTB); };

	// you may choose to implement operator overloaded funcitons for read and write functions for portb
	// void operator<<(const unsigned short &val); // write portb
	// void operator>>(unsigned short &val);       // read portb
};
OUSB::OUSB()
{

}
int OUSB::ousbcommand(string *str)
{
	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(str->c_str(), "r");    // attempt to open pipe and execute a command    
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << line; // print out OUSB data for debug purposes
			if (line[0] == 'F')
			{
				cout << "Z" << endl;
				exit(0);
			}
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// do something with the value returned by the OUSB board, eg:
	int portb = atoi(line); // convert from char array to unsigned short
	//cout << "value = " << portb << endl;

	return (portb);
}

// Traffic Light class
class TrafficLight // Do not change class name
{
private:
	bool red;
	bool yellow;
	bool green;
public: // Interface functions
	OUSB ousb;
	TrafficLight(); // Constructor
	void state(char state);

	void setr() { string setLight = "ousb -r io portb 1"; ousb.ousbcommand(&setLight); };
	bool ron() { return(red = true); }; // Accessor function	

	void sety() { string setLight = "ousb -r io portb 3"; ousb.ousbcommand(&setLight); };
	bool yon() { return(yellow = true); }; // Accessor function

	void setg() { string setLight = "ousb -r io portb 2"; ousb.ousbcommand(&setLight); };
	bool gon() { return(green = true); }; // Accessor function

	void changestate();
};
TrafficLight::TrafficLight()
{

}
void TrafficLight::state(char state)
{
	red = false;
	green = false;
	yellow = false;
	switch (state)
	{
	case 'R':
		setr();
		ron();
		Sleep(1000);
		break;
	case 'G':
		setg();
		gon();
		Sleep(1000);
		break;
	case 'Y':
		sety();
		yon();
		Sleep(1000);
		break;

	}
}
void TrafficLight::changestate()
{
	for (int i = 0; i < 1; i++)
	{
		if (red)
		{
			red = false;
			setg();
			gon();
			Sleep(1000);
			break;
		}
		if (green)
		{
			green = false;
			sety();
			yon();
			Sleep(1000);
			break;
		}
		if (yellow)
		{
			yellow = false;
			setr();
			ron();
			Sleep(1000);
			break;
		}
	}
}

int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		// no parameters on command line just the program name
		//---  edit string below: eg: "studentNumber,student_email,student_name"

		cout << "3553647,s3553647@student.rmit.edu.au,Wen_Xuan_Lee" << endl;

		//--- When run with just the program name, meaning without parameters
		// your code  MUST print student ID string in CSV format.
		// i.e. simply running "lab1_1234567.exe
		// the output MUST print student ID string in Comman Separated Version (CSV)
		// format, such as:                  (NOTE the two commas !)
		//          "studentNumber,student_email,student_name"
		//      eg: "1234567,s1234567@student.rmit.edu.au,Tara-Louise_Brown"


		return(0); 	// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will 
		// assume you have made some major error.  Leave it as zero.
	}


	//--- START YOUR CODE HERE.
	if (argc >= 4)
	{
		cout << "P" << endl;
		return(0);
	}
	if (!(argv[1][0] == 'B' || argv[1][0] == 'Y' || argv[1][0] == 'G' || argv[1][0] == 'R'))
	{
		cout << "I" << endl;
		return(0);
	}
	if (argv[1][1] != NULL)
	{
		cout << "I" << endl;
		return(0);
	}
	if (argc == 2)
	{
		if (argv[1][0] != 'B')
		{
			cout << "N" << endl;
			return(0);
		}
		OUSB read;
		int value = read.readPORTB();
		cout << value << endl;
	}
	if (argc == 3)
	{
		for (int i = 0; argv[2][i] != NULL; i++)
		{
			if (isalpha(argv[2][i]))
			{
				cout << "Y" << endl;
				return(0);
			}
		}
		int N = atoi(argv[2]);
		if (argv[1][0] == 'B')
		{
			if (N > 255 || N < 0)
			{
				cout << "Y" << endl;
				return(0);
			}
			OUSB write;
			int value = write.writePORTB(argv[2]);
			cout << value << endl;
		}
		if (argv[1][0] != 'B')
		{
			if (N > 50 || N < 0)
			{
				cout << "Y" << endl;
				return(0);
			}
			char L = argv[1][0];
			TrafficLight set;
			set.state(L);
			for (int i = 0; i < N; i++)
			{
				set.changestate();
			}
			OUSB read;
			int value = read.readPORTB();
			cout << value << endl;
		}

	}


	return(0); 	// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will 
			// assume you have made some major error. Leave it as zero.
}

// do NOT put any functions after this closing bracket, if you use functions add them before main


// End of File
