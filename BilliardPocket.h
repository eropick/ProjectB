#pragma once

#include <cmath>
#include "SampleBilliardBall.h"
#include <vector>

using std::vector;

class BilliardPocket : public SampleBilliardBall
{
public:
	using SampleBilliardBall::SampleBilliardBall;
	// ������ �Լ� ������  
	virtual void render(sf::RenderTarget& target);
	// �浹 ������
	virtual void collide(SampleBilliardObject& other);
	virtual ~BilliardPocket();
	void putBall(SampleBilliardObject& Ball); //�� �ֱ�
	SampleBilliardObject* outBall(int i) const; //�� ��������

	//���� �׽�Ʈ�ڵ�(�̱���)
	void printBall(sf::RenderTarget& target);
private:
	void collideWithBall(SampleBilliardBall& other);
	void collideWithBoard(SampleBilliardBoard& other);
	static vector<SampleBilliardObject*> Pocket; //���� ����
};