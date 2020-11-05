extern char ASCII[256][10][20]; //헤더 파일에서 전역변수를 불러옴
void AFILL()
{
    //글꼴 크기를 5로 하여 캐릭터를 표현하기 때문에 문자를 크게 표현하기가 어려움
    //전체적인 게임은 도트 아트 형태

    strcpy(ASCII['$'][1],"     =      ");
    strcpy(ASCII['$'][2],"   =#@##.   ");
    strcpy(ASCII['$'][3],"  @* @ ..   ");
    strcpy(ASCII['$'][4],"  @+ @      ");
    strcpy(ASCII['$'][5],"   *@@+     ");
    strcpy(ASCII['$'][6],"     @=@%   ");
    strcpy(ASCII['$'][7],"     @ :@.  ");
    strcpy(ASCII['$'][8],"  %%#@#%.   ");

    strcpy(ASCII['='][0],"■■■■■■\0");
    strcpy(ASCII['='][1],"■■■■■■\0");
    strcpy(ASCII['='][2],"■■■■■■\0");
    strcpy(ASCII['='][3],"■■■■■■\0");
    strcpy(ASCII['='][4],"■■■■■■\0");
    strcpy(ASCII['='][5],"■■■■■■\0");
    strcpy(ASCII['='][6],"■■■■■■\0");
    strcpy(ASCII['='][7],"■■■■■■\0");
    strcpy(ASCII['='][8],"■■■■■■\0");
    strcpy(ASCII['='][9],"■■■■■■\0");

    strcpy(ASCII['-'][0],"■■■■■■\0");

    strcpy(ASCII[' '][0],"            \0");
    strcpy(ASCII[' '][1],"            \0");
    strcpy(ASCII[' '][2],"            \0");
    strcpy(ASCII[' '][3],"            \0");
    strcpy(ASCII[' '][4],"            \0");
    strcpy(ASCII[' '][5],"            \0");
    strcpy(ASCII[' '][6],"            \0");
    strcpy(ASCII[' '][7],"            \0");
    strcpy(ASCII[' '][8],"            \0");
    strcpy(ASCII[' '][9],"            \0");

    strcpy(ASCII[':'][1],"    ■■  \0");
    strcpy(ASCII[':'][2],"    ■■  \0");
    strcpy(ASCII[':'][7],"    ■■  \0");
    strcpy(ASCII[':'][8],"    ■■  \0");

    strcpy(ASCII['0'][0],"■■■■■■\0");
    strcpy(ASCII['0'][1],"■        ■\0");
    strcpy(ASCII['0'][2],"■        ■\0");
    strcpy(ASCII['0'][3],"■        ■\0");
    strcpy(ASCII['0'][4],"■        ■\0");
    strcpy(ASCII['0'][5],"■        ■\0");
    strcpy(ASCII['0'][6],"■        ■\0");
    strcpy(ASCII['0'][7],"■        ■\0");
    strcpy(ASCII['0'][8],"■        ■\0");
    strcpy(ASCII['0'][9],"■■■■■■\0");

    strcpy(ASCII['1'][0],"    ■      \0");
    strcpy(ASCII['1'][1],"    ■      \0");
    strcpy(ASCII['1'][2],"    ■      \0");
    strcpy(ASCII['1'][3],"    ■      \0");
    strcpy(ASCII['1'][4],"    ■      \0");
    strcpy(ASCII['1'][5],"    ■      \0");
    strcpy(ASCII['1'][6],"    ■      \0");
    strcpy(ASCII['1'][7],"    ■      \0");
    strcpy(ASCII['1'][8],"    ■      \0");
    strcpy(ASCII['1'][9],"    ■      \0");

    strcpy(ASCII['2'][0],"■■■■■■\0");
    strcpy(ASCII['2'][1],"          ■\0");
    strcpy(ASCII['2'][2],"          ■\0");
    strcpy(ASCII['2'][3],"          ■\0");
    strcpy(ASCII['2'][4],"■■■■■■\0");
    strcpy(ASCII['2'][5],"■          \0");
    strcpy(ASCII['2'][6],"■          \0");
    strcpy(ASCII['2'][7],"■          \0");
    strcpy(ASCII['2'][8],"■          \0");
    strcpy(ASCII['2'][9],"■■■■■■\0");


    strcpy(ASCII['3'][0],"■■■■■■\0");
    strcpy(ASCII['3'][1],"          ■\0");
    strcpy(ASCII['3'][2],"          ■\0");
    strcpy(ASCII['3'][3],"          ■\0");
    strcpy(ASCII['3'][4],"■■■■■■\0");
    strcpy(ASCII['3'][5],"          ■\0");
    strcpy(ASCII['3'][6],"          ■\0");
    strcpy(ASCII['3'][7],"          ■\0");
    strcpy(ASCII['3'][8],"          ■\0");
    strcpy(ASCII['3'][9],"■■■■■■\0");

    strcpy(ASCII['4'][0],"■        ■\0");
    strcpy(ASCII['4'][1],"■        ■\0");
    strcpy(ASCII['4'][2],"■        ■\0");
    strcpy(ASCII['4'][3],"■        ■\0");
    strcpy(ASCII['4'][4],"■■■■■■\0");
    strcpy(ASCII['4'][5],"          ■\0");
    strcpy(ASCII['4'][6],"          ■\0");
    strcpy(ASCII['4'][7],"          ■\0");
    strcpy(ASCII['4'][8],"          ■\0");
    strcpy(ASCII['4'][9],"          ■\0");

    strcpy(ASCII['5'][0],"■■■■■■\0");
    strcpy(ASCII['5'][1],"■          \0");
    strcpy(ASCII['5'][2],"■          \0");
    strcpy(ASCII['5'][3],"■          \0");
    strcpy(ASCII['5'][4],"■■■■■■\0");
    strcpy(ASCII['5'][5],"          ■\0");
    strcpy(ASCII['5'][6],"          ■\0");
    strcpy(ASCII['5'][7],"          ■\0");
    strcpy(ASCII['5'][8],"          ■\0");
    strcpy(ASCII['5'][9],"■■■■■■\0");

    strcpy(ASCII['6'][0],"■■■■■■\0");
    strcpy(ASCII['6'][1],"■          \0");
    strcpy(ASCII['6'][2],"■          \0");
    strcpy(ASCII['6'][3],"■          \0");
    strcpy(ASCII['6'][4],"■■■■■■\0");
    strcpy(ASCII['6'][5],"■        ■\0");
    strcpy(ASCII['6'][6],"■        ■\0");
    strcpy(ASCII['6'][7],"■        ■\0");
    strcpy(ASCII['6'][8],"■        ■\0");
    strcpy(ASCII['6'][9],"■■■■■■\0");

    strcpy(ASCII['7'][0],"■■■■■■\0");
    strcpy(ASCII['7'][1],"■        ■\0");
    strcpy(ASCII['7'][2],"■        ■\0");
    strcpy(ASCII['7'][3],"■        ■\0");
    strcpy(ASCII['7'][4],"■        ■\0");
    strcpy(ASCII['7'][5],"          ■\0");
    strcpy(ASCII['7'][6],"          ■\0");
    strcpy(ASCII['7'][7],"          ■\0");
    strcpy(ASCII['7'][8],"          ■\0");
    strcpy(ASCII['7'][9],"          ■\0");

    strcpy(ASCII['8'][0],"■■■■■■\0");
    strcpy(ASCII['8'][1],"■        ■\0");
    strcpy(ASCII['8'][2],"■        ■\0");
    strcpy(ASCII['8'][3],"■        ■\0");
    strcpy(ASCII['8'][4],"■■■■■■\0");
    strcpy(ASCII['8'][5],"■        ■\0");
    strcpy(ASCII['8'][6],"■        ■\0");
    strcpy(ASCII['8'][7],"■        ■\0");
    strcpy(ASCII['8'][8],"■        ■\0");
    strcpy(ASCII['8'][9],"■■■■■■\0");

    strcpy(ASCII['9'][0],"■■■■■■\0");
    strcpy(ASCII['9'][1],"■        ■\0");
    strcpy(ASCII['9'][2],"■        ■\0");
    strcpy(ASCII['9'][3],"■        ■\0");
    strcpy(ASCII['9'][4],"■■■■■■\0");
    strcpy(ASCII['9'][5],"          ■\0");
    strcpy(ASCII['9'][6],"          ■\0");
    strcpy(ASCII['9'][7],"          ■\0");
    strcpy(ASCII['9'][8],"          ■\0");
    strcpy(ASCII['9'][9],"■■■■■■\0");

    strcpy(ASCII['A'][0],"    ■■    \0");
    strcpy(ASCII['A'][1],"  ■    ■  \0");
    strcpy(ASCII['A'][2],"  ■    ■  \0");
    strcpy(ASCII['A'][3],"  ■    ■  \0");
    strcpy(ASCII['A'][4],"  ■■■■  \0");
    strcpy(ASCII['A'][5],"  ■    ■  \0");
    strcpy(ASCII['A'][6],"■■    ■■\0");
    strcpy(ASCII['A'][7],"■        ■\0");
    strcpy(ASCII['A'][8],"■        ■\0");
    strcpy(ASCII['A'][9],"■        ■\0");

    strcpy(ASCII['B'][0],"■■■■    \0");
    strcpy(ASCII['B'][1],"■      ■  \0");
    strcpy(ASCII['B'][2],"■        ■\0");
    strcpy(ASCII['B'][3],"■      ■  \0");
    strcpy(ASCII['B'][4],"■■■■    \0");
    strcpy(ASCII['B'][5],"■      ■  \0");
    strcpy(ASCII['B'][6],"■        ■\0");
    strcpy(ASCII['B'][7],"■        ■\0");
    strcpy(ASCII['B'][8],"■      ■  \0");
    strcpy(ASCII['B'][9],"■■■■    \0");

    strcpy(ASCII['C'][0],"    ■■■■\0");
    strcpy(ASCII['C'][1],"  ■        \0");
    strcpy(ASCII['C'][2],"■          \0");
    strcpy(ASCII['C'][3],"■          \0");
    strcpy(ASCII['C'][4],"■          \0");
    strcpy(ASCII['C'][5],"■          \0");
    strcpy(ASCII['C'][6],"■          \0");
    strcpy(ASCII['C'][7],"■          \0");
    strcpy(ASCII['C'][8],"  ■        \0");
    strcpy(ASCII['C'][9],"    ■■■■\0");

    strcpy(ASCII['D'][0],"■■■      \0");
    strcpy(ASCII['D'][1],"■    ■    \0");
    strcpy(ASCII['D'][2],"■      ■  \0");
    strcpy(ASCII['D'][3],"■        ■\0");
    strcpy(ASCII['D'][4],"■        ■\0");
    strcpy(ASCII['D'][5],"■        ■\0");
    strcpy(ASCII['D'][6],"■        ■\0");
    strcpy(ASCII['D'][7],"■      ■  \0");
    strcpy(ASCII['D'][8],"■    ■    \0");
    strcpy(ASCII['D'][9],"■■■      \0");

    strcpy(ASCII['E'][0],"■■■■■■\0");
    strcpy(ASCII['E'][1],"■          \0");
    strcpy(ASCII['E'][2],"■          \0");
    strcpy(ASCII['E'][3],"■          \0");
    strcpy(ASCII['E'][4],"■■■■■■\0");
    strcpy(ASCII['E'][5],"■          \0");
    strcpy(ASCII['E'][6],"■          \0");
    strcpy(ASCII['E'][7],"■          \0");
    strcpy(ASCII['E'][8],"■          \0");
    strcpy(ASCII['E'][9],"■■■■■■\0");

    strcpy(ASCII['F'][0],"■■■■■■\0");
    strcpy(ASCII['F'][1],"■          \0");
    strcpy(ASCII['F'][2],"■          \0");
    strcpy(ASCII['F'][3],"■          \0");
    strcpy(ASCII['F'][4],"■■■■■■\0");
    strcpy(ASCII['F'][5],"■          \0");
    strcpy(ASCII['F'][6],"■          \0");
    strcpy(ASCII['F'][7],"■          \0");
    strcpy(ASCII['F'][8],"■          \0");
    strcpy(ASCII['F'][9],"■          \0");

    strcpy(ASCII['G'][0],"    ■■■■\0");
    strcpy(ASCII['G'][1],"  ■        \0");
    strcpy(ASCII['G'][2],"■          \0");
    strcpy(ASCII['G'][3],"■          \0");
    strcpy(ASCII['G'][4],"■          \0");
    strcpy(ASCII['G'][5],"■    ■■■\0");
    strcpy(ASCII['G'][6],"■        ■\0");
    strcpy(ASCII['G'][7],"  ■      ■\0");
    strcpy(ASCII['G'][8],"  ■      ■\0");
    strcpy(ASCII['G'][9],"    ■■■  \0");


    strcpy(ASCII['H'][0],"■        ■\0");
    strcpy(ASCII['H'][1],"■        ■\0");
    strcpy(ASCII['H'][2],"■        ■\0");
    strcpy(ASCII['H'][3],"■        ■\0");
    strcpy(ASCII['H'][4],"■■■■■■\0");
    strcpy(ASCII['H'][5],"■        ■\0");
    strcpy(ASCII['H'][6],"■        ■\0");
    strcpy(ASCII['H'][7],"■        ■\0");
    strcpy(ASCII['H'][8],"■        ■\0");
    strcpy(ASCII['H'][9],"■        ■\0");

    strcpy(ASCII['I'][0],"■■■■■  \0");
    strcpy(ASCII['I'][1],"    ■    \0");
    strcpy(ASCII['I'][2],"    ■    \0");
    strcpy(ASCII['I'][3],"    ■    \0");
    strcpy(ASCII['I'][4],"    ■    \0");
    strcpy(ASCII['I'][5],"    ■    \0");
    strcpy(ASCII['I'][6],"    ■    \0");
    strcpy(ASCII['I'][7],"    ■    \0");
    strcpy(ASCII['I'][8],"    ■    \0");
    strcpy(ASCII['I'][9],"■■■■■  \0");

    strcpy(ASCII['J'][0],"■■■■■■\0");
    strcpy(ASCII['J'][1],"      ■  \0");
    strcpy(ASCII['J'][2],"      ■  \0");
    strcpy(ASCII['J'][3],"      ■  \0");
    strcpy(ASCII['J'][4],"      ■  \0");
    strcpy(ASCII['J'][5],"      ■  \0");
    strcpy(ASCII['J'][6],"      ■  \0");
    strcpy(ASCII['J'][7],"      ■  \0");
    strcpy(ASCII['J'][8],"■    ■    \0");
    strcpy(ASCII['J'][9],"  ■■      \0");

    strcpy(ASCII['K'][0],"■       ■\0");
    strcpy(ASCII['K'][1],"■      ■  \0");
    strcpy(ASCII['K'][2],"■    ■  \0");
    strcpy(ASCII['K'][3],"■  ■      \0");
    strcpy(ASCII['K'][4],"■■        \0");
    strcpy(ASCII['K'][5],"■■        \0");
    strcpy(ASCII['K'][6],"■  ■      \0");
    strcpy(ASCII['K'][7],"■    ■    \0");
    strcpy(ASCII['K'][8],"■      ■  \0");
    strcpy(ASCII['K'][9],"■        ■\0");

    strcpy(ASCII['L'][0],"■          \0");
    strcpy(ASCII['L'][1],"■          \0");
    strcpy(ASCII['L'][2],"■          \0");
    strcpy(ASCII['L'][3],"■          \0");
    strcpy(ASCII['L'][4],"■          \0");
    strcpy(ASCII['L'][5],"■          \0");
    strcpy(ASCII['L'][6],"■          \0");
    strcpy(ASCII['L'][7],"■          \0");
    strcpy(ASCII['L'][8],"■          \0");
    strcpy(ASCII['L'][9],"■■■■■■\0");

    strcpy(ASCII['M'][0],"■        ■\0");
    strcpy(ASCII['M'][1],"■■    ■■\0");
    strcpy(ASCII['M'][2],"■ ■  ■ ■\0");
    strcpy(ASCII['M'][3],"■  ■■  ■\0");
    strcpy(ASCII['M'][4],"■        ■\0");
    strcpy(ASCII['M'][5],"■        ■\0");
    strcpy(ASCII['M'][6],"■        ■\0");
    strcpy(ASCII['M'][7],"■        ■\0");
    strcpy(ASCII['M'][8],"■        ■\0");
    strcpy(ASCII['M'][9],"■        ■\0");

    strcpy(ASCII['N'][0],"■        ■\0");
    strcpy(ASCII['N'][1],"■■      ■\0");
    strcpy(ASCII['N'][2],"■ ■     ■\0");
    strcpy(ASCII['N'][3],"■  ■    ■\0");
    strcpy(ASCII['N'][4],"■   ■   ■\0");
    strcpy(ASCII['N'][5],"■    ■  ■\0");
    strcpy(ASCII['N'][6],"■     ■ ■\0");
    strcpy(ASCII['N'][7],"■      ■■\0");
    strcpy(ASCII['N'][8],"■        ■\0");
    strcpy(ASCII['N'][9],"■        ■\0");

    strcpy(ASCII['O'][0],"  ■■■■  \0");
    strcpy(ASCII['O'][1],"■        ■\0");
    strcpy(ASCII['O'][2],"■        ■\0");
    strcpy(ASCII['O'][3],"■        ■\0");
    strcpy(ASCII['O'][4],"■        ■\0");
    strcpy(ASCII['O'][5],"■        ■\0");
    strcpy(ASCII['O'][6],"■        ■\0");
    strcpy(ASCII['O'][7],"■        ■\0");
    strcpy(ASCII['O'][8],"■        ■\0");
    strcpy(ASCII['O'][9],"  ■■■■  \0");

    strcpy(ASCII['P'][0],"■■■■■\0");
    strcpy(ASCII['P'][1],"■        ■\0");
    strcpy(ASCII['P'][2],"■        ■\0");
    strcpy(ASCII['P'][3],"■        ■\0");
    strcpy(ASCII['P'][4],"■■■■■  \0");
    strcpy(ASCII['P'][5],"■          \0");
    strcpy(ASCII['P'][6],"■          \0");
    strcpy(ASCII['P'][7],"■          \0");
    strcpy(ASCII['P'][8],"■          \0");
    strcpy(ASCII['P'][9],"■          \0");

    strcpy(ASCII['Q'][0],"  ■■■    \0");
    strcpy(ASCII['Q'][1],"■      ■  \0");
    strcpy(ASCII['Q'][2],"■      ■  \0");
    strcpy(ASCII['Q'][3],"■      ■  \0");
    strcpy(ASCII['Q'][4],"■      ■  \0");
    strcpy(ASCII['Q'][5],"■      ■  \0");
    strcpy(ASCII['Q'][6],"■      ■  \0");
    strcpy(ASCII['Q'][7],"■    ■    \0");
    strcpy(ASCII['Q'][8],"  ■■  ■  \0");
    strcpy(ASCII['Q'][9],"          ■\0");

    strcpy(ASCII['R'][0],"■■■■■\0");
    strcpy(ASCII['R'][1],"■        ■\0");
    strcpy(ASCII['R'][2],"■        ■\0");
    strcpy(ASCII['R'][3],"■        ■\0");
    strcpy(ASCII['R'][4],"■■■■■  \0");
    strcpy(ASCII['R'][5],"■■        \0");
    strcpy(ASCII['R'][6],"■  ■      \0");
    strcpy(ASCII['R'][7],"■    ■    \0");
    strcpy(ASCII['R'][8],"■      ■  \0");
    strcpy(ASCII['R'][9],"■        ■\0");

    strcpy(ASCII['S'][0],"  ■■■■■\0");
    strcpy(ASCII['S'][1],"■          \0");
    strcpy(ASCII['S'][2],"■          \0");
    strcpy(ASCII['S'][3],"■          \0");
    strcpy(ASCII['S'][4],"  ■■■■  \0");
    strcpy(ASCII['S'][5],"          ■\0");
    strcpy(ASCII['S'][6],"          ■\0");
    strcpy(ASCII['S'][7],"          ■\0");
    strcpy(ASCII['S'][8],"          ■\0");
    strcpy(ASCII['S'][9],"■■■■■  \0");

    strcpy(ASCII['T'][0],"■■■■■■\0");
    strcpy(ASCII['T'][1],"    ■    \0");
    strcpy(ASCII['T'][2],"    ■    \0");
    strcpy(ASCII['T'][3],"    ■    \0");
    strcpy(ASCII['T'][4],"    ■    \0");
    strcpy(ASCII['T'][5],"    ■    \0");
    strcpy(ASCII['T'][6],"    ■    \0");
    strcpy(ASCII['T'][7],"    ■    \0");
    strcpy(ASCII['T'][8],"    ■    \0");
    strcpy(ASCII['T'][9],"    ■    \0");

    strcpy(ASCII['U'][0],"■        ■\0");
    strcpy(ASCII['U'][1],"■        ■\0");
    strcpy(ASCII['U'][2],"■        ■\0");
    strcpy(ASCII['U'][3],"■        ■\0");
    strcpy(ASCII['U'][4],"■        ■\0");
    strcpy(ASCII['U'][5],"■        ■\0");
    strcpy(ASCII['U'][6],"■        ■\0");
    strcpy(ASCII['U'][7],"■        ■\0");
    strcpy(ASCII['U'][8],"■        ■\0");
    strcpy(ASCII['U'][9],"  ■■■■  \0");


    strcpy(ASCII['V'][0],"■        ■\0");
    strcpy(ASCII['V'][1],"■        ■\0");
    strcpy(ASCII['V'][2],"■        ■\0");
    strcpy(ASCII['V'][3]," ■      ■ \0");
    strcpy(ASCII['V'][4]," ■      ■ \0");
    strcpy(ASCII['V'][5],"  ■    ■  \0");
    strcpy(ASCII['V'][6],"  ■    ■ \0");
    strcpy(ASCII['V'][7],"   ■  ■   \0");
    strcpy(ASCII['V'][8],"   ■  ■   \0");
    strcpy(ASCII['V'][9],"    ■■    \0");

    strcpy(ASCII['W'][0],"■        ■\0");
    strcpy(ASCII['W'][1],"■        ■\0");
    strcpy(ASCII['W'][2],"■        ■\0");
    strcpy(ASCII['W'][3],"■        ■\0");
    strcpy(ASCII['W'][4],"■        ■\0");
    strcpy(ASCII['W'][5],"■   ■   ■\0");
    strcpy(ASCII['W'][6]," ■  ■  ■ \0");
    strcpy(ASCII['W'][7]," ■  ■  ■ \0");
    strcpy(ASCII['W'][8]," ■  ■  ■ \0");
    strcpy(ASCII['W'][9],"   ■  ■\0");

    strcpy(ASCII['X'][0],"■        ■\0");
    strcpy(ASCII['X'][1]," ■      ■ \0");
    strcpy(ASCII['X'][2],"  ■    ■  \0");
    strcpy(ASCII['X'][3],"   ■  ■   \0");
    strcpy(ASCII['X'][4],"    ■■    \0");
    strcpy(ASCII['X'][5],"    ■■    \0");
    strcpy(ASCII['X'][6],"   ■  ■   \0");
    strcpy(ASCII['X'][7],"  ■    ■  \0");
    strcpy(ASCII['X'][8]," ■      ■ \0");
    strcpy(ASCII['X'][9],"■        ■\0");

    strcpy(ASCII['Y'][0],"■        ■\0");
    strcpy(ASCII['Y'][1]," ■      ■ \0");
    strcpy(ASCII['Y'][2],"  ■    ■  \0");
    strcpy(ASCII['Y'][3],"   ■  ■   \0");
    strcpy(ASCII['Y'][4],"   ■  ■   \0");
    strcpy(ASCII['Y'][5],"    ■■    \0");
    strcpy(ASCII['Y'][6],"    ■■    \0");
    strcpy(ASCII['Y'][7],"    ■■    \0");
    strcpy(ASCII['Y'][8],"    ■■    \0");
    strcpy(ASCII['Y'][9],"    ■■    \0");

    strcpy(ASCII['Z'][0],"■■■■■■\0");
    strcpy(ASCII['Z'][1],"         ■ \0");
    strcpy(ASCII['Z'][2],"        ■  \0");
    strcpy(ASCII['Z'][3],"       ■   \0");
    strcpy(ASCII['Z'][4],"      ■    \0");
    strcpy(ASCII['Z'][5],"    ■      \0");
    strcpy(ASCII['Z'][6],"   ■       \0");
    strcpy(ASCII['Z'][7],"  ■        \0");
    strcpy(ASCII['Z'][8]," ■         \0");
    strcpy(ASCII['Z'][9],"■■■■■■\0");
}
