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
		if (((i + 1) % 3 == 0) || (i == vec->size() - 1)) cout << endl;
	}
	cout << "============================================================================================" << endl;
}

int DessertManager::search(string name)
{
	for (int i = 0; i < (signed)vec->size(); i++)
		if (!(*vec)[i].getName().compare(name))
			return i;
	return -1;
}

void DessertManager::addItem()
{
	string name;
	int price;

	cout << "* �߰��� ��ǰ�� �̸�: "; cin >> name;
	if (search(name) != -1)
	{
		cout << "* ��ǰ ��Ͽ� �̹� �Է��Ͻ� ��ǰ�� �ֽ��ϴ�!" << endl << endl;
		return;
	}
	cout << "* �߰��� ��ǰ�� ����: "; cin >> price;
	cout << "* " << name << "(" << price << "��)�� ��Ͽ� �߰��Ǿ����ϴ�." << endl << endl;

	Dessert obj(name, price);
	(*vec).push_back(obj);
}

void DessertManager::modifyItem()
{
	string name;
	int temp, price;

	cout << "* ������ ��ǰ�� �̸�: "; cin >> name;
	if ((temp = search(name)) >= 0)
	{
		cout << "* ������ ��ǰ�� ����: "; cin >> price;
		if (price < 0) {
			cout << "* ��ǰ�� ������ 0�� �̸��� �� �����ϴ�." << endl << endl;
			return;
		}
		cout << "* " << name << "�� ������ " << (*vec)[temp].getPrice() << "������ " << price << "������ ����Ǿ����ϴ�." << endl << endl;
		(*vec)[temp].setPrice(price);
	}
	else cout << "* �Է��Ͻ� �̸��� ���� ��ǰ�� ã�� �� �������ϴ�." << endl << endl;
}

void DessertManager::eraseItem()
{
	string name;
	int temp;

	cout << "* ������ ��ǰ�� �̸�: "; cin >> name;

	if ((temp = search(name)) >= 0)
	{
		cout << "* ��ǰ '" << (*vec)[temp].getName() << "'�� �����Ǿ����ϴ�." << endl << endl;
		(*vec).erase((*vec).begin() + temp);
	}
	else cout << "* �Է��Ͻ� �̸��� ���� ��ǰ�� ã�� �� �������ϴ�." << endl << endl;
}