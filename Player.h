#pragma once
#include<iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "SampleBilliardObject.h"
#include "SampleBilliardBoard.h"

class Player : public SampleBilliardObject{
public:
	Player();
	Player(int num,bool turn);
	virtual ~Player(void);

	// Sample Game�� ��ü���� �ݵ�� ���� ���� �Լ� �����ؾ� �� 
	virtual void update(float timeElapsed);

	// Sample Game�� ��ü���� �ݵ�� �浹 ���� �����ؾ� ��
	virtual void collide(SampleBilliardObject& other);

	// Sample Game�� ��ü���� �ݵ�� ������ �Լ� �����ؾ� ��  
	virtual void render(sf::RenderTarget& target);

	void setTurn(bool turn); //�� ����
	bool isTurn() const; //���� ������
	void setScore(int param);
	void setScore(std::string param);
	std::string getScore() const;
	void yourWin(bool win); //�¸�
	bool isWin() const; //���а� �����Ǿ�����
	void setBallType(int type); //�� Ÿ��
	int getBallType() const;
	void setPocketSize(int size);
	int getPocketSize() const;
private:
	bool turn;
	bool win; //�⺻ false
	int score;
	int ballType; //0: ����  | 1: Solids  | 9:  Stripes 
	int PocketSize; //������ ��� ���� ������(���� ũ���� ��ȭ�� �Ǵ��� �� ����� ��.
	int PlayerNum; //�÷��̾� �ѹ�
};