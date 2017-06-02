#include <fstream>
#include <iostream>
#include "AccountManager.h"
using namespace std;

AccountManager::AccountManager(vector<Account*>* vec)
{
	this->vec = vec;
	this->vec->push_back(new Admin("admin", "admin"));
}

AccountManager::~AccountManager() {
	// new 연산자를 통해 동적 할당한 메모리는 아래와 같이 해제해주어야 한다.
	for (auto i : *vec)
		delete i;
}

void AccountManager::fileRead()
{
	ifstream readFile("member.txt");

	if (readFile.is_open()) {
		string id, password;
		int money, remainingTime;
		while (readFile >> id >> password >> money >> remainingTime)
			vec->push_back(new User(id, password, money, remainingTime));
	}
	// 파일이 존재하지 않는 경우, member.txt를 새로 생성한다.
	else readFile.open("member.txt", ios::out | ios::trunc);
	readFile.close();
}

void AccountManager::fileWrite()
{
	ofstream writeFile("member.txt");

	if (writeFile.is_open()) {
		for (auto i : *vec)
			if (i->getType().compare("Admin"))
				writeFile << i->getId() << '\t' << i->getPassword() << '\t' << i->getMoney() << '\t' << i->getRemainingTime() << endl;
		writeFile.close();
	}
	else cout << "파일을 여는 도중 에러가 발생하여 쓸 수 없었습니다." << endl;
}

Account* AccountManager::search(string id)
{
	for (auto i : *vec)
		if (!i->getId().compare(id))
			return i;
	return nullptr;
}

Account* AccountManager::login()
{
	Account* pAccount = nullptr;
	string id, password;

	cout << "* 아이디: "; cin >> id;
	cout << "* 비밀번호: "; cin >> password;

	if ((pAccount = search(id)) != nullptr)
	{
		// 발견한 아이디의 비밀번호와 입력한 비밀번호가 일치해야 한다.
		if (pAccount->getPassword().compare(password)) {
			cout << "비밀번호가 일치하지 않습니다." << endl << endl;
			return nullptr;
		}
		// 유저가 컴퓨터를 사용 중임을 표시한다.
		pAccount->setIsUse(true);
		cout << endl << "* " << (!pAccount->getType().compare("Admin") ? "관리자" : id) << "님, 환영합니다!" << endl << endl;
		return pAccount;
	}
	else {
		cout << "입력하신 아이디가 존재하지 않습니다." << endl << endl;
		return nullptr;
	}
}

void AccountManager::logout(Account* pAccount)
{
	cout << "안전하게 로그아웃 되었습니다." << endl << endl;
	pAccount->setIsUse(false);
}

void AccountManager::registerAccount()
{
	string id, password;

	while (true) {
		cout << "* 아이디: "; cin >> id;
		if (search(id)) cout << "동일한 아이디가 존재합니다. 다시 입력해주세요." << endl << endl;
		else break;
	}
	cout << "* 비밀번호: "; cin >> password;
	vec->push_back(new User(id, password));
	cout << "회원가입이 완료되었습니다." << endl << endl;
}