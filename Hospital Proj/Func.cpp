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

    // ������ ID
    socket.send("Enter ID: ");
    socket >> input;

    int id;
    if (std::all_of(input.begin(), input.end(), std::isdigit)) {
        std::cout << typeid(input).name() << std::endl;
        id = std::stoi(input);
    }
    else {
        id = 0;
        std::cout << "incorect" << std::endl;
    }
    while (id < 0) {
        socket.send("Incorrect ID! Enter ID: ");
        socket >> input;
        std::cout << typeid(input).name() << std::endl;
        id = std::stoi(input);
    }
    pat._id = id;

    // ������ �����
    socket.send("Enter name: ");
    socket >> pat._name;

    // ������ �������
    socket.send("Enter surname: ");
    socket >> pat._surname;

    // ������ ����
    socket.send("Enter gender: ");
    socket >> pat._gender;

    // ������ ��������
    socket.send("Enter age: ");
    socket >> input;
    int age = std::stoi(input);
    while (age < 0 || age > 120) {
        socket.send("Incorrect age! Enter age: ");
        socket >> input;
        std::cout << typeid(input).name() << std::endl;
        age = std::stoi(input);
    }
    pat._age = age;

    // ������ ��������
    socket.send("Enter diagnosis: ");
    socket >> pat._diagnosis;

    // ������ �������
    socket.send("Enter status: ");
    socket >> pat._status;

    // ������ �����
    socket.send("Enter doctor: ");
    socket >> pat._doctor;

    // ������ ������
    socket.send("Enter department: ");
    socket >> pat._department;

    // ������ ���������� ����
    socket.send("Remaining days: ");
    socket >> input;
    int days = std::stoi(input);
    while (days < 0 || days > 365) {
        socket.send("Incorrect days! Remaining days: ");
        socket >> input;
        std::cout << typeid(input).name() << std::endl;
        days = std::stoi(input);
    }
    pat._days = days;

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