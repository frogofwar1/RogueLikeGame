#pragma once
#include <string>

class Enemy
{
public:
	Enemy(std::string name,char tile, int attack, int health, int bulletGive, int atkDistance);
	~Enemy();

	void setPosition(int x, int y);
	void getPosition(int &x, int &y);

	std::string getName() { return m_name; }
	char getTile() { return m_tile; }

	int attack();
	int takeDamage(int attack);

	//Enemies AI
	char getMove(int playerX, int playerY);

private:
	std::string m_name;
	char m_tile;
	int m_attack;
	int m_health;
	int m_bulletGive;
	int m_atkDistance;

	int m_posX;
	int m_posY;
};

