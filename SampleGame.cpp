#include "SampleGame.h"
#include "SampleBilliardBoard.h"
#include "SampleBilliardGameBall.h"
#include "BilliardPocket.h"
#include "SampleBilliardObject.h"


SampleGame::SampleGame(int width, int height, int fpsLimit)
	:BaseGame(width, height, fpsLimit), isDraggingBall(false), draggedBall(nullptr)
{

	// SampleGame�� ���� �������̽� ���� �� ��� 

	// SampleGame�� ���� �籸�� ���� �� ��� 
	gameObjects.push_back(new SampleBilliardBoard()); //0��

	// SampleGame�� ���� �籸�� ���� �� ��� 

	//���� 1~6��
	BilliardPocket* Pocket[6];
	//���� x,y ��ǥ �� ���� ���� �����ϵ��� �س����ϴ�.
	float x[2] = { 593,1007 };
	float y[3] = { 45,450,850 };
	sf::Vector2f PocketCord[6] = {
	{x[0], y[0]},{x[0], y[1]},{x[0], y[2]},
	{x[1], y[0]},{x[1], y[1]},{x[1], y[2]},
	};
	for (int i = 0; i < 6; ++i) {
		Pocket[i] = new BilliardPocket(PocketCord[i], 12, sf::Color::Black);
		Pocket[i]->setOwner("0");
		gameObjects.push_back(Pocket[i]);
	}

	//�÷��̾ 7��
	SampleBilliardGameBall* PlayerBall =
		new SampleBilliardGameBall(sf::Vector2f(800, 500), 10, sf::Color::White);
	PlayerBall->setOwner("P");
	PlayerBall->setPlayable(true);
	gameObjects.push_back(PlayerBall);

	//���Ӻ� 8~22������ 
	SampleBilliardBall* ball[15];
	typedef sf::Color C;

	//�� ����
	//1~7�� ���� �ܻ��� = �� 7��
    //9��~15�� ���� �ٹ��� �� = �� 7��
    //���, ����, ����, ����(��ũ), ��Ȳ, �ʷ�, ����  = �� 7��
	C color[15] = {
    C::Yellow, C::Color(0,0,128), C::Red,
    C::Color(77,55,123), C::Color(255,165,0), C::Green,
    C::Color(111, 79, 48),C::Black,C::Yellow,
    C::Color(0,0,128), C::Red,C::Color(77,55,123),
    C::Color(255,165,0), C::Green,  C::Color(111, 79, 48),
	};
	//�� ��ǥ ����
	//1���� �� �տ�, 8���� ���
    //2���� 3���� ���� ����
    //1�� ���� �迭�� ���-���
    //�߰��迭�� ����-��� �����ư��鼭
	sf::Vector2f Cord[15] =
	{ {800, 300},{840, 260},{760, 260},
	{780, 280},{810, 270},{770, 270},
	{800, 260},{800, 280},{830, 270},
	{790, 290},{780, 260},{790, 270},
	{820, 260},{810, 290},{820, 280} };

	//�迭 �ʱ�ȭ
	for (int i = 0; i < 15; ++i) {
		ball[i] = new SampleBilliardBall(Cord[i], 10, color[i]);
		ball[i]->setOwner(std::to_string(i+1)); 
		gameObjects.push_back(ball[i]);
	}

	//�÷��̾� ����
	int PlayerCnt = 2; //�÷��̾� ��
	srand(time(NULL));
	//ù��° �� ����
	int FirstTurn = rand() % PlayerCnt; 
	for (int i = 0; i < 2; ++i) {
		Player* p;
		if(FirstTurn==i){
			p = new Player(i+1, true);
		}
		else{
			p = new Player(i+1, false);
		}
		Players.push_back(p);
	}
}


SampleGame::~SampleGame(void)
{
	// UI �ν��Ͻ� ����  
	// ���� ������Ʈ�� ���� 
	for (SampleBilliardObject* obj : gameObjects)
	{
		delete obj;
	}
	for (Player* p : Players) {
		delete p;
	}
}

sf::Font* SampleGame::font = nullptr;
const sf::Font& SampleGame::getFont(void)
{
	if (font == nullptr) {
		font = new sf::Font;
		font->loadFromFile("Arial.ttf");
	}
	return *font;
}

// ��� Ŭ������ �ݵ�� �̺�Ʈ �ڵ鸵 �Լ� �����ؾ� �� 
void SampleGame::handle(sf::Event& ev)
{
	// SampleGame�� ���� �Է� �̺�Ʈ ó�� 
	switch (ev.type)
	{
	case sf::Event::Closed:
		// �������� x ��ư ������ �����Ѵ� 
		window->close();
		break;
	case sf::Event::KeyPressed:
		// Ű���� �̺�Ʈ 
		if (ev.key.code == sf::Keyboard::Escape)
		{
			// TODO: game paused 
			// TODO: call sample GUI 
		}
		break;
	case sf::Event::MouseMoved:
		// ���콺 ������ �̺�Ʈ 
		mouseXY.x = (float)ev.mouseMove.x;
		mouseXY.y = (float)ev.mouseMove.y;
		break;
	case sf::Event::MouseButtonPressed:
		// ���콺 ��ư ���� �̺�Ʈ 
		if (ev.mouseButton.button == sf::Mouse::Left)
		{
			for (SampleBilliardObject* obj : gameObjects)
			{
				//���� �����̰� �ִ� ���¶�� ��ư ���� �̺�Ʈ�߻�X
				if (Players[0]->isPhase() == 1 || Players[1]->isPhase() == 1)
					continue;

				// SampleBilliardBall�� �ν��Ͻ��� �ƴ� ��� pass
				SampleBilliardGameBall* gameBall = dynamic_cast<SampleBilliardGameBall*>(obj);
				if (gameBall == nullptr)
				{
					continue;
				}

				// Ŀ���� ���� ���ΰ� �ƴ� ��� pass 
				if (!gameBall->isIntersecting(mouseXY))
				{
					continue;
				}

				// ���� Playable�� �ƴ� ��� pass 
				if (!gameBall->isPlayable()) {
					continue;
				}

				// �巡�� ������ �� �ӽ� ���� 
				draggedBall = gameBall;
				isDraggingBall = true;
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		// ���콺 ��ư �� �̺�Ʈ 
		if (ev.mouseButton.button == sf::Mouse::Left && isDraggingBall)
		{
			isDraggingBall = false;
		}
		break;
	}
}

// ��� Ŭ������ �ݵ�� ���� ���� ���� �Լ� �����ؾ� �� 
void SampleGame::update(void)
{
	// �÷��̾� ������ �ּ� �߰�
	if (&(Players[0]->getNextP()) == nullptr) Players[0]->setNextP(*Players[1]);
	if (&(Players[1]->getNextP()) == nullptr) Players[1]->setNextP(*Players[0]);
	
	//�ʿ��� ��
	SampleBilliardGameBall* playerBall = nullptr;
	SampleBilliardObject* eightBall = nullptr;

	// ���� ������Ʈ ������Ʈ 
	for (SampleBilliardObject* obj : gameObjects)
	{
		obj->update(clock.getElapsedTime().asSeconds());
		if (playerBall==nullptr)
			playerBall = dynamic_cast<SampleBilliardGameBall*>(obj);
		if (eightBall == nullptr) {
			SampleBilliardBall* eight = dynamic_cast<SampleBilliardBall*>(obj);
			if (eight!=nullptr&&eight->getOwner().compare("8") == 0)
				eightBall = obj;
		}
	}
	if (playerBall == nullptr) exit(-1);  //������Ʈ ������Ʈ �Ŀ� nullptr�� ���´ٸ� ����

	//�÷��̾� ������Ʈ
	for (Player* p : Players)
	{
		if (p->isWin() == true) break;
		//�÷��̾� ���� ���¿� ���� �۾�
		if (p->isTurn()) { //�÷��̾� ���� ��
			switch (p->isPhase()) {
			case 0: //���� ���� ��ħ
			{
				if (playerBall->getVelocity() == sf::Vector2f(0, 0)) {}
				else //���� �ӵ��� ������ ��
					p->setPhase(1); //�� ģ ���·� ����
			}
			break;
			case 1: //���� ħ
			{
				int check = 0;
				for (SampleBilliardObject* obj : gameObjects) {
					//������ �ƴ� ���������� �ӵ��� ��� 0���� ���Ѵ�.
					if (dynamic_cast<SampleBilliardBall*>(obj) != nullptr
						&& dynamic_cast<BilliardPocket*>(obj) == nullptr) {
						SampleBilliardBall& Ball = *dynamic_cast<SampleBilliardBall*>(obj);
						if (Ball.getVelocity() != sf::Vector2f(0.f, 0.f))
							check = 1;
					}
					if (check == 1) break; //�ϳ��� �ӵ��� 0�� �ƴ϶��
				}
				if (check == 0) //�ӵ��� 0�̶��
					p->setPhase(-1); //ģ ���� ���·� ����
			}
			break;
			case -1: //���� ġ�� ����
			{
				//���� ũ���� ��ȭ�� �ִٸ�
				if (BilliardPocket::getSizePocket() != Player::getSizePocket()) {
					//�̹� �Ͽ� �� ���� ���� ����.
					int DiffSize = BilliardPocket::getSizePocket() - Player::getSizePocket();
					
					if (BilliardPocket::InPocket(*eightBall) >= 0) { //8������ �� ���
						if (BilliardPocket::InPocket(*playerBall) >= 0){ //�÷��̾� ���� �� ���
							p->yourLose(true); //������ �й�
						}
						else {
							if (p->getBallType() <= 0) { //BallType�� �����̶�� �й�
								p->yourLose(true);
							}
							else if(BilliardPocket::InPocket(*eightBall)==
								BilliardPocket::getSizePocket()-1)//8������ ������ ����� �� 
							{
								//�÷��̾��� ��� �������� ���� ���
								if (p->getBallType() == 1&& BilliardPocket::getCntSolids()==7)
									p->yourWin(true); //�¸�
								else if (p->getBallType() == 9 && BilliardPocket::getCntStripes()==7)
									p->yourWin(true); //�¸�
								else //�������� ������ ���
									p->yourLose(true);
							}
							else //8������ ������ ��Ұ� �ƴ� ��� �й�
								p->yourLose(true);
						}
					}
					else if (BilliardPocket::InPocket(*playerBall) >= 0) { //8���� ���� �÷��̾� ���� �� ���
						p->setPhase(0);
						p->setTurn(false); //������
						p->getNextP().setTurn(true); //���� �÷��̾� �� 
						playerBall->setPosition(800, 500); //�÷��̾�� ������ ���ϱ�
						BilliardPocket::outBall(BilliardPocket::InPocket(*playerBall)); //����� ���Ͽ��� ����
						p->setScore(stoi(p->getScore()) + (DiffSize - 1)); //��� �� ���ڸ�ŭ ����.
						Player::setSizePocket(BilliardPocket::getSizePocket()); //���� ũ�� ����

						if (p->getBallType() == -1) { //�극��ũ �� �ΰ�� 
							p->setBallType(0); //���� ���·� ����
							p->getNextP().setBallType(0); 	
						}
						else if (p->getBallType() == 0&&DiffSize>=2) { //���� ������ ���,�÷��̾ ���� 2���̻�
							//���� �� ���̰� � ������ ������ Ȯ��
							int str = 0;
							int sol = 0;
							for (int i = BilliardPocket::getSizePocket() - 1; i >= DiffSize - 2; --i) {
								if (stoi(BilliardPocket::BallRef(i).getOwner()) > 8)
									str++;
								else
									sol++;
							}
							if (str == sol) {} //�� ���ڰ� ���� ���
							else {
								if (stoi(BilliardPocket::BallRef(BilliardPocket::getSizePocket() - 1).getOwner()) > 8) {
									p->setBallType(9); //stripes;
									p->getNextP().setBallType(1); //solids
								}
								else {
									p->setBallType(1); 
									p->getNextP().setBallType(9); 
								}
							}
						}
					}
					else { //8�� �÷��̾� ���� ������ �������� ���ٸ�
						if (p->getBallType() == -1) { //�극��ũ �� �ΰ�� 
							p->setBallType(0); //���� ���·� ����
							p->getNextP().setBallType(0); 
						}
						else if (p->getBallType() == 0) { //���� ������ ���
							//���� �� ���̰� � ������ ������ Ȯ��
							int str = 0;
							int sol = 0;
							for (int i = BilliardPocket::getSizePocket() - 1; i >= DiffSize - 1; --i) {
								if (stoi(BilliardPocket::BallRef(i).getOwner()) > 8)
									str++;
								else
									sol++;
							}
							if (str == sol){} //�� ���ڰ� ���� ���
							else {
								if (stoi(BilliardPocket::BallRef(BilliardPocket::getSizePocket() - 1).getOwner()) > 8) {
									p->setBallType(9); //stripes;
									p->getNextP().setBallType(1); //solids
								}
								else {
									p->setBallType(1);
									p->getNextP().setBallType(9);
								}
							}
						}
						p->setPhase(0);
						//������
						p->setScore(stoi(p->getScore()) + DiffSize); //�� ����ŭ ����
						Player::setSizePocket(BilliardPocket::getSizePocket()); //���� ���� ���� ����
					}
				}
				else { //��ȭ�� ���ٸ�
					if (p->getBallType() == -1) { //�극��ũ �� �ΰ�� 
						p->setBallType(0); //���� ���·� ����
						p->getNextP().setBallType(0);
					}
					p->setPhase(0); //�� ���·� ����
					p->setTurn(false); //�� ����
					p->getNextP().setTurn(true); //���� �÷��̾�� �ϳѱ�
				}
			}
			break;
			}
		}
	}

	// ���� ������Ʈ �浹 �˻�
	for (SampleBilliardObject* obj1 : gameObjects)
	{
		for (SampleBilliardObject* obj2 : gameObjects)
		{
			obj1->collide(*obj2);
		}
	}

	// �����ٰ� ���� ���� �ӵ��� �����ϰ� ǥ�� ���� => �̹� ��� ���� ���¸� �ǹ�
	if (!isDraggingBall && draggedBall != nullptr)
	{
		draggedBall->setVelocity(draggedBall->getPosition().x - mouseXY.x, draggedBall->getPosition().y - mouseXY.y);
		draggedBall = nullptr;
	}

	// ���� ���� �ð��� ���� �ʱ�ȭ 
	clock.restart();
}

// ��� Ŭ������ �ݵ�� ��ü ������ �Լ� �����ؾ� �� 
void SampleGame::render(sf::RenderTarget& target)
{
	// ȭ�� Ŭ���� 
	window->clear(sf::Color(75, 103, 163));

	// �÷��̾� ���� ������
	for (Player* p : Players)
	{
		p->render(target);
	}

	// ���� ������Ʈ ������ 
	for (SampleBilliardObject* obj : gameObjects)
	{
		obj->render(target);
	}

	// ���� �巡�� �ϸ� ���� ǥ�� (���� �� ��)
	renderDragpower(target);

	// ���� UI ������

}

void SampleGame::renderDragpower(sf::RenderTarget& target)
{
	if (isDraggingBall)
	{
		sf::Vector2f distance = (mouseXY - draggedBall->getPosition());
		float distanceBetween = sqrt(distance.x * distance.x + distance.y * distance.y);
		sf::Vector2f invert = distance / distanceBetween; //��������?
		sf::Color directionColor = sf::Color(255, (255 - ((int)distanceBetween / 2) % 255), 0);
		if (distanceBetween > 510)
		{
			directionColor = sf::Color::Red;
		}

		sf::Vector2f toSubtract(distanceBetween * invert.x, distanceBetween * invert.y); //�ݴ����
		sf::Vertex start = sf::Vertex(draggedBall->getPosition(), directionColor);
		sf::Vertex end = sf::Vertex(draggedBall->getPosition() - toSubtract, directionColor);

		sf::VertexArray points;
		points.setPrimitiveType(sf::LineStrip);
		points.append(start);
		points.append(end);
		target.draw(points);
	}
}

