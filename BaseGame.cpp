#include "StartGame.h"
#include "BaseGame.h"

BaseGame::BaseGame(int width, int height, int fpsLimit, int option) : window(nullptr)
{
	switch (option) {
	case EIGHTBALL: //8Ball 
	{
		PlayBGM("게임음악.wav");
		window = new sf::RenderWindow(sf::VideoMode(width, height), "EightBall", sf::Style::Default);
		window->setFramerateLimit(fpsLimit);
	}
	break;
	default:
	{
		//PlayBGM("????");
		window = new sf::RenderWindow(sf::VideoMode(width, height), "???????", sf::Style::Default);
		window->setFramerateLimit(fpsLimit);
	}
	break;
	}
}

BaseGame::~BaseGame(void)
{
	//음악중지
	Gamesound.stop(); 
	// 게임 윈도우 해제 
	delete window;
}

void BaseGame::run(void)
{
	if (window == nullptr)
	{
		// 게임 윈도우가 생성되어 있어야 함 
		return;
	}

	// 메인 게임 루프 
	while (window->isOpen())
	{
		sf::Event ev;
		if (window->pollEvent(ev))
		{
			// 입력 이벤트 처리 (자식 클래스 구현) 
			handle(ev);
		}

		// 게임 업데이트 (자식 클래스 구현) 
		update();

		// 렌더링 (자식 클래스 구현) 
		render(*window);

		// 렌더링 결과 표시
		window->display();
	}
}

void BaseGame::PlayBGM(const char* BGM) {
	//배경음악 로드
	if (!Gamebuffer.loadFromFile(BGM))
		std::cout << "음악을 재생할 수 없습니다." << std::endl;
	Gamesound.setBuffer(Gamebuffer);
	Gamesound.play();
	Gamesound.setLoop(true);
}