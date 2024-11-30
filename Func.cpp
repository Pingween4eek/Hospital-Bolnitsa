#include <string>
#include "Patient.h"
#include <list>
#include <iostream>
#include <vector>
#include "send_message.h"
#include "receive_message.h"
#include "socket_wrapper.h"
#include <algorithm> 

using namespace std;


SocketWrapper& operator>>(SocketWrapper& socket, Patient& pat) {
    std::string input;

    // Запрос ID
    socket.send("Enter ID: ");
    socket >> input;

    int id;
    if (std::all_of(input.begin(), input.end(), std::isdigit)) {
        id = std::stoi(input);
    }
    else {
        id = -1;
    }
    while (id < 0) {
        socket.send("Incorrect ID! Enter ID: ");
        socket >> input;

        if (std::all_of(input.begin(), input.end(), std::isdigit)) {
            id = std::stoi(input);
        }
        else {
            id = -1;
        }
    }
    pat._id = id;

    // Запрос имени
    socket.send("Enter name: ");
    std::string name;

    socket >> name;

    while (true) {
        if (std::all_of(name.begin(), name.end(), std::isdigit) && name != "75") {
            socket.send("Incorrect name! Enter name: ");
            socket >> name;
        }
        else
            break;
    }

    pat._name = name;
    

    // Запрос фамилии
    socket.send("Enter surname: ");
    std::string surname;

    socket >> surname;

    while (true) {
        if (std::all_of(surname.begin(), surname.end(), std::isdigit) && surname != "75") {
            socket.send("Incorrect surname! Enter surname: ");
            socket >> surname;
        }
        else
            break;
    }

    pat._surname = surname;

    // Запрос пола
    socket.send("Enter gender: ");
    socket >> pat._gender;

    // Запрос возраста
    socket.send("Enter age: ");
    socket >> input;

    int age;
    if (std::all_of(input.begin(), input.end(), std::isdigit)) {
        age = std::stoi(input);
    }
    else {
        age = -1;
    }
    while (age < 0 || age > 120) {
        socket.send("Incorrect age! Enter age: ");
        socket >> input;

        if (std::all_of(input.begin(), input.end(), std::isdigit)) {
            age = std::stoi(input);
        }
        else {
            age = -1;
        }
    }
    pat._age = age;

    // Запрос диагноза
    socket.send("Enter diagnosis: ");
    socket >> pat._diagnosis;

    // Запрос статуса
    socket.send("Enter status: ");
    socket >> pat._status;

    // Запрос врача
    socket.send("Enter doctor: ");
    socket >> pat._doctor;

    // Запрос отдела
    socket.send("Enter department: ");
    socket >> pat._department;

    // Запрос оставшихся дней
    socket.send("Remaining days: ");
    socket >> input;

    int days;
    if (std::all_of(input.begin(), input.end(), std::isdigit)) {
        days = std::stoi(input);
    }
    else {
        days = -1;
    }
    while (days <= 0 || days > 365) {
        socket.send("Incorrect days! Enter days: ");
        socket >> input;

        if (std::all_of(input.begin(), input.end(), std::isdigit)) {
            days = std::stoi(input);
        }
        else {
            days = -1;
        }
    }
    pat._days = days;

    return socket;
}

istream& operator >>(istream& in, Patient& pat) {
    in >> pat._id;
    in >> pat._name;
    in >> pat._surname;
    in >> pat._gender;
    in >> pat._age;
    in >> pat._diagnosis;
    in >> pat._status;
    in >> pat._doctor;
    in >> pat._department;
    in >> pat._days;

    return in;
}

SocketWrapper& operator<<(SocketWrapper& socket, Patient& pat) {
    std::string id = std::to_string(pat._id);
    socket << id;
        
    socket << pat._name;
    socket << pat._surname;
    socket << pat._gender;

    std::string age = std::to_string(pat._age);
    socket << age;

    socket << pat._diagnosis;
    socket << pat._status;
    socket << pat._doctor;
    socket << pat._department;

    std::string days = std::to_string(pat._days);
    socket << days;

    return socket;
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