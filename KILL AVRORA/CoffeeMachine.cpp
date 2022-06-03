#include "CoffeeMachine.h"
CoffeeMachine::coffee_n_price& CoffeeMachine::find_coffee(const string& sort) {
	for (auto& x : sorts) {
		if (x.coffee == sort) return x;
	}
	return sorts[0];
}