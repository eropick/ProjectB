#include "SampleBilliardBoard.h"

SampleBilliardBoard::SampleBilliardBoard(void)
{
	// Sample Game�� ���� �籸�� �ؽ�ó �̹��� �ε� 
	texture.loadFromFile("textureBoard.png", sf::IntRect(1, 1, 454, 848));

	// ��������Ʈ ���� 
	sprite.setTexture(texture);
	sprite.setPosition(572.5f, 25.f);

	// �籸�� ��� �ʱ�ȭ - �����¿� 
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

// �Ҹ��� 
SampleBilliardBoard::~SampleBilliardBoard(void)
{
	borderLines.clear();
}

// Sample Game�� ��ü���� �ݵ�� ���� ���� �Լ� �����ؾ� �� 
void SampleBilliardBoard::update(float timeElapsed)
{
	// Sample Game�� �籸��� ���� ���� X 
}

// Sample Game�� ��ü���� �ݵ�� �浹 ���� �����ؾ� ��
void SampleBilliardBoard::collide(SampleBilliardObject& other)
{
	// Sample Game�� �籸��� ���� ������Ʈ�̱� ������ �浹 X 
}

// Sample Game�� ��ü���� �ݵ�� ������ �Լ� �����ؾ� ��  
void SampleBilliardBoard::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

// �籸�븦 �����ϴ� ��� ��� ��ȯ 
const std::vector<SampleBilliardBoard::Border>& SampleBilliardBoard::getBorders(void) const
{
	return borderLines;
}
