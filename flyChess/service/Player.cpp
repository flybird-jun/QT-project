#include"Player.h"
Player::Player(int startPos)
{
	for(int i = 0;i<Airplane_Num;i++)
	{
		fly[i] = new Airplane(startpos);
		if(!fly[i])
		{
			//throw
		}
	}
}
void Player::setGameManager(Game *iGame)
{
	manager = iGame;
}

void Player::turn_on()
{
	//send enable roll signal
}
bool Player::operatorAirplane(int i)
{
	if(!fly[i].go(roll))
	{
		return false;
	}
	return true;
}
void Player::operatorAirplane()
{
	waitRoll();
	//send roll
}
void Player::Win()
{
	manager.WinManager(this);
}
void Player::start_roll()
{
	manager.Roll();
}
Player::~Player()
{
	for(int i = 0;i<4;i++)
	{
		if(fly[i]!=nullptr)
		{
			delete fly[i];
		}
		fly[i] = nullptr;
	}
}