/*========  Proforma : DC Motor Control ===================================

File version: 	2019_v01.0

Last updated:	27-03-2019

PURPOSE     This file is a proforma for the DC Motor Lab Test and it is the
			only document which states the requirements you must achieve.
			You must extend this C++ program to cope with the functionality
			identified below.

GOAL        To write a C++ Win32 Console Application in Visual Studio that
			controls a DC Motor (or circuit that simulates a DC motor).
			You will go through 4 distinct steps to achieve speed control of
			a small DC motor using Pulse Width Modulation. The first 3 steps
			do not need a DC motor and will get you 100% for this lab test.

			The final step is a 3% bonus mark component. The bonus component
			requires you to provide a DC plug pack power supply, your own
			OUSB board and a small DC motor. The bonus marks can be used to
			offset any marks lost for the laboratory component of EEET2250
			capped at the maximum available mark for laboratory component,
			which is 36% of total course mark.

RESOURCES	During this Lab test you will have access to the following PDF
			resources as the autotester will open up with Visual Studio:
				1. "Teach Yourself C++ in 21 Days" PDF ebook
				2. "Open-USB-IO Reference, version 1.13" PDF file
			These PDF files can be found on the EEET2250 Canvas Shell.

			WARNING: Please make sure that during the lab test you do not
			close the PDF files as you will not be able to open them again!

MARKING     Marking has several components-
			  - commands P, A, and L will be tested using the auto-tester.
			  - command M will be marked by the tutor during the lab test
				session after the P, A and L solution has been submitted to
				the autotester.
			  - any time after the lab test you may be asked to
				explain the code you wrote in that lab test.  If you cannot
				make a good explanation of the code then your mark will be
				adjusted downward, to zero if you cannot explain anything.
				This will be done at random and students may face from zero
				to four "explain" tests.
			  - The autotester will not test for the M command, so you are
				free to submit a solution containing code for the M command.


SCHEMATIC FOR COMMANDS P, A and L
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following circuitry has been already added to a standard Open-USB-IO board.

Your C++ Program     OUSB      .  Components Soldered onto Prototype Area
on the PC            Board     .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							   .
ousb J5 pin 37/39 -->----------.->--+
							   .    |
							   .   |"| 1kohm load
Create a square wave           .   |_|
 ousb pwm 1 ...                .    |      47 kohm
   |"|___|"|___| -->-- J5 -----.->--+---[\\\]---+
						pin 27 .                |
							   .        +-------+----+
Read the ADC                   .        |       |    | +
 ousb adc 0 ...  ---<-- J5 ----.-<------+      |"|  ===  10 uF
						pin 1  .          22   |_|   |
							   .          kohm  |    |
							   .                +----+-- J5 any even pin, 0v
							   .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This circuit is a simple control loop.
  * The ousb board uses the PWM command to generate a square wave on
	pin PB3 of the microprocessor,  which is connected to the LED3 (on PORTB),
	and to the inverting buffer which outputs on connector J5 pin 27.
	The command "ousb pwm-freq 1 ..." sets the frequency.
	The command "ousb pwm 1 ..." sets the duty cycle.
	Details can be found in chapter 6 of the Open-USB-IO manual.

  * When the PWM output goes high, LED3 is turned on and pin 27 of J5
	goes low thus pulling current through the load resistor (and later
	the motor). When the PWM output goes low then LED3 is turned off,
	and pin 27 of J5 acts as an open circuit thus no current flows
	through the load resistor. The PWM runs at 46 Hz so the human eye
	cannot see LED flicker. The average current delivered to the load
	is roughly-
	   full_power_current * PWM_fraction_on_time

  * The 47 kohm resistor and 22 kohm resistor form a voltage divider-
	 (Voltage on J5 pin 1) = (Voltage on J5 pin 27) * 22 / (22 + 47)
	The capacitor acts to smooth any voltage bumps from the square wave
	so J5 pin 1 sees a nice smooth voltage level, the resistors and
	capacitor thus form a low pass filter.

  * J5 pin 1 is connected to an analogue to digital converter on the board.
	This converts the voltage to a number,  0 means 0 volts, 1023 means
	+5v volts.

  * Your C++ program can act as a control loop which has the aim of getting
	the ADC read value to a desired target setting. Your code can set an
	initial PWM value, say 50%.  It can read the ADC value, if this does
	not match the target then the PWM duty cycle can be moved up or down
	1% at a time.  After several loops the ADC read value should be close
	to the target value.

___________________________________________________________________________________________
___ GENERAL SPECIFICATIONS (common to all three EEET2250 Laboratory Tests):

G1.	You must rename your file to lab2_1234567.cpp, where 1234567 is your student number.
Your filename MUST NEVER EVER contain any spaces. _under_score_is_Fine.
You do not need to include the 's' in front of your student number.

G2.	Edit the name/email address string in the main() function to your student number,
student email and student name.	The format of the student ID line is CSV (Comma Separated
Variables) with NO SPACES-
student_id,student_email,student_name
When the program is run without any operands i.e. simply the name of the executable such as:
lab2_1234567.exe
the program MUST print student ID string in Comma Separated Values (CSV) format with no
spaces. For example the following text should be outputted to the console updated with
your student details:
"1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

G3.	All outputs are a single error character or a numerical number, as specified by the
FUNCTIONAL SPECIFICATIONS, followed by a linefeed ( endl or \n).

G4.	DO NOT add more than what is specified. Do NOT add additional information, text or
comments to the output console.

G5.	DO NOT use 'cin', system("pause"), getchar(), gets(), etc. type functions. Do NOT ask
for user input from the keyboard.

G6. All input MUST be specified on the command line separated by blank spaces (i.e. use
the argc and argv[] input parameters). All input and output is case sensitive.

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

G12. If an error (as per the definition in the specification) occurs, then the value on
the OUSB LEDs must not to be updated.

G13. All numerical values read from / written to the OUSB Board are considered to be unsigned
and are between 0 and 255 (inclusive). You as the programmer must ensure that you construct
and send correctly formed OUSB commands to the OUSB board via a file pipe.

G14. Any binary numbers within this document have the prefix 0b. This notation is not C++
compliant, however is used to avoid confusion between decimal, hexadecimal and binary
number formats within the description and specification provided in this document. For
example the number 10 in decimal could be written as 0xA in hexadecimal or 0b1010 in binary.
It can equally be written with leading zeroes such as: 0x0A or 0b00001010. For output
to the console screen you should only ever display the numerical characters only and omit
the 0x or 0b prefixes.

G15. Do NOT attempt to read/write to any other OUSB Board IO port other than PORTB 0-7, PINC 0-7,
ADC pins 0 through to 6 and the PWM pin 1, 2 or 3 (on port D). Other pins on the OUSB board are
reserved for the autotester, rs-232 port and the USB interface back to the computer.
___________________________________________________________________________________________________

FUNCTIONAL SPECIFICATIONS:
SPECIFIC REQUIREMENTS FOR COMMANDS P, A , and L
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The P command just sets the PWM duty cycle,  the A command just reads the
analogue voltage on J5 pin 1.  The L command puts these two together to
form a control loop.

  * In general detect errors in the order they are listed below and respond
	as required.

  * Any number required in an output should be an integer
	unless otherwise stated.

  * The command line may have no parameters and the program will
	identify who you are. See the cout statement after main().
	If you make a mistake here your mark will be reduced by 10%.

  * If there is not exactly two parameters after the program name then
	the output shall be the single character 'P' then a newline.

  * The first parameter may be only one of the letters P, A, L or M.
	If it is anything else the output shall be the single character
	'I' then a newline.

  * The autotester will NOT test for the M command. This must be tested
	by the laboratory tutor after autotester submission.

  * The second parameter must be a number between 0 and 1023 inclusive.
	If there is an error the output shall be the single character
	'R' then a newline.

  * If the first parameter is P then take the second parameter
	as the duty cycle which must be between 0 and 100 inclusive.
	If there is a problem output the single letter 'r' then a newline.
	If there is not a problem send commands to the Open-USB-IO
	board to set the frequency to 46 Hz, and the duty cycle to
	the value defined by the second parameter, and then output
	the single letter 'p' and a newline.

  * If the first parameter is A then the second parameter should
	be an ADC channel number 0 to 7 inclusive.
	If this is wrong output 'a' then newline.
	If the ADC channel is OK then use the 'ousb adc' command to
	read the voltage and print the value to the output and a newline.

  * If the first parameter is L then the second parameter must be
	the target ADC read value that the control loop is trying to
	achieve. This command implements the control loop:
	  - Before the loop starts you must set the PWM frequency
		to 46 Hz.
	  - The loop shall have no more than 60 iterations for L command.
	  - On the first loop the PWM duty cycle must set to 50%.
	  - After setting the PWM duty cycle then you must read ADC 0.
		If the value read does not match the target value then
		the next PWM duty cycle may be set to +1 or -1 of
		its current value.
	  - The PWM duty cycle must remain between 0 and 100 inclusive.
	  - When your loop terminates you must print out the last
		PWM duty cycle you sent in the PWM command then a newline
		(just the number, no % symbol). Do not print out any other
		characters.
	  - Do not issue any more "ousb" commands when the loop terminates
		so the PWM is left working. The autotester will read the board
		to determine if your program has achievied the correct control
		value.
	  - Your code should not run for more than 60 seconds in total,
		therefore avoid using second long sleep statements inside
		the control loop. If you code does run for more than 60 seconds
		the autotester will terminate your code and mark that test
		with 0 (zero) marks.


SCHEMATIC FOR COMMAND M   -  Bonus marks component
~~~~~~~~~~~~~~~~~~~~~~~~~~
This part of the lab is for bonus marks component and uses a real DC motor and
power supply that you must provide with your own personal OUSB board. You
technically do not need to do this part of the lab as everything above is
enough to get 100% for this lab component (when combined with the
specifications above and below).


Your C++ Program     OUSB      .  Components Soldered onto Prototype Area
on the PC            Board     .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							   .
ousb J5 pin 37 ----->----------.->--+------------------+------------ (Ext DC Supply)
							   .    |                  |
							   .    |              .---+---.
							   .   |"| 1kohm       | motor |
							   .   |_|  load       '---+---'
							   .    |                  |
							   .    +------------------+
ousb pwm 1 ...                 .    |      47 kohm
   |"|___|"|___| -->-- J5 -----.->--+---[\\\]---+
						pin 27 .                |
							   .        +-------+----+
							   .        |       |    | +
ousb adc 0 ...    --<-- J5 ----.-<------+      |"|  ===  10 uF
						pin 1  .          22   |_|   |
							   .          kohm  |    |
							   .                +----+-- J5 any even pin, 0v
							   .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 * In this circuit the link to the onboard +5v is removed and DC plug
   pack is plugged into the board.  A small DC motor is put in parallel
   with the load resistor.

 * When the PWM on LED3 goes high pin 27 J5 goes low, current flow through
   the motor and drives it.

SPECIFIC REQUIREMENTS FOR COMMAND M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The M command is a control loop very much like the L command.

  * This part of the lab is for bonus marks and will be marked by the
	tutor in the lab test session.

  * The autotester will not test for the M command, so it would be wise
	to get previous commands fully working and submitted your solution
	before working on this part of the lab test.

  * You must supply the DC motor and an external DC plug pack and your
	own OUSB board to do this part of the test.

  *	The motor must be rated at no more than 500 mA even if stalled.
	The plug pack may be up to 12 volts and may be the cheaper
	"unregulated" type. The plug pack must plug into the DC socket
	on the Open-USB-IO. If required, the pin jumpers need to be
	correctly installed.

  * It is allowed for students to share a DC plug pack and motor and OUSB
	board. Students in the same lab session are strongly advised to have
	their own equipment and for it to be ready to use in the lab without
	any major setting up or wiring.

  * The M command is much like the L command but the loop runs forever
	until control-C is pushed from the keyboard. Start creating the
	code with a cut and paste of the L command, as there are only a
	few changes that need to be made.  The Autotester will NOT test
	the M command! M command must be tested in the lab with your tutor
	within the specified time limit.

  * At the end of each loop you shall print the line-
	  Target ADC0= zzzz,  Actual ADC0= yyyy,  Next PWM%= xxx
	Where zzz,yyyy, and xxx are numbers.

  * Work out the maximum and minimum values the ADC will see.
	Given your program name is named myProgram.exe try-
	  myProgram.exe P 100  // motor at full.
	  myProgram.exe A 0    // read ADC value.
	  myProgram.exe P 0    // motor stopped.
	  myProgram.exe A 0    // read ADC value.

  * Take the average of the two ADC readings to provide a good ADC
	target value and start your program-
	  myProgram.exe M average_value
	After the speed settles write down the PWM value.
	Now put your finger on the motor spindle to slow it down.
	Note the PWM duty cycle go up.
	Remove your finger and note the PWM value go down again.
	Hit ctrl-C to stop your program.

  * Now set the motor going using the PWM value noted above.
	  myProgram.exe P PWM_value
	Now apply you finger to the spindle and note that it
	slows down much more than when using your M command.

  * What does the tutor want to see to mark you?
	The two points above.
	The tutor will note if it worked or did not work.

  * If you get this far congratulations you have achieved basic
	speed control of a DC motor!


HELPFUL HINTS
~~~~~~~~~~~~~~~
  * If the motor is left going after a command and is annoying just
	hit the reset switch on the microprocessor to stop it.

  * To thoroughly test your program hit the reset switch on
	Open-USB-IO then run your program.  This will ensure you
	have initialized the board properly.  Ignore the usual
	error message the first time Open-USB-IO is accessed after a
	reset.

  * Debugging the L command could be difficult and it is strongly
	suggested that during the development of your code you print
	out a line of information at the end of the loop-
	  Loop# ww,  ADC target= xx,  ADC read yy,  Next PWM zz
	where ww,xx,yy and zz are numbers.
	Make sure you remove or comment out this code before submitting!

  * If your loop saturates the PWM at 0% or 100% try swapping the
	sign when you do a +- 1% change to the PWM.
	Also try changing the target value.  See the M command for
	choosing a workable target for the ADC read value.
	Note how to work out the range of achievable ADC values
	described above.

  * The Lab test 2 proforma (i.e., this file) and the following code to
	interface with the OUSB board will be provided in the Lab test.


EXTENSION WORK AND THOUGHTS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Read this section if you are interested in motor control.

  * DC motors with permanent magnet fields turn into generators when
	the power is removed and they are still moving.
	With a 46 Hz PWM the off period is small and the motor
	doesn't slow down and so it becomes a generator.

  * Brushed DC motors in motor mode, and especially in generator
	mode, create lots of electrical noise on the power supply.
	If the motor runs from the same supply at the microprocessor
	then the microprocessor could suffer a glitch and crash.

  * If you have used SPICE, try simulating the 2 resistors and
	capacitor to see how the PWM square wave is turned into
	a smooth waveform.

  * The M command uses the voltage on J5 pin 1 as a measure of speed.
	A better measure is the voltage across the motor during
	its off period when the motor is acting as a generator.
	If good speed control is desired this will give a better
	result.  Both methods are imperfect but give a useful level
	of speed control.
	Can you work out how to calculate the voltage across the
	motor in generator mode?  Can you code it?

  * The PWM drive pin used is PB3 but buffered by an Open-Collector
	transistor (Google this term).  The open collector acts like
	a switch and can be either a short to zero volts or an open circuit.
	The open collector used can cope with 500mA and up to 50 volts.
	Open-USB-IO has 7 of these can can be used to drive a variety of
	motors and other devices.

  * The voltage spikes from the motor could destroy the ADC input pin
	on the microprocessor if it were directly connected to it. The
	47 kohm resistor acts as a current limit, and the capacitor helps
	to smooth out the spikes into a small bump.

  * See the following web links to learn more-
	  http://en.wikipedia.org/wiki/Electric_motor
	  http://en.wikipedia.org/wiki/Brushed_DC_electric_motor
	  http://tldp.org/LDP/LGNET/179/radcliffe.html
	   ( Note the control loop in the article above will not
		 meet the requirements of this lab, do not use it.)



GENERAL INFORMATION AND HINTS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  * A plagiarism detector will be used on all student code so don't
	bother copying.
	The test will focus on project work so copying is a stupid idea
	because you wont be able to do the test.

  * Marking will result from testing your program against a whole
	range of inputs.  The secret to getting a good mark is to
	carefully analyse all possible errors and odd situations
	BEFORE you write the code so read the project definition VERY
	carefully.  Ensure in each circumstance you can detect
	the error or condition and report the appropriate result.

  * When text output is required you must generate EXACTLY that
	output and no other output.  For testple-
	 Specified output: "RX"    Actual program output: "rx"      Result: zero marks.
	 Specified output: "RX"    Actual program output: "Got RX"  Result: zero marks.
	 Specified output: "RX"    Actual program output: " RX"     Result: zero marks.


 *	The following code is an example of the syntax required to open a pipe to the OUSB device.
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

Copyright Dr. Pj Radcliffe 2011, modified by S Ippolito 2019
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

//set frequency
//writedutycycle
//readadc
//checkrange
//valiarg

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
		{   		}
		_pclose(fpipe); 
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
		_pclose(fpipe);
	}

	// do something with the value returned by the OUSB board, eg:
	int portvalue = (int)atoi(line); // convert from char array to unsigned short
	return portvalue;
}

bool checkrange(int num, string when)
{
	if (when == ":)" && num >= 0 && num <= 1023)
	{
		return true;
	}
	else if (when == "@P" && num >= 0 && num <= 100)
	{
		return true;
	}
	else if (when == "@A" && num >= 0 && num <= 7)
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

	//--- When no parameters MUST print id string in CSV format. 
	if (argc == 1)  // no parameters print this line.
	{
		cout << "3616240,s3616240@student.rmit.edu.au,Nikhshay_Singh_Kukreja" << endl;
		// Any errors in the line above,  or the naming of the file
		//  will result in 10% being deducted from your mark.
		return(0);
	}
	else if (argc == 3)
	{
		if ((argv[1][0] == 'P' || argv[1][0] == 'A' || argv[1][0] == 'L' || argv[1][0] == 'M') && argv[1][1] == '\0');
		else
		{
			cout << "I" << endl;
			return(0);
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
		if (checkrange(secondparameter, ":)"));
		else
		{
			cout << "R" << endl;
			return(0);
		}

		if (argv[1][0] == 'P')
		{
			if (checkrange(secondparameter, "@P"))
			{
				SetFrequency();
				WriteDutyCycle(secondparameter);
				cout << "p" << endl;
				return(0);
			}
			else
			{
				cout << "r" << endl;
				return(0);
			}
			
		}
		else if (argv[1][0] == 'A')
		{
			if (checkrange(secondparameter, "@A"))
			{
				int currentadc = ReadADC(secondparameter);
				cout << currentadc << endl;
				return(0);
			}
			else
			{
				cout << "a" << endl;
				return(0);
			}
		}
		else if (argv[1][0] == 'L')
		{
			SetFrequency();
			int currentpwm = 50;
			WriteDutyCycle(currentpwm);
			int currentadc = ReadADC(0);
			int targetadc = secondparameter;
			for (int i = 0; i < 60; i++)
			{
				if (targetadc > currentadc  && currentpwm > 0)
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
			SetFrequency();
			int currentpwm = 50;
			WriteDutyCycle(currentpwm);
			int currentadc = ReadADC(0);
			int targetadc = secondparameter;
			for (int i = 1; i > 0; i++)
			{
				cout << "Target ADC " << targetadc << " Current ADC " << currentadc << " Next PWM " << currentpwm << endl;
				if (targetadc > currentadc  && currentpwm > 0)
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
		else;
	}
	else
	{
		cout << "P" << endl;
		return(0);
	}
	//--- START YOUR CODE HERE.




	return(0); // The convention is to return Zero to signal NO ERRORS, if you change it 
			   // the AutoTester will assume you have made some major error.  
			   // Leave it as zero.
}
// do NOT put any functions/code after this closing bracket, if you use functions add them before main
// End of File


