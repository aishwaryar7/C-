#include <iostream>

using namespace std;

class term {
public:
	int power;
	int coef;
	term * next;
	term() { next = nullptr; }
	term(int c, int p) { power = p; coef = c; next = nullptr; }
};

class polynomial {
public:
	int num_terms;
	term * head;
	polynomial() { num_terms = 0; head = nullptr; }

	void add_term(int c, int p);
	polynomial operator+(polynomial P);
	polynomial operator*(polynomial P);
	void print_polynomial();
};


void polynomial::print_polynomial() {
	cout << endl;
	term * p = head;
	while (p != nullptr) {
		cout << p->coef << " " << p->power << "   " ;
		p = p->next;
	}
	cout << endl; 
}
void polynomial::add_term(int c, int p) 
{
	term * new_term = new term(c,p);
	if (head == nullptr)
	{
		head = new_term;
	}
	else 
	{
			if (new_term->power == head->power)
			{
				head->coef = head->coef + new_term->coef;
				if (head->coef == 0)
				{
					head = head->next;
					delete new_term;
					return;
				}
			}
			else if (new_term->power > head->power )
			{
				term *temp=head;
				head = new_term;
				new_term->next = temp;
				return; 
			}
			else if (new_term->power < head->power)
			{
				
				if (head->next == nullptr)
				{
					head->next = new_term;
					return;
				}
				else 
				{
					term *current, *previous;
					current = head->next;		 
					previous = head;		 
					while (current != nullptr)
					{
						if (new_term->power <= current->power ) 
						{
							if (new_term->power == current->power)
							{
								current->coef = current->coef + new_term->coef;
								if (current->coef == 0)
								{
									previous->next = current->next;
									delete new_term;
									return;
								}
								return; 
							}

							previous = current;
							current = current->next;

							if (current == nullptr)
							{
								previous->next = new_term;
								return;
							}

						}
						else if (new_term->power > current->power) 
						{
							previous->next = new_term;
							new_term->next = current;
							return;
						}
					
					}
				}
				
			}
	} 
}

int max(int m, int n) { return (m > n) ? m : n; }

polynomial polynomial::operator+(polynomial P) {
	term *p1 = head;
	term *p2 = P.head;
	polynomial *p3 = new polynomial; 
	while (p1 != nullptr || p2 != nullptr)
	{
		if (p1 != nullptr && p2 != nullptr)
		{
			if (p1->power > p2->power)
			{
				p3->add_term(p1->coef, p1->power);
				p1 = p1->next;
			}
			else if (p1->power < p2->power)
			{
				p3->add_term(p2->coef, p2->power);
				p2 = p2->next;
			}
			else
			{
				p3->add_term(p1->coef + p2->coef, p1->power);
				p1 = p1->next;
				p2 = p2->next;
			}
		}
			while (p1 != nullptr)
			{
				p3->add_term(p1->coef, p1->power);
				p1 = p1->next;
			}
			while (p2 != nullptr)
			{
				p3->add_term(p2->coef, p2->power);
				p2 = p2->next;
			}
	}
	return *p3; 
}

polynomial polynomial::operator*(polynomial P) {
	term *p1 = head;
	polynomial *p3 = new polynomial();
	while (p1 != nullptr)
	{
		term *p2 = P.head;
		while (p2 != nullptr)
		{
			p3->add_term((p1->coef * p2->coef), (p1->power + p2->power));
			p2 = p2->next;
		}
		p1 = p1->next; 
	}
	return *p3; 
}


int main() {
	polynomial p1, p2, p3, p4, p5, p6;
	int num_t;
	cout << "Enter number of terms" << endl;
	cin >> num_t;
	cout << "Enter all terms" << endl;
	for (int i = 0; i < num_t; i++) { 
		int c, p;
		cin >> c >> p;
		if (c != 0)
		{
			p1.add_term(c, p);
		}
	}
	cout << "Polynomial 1 is ";
	p1.print_polynomial();
	cout << endl;

	cout << "Enter number of terms" << endl;
	cin >> num_t;
	cout << "Enter all terms" << endl;
	for (int i = 0; i < num_t; i++) { 
		int c, p;
		cin >> c >> p;
		if (c != 0)
		{
			p2.add_term(c, p);
		} 
	}
	cout << "Polynomial 2 is ";
	p2.print_polynomial();
	cout << endl;
	p3 = p1 + p2;
	cout << "Sum of the polynomials" << endl;
	
	p3.print_polynomial();

	cout << endl;
	p4 = p1 * p2;
	cout << "Product of the polynomials" << endl;
	p4.print_polynomial();
	getchar();
	getchar();
	return 0;
}
