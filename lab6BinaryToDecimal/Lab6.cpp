/*
Jayce Abens
FA2021
Due : November, 10 2021
Lab 6 Binary to Decimal Conversion

Write a C++ program that reads characters representing binary (base 2)
numbers from a data file called BinaryIn.dat and translates them to decimal (base 10)
numbers. The binary and decimal numbers should be output in two columns with
appropriate headings.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void calculateDecimal(ifstream& inFile, string& binaryOut, unsigned int& decimal);
void printConversion(string binaryOut_, string decimalOut);

int main()
{
	const string inputFileName = "C:/Users/Jayce Abens/source/repos/lab6BinaryToDecimal/lab6BinaryToDecimal/BinaryIn.dat"; //input file location, bianary values are separated by line
	ifstream inFile;
	inFile.open(inputFileName);		// opens in file stream
	
	string binaryOut;	// string used to store final binary output to the screen
	unsigned int decimal = 0; // integer used store converted integer value as it it calculated

	printConversion("Binary Number", "Decimal Equivalent"); // prints the column headings using the same alignment logic as the outputed numbers

	while (inFile) // loops until the end of the file is reached
	{
		calculateDecimal(inFile, binaryOut, decimal);
		printConversion(binaryOut, to_string(decimal)); // output decimal value is converted to a string to use alignment logic in printConversion()
	}

	inFile.close(); // closes file stream
	return 0;
}

/* Precondition : The fstream and string libraries are included. Using namespace std. A file stream "inFile" is open at a valid file location. The binary values contained within the file are separated by line.
						String binaryOut and int decimal are declared and passed to the function by reference. 
   Postcondition : The program has read one line of characters from the file storing them within the binaryOut variable.  The binary data is converted and stored in the decimal variable. 
						Any unexpected characters were detected and an error message stored within the binaryOut variable. 
*/
void calculateDecimal(ifstream& inFile, string& binaryOut, unsigned int& decimal)
{
	char binaryRaw;	// char to store each file character as it is read
	bool endOfLine = false;	// boolean to signify the end of the line has been reached
	bool badInput = false;	// boolean to signify an input character was not 1 or 0
	binaryOut = ""; // resets to binaryOut string to blank
	decimal = 0; // resets the converted decimal value to 0

	do {
		inFile.get(binaryRaw); // stores one character from the file
	} while (binaryRaw == ' '); // loops until it is not a blank space character

	do {
		switch (binaryRaw)
		{
		case '0':
		case '1': decimal = (decimal*2) + (int(binaryRaw) - 48); // if the input character is a 1 or 0, the decimal conversion logic is executed. The char is cast to an int (0 = 48, 1 = 49) 48 is subtracted to convert it to its true integer value
			binaryOut.append(1, binaryRaw); // appends the character to the end of the binaryOut string
			inFile.get(binaryRaw);	// stores the next character from the file
			break;
		case '\n': endOfLine = true; // if a end of line character is reached, endOfLine is set to true, ending the loop
			break;
		default: badInput = true; // if a character other than 1 or 0 is read, the badInput condition is set to true, this does not end the loop, it continues until the end of the line
			inFile.get(binaryRaw);	 // stores the next character from the file
		}
	} while (!endOfLine && inFile); // loops until the end of the line or file has been reached

	if (badInput) binaryOut = "Bad digit on input"; // if a line contained a bad input character, the binaryOut string is replaced with an error message
}

/* Precondition : The iostream and iomanip libraries are included. Using namespace std. A string to be printed in the first column is passed to the function as the binaryOut_ parameter. 
						A string to be printed in the second column is passed to the function as the decimalOut parameter. 
   Postcondition : The binaryOut_ and decimalOut strings are printed to the screen centered on two columns of a width defined by columnWidth. 
						If a bad digit error message is diplayed in the first column, the second column should not be printed.
*/
void printConversion(string binaryOut_, string decimalOut)
{
	const int columnWidth = 35; // defines the width of the two columns by character count, outputs are centered on this width. 32 is minimum for 32 bit binary inputs, 3 added for spacing.

	cout << setw(binaryOut_.length() + int(float(columnWidth - binaryOut_.length())/2 + 0.5)); // sets width of output in order to center within specified column width. 0.5 is added to round float vlaue rather than truncate  
	cout << binaryOut_;

	if (binaryOut_ == "Bad digit on input") // if a bad digit error message is displayed, the decimal conversion is not outputed
	{
		cout << endl;
	}
	else
	{
		cout << setw(decimalOut.length() + int(float(columnWidth - decimalOut.length())/2 + 0.5) + (columnWidth - binaryOut_.length()) / 2); // sets width of output in order to center within specified column width
		cout << decimalOut << endl;
	}
}