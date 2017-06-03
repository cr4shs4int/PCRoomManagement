#include <iostream>
#include "User.h"
using namespace std;

void User::order(vector<Dessert> vec) {
	int menu, money;

	cout << "* �޴��� �����ϼ���: "; cin >> menu;
	if (menu >= 1 && menu <= (signed)vec.size())
	{
		cout << "* ������ �ݾ��� " << vec[menu - 1].getPrice() << "�� �Դϴ�." << endl;
		cout << "* ���� �ܾ��� " << getMoney() << "�� �Դϴ�." << endl << endl;
		cout << "* �߰��� ������ ���� �ݾ��� �Է��ϼ���: "; cin >> money;

		setMoney(getMoney() + money);
		if (vec[menu - 1].getPrice() > getMoney())
		{
			cout << "* ���� ���ڶ� �ش� ��ǰ�� ������ �� �����ϴ�." << endl;
			return;
		}
		setMoney(getMoney() - vec[menu - 1].getPrice());
		cout << "* " << vec[menu - 1].getName() << "(" << vec[menu - 1].getPrice() << "��)��(��) �����Ͽ����ϴ�." << endl;
		cout << "* ���� �ܾ��� " << getMoney() << "�� �Դϴ�." << endl << endl;
	}
	else cout << "* �Է��Ͻ� ��ȣ�� �ش��ϴ� �޴��� �������� �ʽ��ϴ�." << endl << endl;
}