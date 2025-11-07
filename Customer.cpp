#include "Customer.h"
#include <iostream>
#include <iomanip>

Customer::Customer() {
	fname = "";
	lname = "";
	address = "";
	phoneNumber = "";
	email = "";
}
Customer::Customer(string _fname, string _lname, string _address, string _phone, string _email) {
	fname = _fname;
	lname = _lname;
	address = _address;
	setPhone(_phone);
	email = _email;
}

void Customer::setAll(string _fname, string _lname, string _address, string _phone, string _email) {
	setFname(_fname);
	setLname(_lname);
	setAddress(_address);
	setPhone(_phone);
	setEmail(_email);
}
void Customer::setFname(string _fname) {
	fname = _fname;
}
void Customer::setLname(string _lname) {
	lname = _lname;
}
void Customer::setAddress(string _address) {
	address = _address;
}
void Customer::setPhone(string _phone) {
	if (_phone.length() == 10) {
		phoneNumber = _phone;
	}
	else {
		phoneNumber = "0000000000";
	}
}
void Customer::setEmail(string _email) {
	email = _email;
}

string Customer::getFname() const {
	return fname;
}
string Customer::getLname() const {
	return lname;
}
string Customer::getAddress() const {
	return address;
}
string Customer::getPhone() const {
	return phoneNumber;
}
string Customer::getEmail() const {
	return email;
}

void Customer::printInfo() {
	cout << left << setw(20) << fname << left << setw(20) << lname << left << setw(30) << address.substr(0,15) << left << setw(20) << phoneNumber << left << setw(20) << email << endl;
}
