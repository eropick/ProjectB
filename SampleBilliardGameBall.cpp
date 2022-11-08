#include "SampleBilliardGameBall.h"
#include "SampleGame.h"

bool SampleBilliardGameBall::isIntersecting(sf::Vector2f mouse)
{
	// mouse�� XY�� radius �ȿ� �������� �˻� 

	if ((std::powf(mouse.x - getPosition().x, 2.f) + std::powf(mouse.y - getPosition().y, 2.f))
		<= getRadius() * getRadius())
	{
		return true;
	}

	return false;
}

bool SampleBilliardGameBall::isPlayable(void)
{
	return playable;
}

void SampleBilliardGameBall::setPlayable(bool playable)
{
	this->playable = playable;
}

void SampleBilliardGameBall::setOwner(std::string owner)
{
	this->owner = owner;
}

bool SampleBilliardGameBall::isOwner(std::string owner)
{
	return owner.compare(this->owner) == 0;
}

std::string SampleBilliardGameBall::getOwner(void)
{
	return owner;
}

void SampleBilliardGameBall::render(sf::RenderTarget& target)
{
	// �� ���� �׸� 
	target.draw(getVertices());
	
	// 9��~15������ �ٹ��� �Է�
	sf::RectangleShape rectangle(sf::Vector2f(19, 9));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(getPosition() - sf::Vector2f(10, 4));
	if(owner!="P")
		if (stoi(owner) >= 9)
			target.draw(rectangle);
	// SampleGame������ �� ���� �÷��̾� ���� ǥ�� 
	sf::Text ballText;
	ballText.setFont(SampleGame::getFont());
	ballText.setFillColor(sf::Color::Black);
	ballText.setString(owner);
	ballText.setCharacterSize(13);
	// 10 �̻��� ���ڰ� �������Ƿ� ��ġ �ٽ� ����
	if (owner != "P") {
		if (stoi(owner)/10==1) //2�ڸ��� �̻�
			ballText.setPosition(getPosition() - sf::Vector2f(8, 10));
		else
			ballText.setPosition(getPosition() - sf::Vector2f(4, 9));
	}
	else
		ballText.setPosition(getPosition() - sf::Vector2f(4, 9));
   target.draw(ballText);
   if (owner == "8")
   {
      ballText.setFillColor(sf::Color::White);
      target.draw(ballText);
   }
}