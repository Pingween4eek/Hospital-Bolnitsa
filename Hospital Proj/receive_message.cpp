#include "receive_message.h"
#include <iostream>

std::string receiveMessage(SOCKET client_socket) {
    char buffer[1024] = { 0 };  // ����� ��� ��������� ���������
    int recvResult = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (recvResult == SOCKET_ERROR) {
        std::cerr << "Failed to receive message: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        return "ERROR001RECEIVE";
    }
    else if (recvResult == 0) {
        std::cout << "Connection closed by client." << std::endl;
        closesocket(client_socket);
        return "ERROR001RECEIVE";
    }
    std::cout << "Client message: " << std::string(buffer, recvResult) << std::endl;

    return std::string(buffer, recvResult);  // ����������� char[] � std::string � ����������
}