#include "BaseGame.h"

BaseGame::BaseGame(int width, int height, int fpsLimit) : window(nullptr)
{
	// ���� ������ �ʱ�ȭ 
	window = new sf::RenderWindow(sf::VideoMode(width, height), "EightBall", sf::Style::Default);
	window->setFramerateLimit(fpsLimit);
}

BaseGame::~BaseGame(void)
{
	// ���� ������ ���� 
	delete window;
}

void BaseGame::run(void)
{
	if (window == nullptr)
	{
		// ���� �����찡 �����Ǿ� �־�� �� 
		return;
	}

	// ���� ���� ���� 
	while (window->isOpen())
	{
		sf::Event ev;
		if (window->pollEvent(ev))
		{
			// �Է� �̺�Ʈ ó�� (�ڽ� Ŭ���� ����) 
			handle(ev);
		}

		// ���� ������Ʈ (�ڽ� Ŭ���� ����) 
		update();

		// ������ (�ڽ� Ŭ���� ����) 
		render(*window);

		// ������ ��� ǥ��
		window->display();
	}
}