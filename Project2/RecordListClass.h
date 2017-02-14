#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <string>
#include <sstream>
using namespace std;
struct RecordType {

	string firstName, lastName, address, city, state, zipCode;

	RecordType *recordPtr;
	RecordType *next;
};
class RecordListClass {
public:

	RecordListClass();
	void insertRecord(RecordType);
	void printRecords(ofstream&,int&,int&);
	bool deleteRecord(RecordType record);
	bool changeRecord(RecordType, int, string);
	
private:
	
	RecordType *StartPtr;

};
RecordListClass::RecordListClass() {
	StartPtr = NULL;
}
void RecordListClass::insertRecord(RecordType record){
		// Declare local pointers
	RecordType *newPtr, *PreviousPtr, *CurrentPtr;
		// Reserve memory for a new node
	newPtr = new(RecordType);
		// if there is no free memory, print an error message
	if (newPtr == NULL)
		int i = 0; // Need to replace this with error message *****************
	else {  // Otherwise, place the data in a new node
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
		while ((CurrentPtr != NULL) &&(newPtr->lastName.compare(CurrentPtr->lastName) > 0 )){
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
		}
			// If both last names are the same, 
		while ((CurrentPtr != NULL) && (newPtr->lastName.compare(CurrentPtr->lastName) == 0) 
			&& (newPtr->firstName.compare(CurrentPtr->firstName) > 0)){
				PreviousPtr = CurrentPtr;
				CurrentPtr = CurrentPtr->next;
		}
			// if no list exist, place new node at the start of the list
		if (PreviousPtr == NULL)
		{
			newPtr->next = StartPtr;
			StartPtr = newPtr;
		}
		else
		{	// insert the new node into the list
			PreviousPtr->next = newPtr;
			newPtr->next = CurrentPtr;
		}
		}
		return;
}
void RecordListClass::printRecords(ofstream&Outfile,int&lineCount,int&MAXLINECOUNT){
	RecordType  *CurrentPtr;
		// Initialize a current pointer to the start of the linked list
	CurrentPtr = StartPtr;
		// Check for an Empty List
	if (CurrentPtr == NULL)	{
		Outfile << "List is Empty" << endl;
		return;
	} 
		// Print a data header
	Outfile << "              MAILING LIST" << endl;
	Outfile << "Last Name   First Name  Address             City";
	Outfile << "        State Zip Code" << endl;
	Outfile << "======================================================================" << endl;
	lineCount += 3; // Increment the line count by 3
		// Print each member of the list
	while (CurrentPtr != NULL)
	{                               //  Print the data
		Outfile << CurrentPtr->lastName << CurrentPtr->firstName;		
		Outfile << CurrentPtr->address << CurrentPtr->city;
		Outfile << CurrentPtr->state << "    " << CurrentPtr->zipCode << endl;
		lineCount ++; // Increment the line count for each record
			//  Move to the next NODE
		CurrentPtr = CurrentPtr->next;
	}
	return;
}

bool RecordListClass::deleteRecord(RecordType record){
	RecordType *tempPtr, *PreviousPtr, *CurrentPtr;
		//If the record to be deleted is the first record, reset the starting pointer
	if (record.lastName.compare(StartPtr->lastName) == 0 
		&& record.firstName.compare(StartPtr->firstName)==0) {
		tempPtr = StartPtr;
		StartPtr = StartPtr->next;
		delete (tempPtr);
		return true;
	}
	else { 		// initialize local pointers to search for the node to be deleted
		PreviousPtr = StartPtr;
		CurrentPtr = StartPtr->next;
		//  step through the list until  the delete node is found or the list is exhausted
		while ((CurrentPtr != NULL) && (record.lastName.compare(CurrentPtr->lastName) != 0
			&& record.firstName.compare(CurrentPtr->firstName) != 0))
		{
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
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
bool RecordListClass::changeRecord(RecordType record,int fieldNumber,string newVal) {
	RecordType *tempPtr, *PreviousPtr, *CurrentPtr;
	//If the record to be deleted is the first record, reset the starting pointer
	if (record.lastName.compare(StartPtr->lastName) == 0
		&& record.firstName.compare(StartPtr->firstName) == 0) {
		switch (fieldNumber) {
		case 1: StartPtr->firstName = newVal;
		case 2: StartPtr->lastName = newVal;
		case 3: StartPtr->address = newVal;
		case 4: StartPtr->city = newVal;
		case 5: StartPtr->state = newVal;
		case 6: StartPtr->zipCode = newVal;
		default: return false;
		}
		return true;
	}
	else { 		// initialize local pointers to search for the node to be changed
		PreviousPtr = StartPtr;
		CurrentPtr = StartPtr->next;
		
		//  step through the list until  the change node is found or the list is exhausted
		//while ((CurrentPtr != NULL) && (record.firstName.compare(CurrentPtr->firstName) != 0) && (record.lastName.compare(CurrentPtr->lastName) != 0))
		while ((CurrentPtr != NULL) && (record.firstName != CurrentPtr->firstName) && (record.lastName != CurrentPtr->lastName)){
			PreviousPtr = CurrentPtr;
			CurrentPtr = CurrentPtr->next;
		}

		if (record.firstName.compare(CurrentPtr->firstName) != 0) {
			int e = 0;
		}







		//  if the node is found, set the new value to the specified field to be changed
		if (CurrentPtr != NULL){			
			switch (fieldNumber) {
				case 1: CurrentPtr->firstName = newVal;
					break;
				case 2: CurrentPtr->lastName = newVal;
					break;
				case 3: CurrentPtr->address = newVal;
					break;
				case 4: CurrentPtr->city = newVal;
					break;
				case 5: CurrentPtr->state = newVal;
					break;
				case 6: CurrentPtr->zipCode = newVal;
					break;
				default: return false;
				}
		return true;
		}
	}
	// return a value that indicates the node was not found
	return false;
}




