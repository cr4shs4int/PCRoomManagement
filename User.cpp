#include <iostream>
#include "User.h"
using namespace std;

void User::order(vector<Dessert> vec) {
	int menu;

	cout << "* �޴��� �����ϼ���: "; cin >> menu;
	if (menu >= 1 && menu <= vec.size())
	{
		if (vec[menu - 1].getPrice() > getMoney())
		{
			cout << "* ���� ���ڶ� �ش� ��ǰ�� ������ �� �����ϴ�." << endl << endl;
			return;
		}
		setMoney(getMoney() - vec[menu - 1].getPrice());
		cout << "* " << vec[menu - 1].getName() << "(" << vec[menu - 1].getPrice() << "��)��(��) �����Ͽ����ϴ�." << endl;
		cout << "* ���� �ܾ��� " << getMoney() << "�� �Դϴ�." << endl << endl;
	}
	else cout << "* �Է��Ͻ� ��ȣ�� �ش��ϴ� �޴��� �������� �ʽ��ϴ�." << endl << endl;
}