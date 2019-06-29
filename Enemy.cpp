#include "Enemy.hpp"
#include <random>
#include <ctime>


Enemy::Enemy(std::string name, char tile, int attack, int health, int bulletGive, int atkDistance)
	:m_name(name),
	m_tile(tile),
	m_attack(attack),
	m_health(health),
	m_bulletGive(bulletGive),
	m_atkDistance(atkDistance)
{
}


Enemy::~Enemy()
{
}

void Enemy::setPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Enemy::getPosition(int &x, int &y)
{
	x = m_posX;
	y = m_posY;
}

int Enemy::attack()
{
	static std::default_random_engine randomEngine(time(nullptr));
	std::uniform_int_distribution<int> attackRoll(0, m_attack);

	return attackRoll(randomEngine);
}

int Enemy::takeDamage(int attack)
{
	static std::default_random_engine randomEngine(time(nullptr));
	m_health -= attack;

	if (m_health <= 0) {
		std::uniform_int_distribution<int> bulletRoll(0, m_bulletGive);
		return bulletRoll(randomEngine);
	}

	return 0;
}

char Enemy::getMove(int playerX, int playerY) {
	static std::default_random_engine randomEngine(time(nullptr));
	std::uniform_int_distribution<int> moveRoll(0, 6);

	int distance;
	int dx = m_posX - playerX;
	int dy = m_posY - playerY;
	int adx = abs(dx);
	int ady = abs(dy);

	distance = adx + ady;

	if (distance <= m_atkDistance) {
		//Move along X axis
		if (adx > ady) {
			if (dx > 0) {
				return 'a';
			}
			else {
				return 'd';
			}
		}
		else { //Move along Y axis
			if (dy > 0) {
				return 'w';
			}
			else {
				return 's';
			}
		}
	}

	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return '.';
	}

}