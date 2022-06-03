#ifndef app_h
#define app_h
#include "CoffeeMachine.h"
#include "Device.h"
class App : public Device {
	CoffeeMachine* ptr_coffee_machine;
	map<string, Device*> tree;
public:
	void handler(const string& command = "", const string& message = "") {};
	App(CoffeeMachine* ptr_coffee_machine) :ptr_coffee_machine(ptr_coffee_machine), Device(ptr_coffee_machine) {}
	Controller* controller;
	bool build_tree_objects();
	bool setup();
	bool work();
};
#endif