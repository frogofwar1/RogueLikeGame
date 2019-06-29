#pragma once

class Player
{
public:
	Player();
	~Player();

	void init(int health, int attack, int bullet);

	void setPosition(int x, int y);
	void getPosition(int &x, int &y);

	int getBulletStatus() { return m_bullet; }
	int getHealth() { return m_health; }
	int getshipEnergyStatus() { return m_shipEnergy; }

	void getBullet(int bullet);
	void heal();
	void getShipEnergy();

	int attack();
	int takeDamage(int attack);

private:

	int m_health;
	int m_attack;
	int m_bullet;
	int m_shipEnergy;

	int m_posX;
	int m_posY;
};

