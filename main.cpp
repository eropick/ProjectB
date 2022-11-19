#include "BaseGame.h"
#include "SampleGame.h"
#include "StartGame.h"

int main(void)
{
	//초기 게임 화면 생성
	StartGame Game(1028, 960, 60);
	Game.Info();
	return 0;
}
