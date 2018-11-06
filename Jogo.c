#include <windows.h>
#include <conio2.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Position{

int x;
int y;
int xTela; /// necessário,porque o x e o y são respectivos à matriz,não à tela
int yTela;

}Position;

typedef struct game{

char matriz_jogo[11][27];
Position position;
/// char nome_mapa[10];

}TIPO_JOGO;

typedef struct player{

char nome[30];
int score;
int status; /// 1 = vivo; 0 = morto ; talvez algum status de poder

}TIPO_JOGADOR;

typedef struct rato {

int posXinicial;
int posYinicial; /// inicial na matriz
Position position;
int status; /// 1 = vivo; 2 = morto(retornar posição original)
int vidas;

}TIPO_RATO;

typedef struct gatos{

int posXinicial; /// como serão 4 gatos,teremos 4 posições
int posYinicial;
Position position;
int status; /// 1 = vivo; 2 = morto(retornar posição original)

}TIPO_GATO;

typedef struct portas{

Position position;
int nPortas; /// vai de 0 à "nportas",pois usaremos como argumento do vetor portas
int status;
char temp_portas[8]; /// 0 = fechada 1 = aberta

}TIPO_PORTA;

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

    /// referente à matriz do jogo
    game->matriz_jogo[rato->position.y][rato->position.x] = ' ';
    rato->position.x = x; /// posição na matriz(mais ou menos 1)
    rato->position.y = y;
    game->matriz_jogo[rato->position.y][rato->position.x] = 'M';

    desenha_rect(rato->position.xTela,rato->position.yTela,WHITE,BLACK);


}

int RecebeDirecao()
 {
    unsigned char a;
    int direction;
    fflush(stdin);


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

               case 27:  direction =5;
                         break;

               default:break;

            }

    return direction;

}

void le_mapa(TIPO_GATO gatos[],TIPO_JOGO *game,TIPO_RATO *rato,TIPO_PORTA portas[])
{

    FILE *mapa;
    char buf; /// reading of each individualized character from the map
    int coluna = 0;
    int linha = 0;
    int nGatos=0;
    portas->nPortas = 0;


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
                            rato->position.xTela = coluna + 21 ;
                            rato->position.yTela = linha + 6 ;
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
                            portas[portas->nPortas].position.x = coluna;
                            portas[portas->nPortas].position.y = linha;
                            portas[portas->nPortas].position.xTela = coluna*2 + 20 ;
                            portas[portas->nPortas].position.yTela = linha*2 + 5 ;
                            portas->nPortas += 1;
                            portas[portas->nPortas].status = 0;
                            coluna++;
                            break;

                case '\n':  coluna=0;
                            linha++;
                            break;

             }

        }


            fclose(mapa);

}

void desenha_mapa(TIPO_JOGO *game,TIPO_PORTA *portas)
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


                    case 'G':   desenha_rect(x0,y0,LIGHTRED,BLACK);
                                x0+=2;
                                break;

                    case 'T':   desenha_rect(x0,y0,DARKGRAY,BLACK);
                                portas[portas->nPortas].position.xTela = x0;
                                portas[portas->nPortas].position.yTela = y0;
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
            break;

    ///esquerda
    case 2:
            newX = rato->position.x-1;
            newY = rato->position.y;
            break;
    /// cima
    case 3:
            newX = rato->position.x;
            newY = rato->position.y -1;
            break;
    ///baixo
    case 4:
             newX = rato->position.x;
             newY = rato->position.y+1;
             break;

    case 5: newX = rato->position.x;
            newY = rato->position.y;
            movendo = false;
            break;

    default:break;

        } /// switch
       checkPosition(newY,newX,game,rato);
    }

}

void modifica_portas(TIPO_JOGO *game,TIPO_PORTA portas[])
{

int i;

    for(i=0;i < portas->nPortas; i++)
    {

        portas[i].temp_portas[i] = game->matriz_jogo[portas[i].position.y+1][portas[i].position.x+1]; /// salvo oque tinha no lugar novo da porta
        game->matriz_jogo[portas[i].position.y][portas[i].position.x] = ' ';
        portas[i].position.y +=1;
        portas[i].position.x +=1;
        game->matriz_jogo[portas[i].position.y][portas[i].position.x] = 'T';
        desenha_rect(portas[i].position.xTela,portas[i].position.yTela,BLACK,BLACK);
        portas[i].position.xTela +=2;
        portas[i].position.yTela +=2;
        desenha_rect(portas[i].position.xTela,portas[i].position.yTela,DARKGRAY,BLACK);

    }
}

void recebe_teclado_letras(TIPO_JOGO *game,TIPO_PORTA portas[])
{


    char ch;
    fflush(stdin);
        ch = getch();
        //ch = tolower(ch);

        switch(ch)
        {

            case 'b': modifica_portas(game,portas);
                break;
            //case 'B':


            case 'p': ///PausaGame()
            break;


            case 9:  /// Apresenta o menu do jogo (TAB)
                break;


        }



}

void GAME(TIPO_RATO *rato,TIPO_JOGO *game,TIPO_PORTA portas[])
{

    atualiza_rato(rato,game);

    recebe_teclado_letras(game,portas);

}



int main(){


TIPO_GATO gatos[4];
TIPO_PORTA portas[8];
TIPO_JOGADOR player;
TIPO_JOGO game;
TIPO_RATO rato;
Position position;


le_mapa(gatos,&game,&rato,portas);
desenha_mapa(&game,portas);
hideCursor();


//GAME(&rato,&game,portas);


atualiza_rato(&rato,&game);
modifica_portas(&game,portas);


      ///atualiza_jogo();
      ///recordes();



/*
            printf("\n");
            printf("\n");

    for(int i=0;i<11;i++)
    {
        for(int j=0;j<27;j++)
        {
            printf("%c",game.matriz_jogo[i][j]);
        }
            printf("\n");

    }
   // printf(" x: %d y: %d",rato.position.x,rato.position.y);
*/



return 0;
}
