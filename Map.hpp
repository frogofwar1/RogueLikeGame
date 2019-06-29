#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.hpp"
#include "Item.h"

class Enemy;

class Map
{
public:
	Map();
	~Map();

	void load(std::string fileName, std::shared_ptr<Player> player);
	void print();
	void movePlayer(char input, std::shared_ptr<Player> player);
	void updateEnemies(std::shared_ptr<Player> player);

	char getTile(int x, int y);
	void setTile(int x, int y, char tile);

private:
	std::vector<std::string> m_mapData;
	std::shared_ptr<std::vector<Enemy>> m_enemies;
	std::shared_ptr<std::vector<Item>> m_Items;

	void processPlayerMove(std::shared_ptr<Player> player, int targetX, int targetY);
	void processEnemyMove(std::shared_ptr<Player> player, int enemyIndex, int targetX, int targetY);
	void battleEnemy(std::shared_ptr<Player> player, int targetX, int targetY);
	void randomRescueItem(std::shared_ptr<Player> player);
};

