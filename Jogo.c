#include <windows.h>
#include <conio2.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Position{

int x;
int y;
<<<<<<< HEAD
int xTela; /// necess·rio,porque o x e o y s„o respectivos ‡ matriz,n„o ‡ tela
int yTela;
=======
int xDobrado;
int yDobrado;
>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088

}Position;

typedef struct game{

char matriz_jogo[11][27];
Position position;
char nome_mapa[10];


}TIPO_JOGO;

typedef struct player{

char nome[30];
int score;
int vidas;
int status; /// 1 = vivo; 0 = morto ; talvez algum status de poder

}TIPO_JOGADOR;

typedef struct rato {

int posXinicial;
int posYinicial; /// inicial na matriz
Position position;
int status; /// 1 = vivo; 2 = morto(retornar posi√ß√£o original)

}TIPO_RATO;

typedef struct gatos{

int posXinicial; /// como ser√£o 4 gatos,teremos 4 posi√ß√µes
int posYinicial;
Position position;
int status; /// 1 = vivo; 2 = morto(retornar posi√ß√£o original)

}TIPO_GATO;

void hideCursor()
{
    CONSOLE_CURSOR_INFO info = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void desenha_rect(int posX,int posY,char cor_fundo,char cor_texto){


            textbackground(cor_fundo);
            textcolor(cor_texto);
            putchxy(posX,posY,' ');
            putchxy(posX+1,posY,' ');
            putchxy(posX,posY+1,' ');
            putchxy(posX+1,posY+1,' ');

}

void move_rato(int y,int x,TIPO_JOGO *game,TIPO_RATO *rato)
{
<<<<<<< HEAD

     desenha_rect(rato->position.xTela,rato->position.yTela,BLACK,BLACK);

      if(x > rato->position.x)
            {
                rato->position.xTela = rato->position.xTela + 2;
                rato->position.yTela = rato->position.yTela;
            }

        else if(x < rato->position.x)
            {
                rato->position.xTela = rato->position.xTela - 2;
                rato->position.yTela = rato->position.yTela;

            }

            else if(y > rato->position.y)
            {
                rato->position.yTela = rato->position.yTela +2;
                rato->position.xTela = rato->position.xTela;

            }

           else if(y < rato->position.y)
            {
                rato->position.yTela = rato->position.yTela -2;  ;
                rato->position.xTela = rato->position.xTela;
            }

    /// referente ‡ matriz do jogo
    game->matriz_jogo[rato->position.y][rato->position.x] = ' ';
    rato->position.x = x; /// posiÁ„o na matriz(mais ou menos 1)
    rato->position.y = y;
=======
    desenha_rect(rato->position.x+21,rato->position.y+6,BLACK,BLACK);

    game->matriz_jogo[rato->position.y][rato->position.x] = ' ';

    rato->position.x = x; /// posi√ß√£o na matriz(mais ou menos 1)
    rato->position.y = y;


>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088
    game->matriz_jogo[rato->position.y][rato->position.x] = 'M';
    desenha_rect((rato->position.xDobrado+21),(rato->position.yDobrado+6),WHITE,BLACK);

    desenha_rect(rato->position.xTela,rato->position.yTela,WHITE,BLACK);


}


int RecebeDirecao()
 {
    unsigned char a;
    int direction;
    fflush(stdin);

/*
  a = getch();

		//for detect the function\arrow keys
		//we must call the getch() again
		//testing if a is '0' or '0xE0'
		if (a==0 || a==0xE0)
            a=getch();

		if (a==27) //ESC for exit the 'while'
		   direction = 5;
		else if (a==72)
            direction =3;
		else if (a==80)
			 direction = 4;
		else if (a==75)
            direction = 2;
		else if (a==77)
			 direction = 1;

*/
        char ch;
            ch = getch();

            switch(ch)
            {
                case 'd':
                case 'D': direction =1;
                break;

                case 'a':
                case 'A':direction=2;
                break;

                case 'w':
                case 'W':direction=3;
                    break;

                case 's':
                case 'S': direction=4;
                        break;

<<<<<<< HEAD
               case 27:  direction =5;
                         break;
=======
               case 'Q':
               case 'q': direction=5;
                        break;
>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088

               default:break;

            }

    return direction;

}


void le_mapa(TIPO_GATO gatos[],TIPO_JOGO *game,TIPO_RATO *rato)
{

    FILE *mapa;
    char buf; /// reading of each individualized character from the map
    int coluna = 0;
    int linha = 0;
    int nGatos=0;

        if(!(mapa = fopen("nivel01.txt","r")))       /// must found a way to change the level name mid-game and read it again as we pass through a new level
            printf("erro na abertura do arquivo");

        else
            while(!feof(mapa))
            {
                buf = getc(mapa);

                switch(buf)
                {

                case 'M':   rato->posXinicial = coluna;
                            rato->posYinicial = linha;
                            rato->position.x = coluna;
                            rato->position.y = linha;
                            rato->position.xTela = coluna+21;
                            rato->position.yTela = linha+6;
                            game->matriz_jogo[rato->position.y][rato->position.x]= buf;
                            coluna++;
                            break;

                case 'X':   game->matriz_jogo[linha][coluna]= buf;
                            coluna++;
                            break;

                case 'Q':   game->matriz_jogo[linha][coluna]= buf;
                            coluna++;
                            break;


                case 'O':   game->matriz_jogo[linha][coluna]= buf;
                            coluna++;
                            break;

                case 'G':   game->matriz_jogo[linha][coluna]= buf;
                            gatos[nGatos].posXinicial = coluna;
                            gatos[nGatos].posYinicial = linha;
                            gatos[nGatos].position.x = coluna;
                            gatos[nGatos].position.y = linha;
                            nGatos++;
                            coluna++;
                            break;

                case 'T':   game->matriz_jogo[linha][coluna]= buf;
                            coluna++;
                            break;

                case '\n':  coluna=0;
                            linha++;
                            break;

             }

        }


            fclose(mapa);

}


void desenha_mapa(TIPO_JOGO *game)
{
    int x0=20;  /// Initial X of screen
    int y0=5;  /// Initial Y of screen

        for(int i=0;i<11;i++)
        {
            for(int j=0;j<27;j++)
            {
               switch(game->matriz_jogo[i][j])
               {

                    case 'M':   desenha_rect(x0,y0,WHITE,BLACK);
                                x0+=2;
                                break;

                    case 'Q':   textcolor(YELLOW);
                                textbackground(BLACK);
                                putchxy(x0+1,y0,'.');
                                x0+=2;
                                break;

                    case 'X':   desenha_rect(x0,y0,GREEN,BLACK);
                                x0+=2;
                                break;

                    case 'O':   textcolor(WHITE);
                                textbackground(BLACK);
                                putchxy(x0,y0,92);
                                putchxy(x0+1,y0,'/');
                                putchxy(x0,y0+1,'/');
                                putchxy(x0+1,y0+1,92);

                                x0+=2;
                                break;


                    case 'G':   desenha_rect(x0,y0,RED,BLACK);
                                x0+=2;
                                break;

                    case 'T':   desenha_rect(x0,y0,DARKGRAY,BLACK); /// COR?
                                x0+=2;
                                break;
               }
            }

            x0=20;
            y0+=2;

        }

}

void checkPosition(int newY,int newX,TIPO_JOGO *game,TIPO_RATO *rato)
{

    switch(game->matriz_jogo[newY][newX])
    {
            case 'X':
            break;

            case 'T':
            break;

            case 'G': move_rato(newY,newX,game,rato);
                      break;

            default:    move_rato(newY,newX,game,rato);
            break;

    }

}

void atualiza_rato(TIPO_RATO *rato,TIPO_JOGO *game)
{


char ch;
int direcao;
bool movendo = true;
int newX;
int newY;

    while(movendo)
    {

    direcao = RecebeDirecao();

     switch(direcao)
    {

    ///direita
    case 1:
            newX = rato->position.x+1;
            newY = rato->position.y;
            rato->position.xDobrado = rato->position.x+2;
            rato->position.yDobrado = rato->position.y;
            break;

    ///esquerda
    case 2:
            newX = rato->position.x-1;
            newY = rato->position.y;
            rato->position.xDobrado = rato->position.x-2;
            rato->position.yDobrado = rato->position.y;
            break;
    /// cima
    case 3:
            newX = rato->position.x;
            newY = rato->position.y -1;
<<<<<<< HEAD
=======
            rato->position.xDobrado = rato->position.x;
            rato->position.yDobrado = rato->position.y-2;
>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088
            break;
    ///baixo
    case 4:
             newX = rato->position.x;
             newY = rato->position.y+1;
<<<<<<< HEAD
=======
             rato->position.xDobrado = rato->position.x;
             rato->position.yDobrado = rato->position.y+2;
>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088
             break;

    case 5: newX = rato->position.x;
            newY = rato->position.y;
            rato->position.xDobrado = rato->position.x;
            rato->position.yDobrado = rato->position.y;
            movendo = false;
            break;

        } /// switch
       checkPosition(newY,newX,game,rato);
    } /// while


}



int main(){


TIPO_GATO gatos[4];
TIPO_JOGADOR player;
TIPO_JOGO game;
TIPO_RATO rato;
Position position;

<<<<<<< HEAD

le_mapa(gatos,&game,&rato);
desenha_mapa(&game);
hideCursor();


      atualiza_rato(&rato,&game);
      ///atualiza_jogo();
      ///recordes();

    /*


=======
int teste=1;
int i=0;

le_mapa(gatos,&game,&rato);    /// you pass the address of the structure as parameter,because you want the whole thing as a localization point
desenha_mapa(&game);

//hideCursor();
//system("mode con:cols=105 lines=30"); // delimitador do tamaho da tela (cols = colunas, lines = linhas)


  atualiza_rato(&rato,&game);


    clrscr();
>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<27;j++)
        {
            printf("%c",game.matriz_jogo[i][j]);
        }
            printf("\n");

    }
<<<<<<< HEAD
   // printf(" x: %d y: %d",rato.position.x,rato.position.y);

        */
=======
    printf(" x: %d y: %d",rato.position.x,rato.position.y);

>>>>>>> 3e04ee8125bb2aab2f26a56aa601ae8ac4505088


return 0;
}

      
