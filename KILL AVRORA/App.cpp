#include "App.h"
#include <iostream>
using namespace std;

bool App::build_tree_objects() {
	controller = new Controller(ptr_coffee_machine);//������� ����� ����������
	//������ ������, �������� � �������� ����������
	tree.insert(pair<string, Device*>("Controller", controller)); //�������� �����
	tree.insert(pair<string, Device*>("Refund money", new RefundMoneyDevice(ptr_coffee_machine)));//������� �����
	tree.insert(pair<string, Device*>("Give coffee", new GiveCoffeeDevice(ptr_coffee_machine)));//������ ����
	tree.insert(pair<string, Device*>("Return change", new ChangeReturnDevice(ptr_coffee_machine)));//�����
	tree.insert(pair<string, Device*>("Display", new DisplayInformation(ptr_coffee_machine)));//����� ����������
	tree.insert(pair<string, Device*>("Take money", new TakeMoneyDevice(ptr_coffee_machine)));//�������� �����

	//������������� ����� ��� ������ ����������
	controller->connections.insert(pair<string, Device*>("Give coffee", tree["Give coffee"])); //���������� ������ ����
	controller->connections.insert(pair<string, Device*>("Return change", tree["Return change"]));//���������� ������ �����
	controller->connections.insert(pair<string, Device*>("Refund money", tree["Refund money"]));//���������� �������� �����
	controller->connections.insert(pair<string, Device*>("Display", tree["Display"]));//���������� ������ ��������� � ���������� ��������
	controller->connections.insert(pair<string, Device*>("Take money", tree["Take money"]));//��������� �������� �����

	//���������� ������ ����� �������� ������ � ������ �������
	tree["Refund money"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));

	//���������� ������ ���� �������� ������ � ������ �������, � ��� ������� ������ ����� � ���, ��� ����������� ��������
	tree["Give coffee"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));
	tree["Display"]->connections.insert(pair<string, Device*>("Give coffee", tree["Give coffee"]));

	//���������� ������ ����� �������� ������ � ������ �������
	tree["Return change"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));

	//���������� �������� ����� �������� ������ � �������� �����
	tree["Take money"]->connections.insert(pair<string, Device*>("Display", tree["Display"]));

	return false;
}



bool App::setup() {
	int n;
	cin >> n;//���� ���������� ������ ����
	ptr_coffee_machine->sorts.resize(n);
	//���� ����� ������
	for (auto& x : ptr_coffee_machine->sorts) {
		cin >> x.coffee;
	}
	//���� ���� ����
	for (auto& x : ptr_coffee_machine->sorts) {
		cin >> x.price;
	}
	//���� ���������� 5-�� � 10-�� �������� �����
	cin >> ptr_coffee_machine->bank.fives;
	cin >> ptr_coffee_machine->bank.tens;
	return false;
}

bool App::work() {
	string command;
	DisplayInformation* display = (DisplayInformation * )controller->connections["Display"];
	controller->display("Start");//������� ���������
	do {
		cin >> command;
		if (command == "Cancel") { //��������� ���������
			controller->off();
			break;
		}
		else if (!command.find("Coffee")) controller->give_coffee();//������ ����
		else if (command == "Refund") {//������� ������
			controller->refund_money();
			cin >> command; //����� �������� Refund money, cin ��������� ������ Refund. cin >> command - ������ �������� ����� � ���� money.
			command = "";
		}
		else controller->take_money(command);//������� ������
	} while (true);
	controller->display("Ready");//������� ���������
	for (const auto& x : display->MAIN_STR) {
		cout << x;
	}
	return false;
}