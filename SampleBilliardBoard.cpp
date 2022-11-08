#include "SampleBilliardBoard.h"

SampleBilliardBoard::SampleBilliardBoard(void)
{
	// Sample Game을 위한 당구대 텍스처 이미지 로드 
	texture.loadFromFile("textureBoard.png", sf::IntRect(1, 1, 454, 848));

	// 스프라이트 설정 
	sprite.setTexture(texture);
	sprite.setPosition(572.5f, 25.f);

	// 당구대 경계 초기화 - 상하좌우 
	SampleBilliardBoard::Border lineTop(632.5f, 55.f, 968.5f, 55.f);
	SampleBilliardBoard::Border lineLeft1(602.5f, 85.f, 602.5f, 400.5f);
	SampleBilliardBoard::Border lineLeft2(602.5f, 445.5f, 602.5f, 800.5f);

	SampleBilliardBoard::Border lineBottom(632.5f, 830.5f, 968.5f, 830.5f);
	SampleBilliardBoard::Border lineRight1(998.5f, 85.5f, 998.5f, 400.5f);
	SampleBilliardBoard::Border lineRight2(998.5f, 445.5f, 998.5f, 800.5f);

	borderLines.push_back(lineTop);
	borderLines.push_back(lineBottom);
	borderLines.push_back(lineLeft1);
	borderLines.push_back(lineRight1);
	borderLines.push_back(lineLeft2);
	borderLines.push_back(lineRight2);
}

// 소멸자 
SampleBilliardBoard::~SampleBilliardBoard(void)
{
	borderLines.clear();
}

// Sample Game의 객체들은 반드시 상태 갱신 함수 구현해야 함 
void SampleBilliardBoard::update(float timeElapsed)
{
	// Sample Game의 당구대는 상태 갱신 X 
}

// Sample Game의 객체들은 반드시 충돌 물리 구현해야 함
void SampleBilliardBoard::collide(SampleBilliardObject& other)
{
	// Sample Game의 당구대는 고정 오브젝트이기 때문에 충돌 X 
}

// Sample Game의 객체들은 반드시 렌더링 함수 구현해야 함  
void SampleBilliardBoard::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

// 당구대를 구성하는 경계 요소 반환 
const std::vector<SampleBilliardBoard::Border>& SampleBilliardBoard::getBorders(void) const
{
	return borderLines;
}
