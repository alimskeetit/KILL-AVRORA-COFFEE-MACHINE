#include "App.h"
#include <iostream>
using namespace std;

bool App::build_tree_objects() {
	controller = new Controller(ptr_coffee_machine);//создаем пульт управления
	//строим дерево, создавая и добавляя устройства
	tree.insert(pair<string, Device*>("Controller", controller)); //добавили пульт
	tree.insert(pair<string, Device*>("Refund money", new RefundMoneyDevice(ptr_coffee_machine)));//возврат денег
	tree.insert(pair<string, Device*>("Give coffee", new GiveCoffeeDevice(ptr_coffee_machine)));//выдача кофе
	tree.insert(pair<string, Device*>("Return change", new ChangeReturnDevice(ptr_coffee_machine)));//сдача
	tree.insert(pair<string, Device*>("Display", new DisplayInformation(ptr_coffee_machine)));//вывод информации
	tree.insert(pair<string, Device*>("Take money", new TakeMoneyDevice(ptr_coffee_machine)));//принятие денег

	//устанавливаем связи для пульта управления
	controller->connections.insert(pair<string, Device*>("Give coffee", tree["Give coffee"])); //устройство выдачи кофе
	controller->connections.insert(pair<string, Device*>("Return change", tree["Return change"]));//устройство выдачи сдачи
	controller->connections.insert(pair<string, Device*>("Refund money", tree["Refund money"]));//устройство возврата денег
	controller->connections.insert(pair<string, Device*>("Display", tree["Display"]));//устройство вывода состояния и результата операции
	controller->connections.insert(pair<string, Device*>("Take money", tree["Take money"]));//устойство принятия денег

	//устройство выдачи денег посылает сигнал о выдаче дисплею
	tree["Refund money"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));

	//устройство выдачи кофе посылает сигнал о выдаче дисплею, а сам дисплей должен знать о том, как завершилась операция
	tree["Give coffee"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));
	tree["Display"]->connections.insert(pair<string, Device*>("Give coffee", tree["Give coffee"]));

	//устройство выдачи сдачи посылает сигнал о выдаче дисплею
	tree["Return change"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));

	//устройство принятия денег посылает сигнал о принятии денег
	tree["Take money"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));

	return false;
}



bool App::setup() {
	int n;
	cin >> n;//ввод количества сортов кофе
	ptr_coffee_machine->sorts.resize(n);
	//ввод самих сортов
	for (auto& x : ptr_coffee_machine->sorts) {
		cin >> x.coffee;
	}
	//ввод цены кофе
	for (auto& x : ptr_coffee_machine->sorts) {
		cin >> x.price;
	}
	//ввод количестов 5-ти и 10-ти рублевых монет
	cin >> ptr_coffee_machine->bank.fives;
	cin >> ptr_coffee_machine->bank.tens;
	return false;
}

bool App::work() {
	string command;
	DisplayInformation* display = (DisplayInformation * )controller->connections["Display"];
	controller->display("Start");//вывести состояние
	do {
		cin >> command;
		if (command == "Cancel") { //завершить программу
			controller->off();
			break;
		}
		else if (!command.find("Coffee")) controller->give_coffee();//выдать кофе
		else if (command == "Refund") {//вернуть деньги
			controller->refund_money();
			cin >> command; //когда вводится Refund money, cin считывает только Refund. cin >> command - просто забирает мусор в виде money.
			command = "";
		}
		else controller->take_money(command);//принять деньги
	} while (true);
	controller->display("Ready");//вывести состояние
	for (const auto& x : display->MAIN_STR) {
		cout << x;
	}
	return false;
}