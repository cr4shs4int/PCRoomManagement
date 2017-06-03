#include <iostream>
#include <thread>

#include "AccountManager.h"
#include "DessertManager.h"
// #include "CWindow.h"
using namespace std;

int main()
{
	int choice, price, temp;
	bool isRun = true, isBack = false;
	User* pUser; Account *pAccount;
	string name;
	vector<Account*> vec; AccountManager acManager(&vec);
	vector<Dessert> vdes; DessertManager desManager(&vdes);

	acManager.fileRead();
	desManager.fileRead();

	// multithread�� ���ؼ� 1�ʸ��� ��ǻ�͸� ������� ������ remainingTime�� 1��ŭ ���ҽ�Ų��.
	thread timeThread{ [&vec, &isRun] {
		while (isRun) {
			this_thread::sleep_for(1s);
			for (auto i : vec)
				if (i->getIsUse() && i->getRemainingTime() > 0)
					i->setRemainingTime(i->getRemainingTime() - 1);
		}
	} };

	while (true) {
		cout << "1. �α��� 2. ȸ������ 3. ����" << endl;
		cout << "�޴��� �����ϼ���: "; cin >> choice;
		cout << endl;

		switch (choice) {
			case 1:
				if ((pAccount = acManager.login()) == nullptr) continue;

				// ����, ������ �������� �α����� �� ���̶��
				if (!pAccount->getType().compare("Admin"))
				{
					bool isLogout = false;

					while (!isLogout) {
						cout << "1. ��ǰ���� 2. �α׾ƿ�" << endl;
						cout << "�޴��� �����ϼ���: "; cin >> choice;
						cout << endl;

						switch (choice) {
							case 1:
								isBack = false;
								while (!isBack) {
									cout << "1. ��ǰ��ȸ 2. ��ǰ���� 3. ��ǰ�߰� 4. ��ǰ���� 5. ���ư���" << endl;
									cout << "�޴��� �����ϼ���: "; cin >> choice;
									cout << endl;

									switch (choice) {
										case 1:
											desManager.showList(); cout << endl;
											break;
										case 2:
											cout << "* ������ ��ǰ�� �̸�: "; cin >> name;
											if ((temp = desManager.search(name)) >= 0)
											{
												cout << "* ������ ��ǰ�� ����: "; cin >> price;
												if (price < 0) {
													cout << "* ��ǰ�� ������ 0�� �̸��� �� �����ϴ�." << endl << endl;
													continue;
												}
												cout << "* " << name << "�� ������ " << vdes[temp].getPrice() << "������ " << price << "������ ����Ǿ����ϴ�." << endl << endl;
												vdes[temp].setPrice(price);
											}
											else cout << "* �Է��Ͻ� �̸��� ���� ��ǰ�� ã�� �� �������ϴ�." << endl << endl;
											break;
										case 3:
											cout << "* �߰��� ��ǰ�� �̸�: "; cin >> name;
											if (desManager.search(name) != -1)
											{
												cout << "* ��ǰ ��Ͽ� �̹� �Է��Ͻ� ��ǰ�� �ֽ��ϴ�!" << endl << endl;
												continue;
											}
											cout << "* �߰��� ��ǰ�� ����: "; cin >> price;
											cout << "* " << name << "(" << price << "��)�� ��Ͽ� �߰��Ǿ����ϴ�." << endl << endl;
											{
												Dessert obj(name, price);
												vdes.push_back(obj);
											}
											break;
										case 4:
											cout << "* ������ ��ǰ�� �̸�: "; cin >> name;

											if ((temp = desManager.search(name)) >= 0)
											{
												cout << "* ��ǰ '" << vdes[temp].getName() << "'�� �����Ǿ����ϴ�." << endl << endl;
												vdes.erase(vdes.begin() + temp);
											}
											else cout << "* �Է��Ͻ� �̸��� ���� ��ǰ�� ã�� �� �������ϴ�." << endl << endl;
											break;
										case 5:
											isBack = true;
											break;
									}
								}
								break;
							case 2:
								acManager.logout(pAccount);
								isLogout = true;
								break;
							default:
								cout << "�Է��� ��ȣ�� �ش��ϴ� �޴��� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
						}
					}
					continue;
				}

				// ����, ���� �������� �α����� �� ���̶��
				if (!pAccount->getType().compare("User") && (pUser = static_cast<User*>(pAccount)))
				{
					bool isLogout = false;

					// �α��� �� ����ڿ��� �´� �޴��� ����Ѵ�.
					while (!isLogout) {
						cout << "1. �ֹ� 2. �ð� Ȯ�� 3. �α׾ƿ�" << endl;
						cout << "�޴��� �����ϼ���: "; cin >> choice;
						cout << endl;

						switch (choice) {
							case 1:
								desManager.showList();
								cout << "�޴��� �����ϼ���: "; cin >> choice;
								break;
							case 2:
								cout << "* " << pUser->getHour() << "�ð� " << pUser->getMinute() << "�� ���ҽ��ϴ�." << endl << endl;
								break;
							case 3:
								acManager.logout(pAccount);
								isLogout = true;
								break;
							default:
								cout << "�Է��� ��ȣ�� �ش��ϴ� �޴��� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
						}
					}
				}
				break;
			case 2: acManager.registerAccount(); break;
			case 3: // ���� �޴�
				acManager.fileWrite();
				desManager.fileWrite();
				// ������ timeThread�� �۾��� ��� ���� ������ ��ٸ���.
				isRun = false;
				timeThread.join();
				return 0;
			default:
				cout << "�Է��� ��ȣ�� �ش��ϴ� �޴��� �������� �ʽ��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
		}
	}
	return 0;
}