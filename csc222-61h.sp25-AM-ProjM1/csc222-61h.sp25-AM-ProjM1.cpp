// csc222-61h.sp25-AM-ProjM1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//M1 Procedural Programming Review Project No. 2: make a gradebook organizer thingy
//resubmission due to VS not fully committing project  to github, improper repos setup.

/*TEST SCORE RANGE AND LETTERS:
90-100: A
80-89:  B
70-79:  C
60-69:  D
0-59:   F
*/

//Project notes: read stud names/test scores getFile, calc average, match average number to a letter grade.
//              write prog in partially filled arrays, actual numb of studs is counted as file is read.
//              num of test scores on file should be stored as global const.
//              stud names in array of strings, scores in 2d array (row stud, score column), test avgs om 3rd array of doubles.


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int maxStudent = 100;
const int maxTest = 5;

int main()
{
	string names[maxStudent];
	double testScores[maxStudent][maxTest];
	double averages[maxStudent];
	int numStudents = 0;

	ifstream file("StudentGrades.txt");
	if (!file)
	{
		cerr << "Error! Couldn't open StudentGrades.txt." << endl;
		return 1;
	}
	readFile(file, names, testScores, numStudents);
	calcAvgs(testScores, averages, numStudents);
	printReport(names, averages, numStudents);

	file.close();
	return 0;
}

//getfile function: this function reads data from the provided text file 
void readFile(ifstream& file, string names[], double testScores[][maxTest], int& numStudents)
{
	numStudents = 0;
	while (file >> names[numStudents])
	{
		for (int i = 0; i < maxTest; ++i)
		{
			file >> testScores[numStudents][i];
		}
		++numStudents;
	}
}

//calc avgs
void calcAvgs(double testScores[][maxTest], double averages[], int numStudents)
{
	for (int i = 0; i < numStudents; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < maxTest; ++j)
		{
			sum += testScores[i][j];
		}
		averages[i] = sum / maxTest;
	}
}

//leter grade conversion funct
char calcLetterGrade(double average)
{
	if (average >= 90.0) return 'A';
	if (average >= 80.0) return 'B';
	if (average >= 70.0) return 'C';
	if (average >= 60.0) return 'D';
	return 'F';
}

//print report function
void printReport(const string names[], const double averages[], int numStudents)
{
	cout << setw(15) << "Name" << setw(10) << "Average" << setw(10) << "Grade" << endl;
	for (int i = 0; i < numStudents; ++i)
	{
		cout << setw(15) << names[i] << setw(10) << fixed << setprecision(2) << averages[i] << setw(10) << calcLetterGrade(averages[i]) << endl;
	}
}
