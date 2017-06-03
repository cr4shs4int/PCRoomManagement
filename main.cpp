#include <iostream>
#include <thread>

#include "AccountManager.h"
#include "DessertManager.h"
// #include "CWindow.h"
using namespace std;

int main()
{
	int choice;
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
						cout << "1. ��ǰ���� 2. �������� 3. �α׾ƿ�" << endl;
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
										case 1: desManager.showList(); cout << endl; break;
										case 2: desManager.modifyItem(); break;
										case 3: desManager.addItem(); break;
										case 4: desManager.eraseItem(); break;
										case 5: isBack = true; break;
									}
								}
								break;
							case 2:
								isBack = false;
								while (!isBack) {
									cout << "1. ������ȸ 2. �������� 3. �����߰� 4. �������� 5. ���ư���" << endl;
									cout << "�޴��� �����ϼ���: "; cin >> choice;
									cout << endl;

									switch (choice) {
										case 1: acManager.showList(); break;
										case 2: acManager.modifyItem(); break;
										case 3: acManager.addItem(); break;
										case 4: acManager.eraseItem(); break;
										case 5: isBack = true; break;
									}
								}
								break;
							case 3:
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