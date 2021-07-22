#include "IOSystem.h"


//IDRes class


IDRes::IDRes(bool isFound, unsigned int row, std::string fileName) :
	found(isFound), row(row), fileName(fileName) {};

bool IDRes::getFound() {
	return this->found;
}

unsigned int IDRes::getRow() {
	return this->row;
}

std::string IDRes::getFileName() {
	return this->fileName;
}

IDRes IDRes::CheckID(unsigned short id, std::string csvName) {
	std::ifstream stream("Files/" + csvName + ".csv", std::ios::in);

	if (stream.is_open()) {

		unsigned short readId;

		std::string line, column;

		unsigned int row = 0;

		while (getline(stream, line)) {
			row++;

			if (line[0] == '*')
				continue;

			std::stringstream s(line);

			getline(s, column, ',');

			readId = std::stoi(column);

			if (readId == id) {
				stream.close();

				return IDRes(true, row, csvName);
			}
		}
		stream.close();
	}

	return IDRes(false);
}

//IDRes end



//StudentIO namespace

void StudentIO::WriteData(Student student) {
	std::ofstream stream("Files/students.csv", std::ios::app | std::ios::out);

	if (stream.is_open()) {

		stream << student.getId() << ','
			<< student.getName() << ','
			<< student.height << ','
			<< student.weight << ','
			<< student.getBirthString() << ','
			<< student.getGenderChar() << '\n';

		stream.close();
	}
}

//StudentIO end