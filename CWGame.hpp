#pragma once

#include <memory>
#include <string>
#include <vector>

class Map;
class Player;

class CWGame
{
public:
	CWGame(std::string mapFileName);
	~CWGame();
	//TODO: copy constructor and assignment operator

	void update();
	void playerMove();
	void checkWinCondition();

private:
	std::shared_ptr<Map> m_map;
	std::shared_ptr<Player> m_player;
	
};


