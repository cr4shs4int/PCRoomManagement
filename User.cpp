#include <iostream>
#include "User.h"
using namespace std;

void User::order(vector<Dessert> vec) {
	int menu;

	cout << "* 메뉴를 선택하세요: "; cin >> menu;
	if (menu >= 1 && menu <= vec.size())
	{
		if (vec[menu - 1].getPrice() > getMoney())
		{
			cout << "* 돈이 모자라서 해당 상품을 구입할 수 없습니다." << endl << endl;
			return;
		}
		setMoney(getMoney() - vec[menu - 1].getPrice());
		cout << "* " << vec[menu - 1].getName() << "(" << vec[menu - 1].getPrice() << "원)을(를) 구입하였습니다." << endl;
		cout << "* 현재 잔액은 " << getMoney() << "원 입니다." << endl << endl;
	}
	else cout << "* 입력하신 번호에 해당하는 메뉴가 존재하지 않습니다." << endl << endl;
}