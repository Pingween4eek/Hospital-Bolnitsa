#pragma once

#include <winsock2.h>
#include <string>

class SocketWrapper {
public:
    explicit SocketWrapper(SOCKET clientSocket);   // ����������� ��� ������������� ������
    ~SocketWrapper();                              // ���������� ��� �������� ������

    // ����� ��� �������� ���������
    void send(const std::string& message);

    // ���������� ��������� >> ��� ������ ������
    SocketWrapper& operator>>(std::string& message);
    SocketWrapper& operator<<(std::string& message);

private:
    SOCKET clientSocket;
};
