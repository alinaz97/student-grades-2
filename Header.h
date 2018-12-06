#ifndef HEADER_H
#define HEADER_H
#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>

using namespace std;
const int NAME_LENGHT = 256;
const long long FN_SIZE = 1125899906842624;

class Student
{
private:
	long long fn;
	char* first_name;
	char* last_name;
	int grade;

public:
	Student() :fn(0), grade(0) {}
	Student(const long long fnum, const char* fname, const char* lname, int grd)
	{
		fn = fnum;
		grade = grd;
		first_name = new char[(strlen(fname)) + 1];
		last_name = new char[(strlen(lname)) + 1];
		strcpy(first_name, fname);
		strcpy(last_name, lname);
	}
	Student(const Student& other)
	{
		fn = other.fn;
		grade = other.grade;
		strcpy(first_name, other.first_name);
		strcpy(last_name, other.last_name);
	}
	Student& operator=(const Student& other) 
	{
		if (this != &other)
		{
			fn = other.fn;
			grade = other.grade;
			delete[] first_name;
			delete[] last_name;
			first_name = new char[(strlen(other.first_name)) + 1];
			last_name = new char[(strlen(other.last_name)) + 1];
			strcpy(first_name, other.first_name);
			strcpy(last_name, other.last_name);
		}
		return *this;
	}
	~Student()
	{
		delete[] first_name;
		delete[] last_name;
	}
	long long get_fn() const {
		return fn;
	}
	char* get_firstname() const
	{
		return first_name;
	}
	char* get_lastname() const
	{
		return last_name;
	}
	int get_grade() const
	{
		return grade;
	}
};


void create()
{

	long long fnum;
	char fname[NAME_LENGHT];
	char lname[NAME_LENGHT];
	int grade;
	cin >> fnum;
	cin >> fname;
	cin >> lname;
	cin >> grade;

	if(fnum < FN_SIZE)
	{
		if (grade >= 2 && grade <= 6)
		{
			Student s(fnum, fname, lname, grade);
			ofstream file("StudentsGrades.db", ios::app);
			if (!file) 
			{
				cout << "File couldn’t be opened!" << endl;
			}
			else
			{
				file << s.get_fn() << " " << s.get_firstname() << " " << s.get_lastname() << " " << s.get_grade() << endl;
				file.close();
				cout << "Record saved!" << endl;
			}
		}
		else cout << "Invalid grade! Please insert a grade between 2 and 6." << endl;
	}

	else cout << "Invalid faculty number!" << endl;
}

void sequentialSearch()
{
	fstream file("StudentsGrades.db");
	string search;
	cin >> search;
	bool found = false;
	int currentline = 0;
	string line;
	while (getline(file, line)) 
	{ 
		if (search == line.substr(0, search.length()) )
		{
			cout << line << endl;
			found = true;
			break;
		}
		
		currentline++;
	}
	if (found == false) cout << "Record not found!" << endl;
	file.seekg(0, ios::beg);
	file.close();
}

void update()
{
	fstream file("StudentsGrades.db");
	string search;
	cin >> search;
	bool found = false;
	int currentline = 0;
	string line;
	while (getline(file, line))
	{
		if (search == line.substr(0, search.length()))
		{
			found = true;
			int size = line.length();
			int grade;
			cin >> grade;
			file.clear();
			file.seekg(size - 1);
			file << grade;
			cout << "Record saved!" << endl;
			break;
		}
		currentline++;
	}
	if (found == false) cout << "Record not found!" << endl;
	file.seekg(0, ios::beg);
	file.close();
}

void deleteStudent()
{
	fstream file("StudentsGrades.db");
	fstream newfile("new.db", ios::out);
	string search;
	cin >> search;
	bool found = false;
	int currentline = 0;
	string line;
	while (getline(file, line))
	{
		if (search == line.substr(0, search.length())) found = true;
		else
		{
			newfile << line << endl;
		}
		currentline++;
	}
	if (found == false) cout << "Record not found!" << endl;
	else cout << "Record deleted!" << endl;

	file.close();
	newfile.seekg(0, ios::beg);
	newfile.close();

	remove("StudentsGrades.db");
	rename("new.db", "StudentsGrades.db");
	
}

#endif