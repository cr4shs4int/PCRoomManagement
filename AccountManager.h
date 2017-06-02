#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "Account.h"
#include <vector>

using std::vector;

class AccountManager {
private:
	vector<Account*>* vec;
public:
	AccountManager(vector<Account*>*);
	~AccountManager();

	void fileRead();
	void fileWrite();
	Account* search(string);
	Account* login();
	void logout(Account*);
	void registerAccount();
};
#endif