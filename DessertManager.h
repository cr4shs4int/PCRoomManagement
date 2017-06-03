#ifndef DESSERTMANAGER_H
#define DESSERTMANAGER_H

#include <vector>
#include "Dessert.h"

using std::vector;

class DessertManager {
private:
	vector<Dessert>* vec;
public:
	DessertManager(vector<Dessert>*);

	void fileRead();
	void fileWrite();
	void showList();
	int search(string);
};
#endif