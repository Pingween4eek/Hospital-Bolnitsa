#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include <typeinfo>
#include <algorithm> 

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    std::string a;
    std::string message = "4";  // Используем std::string для сообщения
    std::string buffer;  // Используем std::string для буфера
    char recv_buffer[1024] = { 0 };  // Буфер для получения данных через recv()
    bool flag = false;

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Настройка адреса сервера
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Преобразование IP-адреса
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address or Address not supported" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::string b = "0";
    int c = stoi(b);
    while (true){
        // Считывание сообщения от сервера
        int recv_len = recv(sock, recv_buffer, 1024, 0);
        if (recv_len > 0) {
            
            buffer = std::string(recv_buffer, recv_len);  // Преобразуем в std::string
            if (buffer == "CLOSE") {
                closesocket(sock); // Закрываем текущее соединение

                // Создаем новый сокет и подключаемся снова
                if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
                    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
                    WSACleanup();
                    return 1;
                }
                if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
                    std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
                    closesocket(sock);
                    WSACleanup();
                    return 1;
                }


                std::cout << "Reconnected to the server." << std::endl;
                recv_len = recv(sock, recv_buffer, 1024, 0);
                if (recv_len > 0) {
                    buffer = std::string(recv_buffer, recv_len);
                    std::cout << "Message from server: " << buffer << std::endl;
                }
            }

            else if (buffer == "STOP") {
                break;
            }

            else if (buffer == "PATIENT") {
                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Id: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Name: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Surname: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Gender: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Age: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Diagnosis: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Status: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Doctor: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Department: " << buffer << std::endl;

                recv_len = recv(sock, recv_buffer, 1024, 0);
                buffer = std::string(recv_buffer, recv_len);
                std::cout << "Days: " << buffer << std::endl;

                //std::cout << "Enter 'ok' to continue" << std::endl;
                flag = true;
            }

            else
                std::cout << "Message from server: " << buffer << std::endl;
        }
        //std::string str = std::to_string(b);  // Преобразуем int в std::string
        //message = str.c_str();  // Преобразуем std::string в const char*

        if (!flag) {
            std::cin >> b;
            if (std::all_of(b.begin(), b.end(), std::isdigit)) {
                c = stoi(b);
            }
            else
                c = 0;
        }
        else {
            b = "next_action";
            flag = false;
        }

        message = b;
        //std::cout << typeid(b).name() << std::endl;
        std::replace(b.begin(), b.end(), '\n', ' ');
        // Отправка сообщения серверу
        send(sock, b.c_str(), b.length(), 0);  // Отправляем строку как массив символов
        //std::cout << "Message sent to server" << std::endl;

    }
    

    // Закрытие сокета
    closesocket(sock);
    WSACleanup();
    return 0;
}
