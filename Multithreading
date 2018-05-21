#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <list>
using namespace std;

mutex m1;
condition_variable part1, part2, part3, part4, product1, product2, product3, product4;
int A = 0, B = 0, C = 0, D = 0;

class Part {
public:
	int a, b, c, d;
	int total = 0;
	Part(int id)
	{
		srand(time(NULL) + id);
		while (total != 3)
		{
			total = 0;
			a = rand() % 4;
			b = rand() % 4;
			c = rand() % 4;
			d = rand() % 4;
			total = a + b + c + d;
		}
	}
	void show()
	{
		cout << "(" << a << "," << b << "," << c << "," << d << ")" << endl;
	}
};

class Product {
public:
	int a, b, c, d;
	int total = 0;
	int count = 0;
	int A[4];
	bool exactlyTwo = false;
	Product(int id)
	{
		srand(time(NULL) + id);
		while (total != 4 || !exactlyTwo)
		{
			total = 0;
			count = 0;
			exactlyTwo = false;

			a = rand() % 4; { if (a == 0) count++; }
			b = rand() % 4; { if (b == 0) count++; }
			c = rand() % 4; { if (c == 0) count++; }
			d = rand() % 4; { if (d == 0) count++; }

			total = a + b + c + d;

			if (count == 2)
			{
				exactlyTwo = true;
			}
		}
	}
	void show()
	{
		cout << "(" << a << "," << b << "," << c << "," << d << ")" << endl;
	}
};

void showBuffer() {

	cout << "(" << A << "," << B << "," << C << "," << D << ")" << endl;
}


void PartWorker(int id)
{
	int request[16];
	request[id] = 1;
	bool stop[16];
	stop[id] = false;
	while (1)
	{
		Part *Worker = new Part(id);
		while ((Worker->a != 0 || Worker->b != 0 || Worker->c != 0 || Worker->d != 0) && !stop[id])
		{
			unique_lock<mutex> ulock1(m1);

			while ((Worker->a > 0 && A >= 6)
				&& (Worker->b == 0 || (Worker->b > 0 && B >= 5))
				&& (Worker->c == 0 || (Worker->c > 0 && C >= 4))
				&& (Worker->d == 0 || (Worker->d > 0 && D >= 3)))
			{
				part1.wait(ulock1);
			}


			while ((Worker->a == 0 || (Worker->a > 0 && A >= 6))
				&& (Worker->b > 0 && B >= 5)
				&& (Worker->c == 0 || (Worker->c > 0 && C >= 4))
				&& (Worker->d == 0 || (Worker->d > 0 && D >= 3)))
			{
				part2.wait(ulock1);
			}

			while ((Worker->a == 0 || (Worker->a > 0 && A >= 6))
				&& (Worker->b == 0 || (Worker->b > 0 && B >= 5))
				&& (Worker->c > 0 && C >= 4)
				&& (Worker->d == 0 || (Worker->d > 0 && D >= 3)))
			{
				part3.wait(ulock1);
			}

			while ((Worker->a == 0 || (Worker->a > 0 && A >= 6))
				&& (Worker->b == 0 || (Worker->b > 0 && B >= 5))
				&& (Worker->c == 0 || (Worker->c > 0 && C >= 4))
				&& (Worker->d > 0 && D >= 3))
			{
				part4.wait(ulock1);
			}

			cout << "PartWorker ID: " << id << endl;
			cout << "Iteration: " << request[id] << endl;
			cout << "Buffer State: "; showBuffer();
			cout << "Place Request: "; Worker->show();

			if (Worker->a > 0)
			{
				if (A + Worker->a < 6)
				{
					A += Worker->a;
					Worker->a = 0;
				}
				else
				{
					Worker->a -= (6 - A);
					A = 6;
				}
				product1.notify_one();
			}
			if (Worker->b > 0)
			{
				if (B + Worker->b < 5)
				{
					B += Worker->b;
					Worker->b = 0;
				}
				else
				{
					Worker->b -= (5 - B);
					B = 5;
				}
				product1.notify_one();
			}
			if (Worker->c > 0)
			{
				if (C + Worker->c < 4)
				{
					C += Worker->c;
					Worker->c = 0;
				}
				else
				{
					Worker->c -= (4 - C);
					C = 4;
				}
				product1.notify_one();
			}
			if (Worker->d > 0)
			{
				if (D + Worker->d < 3)
				{
					D += Worker->d;
					Worker->d = 0;
				}
				else
				{
					Worker->d -= (3 - D);
					D = 3;
				}
				product1.notify_one();
			}

			cout << "Updated Buffer State: "; showBuffer();
			cout << "Updated Place Request: "; Worker->show();
			cout << endl;

			if (request[id] == 5)
			{
				stop[id] = true;
			}
		}
		if (Worker->a == 0 && Worker->b == 0 && Worker->c == 0 && Worker->d == 0)
			request[id]++;
	}
}

void ProductWorker(int id)
{
	int request[12];
	request[id] = 1;
	bool stop[12];
	stop[id] = false;
	while (1)
	{
		Product *Worker = new Product(id);
		while ((Worker->a != 0 || Worker->b != 0 || Worker->c != 0 || Worker->d != 0) && !stop[id])
		{
			unique_lock<mutex> ulock1(m1);

			while ((Worker->a > 0 && A < 1)
				&& (Worker->b == 0 || (Worker->b > 0 && B < 1))
				&& (Worker->c == 0 || (Worker->c > 0 && C < 1))
				&& (Worker->d == 0 || (Worker->d > 0 && D < 1)))
			{
				product1.wait(ulock1);
			}

			while ((Worker->a == 0 || (Worker->a > 0 && A <1))
				&& (Worker->b > 0 && B < 1)
				&& (Worker->c == 0 || (Worker->c > 0 && C < 1))
				&& (Worker->d == 0 || (Worker->d > 0 && D < 1)))
			{
				product2.wait(ulock1);
			}

			while ((Worker->a == 0 || (Worker->a > 0 && A < 1))
				&& (Worker->b == 0 || (Worker->b > 0 && B < 1))
				&& (Worker->c > 0 && C < 1)
				&& (Worker->d == 0 || (Worker->d > 0 && D < 1)))
			{
				product3.wait(ulock1);
			}

			while ((Worker->a == 0 || (Worker->a > 0 && A <1))
				&& (Worker->b == 0 || (Worker->b > 0 && B <1))
				&& (Worker->c == 0 || (Worker->c > 0 && C <1))
				&& (Worker->d > 0 && D < 1))
			{
				product4.wait(ulock1);
			}

			cout << "ProductWorker ID: " << id << endl;
			cout << "Iteration: " << request[id] << endl;
			cout << "Buffer State: "; showBuffer();
			cout << "Pickup Request: "; Worker->show();


			if (Worker->a > 0)
			{
				if (A >= Worker->a)
				{
					A -= Worker->a;
					Worker->a = 0;
				}
				else
				{
					Worker->a -= A;
					A = 0;
				}
				part1.notify_one();
			}
			if (Worker->b > 0)
			{
				if (B >= Worker->b)
				{
					B -= Worker->b;
					Worker->b = 0;
				}
				else
				{
					Worker->b -= B;
					B = 0;
				}
				part2.notify_one();
			}
			if (Worker->c > 0)
			{
				if (C >= Worker->c)
				{
					C -= Worker->c;
					Worker->c = 0;
				}
				else
				{
					Worker->c -= C;
					C = 0;
				}
				part3.notify_one();
			}
			if (Worker->d > 0)
			{
				if (D >= Worker->d)
				{
					D -= Worker->d;
					Worker->d = 0;
				}
				else
				{
					Worker->d -= D;
					D = 0;
				}
				part4.notify_one();
			}

			cout << "Updated Buffer State: "; showBuffer();
			cout << "Updated Pickup Request: "; Worker->show();
			cout << endl;

			if (request[id] == 5)
			{
				stop[id] = true;
			}

		}

		if (Worker->a == 0 && Worker->b == 0 && Worker->c == 0 && Worker->d == 0)
			request[id]++;

	}
}

int main() {
	const int m = 16, n = 12;
	thread partW[m];
	thread prodW[n];
	for (int i = 0; i < n; i++) {
		partW[i] = thread(PartWorker, i);
		prodW[i] = thread(ProductWorker, i);
	}
	for (int i = n; i<m; i++) {
		partW[i] = thread(PartWorker, i);
	}
	/* Join the threads to the main threads */
	for (int i = 0; i < n; i++) {
		partW[i].join();
		prodW[i].join();
	}
	for (int i = n; i<m; i++) {
		partW[i].join();
	}
	cout << "Finish!" << endl;
	getchar();
	getchar();
	return 0;
}
