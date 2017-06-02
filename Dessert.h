#ifndef DESSERT_H
#define DESSERT_H

#include <string>
using std::string;

class Dessert {
private:
	string name;
	int price;
public:
	Dessert() { };
	Dessert(string name, int price) : name(name), price(price) { };

	// virtual void show() const;

	// getter
	string getName() const { return name; };
	int getPrice() const { return price; };
};
#endif