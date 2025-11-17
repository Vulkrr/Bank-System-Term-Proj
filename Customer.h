#pragma once
#ifndef _CUSTOMER_
#define _CUSTOMER_
#include <string>
using namespace std;

class Customer {
	string fname, lname, address, email, phoneNumber, formattedPhoneNumber;
public:
	Customer();
	Customer(string _fname, string _lname, string _address, string _phone, string _email);

	void setAll(string _fname, string _lname, string _address, string _phone, string _email);
	void setFname(string _fname);
	void setLname(string _lname);
	void setAddress(string _address);
	void setPhone(string _phone);
	void setEmail(string _email);

	string getFname() const;
	string getLname() const;
	string getAddress() const;
	string getPhone() const;
	string getEmail() const;

	void printInfoFull();
	void printInfoPartial();
};
#endif // !_CUSTOMER_
