#include "Subject.h"

#ifndef Student_H
#define Student_H

class Student {
public:
	//Constructor
	Student(std::string name, unsigned short heightCm, float weightKg, Subject subjects[7]);

	//Base data
	std::string getName();
	unsigned short getId();
	unsigned short getHeight();
	float getWeight();

	//Calculated
	float Average(); //Calculates total average of grades
	unsigned short DaysMissed(); //Calculates total days missing

private:
	char name[50];
	unsigned short id;

	//Centimeter and Kilogramm
	unsigned short height;
	float weight;

	/*
	* 1. Math
	* 2. P.E.
	* 3. History
	* 4. Grammar
	* 5. Art
	* 6. R.E.
	* 7. I.T.
	*/
	Subject* subjects;
};

#endif // !Student_H