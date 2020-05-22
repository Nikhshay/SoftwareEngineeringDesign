/*==============  Proforma : EEET2250 Lab Test 3 OUSB class and traffic light state machine ============
Proforma version number: 2019.001.b (updated 03-05-2019)

Document Revision Details:
version 2019.001.a (11-04-2019) - Original version
version 2019.001.b (03-05-2019) - G13 updated

PURPOSE:
This file is a proforma for the EEET2250 Lab Test 3: OUSB class and traffic light state machine operations
with the OUSB board. This file defines the assignment - there is no other documentation. You must extend
this C++ program to cope with the functionality identified below.

GOAL:
To write a C++ Win32 Console Application in Visual Studio that implements access to the OUSB board using
classes. Your program will implement a traffic light state machine class called TrafficLight as well as
an OUSB class. Failure to instantiate and use the OUSB and TrafficLight classes will result is a large
marks penalty. PORTB and PORTD of the OUSB board will be used to indicate the current traffic light state.
Text with very specific formatting will also be displayed to the console. The program should perform error
checking.

To put the problem into perceptive, the three LEDs (Red, Yellow and Green) that are wired into the OUSB
board prototype area will be used to represent the actual traffic light lamps, whereas the standard bank
of 8 LEDs connected to PORTB will be used to represents a simplified troubleshooting panel inside the
traffic light control box (e.g. the box that is normally on the side of the road at an intersection).
The troubleshooting (PORTB) lights will have the light states as well as other information encoded in
the 8-bit. Both PORTB and PORTD are used to control the Red, Yellow and Green prototype LEDs.

RESOURCES:
During this Lab test you will have access to the following PDF resources as the autotester will open the
following PDF files along with Visual Studio:
	1. "Teach Yourself C++ in 21 Days" PDF ebook
	2. "Open-USB-IO Reference, version 1.13" PDF file
These PDF files can be found on the EEET2250 Canvas Shell.

WARNING: Please make sure that during the lab test you do not
close the PDF files as you will not be able to open them again!

SCHEMATIC FOR TRAFFIC LIGHT LEDs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following circuitry has been already added to a standard Open-USB-IO board.

Your C++ Program     OUSB       .  Components Soldered onto Prototype Area
on the PC            Board      .
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			 ________           .
			|UNL2003A|          .                     Green LED
PB3	        |4     13|          .        270 ohms      //
----->------|--|> ---|-----J5---.->-----[\\\]--------|<|------| +5V DC
OC0         |        |   pin 27 .
			|        |          .                     Yellow LED
PD5         |2     15|          .        100 ohms      //
----->------|--|> ---|-----J5---.->-----[\\\]--------|<|------| +5V DC
OC1A        |        |   pin 23 .
			|        |          .                     Red LED
PD4         |1     16|          .        270 ohms      //
----->------|--|> ---|-----J5---.->-----[\\\]--------|<|------| +5V DC
OC1B        |________|   pin 21 .
								.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
NOTE: Yellow LED is lower intensity, hence the lower resistor value.


___________________________________________________________________________________________
___ GENERAL SPECIFICATIONS (common to all three EEET2250 Laboratory Tests):

G1.	You must rename your file to lab3_1234567.cpp, where 1234567 is your student number.
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
session and used the Visual studio command line debugging dialog box. You should be using
debug mode and a breakpoint at the return statement prior to program finish in main during the
process of developing your solution.

G8.	When your code exits the 'main()' function using the 'return' command, you MUST
use zero as the return value. This requirement is for exiting the 'main()' function ONLY.
A return value other than zero will indicate that something went wrong to the autotester and
no marks will be awarded.

G9.	Do NOT put any functions or class declarations AFTER the 'main()' function - if you write
your own functions/Classes, add them BEFORE the 'main()' function. This is a requirement of the
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
and are between 0 and 255 (inclusive), except the ADC values which are 0 to 1023. You as the
programmer must ensure that you construct and send correctly formed OUSB commands to the OUSB
board via a file pipe, as well as read back the correct values.

G14. Any binary numbers within this document have the prefix 0b. This notation is not supported
by C++ cout statements, however is used to avoid confusion between decimal, hexadecimal and binary
number formats within the description and specification provided in this document. For
example the number 10 in decimal could be written as 0xA in hexadecimal or 0b1010 in binary.
It can equally be written with leading zeros such as: 0x0A or 0b00001010. For output
to the console screen you should only ever display the numerical characters to represent the number
being displayed (in the expected base format) and omit the 0x or 0b prefixes. Assume all outputs to
the console are in base 10 format (i.e. Decimal) unless specifically specified.

G15. Do NOT attempt to read/write to any other OUSB Board IO port other than: PORTB 0-7 (all 8 bits),
PORTD bits PD5 and PD4 (all other portD bits should remain untouched), PINC 0-7, ADC pins 0 through
to 6 and the PWM pin 1, 2 or 3 (on port D). Other pins on the OUSB board are reserved for the
autotester, rs-232 port and the USB interface back to the computer.

___________________________________________________________________________________________
___ PROGRAM STRUCTURE and FUNCTIONAL REQUIREMENTS:

F1.	For situations where NO command line arguments are passed to your program:

F1.1	Your program must display your correct student details in the format:
"1234567,s1234567@student.rmit.edu.au,FirstName_LastName"

OUSB BOARD ACCESS:
F2.	Your program MUST access the OUSB board using the OUSB class (including read from/write to PORTB
and PORTD). You must ensure that you have private class data members to store the current value of
PORTB and PORTD and include appropriate accessor methods and private methods to read from and write to
PORTB and PORTD.

F2.1 The OUSB class must be instantiated in main() and be used to access the OUSB board IO. The tag
name of the class must be OUSB. You can also instantiate the OUSB class in other parts of the program
if you need too.

F2.2 Your program should accept the following command line parameters to read and write to PORTB:

- 'B' command: 'B' is the first parameter and the optional second parameter is the number to write to
PORTB.  If the 'B' parameter is use without the optional second parameter, print the current value of
PORTB (only the numeric value) to the console. If the 'B' command is used with a valid unsigned integer
between 0 and 255 as the second parameter, write the value to PORTB and print the new value on PORTB
(after the successful write) to the console.

Example 1:
lab3_1234567.exe B     // Read from PORTB and display the number read from PORTB to the console screen
lab3_1234567.exe B 10  // Write 10 to PORTB and display 10 to the console screen if write was successful

F2.3 Your program should accept the following command line parameters to read and write to PORTD:

- 'D' command: 'D' is the first parameter and the optional second parameter is the number to write to
PORTD.  If the 'D' parameter is use without the optional second parameter, print the current value of
PORTD (only the numeric value) to the console. If the 'D' command is used with a valid unsigned integer
between 0 and 255 as the second parameter, write the value to PORTD and print the new value on PORTD
(after the successful write) to the console.

Example 2:
lab3_1234567.exe D     // Read from PORTD and display the number read from PORTD to the console screen
lab3_1234567.exe D 16  // Write 16 to PORTD and display 16 to the console screen if write was successful

NOTE:  As selected bits in PORTD are used for USB and RS-232 support, bits: PD7, PD2 will not stick. For
example, if the command arguments were:
 lab3_1234567.exe D 16 D 255
Bits PD7 and PD2 will stay at logic Zero. Therefore when reading back the actual value on PORTD you will
get 123 (0b01111011). Therefore the correct value your program should display to console will be: 123
as this is the actual value that is now on PORTD after writing 255 to it.

Example 3:5
lab3_1234567.exe D     // Read from PORTD and display the number read from PORTD to the console screen
lab3_1234567.exe D 255 // Write 255 to PORTD and display 123 to the console screen if write was successful
lab3_1234567.exe D 16  // Write 16 to PORTD and display 16 to the console screen if write was successful

TRAFFIC LIGHT STATE MACHINE:
F3. Your program MUST have a Traffic light state machine class. You must ensure that you have private
class data members to store the current state of the traffic light (either as a single state to represent
all three lamps, or three lamp states). Include appropriate accessor functions and methods to change the
traffic light state in the class.

F3.1 The tag name of the class must be TrafficLight. The TrafficLight class must be instantiated
in main() and be used to control the state of the traffic light. The traffic light is composed of three
lamps (LEDs): Red, Yellow, and Green. The only lamp sequence possible is: Green-->Yellow-->Red (then
back to Green and repeat). Only one lamp can be on at a time.

PB3 (PORT_B bit 3) -> Green LED
PD5 (PORT_D bit 5) -> Yellow LED
PD4 (PORT_D bit 4) -> Red LED

F3.2 Your program should accept the following command line parameters as the first and second arguments:
- 'R', 'Y' or 'G' as the first argument: The letter indicates which state to start the traffic light
  state-machine in. The corresponding LED should be illuminated if first and second argument are valid.
- The second parameter is a valid unsigned integer between 0 and 15, which indicates the number of state
  transitions the program should run for.

Note: Due to the wiring and the configuration of the OUSB board PCB layout, when you switch on the Green LED
by writing a 1 to PORTB bit 3, the independently wired LED on the prototype area as well as the bit 3 LED
on the PORTB LED array will illuminate both at the same time. The Red and Yellow LEDs are independent as
they are connected to bit4 and bit5 of PORTD, respectively.

Example 4:
lab3_1234567 R 3  // Start the traffic light on Red and run for three transitions  i.e., R-->G-->Y-->R

F3.3 Use PORTB bits: bit0, bit1 and bit2 to indicate the Red and Yellow states of the state-machine.
In addition to the Red LED connected to PORTD being illuminated for the Red state, bit 0 of PORTB should
also be illuminated when the state machine is in the Red state. Similarly, for the Yellow state, bit 1 as
well as bit 2 of PORTB should be illuminated in conjunction with the Yellow LED when the state machine is
in the Yellow state. The second parameter (a valid unsigned integer between 0 and 15) will indicates the
number of state transitions the program should run for. Each transition should have the correct LED
illuminated with the correct LEDs on PORTB switched on for each state transition.

Example 5:
lab3_1234567 Y 2  // Start the traffic light on Yellow - Yellow LED and bit 1 and bit 2 of PORTB will be
				  // illuminated. Then the state machine will run for two transitions i.e., Y-->R-->G
Example 6:
lab3_1234567 G 5  // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for five transitions i.e., G-->Y-->R-->G-->Y-->R

Note: On exit the current state of the traffic light will be maintained on the OUSB Board.


F3.4 Upon completing all the state transitions, the program should print out the last value of PORTB in
decimal followed directly by a comma symbol (i.e. ',') and then the last value of PORTD in decimal,
followed by a line return. There should be NO white spaces in the output line.

Example 7:
lab3_1234567 G 5  // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for five transitions i.e., G-->Y-->R-->G-->Y-->R
				  // Output to console will be a single line containing the text:
1,16

F3.5 Your program should accept the following command line parameters as the first and second arguments:
- "CR", "CY" or "CG" as the first argument: The first character 'C', which is common to all 3 commands
indicates that you should maintain an incrementing counter for each state machine step. The value of the
counter then should be encoded into the top 4 bits of PORTB without effecting the lower 4 bits.

Note: Bits 0, 1, 2 and 3 of PORTB are already designated to represent the different state values of the
state machine.

Example 8:
lab3_1234567 CG 5 // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for five transitions i.e., G-->Y-->R-->G-->Y-->R
				  // Output to console will be a single line containing the text:
81,16
				  // The value 81 means bits 0, 4 and 6 of PORTB will be high. Bit 0 represents the
				  // final state being Red. Bits 4 and 6 mean five (5) state machine transitions were
				  // stepped through.

Example 9:
lab3_1234567 CG 1 // Start the traffic light on Green - Green LED and bit 3 of PORTB will be illuminated.
				  // Then the state machine will run for one transitions i.e., G-->Y
				  // Output to console will be a single line containing the text:
22,32
				  // The value 22 means bits 1, 2 and 4 of PORTB will be high. Bits 1 and 2 represents
				  // the final state being Yellow. Bit 4 mean one (1) state machine transitions was
				  // stepped through. The number 32 means bit 5 of PORTD is high, which indicates the
				  // Yellow LED is on (as the last state of the state machine was Yellow).

F3.6 All other bits on PORTB and PORTD should not be modified when individual bits in each port are set
high or cleared to zero. Therefore, when writing values to PORTB or PORTD at anytime throughout your
program, you should be maintaining the current value on the port and only set or clear the bit (or bits)
of interest. For instance when modifying PORTB in response to a valid 'G', 'Y' or 'R' command, then only
the first 4 bits of PORTB should be modified and the upper 4 bits should maintain state.

Example 10:
If the OUSB board was setup with the value 255 on PORTB and 123 on PORTD prior to your code running
with the following command line arguments:
lab3_1234567 G 1
The last (and only) line on the console will be:
246,107

Note: In the case of the above example, the program should have only modified bits 0, 1, 2 and 3 of PORTB
and bits 4 and 5 of PORTD.

However, when your program responses to a 'CG', 'CY' or 'CR' commands, then the upper 4 bits and lower 4 bits
of PORTB be can be fully modified as the upper 4 bits of PORTB be are used to maintain a counter.

Example 11:
If the OUSB board was setup with the value 128 on PORTB and 123 on PORTD prior to your code running
with the following command line arguments:
lab3_1234567 CY 1
The last (and only) line on the console will be:
22,107

Commands 'B' and 'D' can modify all 8 bits in their respective ports with the exception of bits 2 and 7 in
PORTD. Remember that bits 2 and 7 of PORTD are used for the USB interface and always read as logic 0 when
using ousb.exe commands.

F3.7 Other considerations:

Your program should only display a single line on the console for all specifications followed by a
newline character and then exit (with a return 0).

Your program MUST use pipes to communicate with the OUSB board, system calls are NOT allowed:
system("ousb -r io portb 127");   // not allowed

System calls take longer and automatically echo the result to the command shell window. If you use system calls
in your code it is very likely the code will not work properly with the autotester or meet specifications. You
will most likely lose all marks for this lab. Therefore, you MUST use the code using pipes. See the code fragments
given to you and explained in lectures and on Blackboard. Sample code to access the OUSB board via pipes is provided.

Please remember to use good programming practice, hence every time you open a file pipe you MUST close the pipe using
'_pclose(<pipename>);. Failure to not do this will result in your code being highly unreliable and you could lose
a lot of marks due to your program not behaving correctly while being tested by the autotester.

************  IMPORTANT !!!  *********   IMPORTANT !!!   *******************************
***
***  IN LAB TEST 3 YOU MUST IMPLEMENT A CLASS to access the OUSB board - this
***  will be checked - your maximum score will be capped at 40% if you do not use
***  an OUSB class!!!  Therefore if you code scores 80% from the autotester, your
***  actual final mark will be reduced to 40%.
***
***  IN LAB TEST 3 YOU WILL AUTOMATICALLY LOSE 20% OF YOUR MARK IF YOU
***  DO NOT HAVE MATCHING _popen(...) and _pclose(...) - this will be checked!!!
***
************  IMPORTANT !!!  *********   IMPORTANT !!!   *******************************

About pipes and _popen:
http://www.cplusplus.com/forum/windows/1341/
http://www.cplusplus.com/forum/windows/10766/

___________________________________________________________________________________________
___ ERROR HANDLING:

The following text lists errors you must detect and a priority of testing.
Note: order of testing is important as each test is slightly more difficult than
the previous test.

All outputs are a single character followed by a newline ( endl or \n).
DO NOT add more than what is specified, do NOT add additional information.

E1. Error precedence:
The order of errors can theoretically be checked in any order, however if multiple errors
occur during a program execution event, your program should only display one error code
followed by a newline character and then exit (with a return 0). The displayed error
codes to the console window should occur in this order:
	'I' - Incorrect input command line argument for first operand (second parameter)
	'P' - Incorrect number of input command line arguments
	'N' - Invalid numerical command line argument (second operand or third parameter)
	'R' - The second operand argument is a numerical value that is out of range
	'Z' - MURPHY'S LAW (undefined error)
Therefore if an invalid numerical command line argument (operand 2) with an invalid first
operand are passed to the program, the first error code should be displayed to the console,
which in this case would be 'I'. Displaying 'N' or 'R' would be result in a loss of marks.


E2. NUMBER OF PARAMETERS

E2.1 If the number of parameters is 1 the program MUST print student ID string in CSV format described
above and then exit. That is, when the program is run without any operands i.e. with no command line
arguments other than the name of the program.

E2.2 The second parameter that is passed into the program can only be 'B' 'D', 'R', 'Y', 'G', 'CR',
'CY' or 'CG'. For any other (case sensitive) letter or character combination or argument string, the
output shall be 'I' which signals the second parameter is erroneous. After outputting 'I' (and new
line), your program should exit without effecting the OUSB board.

E2.3 If the number of parameters is 2 and the (first) operand is not 'B' or 'D', the output shall be
'P' which signals a parameter error. Then program should return 0 and exit.

Example 12: That is, following the program name, the command line can take two or three parameters only:
lab3_1234567.exe  Operand1
Testples:
lab3_1234567.exe B   		(valid)
lab3_1234567.exe G 			(NOT valid: output: P)
lab3_1234567.exe CG			(NOT valid: output: P)

E2.4 If the number of parameters is 4 or more: the output shall be 'P' which signals a parameter error.
Then program should return 0 and exit.

E2.5 If a numerical unsigned integer is not entered as the third parameter as required for all commands
(apart from when 'B' or 'D' are used alone), the output shall be 'N' which signals a numerical
parameter error in the third parameter. Please note, this does not include out of range values. After
outputting 'N' (and a new line), your program should exit without effecting the OUSB board.

Example 13: That is, following the program name, the command line can take two or three parameters only:
lab3_1234567.exe  Operand1 Operand2
Testples:
lab3_1234567.exe G 1		(valid)
lab3_1234567.exe G 1.0		(NOT valid: output: N)
lab3_1234567.exe G -1		(NOT valid: output: N)
lab3_1234567.exe G t1		(NOT valid: output: N)
lab3_1234567.exe G 1t		(NOT valid: output: N)

E3.  VALID NUMBER RANGE

E3.1 If the number entered as the third parameter on the command line is not within an accepted range,
then the output shall be 'R' which signals a range error. Then program should return 0 and exit.

The accepted number ranges are:
	- 'B' and 'D' commands: Second operand must be between 0 and 255 in valid integer format
	- 'R', 'Y' or 'G' commands: Second operand must be between 0 and 15 in valid integer format
	- 'CR', 'CY' or 'CG' commands: Second operand must be between 0 and 15 in valid integer format

Example 14: That is, following the program name, the command line can take two or three parameters only:
lab3_1234567.exe  Operand1 Operand2
Testples:
lab3_1234567.exe B 250		(valid)
lab3_1234567.exe G 10		(valid)
lab3_1234567.exe B 256		(NOT valid: output: R)
lab3_1234567.exe G 16		(NOT valid: output: R)

Note: All numerical arguments must be an unsigned integer value, therefore if a decimal or exponential
number is provided as an argument, your program should have already responded with 'N' from previous
error check.

E4.  ANYTHING ELSE THAT CAN GO WRONG (MURPHY'S LAW TEST)
If there are any other kinds of errors not covered here, the output shall be 'Z'. That is: anything
else that can possibly go wrong and has not be explicitly tested for or covered under the tests above.
For example:
	- no OUSB board connection.
	- disconnection during operation
	- HW dead.
	- ???? anything else Murphy can dream up.
	- everything that has not been covered elsewhere is Murphy's domain.

Note: The OUSB.exe will give a message "Fatal Exception" if the board is not connected or is disconnected
during normal operation. This message should NOT be returned by your code. The only output your code
should give is the single character: 'Z', followed by a new line and then it should return 0 and exit.

Suggestion: only worry about Hardware errors/test if you have clearly covered ALL preceding tests!

ERROR CHECKING HINTS: The basic programming rules are simple (as covered in lectures):
1) Check that the input is valid.
2) Check that the output is valid.
3) If any library function returns an error code USE IT !!! CHECK FOR IT !!! If that means more than 50%
of your code is error checking, then that's the way it has to be.

___________________________________________________________________________________________
___ GENERAL INFORMATION AND HINTS:

- This program must be in one file named lab3_1234567.cpp where 1234567 is your
student number.
For Testple : lab3_1234567.cpp or lab3_3987654.cpp
Your filename MUST NEVER EVER contain any spaces.  _under_score_is_Fine.

- When text output is required you must generate EXACTLY that
output and no other output.  For Testple-
Specified output: "RX"    Actual program output: "rx"      Result: zero marks.
Specified output: "RX"    Actual program output: "Got RX"  Result: zero marks.
Specified output: "RX"    Actual program output: " RX"     Result: zero marks.

- Use debug mode and a breakpoint at the return statement prior to program finish in main.

- What string conversion routines do you know that convert strings to numbers?
Look carefully as they will be needed to convert a command line parameter to a number and
also check for errors.

- Most conversion routines do have inbuilt error checking - USE IT !!!
That means: test for the error condition and take some action if the error is true.
If that means more than 70% of your code is error checking, then that's
the way it has to be.

- Tackle the easiest tasks first and build your program up in stages. The easiest tasks are
are normally the first tasks mentioned. Therefore has you get down to the last few tasks these
are the tasks that can trip you up or lead to issues if you have not designed your code
with an adequate structure to handle all the possible issues and combinations.

- Your mark will result from testing your program against a whole range of inputs. The secret to
getting a good mark is to carefully analyse all possible errors and odd situations BEFORE you
write the code so read the proforma VERY carefully. Ensure in each circumstance you can detect
the error or condition and report the appropriate result. Hint: write test cases before you
write any code.

- General OUSB commands that might be useful:
To read the value at port B:					ousb -r io portb
To write 20 to port B:  						ousb -r io portb 20
To write 16 to port D:  						ousb -r io portd 16
To read the value of the DIP switches (pinc):	ousb -r io pinc
To read the potentiometer (ADC5):				ousb -r adc 5
To set pwm-freq to 45Hz on pin 1:				ousb -r pwm-freq 1 45
To set pwm duty cycle to 50% on pin 1:			ousb -r pwm 1 50

- Description of _itoa_s() library function - Converts an integer to a string.
Prototype:
		   errno_t _itoa_s(int value, char *buffer, int radix);
Parameters:
[in] value   - Number to be converted.
[out] buffer - buffer is filled with the result of the conversions a C string.
[in]  radix  - Base of value, which must be in the range of 2-36.
Return Value - Zero if successful; an error code on failure.


- Description of strcpy_s() library function - Copies a C string.
Prototype:
		   errno_t strcpy_s(char *strDestination, const char *strSource);
Parameters:
strDestination - Location of the destination string buffer.
strSource      - Null-terminated source string buffer.
Return Value   - Zero if successful; an error code on failure.


- Description of strcat_s() library function - Appends a C string.
Prototype:
		   errno_t strcat_s(char *strDestination, const char *strSource);
Parameters:
strDestination - Null-terminated destination string buffer.
strSource      - Null-terminated source string buffer.
Return Value   - Zero if successful; an error code on failure.


- The following code is the syntax required to open a pipe to the device.
It may / may not include all of the necessary code to complete the task.

//----Start of template standalone .cpp file--------------------------------------------
#include "pch.h"
#include <iostream>
#define Debug 1  			// set debug to ON
using namespace std;
int main(int argc, char* argv[])
{
	char command[256] = {};
	strcpy_s(command, "ousb -r io PORTB 20"); // command to write 20 to OUSB board

	if (Debug) cout << "DEBUG :" << command << endl; // print out OUSB data for debug purposes

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			if (Debug) cout << "DEBUG :" << line ; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// do something with the value returned by the OUSB board, eg:
	int portb = (int)atoi(line); // convert from char array to int
	if (Debug) cout << "DEBUG :" << "value = " << portb << endl;

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

using namespace std; // Please do not remove this line

					 // optional: your choice if you want to use/modify these definitions for MAX-MIN-Range
const double MAXRANGE = 255;
const double MINRANGE = 0;

// optional: your choice if you want to write class method and function prototypes here.
//           They should be defined above the OUSB and TrafficLight Class definitions
//           if they are going to be used by the classes themselves as all code must
//           contained in this file (ie. no separate *.h files for autotester)


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
	int read_write_port(string r_w, char portname[], int val);
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


int OUSB::read_write_port(string r_w, char portname[], int val)
{
	string portnamestring = portname;
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousb -r io " }; // Need to have a extra space after PORTB
	char val_string[4] = {};
	strcat_s(command, portname);

	if (r_w == "w")//can only write to two port
	{
		if (portnamestring == "PORTB")
		{
			PORTB = val;
		}
		else if (portnamestring == "PORTD")
		{
			PORTD = val;
		}
		else;

		strcat_s(command, " ");
		_itoa_s(val, val_string, 10);
		strcat_s(command, val_string);
	}
	else if (r_w == "r") //reading from porta or adc is weird
	{
		if (portnamestring == "PORTA")
		{
			strcpy_s(command, "ousb -r adc");
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
			if (line[0] == 'F')
			{
				return 6666;
			}
		}
		_pclose(fpipe);
	}

	
	if (r_w == "r")
	{
		// convert value from char array to int	
		unsigned int portvalue = (unsigned int)atoi(line);
		if (portnamestring == "PORTA")
		{
			PORTA = portvalue;
			return PORTA;
		}
		else if (portnamestring == "PORTB")
		{
			PORTB = portvalue;
			return PORTB;
		}
		else if (portnamestring == "PORTC")
		{
			PORTC = portvalue;
			return PORTC;
		}
		else if (portnamestring == "PORTD")
		{
			PORTD = portvalue;
			return PORTD;
		}
		else
		{
			return 0;
		}
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

	void changeTrafficLightState(char state);

};
// write all class methods and stand alone functions here below this line



void TrafficLight::changeTrafficLightState(char state)
{
		if (state == 'R')
		{
			greenOn(false);
			yellowOn(false);
			redOn(true);
		}
		else if (state == 'Y')
		{
			greenOn(false);
			yellowOn(true);
			redOn(false);
		}
		else
		{
			greenOn(true);
			yellowOn(false);
			redOn(false);
		}
}

int main(int argc, char *argv[])
{
	//--- When no parameters MUST print id string in CSV format. 
	if (argc == 1)  // no parameters print this line.
	{
		cout << "3616240,s3616240@student.rmit.edu.au,Nikhshay_Singh_Kukreja"
			<< endl;
		// Any errors in the line above,  or the naming of the file
		//  will result in 10% being deducted from your mark.
		return(0);
	}

	else if (argc == 2)//1 argument
	{
		//B X write x to portb x= 0-255
		//D X write x to portd x= 0-255
		// R/G/Y x = start traffic light at R/G/B and loop x times, x= 0-15
			//R = bit 0 portb
			//y = bit 1 and 2 portb
			//G = bit 3 portb
			//on exit, current state must be maintained on ousb
			//print out last state value of portb,portd
		//CG/CR/CY x 
		char charportb[] = { "PORTB" };
		char charportd[] = { "PORTD" };
		if (argv[1][0] == 'B')
		{
			OUSB ousb;
			int val = ousb.read_write_port("r", charportb, 0);
			if (val == 6666)
			{
				cout << "Ousb disconnected" << endl;
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

			OUSB ousb;
			int val = ousb.read_write_port("r", charportd, 0);
			if (val == 6666)
			{
				cout << "Ousb disconnected" << endl;
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
			cout << "Invalid argument 1" << endl;
			return 0;
		}
		
	}

	else if(argc == 3)
	{
		if ((argv[1][0] == 'B' || argv[1][0] == 'D'|| argv[1][0] == 'R' || argv[1][0] == 'Y' || argv[1][0] == 'G') && argv[1][1] == '\0');
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
		int argument2 = atoi(argv[2]);//second argument as int



		OUSB board;
		char charportb[] = { "PORTB" };
		char charportc[] = { "PORTC" };
		char charportd[] = { "PORTD" };
		int currentportbvalue = 0;
		int currentportdvalue = 0;
		int currentportcvalue = board.read_write_port("r", charportc, 0);
		if (currentportcvalue == 6666)//check hardware disconnection
		{
			cout << "ousb disconnected" << endl;
			return 0;
		}
		else;


		if (argv[1][0] == 'B')
		{
			if (argument2 >= 0 && argument2 <= 255)
			{
				board.read_write_port("w", charportb, argument2);
				currentportbvalue = board.getPORTBvalue();
				cout << currentportbvalue << endl;
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
			if (argument2 >= 0 && argument2 <= 255)
			{
				board.read_write_port("w", charportd, argument2);
				currentportdvalue = board.getPORTDvalue();
				cout << currentportdvalue << endl;
				return 0;
			}
			else
			{
				cout << "Out of range 2nd arg << endl" << endl;
				return 0; 
			}
		}
		else if (argv[1][0]== 'R' || argv[1][0] == 'G' || argv[1][0] == 'Y')
		{
			TrafficLight Shibuya_crossing;
			currentportbvalue = board.read_write_port("r", charportb, 0);
			currentportdvalue = board.read_write_port("r", charportd, 0);

			if (argument2 >= 0 && argument2 <= 15)
			{
				for (int i = 0; i <= argument2; i++)
				{
					Shibuya_crossing.changeTrafficLightState(argv[1][0]);
					switch (argv[1][0])
					{
						case 'R':
						{
							currentportbvalue = (currentportbvalue & 240) + 1;
							board.read_write_port("w", charportb, currentportbvalue);
							currentportdvalue = (currentportdvalue & 207) + 16;
							board.read_write_port("w", charportd, currentportdvalue);
							argv[1][0] = 'G';
							Sleep(1000); //Debug only remove the line
							break;
						}
						case 'G':
						{
							currentportbvalue = (currentportbvalue & 240) + 8;
							board.read_write_port("w", charportb, currentportbvalue);
							currentportdvalue = (currentportdvalue & 207);
							board.read_write_port("w", charportd, currentportdvalue);
							argv[1][0] = 'Y';
							Sleep(1000); //Debug only remove the line
							break;
						}
						case 'Y':
						{
							currentportbvalue = (currentportbvalue & 240) + 6;
							board.read_write_port("w", charportb, currentportbvalue);
							currentportdvalue = (currentportdvalue & 207) + 32;
							board.read_write_port("w", charportd, currentportdvalue);
							argv[1][0] = 'R';
							Sleep(1000); //Debug only remove the line
							break;
						}
					}
				}
				cout << currentportbvalue << "," << currentportdvalue;
				return 0;
			}
			else
			{
				cout << "Out of range 2nd arg << endl" << endl;
				return 0;
			}
		}
		else
		{
			TrafficLight Shibuya_crossing;
			currentportbvalue = board.read_write_port("r", charportb, 0);
			currentportdvalue = board.read_write_port("r", charportd, 0);
			int count = 0;

			if (argument2 >= 0 && argument2 <= 15)
			{
				for (int i = 0; i <= argument2; i++)
				{
					Shibuya_crossing.changeTrafficLightState(argv[1][1]);
					switch (argv[1][1])
					{
						case 'R':
						{
							board.read_write_port("w", charportb, currentportbvalue);
							currentportbvalue = count + 1;
							board.read_write_port("w", charportb, currentportbvalue);

							currentportdvalue = (currentportdvalue & 207) + 16;
							board.read_write_port("w", charportd, currentportdvalue);
							argv[1][1] = 'G';
							Sleep(1000); //Debug only remove the line
							break;
						}
						case 'G':
						{
							currentportbvalue = count + 8;
							board.read_write_port("w", charportb, currentportbvalue);
							currentportdvalue = (currentportdvalue & 207);
							board.read_write_port("w", charportd, currentportdvalue);
							argv[1][1] = 'Y';
							Sleep(1000); //Debug only remove the line
							break;
						}
						case 'Y':
						{
							currentportbvalue = count + 6;
							board.read_write_port("w", charportb, currentportbvalue);
							currentportdvalue = (currentportdvalue & 207) + 32;
							board.read_write_port("w", charportd, currentportdvalue);
							argv[1][1] = 'R';
							Sleep(1000); //Debug only remove the line
							break;
						}
					}
					cout << "Debug only: count = " << count << endl;
					count = count + 16;
				}
				cout << currentportbvalue << "," << currentportdvalue;
				return 0;
			}
			else
			{
				cout << "Out of range 2nd arg << endl" << endl;
				return 0;
			}
		}
		
	}
	else
	{
		cout << "Invalid num of arg" << endl;
		return 0;
	}


	return(0); 

}
// do NOT put any functions/code after this closing bracket, if you use functions add them before main()
// End of File


