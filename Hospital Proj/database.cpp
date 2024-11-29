#include <iostream>
#include <string>
#include <fstream>
#include "database.h"
#include "Patient.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <algorithm> 
#include "send_message.h"
#include "receive_message.h"
#include <typeinfo>

bool flag = true;

std::string to_lower(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}


namespace patient_db{
    void create_patients(SOCKET *client_socket, std::vector<Patient>* arr) {
        SocketWrapper client(*client_socket);

        const char* message = "Enter number of patients = ";
        sendMessage(client_socket, message);
        
        int n;
        //std::cout << "Enter number of patients = ";
        //std::cin >> n;
        //std::string nt = receiveMessage(client_socket);
        //std::cout << nt << std::endl;
        std::string nt = receiveMessage(*client_socket);
        //std::cout << typeid(nt).name() << std::endl;
        if (std::all_of(nt.begin(), nt.end(), std::isdigit) && (!nt.empty())) {
            //std::cout << typeid(nt).name() << std::endl;
            n = stoi(nt);
            //std::cout << typeid(n).name() << std::endl;
        }
            
        else {
            std::cout << "N not digit" << std::endl;
            n = 0;
        }
        //if (n <= 0) return;

        arr->clear();
        Patient patient;
        for (int i = 0; i < n; i++) {
            //client >> patient;
            client >> patient;
            arr->push_back({ patient });
        }

        //std::cout << "func client_socket = " << client_socket << std::endl;
        write_patients(*arr);
         // Завершение работы с клиентом, закрываем сокет
        sendMessage(client_socket, "CLOSE");
        closesocket(*client_socket);
        std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета
    }
    void write_patients(std::vector<Patient> arr) {
        if (arr.empty()) return;

        std::ofstream out;
        out.open("patients.txt");
        if (!out) return;

        int n = arr.size();
        out << n << std::endl;

        for (int i = 0; i < n; i++) {
            out << arr[i] << std::endl;
        }

        out.close();
    }

    void read_patients(std::vector<Patient>* arr) {
        //SocketWrapper client(client_socket);
        std::ifstream in("patients.txt");
        if (!in) return;

        int n;
        in >> n;
        if (n <= 0) return;

        *arr = {};
        Patient patient;
        for (int i = 0; i < n; i++) {
            in >> patient;
            arr->push_back({ patient });
        }

        in.close();
    }

    void add_patient(SOCKET* client_socket, std::vector<Patient>* arr) {
        SocketWrapper client(*client_socket);
        if (arr->empty()) {
            sendMessage(client_socket, "First create list of patient with command 'create'");
            std::string pusto = receiveMessage(*client_socket);
            sendMessage(client_socket, "CLOSE");
            closesocket(*client_socket);
            std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета

            return;
        }

        Patient patient;
        client >> patient;
        arr->push_back(patient);
        sendMessage(client_socket, "Patient added successfully.");
        std::string pusto = receiveMessage(*client_socket);
        sendMessage(client_socket, "CLOSE");
        closesocket(*client_socket);
        std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета
    }
    

    void delete_patient(SOCKET* client_socket, std::vector<Patient>* arr) {
        SocketWrapper client(*client_socket);

        if (arr->empty()) {
            sendMessage(client_socket, "List of patients doesnt exist");
            std::string pusto = receiveMessage(*client_socket);

            sendMessage(client_socket, "CLOSE");
            closesocket(*client_socket);
            std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета

            return;
        }

        sendMessage(client_socket, "Enter the surname of patient you want to delete: ");
        std::string patient = receiveMessage(*client_socket);
        int id;
        int n = arr->size();
        patient = to_lower(patient);
        bool flag = false;

        for (int i = 0; i < n; i++) {
            if (patient == to_lower((*arr)[i].getSurname())) {
                id = i;
                flag = true;
            }
        }
        if (flag) {
            sendMessage(client_socket, "Patient was delete, enter 'ok' to continue");
            arr->erase(arr->begin() + id);
            std::string pusto = receiveMessage(*client_socket);
        }

        else {
            sendMessage(client_socket, "This patient doesn't exist");
            sendMessage(client_socket, "CLOSE");
            closesocket(*client_socket);
            std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета
            return;
        }
        sendMessage(client_socket, "CLOSE");
        closesocket(*client_socket);
        std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета
    }

    void search_patient(SOCKET* client_socket, std::vector<Patient> arr) {
        SocketWrapper client(*client_socket);

        if (arr.empty()) {
            sendMessage(client_socket, "First create list of patients with command 'create' Print 'ok' to continue");
            std::string pusto = receiveMessage(*client_socket);

            sendMessage(client_socket, "CLOSE");
            closesocket(*client_socket);
            std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета

            return;
        }
    
        sendMessage(client_socket, "What patient you looking for? (Enter surname): ");
        std::string patient = receiveMessage(*client_socket);

        patient = to_lower(patient);
        bool flag = false;
        int id = -1;
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            if (patient == to_lower(arr[i].getSurname())) {
                id = i;
                flag = true;
            }
        }
        if (flag) {
            sendMessage(client_socket, "PATIENT");
            std::cout << arr[id];
            client << arr[id];
            std::string pusto = receiveMessage(*client_socket);
        }
        else {
            std::cout << "There are no matches" << std::endl;
            sendMessage(client_socket, "CLOSE");
            closesocket(*client_socket);
            std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета

            return;
        }
        sendMessage(client_socket, "CLOSE");
        closesocket(*client_socket);
        std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета
    }

    void print_patients(SOCKET* client_socket, std::vector<Patient> arr) {
        if (arr.empty()) {
            sendMessage(client_socket, "First create list of patients with command 'create' Print 'ok' to continue");
            std::string pusto = receiveMessage(*client_socket);

            sendMessage(client_socket, "CLOSE");
            closesocket(*client_socket);
            std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета

            return;
        }

        SocketWrapper client(*client_socket);
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            sendMessage(client_socket, "PATIENT");
            std::cout << arr[i];
            client << arr[i];
            std::string pusto = receiveMessage(*client_socket);
        }

        sendMessage(client_socket, "CLOSE");
        closesocket(*client_socket);
        std::cout << "Client connection closed. Waiting for reconnection..." << std::endl; //сообщ клиенту о закрытии сокета
    }
}