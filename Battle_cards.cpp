#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <map>
using namespace std;

ofstream out("data1.txt");

class card
{
public:
	int number;
	int suit;
	static int uniquenumber;
	card();
	void showcard();
	card * next;
};

class collection
{
public:
	card * start;
	int numberofcards;
	collection(int x);
	collection() { start = nullptr; numberofcards = 0; }
	void showcollection();
	void shuffle();
	card deal();
	void add(card a);
};

card::card()
{
	number = uniquenumber % 13;
	suit = (uniquenumber / 13);
	uniquenumber++;
	next = nullptr;
}

void card::showcard()
{
	switch (number)
	{
	case 0: out << "A"; break;  
	case 10: out << "J"; break;
	case 11: out << "Q"; break;
	case 12: out << "K"; break;
	default: out << (number + 1); break;
	}

	switch (suit) {
	case 0: out << "S  "; break;
	case 1: out << "H  "; break;
	case 2: out << "D  "; break;
	case 3: out << "C  "; break;
	}
}

collection::collection(int x)
{
	start = nullptr;

	numberofcards = 0;
	for (int i = 0; i<x; i++)
	{
		card temp;
		add(temp);
	}
}

void collection::showcollection()
{
	int i;
	card * temp;
	temp = start;
	for (i = 0; i< numberofcards; i++)
	{
		temp->showcard();
		temp = temp->next;
	}
}

void collection::add(card a)
{
		card *temp =new card();
		temp->number = a.number;
		temp->suit = a.suit;
		a.uniquenumber--; 
		if (start == NULL)
		{
			start = temp;
			numberofcards++;
		}
		else
		{
			temp->next = start;
			start = temp;
			numberofcards++;
		}
}

void collection::shuffle()
{
	card *temp2, *temp3;
	temp2 = start;
	temp3 = temp2;
	int i, j, k;
	char c1;
	int num;
	for (i = numberofcards; i>1; i--) {
		j = rand() % i;
		for (k = 0; k <= j - 1; k++)
			temp3 = temp3->next;
		c1 = temp2->suit;
		num = temp2->number;
		temp2->suit = temp3->suit;
		temp2->number = temp3->number;
		temp3->suit = c1;
		temp3->number = num;
		temp2 = temp2->next;
		temp3 = temp2;
	}
}

card collection::deal()
{
	card *temp  ;
	numberofcards--;
	temp = start;
	start = start ->next ;
	return *temp;
}
 
int card::uniquenumber = 0;
void deal_cards(int k, int d, collection &deck, collection *hand);
void battle(int k, collection *hand, collection *table);
void Enter_Num_players_Dealer(int &k_players, int &dealer);
void Show_Initial_Deck_Hands(int &k_players, int &dealer, collection &deck, collection * hand, collection * table);

int main() {

	collection *hand, *table;
	int num_players, dealer, winner = 0;
	srand(time(0));
	Enter_Num_players_Dealer(num_players, dealer);
	collection deck(52);
	hand = new collection[num_players];
	table = new collection[num_players];
	Show_Initial_Deck_Hands(num_players, dealer, deck, hand, table);
	cout << endl << endl;
	battle(num_players, hand, table);
	return 0;
}

void Show_Initial_Deck_Hands(int &k_players, int &dealer, collection &deck, collection * hand, collection * table) {
	out << "\n\n************** initial deck of cards before shuffle ****\n\n";
	deck.showcollection();
	deck.shuffle(); 
	out << "\n\n****************** after shuffle **************\n\n";
	deck.showcollection();
	out << "\n\n****************** after cards are dealt **************\n\n";
	deal_cards(k_players, dealer, deck, hand);
	for (int i = 0; i < k_players; i++)
	{
		out << "\ncards for player " << i + 1 << "\n";
			hand[i].showcollection();
	}
}

void Enter_Num_players_Dealer(int &num_players, int &dealer) {

	do {
		cout << "Enter the number (2-10) of players ";
		cin >> num_players;
		if (num_players > 10 || num_players < 2)
			out << "Illegal player number. Enter again\n\n";
	} while (num_players >10 || num_players < 2);

	do {
		cout << "Enter initial dealer (1-k) ";
		cin >> dealer;
		if (dealer < 1 || dealer > num_players)
			out << "Illegal dealer ID. Enter again\n\n";
	} while (dealer < 1 || dealer > num_players);
}

void battle(int k, collection *hand, collection *table) { 
	card pop, pop1, pop2;
	map < int, card > current;
	bool tie_breaker[13] = { false };
	int active_players = k , index_winner = 0;
	static int minimum = 13;
	int tie = 0, winner;
	while (active_players > 1)
	{
		for (int i = 0; i < k; i++)
		{
			out << endl << "Hand " << i + 1 << "\n";
			hand[i].showcollection(); 
			out << endl;
		}
		current.clear();
		for (int i = 0; i < k; i++)
		{
			out << endl << "Table " << i + 1 << "\n";
			if (hand[i].numberofcards == 0)
			{
				cout << endl << endl; 
				continue;
			}
			if (tie_breaker[i] == true)
			{
				pop1 = hand[i].deal();
				table[i].add(pop1);
				pop2 = hand[i].deal();
				table[i].add(pop2);
				tie_breaker[i] = false;
			}
				pop = hand[i].deal();
				table[i].add(pop);

				table[i].showcollection();
			current.insert(pair <int, card>(i, pop));
			out << endl; 
		}

		map <int, card> ::iterator itr;
		minimum = 13;
		for (itr = current.begin(); itr != current.end(); ++itr)
		{
			if (itr->second.number < minimum)
			{
				minimum = itr->second.number;
				winner = itr->first;
			}
		}
		tie = 0;
		for (itr = current.begin(); itr != current.end(); ++itr)
		{
			if (itr->second.number == minimum)
			{
				index_winner = itr->first;
				tie++;
			}
		}
		if (tie > 1)
		{
 			for (itr = current.begin(); itr != current.end(); ++itr)
			{
				tie_breaker[itr->first] = false;
				if (itr->second.number == minimum)
				{
					tie_breaker[itr->first] = true;
					hand[itr->first].add(itr->second);
					table[itr->first].deal();
				}
				else
				{
					hand[itr->first].add(table[itr->first].deal());
				}
			}
		}
		else
		{
			for (itr = current.begin(); itr != current.end(); ++itr)
			{
				hand[winner].add(table[itr->first].deal());
				if (itr->second.number != minimum)
				{
					if (hand[itr->first].numberofcards < 5)
					{
						active_players--;
						while (hand[itr->first].numberofcards > 0)
						{
							pop = hand[itr->first].deal();
							hand[winner].add(pop);
						}
					}
				}
				while(table[itr->first].numberofcards)
					hand[winner].add(table[itr->first].deal());
			}
			hand[winner].shuffle();
		}
	}
	for (int i = 0; i < k; i++)
	{
		out << endl << "Final Hand " << i + 1 << "\n";
		hand[i].showcollection();
		out << endl;
	}
	//out << endl << "Number of cards " << hand[winner].numberofcards;
}

void deal_cards(int k, int d, collection &deck, collection *hand) {
	card non_dealer;
	card dealer;
	int count = 0 ;
	int for_count = 0;
	while (deck.numberofcards != 0 )
	{
		for (int i = d; i != d - 1 && deck.numberofcards != 0 ; i++)
		{
			i %= k;
			non_dealer = deck.deal();
			hand[i].add(non_dealer);
			if (deck.numberofcards ==  0)
				return; 
		}
		dealer = deck.deal();
		hand[d - 1].add(dealer);
	}
}
