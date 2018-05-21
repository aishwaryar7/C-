#include "stdafx.h"
#include <iostream>
#include <fstream> 

using namespace std;

class node {
public:
	int value;
	node * next;
	node * previous;
	node() { next = previous = nullptr; }
	node(int k) { value = k; next = previous = nullptr; }
};

class linked_list {
public:
	node * head;
	node * tail;
	linked_list() { head = tail = nullptr; }
	void make_random_list(int k, int m);			//create a linked list of 
								                            //k nodes with values in 0 ..m-1 randomly
	void print_forward(); 					          //Print values of all nodes from head node
	void print_reverse(); 					          //Print values of all nodes reversely from tail node
	void reverse(); 					                //Reverse the order of nodes of linked list				
	void sort(); 						                  //Sort the nodes, based on ascending order of node values
	void insert(int k); 					            //Create a new node with values k, and properly add it to an already sorted list
								                            //After the insertion, the entire linked list is still sorted.
	void remove_all(int k); 				          //Remove all nodes whose node values are equal to k
};


void linked_list::make_random_list(int k, int m) { 		//create linked list of k nodes with
								                                      //values randomly in 0 ... m-1
	node * p;
	for (int i = 0; i < k; i++) {
		p = new node(rand() % m);
		p->next = head;
		if (head == nullptr) {
			tail = p; head = p;
		}
		else {
			head->previous = p;
			head = p;
		}
	}
}

void linked_list::print_forward() {
	node * p = head;
	cout << endl;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
}

void linked_list::print_reverse() {
	node * p = tail;
	cout << endl;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->previous;
	}
}

void linked_list::reverse() {
	node *temp;
	tail = head;
	if (head == nullptr || head->next == nullptr)
		return;
	while (head)
	{
		temp = head->previous;
		head->previous = head->next;
		head->next = temp;
		if (head->previous != NULL)
			head = head->previous;
		else
			break;
	}
}


void linked_list::remove_all(int k) {
	if (head == nullptr)
		return;
	node* current = head;
	while (current != nullptr) {
		if (current->value == k)
		{

			if (current->next != nullptr)
				current->next->previous = current->previous;
			if (current->previous != nullptr)
				current->previous->next = current->next;
			if (current == head)
			{
				head = current->next;
				delete head->previous;
				head->previous = nullptr;
			}
			if (current == tail)
			{
				tail = current->previous;
				delete tail->next;
				tail->next = nullptr;
			}
			current = current->next;
		}
		else
			current = current->next;
	}
}

void linked_list::sort() {
	node *p1, *p2, *min;
	if (head == nullptr || head->next == nullptr)
		return;
	else
	{
		p1 = head->next;
		p2 = head;
		min = head;
		while (p2 != nullptr)
		{
			bool swap = false;
			while (p1 != nullptr)
			{
				if (p1->value < min->value) {
					min = p1;
					p1 = p1->next;
					swap = true;
				}
				else
					p1 = p1->next;
			}
			if (min != head && swap)
			{
				min->previous->next = min->next;

				if (min->next != nullptr)
					min->next->previous = min->previous;
				else
					tail = min->previous;

				min->next = p2;
				min->previous = p2->previous;

				if (p2->previous != nullptr)
					p2->previous->next = min;

				p2->previous = min;

				if (p2 == head)
					head = min;
			}

			p2 = min->next;

			if (p2 == tail)
				return;
			min = p2;
			p1 = p2->next;
		}
	}
}


void linked_list::insert(int k)
{
	node* current = head;
	node* p = new node;
	p->value = k;

	if (current == NULL)
	{
		head = p;
		tail = p;
		return;
	}

	else if (head->value >= p->value)
	{
		p->next = head;
		p->next->previous = p;
		head = p;
	}

	else if (tail->value <= p->value)
	{
		p->previous = tail;
		p->previous->next = p;
		tail = p;
	}

	else
	{
		current = head;
		while (current->next != nullptr && current->next->value < p->value)
			current = current->next;

		p->next = current->next;

		if (current->next != nullptr)
			p->next->previous = p;

		current->next = p;
		p->previous = current;
	}
}

int main() {

	linked_list L1;

	L1.make_random_list(60, 15);
	L1.print_forward();
	L1.print_reverse();

	L1.reverse();
	L1.print_forward();
	L1.print_reverse();

	L1.remove_all(11);
	L1.print_forward();
	L1.print_reverse();

	L1.sort();
	L1.print_forward();
	L1.print_reverse();

	L1.insert(0);
	L1.insert(10);
	L1.insert(16);
	L1.print_forward();
	L1.print_reverse();

	getchar();
	getchar();
	return 0;
}
