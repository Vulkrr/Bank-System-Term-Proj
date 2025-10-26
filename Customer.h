#pragma once
#ifndef _CUSTOMER_
#define _CUSTOMER_
#include <string>
using namespace std;

class Customer {
	string fname, lname, address, email, phoneNumber;
public:
	Customer();
	Customer(string _fname, string _lname, string _address, string _email, string _phone);

	void setAll(string _fname, string _lname, string _address, string _email, string _phone);
	void setFname(string _fname);
	void setLname(string _lname);
	void setAddress(string _address);
	void setEmail(string _email);
	void setPhone(string _phone);

	string getFname() const;
	string getLname() const;
	string getAddress() const;
	string getPhone() const;
	string getEmail() const;

	void printInfo();
};
#endif // !_CUSTOMER_
