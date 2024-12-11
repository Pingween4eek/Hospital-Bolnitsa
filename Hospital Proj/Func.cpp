#include <string>
#include "Patient.h"
#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include "send_message.h"
#include "receive_message.h"
#include "socket_wrapper.h"
#include <algorithm> 

using namespace std;

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string word;

    // Читаем слова из строки, разделенные пробелами
    while (stream >> word) {
        result.push_back(word);
    }

    return result;
}

SocketWrapper& operator>>(SocketWrapper& socket, Patient& pat) {
    std::string input;

    socket >> input;

    std::vector<std::string> words = split(input);
    for (int i = 0; i < words.size(); i++) {
        std::cout << words[i] << std::endl;
    }
    // Запрос ID
    //socket.send("Enter ID: ");
    

    pat._id = std::stoi(words[0]);

    // Запрос имени
    //socket.send("Enter name: ");
    pat._name = words[1];
    

    // Запрос фамилии
    //socket.send("Enter surname: ");
    pat._surname = words[2];

    // Запрос пола
    //socket.send("Enter gender: ");
    pat._gender = words[3];

    // Запрос возраста
    //socket.send("Enter age: ");

    pat._age = std::stoi(words[4]);

    // Запрос диагноза
    //socket.send("Enter diagnosis: ");
    pat._diagnosis = words[5];

    // Запрос статуса
    //socket.send("Enter status: ");
    pat._status = words[6];

    // Запрос врача
    //socket.send("Enter doctor: ");
    pat._doctor = words[7];

    // Запрос отдела
    //socket.send("Enter department: ");
    pat._department = words[8];

    // Запрос оставшихся дней
    //socket.send("Remaining days: ");
    pat._days = std::stoi(words[9]);

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