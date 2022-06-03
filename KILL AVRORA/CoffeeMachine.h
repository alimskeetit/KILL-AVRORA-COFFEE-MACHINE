#ifndef CoffeeMachine_h
#define  CoffeeMachine_h
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
class CoffeeMachine {
	struct coffee_n_price {
		string coffee;
		int price;
	};
	struct Bank {//структура в которой хранятся данные о деньгах в кофе машине
		int fives = 0;//кол-во 5-ти рублевых
		int tens = 0;//кол-во 10-ти рублевых
		int cash_in = 0;//кол-во занесённых денег
	};
	bool ready = true;
public:
	void set_ready(bool f) { ready = f; };
	bool is_ready() { return ready; };
	coffee_n_price& find_coffee(const string& sort);
	vector<coffee_n_price> sorts;//сорта кофе
	Bank bank;
	map<string, CoffeeMachine*> connections;
	virtual void handler() {};
};
#endif