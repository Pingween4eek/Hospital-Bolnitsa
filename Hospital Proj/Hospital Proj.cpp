#include <iostream>
#include "Patient.h"
#include "database.h"
#include "time.h"

using namespace std;

int main() {
	int key = 0;
	bool w;
	bool moment = true;
	vector<Patient> temp;

	key = 0;
	while (moment) {
		cout << endl << "1-Patient 2-advance time 3-exit programm" << endl;
		if (!(std::cin >> key).good()) {
			cout << "Error" << endl;
			return 0;
		}
		switch (key) {
		case 1:
		{
			w = true;
			while (w) {
				int key_pat;
				cout << "1 - Create, 2 - write, 3 - read, 4 - add, 5 - search, 6 - delete, 7 - print, 8 - exit" << endl;
				std::cin >> key_pat;
				if (!key_pat) {
					cout << "Error" << endl;
					break;
				}
				switch (key_pat) {
				case 1:
					patient_db::create_patients(&temp);
					break;
				case 2:
					patient_db::write_patients(temp);
					break;
				case 3:
					patient_db::read_patients(&temp);
					break;
				case 5:
				{
					patient_db::search_patient(temp);
					break;
				}
				case 4:

					patient_db::add_patient(&temp);
					break;
				case 6:
					patient_db::delete_patient(&temp);
					break;
				case 7:
					patient_db::print_patients(temp);
					break;
				default:
					w = false;
					break;
				}
			}
		}
		case 2:
		{
			patient_db::read_patients(&temp);

			if (temp.empty())
				std::cout << "First create list of patients with command 'create'" << std::endl;
			else 
				for (int i = 0; i < temp.size(); i++) {
					temp[i].advance_day();
					patient_db::write_patients(temp);
				}		

			break;
		}
		default: {
			moment = false;
			break;

		}
		}
	}
}
