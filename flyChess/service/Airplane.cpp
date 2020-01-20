#include "Airplane.h"
Airplane::Airplane(int _startPos)
{
	StartPos = _startPos;
	pos = 0;
}
void Airplane::go(int delta)
{
	if(pos+delta>endpos)
	{
		pos = endpos - (pos+delta-endpos);
	}
	pos+=delta;
}
bool Airplane::isEnd()
{
	if(pos == endpos)
	{
		return true;
	}
	return false;
}
void goHome()
{
	pos = 0;
