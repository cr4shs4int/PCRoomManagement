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

	void addItem();
	void modifyItem();
	void eraseItem();
	
	void fileRead();
	void fileWrite();
	void showList();
	int search(string);
};
#endif