#include "CoffeeMachine.h"
#include "App.h"

int main() {
	App app(new CoffeeMachine);
	app.build_tree_objects();
	app.setup();
	app.work();
}