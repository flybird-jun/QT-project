#include"Game.h"
Game::Game()
{
	for(int i=0;i<Player_num;i++)
	{
		mPlayer[i] = nullptr;
	}
	overFlag = false;
	_roll = 0;
}
void Game::start()
{
	for(int i=0;i<Player_num;i++)
	{
		if(!mPlayer[i])
		{
			break;//throw
		}
	}
	while(!overFlag)
	{
		for(int i=0;i<Player_num;i++)
		{
			mPlayer[i].turn_on();
		}
	}
	
}
bool Game::addPlayer(Player *iPlayer)
{
	for(int i = 0;i<Player_num;i++)
	{
		if(!mPlayer[i])
		{
			mPlayer[i] = iPlayer;
			iPlayer->setManager(this);
		}
	}
	if(i==Player_num)
	{
		return false;
	}
	return true;
}
void Game::WinManager(Player *iPlayer)
{
	static int index = 1;
	if(index > 4)
	{
		index = 1;
	}
	for(int i = 0;i<Player_num;i++)
	{
		
	}
}
Game::~Game()
{
	for(int i = 0;i<Player_num;i++)
	{
		if(mPlayer[i]!=nullptr)
		{
			delete mPlayer[i];
			mPlayer[i] = nullptr;
		}
	}
}