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
#define ARROW_LEFT   75      // ��������Ű
#define ARROW_RIGHT  77      // ��������Ű
#define ARROW_UP     72      // ���ʹ���Ű
#define ARROW_DOWN   80      // �Ʒ�����Ű

#define KnightX 41 //41
#define KnightY 33
#define KnightX2 70
#define KnightY2 33
#define SwordX 30
#define SwordY 3
#define dl 40 //��ǻ�� ��翡 ���� ����
char StrKnight[4][KnightY+1][KnightX2+1];
char ASCII[256][10][20],chTemp[1003];
int eventnum,StageNum=0,attack,Villageflag,PlayerAlive,StageClear,MonNum,downflag,fly,prevx,prevy;
int StageMon[50][50],StageMonSize[50],MonList[50],Mon,bsp,chf; //i�� stage�� �� �� �ִ� ���� ��ȣ�� ����
char map[MAXY+50][REALX+2];
int mapnum,prevpr,money;
//mapnum, ������ ����� ����
clock_t MonSum; //���Ͱ� ��ȯ�� �ð�
clock_t PlayerMoved; //�÷��̾ ���������� ������ �ð�
clock_t LastHit; //�÷��̾ �������� ���� �ð�
void init(); //ȭ�� ������ �� ���� ó�� �ʱ�ȭ
void MonInfoFill(); //���Ϸκ��� MonInfo�� ä���.
void StageMonFill(); //�������� ���� ���� �� �ִ� ���Ͱ� ����ִ� �迭�� �����.
void AFILL(); //�ƽ�Ű �ڵ� ��Ʈ �����
void gotoxy(int x,int y); //Ŀ�� (x,y)�� �̵�
void print(int CSZ,char str[], int c, int r); //���ڿ� ���
void FilePrint(FILE *F, int x, int y); //���� ���
void Knightstr(); //���Ϸ� ���� knight �� Strknight�� ����
void Mainpage(); //ó�� ȭ��
void EraseMonsters(); //��� ���͸� �����.(�̹�����)
void Erase(int X, int Y, int eX, int EY); //���� ���簢���� ���� �� x,y��ǥ , ���� ����, ���� ����
void ErasePlayer(int X, int Y, int T); //T���� �ִ� ���ڿ� ���� �ܼ��� �����.
void check_key(); //Ű���� Ȯ�� �� ���ΰ� �̵�, ����
void shopfunc(); //���� �α� ����
void bankfunc(); //���� �α� ����
void make_floor(); //�� �ٴ� �����
void Infoprint(int num); //�÷��̾��� ���� ���� �ֿܼ� ����Ѵ�.
int Check_lv();//�÷��̾��� ������
void towerfunc(); //ž ������ �̵�
int MonCanMove(int num, int mx, int my); //num�� ���Ͱ� mx my��ŭ ������ �� �ִ��� ��ȯ
void PrintKnight(int X, int Y, int t); //knight.txt ���Ϸ� ���� �о� ����ϴ� �� ���� �̸� ���� ���ڿ��� ����ϴ� ���� �� ���� ���� X,Y��ǥ�� knight���
void Summon(); //���͸� ��ȯ
void MonsterGen(); //���������� �´� ���͸� ��ȯ
void MapSummon(); //���������� ���� �׸���.
void MapGen(); //ž �� ���������� ���� ����
int PlayerCanMove(int X, int Y); //knight(�÷��̾�)�� (X,Y)�� �̵� �� �� �ִ� �� ���� ��ȯ
void PlayerUpdate(); //�÷��̾��� ��ġ�� ������Ʈ
void wait(int num); //for ���� num�� ����(1ms �̸��� �ð� ����)
void DivideCon(); //�÷��� â�� ���� �� �ܼ� â�� ������ ��
void ConsolePrint(int line, char *str, int num); //line��° �ٿ� str�� ����ϰ� num/1000�� ��ŭ �����̸� ��
void Village(); //���� ȭ��
int MonsterMeetPlayer();

struct ALIVE  //�÷��̾�� ������ �⺻���� ������ �����Ѵ�.
{
    char name[20]; //�̸�
    int ATK,DEF,lv,EXP,look,HP; //����, ���(�ִ� ü��), ����, ����ġ, ���� �ִ� ����, ���� ü��
    int curX,curY,MOVE[2],MaxX,MaxY; //���� x��ǥ, y��ǥ, ���� �ð� ���� �����̴� x��ǥ�� ��, �÷��̾ ���͸� ��Ÿ���� ������ �ִ� ũ��
} Player,MonInfo[50];
struct Monster
{
    int ATK,DEF,EXP,MOVE[2],look,up,curX,curY,MaxX,MaxY,num;
    FILE *A,*B;
    ///����,���,����ġ,�̵�,���� ���� -1,1, ���̴� ���, ���� x,y��ǥ, �ؽ�Ʈ�� x,y��ǥ, ���Ͱ� �� ��° ����;
} Monster[10];
struct MapGen
{
    int X[10], Y[10],len[10]; //���� �ٰ� ��ġ�ϴ� x��ǥ, y��ǥ, ���� ���� ����
} MAP[20];
struct Weapon  //������ ���ݷ�, ����
{
    int ATK,DEF; //���ݷ�, ����
} NOW, GET;
//PlayInfo
int died, moneyspent, maxatk, maxdef, maxstage,monsterdied;
clock_t playtime,up;

int main()
{
    int dwID;
    MCI_OPEN_PARMS mciOpen;   // MCI_OPEN_PARAMS ����ü ����
    mciOpen.lpstrDeviceType = "mpegvideo";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
    mciOpen.lpstrElementName = "music.mp3"; // �����̸�
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE|MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

    // ���
    MCI_PLAY_PARMS mciPlay;
    dwID= mciOpen.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
    //MCI_NOTIFY : �⺻, MCI_DGV_PLAY_REPEAT : �ݺ�


    playtime=clock();
    char ch;
replay: //�ٽ� �÷��� �� ��
    init(); //�⺻���� ���� �� �� ȭ���� �ʱⰪ ����
    AFILL(); //��� ��Ʈ ����� font.h�� ���� ���� include ����
    // print(1,"I AM GROOT",10,0);
    Mainpage(); //�ʱ� ȭ��(Press any key to continue)�� �̵�
    Village(); //������ �̵�(3���� �ǹ� �߿� �����ϴ� ȭ��)
    while(kbhit())
        ch=getch(); //������ ���� �ʱ�ȭ�� ������ �Է� ���� Ű �� ����
    FILE *F=fopen("plusstat.txt","r"); //�ٽ� �¾�� ���� ���ؼ� �÷��̾��� ���� ���� ������ �о��
    int a,b;
    fscanf(F,"%d %d",&a,&b); //���� ���ݷ�, ������ �Է� ����
    fclose(F);
    FILE *W=fopen("plusstat.txt","w"); //������ ����� ���� ���� ��ȯ
    fprintf(W,"%d %d %d",a+(Player.ATK-a)/10,b+(Player.DEF-b)/10,money); //�÷��̾��� ���ݷ� ������ 10%�� �÷��̾��� ���� ��������
    fclose(W);
    goto replay;
    system("pause>null");
    return 0;
}
void init()
{
    //�������� �ʱ�ȭ
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
    //���� ������ �� �¾ �÷��̾� ������ �ֱ�
    FILE *F=fopen("plusstat.txt","r");
    fscanf(F,"%d %d %d",&Player.ATK,&Player.DEF,&money);
    Player.HP=Player.DEF;
    //�ܼ� ũ�� ����
    sprintf(chTemp,"mode con cols=%d lines=%d",MAXX,MAXY);
    system(chTemp);
    //���� ����� ���� ������ �̸� �о�� ���ڿ��� �־����
    Knightstr();
    //���������� ������ ���� ��ȣ�� �־����
    StageMonFill();
    //���� ������ ä��
    MonInfoFill();
    srand( (unsigned)time(NULL) ); //���� ����
    //Ŀ�� �� ���̰�
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    fclose(F);
    return;
}
void MonInfoFill()  //���� ������ ����
{
    int i=1,x,y;
    char ch;
    FILE *F=fopen("monsterinfo.txt","r");
    //,&MonInfo[i].MaxY,&MONInfo[i].MaxX
    while(fscanf(F,"%d %d %d %d %d",&MonInfo[i].ATK,&MonInfo[i].DEF,&MonInfo[i].EXP,&MonInfo[i].MOVE[0],&MonInfo[i].MOVE[1])!=EOF)
        i++;
    for(i=1; i<=20; i++) //monster�� MaxX�� MaxY
    {
        sprintf(chTemp,"monster%d-up.txt",i); //���Ͱ� ����� �޶����� ���� ǥ���Ϸ��� �� ���� ������ �ʿ��� up�� down ������ �ݺ��ؼ� ������
        FILE *A=fopen(chTemp,"r");
        sprintf(chTemp,"monster%d-down.txt",i);
        FILE *B=fopen(chTemp,"r");
        //���� ������ ��� ���� ũ�⸦ �־� ����
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
void StageMonFill()  //���� ������ ����
{
    //���Ͽ��� 3�� ���Ͱ� ���� �� �ִ� ���������� ���Ѱ� ������ ����
    //�� �Լ������� 1�� ���������� �� �� ���� ���� ���� �� �ִ��� i��° ������������ ���� �� �ִ� ���͵��� StageMon[i]�� ����
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
void PrintKnight(int X, int Y, int t)  //knight�� ���� �������� ��� ������ ���ڿ��� ���� ���� ���
{
    int i;
    for(i=0; i<KnightY-2; i++)
    {
        gotoxy(X,Y++);
        puts(StrKnight[t][i]); //goto�� �ϳ��ϳ� ����ϸ� ����� �ʹ� ���� �ɷ��� puts���
    }
    return;
}

void Knightstr()
{
    char ch;
    int x=0,y=0;
    //���� ���� ���� �ִ� ����Ʈ
    FILE* Knight=fopen("knight.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[0][y][x++]=ch;
    }
    y=0;
    //������ ���� �ִ� ����Ʈ
    Knight=fopen("knight_reverse.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[1][y][x++]=ch;
    }
    y=0;
    //���������� ������ �ϴ� ����Ʈ
    Knight=fopen("knight2.txt","r");
    while(fscanf(Knight,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            y+=1,x=0;
        else
            StrKnight[2][y][x++]=ch;
    }
    y=0;
    //�������� ������ �ϴ� ����Ʈ
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
    print(2,"GMO invasion",270,10); //���� ���
    print(2,"------------",270,33);
    Sleep(100);
    print(1,"MOVE:WASD KEYS",270,50);
    print(1,"SELECT AND",270,75);
    print(1,"ATTACK:SPACE BAR",270,90);
    while(!kbhit())  //Ű�� �ԷµǸ� ������ ����
    {
        print(1,"PRESS ANY KEY TO CONTINUE",10,130);
        Sleep(250);
        print(1,"                         ",10,130);
        Sleep(250);
    }
    while(kbhit())
        getch(); //���� �� ������ ���� �����ϱ� �Էµ� Ű ����
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
/*void ErasePlayer(int X, int Y, int T){ //�̵��� ���� x,y ��ǥ �̹����� x, y��ǥ ������ x��ǥ, ������ y��ǥ
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
void EraseMonsters()   //�������� ���� ���� �����
{
    int i;
    for(i=0; i<MonNum; i++)
    {
        Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY);
    }
    return;
}
void Erase(int X, int Y, int eX, int EY)  //�̵��� ���� x,y ��ǥ �̹����� x, y��ǥ ������ x��ǥ, ������ y��ǥ
{
    gotoxy(X,Y);
    int i;
    for(i=0; i<eX; i++)
        chTemp[i]=' '; //chTemp�� �־� ���Ҵٰ�
    chTemp[eX]=0;
    for(i=0; i<EY; i++)
    {
        puts(chTemp); //printf���� ���� puts�� �����
        gotoxy(X,Y+i);
    }
    return;
}
void shopfunc()  //���� ����
{
    system("cls");
    DivideCon();
    int r=0,c=0,flag=1,num=0,i;
    int ln=25,po[5]= {1,4,16,64,256};
    int inf[5][2]= {{9,4},{99,44},{999,444},{9999,4444},{99999,44444}}; //����, �� ����
    //����, �� ���� ���
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
    //���� ����, �� ���
    Infoprint(6);
    Infoprint(7);
    Infoprint(8);
    //����, �� ����
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
                // 1 + (n=10000, p=po[r]/10000�� ���� ����)
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
                //�� ���� ����
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
void make_floor()  //�ٴ� �����
{
    int i,j;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 8);
    for(i=0; i<20; i++)
    {
        gotoxy(0,130+i);
        for(j=0; j<200; j++)
        {
            printf("��");
            map[130+i][j*2]=map[130+i][j*2+1]=1; //�� �� ����� 1�� ǥ��
        }
    }
    for(i=0; i<=130; i++)
    {
        gotoxy(0,i); //���� ��
        map[i][0]=map[i][1]=map[i][2]=map[i][3]=map[i][397]=map[i][398]=map[i][399]=map[i][400]=1; //�� �� ����� 1�� ǥ��
        printf("��");
        gotoxy(398,i); //������ ��
        printf("��");
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
    return;
    //memset(map[131],0,sizeof(map[131])); //�÷��̾�� �� ������ �Ÿ��� ���̱� ����
}
void Infoprint(int num)
{
    /*
    1  : �������� ��ȣ
    2  : ����
    3  : ���ݷ�
    4  : ü��
    5  : ����ġ
    6 : ���� ���ݷ�
    7  : �� ü��
    8 : ���� ���� ���ݷ�
    9 : ���� �� ü��
    10 : �ٲ� ����
    �� ���� ������ ���
    */
    int i;
    for(i=0; i<14; i++)
        chTemp[i]=0; //�����ϰ� �ʱ�ȭ
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
int Check_lv()  //�÷��̾��� ������ üũ�ϰ� ����ġ�� Player�� ���� *30 �̻��̶�� ���� ��
{
    if(Player.EXP>=Player.lv*30)
    {
        Player.EXP-=Player.lv*30;
        int num=rand()%(5+Player.lv); //trpg �帣�� �ٽ��� ������, ���°� ���ݷ��� �������� ����, ���� �� �غ��鼭 ���ݷ°� ���� ����ġ�� ���� ������
        Player.DEF+=num,Player.ATK+=(5+Player.lv)-num; //���ݷ� ���� up
        Player.lv++; //���� ��
        Player.HP=Player.DEF; //���� ü���� �ִ� ü������ ȸ��
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
        Infoprint(2); //lv ����
        Infoprint(3); //���ݷ� ����
        Infoprint(4); //ü�� ����
        Infoprint(5); //����ġ ����
        Sleep(1000);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
        Infoprint(2); //lv ����
        Infoprint(3); //���ݷ� ����
        Infoprint(4); //ü�� ����
        Infoprint(5); //����ġ ����
        return 1; //�� ���� 2lv �̻��� ���� �� ������ �� �� �� üũ
    }
    return 0; //���� �� �� ������ üũ �� �ʿ� ����
}
void BOSS() //������ ���´�.
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
    //������ 20���� ���ͷ� ����
    bsp=20;
    while(PlayerAlive && Monster[0].num>0)
    {
        PlayerUpdate();
        if(clock()-up>250)   //0.25�ʸ��� ���� ������ üũ
        {
            if(MonsterMeetPlayer(up))  //���Ͱ� �÷��̾ �����ϴ� �Լ�, ���Ͱ� �÷��̾ �׿��ٸ� 1�� ��ȯ
            {
                PlayerAlive=0; //�÷��̾�� �׾���
                break;
            }
            Summon(); //���͸� ��ȯ�ϱ�
            up=clock(); //�ٽ� up�� ���� �ð�����
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
    system("cls"); //�� �����
    DivideCon(); //�ְܼ� ������ ��� ������
    int i,j,t;
    clock_t up=clock(); //���� �ð��� ����
    make_floor(); //�ٴ� �����
    PlayerAlive=1; //�÷��̾ ��� ����
    while(kbhit())
        getch(); //�� ���̿� �Էµ� ���� ������
    for(i=1; i<=7; i++) //�⺻ ���� ����ϱ�
    {
        Infoprint(i);
    }
    while(PlayerAlive && StageNum<=40)  //�÷��̾ ��� �ִٸ�
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 1);
        Infoprint(1); //���������� ���
        Sleep(1000);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
        Infoprint(1);
        Player.look=1; //�÷��̾�� �������� ���� ����
        PrintKnight(Player.curX=10,Player.curY=100-KnightY,0); //knight�� ���
        MapGen(); //map�����
        MonsterGen(); //���� ���� ������ �����
        while(5<Player.curX && Player.curX<340)
        {
            PlayerUpdate(); //����ڰ� Ű�� �����ٸ� �÷��̾ �̵��ϰ� ��
            if(clock()-up>100)   //0.1�ʸ��� ���� ������ üũ
            {
                if(MonsterMeetPlayer(up))  //���Ͱ� �÷��̾ �����ϴ� �Լ�, ���Ͱ� �÷��̾ �׿��ٸ� 1�� ��ȯ
                {
                    PlayerAlive=0; //�÷��̾�� �׾���
                    break;
                }
                Summon(); //���͸� ��ȯ�ϱ�
                up=clock(); //�ٽ� up�� ���� �ð�����
            }
        }
        if(Player.curX>=340)  //�������� Ŭ����
        {
            EraseMonsters(); //���� ���͸� ��� �����
            t=1; //�÷��̾ ��� ���͸� �׿��� Ȯ��
            for(i=0; i<MonNum; i++)
                if(Monster[i].num!=-1)
                    t=0;
            if(t)  //��� ���Ͱ� -1�̸� (��� �׾����� )
            {
                Player.EXP+=++StageNum*3; //�������� *3 �� �ش��ϴ� ����ġ ���ʽ��� ����
                Check_lv(); //���� ��?
                Infoprint(5); //EXP ���� ����
            }
            else
                StageNum++;
        }
        else  //�÷��̾ �ڷ� ��
        {
            EraseMonsters(); //���͸� �� �����
            if(StageNum)
                --StageNum; //�� ���������� �̵�
        }
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //�÷��̾� �����
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
    print(4,"You Died",108,51); //�� �׾���
    Sleep(1000);
    print(4,"        ",108,51);
    print(4,"You Died",108,51);
    Sleep(2000);
    //����, �� ���ݷ� �缳��
    Player.ATK-=NOW.ATK;
    Player.DEF-=NOW.DEF;
    NOW.ATK=NOW.DEF=0;
    return;
}
int MonCanMove(int num, int mx, int my)  //�����¿�θ� �̵��� Ȯ�� ���� (���� �ð��� ���̱� ����)
{
    int si,ei,sj,ej,i,j;
    //���� y��ǥ,�� y��ǥ,���� x��ǥ,�� x��ǥ
    //���Ͱ� ���� �̵��� �� �ִ��� Ȯ�� �ϴ� �Լ��ε�
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
int MonsterMeetPlayer()  //���Ͱ� �÷��̾ �����ϴ� ����� �ϴ� �Լ�
{
    int i,flag=0;
    for(i=0; i<MonNum; i++)
    {
        //���Ͱ� �����ٸ�
        flag=0;
        flag|=Player.curX<=Monster[i].curX && Monster[i].curX<=Player.curX+Player.MaxX-10;
        flag|=Player.curX<=Monster[i].curX+Monster[i].MaxX && Monster[i].curX+Monster[i].MaxX<=Player.curX+Player.MaxX-5;
        flag|=(Player.curY<=Monster[i].curY && Monster[i].curY<=Player.curY+Player.MaxY-5)<<1;
        flag|=(Player.curY<=Monster[i].curY+Monster[i].MaxY && Monster[i].curY+Monster[i].MaxY<=Player.curY+Player.MaxY-5)<<1;
        if(flag==3 && Monster[i].num>0)
        {
            Player.HP-=Monster[i].ATK; //������ ���ݷ� ��ŭ �÷��̾��� ���� ü�� ����
            Infoprint(4); //ü�� ���� ����
            if(Player.HP<=0)
                return 1; //�÷��̾ ������ 1 ��ȯ
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 4);
            ConsolePrint(8,"HP down",500);
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
            chf=1;
        }
    }
    return 0;
}
void Summon()  //���� ����
{
    int i,num;
    FILE *F;
    for(i=0; i<MonNum; i++)
        if(Monster[i].num>0)  //���Ͱ� ������ ���ڸ� -1�� ��� �ִ� ���͸� ����
        {
            if((clock()-MonSum)%3000<1500)
                F=Monster[i].A; //1.5�ʸ��� ���� ��� ������ �ٲ�
            else
                F=Monster[i].B;
            while(MonCanMove(i,0,2))  //���Ͱ� ������ ���� �� �� �ִٸ� ���� ����(���߿��� �� �ٴ��� �ʰ�)
            {
                fseek(F,0,SEEK_SET);
                Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1); //+1+1
                FilePrint(F,Monster[i].curX,Monster[i].curY+=2);
            }
            fseek(F,0,SEEK_SET); //���� ������ �ٽ� ������
            //1�ʸ��� ���Ͱ� �����̴� ���� �ٸ� ���� ��� move[0]=-5,move[1]=10 �̸� �ڷ� ���ٰ� ���ڱ� ������ �����̴� ����
            //move[0]=0,move[1]=10 ����ٰ� ������ �̵�, move[0]=3,move[1]=3 ���� �ӵ��� ������ �̵�
            if((clock()-MonSum)%2000<1000)
            {
                if(MonCanMove(i,Monster[i].MOVE[0]*Monster[i].look,0))  //���Ͱ� ������ �� �ִٸ� �����̱�
                {
                    Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1);
                    FilePrint(F,Monster[i].curX+=Monster[i].MOVE[0]*Monster[i].look,Monster[i].curY);
                }
                else
                    Monster[i].look=-Monster[i].look; //���Ͱ� ���� ������ �� �� ���ٸ� �ݴ� �������� �����̰� �ٲٱ�
            }
            else
            {
                if(MonCanMove(i,Monster[i].MOVE[1]*Monster[i].look,0))  //���Ͱ� ������ �� �ִٸ� �����̱�
                {
                    Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1);
                    FilePrint(F,Monster[i].curX+=Monster[i].MOVE[1]*Monster[i].look,Monster[i].curY);
                }
                else
                    Monster[i].look=-Monster[i].look; //���Ͱ� ���� ������ �� �� ���ٸ� �ݴ� �������� �����̰� �ٲٱ�
            }
        }

    return;
}
void MonsterGen()  //���� �����
{
    MonNum=rand()%3+2; //���������� ���ʹ� 2~4����
    int i,temp;
    //StageNum
    ///debug
    for(i=0; i<MonNum; i++)
    {
        //���� ���� ����, monsterinfo�� ���� �� �Ǵµ� ü��, ��ġ ���� ������ �ٲ�� ���� ���� �ؾ� ��
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
        //���� ���ʿ� �ִٸ� ���� ������ �� �ִ� �������� ����(��� ������ �� ���� ���̸� ������ �ݴ�� �ٲ㼭 ���� ��� ������ Ȥ�� �� ���ܿ� �����)
        if(Monster[i].curX>300)
            Monster[i].look=-1;
        else if(Monster[i].curX<100)
            Monster[i].look=1;
        else
            Monster[i].look=(rand()&1)?1:-1;
    }
    MonSum=clock(); //���Ͱ� ������ �ð�
    return;
}
void MapSummon()  //�����ϴ� �� �����
{
    int EX,EY,ELEN,i;
    //���� �ڵ����� ��������� �ʹ� �Ⱬ�� ����� ���� ���ͼ� �̸� 20���� ���� ����� �� �� �ϳ��� ��������
    //TRPG �帣�� ��ŭ �ʿ� ���� ���� ����� ���̵��� ���� �ٸ�
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 8);
    sprintf(chTemp,"map%d.txt\0",mapnum);
    FILE *B=fopen(chTemp,"r");
    while(fscanf(B,"%d %d %d",&EX,&EY,&ELEN)!=EOF)
    {
        gotoxy(EX,EY);
        for(i=0; i<ELEN; i++)
        {
            printf("��");
            map[EY][EX+i*2]=map[EY][EX+i*2+1]=1; //2����Ʈ �ϱ� 1(��)�� 2���� ����
        }
        gotoxy(EX,EY+=1);
        for(i=0; i<ELEN; i++)
        {
            printf("��");
            map[EY][EX+i*2]=map[EY][EX+i*2+1]=1;
        }
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7);
    fclose(B);
    return;
}
void MapGen()  //�� ���������� ���� ����� �� �� ���� ���� ��
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
    mapnum=rand()%20; //�� �� �� �ұ�
    //ConsolePrint(2,chTemp);
    MapSummon(); //�� ���, �� ���� ����
    fclose(A);
    return;
}

int PlayerCanMove(int X, int Y)  //�÷��̾ (X,Y)��ǥ�� ������ �� �ֈd �� Ȯ��
{
    int i,j;
    for(i=Y-2; i<Y+KnightY-2; i++)
    {
        for(j=X; j<X+KnightX; j++)
        {
            if(map[i][j])
                return 0; //���� �־ �������̸� 0 ��ȯ
        }
    }
    return 1; //�� ������ 1 ��ȯ
}
void print(int CSZ,char str[], int c, int r)  //��Ʈ ������, ��� ����, ����� ��ġ x, y
{
    int i,j,a,b;
    char pr;
    while(pr=toupper(*str))  //Ȥ�� �ҹ��ڷ� ����ϰ� ���� ���� �����ϱ� �빮�ڷ�(��Ʈ�� �빮�ڸ� ����)
    {
        str++;
        for(i=0; i<10; i++)
        {
            for(a=0; a<CSZ; a++) //��Ʈ ������ ��ŭ �� ũ�� ��� �ø���
            {
                gotoxy(c,r+i*CSZ+a); //
                for(j=0; ASCII[pr][i][j];)
                {
                    for(b=0; b<CSZ; b++) //��Ʈ ������ ��ŭ �� ũ�� ��� �ø���
                    {
                        if(ASCII[pr][i][j]==' ')   //���� �����̶�� �ϳ� ���
                        {
                            printf("%c",ASCII[pr][i][j]);
                        }
                        else  //������ �ƴ϶�� ������ 2����Ʈ�ϱ� 2�� ���
                        {
                            printf("%c%c",ASCII[pr][i][j],ASCII[pr][i][j+1]);
                        }
                    }
                    j+=(ASCII[pr][i][j]!=' ')+1; //�����̸� +1, �׸�� +2
                }
            }
        }
        //Ŀ�� �̵� �ؾ� ��
        gotoxy(c+=12*CSZ+1,r); //��Ʈ�� CSZ��� ��� �Ǵ� �⺻ ��Ʈ�� ���� �ϴ� ĭ�� 12ĭ�ε� CSZ�� ��ŭ �̵�, ���ڰ� ���� �پ �˾ƺ��� ���� �ڰ��� 1ĭ���� ����
    }
    return;
}

void FilePrint(FILE *F, int x, int y)  //(x,y)�� ���� F�� ����ϱ�
{
    gotoxy(x,y);
    char ch;
    while(fscanf(F,"%c",&ch)!=EOF)
    {
        if(ch=='\n')
            gotoxy(x,y+=1); //�ٹٱ�
        else
            printf("%c",ch); //���
    }
    return;
    fclose(F);
}
void PlayerUpdate()  //�÷��̾��� ��ǥ ������ �� ���� ó��
{
    int i;
    if(GetAsyncKeyState(' ') & 0x8000 && clock()-LastHit>300)  //���������� ������ �� 0.5 �ʰ� ������ �� ������ �����ٸ�
    {
        if(Villageflag==1)  //���� ���� ȭ�鿡 village�� �־��ٸ�
        {
            if(0<=Player.curX && Player.curX<=100)
                Villageflag=2; //Shop
            else if(101<=Player.curX && Player.curX<=230)
                Villageflag=3; //Bank
            else if(231<=Player.curX && Player.curX<=400)
                Villageflag=4; //Tower
            return;
        }
        downflag=1; //������ �� �ִ�.
        int i,j,k;
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //�켱 �÷��̾ �����.
        //�׸��� Į�� ���� �÷��̾ ����Ѵ�.
        if(Player.look==1)
            PrintKnight(Player.curX,Player.curY,2);
        else
            PrintKnight(Player.curX,Player.curY,3);
        if(Player.look==1)  //�������� ���� �ִٸ�
        {
            //���� �÷��̾ ���� �����ٸ� ������ �� ����
            for(i=Player.curY+15; i<=Player.curY+15+SwordY; i++)
            {
                for(j=Player.curX+KnightX; j<=Player.curX+KnightX+SwordX; j++)
                {
                    if(map[i][j])
                        return;
                }
            }
            //�÷��̾��� �� ��ġ�� Į�� ����Ѵ�.
            FILE *F=fopen("sword.txt","r");
            FilePrint(F,Player.curX+KnightX,Player.curY+15);
            //0.25�� ��ٸ���.
            Sleep(250);
            //���͸� �����ߴ����� Ȯ���Ѵ�.
            for(i=0; i<MonNum; i++)
            {
                //���� �÷��̾ ���͸� �����ߴٸ�(Į�� ���Ͱ� ������, ��ǥ�� �̿��Ͽ� ����)
                if(Player.curX<=Monster[i].curX && Monster[i].curX<=Player.curX+KnightX+SwordX && (Player.curY<=Monster[i].curY+Monster[i].MaxY && Player.curY+KnightY>=Monster[i].curY+15))
                {
                    Monster[i].DEF-=Player.ATK; //������ ü���� �÷��̾��� ���ݷ¸�ŭ ����
                    if(Monster[i].DEF<=0 && Monster[i].num>0)   //������ ü���� 0�����̰� ���Ͱ� ����ִٸ�
                    {
                        monsterdied++;
                        money+=Monster[i].num*((int)sqrt(Monster[i].num))*(rand()%3); //���� ���� ��ȣ^1.5 * 0~2�� ��ŭ ����
                        Player.EXP+=Monster[i].EXP; //�÷��̾��� ����ġ ����
                        Monster[i].num=-1;//���� ����
                        Erase(Monster[i].curX,Monster[i].curY,Monster[i].MaxX,Monster[i].MaxY+1); //���� �����
                        Check_lv(); //���� Ȯ��
                        Infoprint(5); //����ġ ����
                    }
                    Monster[i].look=-Player.look; //������ �޾Ҵٸ� ������ �ٲ� �÷��̾ ���� �ٰ���
                }
            }
            Erase(Player.curX+KnightX,Player.curY+15,SwordX,SwordY+1); //Į �����
            PrintKnight(Player.curX,Player.curY,0); //Į�� ��� �ִ� �÷��̾� ���
            fclose(F); //���� �ݱ�
        }
        else //������ ���� �ִٸ�, (�������� ���� �ִٸ鿡���� ���� �� �Ȱ���)
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
            FilePrint(F,Player.curX-SwordX,Player.curY+15); //sword����
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
    //windows.h�� ���ǵǾ� �ִ� �Լ��� ��ü Ű�� �ƴ� �ϳ��� Ű�� ���ȴ°� ���� Ȯ���ؼ� kbhit���� ���� �ӵ��� ������.
    //Ű�� ���α׷� ���� �� ó�� �����ٸ� 0x8000�� ��ȯ �� ��° ������ �����ʹ� 0x8001 ��ȯ
    while(downflag==1 && PlayerCanMove(Player.curX,Player.curY+2))  //���� ������ �� �ִٸ�
    {
        Erase(Player.curX-prevx,Player.curY-1,KnightX+1,KnightY); //�� ��ġ�� �ִ� �÷��̾ ������
        if((GetAsyncKeyState('A') & 0x8000) && PlayerCanMove(Player.curX-2,Player.curY))
            Player.curX-=2,prevx=-2,Player.look=-1; //�������鼭 ���� Ű�� �����ٸ�
        if((GetAsyncKeyState('D') & 0x8000) && PlayerCanMove(Player.curX+2,Player.curY))
            Player.curX+=2,prevx=2,Player.look=1; //������ Ű�� �����ٸ�
        //�� �ʿ� ���
        if(Player.look==1)
            PrintKnight(Player.curX,Player.curY+=2,0);
        else
            PrintKnight(Player.curX,Player.curY+=2,1);
        Sleep(1); //�ӵ� ����
        if(Player.curX>=340)
            return; //��ǥ�� 340 �̻��̸� �������� Ŭ����
    }
    downflag=0; //�� ������ �� ����
    if(GetAsyncKeyState('W') & 0x8000)  //����
    {
        if(fly>15+bsp)  //���� 15�� �̻� ����������
        {
            downflag=1; //�������� ��
            fly=0; //�� ����
            return; //��
        }
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //�÷��̾� �����
        //�÷��̾��� x��ǥ �ٲٱ�, ���� ���� ����� prevx �ٲٱ� �ٶ� ���� ���� �ٲٱ�
        if((GetAsyncKeyState('A') & 0x8000) && PlayerCanMove(Player.curX-2,Player.curY))
            Player.curX-=2,prevx=-2,Player.look=-1;
        if((GetAsyncKeyState('D') & 0x8000) && PlayerCanMove(Player.curX+2,Player.curY))
            Player.curX+=2,prevx=2,Player.look=1;
        if(PlayerCanMove(Player.curX,Player.curY-2))
            Player.curY-=2; //����
        if(Player.look==1)
            PrintKnight(Player.curX,Player.curY,0); //�ٶ� ���� ���⿡ ���� ���
        else
            PrintKnight(Player.curX,Player.curY,1);
        Sleep(5);
        fly++; //�� �� ������
        return;
    }
    if((GetAsyncKeyState('A') & 0x8000) && PlayerCanMove(Player.curX-2,Player.curY))   //���� �������� �� �� �ְ� A�� �����ٸ�
    {
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //�����
        PrintKnight(Player.curX-=2,Player.curY,1); //�̵�
        Sleep(1);
        downflag=1; //���� �� �� ����
        Player.look=-1; //���� �ٶ�
        return;
    }
    if((GetAsyncKeyState('D') & 0x8000) && PlayerCanMove(Player.curX+2,Player.curY))  //���� D�� ������ ���������� �� �� �ִٸ�
    {
        Erase(Player.curX,Player.curY,KnightX,KnightY-1); //�����
        PrintKnight(Player.curX+=2,Player.curY,0); //�̵�
        Sleep(1);
        downflag=1; //������ �� ����
        Player.look=1; //������ �ٶ�
        return;
    }
    Sleep(dl);
    //�ƹ��͵� �� ������ ������
    downflag=1; //������ �� ����
    return;
}
/*void SwordUpdate(){
    if(clock()-ATTACK<300)
}*/
void wait(int num)  //1ms �̸��� delay
{
    int i;
    for(i=0; i<num; i++);
    return;
}
void DivideCon()  //�ܼ� â �и�
{
    for(int y=0; y<MAXY; y++)
    {
        gotoxy(399,y);
        printf("|");
    }
    print(1,"CONSOLE",420,3);
    print(1,"--------------",400,15); //console log�� 16���� ����
    return;
}
void ConsolePrint(int line, char *str,int num)  //14�ڸ� ���� ����, 10�ٱ��� ����
{
    //������ �ֿܼ� ����Ʈ �ϵ��� ���� �Լ�
    //��, ���ڿ�, num�� ���� ���� �� �����, 0 �̸� ��� ���� �ִ� ��
    int i;
    print(1,str,410,5+line*15);
    if(num)
    {
        Sleep(num); //���߰�
        print(1,"              ",410,5+line*15); //14�� �����
    }
    return;
}
void Village()
{
    FILE *Bank=fopen("bank.txt", "r"), *Tower=fopen("tower.txt", "r"), *Shop=fopen("shop.txt","r"),*Knight=fopen("knight.txt","r");
    system("cls");
    //�÷��̾� ��ǥ ����
    Player.curX=100,Player.curY=130-47;
    //��� ����Ʈ
    FilePrint(Shop,5,80-54);
    FilePrint(Bank,130,80-50);
    FilePrint(Tower,260,80-80);
    DivideCon();
    make_floor();
    Villageflag=1;
    while(1)
    {
        PlayerUpdate(); //�÷��̾� ���� ����(��ġ, ����, ü��, ����ġ, ���� ���� ���� �ϴµ� ���⼭�� ��ġ�� ���� ���θ�)
        //���õ� flag�� ���� �ٸ� ������� �̵�
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
    //���� �ݱ�
    fclose(Bank);
    fclose(Tower);
    fclose(Shop);
    fclose(Knight);
    return;
}
