#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "Manager.h"
#include "Account.h"
#include <vector>

using std::vector;

class AccountManager : public Manager {
private:
	vector<Account*>* vec;
public:
	AccountManager(vector<Account*>*);
	~AccountManager();

	void addItem();
	void modifyItem();
	void eraseItem();
	void showList();
	void fileRead();
	void fileWrite();
	Account* search(string);
	Account* login();
	void logout(Account*);
	void registerAccount();
};
#endif