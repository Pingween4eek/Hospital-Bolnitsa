#include <string>
#include "Patient.h"
#include <list>
#include <iostream>
#include <vector>

using namespace std;

istream& operator >>(istream& in, Patient& pat) {
	cout << "Enter id:";
	int id;
	in >> id;
	while (id < 0 ) {
		std::cout << "Incorrect Id!" << std::endl;
		cout << "Enter id:";
		in >> id;
	}
	pat._id = id;
	cout << "Enter name:";
	in >> pat._name;
	cout << "Enter surname:";
	in >> pat._surname;
	cout << "Enter gender:";
	in >> pat._gender;
	cout << "Enter age:";
	int age;
	in >> age;
	while (age < 0 || age > 120) {
		std::cout << "Incorrect Age!" << std::endl;
		cout << "Enter age:";
		in >> age;
	}
	pat._age = age;
	cout << "Enter diagnosis:";
	in >> pat._diagnosis;
	cout << "Enter status:";
	in >> pat._status;
	cout << "Enter doctor:";
	in >> pat._doctor;
	cout << "Enter department:";
	in >> pat._department;
	cout << "Remaining days: ";
	int days;
	in >> days;
	while (days < 0 || days > 365) {
		std::cout << "Incorrect days!" << std::endl;
		cout << "Remaining days: ";
		in >> days;
	}
	pat._days = days;
	return in;
}

ostream& operator <<(ostream& out, Patient& pat) {
	cout << " Id: ";
	out << pat._id << endl;
	cout << " Name: ";
	out << pat._name << endl;
	cout << " Surname: ";
	out << pat._surname << endl;
	cout << " Gender: ";
	out << pat._gender << endl;
	cout << " Age: ";
	out << pat._age << endl;
	cout << " Diagnosis: ";
	out << pat._diagnosis << endl;
	cout << " Status: ";
	out << pat._status << endl;
	cout << " Doctor: ";
	out << pat._doctor << endl;
	cout << " Department: ";
	out << pat._department << endl;
	cout << "Days:";
	out << pat._days << endl;
	return out;
}