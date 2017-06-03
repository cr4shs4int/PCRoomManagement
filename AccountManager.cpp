#include <fstream>
#include <iostream>
#include <iomanip>
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

void AccountManager::addItem()
{
	string id, password;

	cout << "* 추가할 계정의 아이디: "; cin >> id;
	if (search(id) != nullptr)
	{
		cout << "* 계정 목록에 이미 입력하신 계정의 아이디가 존재합니다!" << endl << endl;
		return;
	}
	cout << "* 추가할 계정의 비밀번호: "; cin >> password;
	cout << "* 계정 " << id << "이 목록에 추가되었습니다." << endl << endl;

	(*vec).push_back(new User(id, password));
}

void AccountManager::eraseItem()
{
	string id;
	Account *pAccount;

	cout << "* 삭제할 계정의 아이디: "; cin >> id;
	
	for (int i = 0; i < (signed)vec->size(); i++)
	{
		if (!(*vec)[i]->getId().compare(id)) {
			if (!(*vec)[i]->getType().compare("Admin"))
			{
				cout << "* 관리자 계정을 삭제할 수는 없습니다." << endl << endl;
				return;
			}
			cout << "* 계정 " << id << "이 삭제되었습니다." << endl << endl;
			delete (*vec)[i];
			(*vec).erase((*vec).begin() + i);
			return;
		}
	}
	cout << "* 입력하신 아이디를 가진 계정을 찾을 수 없었습니다." << endl << endl;
}

void AccountManager::showList()
{
	cout << "================================================" << endl;
	cout << setw(10) << "아이디" << setw(15) << "비밀번호" << setw(10) << "로그인" << setw(13) << "남은 시간" << endl;
	cout << "================================================" << endl;
	for (vector<Account*>::size_type i = 0; i < vec->size(); i++)
	{
		cout << setw(10) << (*vec)[i]->getId() << setw(15) << (*vec)[i]->getPassword() << setw(10) << ((*vec)[i]->getIsUse() ? "로그인" : "로그아웃");
		if ((*vec)[i]->getType().compare("Admin"))
		{
			string time = to_string((*vec)[i]->getHour()) + "시간 " + to_string((*vec)[i]->getMinute()) + "분";
			cout << setw(13) << time;
		}
		cout << endl;
	}
	cout << "================================================" << endl << endl;
}

void AccountManager::modifyItem()
{
	string id, password;
	User *pUser;

	cout << "* 수정할 계정의 아이디: "; cin >> id;

	Account* pAccount = search(id);
	if (pAccount != nullptr && !pAccount->getType().compare("User") && (pUser = static_cast<User*>(pAccount)))
	{
		cout << "* 수정할 계정의 비밀번호: "; cin >> password;
		cout << "* " << id << "의 비밀번호가 정상적으로 변경되었습니다." << endl << endl;
		pUser->setPassword(password);
	}
	else cout << "* 입력하신 아이디를 가진 계정을 찾을 수 없었습니다." << endl << endl;
}