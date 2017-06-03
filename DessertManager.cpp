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
	// 파일이 존재하지 않는 경우, dessert.txt를 새로 생성한다.
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
	else cout << "파일을 여는 도중 에러가 발생하여 쓸 수 없었습니다." << endl;
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

	cout << "* 추가할 상품의 이름: "; cin >> name;
	if (search(name) != -1)
	{
		cout << "* 상품 목록에 이미 입력하신 상품이 있습니다!" << endl << endl;
		return;
	}
	cout << "* 추가할 상품의 가격: "; cin >> price;
	cout << "* " << name << "(" << price << "원)이 목록에 추가되었습니다." << endl << endl;

	Dessert obj(name, price);
	(*vec).push_back(obj);
}

void DessertManager::modifyItem()
{
	string name;
	int temp, price;

	cout << "* 수정할 상품의 이름: "; cin >> name;
	if ((temp = search(name)) >= 0)
	{
		cout << "* 수정할 상품의 가격: "; cin >> price;
		if (price < 0) {
			cout << "* 상품의 가격은 0원 미만일 수 없습니다." << endl << endl;
			return;
		}
		cout << "* " << name << "의 가격이 " << (*vec)[temp].getPrice() << "원에서 " << price << "원으로 변경되었습니다." << endl << endl;
		(*vec)[temp].setPrice(price);
	}
	else cout << "* 입력하신 이름을 가진 상품을 찾을 수 없었습니다." << endl << endl;
}

void DessertManager::eraseItem()
{
	string name;
	int temp;

	cout << "* 삭제할 상품의 이름: "; cin >> name;

	if ((temp = search(name)) >= 0)
	{
		cout << "* 상품 '" << (*vec)[temp].getName() << "'가 삭제되었습니다." << endl << endl;
		(*vec).erase((*vec).begin() + temp);
	}
	else cout << "* 입력하신 이름을 가진 상품을 찾을 수 없었습니다." << endl << endl;
}