#include "BilliardPocket.h"
#include "SampleGame.h"

//정적변수
vector<SampleBilliardObject*> BilliardPocket::Pocket;

//소멸자.
BilliardPocket::~BilliardPocket() {
	for (SampleBilliardObject* obj : Pocket)
	{
		delete obj;
	}
}

//오브젝트 충돌 재정의
void BilliardPocket::collide(SampleBilliardObject& other)
{
	// 공과 충돌할 경우 
	if (dynamic_cast<SampleBilliardBall*>(&other) != nullptr)
	{
		SampleBilliardBall& ball = *dynamic_cast<SampleBilliardBall*>(&other);
		collideWithBall(ball);
	}

	// 당구대와 충돌할 경우 
	if (dynamic_cast<SampleBilliardBoard*>(&other) != nullptr)
	{
		SampleBilliardBoard& board = *dynamic_cast<SampleBilliardBoard*>(&other);
		collideWithBoard(board);
	}
}

//포켓과 공 충돌
void BilliardPocket::collideWithBall(SampleBilliardBall& other)
{
	// 동일한 공 비교시 종료 
	if (this == &other)
	{
		return;
	}
	// 거리 계산 
	sf::Vector2f distance = getPosition() - other.getPosition();
	float distanceBetween = (sqrtf((distance.x * distance.x) + (distance.y * distance.y)));

	// 두 공이 겹치는지 검사 
	if (distanceBetween < (getRadius() + other.getRadius()))
	{
		putBall(other); //포켓에 공넣기
		other.setPosition(10, 10); //충돌한 공의 위치 지정
		other.setVelocity(0, 0); 
		setVelocity(0, 0); //포켓 속도0
	}
}

//당구대 충돌 재정의
void BilliardPocket::collideWithBoard(SampleBilliardBoard& other)
{
	for (SampleBilliardBoard::Border border : other.getBorders())
	{
		sf::Vector2f p = getPosition();
		sf::Vector2f s(border.getPoints()[0].position);
		sf::Vector2f e = border.getPoints()[1].position;
		sf::Vector2f ps = p - s;
		sf::Vector2f se = e - s;

		float lineLength = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);
		float t = ((ps.x * se.x) + (ps.y * se.y)) / lineLength;
		sf::Vector2f st(s.x + t * se.x, s.y + t * se.y);

		sf::Vector2f distance = p - st;
		float distanceBetween = sqrtf((distance.x * distance.x) + (distance.y * distance.y));

		sf::Vector2f normal = distance / distanceBetween;
		float dotProductNormal = getVelocity().x * normal.x + getVelocity().y * normal.y;

		sf::Vector2f tangential = sf::Vector2f(-normal.y, normal.x);
		float dotProductTangential = getVelocity().x * tangential.x + getVelocity().y * tangential.y;

		float overlap = distanceBetween - getRadius();
		if (distanceBetween <= getRadius())
		{
			if (t > -0.f && t < 1.f)
			{
				setPosition(p.x - distance.x * overlap / distanceBetween, p.y - distance.y * overlap / distanceBetween);
				setVelocity(-normal.x * dotProductNormal + tangential.x * dotProductTangential,
					-normal.y * dotProductNormal + tangential.y * dotProductTangential);
			}
		}
	}
}

//렌더링 재정의
void BilliardPocket::render(sf::RenderTarget& target) {
	printBall(target);
	target.draw(getVertices());
}

//포켓에 넣은 공 출력
void BilliardPocket::printBall(sf::RenderTarget& target) {
	for (int i = 0; i < Pocket.size(); ++i) {
		//BilliardGameBall로 동적캐스팅
		SampleBilliardGameBall& ball = *dynamic_cast<SampleBilliardGameBall*>(Pocket[i]);
		sf::Text BallName;
		BallName.setFont(SampleGame::getFont());
		BallName.setFillColor(sf::Color::Black);
		BallName.setString(ball.getOwner());
		BallName.setCharacterSize(20);
		BallName.setPosition(450,i*50+300);
		target.draw(BallName);
	}
}

//포켓에 공넣기
void BilliardPocket::putBall(SampleBilliardObject& Ball) {
	Pocket.push_back(&Ball);
}

//포켓에서 공빼오기
SampleBilliardObject* BilliardPocket::outBall(int i) const {
	return Pocket[i];
}