#include <iostream>
#include <iomanip>
#include <fstream>
#include "DessertManager.h"
using namespace std;

DessertManager::DessertManager(vector<Dessert>* vec)
{
	this->vec = vec;
}

void DessertManager::fileRead()
{
	ifstream readFile("dessert.txt");

	if (readFile.is_open()) {
		string name;
		int price;
		while (readFile >> name >> price)
		{
			Dessert obj(name, price);
			vec->push_back(obj);
		}
	}
	// ������ �������� �ʴ� ���, dessert.txt�� ���� �����Ѵ�.
	else readFile.open("dessert.txt", ios::out | ios::trunc);
	readFile.close();
}

void DessertManager::fileWrite()
{
	ofstream writeFile("dessert.txt");

	if (writeFile.is_open()) {
		for (auto i : *vec)
			writeFile << i.getName() << '\t' << i.getPrice() << endl;
		writeFile.close();
	}
	else cout << "������ ���� ���� ������ �߻��Ͽ� �� �� �������ϴ�." << endl;
}

void DessertManager::showList()
{
	cout << "============================================================================================" << endl;
	for (vector<Dessert>::size_type i = 0; i < vec->size(); i++)
	{
		cout << setw(3) << i + 1 << ' ' << setw(18) << (*vec)[i].getName() << ' ' << setw(5) << (*vec)[i].getPrice() << '\t';
		if ((i + 1) % 3 == 0) cout << endl;
	}
	cout << "============================================================================================" << endl;
}