#define KnightX 41
#define KnightY 33
void gotoxy(int x,int y){
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    return;
}
void print(int CSZ,char str[], int c, int r){ //��Ʈ ������, ��� ����, ����� ��ġ x, y
    int i,j,a,b;
    char pr;
    while(pr=toupper(*str)){
        str++;
        for(i=0;i<10;i++){
            for(a=0;a<CSZ;a++){ //��Ʈ ������ ��ŭ �� ũ�� ��� �ø���
                gotoxy(c,r+i*CSZ+a); //
                for(j=0;ASCII[pr][i][j];){
                    for(b=0;b<CSZ;b++){ //��Ʈ ������ ��ŭ �� ũ�� ��� �ø���
                        if(ASCII[pr][i][j]==' ') { //���� �����̶�� �ϳ� ���
                            printf("%c",ASCII[pr][i][j]);
                        }
                        else{ //������ �ƴ϶�� 2����Ʈ�ϱ� 2�� ���
                            printf("%c%c",ASCII[pr][i][j],ASCII[pr][i][j+1]);
                        }
                    }
                    j+=(ASCII[pr][i][j]!=' ')+1; //�����̸� +1, �׸�� +2
                }
            }
        }
        //Ŀ�� �̵� �ؾ� ��
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
