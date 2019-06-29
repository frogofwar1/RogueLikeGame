#include "pch.h"
#include "Map.hpp"
#include "utility.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <random>
#include <ctime>


Map::Map()
	:m_enemies(std::make_shared<std::vector<Enemy>>())
	,m_Items(std::make_shared<std::vector<Item>>())
{
}

Map::~Map()
{
}

void Map::load(std::string fileName, std::shared_ptr<Player> player) {
	
	std::ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	std::string line;
	
	while (std::getline(file, line)) {
		m_mapData.push_back(line);
	}

	file.close();

	char tile;
	for (unsigned int i = 0; i < m_mapData.size(); i++) {
		for (unsigned int j = 0; j < m_mapData[i].size(); j++) {
			tile = m_mapData[i][j];

			switch (tile)
			{
			case 'P':
				player->setPosition(j, i);
				break;
			case 'S':
				m_enemies->push_back(Enemy("Small Alien", tile, 3, 12, 2, 10));
				m_enemies->back().setPosition(j, i);
				break;
			case 'B':
				m_enemies->push_back(Enemy("Big Alien", tile, 8, 30, 5, 5));
				m_enemies->back().setPosition(j, i);
				break;
			case 'Q':
				m_enemies->push_back(Enemy("Alien Queen", tile, 50, 500, 1000, 5));
				m_enemies->back().setPosition(j, i);
				break;
			case 'r':
				m_Items->push_back(Item("Rescue Equip"));
				m_Items->back().setPosition(j, i);
				break;
			case 'e':
				m_Items->push_back(Item("StarShip Energy"));
				m_Items->back().setPosition(j, i);
				break;
			}
		}
	}
}

void Map::print() {

	system("cls");

	//std::cout << std::string(100, '\n');

	for (unsigned int i = 0; i < m_mapData.size(); i++) {
		printf("%s\n", m_mapData[i].c_str());
	}
	printf("\n");
}

void Map::movePlayer(char input, std::shared_ptr<Player> player) {

	int playerX;
	int playerY;

	player->getPosition(playerX, playerY);


	switch (input)
	{
	case 'w':
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
		break;
	case 's':
	case 'S':
		processPlayerMove(player, playerX, playerY + 1);
		break;
	case 'a':
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
	case 'd':
	case 'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("INVALID INPUT!\n");
		system("PAUSE");
		break;
	}
}

void Map::updateEnemies(std::shared_ptr<Player> player)
{
	char aiMove;
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	player->getPosition(playerX, playerY);

	for (int i = 0; i < m_enemies->size(); i++) {
		aiMove = m_enemies->at(i).getMove(playerX, playerY);
		m_enemies->at(i).getPosition(enemyX, enemyY);

		switch (aiMove)
		{
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
		case 's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
		case 'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}
	}
}


char Map::getTile(int x, int y) 
{
	return m_mapData[y][x];
}

void Map::setTile(int x, int y, char tile) 
{
	m_mapData[y][x] = tile;
}

void Map::processPlayerMove(std::shared_ptr<Player> player, int targetX, int targetY)
{
	int playerX;
	int playerY;

	player->getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		player->setPosition(targetX, targetY);
		setTile(playerX, playerY, '.');
		setTile(targetX, targetY, 'P');
		break;
	case '#':
		break;
	case 'r':
		randomRescueItem(player);
		setTile(targetX, targetY, '.');
		system("PAUSE");
		break;
	case 'e':
		player->getShipEnergy();
		setTile(targetX, targetY, '.');
		system("PAUSE");
		break;
	default:
		battleEnemy(player, targetX, targetY);
		break;
	}
}

void Map::processEnemyMove(std::shared_ptr<Player> player, int enemyIndex, int targetX, int targetY) {
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	m_enemies->at(enemyIndex).getPosition(enemyX, enemyY);
	player->getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '.':
		m_enemies->at(enemyIndex).setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '.');
		setTile(targetX, targetY, m_enemies->at(enemyIndex).getTile());
		break;
	case 'P':
		battleEnemy(player, enemyX, enemyY);
		break;
	default:
		break;
	}
}

void Map::battleEnemy(std::shared_ptr<Player> player, int targetX, int targetY)
{
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackDamage;
	int attackResult;
	std::string enemyName;

	player->getPosition(playerX, playerY);

	for (unsigned int i = 0; i < m_enemies->size(); i++)
	{
		m_enemies->at(i).getPosition(enemyX, enemyY);
		enemyName = m_enemies->at(i).getName();

		if (targetX == enemyX && targetY == enemyY) {

			//Battle!
			attackDamage = player->attack();
			printf("Player attacked %s with %d damage\n", enemyName.c_str(), attackDamage);
			attackResult = m_enemies->at(i).takeDamage(attackDamage);

			if (attackResult != 0) {
				setTile(targetX, targetY, '.');
				print();
				printf("%s died!\n", enemyName.c_str());

				//remove the enemy
				m_enemies->at(i) = m_enemies->back();
				m_enemies->pop_back();
				i--;

				player->getBullet(attackResult);
				//add some item
				system("PAUSE");

				return;
			}
			//Monster turn!
			attackDamage = m_enemies->at(i).attack();
			printf("%s attacked Player with %d damage\n", enemyName.c_str(), attackDamage);
			attackResult = player->takeDamage(attackDamage);

			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				print();
				printf("You died!\n");
				system("PAUSE");

				exit(0);
				return;
			}
			system("PAUSE");
			return;
		}
	}
}

void Map::randomRescueItem(std::shared_ptr<Player> player) {
	static std::default_random_engine randomEngine(time(nullptr));
	std::uniform_int_distribution<int> itemRoll(0, 1);
	if (itemRoll(randomEngine) == 0){
		player->heal();
	}
	else{
		player->getBullet(10);
	}
}