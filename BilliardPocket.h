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
	static SampleBilliardObject& outBall(int index); //공 가져오기
	//포켓안에 해당 공이 있는지 검사 후 인덱스 반환(없으면 -1)
	static int InPocket(SampleBilliardObject& Ball); 
	//포켓 테스트코드
	void printBall(sf::RenderTarget& target);

private:
	void collideWithBall(SampleBilliardBall& other);
	static vector<SampleBilliardObject*> Pocket; //정적 포켓
};