#ifndef device_h
#define  device_h
#include "CoffeeMachine.h"
#include "functions.h"
#include <string>
#include <map>

class Device {
protected:
	CoffeeMachine* ptr_coffee_machine;
	bool ready = true;
	bool last_operation = false;
public:
	bool get_last_operation() { return last_operation; };
	Device(CoffeeMachine* ptr) : ptr_coffee_machine(ptr) {};
	bool is_ready() { return ready; }
	virtual void handler(const string& command = "", const string& message = "") = 0;
	map<string, Device*> connections;
};

class Controller : public Device {
public:
	void handler(const string& command = "", const string& message = "") {};
	Controller(CoffeeMachine* ptr_coffee_machine) : Device(ptr_coffee_machine) {}
	bool give_coffee();
	bool refund_money();
	bool take_money(const string& money);
	bool display(const string& command);
	bool off();
};

class RefundMoneyDevice : public Device {
	bool refund_money();
public:
	void handler(const string& command = "", const string& message = "");
	RefundMoneyDevice(CoffeeMachine* ptr_coffee_machine) : Device(ptr_coffee_machine) {}
};

class GiveCoffeeDevice : public Device {
	bool give_coffee();
public:
	void handler(const string& command = "", const string& message = "");
	GiveCoffeeDevice(CoffeeMachine* ptr_coffee_machine) : Device(ptr_coffee_machine) {}
};

class ChangeReturnDevice : public Device {
	bool return_change();
public:
	ChangeReturnDevice(CoffeeMachine* ptr_coffee_machine) : Device(ptr_coffee_machine) {}
	void handler(const string& command = "", const string& message = "");
};

class TakeMoneyDevice : public Device {
public:
	void handler(const string& money = "", const string& message = "");
	TakeMoneyDevice(CoffeeMachine* ptr_coffee_machine) : Device(ptr_coffee_machine) {}
	bool take_money(const string& string_money);
};

class DisplayInformation : public Device {
public:
	DisplayInformation(CoffeeMachine* ptr_coffee_machine) : Device(ptr_coffee_machine) {}
	void handler(const string& command = "", const string& message = "");
	bool display_information();
	string MAIN_STR;
};

#endif // !device_h