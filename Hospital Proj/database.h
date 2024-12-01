#pragma once

#include <vector>
#include "Patient.h"
#include <iostream>
#include <winsock2.h>
#include <string>

inline std::string to_lower(const std::string& str);

namespace patient_db {
	std::string create_patients(SOCKET *client_socket, std::vector<Patient> *arr);
	void write_patients(std::vector<Patient> arr);
	void read_patients(std::vector<Patient> *arr);
	std::string add_patient(SOCKET* client_socket, std::vector<Patient> *arr);
	std::string search_patient(SOCKET* client_socket, std::vector<Patient> arr);
	std::string delete_patient(SOCKET* client_socket, std::vector<Patient> *arr);
	void advance_time(std::vector<Patient> *arr, int days);
	std::string print_patients(SOCKET* client_socket, std::vector<Patient> arr);
}
