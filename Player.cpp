#include "SampleBilliardBall.h"
#include "SampleBilliardBoard.h"
#include "BilliardPocket.h"
#include "SampleGame.h"
#include "Player.h"

Player::Player() : Player(0,false){}

Player::Player(int num,bool turn) : turn(turn), score(0), win(false), ballType(0),PlayerNum(num), PocketSize(0) {}

Player::~Player(void) {
	//x
}

// Sample Game의 객체들은 반드시 상태 갱신 함수 구현해야 함 
void Player::update(float timeElapsed) {
	//미구현
}

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

	//폰트 설정
	P_score.setFont(SampleGame::getFont());
	ScoreText.setFont(SampleGame::getFont());
	TurnText.setFont(SampleGame::getFont());

	//색
	P_score.setFillColor(sf::Color::White);
	ScoreText.setFillColor(sf::Color::Cyan);
	TurnText.setFillColor(sf::Color::Cyan);

	//크기
	P_score.setCharacterSize(80);
	ScoreText.setCharacterSize(50);
	TurnText.setCharacterSize(40);

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

	P_score.setPosition(120.f+(PlayerNum-1)*180.f, 250.f);
	ScoreText.setPosition(70.f+(PlayerNum-1)*180.f, 200.f);
	if(turn==true)
		TurnText.setPosition(100.f + (PlayerNum - 1) * 180.f, 350.f);
	target.draw(P_score);
	target.draw(ScoreText);
	if (turn == true)
		target.draw(TurnText);
}

void Player::setTurn(bool turn) {
	this->turn = turn;
}
bool Player::isTurn() const {
	return turn;
}

std::string Player::getScore() const {
	return std::to_string(score);
}


void Player::setScore(int param) {
	score = score + param;
}

void Player::setScore(std::string param) {
	score = stoi(getScore()) + stoi(param);
}

void Player::yourWin(bool win) {
	this->win = win;
}
bool Player::isWin() const {
	return win;
}

void Player::setBallType(int type) {
	if (0<type && type< 8) {
		ballType = 1; //solids
	}
	else if (type > 8){
		ballType = 9; //stripes
	}
	else
		ballType = 0;
}
int Player::getBallType() const {
	return ballType;
}

void Player::setPocketSize(int size) {
	PocketSize = size;
}
int Player::getPocketSize() const {
	return PocketSize;
}