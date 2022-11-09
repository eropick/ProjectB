#include "SampleGame.h"
#include "SampleBilliardBoard.h"
#include "SampleBilliardGameBall.h"
#include "BilliardPocket.h"
#include "SampleBilliardObject.h"

SampleGame::SampleGame(int width, int height, int fpsLimit)
	:BaseGame(width, height, fpsLimit), isDraggingBall(false), draggedBall(nullptr)
{
	// SampleGame을 위한 인터페이스 생성 및 등록 

	// SampleGame을 위한 당구대 생성 및 등록 
	gameObjects.push_back(new SampleBilliardBoard());

	// SampleGame을 위한 당구공 생성 및 등록 
	
	BilliardPocket* Pocket[6];
	//포켓 x,y 좌표 한 번에 변경 가능하도록 해놨습니다.
	float x[2] = { 593,1014 };
	float y[3] = { 45,450,848 };
	sf::Vector2f PocketCord[6] = {
	{x[0], y[0]},{x[0], y[1]},{x[0], y[2]},
	{x[1], y[0]},{x[1], y[1]},{x[1], y[2]},
	};
	for (int i = 0; i < 6; ++i) {
		Pocket[i] = new BilliardPocket(PocketCord[i], 12, sf::Color::Black);
		gameObjects.push_back(Pocket[i]);
	}
	//플레이어볼
	SampleBilliardGameBall* PlayerBall= 
		new SampleBilliardGameBall(sf::Vector2f(800, 500), 10, sf::Color::White);
	PlayerBall->setOwner("P");
	PlayerBall->setPlayable(true);
	gameObjects.push_back(PlayerBall);

	//게임볼
	SampleBilliardGameBall* ball[15];
	typedef sf::Color C;

	//색 매핑
	//1~7번 공은 단색공 = 총 7개
    //9번~15번 공은 줄무늬 공 = 총 7개
    //노랑, 남색, 빨강, 보라(핑크), 주황, 초록, 갈색  = 총 7개
	C color[15] = {
    C::Yellow, C::Color(0,0,128), C::Red,
    C::Color(77,55,123), C::Color(255,165,0), C::Green,
    C::Color(111, 79, 48),C::Black,C::Yellow,
    C::Color(0,0,128), C::Red,C::Color(77,55,123),
    C::Color(255,165,0), C::Green,  C::Color(111, 79, 48),
	};
	//공 좌표 매핑
	//1번은 맨 앞에, 8번은 가운데
    //2번과 3번은 양쪽 끝에
    //1번 다음 배열은 띠공-띠공
    //중간배열은 색꽁-띠공 번갈아가면서
	sf::Vector2f Cord[15] =
	{ {800, 300},{840, 260},{760, 260},
	{780, 280},{810, 270},{770, 270},
	{800, 260},{800, 280},{830, 270},
	{790, 290},{780, 260},{790, 270},
	{820, 260},{810, 290},{820, 280} };

	//배열 초기화
	for (int i = 0; i < 15; ++i) {
		ball[i] = new SampleBilliardGameBall(Cord[i], 10, color[i]);
		char Intstr[10];
		_itoa(i+1, Intstr, 10); //정수를 문자열로
		std::string str = Intstr;
		ball[i]->setPlayable(false);
		ball[i]->setOwner(str);
		gameObjects.push_back(ball[i]);
	}
}


SampleGame::~SampleGame(void)
{
	// UI 인스턴스 해제  
	// 게임 오브젝트들 해제 
	for (SampleBilliardObject* obj : gameObjects)
	{
		delete obj;
	}
}

sf::Font* SampleGame::font = nullptr;
const sf::Font& SampleGame::getFont(void)
{
	if (font == nullptr) {
		font = new sf::Font;
		font->loadFromFile("Arial.ttf");
	}
	return *font;
}

// 상속 클래스는 반드시 이벤트 핸들링 함수 구현해야 함 
void SampleGame::handle(sf::Event& ev)
{
	// SampleGame을 위한 입력 이벤트 처리 
	switch (ev.type)
	{
	case sf::Event::Closed:
		// 윈도우의 x 버튼 누르면 종료한다 
		window->close();
		break;
	case sf::Event::KeyPressed:
		// 키보드 이벤트 
		if (ev.key.code == sf::Keyboard::Escape)
		{
			// TODO: game paused 
			// TODO: call sample GUI 
		}
		break;
	case sf::Event::MouseMoved:
		// 마우스 움직임 이벤트 
		mouseXY.x = (float)ev.mouseMove.x;
		mouseXY.y = (float)ev.mouseMove.y;
		break;
	case sf::Event::MouseButtonPressed:
		// 마우스 버튼 누름 이벤트 
		if (ev.mouseButton.button == sf::Mouse::Left)
		{
			for (SampleBilliardObject* obj : gameObjects)
			{
				// SampleBilliardBall의 인스턴스가 아닌 경우 pass
				SampleBilliardGameBall* gameBall = dynamic_cast<SampleBilliardGameBall*>(obj);
				if (gameBall == nullptr)
				{
					continue;
				}

				// 커서가 공의 내부가 아닌 경우 pass 
				if (!gameBall->isIntersecting(mouseXY))
				{
					continue;
				}

				// 공이 Playable이 아닌 경우 pass 
				if (!gameBall->isPlayable()) {
					continue;
				}

				// 드래그 가능한 공 임시 저장 
				draggedBall = gameBall;
				isDraggingBall = true;
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		// 마우스 버튼 뗌 이벤트 
		if (ev.mouseButton.button == sf::Mouse::Left && isDraggingBall)
		{
			isDraggingBall = false;
		}
		break;
	}
}

// 상속 클래스는 반드시 게임 상태 갱신 함수 구현해야 함 
void SampleGame::update(void)
{
	// 게임 오브젝트 업데이트 
	for (SampleBilliardObject* obj : gameObjects)
	{
		obj->update(clock.getElapsedTime().asSeconds());
	}

	// 게임 오브젝트 충돌 검사
	for (SampleBilliardObject* obj1 : gameObjects)
	{
		for (SampleBilliardObject* obj2 : gameObjects)
		{
			obj1->collide(*obj2);
		}
	}

	// 끌었다가 놓은 공에 속도를 지정하고 표시 해제 
	if (!isDraggingBall && draggedBall != nullptr)
	{
		draggedBall->setVelocity(draggedBall->getPosition().x - mouseXY.x, draggedBall->getPosition().y - mouseXY.y);
		draggedBall = nullptr;
	}

	// 다음 단위 시간을 위해 초기화 
	clock.restart();
}

// 상속 클래스는 반드시 객체 렌더링 함수 구현해야 함 
void SampleGame::render(sf::RenderTarget& target)
{
	// 화면 클리어 
	window->clear(sf::Color(75, 103, 163));

	// 게임 오브젝트 렌더링 
	for (SampleBilliardObject* obj : gameObjects)
	{
		obj->render(target);
	}

	//게임 스코어
	renderScore(target);

	// 공을 드래그 하면 세기 표시 (길이 및 색)
	renderDragpower(target);
	
	// 게임 UI 렌더링
	
}

void SampleGame::renderDragpower(sf::RenderTarget& target)
{
	if (isDraggingBall)
	{
		sf::Vector2f distance = (mouseXY - draggedBall->getPosition());
		float distanceBetween = sqrt(distance.x * distance.x + distance.y * distance.y);
		sf::Vector2f invert = distance / distanceBetween; //단위벡터?
		sf::Color directionColor = sf::Color(255, (255 - ((int)distanceBetween / 2) % 255), 0);
		if (distanceBetween > 510)
		{
			directionColor = sf::Color::Red;
		}

		sf::Vector2f toSubtract(distanceBetween * invert.x, distanceBetween * invert.y); //반대방향
		sf::Vertex start = sf::Vertex(draggedBall->getPosition(), directionColor);
		sf::Vertex end = sf::Vertex(draggedBall->getPosition() - toSubtract, directionColor);

		sf::VertexArray points;
		points.setPrimitiveType(sf::LineStrip);
		points.append(start);
		points.append(end);
		target.draw(points);
	}
}

void SampleGame::renderScore(sf::RenderTarget& target) {
	// 점수판
	sf::Text P1_score;
	sf::Text P2_score;
	sf::Text ScoreText;
	
	//폰트 설정
	P1_score.setFont(getFont());
	P2_score.setFont(getFont());
	ScoreText.setFont(getFont());

	//색
	P1_score.setFillColor(sf::Color::White);
	P2_score.setFillColor(sf::Color::White);
	ScoreText.setFillColor(sf::Color::Cyan);

	//크기
	P1_score.setCharacterSize(80);
	P2_score.setCharacterSize(80);
	ScoreText.setCharacterSize(50);

	P1_score.setString("0");
	P2_score.setString("0");
	
	P1_score.setOutlineColor(sf::Color::Cyan);
	P2_score.setOutlineColor(sf::Color::Cyan);

	P1_score.setOutlineThickness(1.f);
	P2_score.setOutlineThickness(1.f);

	ScoreText.setString("player1 | player2");
	ScoreText.setOutlineColor(sf::Color::White);
	ScoreText.setOutlineThickness(1.f);

	P1_score.setPosition(120.f, 250.f);
	P2_score.setPosition(300.f, 250.f);
	ScoreText.setPosition(70.f, 200.f);

	target.draw(P1_score);
	target.draw(P2_score);
	target.draw(ScoreText);
}