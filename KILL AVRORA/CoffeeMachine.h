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
	struct Bank {//��������� � ������� �������� ������ � ������� � ���� ������
		int fives = 0;//���-�� 5-�� ��������
		int tens = 0;//���-�� 10-�� ��������
		int cash_in = 0;//���-�� ��������� �����
	};
	bool ready = true;
public:
	void set_ready(bool f) { ready = f; };
	bool is_ready() { return ready; };
	coffee_n_price& find_coffee(const string& sort);
	vector<coffee_n_price> sorts;//����� ����
	Bank bank;
	map<string, CoffeeMachine*> connections;
	virtual void handler() {};
};
#endif