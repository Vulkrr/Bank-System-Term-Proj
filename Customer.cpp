#include "Customer.h"
#include <iostream>
#include <iomanip>

Customer::Customer() {
	fname = "";
	lname = "";
	address = "";
	phoneNumber = 0;
	formattedPhoneNumber = "";
	email = "";
}
Customer::Customer(string _fname, string _lname, string _address, int _phone, string _email) {
	fname = _fname;
	lname = _lname;
	address = _address;
	setPhone(_phone);
	email = _email;
}

void Customer::setAll(string _fname, string _lname, string _address, int _phone, string _email) {
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
void Customer::setPhone(int _phone) {
	string tempPhone = to_string(_phone);
	if (tempPhone.length() == 10) {
		phoneNumber = _phone;
	}
	else {
		phoneNumber = 0;
	}
	formattedPhoneNumber = tempPhone.substr(0, 3) + "-" + tempPhone.substr(3, 3) + "-" + tempPhone.substr(6);
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
int Customer::getPhone() const {
	return phoneNumber;
}
string Customer::getEmail() const {
	return email;
}

void Customer::printInfoFull() {

	cout << "Name: " << fname << " " << lname << endl;
	cout << "Address: " << address << endl;
	cout << "Phone #: " << to_string(phoneNumber).substr(0, 3) << "-" << to_string(phoneNumber).substr(3, 3) << left << "-" << to_string(phoneNumber).substr(7) << endl;
	cout << "Email: " << email << endl;
}

void Customer::printInfoPartial() {
	cout << left << setw(20) << fname << left << setw(20) << lname << left << setw(30) << address.substr(0, 15) << left << setw(20) << formattedPhoneNumber << left << setw(20) << email << endl;
}
