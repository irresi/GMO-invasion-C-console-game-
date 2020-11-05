#define KnightX 41
#define KnightY 33
void gotoxy(int x,int y){
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return;
}
void print(int CSZ,char str[], int c, int r){ //폰트 사이즈, 출력 문자, 출력할 위치 x, y
    int i,j,a,b;
    char pr;
    while(pr=toupper(*str)){
        str++;
        for(i=0;i<10;i++){
            for(a=0;a<CSZ;a++){ //폰트 사이즈 만큼 행 크기 배로 늘리기
                gotoxy(c,r+i*CSZ+a); //
                for(j=0;ASCII[pr][i][j];){
                    for(b=0;b<CSZ;b++){ //폰트 사이즈 만큼 열 크기 배로 늘리기
                        if(ASCII[pr][i][j]==' ') { //만약 공백이라면 하나 출력
                            printf("%c",ASCII[pr][i][j]);
                        }
                        else{ //공백이 아니라면 2바이트니까 2개 출력
                            printf("%c%c",ASCII[pr][i][j],ASCII[pr][i][j+1]);
                        }
                    }
                    j+=(ASCII[pr][i][j]!=' ')+1; //공백이면 +1, 네모면 +2
                }
            }
        }
        //커서 이동 해야 함
        gotoxy(c+=12*CSZ+1,r);
    }
    return;
}

void FilePrint(FILE *F, int x, int y){
    gotoxy(x,y);
    char ch;
    while(fscanf(F,"%c",&ch)!=EOF){
        if(ch=='\n') gotoxy(x,y+=1);
        else printf("%c",ch);
    }
    return;
}
void PrintKnight(int X, int Y){
    int i;
    extern char StrKnight[KnightY+1][KnightX+1];
    for(i=0;i<KnightY-2;i++){
        gotoxy(X,Y++);
        puts(StrKnight[i]);
    }
    return;
}
