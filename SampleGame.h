#pragma once
#define _CRT_SECURE_NO_WARNINGS //헤더에 이거 추가해야 아마 itoi쓸수 있을거에요
#include <iostream> 
#include <vector> 

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "BaseGame.h"
#include "SampleBilliardObject.h"
#include "SampleBilliardGameBall.h"

class SampleGame : public BaseGame
{
public:
	// Sample Game 초기화 
	SampleGame(int width, int height, int fpsLimit);

	// Sample Game 해제 
	virtual ~SampleGame(void);

	// Sample Game 전역 폰트 
	static const sf::Font& getFont(void);

protected:
	// 상속 클래스는 반드시 이벤트 핸들링 함수 구현해야 함 
	virtual void handle(sf::Event& ev);

	// 상속 클래스는 반드시 게임 상태 갱신 함수 구현해야 함 
	virtual void update(void);

	// 상속 클래스는 반드시 객체 렌더링 함수 구현해야 함 
	virtual void render(sf::RenderTarget& target);

private:
	// Sample Game 에서 공을 쏘는 강도 표시
	void renderDragpower(sf::RenderTarget& target);
	// Sample Game 에서의 점수판
	void renderScore(sf::RenderTarget& target);

private:
	// Sample Game에서 관리하는 게임 오브젝트들 (공, 당구대 등) 
	std::vector<SampleBilliardObject*> gameObjects;

	// 게임 UI 

	// 게임 시간 
	sf::Clock clock;

	// 마우스 위치
	sf::Vector2f mouseXY;

	// 공 발사용 
	bool isDraggingBall;
	SampleBilliardGameBall* draggedBall;

	// 게임 전역 폰트 
	static sf::Font* font;
};