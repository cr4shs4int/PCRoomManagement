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
	// new �����ڸ� ���� ���� �Ҵ��� �޸𸮴� �Ʒ��� ���� �������־�� �Ѵ�.
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
	// ������ �������� �ʴ� ���, member.txt�� ���� �����Ѵ�.
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
	else cout << "������ ���� ���� ������ �߻��Ͽ� �� �� �������ϴ�." << endl;
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

	cout << "* ���̵�: "; cin >> id;
	cout << "* ��й�ȣ: "; cin >> password;

	if ((pAccount = search(id)) != nullptr)
	{
		// �߰��� ���̵��� ��й�ȣ�� �Է��� ��й�ȣ�� ��ġ�ؾ� �Ѵ�.
		if (pAccount->getPassword().compare(password)) {
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl << endl;
			return nullptr;
		}
		// ������ ��ǻ�͸� ��� ������ ǥ���Ѵ�.
		pAccount->setIsUse(true);
		cout << endl << "* " << (!pAccount->getType().compare("Admin") ? "������" : id) << "��, ȯ���մϴ�!" << endl << endl;
		return pAccount;
	}
	else {
		cout << "�Է��Ͻ� ���̵� �������� �ʽ��ϴ�." << endl << endl;
		return nullptr;
	}
}

void AccountManager::logout(Account* pAccount)
{
	cout << "�����ϰ� �α׾ƿ� �Ǿ����ϴ�." << endl << endl;
	pAccount->setIsUse(false);
}

void AccountManager::registerAccount()
{
	string id, password;

	while (true) {
		cout << "* ���̵�: "; cin >> id;
		if (search(id)) cout << "������ ���̵� �����մϴ�. �ٽ� �Է����ּ���." << endl << endl;
		else break;
	}
	cout << "* ��й�ȣ: "; cin >> password;
	vec->push_back(new User(id, password));
	cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl << endl;
}

void AccountManager::addItem()
{
	string id, password;

	cout << "* �߰��� ������ ���̵�: "; cin >> id;
	if (search(id) != nullptr)
	{
		cout << "* ���� ��Ͽ� �̹� �Է��Ͻ� ������ ���̵� �����մϴ�!" << endl << endl;
		return;
	}
	cout << "* �߰��� ������ ��й�ȣ: "; cin >> password;
	cout << "* ���� " << id << "�� ��Ͽ� �߰��Ǿ����ϴ�." << endl << endl;

	(*vec).push_back(new User(id, password));
}

void AccountManager::eraseItem()
{
	string id;
	Account *pAccount;

	cout << "* ������ ������ ���̵�: "; cin >> id;
	
	for (int i = 0; i < (signed)vec->size(); i++)
	{
		if (!(*vec)[i]->getId().compare(id)) {
			if (!(*vec)[i]->getType().compare("Admin"))
			{
				cout << "* ������ ������ ������ ���� �����ϴ�." << endl << endl;
				return;
			}
			cout << "* ���� " << id << "�� �����Ǿ����ϴ�." << endl << endl;
			delete (*vec)[i];
			(*vec).erase((*vec).begin() + i);
			return;
		}
	}
	cout << "* �Է��Ͻ� ���̵� ���� ������ ã�� �� �������ϴ�." << endl << endl;
}

void AccountManager::showList()
{
	cout << "================================================" << endl;
	cout << setw(10) << "���̵�" << setw(15) << "��й�ȣ" << setw(10) << "�α���" << setw(13) << "���� �ð�" << endl;
	cout << "================================================" << endl;
	for (vector<Account*>::size_type i = 0; i < vec->size(); i++)
	{
		cout << setw(10) << (*vec)[i]->getId() << setw(15) << (*vec)[i]->getPassword() << setw(10) << ((*vec)[i]->getIsUse() ? "�α���" : "�α׾ƿ�");
		if ((*vec)[i]->getType().compare("Admin"))
		{
			string time = to_string((*vec)[i]->getHour()) + "�ð� " + to_string((*vec)[i]->getMinute()) + "��";
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

	cout << "* ������ ������ ���̵�: "; cin >> id;

	Account* pAccount = search(id);
	if (pAccount != nullptr && !pAccount->getType().compare("User") && (pUser = static_cast<User*>(pAccount)))
	{
		cout << "* ������ ������ ��й�ȣ: "; cin >> password;
		cout << "* " << id << "�� ��й�ȣ�� ���������� ����Ǿ����ϴ�." << endl << endl;
		pUser->setPassword(password);
	}
	else cout << "* �Է��Ͻ� ���̵� ���� ������ ã�� �� �������ϴ�." << endl << endl;
}