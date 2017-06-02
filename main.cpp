#include <iostream>
#include <thread>

#include "AccountManager.h"
#include "DessertManager.h"
// #include "Dessert.h"
// #include "CWindow.h"
using namespace std;

int main()
{
	int choice;
	bool isRun = true;
	User* pUser; Account *pAccount;
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