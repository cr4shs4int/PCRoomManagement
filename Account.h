#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

class Account {
private:
	int money, remainingTime;
	string id, password, name, phone;
	bool isUse;
public:
	Account(string id, string password, string name, string phone, int money, int remainingTime) : id(id), password(password), name(name), phone(phone), money(money), remainingTime(remainingTime) { this->isUse = false; }

	int getHour() { return remainingTime / 60; }
	int getMinute() { return remainingTime % 60; }

	// setter
	void setId(string id) { this->id = id; }
	void setPassword(string password) { this->password = password; }
	void setName(string name) { this->name = name; }
	void setPhone(string phone) { this->phone = phone; }
	void setMoney(int money) { this->money = money; }
	void setRemainingTime(int remainingTime) { this->remainingTime = remainingTime; }
	void setIsUse(bool isUse) { this->isUse = isUse; }

	// getter
	string getId() { return id; }
	string getPassword() { return password; }
	string getName() { return name; }
	string getPhone() { return phone; }
	int getMoney() { return money; }
	int getRemainingTime() { return remainingTime; }
	bool getIsUse() { return isUse; }

	virtual string getType() const = 0;
};

class Admin : public Account {
public:
	Admin(string id, string password, string name = "없음", string phone = "없음", int money = 0, int remainingTime = 0) : Account(id, password, name, phone, money, remainingTime) { }

	string getType() const { return "Admin"; }
};
#endif