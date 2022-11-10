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

	//당구대 충돌은 없어도 됨.
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
	if (distanceBetween < getRadius()/1.5)  
	{
		if (typeid(other) == typeid(SampleBilliardGameBall)) { //파울인 경우
			other.setPosition(700, 700);
			other.setVelocity(0, 0);
			setVelocity(0, 0); //포켓 속도 0
		}
		else {
			putBall(other); //포켓에 공넣기
			SampleBilliardBall* Ball = dynamic_cast<SampleBilliardBall*>(&other);
			//닿으면 바로 넣어지지 않고 특정 비율 넘어가면 포켓에 넣는 것으로 판정
			int size = Pocket.size();
			other.setPosition(300, 800 - (2 * size * Ball->getRadius())); //충돌한 공의 위치 지정
			other.setVelocity(0, 0);
			setVelocity(0, 0); //포켓 속도0
		}
	}
}

//렌더링 재정의
void BilliardPocket::render(sf::RenderTarget& target) {
	//printBall(target); 벡터 테스트코드
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

//포켓에서 공 빼오기
SampleBilliardObject& BilliardPocket::outBall(int index){
	SampleBilliardObject* Ball = Pocket[index];
	//포켓 시작에서 끝 범위에서 해당 값을 가진 오브젝트를 제거
	Pocket.erase(remove(Pocket.begin(), Pocket.end(), Pocket[index]), Pocket.end());
	return *Ball;
}

//포켓안에 해당 공이 있는지 검사
int BilliardPocket::InPocket(SampleBilliardObject& other){ 
	int index = -1;
	SampleBilliardGameBall* oB = dynamic_cast<SampleBilliardGameBall*>(&other);
	for (int i = 0; i < Pocket.size(); ++i) {
		SampleBilliardGameBall* pB = dynamic_cast<SampleBilliardGameBall*>(Pocket[i]);
		if (pB == oB) { //포켓안에 있다면
			index = i;
			break;
		}
	}
	return index;
}