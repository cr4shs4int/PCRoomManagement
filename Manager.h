#ifndef MANAGER_H
#define MANAGER_H

class Manager {
public:
	virtual void addItem() = 0;
	virtual void modifyItem() = 0;
	virtual void eraseItem() = 0;

	virtual void fileRead() = 0;
	virtual void fileWrite() = 0;
	virtual void showList() = 0;
};
#endif