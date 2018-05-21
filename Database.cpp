#include "stdafx.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool operator<(const course &c) { return (name < c.name); }
	bool operator==(const course &c) { return (name == c.name); }
};
void add_student(map<int, map<int, list<course *> * > *> &DB, int id);
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id);
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); 																							  
void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course *> * >  *> &DB, int id);
void print_DB(map<int, map<int, list<course *> * >  *> &DB);

int main() {
	map<int, map<int, list<course  *> *>   *> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course *> * > *> &DB, int id) {
	auto it1 = DB.find(id);
	if (it1 == DB.end())
	{
		DB[id] = new map<int, list<course *> * >;
		return;
	}
}
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id) {
	auto it1 = DB.find(id);

	auto it2 = (*DB[id]).begin();
	while (it2 != (*DB[id]).end())
	{
		auto it3 = it2->second->begin();
		while(it3 != it2->second->end())
		{	
			delete *it3;										    
			it3++;
		}
		delete it2->second;										
		it2++;
	}
	delete it1->second;											
	DB.erase(it1);										
}


void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
	
	if (DB.empty() == true) return;								              
	auto it1 = DB.find(id);										                  
	if (it1 == DB.end()) return;

	auto it2 = (*DB[id]).find(semester);						            
	if (it2 == (*DB[id]).end())
	{
		(*(DB)[id])[semester] = new list<course *>;
		(*(DB)[id])[semester]->push_back(new course(c));
		return;
	}

	auto it3 = (*DB[id])[semester]->begin();					          
	while (it3 != (*DB[id])[semester]->end())
	{
		if (c.name == (*it3)->name && c.credits == (*it3)->credits && c.section == (*it3)->section)
			return;
		it3++; 
	}

	(*(DB)[id])[semester]->push_back(new course(c));			      

}

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
		auto it1 = ((*DB[id])[semester])->begin();
		while (it1 != ((*DB[id])[semester])->end())
		{
			if ((*it1)->name == c.name)
			{
				delete *it1;
				(*DB[id])[semester]->erase(it1);
				return;
			}
			it1++;
		}
}

void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id) {
	auto it1 = DB.find(id);
	cout << endl;
	cout << endl;
	cout << "Student id = " << it1->first << endl;

	auto it2 = (*DB[id]).find(semester);
	if (it2 != (*DB[id]).end())
	{
		cout << "Semester = " << it2->first << endl;
		auto it3 = (*DB[id])[semester]->begin();
		while (it3 != (*DB[id])[semester]->end())
		{
			cout << (*it3)->name << " " << (*it3)->section << " " << (*it3)->credits << " ";
			it3++;
		}
		cout << endl;
	}
}
void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id) {
	auto it1 = DB.find(id);
	cout << endl;
	cout << endl;
	cout << "Student id = " << id << endl;

	auto it2 = (*DB[id]).begin();
	while (it2 != (*DB[id]).end())
	{
		cout << "Semester = " << it2->first << endl;
		auto it3 = it2->second->begin();
		while (it3 != it2->second->end())

		{
			cout << (*it3)->name << " " << (*it3)->section << " " << (*it3)->credits << " ";
			it3++;
		}
		cout << endl;
		it2++;
	}
}

void print_DB(map<int, map<int, list<course *> * >  *> &DB) {
	cout << endl;
	cout << endl;
	auto it1 = DB.begin();
	while (it1 != DB.end())
	{
		cout << "Student id = " << it1->first << endl;

		auto it2 = it1->second->begin();
		while (it2 != it1->second->end())
		{
			cout << "Semester = " << it2->first << endl;
			auto it3 = it2->second->begin();
			while (it3 != it2->second->end())

			{
				cout << (*it3)->name << " " << (*it3)->section << " " << (*it3)->credits << " ";
				it3++;
			}
			cout << endl;
			it2++;
		}
		it1++;
	}
}
