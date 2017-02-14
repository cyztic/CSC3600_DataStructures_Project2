#include <string>
#include <sstream>
#include <RecordClass2.h>
using namespace std;
class RecordClass {
public:

	RecordClass() {		firstName = "";
		lastName = "";
		sAddress = "";

	}

	void setFirstName(string setToThis) {
		firstName = setToThis;
	}
	void setLastName(string setToThis) {
		lastName = setToThis;
	}
	void setsAddress(string setToThis) {
		firstName = setToThis;
	}
	void setCity(string setToThis) {
		firstName = setToThis;
	}
	void setState(string setToThis) {
		firstName = setToThis;
	}
	void setZipCode(string setToThis) {
		firstName = setToThis;
	}


	string getFirstName() {
		return firstName;
	}
	string getLastName() {

	}
	string getsAddress() {

	}
	string getCity() {

	}
	string getState() {

	}
	string getZipCode() {

	}



private:
	string firstName;
	string lastName;
	string sAddress;
	string city;
	string state;
	string zipCode;



};