#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<ctype.h>
#include<mmsystem.h>
#include "font.h"
#include "Digitalv.h"
#define MAXX 600
#define MAXY 150
#define REALX 400
#define NOMINMAX
#define ARROW_LEFT   75      // 좌측방향키
#define ARROW_RIGHT  77      // 우측방향키
#define ARROW_UP     72      // 위쪽방향키
#define ARROW_DOWN   80      // 아래방향키

#define KnightX 41 //41
#define KnightY 33
#define KnightX2 70
#define KnightY2 33
#define SwordX 30
#define SwordY 3
#define dl 40 //컴퓨터 사양에 따라 설정
char StrKnight[4][KnightY+1][KnightX2+1];
char ASCII[256][10][20],chTemp[1003];
int eventnum,StageNum=0,attack,Villageflag,PlayerAlive,StageClear,MonNum,downflag,fly,prevx,prevy;
int StageMon[50][50],StageMonSize[50],MonList[50],Mon,bsp,chf; //i번 stage에 들어갈 수 있는 몬스터 번호를 저장
char map[MAXY+50][REALX+2];
int mapnum,prevpr,money;
//mapnum, 마지막 출력한 종류
clock_t MonSum; //몬스터가 소환된 시간
clock_t PlayerMoved; //플레이어가 마지막으로 움직인 시간
clock_t LastHit; //플레이어가 마지막에 때린 시간
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
int MonsterMeetPlayer();

struct ALIVE  //플레이어와 몬스터의 기본적인 정보를 저장한다.
{
    char name[20]; //이름
    int ATK,DEF,lv,EXP,look,HP; //공격, 방어(최대 체력), 레벨, 경험치, 보고 있는 방향, 현재 체력
    int curX,curY,MOVE[2],MaxX,MaxY; //현재 x좌표, y좌표, 일정 시간 동안 움직이는 x좌표의 양, 플레이어나 몬스터를 나타내는 파일의 최대 크기
} Player,MonInfo[50];
struct Monster
{
    int ATK,DEF,EXP,MOVE[2],look,up,curX,curY,MaxX,MaxY,num;
    FILE *A,*B;
    ///공격,방어,경험치,이동,보는 방향 -1,1, 보이는 모습, 현재 x,y좌표, 텍스트의 x,y좌표, 몬스터가 몇 번째 인지;
} Monster[10];
struct MapGen
{
    int X[10], Y[10],len[10]; //점프 바가 위치하는 x좌표, y좌표, 점프 바의 길이
} MAP[20];
struct Weapon  //무기의 공격력, 방어력
{
    int ATK,DEF; //공격력, 방어력
} NOW, GET;
//PlayInfo
int died, moneyspent, maxatk, maxdef, maxstage,monsterdied;
clock_t playtime,up;

int main()
{
    int dwID;
    MCI_OPEN_PARMS mciOpen;   // MCI_OPEN_PARAMS 구조체 변수
    mciOpen.lpstrDeviceType = "mpegvideo";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
    mciOpen.lpstrElementName = "music.mp3"; // 파일이름
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE|MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

    // 재생
    MCI_PLAY_PARMS mciPlay;
    dwID= mciOpen.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
    //MCI_NOTIFY : 기본, MCI_DGV_PLAY_REPEAT : 반복


    playtime=clock();
    char ch;
replay: //다시 플레이 할 때
    init(); //기본적인 변수 값 및 화면의 초기값 설정
    AFILL(); //출력 폰트 만들기 font.h를 직접 만들어서 include 했음
    // print(1,"I AM GROOT",10,0);
    Mainpage(); //초기 화면(Press any key to continue)로 이동
    Village(); //마을로 이동(3가지 건물 중에 선택하는 화면)
    while(kbhit())
        ch=getch(); //다음에 나올 초기화면 때문에 입력 받은 키 다 버림
    FILE *F=fopen("plusstat.txt","r"); //다시 태어나는 것을 위해서 플레이어의 영구 스탯 파일을 읽어옴
    int a,b;
    fscanf(F,"%d %d",&a,&b); //영구 공격력, 방어력을 입력 받음
    fclose(F);
    FILE *W=fopen("plusstat.txt","w"); //파일을 지우며 쓰기 모드로 변환
    fprintf(W,"%d %d %d",a+(Player.ATK-a)/10,b+(Player.DEF-b)/10,money); //플레이어의 공격력 방어력의 10%를 플레이어의 영구 스탯으로
    fclose(W);
    goto replay;
    system("pause>null");
    return 0;
}
void init()
{
    //전역변수 초기화
    memset(StrKnight,0,sizeof(StrKnight));
    memset(ASCII,0,sizeof(ASCII));
    memset(chTemp,0,sizeof(chTemp));
    eventnum=StageNum=attack=Villageflag=PlayerAlive=StageClear=MonNum=downflag=fly=prevx=prevy=0;
    memset(StageMon,0,sizeof(StageMon));
    memset(StageMonSize,0,sizeof(StageMonSize));
    memset(MonList,0,sizeof(MonList));
    memset(map,0,sizeof(map));
    memset(&Player,0,sizeof(Player));
    memset(MonInfo,0,sizeof(MonInfo[0]));
    memset(Monster,0,sizeof(Monster[0]));
    memset(MAP,0,sizeof(MAP[0]));
    Mon=mapnum=prevpr;
    Player.lv=1;
    Player.MaxX=KnightX;
    Player.MaxY=KnightY;
    //영구 스탯을 막 태어난 플레이어 정보에 넣기
    FILE *F=fopen("plusstat.txt","r");
    fscanf(F,"%d %d %d",&Player.ATK,&Player.DEF,&money);
    Player.HP=Player.DEF;
    //콘솔 크기 조정
    sprintf(chTemp,"mode con cols=%d lines=%d",MAXX,MAXY);
    system(chTemp);
    //빠른 출력을 위해 파일을 미리 읽어와 문자열에 넣어놓음
    Knightstr();
    //스테이지에 나오는 몬스터 번호를 넣어놓음
    StageMonFill();
    //몬스터 정보를 채움
    MonInfoFill();
    srand( (unsigned)time(NULL) ); //난수 생성
    //커서 안 보이게
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    fclose(F);
    return;
}
void MonInfoFill()  //몬스터 정보를 넣음
{
    int i=1,x,y;
    char ch;
    FILE *F=fopen("monsterinfo.txt","r");
    //,&MonInfo[i].MaxY,&MONInfo[i].MaxX
    while(fscanf(F,"%d %d %d %d %d",&MonInfo[i].ATK,&MonInfo[i].DEF,&MonInfo[i].EXP,&MonInfo[i].MOVE[0],&MonInfo[i].MOVE[1])!=EOF)
        i++;
    for(i=1; i<=20; i++) //monster의 MaxX와 MaxY
    {
        sprintf(chTemp,"monster%d-up.txt",i); //몬스터가 모양이 달라지는 것을 표현하려면 두 가지 파일이 필요함 up과 down 파일을 반복해서 보여줌
        FILE *A=fopen(chTemp,"r");
        sprintf(chTemp,"monster%d-down.txt",i);
        FILE *B=fopen(chTemp,"r");
        //몬스터 파일의 행과 열의 크기를 넣어 놓음
        x=y=0;
        while(fscanf(A,"%c",&ch)!=EOF)
        {
            if(ch=='\n')
                y++,x=0;
            else
            {
                ++x;
                if(MonInfo[i].MaxX < x)
                    MonInfo[i].MaxX=x;
            }
        }
        MonInfo[i].MaxY=y;
        x=y=0;
        while(fscanf(B,"%c",&ch)!=EOF)
        {
            if(ch=='\n')
                y++,x=0;
            else
            {
                ++x;
                if(MonInfo[i].MaxX < x)
                    MonInfo[i].MaxX=x;
            }
        }
        if(MonInfo[i].MaxY<y)
            MonInfo[i].MaxY=y;
        fclose(A);
        fclose(B);
    }
    fclose(F);
    return;
}
void StageMonFill()  //몬스터 정보를 넣음
{
    //파일에는 3번 몬스터가 나올 수 있는 스테이지의 하한과 상한이 있음
    //이 함수에서는 1번 스테이지에 몇 번 몬스터 들이 나올 수 있는지 i번째 스테이지에서 나올 수 있는 몬스터들을 StageMon[i]에 저장
    int i,a,b,cnt=3;
    FILE *F=fopen("monsterstage.txt", "r");
    while(fscanf(F,"%d %d",&a,&b)!=EOF)
    {
        for(i=a; i<=b; i++)
        {
            StageMon[i][StageMonSize[i]++]=cnt;
        }
        cnt++;
    }
    for(i=3; i<20; i++)
    {
        StageMon[41][StageMonSize[41]++]=i;
    }
    fclose(F);
    return;
}
void PrintKnight(int X, int Y, int t)  //knight는 가장 움직임이 잦기 때문에 문자열에 넣은 것을 출력
{
    int i;
    for(i=0; i<KnightY-2; i++)
    {
        gotoxy(X,Y++);
        puts(StrKnight[t][i]); //goto로 하나하나 출력하면 출력이 너무 오래 걸려서 puts사용
    }
    return;
}

void Knightstr()
{
    char ch;
    int x=0,y=0;
    //오른 쪽을 보고 있는 나이트
    FILE* Knight=fopen("knight.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[0][y][x++]=ch;
    }
    y=0;
    //왼쪽을 보고 있는 나이트
    Knight=fopen("knight_reverse.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[1][y][x++]=ch;
    }
    y=0;
    //오른쪽으로 공격을 하는 나이트
    Knight=fopen("knight2.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[2][y][x++]=ch;
    }
    y=0;
    //왼쪽으로 공격을 하는 나이트
    Knight=fopen("knight2_reverse.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[3][y][x++]=ch;
    }
    y=0;
    fclose(Knight);
    return;
}
void Mainpage()
{
    FILE *knight=fopen("knight.txt", "r"),*castle=fopen("castle.txt", "r");
    FilePrint(castle,10,10);
    print(2,"GMO invasion",270,10); //글자 출력
    print(2,"------------",270,33);
    Sleep(100);
    print(1,"MOVE:WASD KEYS",270,50);
    print(1,"SELECT AND",270,75);
    print(1,"ATTACK:SPACE BAR",270,90);
    while(!kbhit())  //키가 입력되면 게임을 시작
    {
        print(1,"PRESS ANY KEY TO CONTINUE",10,130);
        Sleep(250);
        print(1,"                         ",10,130);
        Sleep(250);
    }
    while(kbhit())
        getch(); //여러 번 눌렀을 수도 있으니까 입력된 키 버림
    fclose(knight);
    fclose(castle);
    return;
}
void gotoxy(int x,int y)
{
    COORD pos= {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return;
}
/*void ErasePlayer(int X, int Y, int T){ //이동할 것의 x,y 좌표 이미지의 x, y좌표 움직일 x좌표, 없어질 y좌표
    int i,j;
    for(i=0;i<KnightY;i++){
        gotoxy(j+X,i+Y);
        for(j=0;j<KnightX2;j++){
            if(StrKnight[T][i][j]!='\0') {
                printf(" ");
            }
        }
    }
    return;
}*/
void EraseMonsters()   //스테이지 내의 몬스터 지우기
{
    int i;
    for(i=0; i<MonNum; i++)
    {
        Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY);
    }
    return;
}
void Erase(int X, int Y, int eX, int EY)  //이동할 것의 x,y 좌표 이미지의 x, y좌표 움직일 x좌표, 없어질 y좌표
{
    gotoxy(X,Y);
    int i;
    for(i=0; i<eX; i++)
        chTemp[i]=' '; //chTemp에 넣어 놓았다가
    chTemp[eX]=0;
    for(i=0; i<EY; i++)
    {
        puts(chTemp); //printf보다 빠른 puts로 지우기
        gotoxy(X,Y+i);
    }
    return;
}
void shopfunc()  //상점 얻음
{
    system("cls");
    DivideCon();
    int r=0,c=0,flag=1,num=0,i;
    int ln=25,po[5]= {1,4,16,64,256};
    int inf[5][2]= {{9,4},{99,44},{999,444},{9999,4444},{99999,44444}}; //무기, 방어구 가격
    //무기, 방어구 정보 출력
    print(1,"weapon1:9$",10,ln*0+2);
    print(1,"weapon2:99$",10,ln*1+2);
    print(1,"weapon3:999$",10,ln*2+2);
    print(1,"weapon4:9999$",10,ln*3+2);
    print(1,"weapon5:99999$",10,ln*4+2);
    print(1,"exit",10,ln*5+2);
    print(1,"armor1:4$",210,ln*0+2);
    print(1,"armor2:44$",210,ln*1+2);
    print(1,"armor3:444$",210,ln*2+2);
    print(1,"armor4:4444$",210,ln*3+2);
    print(1,"armor5:44444$",210,ln*4+2);
    print(1,"goto tower",210,ln*5+2);
    print(1,"-------------",c*200+10,ln*r+13);
    //가진 무기, 방어구 출력
    Infoprint(6);
    Infoprint(7);
    Infoprint(8);
    //무기, 방어구 선택
    while(flag)
    {
        if(GetAsyncKeyState('W')&0x8000 && r>0)
        {
            print(1,"             ",c*200+10,ln*r+13);
            r--;
            print(1,"-------------",c*200+10,ln*r+13);
            Sleep(100);
        }
        else if(GetAsyncKeyState('S')&0x8000 && r<5)
        {
            print(1,"             ",c*200+10,ln*r+13);
            r++;
            print(1,"-------------",c*200+10,ln*r+13);
            Sleep(100);
        }
        else if(GetAsyncKeyState('A')&0x8000 && c==1)
        {
            print(1,"             ",c*200+10,ln*r+13);
            c=0;
            print(1,"-------------",c*200+10,ln*r+13);
            Sleep(100);
        }
        else if(GetAsyncKeyState('D')&0x8000 && c==0)
        {
            print(1,"             ",c*200+10,ln*r+13);
            c=1;
            print(1,"-------------",c*200+10,ln*r+13);
            Sleep(100);
        }
        else if(GetAsyncKeyState(' ')&0x8000)
        {
            if(r==5)
            {
                if(c==0)
                {
                    return;
                }
                if(c==1)
                {
                    towerfunc();
                    return;
                }
            }
            num=1;
            if(money>inf[r][c])
            {
                ConsolePrint(1,"selected",1000);
                // 1 + (n=10000, p=po[r]/10000인 이항 분포)
                int n=10000;
                for(i=0; i<n; i++)
                {
                    if(rand()%10000<po[r])
                        num++;
                }
                if(c==0)
                {
                    if(NOW.ATK<num)
                    {
                        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
                        NOW.ATK=num;
                        Infoprint(6);
                    }
                }
                else
                {
                    if(NOW.DEF<num)
                    {
                        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
                        NOW.DEF=num;
                        Infoprint(7);
                    }
                }
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
                money-=inf[r][c];
                moneyspent+=inf[r][c];
                Infoprint(8);
                //돈 파일 쓰기
                FILE *F=fopen("plusstat.txt","w");
                fprintf(F,"%d %d %d",Player.ATK,Player.DEF,money);
                fclose(F);
                sprintf(chTemp, "%s:%d",(c?"armor":"weapon"),num);
                ConsolePrint(1,chTemp,800);
                Sleep(100);
                ConsolePrint(1,chTemp,800);
                Sleep(100);
                Infoprint(6);
                Infoprint(7);
            }
            else
            {
                ConsolePrint(1,"no money",1000);
            }
        }
    }
    return;
}
void bankfunc()
{
    system("cls");
    //PlayInfo
    //int died, moneyspent, maxatk, maxdef, maxstage,monsterdied;
    //clock_t playtime;
    print(1,"Information",100,5);
    sprintf(chTemp,"Died : %d",died);
    print(1,chTemp,100,25);
    sprintf(chTemp,"MaxAtk : %d",maxatk);
    print(1,chTemp,100,45);
    sprintf(chTemp,"MaxDef : %d",maxdef);
    print(1,chTemp,100,65);
    sprintf(chTemp,"MaxStage : %d",maxstage);
    print(1,chTemp,100,85);
    sprintf(chTemp,"Monster died : %d",monsterdied);
    print(1,chTemp,100,105);
    sprintf(chTemp,"Time played : %dmin",(clock()-playtime)/60000);
    print(1,chTemp,100,125);
    Sleep(5000);
    return;
}
void make_floor()  //바닥 만들기
{
    int i,j;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 8);
    for(i=0; i<20; i++)
    {
        gotoxy(0,130+i);
        for(j=0; j<200; j++)
        {
            printf("■");
            map[130+i][j*2]=map[130+i][j*2+1]=1; //벽 및 블록은 1로 표시
        }
    }
    for(i=0; i<=130; i++)
    {
        gotoxy(0,i); //왼쪽 벽
        map[i][0]=map[i][1]=map[i][2]=map[i][3]=map[i][397]=map[i][398]=map[i][399]=map[i][400]=1; //벽 및 블록은 1로 표시
        printf("■");
        gotoxy(398,i); //오른쪽 벽
        printf("■");
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
    return;
    //memset(map[131],0,sizeof(map[131])); //플레이어와 땅 사이의 거리를 줄이기 위해
}
void Infoprint(int num)
{
    /*
    1  : 스테이지 번호
    2  : 레벨
    3  : 공격력
    4  : 체력
    5  : 경험치
    6 : 무기 공격력
    7  : 방어구 체력
    8 : 얻은 무기 공격력
    9 : 얻은 방어구 체력
    10 : 바뀐 정보
    에 따라서 정보를 출력
    */
    int i;
    for(i=0; i<14; i++)
        chTemp[i]=0; //안전하게 초기화
    if(num==1)
        sprintf(chTemp,"STAGE : %d",StageNum);
    else if(num==2)
        sprintf(chTemp,"LV : %d",Player.lv);
    else if(num==3)
        sprintf(chTemp,"ATK : %d",Player.ATK);
    else if(num==4)
        sprintf(chTemp,"HP : %d  %d",Player.HP,Player.DEF);
    else if(num==5)
        sprintf(chTemp,"EXP : %d",Player.EXP);
    else if(num==6)
        sprintf(chTemp,"WEAPON : %d",NOW.ATK);
    else if(num==7)
        sprintf(chTemp,"ARMOR : %d",NOW.DEF);
    else if(num==8)
        sprintf(chTemp,"MONEY : %d",money);
    for(i=strlen(chTemp); i<14; i++)
        chTemp[i]=' ';
    chTemp[14]=0;
    ConsolePrint(num,chTemp,0);
    return;
}
int Check_lv()  //플레이어의 레벨을 체크하고 경험치가 Player의 레벨 *30 이상이라면 레벨 업
{
    if(Player.EXP>=Player.lv*30)
    {
        Player.EXP-=Player.lv*30;
        int num=rand()%(5+Player.lv); //trpg 장르의 핵심은 랜덤성, 방어력과 공격력이 랜덤으로 오름, 여러 번 해보면서 공격력과 방어력 증가치의 합을 조정함
        Player.DEF+=num,Player.ATK+=(5+Player.lv)-num; //공격력 방어력 up
        Player.lv++; //레벨 업
        Player.HP=Player.DEF; //현재 체력이 최대 체력으로 회복
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
        Infoprint(2); //lv 갱신
        Infoprint(3); //공격력 갱신
        Infoprint(4); //체력 갱신
        Infoprint(5); //경험치 갱신
        Sleep(1000);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
        Infoprint(2); //lv 갱신
        Infoprint(3); //공격력 갱신
        Infoprint(4); //체력 갱신
        Infoprint(5); //경험치 갱신
        return 1; //한 번에 2lv 이상이 오를 수 있으니 한 번 더 체크
    }
    return 0; //레벨 업 안 했으니 체크 할 필요 없음
}
void BOSS() //보스가 나온다.
{
    int i,t;
    char skill[10][10]= {"TRANSPORT\0","DASH\0"};
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 4);
    for(i=0; i<5; i++)
    {
        ConsolePrint(8,"BOSS ALERT",400);
        ConsolePrint(8,"          ",10);
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
    Monster[0].num=21;
    Monster[0].ATK=MonInfo[21].ATK;
    Monster[0].DEF=MonInfo[21].DEF;
    Monster[0].MOVE[0]=MonInfo[21].MOVE[0];
    Monster[0].MOVE[1]=MonInfo[21].MOVE[1];
    Monster[0].curX=200;
    Monster[0].curY=0;
    Monster[0].MaxX=50;
    Monster[0].MaxY=42;
    Monster[0].EXP=MonInfo[21].EXP;
    sprintf(chTemp,"devil.txt\0",Monster[0].num);
    Monster[0].A=fopen(chTemp,"r");
    sprintf(chTemp,"devil.txt\0",Monster[0].num);
    Monster[0].B=fopen(chTemp,"r");
    clock_t BS=clock(),p=rand()%5000+2000,up=clock();
    PrintKnight(Player.curX=10,Player.curY=100-KnightY,0);
    MonNum=1;
    //보스인 20번쨰 몬스터로 설정
    bsp=20;
    while(PlayerAlive && Monster[0].num>0)
    {
        PlayerUpdate();
        if(clock()-up>250)   //0.25초마다 몬스터 정보를 체크
        {
            if(MonsterMeetPlayer(up))  //몬스터가 플레이어를 공격하는 함수, 몬스터가 플레이어를 죽였다면 1을 반환
            {
                PlayerAlive=0; //플레이어는 죽었음
                break;
            }
            Summon(); //몬스터를 소환하기
            up=clock(); //다시 up을 현재 시각으로
        }
        if(clock()-BS>p)
        {
            t=rand()%2;
            ConsolePrint(8,skill[t],400);
            Monster[0].MOVE[0]=Monster[0].MOVE[1]=0;
            if(t==0)
            {
                Erase(Monster[0].curX,Monster[0].curY,Monster[0].MaxX,Monster[0].MaxY+2);
                Monster[0].curX=rand()%340;
                Monster[0].curY=0;
            }
            if(t==1)
            {
                Monster[0].MOVE[0]=5;
                Monster[0].MOVE[1]=3;
                Monster[0].look=-Player.look;
            }
            p=rand()%5000+2000;
            BS=clock();
        }
    }
    bsp=0;
    ConsolePrint(8,"CLEAR",4000);
    return;
}
void towerfunc()
{
    Player.ATK+=NOW.ATK;
    Player.DEF+=NOW.DEF;
    Player.HP+=NOW.DEF;
    system("cls"); //다 지우기
    DivideCon(); //콘솔과 게임의 경계 나누기
    int i,j,t;
    clock_t up=clock(); //현재 시각을 저장
    make_floor(); //바닥 만들기
    PlayerAlive=1; //플레이어가 살아 있음
    while(kbhit())
        getch(); //그 사이에 입력된 문자 버리기
    for(i=1; i<=7; i++) //기본 정보 출력하기
    {
        Infoprint(i);
    }
    while(PlayerAlive && StageNum<=40)  //플레이어가 살아 있다면
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
        Infoprint(1); //스테이지를 출력
        Sleep(1000);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
        Infoprint(1);
        Player.look=1; //플레이어는 오른쪽을 보고 있음
        PrintKnight(Player.curX=10,Player.curY=100-KnightY,0); //knight를 출력
        MapGen(); //map만들기
        MonsterGen(); //나올 몬스터 정보를 만들기
        while(5<Player.curX && Player.curX<340)
        {
            PlayerUpdate(); //사용자가 키를 눌렀다면 플레이어를 이동하게 함
            if(clock()-up>100)   //0.1초마다 몬스터 정보를 체크
            {
                if(MonsterMeetPlayer(up))  //몬스터가 플레이어를 공격하는 함수, 몬스터가 플레이어를 죽였다면 1을 반환
                {
                    PlayerAlive=0; //플레이어는 죽었음
                    break;
                }
                Summon(); //몬스터를 소환하기
                up=clock(); //다시 up을 현재 시각으로
            }
        }
        if(Player.curX>=340)  //스테이지 클리어
        {
            EraseMonsters(); //남은 몬스터를 모두 지우기
            t=1; //플레이어가 모든 몬스터를 죽였나 확인
            for(i=0; i<MonNum; i++)
                if(Monster[i].num!=-1)
                    t=0;
            if(t)  //모든 몬스터가 -1이면 (모두 죽었으면 )
            {
                Player.EXP+=++StageNum*3; //스테이지 *3 에 해당하는 경험치 보너스를 받음
                Check_lv(); //레벨 업?
                Infoprint(5); //EXP 정보 갱신
            }
            else
                StageNum++;
        }
        else  //플레이어가 뒤로 옴
        {
            EraseMonsters(); //몬스터를 다 지우기
            if(StageNum)
                --StageNum; //전 스테이지로 이동
        }
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //플레이어 지우기
    }
    if(StageNum>40)
    {
        BOSS();
        return;
    }
    died++;
    if(maxatk<Player.ATK)
        maxatk=Player.ATK;
    if(maxdef<Player.DEF)
        maxdef=Player.DEF;
    if(maxstage<StageNum)
        maxstage=StageNum;

    system("cls");
    print(4,"You Died",108,51); //넌 죽었어
    Sleep(1000);
    print(4,"        ",108,51);
    print(4,"You Died",108,51);
    Sleep(2000);
    //무기, 방어구 공격력 재설정
    Player.ATK-=NOW.ATK;
    Player.DEF-=NOW.DEF;
    NOW.ATK=NOW.DEF=0;
    return;
}
int MonCanMove(int num, int mx, int my)  //상하좌우로만 이동을 확인 가능 (실행 시간을 줄이기 위해)
{
    int si,ei,sj,ej,i,j;
    //시작 y좌표,끝 y좌표,시작 x좌표,끝 x좌표
    //몬스터가 맵을 이동할 수 있는지 확인 하는 함수인데
    if(mx>0)
        sj=Monster[num].curX+Monster[num].MaxX,ej=Monster[num].curX+Monster[num].MaxX+mx,si=Monster[num].curY+1,ei=Monster[num].curY+Monster[num].MaxY-1;
    else if(mx<0)
        sj=Monster[num].curX+mx,ej=Monster[num].curX,si=Monster[num].curY+1,ei=Monster[num].curY+Monster[num].MaxY-1;
    else if(my>0)
        sj=Monster[num].curX,ej=Monster[num].curX+Monster[num].MaxX,si=Monster[num].curY+Monster[num].MaxY,ei=Monster[num].curY+Monster[num].MaxY+my;
    else if(my<0)
        sj=Monster[num].curX,ej=Monster[num].curX+Monster[num].MaxX,si=Monster[num].curY+my,ei=Monster[num].curY;
    else
        return 1;
    for(i=si; i<=ei; i++)
    {
        for(j=sj; j<=ej; j++)
        {
            if(map[i][j])
                return 0;
        }
    }
    return 1;
}
int MonsterMeetPlayer()  //몬스터가 플레이어를 공격하는 기능을 하는 함수
{
    int i,flag=0;
    for(i=0; i<MonNum; i++)
    {
        //몬스터가 만났다면
        flag=0;
        flag|=Player.curX<=Monster[i].curX && Monster[i].curX<=Player.curX+Player.MaxX-10;
        flag|=Player.curX<=Monster[i].curX+Monster[i].MaxX && Monster[i].curX+Monster[i].MaxX<=Player.curX+Player.MaxX-5;
        flag|=(Player.curY<=Monster[i].curY && Monster[i].curY<=Player.curY+Player.MaxY-5)<<1;
        flag|=(Player.curY<=Monster[i].curY+Monster[i].MaxY && Monster[i].curY+Monster[i].MaxY<=Player.curY+Player.MaxY-5)<<1;
        if(flag==3 && Monster[i].num>0)
        {
            Player.HP-=Monster[i].ATK; //몬스터의 공격력 만큼 플레이어의 현재 체력 감소
            Infoprint(4); //체력 정보 갱신
            if(Player.HP<=0)
                return 1; //플레이어가 죽으면 1 반환
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 4);
            ConsolePrint(8,"HP down",500);
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
            chf=1;
        }
    }
    return 0;
}
void Summon()  //몬스터 갱신
{
    int i,num;
    FILE *F;
    for(i=0; i<MonNum; i++)
        if(Monster[i].num>0)  //몬스터가 죽으면 숫자를 -1로 살아 있는 몬스터만 갱신
        {
            if((clock()-MonSum)%3000<1500)
                F=Monster[i].A; //1.5초마다 몬스터 출력 파일을 바꿈
            else
                F=Monster[i].B;
            while(MonCanMove(i,0,2))  //몬스터가 밑으로 내려 갈 수 있다면 내려 가게(공중에서 떠 다니지 않게)
            {
                fseek(F,0,SEEK_SET);
                Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1); //+1+1
                FilePrint(F,Monster[i].curX,Monster[i].curY+=2);
            }
            fseek(F,0,SEEK_SET); //파일 포인터 다시 앞으로
            //1초마다 몬스터가 움직이는 양이 다름 예를 들어 move[0]=-5,move[1]=10 이면 뒤로 갔다가 갑자기 앞으로 움직이는 몬스터
            //move[0]=0,move[1]=10 멈췄다가 빠르게 이동, move[0]=3,move[1]=3 느린 속도로 일정히 이동
            if((clock()-MonSum)%2000<1000)
            {
                if(MonCanMove(i,Monster[i].MOVE[0]*Monster[i].look,0))  //몬스터가 움직일 수 있다면 움직이기
                {
                    Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1);
                    FilePrint(F,Monster[i].curX+=Monster[i].MOVE[0]*Monster[i].look,Monster[i].curY);
                }
                else
                    Monster[i].look=-Monster[i].look; //몬스터가 벽에 막혀서 갈 수 없다면 반대 방향으로 움직이게 바꾸기
            }
            else
            {
                if(MonCanMove(i,Monster[i].MOVE[1]*Monster[i].look,0))  //몬스터가 움직일 수 있다면 움직이기
                {
                    Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1);
                    FilePrint(F,Monster[i].curX+=Monster[i].MOVE[1]*Monster[i].look,Monster[i].curY);
                }
                else
                    Monster[i].look=-Monster[i].look; //몬스터가 벽에 막혀서 갈 수 없다면 반대 방향으로 움직이게 바꾸기
            }
        }

    return;
}
void MonsterGen()  //몬스터 만들기
{
    MonNum=rand()%3+2; //스테이지당 몬스터는 2~4마리
    int i,temp;
    //StageNum
    ///debug
    for(i=0; i<MonNum; i++)
    {
        //몬스터 정보 저장, monsterinfo를 쓰면 안 되는데 체력, 위치 등의 정보가 바뀌니 따로 저장 해야 함
        Monster[i].num=MonList[i]=StageMon[StageNum][rand()%StageMonSize[StageNum]];
        Monster[i].ATK=MonInfo[MonList[i]].ATK;
        Monster[i].DEF=MonInfo[MonList[i]].DEF;
        Monster[i].MOVE[0]=MonInfo[MonList[i]].MOVE[0];
        Monster[i].MOVE[1]=MonInfo[MonList[i]].MOVE[1];
        Monster[i].curX=rand()%250+80;
        Monster[i].curY=30;
        Monster[i].MaxX=MonInfo[MonList[i]].MaxX;
        Monster[i].MaxY=MonInfo[MonList[i]].MaxY;
        Monster[i].EXP=MonInfo[MonList[i]].EXP;
        sprintf(chTemp,"Monster%d-up.txt\0",Monster[i].num);
        Monster[i].A=fopen(chTemp,"r");
        sprintf(chTemp,"Monster%d-down.txt\0",Monster[i].num);
        Monster[i].B=fopen(chTemp,"r");
        //만약 끝쪽에 있다면 많이 움직일 수 있는 방향으로 가기(사실 어차피 못 가는 곳이면 방향을 반대로 바꿔서 가서 없어도 되지만 혹시 모를 예외에 대비함)
        if(Monster[i].curX>300)
            Monster[i].look=-1;
        else if(Monster[i].curX<100)
            Monster[i].look=1;
        else
            Monster[i].look=(rand()&1)?1:-1;
    }
    MonSum=clock(); //몬스터가 출현한 시간
    return;
}
void MapSummon()  //점프하는 땅 만들기
{
    int EX,EY,ELEN,i;
    //맵을 자동으로 만들었더니 너무 기괴한 모양이 많이 나와서 미리 20개의 맵을 만들고 그 중 하나를 랜덤으로
    //TRPG 장르인 만큼 맵에 따라서 몬스터 사냥의 난이도가 많이 다름
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 8);
    sprintf(chTemp,"map%d.txt\0",mapnum);
    FILE *B=fopen(chTemp,"r");
    while(fscanf(B,"%d %d %d",&EX,&EY,&ELEN)!=EOF)
    {
        gotoxy(EX,EY);
        for(i=0; i<ELEN; i++)
        {
            printf("■");
            map[EY][EX+i*2]=map[EY][EX+i*2+1]=1; //2바이트 니까 1(벽)을 2개씩 저장
        }
        gotoxy(EX,EY+=1);
        for(i=0; i<ELEN; i++)
        {
            printf("■");
            map[EY][EX+i*2]=map[EY][EX+i*2+1]=1;
        }
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
    fclose(B);
    return;
}
void MapGen()  //전 스테이지의 맵을 지우고 몇 번 맵을 할지 고름
{
    int i,j,EX,EY,ELEN;
    sprintf(chTemp,"map%d.txt\0",mapnum);
    FILE *A=fopen(chTemp,"r");
    while(fscanf(A,"%d %d %d",&EX,&EY,&ELEN)!=EOF)
    {
        gotoxy(EX,EY);
        for(i=0; i<ELEN; i++)
        {
            printf("  ");
            map[EY][EX+i*2]=map[EY][EX+i*2+1]=0;
        }
        gotoxy(EX,EY+=1);
        for(i=0; i<ELEN; i++)
        {
            printf("  ");
            map[EY][EX+i*2]=map[EY][EX+i*2+1]=0;
        }
    }
    mapnum=rand()%20; //몇 번 맵 할까
    //ConsolePrint(2,chTemp);
    MapSummon(); //맵 출력, 맵 정보 저장
    fclose(A);
    return;
}

int PlayerCanMove(int X, int Y)  //플레이어가 (X,Y)좌표로 움직일 수 있늕 지 확인
{
    int i,j;
    for(i=Y-2; i<Y+KnightY-2; i++)
    {
        for(j=X; j<X+KnightX; j++)
        {
            if(map[i][j])
                return 0; //벽이 있어서 못움직이면 0 반환
        }
    }
    return 1; //벽 없으면 1 반환
}
void print(int CSZ,char str[], int c, int r)  //폰트 사이즈, 출력 문자, 출력할 위치 x, y
{
    int i,j,a,b;
    char pr;
    while(pr=toupper(*str))  //혹시 소문자로 출력하게 했을 수도 있으니까 대문자로(폰트가 대문자만 있음)
    {
        str++;
        for(i=0; i<10; i++)
        {
            for(a=0; a<CSZ; a++) //폰트 사이즈 만큼 행 크기 배로 늘리기
            {
                gotoxy(c,r+i*CSZ+a); //
                for(j=0; ASCII[pr][i][j];)
                {
                    for(b=0; b<CSZ; b++) //폰트 사이즈 만큼 열 크기 배로 늘리기
                    {
                        if(ASCII[pr][i][j]==' ')   //만약 공백이라면 하나 출력
                        {
                            printf("%c",ASCII[pr][i][j]);
                        }
                        else  //공백이 아니라면 ■으로 2바이트니까 2개 출력
                        {
                            printf("%c%c",ASCII[pr][i][j],ASCII[pr][i][j+1]);
                        }
                    }
                    j+=(ASCII[pr][i][j]!=' ')+1; //공백이면 +1, 네모면 +2
                }
            }
        }
        //커서 이동 해야 함
        gotoxy(c+=12*CSZ+1,r); //폰트가 CSZ배로 출력 되니 기본 폰트가 차지 하는 칸이 12칸인데 CSZ배 만큼 이돋, 글자가 서로 붙어서 알아보기 힘들어서 자간을 1칸으로 만듬
    }
    return;
}

void FilePrint(FILE *F, int x, int y)  //(x,y)에 파일 F를 출력하기
{
    gotoxy(x,y);
    char ch;
    while(fscanf(F,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            gotoxy(x,y+=1); //줄바굼
        else
            printf("%c",ch); //출력
    }
    return;
    fclose(F);
}
void PlayerUpdate()  //플레이어의 좌표 움직임 및 공격 처리
{
    int i;
    if(GetAsyncKeyState(' ') & 0x8000 && clock()-LastHit>300)  //마지막으로 공격한 지 0.5 초가 지났고 또 공격을 눌렀다면
    {
        if(Villageflag==1)  //만약 메인 화면에 village에 있었다면
        {
            if(0<=Player.curX && Player.curX<=100)
                Villageflag=2; //Shop
            else if(101<=Player.curX && Player.curX<=230)
                Villageflag=3; //Bank
            else if(231<=Player.curX && Player.curX<=400)
                Villageflag=4; //Tower
            return;
        }
        downflag=1; //내려갈 수 있다.
        int i,j,k;
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //우선 플레이어를 지운다.
        //그리고 칼을 지운 플레이어를 출력한다.
        if(Player.look==1)
            PrintKnight(Player.curX,Player.curY,2);
        else
            PrintKnight(Player.curX,Player.curY,3);
        if(Player.look==1)  //오른쪽을 보고 있다면
        {
            //만약 플레이어가 벽을 때린다면 공격할 수 없음
            for(i=Player.curY+15; i<=Player.curY+15+SwordY; i++)
            {
                for(j=Player.curX+KnightX; j<=Player.curX+KnightX+SwordX; j++)
                {
                    if(map[i][j])
                        return;
                }
            }
            //플레이어의 손 위치에 칼을 출력한다.
            FILE *F=fopen("sword.txt","r");
            FilePrint(F,Player.curX+KnightX,Player.curY+15);
            //0.25초 기다린다.
            Sleep(250);
            //몬스터를 공격했는지를 확인한다.
            for(i=0; i<MonNum; i++)
            {
                //만약 플레이어가 몬스터를 공격했다면(칼과 몬스터가 만나면, 좌표를 이용하여 판정)
                if(Player.curX<=Monster[i].curX && Monster[i].curX<=Player.curX+KnightX+SwordX && (Player.curY<=Monster[i].curY+Monster[i].MaxY && Player.curY+KnightY>=Monster[i].curY+15))
                {
                    Monster[i].DEF-=Player.ATK; //몬스터의 체력은 플레이어의 공격력만큼 깎임
                    if(Monster[i].DEF<=0 && Monster[i].num>0)   //몬스터의 체력이 0이하이고 몬스터가 살아있다면
                    {
                        monsterdied++;
                        money+=Monster[i].num*((int)sqrt(Monster[i].num))*(rand()%3); //돈은 몬스터 번호^1.5 * 0~2배 만큼 얻음
                        Player.EXP+=Monster[i].EXP; //플레이어의 경험치 갱신
                        Monster[i].num=-1;//몬스터 죽음
                        Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1); //몬스터 지우기
                        Check_lv(); //레벨 확인
                        Infoprint(5); //경험치 갱신
                    }
                    Monster[i].look=-Player.look; //공격을 받았다면 방향을 바꿔 플레이어를 향해 다가옴
                }
            }
            Erase(Player.curX+KnightX,Player.curY+15,SwordX,SwordY+1); //칼 지우기
            PrintKnight(Player.curX,Player.curY,0); //칼을 들고 있는 플레이어 출력
            fclose(F); //파일 닫기
        }
        else //왼쪽을 보고 있다면, (오른쪽을 보고 있다면에서의 역할 과 똑같음)
        {
            for(i=Player.curY+15; i<=Player.curY+15+SwordY; i++)
            {
                for(j=Player.curX-SwordX; j<=Player.curX; j++)
                {
                    if(map[i][j])
                        return;
                }
            }
            FILE *F=fopen("sword_reverse.txt","r");
            FilePrint(F,Player.curX-SwordX,Player.curY+15); //sword길이
            Sleep(250);
            for(i=0; i<MonNum; i++)
            {
                if(Player.curX-SwordX-Monster[i].MaxX<=Monster[i].curX && Monster[i].curX<=Player.curX+10  && (Player.curY<=Monster[i].curY+Monster[i].MaxY && Player.curY+KnightY>=Monster[i].curY+15))
                {
                    Monster[i].DEF-=Player.ATK;
                    if(Monster[i].DEF<=0 && Monster[i].num>0)
                    {
                        monsterdied++;
                        Player.EXP+=Monster[i].EXP;
                        Monster[i].num=-1;
                        Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1);
                        Check_lv();
                        Infoprint(5);
                    }
                    Monster[i].look=-Player.look;
                }
            }
            Erase(Player.curX-SwordX,Player.curY+15,SwordX,SwordY+1);
            PrintKnight(Player.curX,Player.curY,1);
            fclose(F);
        }
        LastHit=clock();
        return;
    }
    //windows.h에 정의되어 있는 함수로 전체 키가 아닌 하나의 키가 눌렸는가 만을 확인해서 kbhit보다 반응 속도가 빠르다.
    //키가 프로그램 실행 후 처음 눌혔다면 0x8000을 반환 두 번째 눌렸을 때부터는 0x8001 반환
    while(downflag==1 && PlayerCanMove(Player.curX,Player.curY+2))  //만약 내려갈 수 있다면
    {
        Erase(Player.curX-prevx,Player.curY-1,KnightX+1,KnightY); //전 위치에 있는 플레이어를 지우자
        if((GetAsyncKeyState('A') & 0x8000) && PlayerCanMove(Player.curX-2,Player.curY))
            Player.curX-=2,prevx=-2,Player.look=-1; //내려가면서 왼쪽 키를 눌렀다면
        if((GetAsyncKeyState('D') & 0x8000) && PlayerCanMove(Player.curX+2,Player.curY))
            Player.curX+=2,prevx=2,Player.look=1; //오른쪽 키를 눌렀다면
        //밑 쪽에 출력
        if(Player.look==1)
            PrintKnight(Player.curX,Player.curY+=2,0);
        else
            PrintKnight(Player.curX,Player.curY+=2,1);
        Sleep(1); //속도 조정
        if(Player.curX>=340)
            return; //좌표가 340 이상이면 스테이지 클리어
    }
    downflag=0; //더 내려갈 수 없음
    if(GetAsyncKeyState('W') & 0x8000)  //점프
    {
        if(fly>15+bsp)  //만약 15번 이상 점프했으면
        {
            downflag=1; //내려가야 돼
            fly=0; //못 날아
            return; //끝
        }
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //플레이어 지우기
        //플레이어의 x좌표 바꾸기, 지울 것을 대비해 prevx 바꾸기 바라 보는 방향 바꾸기
        if((GetAsyncKeyState('A') & 0x8000) && PlayerCanMove(Player.curX-2,Player.curY))
            Player.curX-=2,prevx=-2,Player.look=-1;
        if((GetAsyncKeyState('D') & 0x8000) && PlayerCanMove(Player.curX+2,Player.curY))
            Player.curX+=2,prevx=2,Player.look=1;
        if(PlayerCanMove(Player.curX,Player.curY-2))
            Player.curY-=2; //점프
        if(Player.look==1)
            PrintKnight(Player.curX,Player.curY,0); //바라 보는 방향에 따라 출력
        else
            PrintKnight(Player.curX,Player.curY,1);
        Sleep(5);
        fly++; //한 번 점프함
        return;
    }
    if((GetAsyncKeyState('A') & 0x8000) && PlayerCanMove(Player.curX-2,Player.curY))   //만약 왼쪽으로 갈 수 있고 A를 눌렀다면
    {
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //지우기
        PrintKnight(Player.curX-=2,Player.curY,1); //이동
        Sleep(1);
        downflag=1; //내려 갈 수 있음
        Player.look=-1; //왼쪽 바라봄
        return;
    }
    if((GetAsyncKeyState('D') & 0x8000) && PlayerCanMove(Player.curX+2,Player.curY))  //만약 D를 눌렀고 오른쪽으로 갈 수 있다면
    {
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //지우기
        PrintKnight(Player.curX+=2,Player.curY,0); //이동
        Sleep(1);
        downflag=1; //내려갈 수 있음
        Player.look=1; //오른쪽 바라봄
        return;
    }
    Sleep(dl);
    //아무것도 안 누르고 있으면
    downflag=1; //내려갈 수 있음
    return;
}
/*void SwordUpdate(){
    if(clock()-ATTACK<300)
}*/
void wait(int num)  //1ms 미만의 delay
{
    int i;
    for(i=0; i<num; i++);
    return;
}
void DivideCon()  //콘솔 창 분리
{
    for(int y=0; y<MAXY; y++)
    {
        gotoxy(399,y);
        printf("|");
    }
    print(1,"CONSOLE",420,3);
    print(1,"--------------",400,15); //console log는 16부터 가능
    return;
}
void ConsolePrint(int line, char *str,int num)  //14자리 까지 가능, 10줄까지 가능
{
    //오른쪽 콘솔에 프린트 하도록 돕는 함수
    //행, 문자열, num초 동안 멈춘 후 지우기, 0 이면 계속 보여 주는 것
    int i;
    print(1,str,410,5+line*15);
    if(num)
    {
        Sleep(num); //멈추고
        print(1,"              ",410,5+line*15); //14줄 지우기
    }
    return;
}
void Village()
{
    FILE *Bank=fopen("bank.txt", "r"), *Tower=fopen("tower.txt", "r"), *Shop=fopen("shop.txt","r"),*Knight=fopen("knight.txt","r");
    system("cls");
    //플레이어 좌표 지정
    Player.curX=100,Player.curY=130-47;
    //배경 프린트
    FilePrint(Shop,5,80-54);
    FilePrint(Bank,130,80-50);
    FilePrint(Tower,260,80-80);
    DivideCon();
    make_floor();
    Villageflag=1;
    while(1)
    {
        PlayerUpdate(); //플레이어 정보 갱신(위치, 공격, 체력, 경험치, 레벨 등을 갱신 하는데 여기서는 위치와 선택 여부만)
        //선택된 flag에 따라 다른 기능으로 이동
        if(Villageflag==2)
        {
            ConsolePrint(1,"SHOP SELECTED\0",1500);
            shopfunc();
            break;
        }
        if(Villageflag==3)
        {
            ConsolePrint(1,"BANK SELECTED\0",1500);
            bankfunc();
            break;
        }
        if(Villageflag==4)
        {
            ConsolePrint(1,"TOWER SELECTED\0",1500);
            towerfunc();
            break;
        }
    }
    //파일 닫기
    fclose(Bank);
    fclose(Tower);
    fclose(Shop);
    fclose(Knight);
    return;
}
