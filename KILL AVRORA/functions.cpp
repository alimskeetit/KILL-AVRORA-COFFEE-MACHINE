#include "functions.h"
#include <iostream>
string decode_tens_and_fives(const string& message) {
	string to_return = "";
	int i = 0;
	for (; message[i] != ' '; to_return += message[i++]);
	to_return += " rub.,  5 * ";
	for (; i != message.length(); to_return += message[++i]);
	to_return += " rub.";
	return to_return;
}