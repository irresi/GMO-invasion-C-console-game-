# GMO-invasion-C-console-game-
only text

# 스토리
서기 3000년, 생명공학은 지금과는 달리 매우 발전했다. 한 생명공학자가 GMO 식품에 대해 연구하던 중 GMO 식품에 생명을 부여하는 방법을 찾아냈다. 한 박테리움과 식품이 만나면 이 박테리움이 식품 속으로 들어가서 식품에 침투해서 유전자 변이가 일어나는 것이다. 최근 몇 백년간 유전자 변이로 인해 식품이 동물처럼 움직일 수 있게 되었지만, 이제는 지능을 가진 식품이 생겨나기에 이르렀다. 이 과학자는 끊임없는 연구 끝에 사람보다 강한 식품을 만들었고 세계는 식품들에 의해 지배당하게 되었고 식품들에게 모든 연구 자료를 빼앗겼고 남은 것은 쇳덩이 밖에 없었다. 그래서 이 쇳덩이를 녹여서 갑옷과 칼을 만들고 자신이 만든 실수를 다시 바로 잡기 위해 모험을 떠난다. 

# 게임의 목표
캐릭터의 육성과 스토리에 따른 보스를 잡는 것이다. 40개의 스테이지를 모두 지나간다음 순간 이동과 속박, 돌진 스킬을 가진 보스(박테리움)를 잡으면 게임을 클리어한다.

# 장르
이 게임은 슈퍼 마리오 같은 2d 횡스크롤 방식과 캐릭터를 육성하는 rpg, 그리고 죽으면 세이브 파일이 삭제되는 로그라이크 장르를 결합했다. 
로그라이크류의 특징을 살려 텍스트만을 이용하여 만들었으며 랜덤 요소를 많이 넣었고 죽었을 때 능력치의 10%만 세이브를 할 수 있게 만들었다. 
그리고 계속 플레이를 하고 죽으며 영구 능력치와 돈을 얻을 수 있다. 

# 게임 방법
캐릭터는 WASD로 움직일 수 있고 공격과 선택은 SPACE BAR를 통해 할 수 있다.
캐릭터가 강해지는 방법?
-> 레벨 업, 환생, 몬스터 사냥, 스테이지 내 몬스터를 모두 잡고 스테이지 클리어

# 함수 설명
구조체로 소환된 몬스터 정보, 플레이어 정보, 몬스터 정보, 장비 정보를 만들었다.

void init(); //화면 사이즈 등 제일 처음 초기화

void MonInfoFill(); //파일로부터 MonInfo를 채운다.

void StageMonFill(); //스테이지 별로 나올 수 있는 몬스터가 들어있는 배열을 만든다.

void AFILL(); //아스키 코드 폰트 만들기

void gotoxy(int x,int y); //커서 (x,y)로 이동

void print(int CSZ,char str[], int c, int r); //문자열 출력

void FilePrint(FILE *F, int x, int y); //파일 출력

void Knightstr(); //파일로 부터 knight 를 Strknight에 넣음

void Mainpage(); //처음 화면

void EraseMonsters(); //모든 몬스터를 지운다.(이미지만)

void Erase(int X, int Y, int eX, int EY); //지울 직사각형의 왼쪽 위 x,y좌표 , 가로 길이, 세로 길이

void ErasePlayer(int X, int Y, int T); //T번에 있는 문자에 맞춰 콘솔을 지운다.

void check_key(); //키보드 확인 및 주인공 이동, 공격

void shopfunc(); //상점 로그 띄우기

void bankfunc(); //은행 로그 띄우기

void make_floor(); //밑 바닥 만들기

void Infoprint(int num); //플레이어의 정보 등을 콘솔에 출력한다.

int Check_lv();//플레이어의 레벨업

void towerfunc(); //탑 안으로 이동

int MonCanMove(int num, int mx, int my); //num번 몬스터가 mx my만큼 움직일 수 있는지 반환

void PrintKnight(int X, int Y, int t); //knight.txt 파일로 부터 읽어 출력하는 것 보다 미리 읽은 문자열을 출력하는 것이 더 빨라서 만듬 X,Y좌표에 knight출력

void Summon(); //몬스터를 소환

void MonsterGen(); //스테이지에 맞는 몬스터를 소환

void MapSummon(); //스테이지의 맵을 그린다.

void MapGen(); //탑 안 스테이지의 맵을 생성

int PlayerCanMove(int X, int Y); //knight(플레이어)가 (X,Y)로 이동 할 수 있는 지 여부 반환

void PlayerUpdate(); //플레이어의 위치를 업데이트

void wait(int num); //for 문을 num번 돌림(1ms 미만의 시간 지연)

void DivideCon(); //플레이 창과 게임 내 콘솔 창을 나누어 줌

void ConsolePrint(int line, char *str, int num); //line번째 줄에 str을 출력하고 num/1000초 만큼 딜레이를 줌

void Village(); //마을 화면

int MonsterMeetPlayer(); //플레이어와 몬스터가 만났을 경우 체력을 갱신 

# 개발 환경
codeblocks 13.12
