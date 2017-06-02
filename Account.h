#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

class Account {
private:
	int money, remainingTime;
	string id, password;
	bool isUse;
public:
	Account(string id, string password, int money, int remainingTime) : id(id), password(password), money(money), remainingTime(remainingTime) { this->isUse = false; }

	int getHour() { return remainingTime / 60; }
	int getMinute() { return remainingTime % 60; }

	// setter
	void setId(string id) { this->id = id; }
	void setPassword(string password) { this->password = password; }
	void setMoney(int money) { this->money = money; }
	void setRemainingTime(int remainingTime) { this->remainingTime = remainingTime; }
	void setIsUse(bool isUse) { this->isUse = isUse; }

	// getter
	string getId() { return id; }
	string getPassword() { return password; }
	int getMoney() { return money; }
	int getRemainingTime() { return remainingTime; }
	bool getIsUse() { return isUse; }

	virtual string getType() const = 0;
};

class User : public Account {
public:
	User(string id, string password, int money = 0, int remainingTime = 0) : Account(id, password, money, remainingTime) { }

	void order() {

	}

	string getType() const { return "User"; }
};

class Admin : public Account {
public:
	Admin(string id, string password, int money = 0, int remainingTime = 0) : Account(id, password, money, remainingTime) { }

	string getType() const { return "Admin"; }
};

#endif