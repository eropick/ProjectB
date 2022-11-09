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

	// �籸��� �浹�� ��� 
	if (dynamic_cast<SampleBilliardBoard*>(&other) != nullptr)
	{
		SampleBilliardBoard& board = *dynamic_cast<SampleBilliardBoard*>(&other);
		collideWithBoard(board);
	}
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
		putBall(other); //���Ͽ� ���ֱ�
		SampleBilliardGameBall* Ball = dynamic_cast<SampleBilliardGameBall*>(&other);
		//������ �ٷ� �־����� �ʰ� Ư�� ���� �Ѿ�� ���Ͽ� �ִ� ������ ����
		int size = Pocket.size();
		other.setPosition(300,800-(2*size*Ball->getRadius())); //�浹�� ���� ��ġ ����
		other.setVelocity(0, 0); 
		setVelocity(0, 0); //���� �ӵ�0
	}
}

//�籸�� �浹 ������
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