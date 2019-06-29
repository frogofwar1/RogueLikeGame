#pragma once
#include <string>

class Item
{
public:
	Item(std::string name);
	~Item();

	void setPosition(int x, int y);
	void getPosition(int &x, int &y);

private:
	std::string m_name;
	int m_posX;
	int m_posY;
};

