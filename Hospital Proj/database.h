#pragma once

#include <vector>
#include "Patient.h"

inline std::string to_lower(const std::string& str);

namespace patient_db {
	void create_patients(std::vector<Patient> *arr);
	void write_patients(std::vector<Patient> arr);
	void read_patients(std::vector<Patient> *arr);
	void add_patient(std::vector<Patient> *arr);
	void search_patient(std::vector<Patient> arr);
	void delete_patient(std::vector<Patient> *arr);
	void advance_time(std::vector<Patient> *arr, int days);
	void print_patients(std::vector<Patient> arr);
}
