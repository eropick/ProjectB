#pragma once

#include <cmath>
#include "SampleBilliardBall.h"
#include <vector>

using std::vector;

class BilliardPocket : public SampleBilliardBall
{
public:
	using SampleBilliardBall::SampleBilliardBall;
	// 렌더링 함수 재정의  
	virtual void render(sf::RenderTarget& target);
	// 충돌 재정의
	virtual void collide(SampleBilliardObject& other);
	virtual ~BilliardPocket();
	void putBall(SampleBilliardObject& Ball); //공 넣기
	SampleBilliardObject* outBall(int i) const; //공 가져오기

	//포켓 테스트코드(미구현)
	void printBall(sf::RenderTarget& target);
private:
	void collideWithBall(SampleBilliardBall& other);
	void collideWithBoard(SampleBilliardBoard& other);
	static vector<SampleBilliardObject*> Pocket; //정적 포켓
};