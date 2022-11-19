#pragma once
#include <iostream> 
#include <vector> 
#include <string>
#include <cstdlib>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "SampleGame.h"
#include "BaseGame.h"
#include "SampleBilliardGameBall.h"

#define EIGHTBALL 1

enum {
	T1=1,T2,T3,T4
};

class StartGame{
public:
	StartGame(int width, int height, int fpsLimit);

	~StartGame(void);

	void handle(sf::Event& ev);

	void render(sf::RenderTarget& target);

	void Info(void);

private:
	int option;
	int Width;
	int Height;
	int FpsLimit;

	//�ؽ��� �ð� ����
	sf::Clock clock;
	float time;
	float interval;

	// ���� UI 
	// ���� ȭ��
	sf::Texture			texture;
	sf::Sprite			sprite;

	//��ư �ؽ���
	sf::Texture			Btexture;
	sf::Sprite			Bsprite;

	// ���� UI��
	sf::Texture	ButtonT1;
	sf::Texture	ButtonT2;
	sf::Texture	ButtonT3;
	sf::Texture	ButtonT4;

	// ���� ���� �ؽ��� ��ȣ
	int Tnum;

	// ���� ������ Ÿ��
	sf::RenderWindow* window;
};