#include "Item.h"



Item::Item(std::string name) : m_name(name)
{
}


Item::~Item()
{
}


void Item::setPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Item::getPosition(int &x, int &y)
{
	x = m_posX;
	y = m_posY;
}