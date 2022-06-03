#include "Device.h"
#include <iostream>
using namespace std;

bool Controller::give_coffee() {
	connections["Give coffee"]->handler();//выдача кофе
	connections["Return change"]->handler();//сдача
	connections["Display"]->handler("Ready");
	return false;
}

bool Controller::refund_money() {
	connections["Refund money"]->handler();
	return false;
}

bool Controller::take_money(const string& money) {
	connections["Take money"]->handler(money);
	return false;
}

bool Controller::display(const string& command) {
	connections["Display"]->handler(command);
	return false;
}

bool Controller::off() {
	ptr_coffee_machine->set_ready(false);
	return false;
}



void RefundMoneyDevice::handler(const string& command, const string& message) {
	if (ready) refund_money();
	if (ready) connections["Display"]->handler("Ready");
	//MAIN_STR +="IN HANDLER\n";
}

bool RefundMoneyDevice::refund_money() {
	auto ptr = ptr_coffee_machine;//для простоты
	int tens = ptr->bank.cash_in / 10;
	if (tens > ptr->bank.tens) tens = ptr->bank.tens;
	int fives = (ptr->bank.cash_in - tens * 10) / 5;
	ptr->bank.tens -= tens;
	ptr->bank.fives -= fives;
	ptr->bank.cash_in -= (tens * 10 + fives * 5);
	connections["Display"]->handler("Refund money", to_string(tens) + " " + to_string(fives) + " ");
	return false;
}





bool GiveCoffeeDevice::give_coffee() {
	string sort;
	int price;
	cin >> sort;
	price = ptr_coffee_machine->find_coffee(sort).price;
	if (price <= ptr_coffee_machine->bank.cash_in) {
		ptr_coffee_machine->bank.cash_in -= price;
		last_operation = false;
		connections["Display"]->handler("Give coffee", sort);
		//MAIN_STR +="\nTake the coffee " << sort;
	}
	else {
		last_operation = true;
		connections["Display"]->handler("Give coffee");//MAIN_STR +="\nThere is not enough money";
	}
	return false;
}

void GiveCoffeeDevice::handler(const string& command, const string& message) {
	if (ready) give_coffee();
}

bool ChangeReturnDevice::return_change() {
	int tens, fives;
	auto ptr = ptr_coffee_machine;//для простоты
	tens = ptr->bank.cash_in / 10;
	if (tens > ptr->bank.tens) tens = ptr->bank.tens;
	fives = (ptr->bank.cash_in - tens * 10) / 5;
	if (tens <= ptr->bank.tens && fives <= ptr->bank.fives) {
		ptr->bank.tens -= tens;
		ptr->bank.fives -= fives;
		if (tens == fives == 0) connections["Display"]->handler("Return change", to_string(tens) + " " + to_string(fives) + " ");
		ptr->bank.cash_in -= (tens * 10 + fives * 5);
	}
	return false;
}

void ChangeReturnDevice::handler(const string& command, const string& message) {
	if (ready) return_change();
}




bool TakeMoneyDevice::take_money(const string& string_money) {
	int money = stoi(string_money);
	if (money == 50 || money == 100) {
		int tens, fives;
		tens = money / 10;
		if (tens > ptr_coffee_machine->bank.tens) tens = ptr_coffee_machine->bank.tens;
		fives = (money - tens * 10) / 5;
		if (tens > ptr_coffee_machine->bank.tens || fives > ptr_coffee_machine->bank.fives) {
			connections["Display"]->handler("Take money");
			//MAIN_STR +="\nTake the money back, no change";
			return false;
		}
	}
	ptr_coffee_machine->bank.cash_in += money;
	connections["Display"]->handler("Amount");
	return false;
}

void TakeMoneyDevice::handler(const string& money, const string& message) {
	if (ready) take_money(money);
}



bool DisplayInformation::display_information()
{
	return false;
}

void DisplayInformation::handler(const string& command, const string& message) {
	if (command == "Refund money") {
		MAIN_STR += "\nTake the money: 10 * " + decode_tens_and_fives(message); //функция, которая расшифровывает, то, что в message. В message такая инфа: "5 3" - типо 5 десяток, 3 пятерки.
	}
	if (command == "Give coffee") {
		if (connections["Give coffee"]->get_last_operation()) {
			MAIN_STR +="\nThere is not enough money";
		}
		else MAIN_STR +="\nTake the coffee " + message;
	}
	if (command == "Return change") {
		MAIN_STR +="\nTake the change: 10 * " + decode_tens_and_fives(message); //функция, которая расшифровывает, то, что в message. В message такая инфа: "5 3" - типо 5 десяток, 3 пятерки.
	}
	if (command == "Take money") MAIN_STR +="\nTake the money back, no change";
	if (command == "Amount") MAIN_STR += "\nThe amount: " + to_string(ptr_coffee_machine->bank.cash_in);
	if (command == "Start") {
		if (ptr_coffee_machine->is_ready()) MAIN_STR +="Ready to work";
		else MAIN_STR +="Turned off";
	}
	if (command == "Ready") {
		if (ptr_coffee_machine->is_ready()) MAIN_STR +="\nReady to work";
		else MAIN_STR +="\nTurned off";
	}
}