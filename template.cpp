#include "stdafx.h"
#include <iostream>
#include <fstream> 
#include <stdlib.h>
#include <string>

using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i) { ht = wid = dep = i; }
	ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }
	template <class U> friend ostream & operator<<(ostream &stream, const ThreeD<U> &T1);
	bool operator==(const ThreeD<T> &T1);	
};

template <class T> class node {
public:
	T value;
	node<T> * next;
	node<T> * previous;
	node<T>() { next = previous = nullptr; }
	node<T>(T v) { value = v; next = previous = nullptr; }
};

template <class T> class linked_list { 
public:
	node<T> * head;
	node<T> * tail;
	int num_nodes;
	int size() { return num_nodes; }
	linked_list() { head = tail = nullptr; }
	~linked_list();
	void push_front(T v);
	void operator= (linked_list &P);			
	linked_list(const linked_list<T> &P);
	bool operator==(const linked_list<T> &T1);
	template <class U> friend ostream & operator<<(ostream &stream, const linked_list<U> &T1);
	
};

template <class X> class item {
public:
	X value;
	item<X> *next;
	item<X> *previous;
	item<X>() { next = previous = nullptr; }
	item<X>(X v) { value = v; next = nullptr; previous = nullptr; }
};

template <class X> class bag {
public:
	item<X> *last;
	item<X> *first;
	int num_items;
	int size() { return num_items; }
	bag() { last = nullptr; first = nullptr; num_items = 0; }
	bag(const bag<X> &P);	
	void operator= (bag &P);
	~bag();					
	void push_back(X v);	
	void push_front(X v);	
	void pop_back();		
	void pop_front();		
	X &operator[](int i);
	X front() {				
		return first->value;
	}
	X back() {				
		return last->value;
	}
	void clear();				      
	item<X> * find(X x);		 
	void erase(item<X> * p);	
	void erase(int i);			 
	template <class U> friend ostream & operator<<(ostream &stream, const bag<U> &T1);	
};

template <class U> bool ThreeD<U>::operator==(const ThreeD<U> &T1)
{
	if (T1.ht == ht && T1.wid == wid && T1.dep == dep)
		return true;
	else
		return false;
}

template <class U> ostream & operator<<(ostream &stream, const ThreeD<U> &T1) {
	stream << "( " << T1.ht << ", " << T1.wid << ", " << T1.dep << " )";
	return stream;
}

template <class U> bool linked_list<U>::operator==(const linked_list<U> &T1)
{
	node<U> *p = T1.head;
	node<U> *q = head;
	while (p != nullptr && q != nullptr)
	{
		if (q->value == p->value)
		{
			q = q->next;
			p = p->next;
		}
		else
			return false;
	}
}
template<class T> void linked_list<T>::operator=(linked_list &P)					
{
	this->head = nullptr;
	this->tail = nullptr;
	num_nodes = P.num_nodes;
	while (head != nullptr) {
		node<T> * p = head->next;
		delete head;
		head = p;
	}
	node<T>* p1 = P.head;
	while (p1 != nullptr) {
		node<T> * p2 = new node<T>;
		p2->next = head;
		if (head == nullptr) {
			tail = p2; head = p2;
		}
		else {
			head->previous = p2;
			head = p2;
		}
		p1 = p1->next;
	}
	p1 = P.head;
	node<T> * p2 = head;
	while (p1 != nullptr) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}

template<class T> linked_list<T>::linked_list(const linked_list<T> &P)			
{
	this->head = nullptr;
	this->tail = nullptr;
	num_nodes = P.num_nodes;
	node<T>* p1 = P.head;
	while (p1 != nullptr) {
		node<T> * p2 = new node<T>;
		p2->next = head;
		if (head == nullptr) {
			tail = p2; head = p2;
		}
		else {
			head->previous = p2;
			head = p2;
		}
		p1 = p1->next;
	}
	p1 = P.head;
	node<T> * p2 = head;
	while (p1 != nullptr) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}

template<class T> linked_list<T>::~linked_list() {
	while (head != nullptr) {
		node<T> * p = head->next;
		delete head;
		head = p;
	}
	tail = nullptr;
}

template <class T> void linked_list<T>::push_front(T v) {
	node<T>* p = new node<T>;
	p->value = v;
	num_nodes++;
	if (head == nullptr)
	{
		head = tail = p;
		return;
	}
	p->next = head;
	p->next->previous = p;
	head = p;
}

template <class U> ostream & operator<<(ostream &stream, const linked_list<U> &T1) {
	node<U> * p = T1.head;
	while (p != nullptr) {
		stream << p->value << " ";
		p = p->next;
	}
	return stream;
}

template <class X> void bag<X>::push_front(X v) {
	item<X>* p = new item<X>;
	p->value = v;
	num_items++;
	if (first == nullptr)
	{
		first = last = p;
		return;
	}
	p->next = first;
	p->next->previous = p;
	first = p;
}

template <class X> void bag<X>::push_back(X v) {
	item<X>* p = new item<X>;
	p ->value = v; 
	num_items++;
	if (last == nullptr) {
		first = last = p;
		return;
	}
	p->previous = last;
	p->previous->next = p;
	last = p;
}

template <class X> void bag<X>::pop_front() {
	first = first ->next;
	delete first ->previous;
	first->previous = nullptr;
	num_items--;
}

template <class X> void bag<X>::pop_back() {
	last = last ->previous;
	delete last ->next;
	last ->next = nullptr;
	num_items--;
}

template <class X> X &bag<X>::operator[](int i)
{
	item<X>* current = first;
	int count = 0;
	while (current != NULL)
	{
		if (count == i)
			return (current->value) ;
		count++; 
		current = current->next; 
	}
}

template <class X> void bag<X>::clear() 
{
	if (first == nullptr)
		return;
	item<X>* current; 
	while (first != NULL)
	{
		current = first; 
		first = current->next;
		delete current;
		num_items--;
	}
}

template <class X> item<X> * bag<X>::find(X x)
{
	item<X>* current = first;
	while (current != NULL)
	{
		if ( x == current->value)
			return current;
		current = current->next;
	}
	return nullptr;
}

template <class X> void bag<X>::erase(item<X> * p)
{
	if (first == nullptr )
		return;
	item<X>* current = first ;
	while (current != nullptr)
	{
		if (current == p)
		{
			if (current->next != nullptr && current->previous != nullptr)
			{
				current->next->previous = current->previous;
				current->previous->next = current->next;
				num_items--;
				return; 
			}
			if (current == first)
			{
				first = current->next;
				delete first->previous;
				first->previous = nullptr;
				num_items--;
				return;
			}
			if (current == last)
			{
				last = current->previous;
				delete last->next;
				last->next = nullptr;
				num_items--;
				return;
			}
		}
		current = current->next;
	}
}

template <class X> void bag<X>::erase(int i)
{
	if (first == nullptr || i > num_items)
		return;
	item<X>* current = first;
	int count = 0;
	while (current != NULL)
	{
		if (count == i)
		{
			if (i == 0)
			{
				current = first;
				first = current->next;
				delete first->previous;
				first->previous = nullptr;
				num_items--;
				return;
			}
			if (current->next != nullptr && current->previous != nullptr)
			{
				current->next->previous = current->previous;
				current->previous->next = current->next;
				num_items--;
				return;
			}
			if (i == num_items)
			{
				current = last;
				last = current->previous;
				delete last->next;
				last->next = nullptr;
				num_items--;
				return;
			}
		}
		count++;
		current = current->next;
	}
}

template <class X> void bag<X>::operator=(bag &P)					
{
	this->first = nullptr;
	this->last = nullptr;
	num_items = P.num_items;
	while (first != nullptr)
	{
		item<T> * p = first->next;
		delete first;
		first = p;
	}
	item<T>* p1 = P.first;
	while (p1 != nullptr)
	{
		item<T> * p2 = new item<T>;
		p2->next = first;
		if (first == nullptr) {
			first = p2; last = p2;
		}
		else {
			first->previous = p2;
			first = p2;
		}
		p1 = p1->next;
	}
	p1 = P.first;
	item<T> * p2 = first;
	while (p1 != nullptr)
	{
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}
template <class X> bag<X>::bag(const bag<X> &P)			
{
	this->first = nullptr;
	this->last = nullptr;
	num_items = P.num_items;
	item<T>* p1 = P.first;
	while (p1 != nullptr)
	{
		item<T> * p2 = new item<T>;
		p2->next = first;
		if (first == nullptr) {
			first = p2; last = p2;
		}
		else {
			first->previous = p2;
			first = p2;
		}
		p1 = p1->next;
	}
	p1 = P.first;
	item<T> * p2 = first;
	while (p1 != nullptr)
	{
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}
template <class X> bag<X>::~bag() {
	while (first != nullptr) {
		item<X> * p = first->next;
		delete first;
		first = p;
	}
	last = nullptr;
}

template <class U> ostream & operator<<(ostream &stream, const bag<U> &T1) {
	item<U>* p = T1.first;
	while (p != nullptr) {
		stream << p->value << " ";
		p = p->next;
	}
	return stream;
}

//template-based doubly linked list, template-based ThreeD, vector, list, map, etc.

int main() {
	
	bag<double> bag_d;
	bag_d.push_back(5.5);
	bag_d.push_back(6.6);
	bag_d.push_front(4.4);
	bag_d.push_front(3.3);
	bag_d.pop_front();
	bag_d.pop_back();
	cout << bag_d << endl;

	bag<int> bag_i;
	bag_i.push_back(5);
	bag_i.push_back(6);
	bag_i.push_front(4);
	bag_i.push_front(3);
	bag_i.pop_front();
	bag_i.pop_back();
	cout << bag_i << endl;

	ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
	bag<ThreeD<int>> bag_3D;
	bag_3D.push_back(td5);
	bag_3D.push_back(td6);
	bag_3D.push_front(td4);
	bag_3D.push_front(td3);
	bag_3D.pop_front();
	bag_3D.pop_back();
	cout << bag_3D << endl;;
	cout << bag_3D.front() << bag_3D.back();
	cout << bag_3D[0] << " " << bag_3D[1] << endl;
	bag_3D[1] = td7;
	cout << bag_3D[0] << " " << bag_3D[1] << endl;
	bag_3D.clear();
	cout << bag_3D << endl;;
	cout << bag_3D.size() << endl;

	linked_list<string>ls_1;
	ls_1.push_front("David");
	ls_1.push_front("John");
	ls_1.push_front("Pat");
	ls_1.push_front("Ben");
	ls_1.push_front("Jeff");
	cout << ls_1 << endl;

	linked_list<string>ls_2;
	ls_2.push_front("Wendy");
	ls_2.push_front("Mary");
	ls_2.push_front("Nancy");
	ls_2.push_front("Jennifer");
	cout << ls_2 << endl;

	bag<linked_list<string>> bag_string;

	bag_string.push_back(ls_1);

	bag_string.push_back(ls_2);

	cout << bag_string << endl;
	cout << bag_string[1] << endl;

	ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
	
	linked_list<ThreeD<double>> LTD1;
	LTD1.push_front(t10);
	LTD1.push_front(t11);
	
	linked_list<ThreeD<double>> LTD2;
	LTD2.push_front(t13);
	LTD2.push_front(t12);
	LTD2.push_front(t10);
	LTD2.push_front(t11);

	bag<linked_list<ThreeD<double> > > BLTD;
	BLTD.push_back(LTD1);
	BLTD.push_back(LTD2);
	cout << BLTD << endl;

	item<linked_list<ThreeD<double>>> * p2;

	p2 = BLTD.find(LTD1);
	BLTD.erase(p2);
	cout << BLTD << endl;
	BLTD.push_back(LTD1);
	cout << BLTD << endl;
	BLTD.erase(0);
	cout << BLTD << endl;

	getchar();
	getchar();
	return 0;
