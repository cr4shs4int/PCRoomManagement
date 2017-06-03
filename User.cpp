#include <iostream>
#include "User.h"
using namespace std;

void User::order(vector<Dessert> vec) {
	int menu, money;

	cout << "* 메뉴를 선택하세요: "; cin >> menu;
	if (menu >= 1 && menu <= (signed)vec.size())
	{
		cout << "* 결제할 금액은 " << vec[menu - 1].getPrice() << "원 입니다." << endl;
		cout << "* 현재 잔액은 " << getMoney() << "원 입니다." << endl << endl;
		cout << "* 추가로 넣으실 돈의 금액을 입력하세요: "; cin >> money;

		setMoney(getMoney() + money);
		if (vec[menu - 1].getPrice() > getMoney())
		{
			cout << "* 돈이 모자라서 해당 상품을 구입할 수 없습니다." << endl;
			return;
		}
		setMoney(getMoney() - vec[menu - 1].getPrice());
		cout << "* " << vec[menu - 1].getName() << "(" << vec[menu - 1].getPrice() << "원)을(를) 구입하였습니다." << endl;
		cout << "* 현재 잔액은 " << getMoney() << "원 입니다." << endl << endl;
	}
	else cout << "* 입력하신 번호에 해당하는 메뉴가 존재하지 않습니다." << endl << endl;
}