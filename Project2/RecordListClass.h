//************************************  PROGRAM IDENTIFICATION  ***************************************
//*                                                                                                   *
//*   PROGRAM FILE NAME:  RecordListClass.cpp          ASSIGNMENT #:  2                               *
//*                                                                                                   *
//*                                                                                                   *
//*   USER DEFINED                                                                                    *
//*    MODULES     : insertRecord - Insert one record of type RecordType into list of records         *
//*                  printRecords - Print each of the records in the list                             *
//*                  deleteRecord - Delete one record from the list	                                  *
//*                  changeRecord - Change one value of one record in record list                     *
//*                                                                                                   *
//*****************************************************************************************************
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
using namespace std;
//*****************************************************************************************************
struct RecordType {
		// The structure "RecordType" holds each record file.
	string firstName, lastName, address, city, state, zipCode;
	RecordType *recordPtr;
	RecordType *next;
};
class RecordListClass {
public:
	RecordListClass();
	bool insertRecord(RecordType);
	void printRecords(ofstream&, int&);
	bool deleteRecord(RecordType record);
	bool changeRecord(RecordType, int, string);
private:
	RecordType *StartPtr;
};
//*****************************************************************************************************
RecordListClass::RecordListClass() {
	StartPtr = NULL;
}
//*****************************************************************************************************
bool RecordListClass::insertRecord(RecordType record) {
		// Receives – A single record of type RecordType
		// Task - Add a record to the list of records.
		// Returns - True or false indicating whether a record was added.
		// Declare local pointers
	RecordType *newPtr, *PreviousPtr, *CurrentPtr, *dupPrevPtr, *dupCurrPtr;
		// Reserve memory for a new node
	newPtr = new(RecordType);
		// Place the data in the new node
	newPtr->firstName = record.firstName;
	newPtr->lastName = record.lastName;
	newPtr->address = record.address;
	newPtr->city = record.city;
	newPtr->state = record.state;
	newPtr->zipCode = record.zipCode;
	newPtr->next = record.next;
	PreviousPtr = NULL;
	CurrentPtr = StartPtr; // Begin searching from start of linked list

		// search for the location to insert the new node 
	while ((CurrentPtr != NULL) && (newPtr->lastName.compare(CurrentPtr->lastName) > 0)) {
		PreviousPtr = CurrentPtr;
		CurrentPtr = CurrentPtr->next;
	}
		// Once the intended location is found, make sure that if last names are equal,
			// the search continues based on first name.
	while ((CurrentPtr != NULL) && (newPtr->lastName.compare(CurrentPtr->lastName) == 0) 
		&& (newPtr->firstName.compare(CurrentPtr->firstName) > 0)) {
		PreviousPtr = CurrentPtr;
		CurrentPtr = CurrentPtr->next;
	}
		// Continue through the list If both last name and first name are the same, return false, 
		//	indicating that record could not be added.
	dupPrevPtr = PreviousPtr;
	dupCurrPtr = CurrentPtr;
	while (dupCurrPtr != NULL) {
		if ((newPtr->lastName.compare(dupCurrPtr->lastName) == 0)
			&& (newPtr->firstName.compare(dupCurrPtr->firstName) == 0)) {
				return false;
			}
		dupPrevPtr = dupCurrPtr;
		dupCurrPtr = dupCurrPtr->next;
	}
	// if no list exist, place new node at the start of the list
	if (PreviousPtr == NULL)
	{
		newPtr->next = StartPtr;
		StartPtr = newPtr;
		return true;
	}
	else
	{	// insert the new node into the list
		PreviousPtr->next = newPtr;
		newPtr->next = CurrentPtr;
		return true;
	}
	return false;
}
//*****************************************************************************************************
void RecordListClass::printRecords(ofstream&Outfile, int&lineCount) {
		// Receives – A the output file, and the line count.
		// Task - Prints each record in the list.
		// Returns - Nothing
	RecordType  *CurrentPtr;
		// Initialize a current pointer to the start of the linked list
	CurrentPtr = StartPtr;
		// Check for an Empty List
	if (CurrentPtr == NULL) {
		Outfile << "List is Empty" << endl;
		lineCount++;
		return;
	}
		// Print a data header
	Outfile << endl << "                         MAILING LIST" << endl;
	Outfile << "Last Name   First Name  Address             City";
	Outfile << "        State Zip Code" << endl;
	Outfile << "======================================================================" << endl;
	lineCount += 4; // Increment the line count by 4
					// Print each member of the list
	while (CurrentPtr != NULL)
	{                               //  Print the data
		Outfile << CurrentPtr->lastName << CurrentPtr->firstName;
		Outfile << CurrentPtr->address << CurrentPtr->city;
		Outfile << CurrentPtr->state << "    " << CurrentPtr->zipCode << endl;
		lineCount++; // Increment the line count for each record
					 //  Move to the next NODE
		CurrentPtr = CurrentPtr->next;
	}
	return;
}
//*****************************************************************************************************
bool RecordListClass::deleteRecord(RecordType record) {
		// Receives – A single record of type RecordType
		// Task - Delete a record from the list of records.
		// Returns - True or false indicating whether a record was deleted.
	RecordType *tempPtr, *PreviousPtr, *CurrentPtr;
		//If the record to be deleted is the first record, reset the starting pointer
	if (record.lastName.compare(StartPtr->lastName) == 0
		&& record.firstName.compare(StartPtr->firstName) == 0) {
		tempPtr = StartPtr;
		StartPtr = StartPtr->next;
		delete (tempPtr);
		return true;
	}
	else { 		// initialize local pointers to search for the node to be deleted
		PreviousPtr = StartPtr;
		CurrentPtr = StartPtr->next;
		//  step through the list until  the delete node is found or the list is exhausted
		while (CurrentPtr != NULL) {
			if ((record.firstName != CurrentPtr->firstName) 
				|| (record.lastName != CurrentPtr->lastName)) {
				PreviousPtr = CurrentPtr;
				CurrentPtr = CurrentPtr->next;
			}
			else {
				break;
			}
		}
			//  if the node is found, adjust pointers to removed it from the list, free up the space
			//  in memory used by the  deleted node, and return the data.
		if (CurrentPtr != NULL)
		{
			tempPtr = CurrentPtr;
			PreviousPtr->next = CurrentPtr->next;
			delete (tempPtr);
			return true;
		}
	}
		// return a value that indicates the node was not found
	return false;
}
bool RecordListClass::changeRecord(RecordType record, int fieldNumber, string newVal) {
		// Receives – A record of type RecordType, an int indicating type of value and the new value
		// Task - change a record in the list of records.
		// Returns - True or false indicating whether a record was changed.
	RecordType *PreviousPtr, *CurrentPtr, newRecord;
			// initialize local pointers to search for the node to be changed
		PreviousPtr = NULL;
		CurrentPtr = StartPtr;  // Start searching at first node

			//  step through the list until  the change node is found or the list is exhausted
		while (CurrentPtr != NULL) {
			if ((record.firstName != CurrentPtr->firstName) 
				|| (record.lastName != CurrentPtr->lastName)){
				PreviousPtr = CurrentPtr;
				CurrentPtr = CurrentPtr->next;
			}
			else {
				break;
			}
		}
			//  if the node is found, delete the current record in the list, and add the
				// updated one.
		if (CurrentPtr != NULL) {
				// Copy values of current node to new record.
			newRecord.firstName = CurrentPtr->firstName;
			newRecord.lastName = CurrentPtr->lastName;
			newRecord.address = CurrentPtr->address;
			newRecord.city = CurrentPtr->city;
			newRecord.state = CurrentPtr->state;
			newRecord.zipCode = CurrentPtr->zipCode;
			deleteRecord(record); // Delete the current record in the list
			switch (fieldNumber) { // Update the new record which will be added to the list
			case 1: newRecord.firstName = newVal;
				break;
			case 2: newRecord.lastName = newVal;
				break;
			case 3: newRecord.address = newVal;
				break;
			case 4: newRecord.city = newVal;
				break;
			case 5: newRecord.state = newVal;
				break;
			case 6: newRecord.zipCode = newVal;
				break;
			}
			insertRecord(newRecord); // Insert the updated record in the list
			return true;
		}
	// return a value that indicates the node was not found
	return false;
}
