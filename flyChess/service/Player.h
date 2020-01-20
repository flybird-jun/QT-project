_Pragma("once")
#include "Game.h"
#include "connect.h"
#define Airplane_Num 4
struct user_info
{
		unsigned id;
		string name;
};
class Player:public Connect
{
private:
	Airplane* fly[Airplane_Num];
	int roll;
	Game *manager;
	user_info info;
public:
	Player(int startPos);
	
	void setGameManager(Game *iGame);
	
	bool operatorAirplane(int i);
	void operatorAirplane();
	//观察者模式发送
	void start_roll();
	void Win();
	
	//发送给客户端消息
	void turn_on();
	
	//接收客户端消息
	~Player();
};