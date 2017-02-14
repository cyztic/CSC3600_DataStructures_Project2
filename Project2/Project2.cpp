//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  Project2.cpp          ASSIGNMENT #:  2            Grade: _________          *
//*                                                                                                   *
//*   PROGRAM AUTHOR:     __________________________________________                                  *
//*                                     Micaiah Skolnick                                              *
//*                                                                                                   *
//*   COURSE #:  CSC 36000 1                            DUE DATE:  February 6, 2017                  *
//*                                                                                                   *
//*****************************************************************************************************
//***********************************  PROGRAM DESCRIPTION  *******************************************
//*                                                                                                   *
//*   PROCESS: This program first reads a one character code, then depending on the code, processes   *
//*              values for a record list on the subsequent input lines. Records are stored in a      *
//*              structure, and the list of structures is built by a class which controls the list.   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : newPage - Prints a blank line for each blank space left on the page              *
//*                  Footer - Prints a footer to signify end of program output                        *
//*                  Header - Prints a header to signify start of program output                      *
//*                  getData - Data from the input file is read into the program                      *
//*                  main - Variables are declared, functions are called, and headers are printed     *
//*                  processData - Read each Op code character and perform the subsequent action.     *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
#include "RecordListClass.h"
using namespace std;
int lineCount;
int MAXLINECOUNT;
//*****************************************************************************************************
void newPage(ofstream&dataOUT) {
	// Receives – the output file
	// Task - Insert blank lines to fill the rest of the current page
	// Returns - Nothing
	while (lineCount < MAXLINECOUNT) {
		dataOUT << endl;
		lineCount++;
	}
	lineCount = 0; // Reset the line count to 0 for next page.
}
//*****************************************************************************************************
//*************************************  FUNCTION HEADER  *********************************************
void Header(ofstream &Outfile)
{       // Receives – the output file
		// Task - Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Micaiah Skolnick ";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(27) << "Spring 2017";
	Outfile << setw(30) << "Assignment #2" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- - " << endl << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION HEADER  ***************************************
//*************************************  FUNCTION FOOTER  *********************************************
void Footer(ofstream &Outfile, int lineCount)
{
	// Receives – the output file
	// Task - Prints the output salutation
	// Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
	Outfile << setw(35) << "-------------------------------- - " << endl;
	lineCount += 4;
	return;
}
//************************************* END OF FUNCTION FOOTER  ***************************************
void processData(ofstream&dataOUT, ifstream&dataIN) {
		// Receives – The input and output files
		// Task - Process each data record/op code.
		// Returns - Nothing
	RecordListClass RecordList;
	bool firstPrint = true;

	RecordType record;
	int fieldNumber;
	string newValue;

	char code;
	dataIN >> ws >> code >> ws; // seed read first code
		
	while (code != 'Q') {  // As long as there is another code, read it in
		switch (code) {
		case 'A':	// If the code = 'A', first read a record, then insert it into the list.
			std::getline(dataIN, record.firstName);
			std::getline(dataIN, record.lastName);
			std::getline(dataIN, record.address);
			std::getline(dataIN, record.city);
			std::getline(dataIN, record.state);
			std::getline(dataIN, record.zipCode);
			if (!RecordList.insertRecord(record)) {
				dataOUT << endl;
				lineCount++;
				dataOUT << record.firstName << record.lastName;
				dataOUT << " is already in list. Attempt to duplicate record failed!";
			}
			break;
		case 'D': // If the code is 'D', first read the name of the record, then delete from the list.
			std::getline(dataIN, record.firstName);
			std::getline(dataIN, record.lastName);
			if (!RecordList.deleteRecord(record)) {
				dataOUT << endl;
				lineCount++;
				dataOUT << "Record of " << record.firstName << record.lastName;
				dataOUT << " not found. Attempt to delete record failed!";
			}
			break;
		case 'C': // If the op code is a 'C' change the indicated record
			std::getline(dataIN, record.firstName);
			std::getline(dataIN, record.lastName);
			dataIN >> fieldNumber >> ws;
			std::getline(dataIN, newValue);
			if (!RecordList.changeRecord(record, fieldNumber, newValue)) {
				dataOUT << endl;
				lineCount++;
				dataOUT << "Record of " << record.firstName << record.lastName;
				dataOUT << " not found. Attempt to change record failed!";
			}
			break;
		case 'P':
			if (!firstPrint) { // After the first time printing, start a new page for each list.
				newPage(dataOUT);
			}
			RecordList.printRecords(dataOUT, lineCount);
			firstPrint = false;
			break;
		}
		dataIN >> ws >> code >> ws; // Read in the next code
	}
}
int main() {
		// Receives – Nothing
		// Task - Call each necessary function of the program in order
		// Returns - Nothing
	// Declare variables used in program.	 
	ifstream dataIN;
	ofstream dataOUT;
	lineCount = 0;
	MAXLINECOUNT = 54;

	dataIN.open("data2.txt"); // Open the file containing data.
	dataOUT.open("dataOUT.doc"); // Create and open the file to write data to.		
	Header(dataOUT); // Print data header.
	processData(dataOUT, dataIN); // Process each section of data from the input file.
	newPage(dataOUT); // Insert a page break before the footer
	Footer(dataOUT, lineCount); // Print footer. 
	dataIN.close(); // Close input data file. 
	dataOUT.close(); // Close output data file.

	return 0;
}


