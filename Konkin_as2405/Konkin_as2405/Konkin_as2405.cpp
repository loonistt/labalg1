#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipeline {
	string title;
	double length;
	double diameter;
	bool fixing = false;
};

struct compressorstation {
	string title;
	int workshop;
	int activeworkshop;
	float points;
};

void showMenu() {
	cout << "Menu: \n";
	cout << "1. Add a pipe \n";
	cout << "2. Add a compressor station \n";
	cout << "3. View all objects \n";
	cout << "4. Edit a pipe \n";
	cout << "5. Edit a compressor station \n";
	cout << "6. Save to file \n";
	cout << "7. Load from file \n";
	cout << "0. Exit \n\n";
	cout << "Please select an menu number :";
}

void errcheck() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(500, '\n');
		cout << "Wrong value!!!\n";
	}
}

void addPipe(pipeline& pipe) {
	cout << "Write the pipe name: ";
	getline(cin >> ws, pipe.title);

	while (true) {
		cout << "\nWrite the length of the pipe (m): ";
		cin >> pipe.length;

		errcheck();
		if (pipe.length <= 0) {
			cout << "Length cannot be less than 0 meters or equal to 0.\n";
		}
		else if (pipe.length > 600) {
			cout << "Length cannot be more than 600 meters.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nWrite the diameter of the pipe (mm): ";
		cin >> pipe.diameter;

		errcheck();
		if (pipe.diameter <= 0) {
			cout << "Diameter cannot be less than 0 millimeters or equal to 0.\n";
		}
		else if (pipe.diameter > 1220) {
			cout << "Diameter cannot be more than 1220 millimeters.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nChoose the status of the pipe: 0 - in service, 1 - at work: ";
		cin >> pipe.fixing;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value, choose 0 or 1.\n";
		}
		else {
			break;
		}
	}
}

void addCs(compressorstation& cs) {
	cout << "Write the compressor station name: ";
	getline(cin >> ws, cs.title);

	while (true) {
		cout << "\nWrite the workshops number: ";
		cin >> cs.workshop;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value!!!\n";
		}
		else if (cs.workshop <= 0) {
			cout << "Number cannot be less than 0 or equal to 0\n";
		}
		else if (cs.workshop > 100) {
			cout << "Number cannot be more than 100.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nWrite the active workshops number: ";
		cin >> cs.activeworkshop;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value!!!\n";
		}
		else if (cs.activeworkshop < 0) {
			cout << "Number cannot be less than 0.\n";
		}
		else if (cs.activeworkshop > cs.workshop) {
			cout << "Number cannot be more than the number of workshops.\n";
		}
		else {
			break;
		}
	}

	while (true) {
		cout << "\nWrite the points of the compressor station: ";
		cin >> cs.points;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value!!!\n";
		}
		else if (cs.points > 100) {
			cout << "Points must be in range from 0 to 100.";
		}
		else if (cs.points < 0) {
			cout << "Points must be in range from 0 to 100.";
		}
		else {
			break;
		}
	}
}

ostream& operator << (ostream& out, const pipeline& pipe) {
	out << "Pipelines information:\n\n"
		<< "Title: " << pipe.title
		<< "\nLength: " << pipe.length
		<< "\nDiameter: " << pipe.diameter
		<< "\nStatus: " << ((pipe.fixing) ? "not " : "") << "in service\n\n\n";
	return out;
}

ostream& operator << (ostream& out, const compressorstation& cs) {
	out << "Compressor stations information:\n\n"
		<< "Name: " << cs.title
		<< "\nNumber of workshops: " << cs.workshop
		<< "\nNumber of active workshops: " << cs.activeworkshop
		<< "\nPoints: " << cs.points << "\n\n\n";
	return out;
}

void editpipe(pipeline& pipe) {
	while (true) {
		cout << "Choose the new status of the pipe: 0 - in service, 1 - at work: ";
		cin >> pipe.fixing;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value!!!\n";
		}
		else {
			break;
		}
	}
}

void editcs(compressorstation& cs) {
	while (true) {
		cout << "\nWrite the new number of active workshops: ";
		cin >> cs.activeworkshop;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value!!!\n";
		}
		else if (cs.activeworkshop < 0) {
			cout << "Number cannot be less than 0..\n";
		}
		else if (cs.activeworkshop > cs.workshop) {
			cout << "Number cannot be more than the number of workshops.\n";
		}
		else {
			break;
		}
	}
}

void savepipe(pipeline& pipe, bool pipeavailability) {
	ofstream file;
	file.open("db.txt");

	if (file.is_open()) {
		if (pipeavailability)
			file << "1" << "\n" << pipe.title << "\n" << pipe.length << "\n" << pipe.diameter << "\n" << pipe.fixing << "\n";
		else
			file << "0\n";
	}
	file.close();
}

void savecs(compressorstation& cs, bool csavailability) {
	ofstream file;
	file.open("db.txt", ios::app);

	if (file.is_open() && csavailability)
		file << "1" << "\n" << cs.title << "\n" << cs.workshop << "\n" << cs.activeworkshop << "\n" << cs.points << "\n";
	else
		file << "0";
	file.close();
}

bool loadpipe(pipeline& pipe, ifstream& file) {
	int pipecount;

	if (file.is_open()) {
		file >> pipecount;
		if (pipecount == 1) {
			getline(file >> ws, pipe.title);
			file >> pipe.length;
			file >> pipe.diameter;
			file >> pipe.fixing;
		}
		if (pipecount)
			return true;
	}
	return false;
}

bool loadcs(compressorstation& cs, ifstream& file) {
	int cscount;

	if (file.is_open()) {
		file >> cscount;
		if (cscount == 1) {
			getline(file >> ws, cs.title);
			file >> cs.workshop;
			file >> cs.activeworkshop;
			file >> cs.points;
		}
		if (cscount)
			return true;
	}
	return false;
}

int main()
{
	pipeline pipe;
	bool pipeavailability = false;
	compressorstation cs;
	bool csavailability = false;

	while (true) {
		showMenu();
		int menunumber;
		cin >> menunumber;

		if (cin.good() && menunumber >= 0 && menunumber <= 7) {
			switch (menunumber) {
			case 0:
				return 0;

			case 1:
				if (pipeavailability) {
					cout << "Pipeline has already been added.\n\n";
				}
				else {
					addPipe(pipe);
					cout << "Pipe added.\n\n";
					pipeavailability = true;
				}
				break;

			case 2:
				if (csavailability) {
					cout << "Compressor station has already been added.\n\n";
				}
				else {
					addCs(cs);
					cout << "Compressor station added.\n\n";
					csavailability = true;
				}
				break;
			case 3:
				if (pipeavailability) {
					cout << pipe;
				}
				else {
					cout << "Pipeline hasn't been added yet.\n\n";
				}
				if (csavailability) {
					cout << cs;
				}
				else {
					cout << "Compressor station hasn't been added yet.\n\n";
				}
				break;
			case 4:
				if (pipeavailability) {
					editpipe(pipe);
					cout << "Pipe was edited.\n\n";
				}
				else {
					cout << "Pipeline hasn't been added yet.\n\n";
				}
				break;
			case 5:
				if (csavailability) {
					editcs(cs);
					cout << "Compressor station was edited.\n\n";
				}
				else {
					cout << "Compressor station hasn't been added yet.\n\n";
				}
				break;
			case 6:
				savepipe(pipe, pipeavailability);
				if (pipeavailability)
					cout << "Pipe was saved.\n\n";
				else
					cout << "Pipeline hasn't been added yet.\n\n";

				savecs(cs, csavailability);
				if (csavailability) {
					cout << "Compressor station was saved.\n\n";
				}
				else
					cout << "Compressor station hasn't been added yet.\n\n";

				break;
			case 7:
				ifstream file;
				file.open("db.txt");
				pipeavailability = loadpipe(pipe, file);
				if (pipeavailability)
					cout << "Pipeline was loaded.\n\n";
				else
					cout << "Pipeline hasn't been added yet.\n\n";

				csavailability = loadcs(cs, file);
				if (csavailability) {
					cout << "Compressor station was loaded.\n\n";
				}
				else
					cout << "Compressor station hasn't been added yet.\n\n";
				break;
			}
		}
		else {
			cin.clear();
			cin.ignore(500, '\n');
			cout << "Wrong value!!!\n\n";
		}
	}
	return 0;
}