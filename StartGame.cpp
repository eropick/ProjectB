#include "StartGame.h"

StartGame::StartGame(int width, int height, int fpsLimit) 
	: Width(width), Height(height), FpsLimit(fpsLimit), option(0)
{	
	//������ �ʱⰪ ����
	window = new sf::RenderWindow(sf::VideoMode(500, 500), "Billiard Game", sf::Style::Default);
	window->setFramerateLimit(fpsLimit);
	
	system("cls");
	std::cout << "[Load mainframe]" << std::endl;

	texture.loadFromFile("logo.png", sf::IntRect(0, 0, 500, 500));
	ButtonT1.loadFromFile("ButtonT1.png", sf::IntRect(0, 0, 225, 25));
	ButtonT2.loadFromFile("ButtonT2.png", sf::IntRect(0, 0, 225, 25));
	ButtonT3.loadFromFile("ButtonT3.png", sf::IntRect(0, 0, 225, 25));
	ButtonT4.loadFromFile("ButtonT4.png", sf::IntRect(0, 0, 225, 25));

	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	Tnum = T1;
}

StartGame::~StartGame(void)
{
	delete window;
	//â �ݰ� ���� �ҷ���
	switch (option) {
	case EIGHTBALL:
	{
		BaseGame&& game = SampleGame(Width, Height, FpsLimit);
		game.run();
		std::cout << "Exit" << std::endl;
	}	
	break;
	default:
		break;
	}
}

void StartGame::handle(sf::Event& ev)
{
	switch (ev.type) {
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::MouseButtonPressed:
		if (ev.mouseButton.button == sf::Mouse::Left) {
			//���⿡�� ���� ����
			option = EIGHTBALL;
			window->close();
		}
	}
}

void StartGame::Info(void)
{
	if (window == nullptr)
	{
		//������ ��������
		return;
	}

	// ���� ���� ���� 
	while (window->isOpen())
	{
		sf::Event ev;
		while (window->pollEvent(ev))
		{
			// �Է� �̺�Ʈ ó�� (�ڽ� Ŭ���� ����) 
			handle(ev);
		}

		// ������ (�ڽ� Ŭ���� ����) 
		render(*window);

		// ������ ��� ǥ��
		window->display();
	}
}

void StartGame::render(sf::RenderTarget& target)
{	
	float xPosition = 130;
	float yPosition = 450;
	time = clock.getElapsedTime().asSeconds();
	interval += time;
	if (interval > 0.1) 
	{
		switch (Tnum) {
		case T1:
		{
			Bsprite.setTexture(ButtonT2);
			Bsprite.setPosition(xPosition, yPosition);
			Tnum = T2;
		}
		break;
		case T2:
		{
			Bsprite.setTexture(ButtonT3);
			Bsprite.setPosition(xPosition, yPosition);
			Tnum = T3;
		}
		break;
		case T3:
		{
			Bsprite.setTexture(ButtonT4);
			Bsprite.setPosition(xPosition, yPosition);
			Tnum = T4;
		}
		break;
		case T4:
		{
			Bsprite.setTexture(ButtonT1);
			Bsprite.setPosition(xPosition, yPosition);
			Tnum = T1;
		}
		break;
		}
		interval = 0;
	}
	target.draw(sprite);
	target.draw(Bsprite);
	clock.restart(); //�����
}
