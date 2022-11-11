#include "SampleGame.h"
#include "SampleBilliardBoard.h"
#include "SampleBilliardGameBall.h"
#include "BilliardPocket.h"
#include "SampleBilliardObject.h"


SampleGame::SampleGame(int width, int height, int fpsLimit)
	:BaseGame(width, height, fpsLimit), isDraggingBall(false), draggedBall(nullptr)
{

	// SampleGame을 위한 인터페이스 생성 및 등록 

	// SampleGame을 위한 당구대 생성 및 등록 
	gameObjects.push_back(new SampleBilliardBoard()); //0번

	// SampleGame을 위한 당구공 생성 및 등록 

	//포켓 1~6번
	BilliardPocket* Pocket[6];
	//포켓 x,y 좌표 한 번에 변경 가능하도록 해놨습니다.
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

	//플레이어볼 7번
	SampleBilliardGameBall* PlayerBall =
		new SampleBilliardGameBall(sf::Vector2f(800, 500), 10, sf::Color::White);
	PlayerBall->setOwner("P");
	PlayerBall->setPlayable(true);
	gameObjects.push_back(PlayerBall);

	//게임볼 8~22번까지 
	SampleBilliardBall* ball[15];
	typedef sf::Color C;

	//색 매핑
	//1~7번 공은 단색공 = 총 7개
    //9번~15번 공은 줄무늬 공 = 총 7개
    //노랑, 남색, 빨강, 보라(핑크), 주황, 초록, 갈색  = 총 7개
	C color[15] = {
    C::Yellow, C::Color(0,0,128), C::Red,
    C::Color(77,55,123), C::Color(255,165,0), C::Green,
    C::Color(111, 79, 48),C::Black,C::Yellow,
    C::Color(0,0,128), C::Red,C::Color(77,55,123),
    C::Color(255,165,0), C::Green,  C::Color(111, 79, 48),
	};
	//공 좌표 매핑
	//1번은 맨 앞에, 8번은 가운데
    //2번과 3번은 양쪽 끝에
    //1번 다음 배열은 띠공-띠공
    //중간배열은 색꽁-띠공 번갈아가면서
	sf::Vector2f Cord[15] =
	{ {800, 300},{840, 260},{760, 260},
	{780, 280},{810, 270},{770, 270},
	{800, 260},{800, 280},{830, 270},
	{790, 290},{780, 260},{790, 270},
	{820, 260},{810, 290},{820, 280} };

	//배열 초기화
	for (int i = 0; i < 15; ++i) {
		ball[i] = new SampleBilliardBall(Cord[i], 10, color[i]);
		ball[i]->setOwner(std::to_string(i+1)); 
		gameObjects.push_back(ball[i]);
	}

	//플레이어 정보
	int PlayerCnt = 2; //플레이어 수
	srand(time(NULL));
	//첫번째 턴 난수
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
	// UI 인스턴스 해제  
	// 게임 오브젝트들 해제 
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

// 상속 클래스는 반드시 이벤트 핸들링 함수 구현해야 함 
void SampleGame::handle(sf::Event& ev)
{
	// SampleGame을 위한 입력 이벤트 처리 
	switch (ev.type)
	{
	case sf::Event::Closed:
		// 윈도우의 x 버튼 누르면 종료한다 
		window->close();
		break;
	case sf::Event::KeyPressed:
		// 키보드 이벤트 
		if (ev.key.code == sf::Keyboard::Escape)
		{
			// TODO: game paused 
			// TODO: call sample GUI 
		}
		break;
	case sf::Event::MouseMoved:
		// 마우스 움직임 이벤트 
		mouseXY.x = (float)ev.mouseMove.x;
		mouseXY.y = (float)ev.mouseMove.y;
		break;
	case sf::Event::MouseButtonPressed:
		// 마우스 버튼 누름 이벤트 
		if (ev.mouseButton.button == sf::Mouse::Left)
		{
			for (SampleBilliardObject* obj : gameObjects)
			{
				//공이 움직이고 있는 상태라면 버튼 누름 이벤트발생X
				if (Players[0]->isPhase() == 1 || Players[1]->isPhase() == 1)
					continue;

				// SampleBilliardBall의 인스턴스가 아닌 경우 pass
				SampleBilliardGameBall* gameBall = dynamic_cast<SampleBilliardGameBall*>(obj);
				if (gameBall == nullptr)
				{
					continue;
				}

				// 커서가 공의 내부가 아닌 경우 pass 
				if (!gameBall->isIntersecting(mouseXY))
				{
					continue;
				}

				// 공이 Playable이 아닌 경우 pass 
				if (!gameBall->isPlayable()) {
					continue;
				}

				// 드래그 가능한 공 임시 저장 
				draggedBall = gameBall;
				isDraggingBall = true;
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		// 마우스 버튼 뗌 이벤트 
		if (ev.mouseButton.button == sf::Mouse::Left && isDraggingBall)
		{
			isDraggingBall = false;
		}
		break;
	}
}

// 상속 클래스는 반드시 게임 상태 갱신 함수 구현해야 함 
void SampleGame::update(void)
{
	// 플레이어 서로의 주소 추가
	if (&(Players[0]->getNextP()) == nullptr) Players[0]->setNextP(*Players[1]);
	if (&(Players[1]->getNextP()) == nullptr) Players[1]->setNextP(*Players[0]);
	
	//필요한 공
	SampleBilliardGameBall* playerBall = nullptr;
	SampleBilliardObject* eightBall = nullptr;

	// 게임 오브젝트 업데이트 
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
	if (playerBall == nullptr) exit(-1);  //오브젝트 업데이트 후에 nullptr을 갖는다면 종료

	//플레이어 업데이트
	for (Player* p : Players)
	{
		if (p->isWin() == true) break;
		//플레이어 볼의 상태에 따른 작업
		if (p->isTurn()) { //플레이어 턴일 때
			switch (p->isPhase()) {
			case 0: //공을 아직 안침
			{
				if (playerBall->getVelocity() == sf::Vector2f(0, 0)) {}
				else //공의 속도가 변했을 때
					p->setPhase(1); //공 친 상태로 변경
			}
			break;
			case 1: //공을 침
			{
				int check = 0;
				for (SampleBilliardObject* obj : gameObjects) {
					//포켓이 아닌 목적공들의 속도가 모두 0인지 구한다.
					if (dynamic_cast<SampleBilliardBall*>(obj) != nullptr
						&& dynamic_cast<BilliardPocket*>(obj) == nullptr) {
						SampleBilliardBall& Ball = *dynamic_cast<SampleBilliardBall*>(obj);
						if (Ball.getVelocity() != sf::Vector2f(0.f, 0.f))
							check = 1;
					}
					if (check == 1) break; //하나라도 속도가 0이 아니라면
				}
				if (check == 0) //속도가 0이라면
					p->setPhase(-1); //친 후의 상태로 변경
			}
			break;
			case -1: //공을 치고 정지
			{
				//포켓 크기의 변화가 있다면
				if (BilliardPocket::getSizePocket() != Player::getSizePocket()) {
					//이번 턴에 들어간 공의 수를 구함.
					int DiffSize = BilliardPocket::getSizePocket() - Player::getSizePocket();
					
					if (BilliardPocket::InPocket(*eightBall) >= 0) { //8번공이 들어간 경우
						if (BilliardPocket::InPocket(*playerBall) >= 0){ //플레이어 볼이 들어간 경우
							p->yourLose(true); //무조건 패배
						}
						else {
							if (p->getBallType() <= 0) { //BallType이 미정이라면 패배
								p->yourLose(true);
							}
							else if(BilliardPocket::InPocket(*eightBall)==
								BilliardPocket::getSizePocket()-1)//8번공이 마지막 요소일 때 
							{
								//플레이어의 모든 목적볼을 넣은 경우
								if (p->getBallType() == 1&& BilliardPocket::getCntSolids()==7)
									p->yourWin(true); //승리
								else if (p->getBallType() == 9 && BilliardPocket::getCntStripes()==7)
									p->yourWin(true); //승리
								else //목적공을 못넣은 경우
									p->yourLose(true);
							}
							else //8번공이 마지막 요소가 아닌 경우 패배
								p->yourLose(true);
						}
					}
					else if (BilliardPocket::InPocket(*playerBall) >= 0) { //8번공 제외 플레이어 볼이 들어간 경우
						p->setPhase(0);
						p->setTurn(false); //턴종료
						p->getNextP().setTurn(true); //다음 플레이어 턴 
						playerBall->setPosition(800, 500); //플레이어볼의 포지션 정하기
						BilliardPocket::outBall(BilliardPocket::InPocket(*playerBall)); //흰공을 포켓에서 꺼냄
						p->setScore(stoi(p->getScore()) + (DiffSize - 1)); //흰공 뺀 숫자만큼 득점.
						Player::setSizePocket(BilliardPocket::getSizePocket()); //포켓 크기 갱신

						if (p->getBallType() == -1) { //브레이크 샷 인경우 
							p->setBallType(0); //미정 상태로 변경
							p->getNextP().setBallType(0); 	
						}
						else if (p->getBallType() == 0&&DiffSize>=2) { //미정 상태인 경우,플레이어볼 포함 2개이상
							//공이 몇 개이고 어떤 종류가 들어갔는지 확인
							int str = 0;
							int sol = 0;
							for (int i = BilliardPocket::getSizePocket() - 1; i >= DiffSize - 2; --i) {
								if (stoi(BilliardPocket::BallRef(i).getOwner()) > 8)
									str++;
								else
									sol++;
							}
							if (str == sol) {} //두 숫자가 같은 경우
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
					else { //8과 플레이어 볼을 제외한 목적구가 들어갔다면
						if (p->getBallType() == -1) { //브레이크 샷 인경우 
							p->setBallType(0); //미정 상태로 변경
							p->getNextP().setBallType(0); 
						}
						else if (p->getBallType() == 0) { //미정 상태인 경우
							//공이 몇 개이고 어떤 종류가 들어갔는지 확인
							int str = 0;
							int sol = 0;
							for (int i = BilliardPocket::getSizePocket() - 1; i >= DiffSize - 1; --i) {
								if (stoi(BilliardPocket::BallRef(i).getOwner()) > 8)
									str++;
								else
									sol++;
							}
							if (str == sol){} //두 숫자가 같은 경우
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
						//턴유지
						p->setScore(stoi(p->getScore()) + DiffSize); //들어간 수만큼 득점
						Player::setSizePocket(BilliardPocket::getSizePocket()); //포켓 공의 개수 갱신
					}
				}
				else { //변화가 없다면
					if (p->getBallType() == -1) { //브레이크 샷 인경우 
						p->setBallType(0); //미정 상태로 변경
						p->getNextP().setBallType(0);
					}
					p->setPhase(0); //전 상태로 돌림
					p->setTurn(false); //턴 종료
					p->getNextP().setTurn(true); //다음 플레이어에게 턴넘김
				}
			}
			break;
			}
		}
	}

	// 게임 오브젝트 충돌 검사
	for (SampleBilliardObject* obj1 : gameObjects)
	{
		for (SampleBilliardObject* obj2 : gameObjects)
		{
			obj1->collide(*obj2);
		}
	}

	// 끌었다가 놓은 공에 속도를 지정하고 표시 해제 => 이미 끌어서 놓은 상태를 의미
	if (!isDraggingBall && draggedBall != nullptr)
	{
		draggedBall->setVelocity(draggedBall->getPosition().x - mouseXY.x, draggedBall->getPosition().y - mouseXY.y);
		draggedBall = nullptr;
	}

	// 다음 단위 시간을 위해 초기화 
	clock.restart();
}

// 상속 클래스는 반드시 객체 렌더링 함수 구현해야 함 
void SampleGame::render(sf::RenderTarget& target)
{
	// 화면 클리어 
	window->clear(sf::Color(75, 103, 163));

	// 플레이어 정보 렌더링
	for (Player* p : Players)
	{
		p->render(target);
	}

	// 게임 오브젝트 렌더링 
	for (SampleBilliardObject* obj : gameObjects)
	{
		obj->render(target);
	}

	// 공을 드래그 하면 세기 표시 (길이 및 색)
	renderDragpower(target);

	// 게임 UI 렌더링

}

void SampleGame::renderDragpower(sf::RenderTarget& target)
{
	if (isDraggingBall)
	{
		sf::Vector2f distance = (mouseXY - draggedBall->getPosition());
		float distanceBetween = sqrt(distance.x * distance.x + distance.y * distance.y);
		sf::Vector2f invert = distance / distanceBetween; //단위벡터?
		sf::Color directionColor = sf::Color(255, (255 - ((int)distanceBetween / 2) % 255), 0);
		if (distanceBetween > 510)
		{
			directionColor = sf::Color::Red;
		}

		sf::Vector2f toSubtract(distanceBetween * invert.x, distanceBetween * invert.y); //반대방향
		sf::Vertex start = sf::Vertex(draggedBall->getPosition(), directionColor);
		sf::Vertex end = sf::Vertex(draggedBall->getPosition() - toSubtract, directionColor);

		sf::VertexArray points;
		points.setPrimitiveType(sf::LineStrip);
		points.append(start);
		points.append(end);
		target.draw(points);
	}
}

