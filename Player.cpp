#include "pch.h"
#include "Player.h"
#include <iostream>
#include <random>
#include <ctime>

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(int health, int attack, int bullet)
{
	m_health = health;
	m_attack = attack;
	m_bullet = bullet;
	m_shipEnergy = 0; 
}

void Player::setPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Player::getPosition(int &x, int &y)
{
	x = m_posX;
	y = m_posY;
}

void Player::getBullet(int bullet) {
	printf("Get %d Bullets!\n", bullet);
	m_bullet += bullet;
}

void Player::heal() {
	printf("Get a medicine!\n");
	m_health += 50;
	if (m_health > 100) {
		m_health = 100;
	}
}

void Player::getShipEnergy() {
	printf("Get a ship energy!\n");
	m_shipEnergy++;
}

int Player::attack()
{
	if (m_bullet <= 0) {
		m_bullet = 0;
		return 0;
	}

	static std::default_random_engine randomEngine(time(nullptr));
	std::uniform_int_distribution<int> attackRoll(3, m_attack);
	m_bullet--;

	return attackRoll(randomEngine);
}

int Player::takeDamage(int attack)
{
	m_health -= attack;

	if (m_health <= 0) {
		return 1;
	}

	return 0;
}