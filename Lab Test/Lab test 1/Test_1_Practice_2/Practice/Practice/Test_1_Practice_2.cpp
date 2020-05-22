/*==============  Proforma : EEET2250 Lab Test 1 File I/O and Bitwise Operations with OUSB ============


File version: 2019_v01.0

GOAL:
To write a C++ Win32 Console Application in Visual Studio that reads data from file, and writes this
data out to PORTB using bitwise operations. When writing data to PORTB, the current state of the top 4
bits of PORTB (PB4-PB7) must be maintained. The program should perform error checking inline with the
SPECIFICATIONS Section. You final program should take command line argument via argv[] array, reads data
from the designated text file and print out a well defined result to the console or display a value to
PORTB on the OUSB Board, and nothing else. No additional keyboard user input should be required for the
process.

Use debug mode and a breakpoint at the return statement prior to program finish in main. Do NOT use
system("Pause"), cin, or getchar(), while(1), etc. type statements in your final solution!

RESOURCES:
During this Lab test you will have access to 2 PDF resources. The autotester will open up the following
PDF files:
		1. "Teach Yourself C++ in 21 Days" PDF ebook
		2. "Open-USB-IO Reference, version 1.13" PDF file

Both these PDF files can be found on the EEET2250 Canvas Shell. WARNING: Please make sure that during
the lab test you do not close the PDF files as you will NOT be able to open them again!

BACKGROUND:
This file is a proforma for the EEET2250 Lab Test 1: File I/O and bitwise operations with the OUSB board.
This file defines the assignment - there is no other documentation. You the student must extend this C++
program to cope with the functionality identified below in the SPECIFICATIONS Section.

During the lab sessions you will be given OUSB boards to practice on. However you may also want to
purchase one for $70 from the Design Store by using the appropriate form.


Avoid losing 10% by follow the following 5 instructions:
1. Please rename your file NOW to lab1_1234567.cpp, where 1234567 is your student number.

2. Your filename MUST NEVER EVER contain any spaces.  _under_score_is_Fine.

3. DO NOT include the 's' in front of your student number.

4. You MUST run this file as part of a Project.

5. DO NOT use system wide pre-defined variables because systems differ and what is defined in your system
may not be be defined in another system.

___________________________________________________________________________________________
___ GENERAL SPECIFICATIONS (common to all three EEET2250 Laboratory Tests):

G1.	You must rename your file to lab_1234567.cpp, where 1234567 is your student number.
Your filename MUST NEVER EVER contain any spaces. _under_score_is_Fine.
You do not need to include the 's' in front of your student number.

G2.	Edit the name/email address string in the main() function to your student number,
student email and student name.	The format of the student ID line is CSV (Comma Separated
Variables) with NO SPACES-
student_id,student_email,student_name
When the program is run without any operands i.e. simply the name of the executable such as:
lab3_1234567.exe
the program MUST print student ID string in Comma Separated Values (CSV) format with no
spaces. For example the following text should be outputted to the console updated with
your student details:
"1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

G3.	All outputs are a binary representation of an integer or a single character error
indicator followed by a linefeed ( endl or \n).

G4.	DO NOT add more than what is specified. Do NOT add additional information, text or
comments to the output console.

G5.	DO NOT use 'cin', system("pause"), getchar(), gets(), etc. type functions. Do NOT ask
for user input.

G6. All input MUST be specified on the command line separated by blank spaces (i.e. use
the argv and argc input parameters). All input and output is case sensitive.

G7.	You should use the Integrated Debugging Environment (IDE) to change input arguments during
the development process. During the lab tests, the command line window (i.e. cmd command) will
not be available. However you will be able to compile and run your code during the lab test
session and used the Visual studio command line debugging dialog box.

G8.	When your code exits the 'main()' function using the 'return' command, you MUST
use zero as the return value. This requirement is for exiting the 'main()' function ONLY.
A return value other than zero will indicate that something went wrong to the autotester and
no marks will be awarded.

G9.	Do NOT put any functions or class declarations AFTER the 'main()' function - if you write
your own functions, add them BEFORE the 'main()' function. This is a requirement of the
Autotester and failure to do so will result in the Autotester not compiling your code correctly
and loss of marks, even though the code will compile during the lab test session. Hence any
user-defined functions to read and write to the OUSB board must be written before the 'main()'
function.

G10. You MUST run this file as part of a Project - No other *.cpp files or *.h files should be
added to your solution. The OUSB.exe file will be provided as part of the project.

G11. You are not permitted to add any other #includes statements to your solution. The only
libraries permitted to be used are the ones predefined in this file.

G12. If an error (as per the definition in this specification) occurs, then the value on
the OUSB LEDs must not to be updated.

G13. All numerical values read from / written to the OUSB Board are considered to be unsigned
and are between 0 and 255 (inclusive).

G14. Any binary numbers within this document have the prefix 0b. This notation is not C++
compliant, however is used to avoid confusion between decimal, hexadecimal and binary
number formats within the description and specification provided in this document. For
example the number 10 in decimal could be written as 0xA in hexadecimal or 0b1010 in binary.
It can equally be written with leading zeroes such as: 0x0A or 0b00001010. For output
to the console screen you should only ever display the numerical characters only and omit
the 0x or 0b prefixes.

G15. Do NOT attempt to read/write to any other OUSB Board IO port other than PORTB 0-7, PINC 0-7,
ADC pins 0 through to 6 and the PWM pin 1 (on port D). Other pins on the OUSB board are
reserved for the autotester, rs-232 port and the USB interface back to the computer.
______________________________________________________________________________________________________________

SPECIFICATIONS:
Your program must read in data from a text file, where the filename is entered as a parameter on the command
line (filename entered on the command line must include the file extension i.e., do not assume a file extension
in your code). YOUR CODE WILL BE TESTED WITH MULTIPLE INPUT TEXT FILES, so do not hard-code the filename into
your solution!!! Valid data read from the file should be written out to PORTB, maintaining the current state of
the top four bits of PORTB (PB4-PB7). The file contains one data value per line (numbers from 0-15
inclusive i.e., only using the bottom four bits of PORTB), and your program must continue reading in each
line of data and writing valid data to PORTB until the end of the file is reached.

The numerical data from the file should be within the range of 0-15 i.e., only the bottom four bits of PORTB
should be changed. Your code will need to perform error checking to ensure that numbers outside of the
accepted range of 0-15 are not sent to PORTB.

The top four bits of PORTB (PB4-PB7) must not be changed when you write data to PORTB - use bitwise
operations to do this.

Hint: 	- you can use a bitwise AND (to read the important bits of PORTB) then bitwise OR (to set the new
		  bits on PORTB).

Your program MUST use pipes to communicate with the OUSB board, system calls are NOT allowed:
Example of system calls which are NOT allowed: system("ousb -r io portb 127");

System calls take longer and automatically echo the result to the command shell window. If you use system
calls in your code it is likely the code will not meet the required specifications and you will most likely
lose all marks for this lab. Therefore, you MUST write code using pipes to access the OUSB.exe
functionality. See the code fragments given to you and explained in lectures and on Blackboard.

For every '_popen(command,"r"); ' call you MUST close the pipe using '_pclose(<pipename>); '. Otherwise you
program is likely to suffer from a memory leak and your program might not be able to run correctly when the
autotester executes it 100's of times over.

Before exiting your program you can call '_pclose(<pipename>); ' one last time.

About pipes and _popen (these links will not work during the actual lab test session):
http://www.cplusplus.com/forum/windows/1341/
http://www.cplusplus.com/forum/windows/10766/

------------------------------

OUSB OUTPUT FORMATS: AS FOR A COMMAND SHELL WINDOW.

The OUSB board outputs commands sent to it in a default format. You will be required to change the
default setting. Example: if the command given is: "ousb.exe io portb 128"  The DEFAULT response
from the OUSB board will be: PORTB = 128   This is NOT what you code should produce.

If the specifications state that you are to display the returned value from the OUSB Board, which for
example is 128, then your code should display ONLY the number 128, not: PORTB = 128
The method of how to make the OUSB board respond with just the number as output can easily be found
out by prior to the lab test by following these steps:
1) opening a command window in Windows: START -> RUN -> "cmd"  (note: don't do this during the lab test)
2) typing 'ousb' on the command line. This will bring up a help menu
3) see the option for 'raw (decimal)' output.
NOTE: you will not be able to do this during the actual Lab test as you will only be able to communicate
to the OUSB board during the lab test via visual studio. Rather, do this during the lab sessions.

If you use _popen() and a file pipe, do not add EXTRA newlines, do not add extra blank
spaces or any other characters. Output must be as it would be for a standard command line window.

The only text in the command shell window should be:
- text returned from the OUSB board in response to your code or an error condition
- NO debug code should appear in the command shell window. This means: any of your debug comments
  must be turned off for the final submitted copy.

------------------------------

ERRORS:
Error checking is a big part of software development. You cannot always expect a user to use your program
as you intended. Therefore you should implement the following ERROR CHECKS in your solution.

	Hint: -	Implement the error checks in the order they appear below as each check is harder to implement
			than the previous one.
		  - The following text lists errors you must detect and a priority of testing.  NB: order of testing
			is important.

All outputs are a single character followed by a newline ( endl or \n). DO NOT add more than what is specified,
do NOT add additional information, simply and only the output as required. DO NOT use 'cin', do NOT ask for user
input. This includes system("pause") or getchar(), etc. function calls. All input MUST be read in from the command line
arguments and/or from file only.

The closing } of the main statement must be the last closing brace in the file. The last line containing
"main()" must be the main statement where execution is started. In other words: ALL your functions MUST be
between the start of the file and the int main(int argc, char *argv[]) function. Do NOT put any functions
after the main function, if you use functions add them BEFORE the 'main' function.

You are NOT permitted to add any additional C/C++ include libraries other than the ones defined in this file!

You should use the Integrated debugging environment. In the lab tests the command line window will not
be available.

When your code exits the 'main()' function using the 'return' command then you MUST use zero as the return
value. This requirement is for exiting the 'main()' function ONLY. Anything other than return 0, will indicate
to the autotester that an error occurred during the testing process of your code and you will receive no
marks for that test.

Common error: Zero and the capital letter 'O' may look the same/similar but are not the same in ASCII.

The basic programming rules of error checking are simple:
1) check that the input is valid.
2) check that the output is valid.
3) if any library function returns an error code USE IT !!! CHECK FOR IT !!! If that means more than 70%
   of your code is error checking, then that's the way it has to be.


ERROR CHECK 1:   NUMBER OF PARAMETERS
NB: the name of the program counts as the 1st parameter (0th value in the array).

If the number of parameters is 1 then the program MUST print student ID string in CSV format as explained
above and then exit. This should be the first thing you do before starting to tackle the problem.

If the number of parameters is 2, the second parameter is taken to be the filename.

If the number of parameters is 3 or more, the output shall be 'P' which signals a parameter error and
then exit.

When the program is run without any operands i.e. simply the name of the executable such as:
			lab1_1234567.exe

			the program MUST print student ID string in Comma Separated Values (CSV)
			format, example:
				"studentNumber,student_email,student_name"
			eg: "1234567,s1234567@student.rmit.edu.au,FirstName_LastName"
			There are three fields in CSV string, student number, email, name.
			You need to enter all THREE, separated by commas.

			Following the program name, the command line can take one parameter only
			(i.e. one argument only)
				ProgramName.exe  Operand1
				Example:
					lab1_1234567.exe    myFile.txt

ERROR CHECK 2:   VALID FILE
If the file cannot be opened using parameter 2 from the command line (which should be the filename), the
output shall be 'F' and the program should exit.

ERROR CHECK 3:   VALID NUMBER RANGE
If the data read from file contains a number beyond the range accepted by the bottom four bits of PORTB
(i.e., 0-15, inclusive), the output shall be 'Y'. The program should not write this data to PORTB but
should continue operating i.e., keep reading in data from the next line and writing data to PORTB.

Examples of valid number input: 6 0 15 9 12
Examples of invalid number input: 16 -4 8.54 8v +6 127 b u7

ERROR CHECK 4:   ANYTHING ELSE THAT CAN GO WRONG (MURPHY'S LAW TEST)
If there are any other kinds of errors not covered here, the output shall be 'Z'. That is:  anything else
that can possibly go wrong and has not be explicitly tested for or covered under the tests above,
for example:
- no connection,
- disconnection during operation
- HW dead.
- ???? anything else Murphy can dream up.
- everything that has not been covered elsewhere is Murphy's domain.

Note: The OUSB.exe will give a message "Fatal Exception" if the board is not connected or is disconnected
during normal operation. This message should NOT be returned by your code. The only output your code
should give is the single character: 'Z'

However, Murphy's laws are hard to test for. Very hard to test for with autotester.
Suggestion: only worry about this test if you have clearly covered ALL preceding tests!



GENERAL REQUIREMENTS & INFORMATION
 * This program must be in one file named lab1_1234567.cpp where 1234567 is your student number.
   For example : lab1_1234567.cpp or lab1_3987654.cpp

 * The format of the student id line is CSV (Comma Separated Variables) with NO SPACES:
	  student_id,student_email,student_name
	  When the program is run without any operands i.e. simply the name of the executable such as:
	  lab1_1234567.exe
	  the program MUST print student ID string in Comma Separated Values (CSV)
	  format, example:  - NO spaces are allowed
		"studentNumber,student_email,student_name"
	  eg: "1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

	REMEMBER: please do not include the 's' in front of the student number!

 *  A plagiarism detector will be used on all student code so don't bother copying. The end of semester
	exam will focus on laboratory work so copying is a stupid idea because you wont be able to do the exam.

 *  What string conversion routines do you know (string to number)? Look carefully as they will be needed
	to convert characters to a number and also check for errors.

 *  Marking will result from testing your program against a whole range of inputs. The secret to getting a
	good mark is to carefully analyse all possible errors and odd situations BEFORE you write the code so
	read the project definition VERY carefully.  Ensure in each circumstance you can detect the error or
	condition and report the appropriate result.  Hint: write test cases before you write any code.

 *  When text output is required you must generate EXACTLY that output and no other output. For example-
	Specified output: "RX"    Actual program output: "rx"      Result: zero marks.
	Specified output: "RX"    Actual program output: "Got RX"  Result: zero marks.
	Specified output: "RX"    Actual program output: " RX"     Result: zero marks.

 *	The following code is an example of the syntax required to open a pipe to the device.
	It may / may not include all of the necessary code to complete the task.

//----Start of template standalone .cpp file--------------------------------------------
	#include "pch.h"
	#include <iostream>
	#define Debug 1
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
				if (Debug) cout << line; // print out OUSB data for debug purposes
			}
			_pclose(fpipe);   // close pipe
		}
		else cout << "Error, problems with pipe!\n";

		// do something with the value returned by the OUSB board, eg:
		unsigned short portb = (unsigned short)atoi(line); // convert from char array to unsigned short
		cout << "value = " << portb << endl;

		return 0;
	}
//----End of template standalone .cpp file----------------------------------------------
____________________________________________________________________________________________
*/
// These are the libraries you are allowed to use to write your solution. Do not add any
// additional libraries as the auto-tester will be locked down to the following:
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
	strcpy_s(command, "ousb -r io PORTB ");
	char line[250] = {}; // size of Line should be smaller than command
	char val_string[4] = {};
	FILE *fpipe;
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

int ReadPortB()
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB ");
	char line[250] = {}; // size of Line should be smaller than command
	char val_string[4] = {};
	FILE *fpipe;

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				_pclose(fpipe);
				return 1000;
			}
		}
		_pclose(fpipe);   // close pipe
	}
	unsigned short portb = (unsigned short)atoi(line);
	return portb;
}

bool validarg(string line)
{
	bool current = true;
	for (int i = 0; i < line.length(); i++)
	{
		if (isdigit(line[i]))
		{
			current = true;
		}
		else
		{
			return false;
		}
	}
	return current;
}

bool checkrange(int val)
{
	if (val >= 0 & val <= 15)
	{

		return true;
	}
	else
	{
		return false;
	}
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
		int oldportbval = ReadPortB();
		if (oldportbval == 1000)
		{
			cout << "Z" << endl; //ousb connection
			return 0;
		}
		else
		{

		}


		ifstream infile(argv[1]);
		if (infile)
		{
			while (!infile.eof())
			{
				string line; 
				getline(infile, line);
				if (line.length() == 0)
				{
					//empty input means skip
				}
				else if (validarg(line))
				{
					int val;
					val = stoi(line);
					if (checkrange(val))
					{
						int newportbval = oldportbval & 240;
						newportbval |= val;
						WritePortB(newportbval);
					}
					else
					{
						cout << "Y" << endl; //out of range
					}
				}
				else
				{
					cout << "Y" << endl; //invalid argument
				}
			}
		}
		else
		{
			cout << "F" << endl; // cant open file
			return 0;
		}

	}

	else
	{
		cout << "P" << endl; // too many argument
		return 0;
	}
	


		// The convention is to return Zero to signal NO ERRORS, if you change it the AutoTester will
		//assume you have made some major error.  Leave it as zero.
	return 0;
}
// do NOT put any functions after this closing bracket, if you use functions add them before main()
// End of File  - DO NOT Modify this line or anything below this line


