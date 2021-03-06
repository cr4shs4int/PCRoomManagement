#include <iostream>
#include <thread>

#include "User.h"
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

	// multithread를 통해서 1초마다 컴퓨터를 사용중인 계정의 remainingTime을 1만큼 감소시킨다.
	thread timeThread{ [&vec, &isRun] {
		while (isRun) {
			this_thread::sleep_for(1s);
			for (auto i : vec)
				if (i->getIsUse() && i->getRemainingTime() > 0)
					i->setRemainingTime(i->getRemainingTime() - 1);
		}
	} };

	while (true) {
		cout << "1. 로그인 2. 회원가입 3. 종료" << endl;
		cout << "메뉴를 선택하세요: "; cin >> choice;
		cout << endl;

		switch (choice) {
			case 1:
				if ((pAccount = acManager.login()) == nullptr) continue;

				// 만약, 관리자 계정으로 로그인을 한 것이라면
				if (!pAccount->getType().compare("Admin"))
				{
					bool isLogout = false;

					while (!isLogout) {
						cout << "1. 상품관리 2. 계정관리 3. 로그아웃" << endl;
						cout << "메뉴를 선택하세요: "; cin >> choice;
						cout << endl;

						switch (choice) {
							case 1:
								isBack = false;
								while (!isBack) {
									cout << "1. 상품조회 2. 상품수정 3. 상품추가 4. 상품삭제 5. 돌아가기" << endl;
									cout << "메뉴를 선택하세요: "; cin >> choice;
									cout << endl;

									switch (choice) {
										case 1: desManager.showList(); cout << endl; break;
										case 2: desManager.modifyItem(); break;
										case 3: desManager.addItem(); break;
										case 4: desManager.eraseItem(); break;
										case 5: isBack = true; break;
										default: cout << "입력한 번호에 해당하는 메뉴가 존재하지 않습니다. 다시 입력해주세요." << endl << endl;
									}
								}
								break;
							case 2:
								isBack = false;
								while (!isBack) {
									cout << "1. 계정조회 2. 계정수정 3. 계정추가 4. 계정삭제 5. 돌아가기" << endl;
									cout << "메뉴를 선택하세요: "; cin >> choice;
									cout << endl;

									switch (choice) {
										case 1: acManager.showList(); break;
										case 2: acManager.modifyItem(); break;
										case 3: acManager.addItem(); break;
										case 4: acManager.eraseItem(); break;
										case 5: isBack = true; break;
										default: cout << "입력한 번호에 해당하는 메뉴가 존재하지 않습니다. 다시 입력해주세요." << endl << endl;
									}
								}
								break;
							case 3:
								acManager.logout(pAccount);
								isLogout = true;
								break;
							default:
								cout << "입력한 번호에 해당하는 메뉴가 존재하지 않습니다. 다시 입력해주세요." << endl << endl;
						}
					}
					continue;
				}

				// 만약, 유저 계정으로 로그인을 한 것이라면
				if (!pAccount->getType().compare("User") && (pUser = static_cast<User*>(pAccount)))
				{
					bool isLogout = false;

					// 로그인 후 사용자에게 맞는 메뉴를 출력한다.
					while (!isLogout) {
						cout << "1. 주문 2. 시간 확인 3. 돌아가기 4. 로그아웃" << endl;
						cout << "메뉴를 선택하세요: "; cin >> choice;
						cout << endl;

						switch (choice) {
							case 1:
								desManager.showList();
								pUser->order(vdes);
								break;
							case 2:
								cout << "* " << pUser->getHour() << "시간 " << pUser->getMinute() << "분 남았습니다." << endl << endl;
								break;
							case 3:
								isLogout = true;
								break;
							case 4:
								acManager.logout(pAccount);
								isLogout = true;
								break;
							default:
								cout << "입력한 번호에 해당하는 메뉴가 존재하지 않습니다. 다시 입력해주세요." << endl << endl;
						}
					}
				}
				break;
			case 2: acManager.registerAccount(); break;
			case 3: // 종료 메뉴
				acManager.fileWrite();
				desManager.fileWrite();
				// 스레드 timeThread의 작업이 모두 끝날 때까지 기다린다.
				isRun = false;
				timeThread.join();
				return 0;
			default:
				cout << "입력한 번호에 해당하는 메뉴가 존재하지 않습니다. 다시 입력해주세요." << endl << endl;
		}
	}
	return 0;
}