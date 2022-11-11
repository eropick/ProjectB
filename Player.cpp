#include "SampleBilliardBall.h"
#include "SampleBilliardBoard.h"
#include "BilliardPocket.h"
#include "SampleGame.h"
#include "Player.h"

Player::Player() : Player(0,false){}

Player::Player(int num,bool turn) : turn(turn), Phase(0)
,score(0), win(false), ballType(-1),PlayerNum(num) {
	NextP = nullptr;
}

Player::~Player(void) {
	NextP = nullptr;
	//NextP는 SampleGame에서 소멸됨
}

int Player::PocketSize = 0;

void Player::setSizePocket(int size) {
	PocketSize = size;
}
int Player::getSizePocket() {
	return PocketSize;
}

//업데이트 재정의
void Player::update(SampleBilliardGameBall& Ball){
	
}

// Sample Game의 객체들은 반드시 상태 갱신 함수 구현해야 함 
void Player::update(float timeElapsed) {} //timeElapsed사용 할 일이 없음

// Sample Game의 객체들은 반드시 충돌 물리 구현해야 함
void Player::collide(SampleBilliardObject& other) {
	//충돌 이벤트 x
}

// Sample Game의 객체들은 반드시 렌더링 함수 구현해야 함  
void Player::render(sf::RenderTarget& target) {
	// 점수판
	sf::Text P_score;
	sf::Text ScoreText;
	sf::Text TurnText;
	sf::Text WinText;
	sf::Text BallText;

	//폰트 설정
	P_score.setFont(SampleGame::getFont());
	ScoreText.setFont(SampleGame::getFont());
	TurnText.setFont(SampleGame::getFont());
	WinText.setFont(SampleGame::getFont());
	BallText.setFont(SampleGame::getFont());

	//색
	P_score.setFillColor(sf::Color::White);
	ScoreText.setFillColor(sf::Color::Cyan);
	TurnText.setFillColor(sf::Color::Cyan);
	WinText.setFillColor(sf::Color::Cyan);
	BallText.setFillColor(sf::Color::Cyan);

	//크기
	P_score.setCharacterSize(80);
	ScoreText.setCharacterSize(50);
	TurnText.setCharacterSize(40);
	WinText.setCharacterSize(40);
	BallText.setCharacterSize(40);

	//점수 가져옴
	P_score.setString(getScore());
	P_score.setOutlineColor(sf::Color::Cyan);
	P_score.setOutlineThickness(1.f);

	std::string str1 = "player";
	std::string str2 = std::to_string(PlayerNum);
	ScoreText.setString(str1+str2);
	ScoreText.setOutlineColor(sf::Color::White);
	ScoreText.setOutlineThickness(1.f);

	TurnText.setString("Turn");
	TurnText.setOutlineColor(sf::Color::Red);
	TurnText.setOutlineThickness(1.f);

	WinText.setString("Win");
	WinText.setOutlineColor(sf::Color::Yellow);
	WinText.setOutlineThickness(1.f);

	if(ballType<=0)
		BallText.setString("Unknown");
	else if(ballType==1)
		BallText.setString("Solids");
	else
		BallText.setString("Stripes");
	BallText.setOutlineColor(sf::Color::Yellow);
	BallText.setOutlineThickness(1.f);

	P_score.setPosition(120.f+(PlayerNum-1)*180.f, 250.f);
	ScoreText.setPosition(70.f+(PlayerNum-1)*180.f, 200.f);
	if(turn==true)
		TurnText.setPosition(100.f + (PlayerNum - 1) * 180.f, 350.f);
	if(win==true)
		WinText.setPosition(100.f + (PlayerNum - 1) * 180.f, 350.f);
	BallText.setPosition(50.f + (PlayerNum - 1) * 190.f, 150.f);

	target.draw(P_score);
	target.draw(ScoreText);
	if (turn == true) {
		if (win == true)
			target.draw(WinText);
		else
			target.draw(TurnText);
	}
	target.draw(BallText);
}

void Player::setTurn(bool turn) {
	this->turn = turn;
}
bool Player::isTurn() const {
	return turn;
}

void Player::setPhase(int Phase) {
	this->Phase = Phase;
}
int Player::isPhase() const {
	return Phase;
}


std::string Player::getScore() const {
	return std::to_string(score);
}


void Player::setScore(int param) {
	score = param;
}

void Player::setScore(std::string param) {
	score = stoi(getScore()) + stoi(param);
}

void Player::yourWin(bool win) {
	Phase = 0;
	turn = true;
	this->win = win;
}

void Player::yourLose(bool lose) {
	Phase = 0;
	turn = false;
	getNextP().yourWin(true); //해당 플레이어 패배 == 상대 플레이어 승리
}
bool Player::isWin() const {
	return win;
}

void Player::setBallType(int type) {
	if (0 < type && type < 8) {
		ballType = 1; //solids
	}
	else if (type > 8) {
		ballType = 9; //stripes
	}
	else if (type == 0)
		ballType = 0; //미정
	else
		ballType = - 1; //초기
}
int Player::getBallType() const {
	return ballType;
}


void Player::setNextP(Player& p) {
	NextP = &p;
}

Player& Player::getNextP()const{
	return *NextP;
}