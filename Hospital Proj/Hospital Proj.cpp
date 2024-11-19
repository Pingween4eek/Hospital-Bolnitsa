#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sstream>
#include "Patient.h"
#include "database.h"
#include "time.h"
#include "send_message.h"
#include "receive_message.h"
#include <algorithm> 
#include <typeinfo>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

using namespace std;

int main() {
	WSADATA wsaData;
	SOCKET server_socket;
	SOCKET client_socket;
	struct sockaddr_in server_addr, client_addr;
	int client_addr_len = sizeof(client_addr);
	std::string buffer;  // Используем std::string для буфера
	const char* message = "1-Patient 2-advance time 3-exit programm";
	char recv_buffer[1024] = { 0 };  // Буфер для получения данных через recv()

	int key = 0;
	bool w;
	bool moment = true;
	vector<Patient> temp;

	// Инициализация Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
		return 1;
	}

	// Создание сокета
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	// Настройка адреса сервера
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	// Привязка сокета к IP-адресу и порту
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}

	// Прослушивание входящих подключений
	if (listen(server_socket, 3) == SOCKET_ERROR) {
		std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}

	std::cout << "Waiting for connections..." << std::endl;

	// Принятие подключения клиента
	if ((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len)) == INVALID_SOCKET) {
		std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}

	int key_pat;
	const char* message_2 = "1 - Create, 2 - write, 3 - read, 4 - add, 5 - search, 6 - delete, 7 - print, 8 - exit";
	while (key != 3) {
		// Отправка сообщения клиенту
		moment = true;
		sendMessage(&client_socket, message);
		//send(client_socket, message, strlen(message), 0);
		//std::cout << "Message sent to client" << std::endl;

		// Чтение сообщения от клиента
		std::string key_st = receiveMessage(client_socket);
		if ((std::all_of(key_st.begin(), key_st.end(), std::isdigit)) && (!key_st.empty())) {
			//std::cout << typeid(key_st).name() << std::endl;
			key = stoi(key_st);
		}
		else {
			key = 3;
			std::cout << "error" << std::endl;
		}

		//key = stoi(receiveMessage(client_socket));
		//int recv_len = recv(client_socket, recv_buffer, 1024, 0);  // Получаем данные в char[]
		//if (recv_len > 0) {
			//buffer = std::string(recv_buffer, recv_len);  // Преобразуем в std::string
			
		std::cout << "Message from client: " << key << std::endl;
		//}
		while (moment) {
			switch (key) {
			case 1:
			{
				w = true;
				while (w) {
					//int key_pat;
					//const char* message_2 = "1 - Create, 2 - write, 3 - read, 4 - add, 5 - search, 6 - delete, 7 - print, 8 - exit";
					//std::cout << "client_socket = " << client_socket << std::endl;
					sendMessage(&client_socket, message_2);
					//send(client_socket, message_2, strlen(message_2), 0);
					//cout << "1 - Create, 2 - write, 3 - read, 4 - add, 5 - search, 6 - delete, 7 - print, 8 - exit" << endl;
					//if (recv_len > 0) {
						//buffer = std::string(recv_buffer, recv_len);  // Преобразуем в std::string
						//key_pat = stoi(buffer);
						//std::cout << "Message from client: " << buffer << std::endl;
					//}
					std::string key_pat_st = receiveMessage(client_socket);
					//std::replace(key_pat_st.begin(), key_pat_st.end(), '\n', ' ');

					if (std::all_of(key_pat_st.begin(), key_pat_st.end(), std::isdigit) && (!key_pat_st.empty())) {
						//std::cout << typeid(key_pat_st).name() << std::endl;
						key_pat = stoi(key_pat_st);
					}
					else {				
						std::cout << "key_pat_st: " << key_pat_st << std::endl;
						//continue;
						std::string cache = receiveMessage(client_socket);
						key_pat = 11;
						std::cout << "error 2" << std::endl;
						w = false;
						moment = false;
					}

					if (!key_pat) {
						cout << "Error" << endl;
						break;
					}
					switch (key_pat) {
					case 1:

						patient_db::create_patients(&client_socket, &temp);
						client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
						//Проверка подключения
						if (client_socket == INVALID_SOCKET) {
							std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
							closesocket(server_socket);
							WSACleanup();
							return 1;
						}
						
						break;
					case 2:
						patient_db::write_patients(temp);
						break;
					case 3:
						patient_db::read_patients(&temp);
						break;
					case 5:
					{
						patient_db::search_patient(&client_socket, temp);
						client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
						//Проверка подключения
						if (client_socket == INVALID_SOCKET) {
							std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
							closesocket(server_socket);
							WSACleanup();
							return 1;
						}
						break;
					}
					case 4:

						patient_db::add_patient(&client_socket, &temp);
						client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
						//Проверка подключения
						if (client_socket == INVALID_SOCKET) {
							std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
							closesocket(server_socket);
							WSACleanup();
							return 1;
						}

						break;

					case 6:
						patient_db::delete_patient(&client_socket, &temp);
						client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
						//Проверка подключения
						if (client_socket == INVALID_SOCKET) {
							std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
							closesocket(server_socket);
							WSACleanup();
							return 1;
						}

						break;
					case 7:
						patient_db::print_patients(&client_socket, temp);
						break;
					default:
						w = false;
						moment = false;
						break;
					}
				}
				break;
			}
			case 2:
			{
				patient_db::read_patients(&temp);

				if (temp.empty()) {
					const char* message_3 = "First create list of patients with command 'create'";
					std::cout << "okak" << std::endl;
					send(client_socket, message_3, strlen(message_3), 0);
					//std::cout << "First create list of patients with command 'create'" << std::endl;
				}				
				else
					for (int i = 0; i < temp.size(); i++) {
						temp[i].advance_day();
						patient_db::write_patients(temp);
					}

				break;
			}
			default: {
				moment = false;
				sendMessage(&client_socket, "STOP");
				break;

			}
			}
		}
	}

	

	// Закрытие сокетов
	closesocket(client_socket);
	closesocket(server_socket);
	WSACleanup();

	return 0;
}
