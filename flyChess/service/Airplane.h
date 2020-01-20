_Pragma("once")
class Airplane
{
private:
	int pos;
	int StartPos;
	const int endpos = 40;
public:
	Airplane(int _startPos);
	void go(int delta);
	bool isEnd();
	void goHome();
};