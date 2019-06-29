#include "pch.h"

#include "CWGame.hpp"
#include <iostream>
#include <conio.h>

#include "Map.hpp"
#include "Player.h"

CWGame::CWGame(std::string mapFileName)
	:m_map(std::make_shared<Map>()),
	m_player(std::make_shared<Player>())
{

	m_player->init(100, 10, 20);

	m_map->load(mapFileName, m_player);
	m_map->print();

}

CWGame::~CWGame()
{

}

void CWGame::update()
{

	m_map->print();
	playerMove();
	m_map->updateEnemies(m_player);
	checkWinCondition();

}

void CWGame::playerMove() 
{
	int Health = m_player->getHealth();
	int Bullet = m_player->getBulletStatus();
	int shipEnergy = m_player->getshipEnergyStatus();

	char input;
	printf("Enter a move command (w/s/a/d)\n");
	printf("Health : %d\n", Health);
	printf("Bullet : %d\n", Bullet);
	printf("Starship Energy : %d\n", shipEnergy);

	input = _getch();

	m_map->movePlayer(input, m_player);
}

void CWGame::checkWinCondition()
{
	if (m_player->getshipEnergyStatus() >= 4) {
		printf("You win!\n");
		system("PAUSE");

		exit(0);
	}
}
