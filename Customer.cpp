#include "Customer.h"
#include <iostream>

Customer::Customer() {
	fname = "";
	lname = "";
	address = "";
	email = "";
	phoneNumber = "";
}
Customer::Customer(string _fname, string _lname, string _address, string _email, string _phone) {
	fname = _fname;
	lname = _lname;
	address = _address;
	email = _email;
	setPhone(_phone);
}
void Customer::setAll(string _fname, string _lname, string _address, string _email, string _phone) {
	setFname(_fname);
	setLname(_lname);
	setAddress(_address);
	setEmail(_email);
	setPhone(_phone);
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
void Customer::setEmail(string _email) {
	email = _email;
}
void Customer::setPhone(string _phone) {
	if (_phone.length() == 10) {
		phoneNumber = _phone;
	}
	else {
		phoneNumber = "0000000000";
	}
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
string Customer::getEmail() const {
	return email;
}
string Customer::getPhone() const {
	return phoneNumber;
}
void Customer::printInfo() {
	cout << "Customer:" << fname << " " << lname << endl <<
		"Address: " << address << endl <<
		"Contact through email: " << email << ", or call at: " << phoneNumber << endl;
}
