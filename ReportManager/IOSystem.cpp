#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "IOSystem.h"

bool CheckID(unsigned short id, std::string fileName) {
	const std::string file = "Files/" + fileName;

	std::ifstream stream(file, std::ios::in);

	std::string line, word;

	std::vector<unsigned short> row;

	while (std::getline(stream, line)) {

		if (line[0] == '*')
			continue;

		row.clear();

		std::stringstream s(line);

		std::getline(s, word, ',');

		int readId = std::stoi(word);

		if (readId == id) {
			stream.close();

			return true;
		}
	}

	return false;
}


//StudentIO
void StudentIO::WriteData(Student student) {
	while (CheckID(student.getId(), "students.csv")) {
		student.RegenID();
	}

	std::ofstream stream("Files/students.csv", std::ios::app | std::ios::out);

	if (stream.is_open()) {
		stream << student.getId() << ','
			<< student.getName() << ','
			<< student.getHeight() << ','
			<< student.getWeight() << '\n';
	}

	stream.close();
}

std::vector<Student> StudentIO::ReadAll() {
	std::ifstream stream("File/students.csv", std::ios::in);

	std::vector<Student> students;

	if (stream.is_open()) {
		
		std::string line, data;

		std::vector<std::string> row;

		while (std::getline(stream, line)) {
			if (line[0] == '*')
				continue;

			row.clear();

			std::stringstream s(line);

			while (std::getline(s, data, ',')) {

				row.push_back(data);

			}

			Subject* subjects = GradeIO::ReadGrade(std::stoi(row[0]));

			Student student(std::stoi(row[0]), row[1], std::stoi(row[2]), std::stof(row[3]), subjects);

			students.push_back(student);
		}
	}

	return students;
}

//GradeIO
void GradeIO::WriteData(Student student) {
	std::ofstream stream("Files/grades.csv", std::ios::out, std::ios::app);

	if (stream.is_open()) {
		if (!CheckID(student.getId(), "grades.csv")) {
			stream << student.getId() << ','
				<< student.getSubject(0).StringifyGrades() << ','
				<< student.getSubject(1).StringifyGrades() << ','
				<< student.getSubject(2).StringifyGrades() << ','
				<< student.getSubject(3).StringifyGrades() << ','
				<< student.getSubject(4).StringifyGrades() << ','
				<< student.getSubject(5).StringifyGrades() << ','
				<< student.getSubject(6).StringifyGrades() << '\n';
		}
	}
}

Subject* GradeIO::ReadGrade(unsigned short id) {
	std::ifstream stream("Files/grades.csv", std::ios::in);

	if (stream.is_open()) {

		Subject* arr = NULL;

		std::vector<Subject> subjects;

		std::string line, word;
		std::vector<std::string> row;

		bool found = false;

		while (std::getline(stream, line)) {

			if (line[0] == '*')
				continue;

			row.clear();

			std::stringstream s(line);

			while (std::getline(s, word, ',')) {

				row.push_back(word);
			}

			unsigned short newId = std::stoi(row[0]);

			if (newId == id) {
				found = true;

				for (unsigned short i = 1; i < 8; i++)
				{ 
					std::vector<short> grades = Subject::StringToGrade(row[i]);

					Subject subject((SubjectName)i, grades);

					subjects.push_back(subject);
				}
			}
		}

		std::copy(subjects.begin(),
			subjects.end(),
			arr);

		return arr;
	}
	throw(404);
}

