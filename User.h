#ifndef USER_H
#define USER_H

#include <vector>
#include "Account.h"
#include "Dessert.h"

using std::vector;

class User : public Account {
public:
	User(string id, string password, int money = 0, int remainingTime = 0) : Account(id, password, money, remainingTime) { }

	void order(vector<Dessert>);

	string getType() const { return "User"; }
};
#endif
