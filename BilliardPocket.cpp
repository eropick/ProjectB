#include "BilliardPocket.h"
#include "SampleGame.h"

//��������
vector<SampleBilliardObject*> BilliardPocket::Pocket;

//�Ҹ���.
BilliardPocket::~BilliardPocket() {
	for (SampleBilliardObject* obj : Pocket)
	{
		delete obj;
	}
}

//������Ʈ �浹 ������
void BilliardPocket::collide(SampleBilliardObject& other)
{
	// ���� �浹�� ��� 
	if (dynamic_cast<SampleBilliardBall*>(&other) != nullptr)
	{
		SampleBilliardBall& ball = *dynamic_cast<SampleBilliardBall*>(&other);
		collideWithBall(ball);
	}

	//�籸�� �浹�� ��� ��.
}

//���ϰ� �� �浹
void BilliardPocket::collideWithBall(SampleBilliardBall& other)
{

	// ������ �� �񱳽� ���� 
	if (this == &other)
	{
		return;
	}
	// �Ÿ� ��� 
	sf::Vector2f distance = getPosition() - other.getPosition();
	float distanceBetween = (sqrtf((distance.x * distance.x) + (distance.y * distance.y)));

	// �� ���� ��ġ���� �˻� 
	if (distanceBetween < getRadius()/1.5)  
	{
		if (typeid(other) == typeid(SampleBilliardGameBall)) { //�Ŀ��� ���
			other.setPosition(700, 700);
			other.setVelocity(0, 0);
			setVelocity(0, 0); //���� �ӵ� 0
		}
		else {
			putBall(other); //���Ͽ� ���ֱ�
			SampleBilliardBall* Ball = dynamic_cast<SampleBilliardBall*>(&other);
			//������ �ٷ� �־����� �ʰ� Ư�� ���� �Ѿ�� ���Ͽ� �ִ� ������ ����
			int size = Pocket.size();
			other.setPosition(300, 800 - (2 * size * Ball->getRadius())); //�浹�� ���� ��ġ ����
			other.setVelocity(0, 0);
			setVelocity(0, 0); //���� �ӵ�0
		}
	}
}

//������ ������
void BilliardPocket::render(sf::RenderTarget& target) {
	//printBall(target); ���� �׽�Ʈ�ڵ�
	target.draw(getVertices());
}

//���Ͽ� ���� �� ���
void BilliardPocket::printBall(sf::RenderTarget& target) {
	for (int i = 0; i < Pocket.size(); ++i) {
		//BilliardGameBall�� ����ĳ����
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

//���Ͽ� ���ֱ�
void BilliardPocket::putBall(SampleBilliardObject& Ball) {
	Pocket.push_back(&Ball);
}

//���Ͽ��� �� ������
SampleBilliardObject& BilliardPocket::outBall(int index){
	SampleBilliardObject* Ball = Pocket[index];
	//���� ���ۿ��� �� �������� �ش� ���� ���� ������Ʈ�� ����
	Pocket.erase(remove(Pocket.begin(), Pocket.end(), Pocket[index]), Pocket.end());
	return *Ball;
}

//���Ͼȿ� �ش� ���� �ִ��� �˻�
int BilliardPocket::InPocket(SampleBilliardObject& other){ 
	int index = -1;
	SampleBilliardGameBall* oB = dynamic_cast<SampleBilliardGameBall*>(&other);
	for (int i = 0; i < Pocket.size(); ++i) {
		SampleBilliardGameBall* pB = dynamic_cast<SampleBilliardGameBall*>(Pocket[i]);
		if (pB == oB) { //���Ͼȿ� �ִٸ�
			index = i;
			break;
		}
	}
	return index;
}