0. BilliardPocket의 static멤버 변수 초기화 패스로 
인한 메모리 참조 오류 수정

1. 시작 화면 게임 선택창 추가

2. 파워 클래스 추가
마우스 드래그로 방향 조절
마우스로 속도 조절 가능
스페이스바로 속도 조절 가능 

####
static 멤버가 있는 파일

1. Player.h
//턴을 지정할 때마다 플레이어를 이 변수로 넘김
static Player* TurnPlayer; 
//포켓 크기 변경점을 위한 변수, 승패 결정 시 초기화됨.
static int PocketSize;

2. BilliardPocket.h
//포켓 인스턴스에 닿을 경우 멤버 변수로 인스턴스가 들어감.
//외부에서 static멤버함수를 통해 초기화, 접근 가능.
static vector<SampleBilliardObject*> Pocket;

3. SampleGame.h
폰트

4. StartGame.h
//StartGame의 윈도우가 게임실행으로 인한 종료인지 => 게임 종료 후 다시 생성
//닫기 버튼으로 인한 종료인지 판단 => 프로그램 종료
static bool Close;
 