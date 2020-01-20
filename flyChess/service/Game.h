_Pragma("once")
#include "Player.h"
#define Player_num 4
class Game
{
private:
	Player* mPlayer[Player_num];
	
	int _roll;
	bool overFlag;
public:
	Game();
	void start();
	bool addPlayer(Player *iPlayer);
	
	//观察者模式接收
	void WinManager(Player *iPlayer);
	void Roll();
	
	//观察者模式发送
	void sendRoll();
	void GameOver();
	~Game();
}