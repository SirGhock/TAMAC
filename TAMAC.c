/*
JOGO DESENVOLVIDO NA GAME JAM 2017
TEMA: EDUCACAO FINANCEIRA
HORARIO DE INICIO: 14H DO DIA 16/09/17
HORARIO DE FIM: 12H DO DIA 17/09/17

   INTEGRANTES:JOAO FERNANDO
               LEONARDO NORIO
               MAIKON ALEXANDER
*/
//----------INCLUDES---------------
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include<unistd.h>
//----------DEFINES---------------
#define TAMX 20      //TAMANHO DE X PRIMEIRO_MINIJOGO
#define TAMY 20      //TAMANHO DE Y PRIMEIRO_MINIJOGO
#define PAREDE 219   //SPRITE PAREDE PRIMEIRO_MINIJOGO
#define COLUNA 177   //SPRITE COLUNA PRIMEIRO_MINIJOGO
#define MOEDA 184    //SPRITE MOEDA PRIMEIRO_MINIJOGO
#define CHAO 0       //SPRITE CHAO PRIMEIRO_MINIJOGO
#define CIMA 72
#define BAIXO 80
#define DIREITA 77      //ASCII SETAS E ENTER TECLADO
#define ESQUERDA 75
#define ENTER 13
//---------RANDON DUNGEON----------
#ifdef RAND_MAX
#undef RAND_MAX
#define RAND_MAX 900
#endif
//-----------------------STRUCTS----------------------------------------
typedef struct persona{
   int id;
   int vida;
   int fome;                                //PERSONAGEM
   int felicidade;
   float dinheiro;
}ppersonagem;
typedef struct monst{
      char nome[10];
      int vida;                               //MONSTRO
      int dano;
}monstro;
//------------------------PROTOTIPACOES----------------------------------------
int jogo(ppersonagem* personagem);
int menu();
void comoJogar();
void movimento(int *a, int mat[TAMX][TAMY], int vet[TAMX][TAMY], int *x, int *y, int valor);
void desenha(int mat[TAMX][TAMY]);
void criaBordas(int mat[TAMX][TAMY]);
void randome(int vet[TAMX][TAMY]);
void geraDungeon(int mat[TAMX][TAMY], int vet[TAMX][TAMY], int SPR_PERS);
void geraMoedas(int mat[TAMX][TAMY], int vet[TAMX][TAMY], int SPR_PERS);
int contMoedas(int mat[TAMX][TAMY]);
void check(int mat[TAMX][TAMY], int SPR_PERS);
void mostquestao(int per);
void questao(ppersonagem* personagem);
void monster(monstro*mob, int mons);
int batalha(ppersonagem *personagem);
//-----------------------FUNÇOES----------------------------------------
//-----------------------CRIA_LINHA----------------------------------------
void delimitaLinha(){
   printf("\n");
   printf("---------------------------------------------");
}
//-----------------------MENU_PRIMEIRO_MINIJOGO----------------------------------------
int miniUm(ppersonagem* personagem){
   int tempo = 0;
   int c = 0;
   while(c != 4){
      system("cls");
      c = menu();
      if(c == 0){
         system("cls");
         jogo(personagem);
      }
      if(c == 1){                   //CHAMA O MENU PARA O PRIMEIRO_MINIJOGO
         system("cls");
         comoJogar();
      }
      if(c == 2){
         system("cls");
         return 0;
      }
   }
   return 0;
}
//-----------------------PRIMEIRO_MINIJOGO----------------------------------------
int jogo(ppersonagem* personagem){
   int vet [TAMY][TAMX];   ///MATRIZ GERADORA DA DUNGEON
   int mat [TAMY][TAMX];   ///MATRIZ PRINCIPAL DO PRIMEIRO MINIJOGO
   int j = 0,  /// COLUNA
   i = 0,  /// LINHA
   x = 0,  /// RECEBE O I
   y = 0,  /// RECEBE O J
   qntMoedas = 0,
   a = 0;  /// CONTA OS PONTOS
   char nome[30];
   clock_t tInicio, tFim, tDecorrido;
   tInicio = clock();
   int SPR_PERS = 0;
   if(personagem->id == 0){
      SPR_PERS = 30;
   }
   if(personagem->id == 1){
      SPR_PERS = 20;
   }
   if(personagem->id == 2){
      SPR_PERS = 258;
   }
   criaBordas(mat);
   mat[2][2] = SPR_PERS;
   x = 2;
   y = 2;
   geraDungeon(mat, vet, SPR_PERS);
   geraMoedas(mat, vet, SPR_PERS);
   qntMoedas = contMoedas(mat);
   check(mat, SPR_PERS);
   while(1){
      if(a == qntMoedas){
         personagem->dinheiro += a;
         personagem->fome -= 10;             //SE PEGA TODAS AS MOEDAS O PRIMEIRO_MINIJOGO ACABA
         personagem->felicidade -= 5;
         return 0;
      }
      printf("%d, tot = %d", a, qntMoedas);
      printf("\n\n");
      desenha(mat);
      movimento(&a, mat, vet, &x, &y, SPR_PERS);
      printf("\n\n");
      system("cls");
   }
   return qntMoedas;
}
//-----------------------MOVIMENTACAO_PRIMEIRO_MINIJOGO----------------------------------------
void movimento(int *a, int mat[TAMX][TAMY], int vet[TAMX][TAMY], int *x, int *y, int valor){
   int SPR_PERS = valor;
   char c;
   int j = 0,                 //MOVIMENTACAO DO PERSONAGEM DENTRO DA MATRIZ
   i = 0;
   c = getch();
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMY; j++){
         if(mat[i][j] == SPR_PERS){
            *x = i;
            *y = j;
         }
      }
   }
   if((c == '6' || c == 'd') && (mat[*x][*y + 1] == 0 || mat[*x][*y + 1] == MOEDA)){
      if(mat[*x][*y + 1] == MOEDA){
         *a+= 1;
         printf("\a");
      }
      mat[*x][*y + 1] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '4' || c == 'a') && (mat[*x][*y - 1] == 0 || mat[*x][*y - 1] == MOEDA)){
      if(mat[*x][*y - 1] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x][*y - 1] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '8' || c == 'w') && (mat[*x - 1][*y] == 0 || mat[*x - 1][*y] == MOEDA)){
      if(mat[*x - 1][*y] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x - 1][*y] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '2' || c == 'x') && (mat[*x + 1][*y] == 0 || mat[*x + 1][*y] == MOEDA)){
      if(mat[*x + 1][*y] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x + 1][*y] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '3' || c == 'c') && (mat[*x + 1][*y + 1] == 0 || mat[*x + 1][*y + 1] == MOEDA)){
      if(mat[*x + 1][*y + 1] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x + 1][*y + 1] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '7' || c == 'q') && (mat[*x - 1][*y-1] == 0 || mat[*x - 1][*y - 1] == MOEDA)){
      if(mat[*x - 1][*y - 1] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x - 1][*y - 1] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '9' || c == 'e') && (mat[*x - 1][*y + 1] == 0 || mat[*x - 1][*y + 1] == MOEDA)){
      if(mat[*x - 1][*y + 1] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x - 1][*y + 1] = SPR_PERS;
      mat[*x][*y] = 0;
   }
   if((c == '1' || c == 'z') && (mat[*x + 1][*y - 1] == 0 || mat[*x + 1][*y - 1] == MOEDA)){
      if(mat[*x + 1][*y - 1] == MOEDA){
         *a += 1;
         printf("\a");
      }
      mat[*x + 1][*y - 1] = SPR_PERS;
      mat[*x][*y] = 0;
   }
}
//-----------------------DESENHA_PRIMEIRO-MINIJOGO----------------------------------------
void desenha(int mat[TAMX][TAMY]){
   int i = 0, j = 0;
   for(i = 0; i < TAMY; i++){
      printf("\n\t\t\t\t");               //DESENHA A MATRIZ NO PRIMEIRO_MINIJOGO
      for(j = 0; j < TAMX; j++){
         printf("%c", mat[i][j]);
      }
   }
}
//-----------------------CRIA_BORDAS_PRIMEIRO_MINIJOGO----------------------------------------
void criaBordas(int mat[TAMX][TAMY]){
   int i = 0, j = 0;
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMX; j++){
         mat[i][j] = CHAO;
      }
   }
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMX; j++){
         if(i == 0 || i == TAMY-1 || j == 0 || j == TAMX -1){
            mat[i][j] = PAREDE;
         }
      }
   }
}
//-----------------------FUNÇAO_RANDOM_PRIMEIRO_MINIJOGO----------------------------------------
void randome(int vet[TAMX][TAMY]){
   int j = 0,  /// COLUNA
   i = 0,  /// LINHA
   f = 0,  /// RANDON
   d = 0;  /// RANDON
   srand(time(NULL));
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMX; j++){
         f = 1 + rand()%RAND_MAX;
         d = 1 + rand()%RAND_MAX;
         vet[i][j] = f/d;
      }
   }
}
//-----------------------GERA_MAPA_PRIMEIRO_MINIJOGO----------------------------------------
void geraDungeon(int mat[TAMX][TAMY], int vet[TAMX][TAMY], int SPR_PERS){
   int j = 0,  /// COLUNA
   i = 0;  /// LINHA
   randome(vet);
   for(i = 0; i<TAMY; i++){
      for(j = 0; j<TAMX; j++){
         if(vet[i][j] == 1 && mat[i][j] != SPR_PERS && mat[i][j] != PAREDE){
            mat[i][j] = COLUNA;
         }
      }
   }
}
//-----------------------GERA_MOEDAS_PRIMEIRO_MINIJOGO----------------------------------------
void geraMoedas(int mat[TAMX][TAMY], int vet[TAMX][TAMY], int SPR_PERS){
   int j = 0,  /// COLUNA
   i = 0;  /// LINHA
   randome(vet);
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMX; j++){
         if(vet[i][j] == 2 && mat[i][j] != SPR_PERS && mat[i][j] != PAREDE){
            mat[i][j] = MOEDA;
         }
      }
   }
}
//-----------------------CONTA_MOEDAS_PRIMEIRO_MINIJOGO----------------------------------------
int contMoedas(int mat[TAMX][TAMY]){
   int i = 0, j = 0, cont = 0;
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMX; j++){
         if(mat[i][j] == MOEDA){
            cont++;
         }
      }
   }
   return cont;
}
//-----------------------CHECA_MOEDAS_PRIMEIRO_MINIJOGO----------------------------------------
void check(int mat[TAMX][TAMY], int SPR_PERS){
   int i = 0,
   j = 0,
   x = 0,
   y = 0,
   cont = 0;
   for(i = 0; i < TAMY; i++){
      for(j = 0; j < TAMX; j++){                  //CHECA SE NUNCA TERA UM QUADRADO FECHADO NO PRIMEIRO_MINIJOGO
         if(mat[i][j] == SPR_PERS){
            x = i;
            y = j;
         }
      }
   }
   if(mat[x - 1][y - 1] == COLUNA && mat[x][y - 1] == COLUNA && mat[x + 1][y - 1] == COLUNA
      && mat[x - 1][y] == COLUNA && mat[x + 1][y] == COLUNA && mat[x - 1][y + 1] == COLUNA
      && mat[x][y + 1] == COLUNA && mat[x + 1][y + 1] == COLUNA){
         mat[x - 1][y + 1] = 0;
         mat[x + 1][y] = 0;
         mat[x + 1][y + 1] = 0;
      }
   }
//-----------------------MENU_PRIMEIRO_MINIJOGO----------------------------------------
int menu(){
   int i = 0, j = 0, select = 0, c = 0;
   char menu[3][11] = {{' ','J', 'O', 'G', 'A', 'R'},
                        {' ', 'C', 'O', 'M', 'O', ' ', 'J', 'O', 'G', 'A', 'R'},
                        {' ', 'S', 'A', 'I', 'R'}};
   menu[select][0] = '>';
   for(i = 0; i < 3; i++){
      printf("\n");
      for(j = 0; j < 11; j++){
         printf("%c", menu[i][j]);
      }
   }
   while(1){
      c = getch();
      if(c == CIMA){
         if(select == 0){
            select = 2;
         }
         else{
            select--;
         }
      }
      if(c == BAIXO){
         if(select == 2){
            select = 0;
         }
         else{
            select++;
         }
      }
      if(c == ENTER){
         if(select == 0)
            return 0;
         if(select == 1)
            return 1;
         if(select == 2)
            return 2;
         if(select == 3)
            return 3;
      }
      for(i = 0; i < 3; i++){
         menu[i][0] = ' ';
      }
      menu[select][0] = '>';
      system("cls");
      for(i = 0; i < 3; i++){
         printf("\n");
         for(j = 0; j < 11; j++){
            printf("%c", menu[i][j]);
         }
      }
   }
}
//-----------------------COMO_JOGAR_PRIMEIRO_MINIJOGO----------------------------------------
void comoJogar(){
   printf("-------------------------COMO-JOGAR-------------------------\n\n");
   printf(" PARA SE MOVER UTILIZE AS TECLAS NESSAS DIRECOES\n");
   printf(" Q-W-E\n");
   printf(" A- -D                    S-ENTER\n");
   printf(" Z-X-C\n");
   printf("\n   OU\n\n");
   printf(" 7-8-9\n");
   printf(" 4- -6                    5-ENTER\n");
   printf(" 1-2-3\n");
   printf("\n\n PEGUE AS MOEDAS O MAIS RAPIDO POSSIVEL\n\n");
   system("pause");
}
//-----------------------COMO_JOGAR_PRINCIPAL----------------------------------------
void instrucao(){
   system("cls");
   printf("\nSETAS DIRECIONAIS = MOVIMENTACAO" );
   printf("\nMENU" );
   printf("\nUTILIZE OS BOTOES 1, 2, 3 E 4 PARA INTERAGIR NA TELA INGAME" );
   printf("\n===========================================================" );
   printf("\nLOJA" );
   printf("\nLOCAL ONDE PODEM SER ADQUUIRIDOS ITENS PARA SEU PERSONAGEM ");
   printf("\n===========================================================" );
   printf("\nJOGOS" );
   printf("\nPARA CONSEGUIR DINHEIRO NO JOGO,EH NECESSARIO PARTICIPAR DAS ATIVIDADES, E OS JOGOS SAO EXATAMENTE ISSO\n" );
   printf("\n===========================================================" );
   printf("\nOBJETIVOS");
   printf("\nENSINAR A EDUCACAO FINANCEIRA DIVERTIDAMENTE");
   printf("\n===========================================================" );
   printf("\nREGRAS");
   printf("\nNAO DEIXAR O PERSONAGEM MORRER E NEM CHEGAR PERTO DE FALIR\n");
   system("PAUSE");
}
//-----------------------CREDITOS_JOGO----------------------------------------
void creditos(){
   system("cls");
   printf("\t\t\tDESENVOLVIDOS PELOS  ALUNOS .:\n");
   printf("\n\t\t\tJOAO FERNANDO GARCIA DE SOUZA\n");
   printf("\n\t\t\tLEONARDO NORIO YAMASAKI CRUZ\n");
   printf("\n\t\t\tMAIKON ALEXANDER DE BARROS DIAS\n");
   printf("\n\n\t\t\tDURANTE A GAME JAM 2017\n\n\n");
   system("PAUSE");
}
//-----------------------MENU_INICIAL----------------------------------------
int intro(){
   char menu[4][10]= {{' ','J','O','G','A','R','(',' ',' ',' '},
                        {' ','I','N','S','T','R','U','C','A','O'},
                        {' ','C','R','E','D','I','T','O','S',' '},
                        {' ','S','A','I','R',' ',' ',' ',' ',' '}};
   char pers[3][6]= {{'S','L','I','M','E',' '},
                     {'V','A','C','A',' ',' '},
                     {'M','I','Y','A','G','I'}};
   int i, opcao = 1, j = 0;
   int saida = 0;
   char escolha;
   while(saida == 0){
      system("cls");
      for(i = 0; i < 4; i++){
         menu[i][0] = ' ';
      }
      menu[opcao-1][0] = '>';
      for(i = 0;i < 7; i++){
         printf ("%c",menu[0][i]);
      }
      for(i = 0; i < 6; i++){
         if (pers[j][i] != ' '){
            printf ("%c",pers[j][i]);
         }
      }
      printf(")\n");
      for(i = 0; i < 10; i++){
         printf ("%c",menu[1][i]);
      }
      printf("\n");
      for(i = 0; i < 10; i++){
         printf ("%c",menu[2][i]);
      }
      printf("\n");
      for(i = 0; i < 5; i++){
         printf ("%c",menu[3][i]);
      }
      printf("\n");
      fflush(stdin);
      escolha = getch();
      if (escolha == CIMA){
         if (opcao == 1){
            opcao = 4;
         }
         else{
            opcao--;
         }
      }else if(escolha == BAIXO){
         if (opcao == 4){
            opcao = 1;
         }
         else{
            opcao++;
         }
      }else if (opcao == 1 && escolha == DIREITA){
         if(j == 2){
            j = 0;
         }
         else{
            j++;
         }
      }else if (opcao == 1 && escolha == ESQUERDA){
         if(j == 0){
            j = 2;
         }
         else{
            j--;
         }
      }
      if (escolha == ENTER){
         switch(opcao){
            case 1:
               saida = 1;
               return j;
               break;
            case 2:
               instrucao();
               break;
            case 3:
               creditos();
               break;
            case 4:
               exit(0);
               break;
            default:
               break;
         }
      }
   }
}
//-----------------------TELA_MINIJOGOS----------------------------------------
int miniGames(ppersonagem* personagem){
   system("cls");
   int i = 0, j = 0, select = 0;
   char menu[4][11] = {{' ','C', 'A', 'P', 'T', 'U', 'R', 'A',' ',' '},
                        {' ','Q', 'U', 'I', 'Z', '(', 'R', '$','3','0',')'},
                        {' ','B', 'A', 'T', 'A', 'L', 'H', 'A',' ',' ',' '},
                        {' ','S', 'A', 'I', 'R',' ',' ',' ',' ',' ',' '}};
   menu[select][0] = '>';
   char c;
   for(i = 0; i<4; i++){
      printf("\n");
      for(j = 0; j<11; j++){
         printf("%c", menu[i][j]);
      }
   }
   while(1){
      c = getch();
      if(c == CIMA){
         if(select == 0){
            select = 2;
         }
         else{
            select--;
         }
      }
      if(c == BAIXO){
         if(select==3){
            select = 0;
         }
         else{
            select++;
         }
      }
      if(c == ENTER){
         switch(select){
            case 0:
               miniUm(personagem);
               break;
            case 1:
               system("cls");
               personagem->fome = personagem->fome - 10;
               if(personagem->fome < 0){
                  personagem->fome = 0;
               }
               personagem->felicidade = personagem->felicidade - 5;
               if(personagem->felicidade < 0){
                  personagem->felicidade = 0;
               }
               questao(personagem);
               break;
            case 2:
               personagem->fome = personagem->fome - 20;
               if(personagem->fome < 0){
                  personagem->fome = 0;
               }
               personagem->felicidade = personagem->felicidade - 10;
               if(personagem->felicidade < 0){
                  personagem->felicidade = 0;
               }
               batalha(personagem);
               break;
            case 3:
               return 0;
               break;
            default:
               break;
         }
      }
      for (i=0;i<4;i++){
         menu[i][0] = ' ';
      }
      menu[select][0] = '>';
      system("cls");
      for(i = 0; i<4; i++){
         printf("\n");
         for(j = 0; j<11; j++){
            printf("%c", menu[i][j]);
         }
      }
   }
}
//-----------------------TELA_LOJA----------------------------------------
void loja(ppersonagem* jogador){
   char itens[7][15] = {{' ','C','O','M','I','D','A',' ',' ',' ',' ',' ',' ',' ',' '},
                        {' ','R','O','U','P','A','S',' ','D','A',' ','M','O','D','A'},
                        {' ','R','E','M','E','D','I','O','S',' ',' ',' ',' ',' ',' '},
                        {' ','V','I','A','G','E','M',' ',' ',' ',' ',' ',' ',' ',' '},
                        {' ','H','I','G','I','E','N','E',' ','B','A','S','I','C','A'},
                        {' ','J','A','N','T','A','R',' ','F','O','R','A',' ',' ',' '},
                        {' ','S','A','I','R',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}};
   int i, j, aux = 0;
   int saida=0;
   char escolha;
   float qnt;
   while (saida == 0){
      system("cls");
      for(i=0;i<7;i++){
         itens[i][0] = ' ';
      }
      itens[aux][0] = '>';
      printf("Loja .:\n");
      for(j=0;j<7;j++){
         printf("%c",itens[0][j]);
      }
      printf ("\t\t\tPRECO .: R$15\n +15 FOME\n");
      delimitaLinha();
      printf("\n");
      for(j=0;j<15;j++){
         printf("%c",itens[1][j]);
      }
      printf ("\t\tPRECO .: R$45\n +20 FELICIDADE\n");
      delimitaLinha();
      printf("\n");
      for(j=0;j<9;j++){
         printf("%c",itens[2][j]);
      }
      printf ("\t\tPRECO .: R$100\n +40 VIDA\n");
      delimitaLinha();
      printf("\n");
      for(j=0;j<7;j++){
         printf("%c",itens[3][j]);
      }
      printf ("\t\t\tPRECO .: R$350\n +100 FELICIDADE\n");
      delimitaLinha();
      printf("\n");
      for(j=0;j<15;j++){
         printf("%c",itens[4][j]);
      }
      printf ("\t\tPRECO .: R$25\n +5 VIDA \t +10 FELICIDADE\n");
      delimitaLinha();
      printf("\n");
      for(j=0;j<12;j++){
         printf("%c",itens[5][j]);
      }
      printf ("\t\tPRECO .: R$90\n +25 FOME \t +15 FELICIDADE\n");
      delimitaLinha();
      printf("\n");
      for(j=0;j<5;j++){
         printf("%c",itens[6][j]);
      }
      printf("\n");
      escolha = getch();
      if(escolha == CIMA){
         if(aux == 0){
            aux = 6;
         }
         else{
            aux --;
         }
      }else if(escolha == BAIXO){
         if(aux == 6){
            aux = 0;
         }
         else{
            aux ++;
         }
      }
      if(escolha == ENTER){
         switch(aux+1){
            case 1:
               system("cls");
               printf("QUANTOS ITENS DESEJA COMPRAR .:");
               scanf("%f",&qnt);
               jogador->dinheiro = jogador->dinheiro - (15*qnt);
               if (jogador->fome < 100){
                  jogador->fome = jogador->fome + (15*qnt);
                  if (jogador->fome > 100){
                     jogador->fome = 100;
                  }
               }
               break;
            case 2:
               system("cls");
               printf("QUANTOS ITENS DESEJA COMPRAR .:");
               scanf("%f",&qnt);
               jogador->dinheiro = jogador->dinheiro - (45*qnt);
               if (jogador->felicidade < 100){
                  jogador->felicidade = jogador->felicidade + (20*qnt);
                  if (jogador->felicidade > 100){
                     jogador->felicidade = 100;
                  }
               }
               break;
            case 3:
               system("cls");
               printf("QUANTOS ITENS DESEJA COMPRAR .:");
               scanf("%f",&qnt);
               jogador->dinheiro = jogador->dinheiro - (100*qnt);
               if (jogador->vida < 100){
                  jogador->vida = jogador->vida + (40*qnt);
                  if (jogador->vida > 100){
                     jogador->vida = 100;
                  }
               }
               break;
            case 4:
               system("cls");
               printf("QUANTOS ITENS DESEJA COMPRAR .:");
               scanf("%f",&qnt);
               jogador->dinheiro = jogador->dinheiro - (350*qnt);
               if (jogador->felicidade < 100){
                  jogador->felicidade = jogador->felicidade + (100*qnt);
                  if (jogador->felicidade > 100){
                     jogador->felicidade = 100;
                  }
               }
               break;
            case 5:
               system("cls");
               printf("QUANTOS ITENS DESEJA COMPRAR .:");
               scanf("%f",&qnt);
               jogador->dinheiro = jogador->dinheiro - (25*qnt);
               if (jogador->felicidade < 100){
                  jogador->felicidade = jogador->felicidade + (10*qnt);
                  if (jogador->felicidade > 100){
                     jogador->felicidade = 100;
                  }
               }
               if (jogador->vida < 100){
                  jogador->vida = jogador->vida + (5*qnt);
                  if (jogador->vida > 100){
                     jogador->vida = 100;
                  }
               }
               break;
            case 6:
               system("cls");
               printf("QUANTOS ITENS DESEJA COMPRAR .:");
               scanf("%f",&qnt);
               jogador->dinheiro = jogador->dinheiro - (90*qnt);
               if (jogador->felicidade < 100){
                  jogador->felicidade = jogador->felicidade + (15*qnt);
                  if (jogador->felicidade > 100){
                     jogador->felicidade = 100;
                  }
               }
               if (jogador->fome < 100){
                  jogador->fome = jogador->fome + (25*qnt);
                  if (jogador->fome > 100){
                     jogador->fome = 100;
                  }
               }
               break;
            case 7:
               saida = 1;
               break;
         }
      }
   }
}
//-----------------------TELA_FIMJOGO----------------------------------------
void gameover (ppersonagem* personagem){
      //---------------------------------------------------------------------------------------
      char miyagiMorto[13][13] = {{0,219,219,219,219,219,219,219,219,219,219,219,0},
      {0,219,0,0,0,0,0,0,0,0,0,219,0},
      {0,178,178,178,178,158,158,158,178,178,178,178,0},
      {177,219,0,0,0,0,0,0,0,0,0,219,177},
      {177,219,0,0,88,0,0,0,88,0,0,219,177},
      {177,219,0,0,0,0,0,0,0,0,0,219,177},
      {0,219,0,0,0,0,0,0,0,0,0,219,0},
      {0,219,0,177,177,177,177,177,177,177,0,219,0},
      {0,219,0,177,0,0,0,0,0,177,0,219,0},
      {0,219,219,177,177,177,177,177,177,177,219,219,0},
      {0,0,0,177,177,177,177,177,177,177,0,0,0},
      {0,0,0,0,177,177,177,177,177,0,0,0,0},
      {0,0,0,0,0,177,177,177,0,0,0,0,0}};
      //---------------------------------------------------------------------------------------
      char vacaMorto[13][13] = {{0,0,219,0,0,0,0,0,0,0,219,0,0},
      {0,0,219,219,0,0,0,0,0,219,219,0,0},
      {0,0,219,0,219,0,0,0,219,0,219,0,0},
      {0,0,219,0,0,219,219,219,0,0,219,0,0},
      {219,219,219,0,0,0,0,0,0,0,219,219,219},
      {0,219,0,0,88,0,0,0,88,0,0,219,0},
      {0,0,219,0,0,0,0,0,0,0,219,0,0},
      {0,0,219,0,0,0,0,0,0,0,219,0,0},
      {0,0,219,177,177,177,177,177,177,177,219,0,0},
      {0,0,177,177,219,177,177,177,219,177,177,0,0},
      {0,0,0,177,177,177,177,177,177,177,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0}};
      //---------------------------------------------------------------------------------------
      char slimeMorto[13][13] = {{0,0,0,0,0,0,219,0,0,0,0,0,0},
      {0,0,0,0,0,219,0,219,0,0,0,0,0},
      {0,0,0,0,0,219,0,219,0,0,0,0,0},
      {0,0,0,219,219,0,0,0,219,219,0,0,0},
      {0,0,219,0,0,0,0,0,0,0,219,0,0},
      {0,219,0,0,0,0,0,0,0,0,0,219,0},
      {219,0,0,0,88,0,0,0,88,0,0,0,219},
      {219,0,0,0,0,0,0,0,0,0,0,0,219},
      {0,219,0,0,0,0,0,0,0,0,0,219,0},
      {0,0,219,219,0,0,0,0,0,219,219,0,0},
      {0,0,0,0,219,219,219,219,219,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0}};
      int i = 0;
      int j = 0;
      if (personagem->vida <= 0 || personagem->dinheiro < 50){
      if(personagem->id == 0) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", slimeMorto[i][j]);
            }
         }
      }
      if(personagem->id == 1) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", vacaMorto[i][j]);
            }
         }
      }
      if(personagem->id == 2) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", miyagiMorto[i][j]);
            }
         }
      }
      printf("\n\t\tGAMEOVER !!!!");
      exit(0);
   }
}
//-----------------------CHECKS_STATUS_PERSONAGEM----------------------------------------
void checagem (ppersonagem* personagem){
   if(personagem->felicidade <= 20){
      personagem->vida -= 10;
      if(personagem->vida < 0){
         personagem->vida = 0;
      }
   }
   if(personagem->fome <= 30){
      personagem->vida -= 5;
      if(personagem->vida < 0){
         personagem->vida = 0;
      }
   }
}
//-----------------------RANDOM_SEGUNDO_MINIJOGO----------------------------------------
int rng(){
   int r = (rand()%10) +1;
   return r;
}
//-----------------------RANDOM_TERCEIRO_MINIJOGO----------------------------------------
int rnga(){
   return rand()%3;
}
//-----------------------BD_TERCEIRO_MINIJOGO----------------------------------------
void monster(monstro*mob, int mons){
   if(mons == 0){
      strcpy (mob->nome,"DEBITO");
      mob->vida = 70;
      mob->dano = 9;
   }else if(mons == 1){
      strcpy (mob->nome,"DESPESAS");
      mob->vida = 25;
      mob->dano = 3;
   }else{
      strcpy (mob->nome,"DIVIDA");
      mob->vida = 40;
      mob->dano = 6;
   }
}
//-----------------------TERCEIRO_MINIJOGO----------------------------------------
int batalha(ppersonagem *personagem){
   int i = 0;
   int j = 0;
   system("cls");
   monstro* mob = (monstro*)malloc(sizeof(monstro));
   char atk[2][20] = {{' ','P','A','G','A','M','E','N','T','O',' ','P','A','R','C','E','L','A','D','O'},
   {' ','P','A','G','A','M','E','N','T','O',' ','A',' ','V','I','S','T','A',' ',' '}};
   int mons, contador2 = 0;
   int aux1, aux2, opcao = 0;
   char opt;
   srand((unsigned)time(NULL));
   mons = rnga();
   monster(mob,mons);
   while(personagem->vida > 0 && mob->vida > 0){
      for(i=0;i<2;i++){
         atk[i][0] = ' ';
      }
      atk[opcao][0] = '>';
      printf("\n\n\n\n\n");
      printf("\t ");
      if(personagem->id == 0){
         printf("%c", 30);
      }
      if(personagem->id == 1){
         printf("%c", 20);
      }
      if(personagem->id == 2){
         printf("%c", 258);
      }
      printf("\t\t\t\t");
      printf("%c", 209);
      printf("\n\tVOCE");
      printf("\t\t\t\tNome %s\n",mob->nome);
      printf("\tVida %d",personagem->vida);
      if(personagem->vida == 100){
         printf("\t\t\tVida %d\n",mob->vida);
      }else{
         printf("\t\t\t\tVida %d\n",mob->vida);
      }
      printf("\n\n\t\t    ");
      for(i=0;i<20;i++){
         printf("%c",atk[0][i]);
      }
      printf("\n");
      printf("\n\t\t    ");
      if (contador2 == 0){
         for(i=0;i<20;i++){
            printf("%c",atk[1][i]);
         }
      }
      printf ("\n");
      opt = getch();
      if (opt == CIMA){
         if (contador2 != 0){
            opcao = 0;
         }else if (opcao == 0){
            opcao = 1;
         }else{
            opcao --;
         }
      }else if (opt == BAIXO){
         if (contador2 != 0){
            opcao = 0;
         }else if (opcao == 1){
            opcao = 0;
         }else{
            opcao ++;
         }
      }
      if (opt == ENTER){
         switch(opcao){
            case 0:
               if (contador2 == 0){
                  contador2 = 0;
               }
               else{
                  contador2 --;
               }
               aux1 = (personagem->dinheiro*1)*rnga();
               aux1 = aux1/10;
               printf("\a");
               break;
            case 1:
               contador2 = 2;
               opcao = 0;
               aux1 = (personagem->dinheiro*2)*rnga();
               aux1 = aux1/10;
               printf("\a");
               break;
         }
         aux2 =  mob->dano*rnga();
         mob->vida = mob->vida - aux1;
         sleep(1);
         personagem->vida = personagem->vida - aux2;
      }
      system("cls");
   }
   if(personagem->vida > 0)
      personagem->dinheiro = personagem->dinheiro + 150;
   return 0;
}
//-----------------------SEGUNDO_MINIJOGO----------------------------------------
void questao(ppersonagem* personagem){
   char qst[2][10] = {{'0','1','2','3','4','5','6','7','8','9'},
                     {'a','c','b','c','a','c','b','c','b','c'}};
   char ans;
   int per;
   personagem->dinheiro = personagem->dinheiro - 30;
   printf("***QUIZ FINANCEIRO***");
   printf("\nACERTE UMA QUESTAO E GANHE MOEDAS\n");
   per = rng();
   mostquestao(per);
   printf ("\nDIGITE A RESPOSTA EM MINUSCULO .: ");
   ans = getche();
   if(ans == qst[1][per-1]){
      printf ("\nACERTOU\n ");
      printf("\a");
      personagem->dinheiro = personagem->dinheiro + 50;
   }
   else{
      printf ("\nERROU\n ");
   }
   system("PAUSE");
   system("cls");
}
//-----------------------BD_QUESTOES----------------------------------------
void mostquestao(int per){
   if (per == 1 ){
      printf("1 - COMO CONTROLAR GASTOS ?");
      printf("\n");
      printf("\na: FAZENDO PLANILHAS DE GASTOS");
      printf("\nb: FAZENDO AQUISICOES");
      printf("\nc: ESTABELECENDO UMA DIVIDA");
      printf("\n");
   }
   if(per == 2){
      printf("2 - O QUE E PRIORIZAR GASTOS ?");
      printf("\n");
      printf("\na: GASTAR COM ITENS QUE SENTE VONTADE COMPRAR");
      printf("\nb: USAR O DINHEIRO SOMENTE COM NECESSIDADES");
      printf("\nc: UTILIZAR PARA NECESSIDADES E SE PLANEJAR PARA OUTROS GASTOS");
      printf("\n");
   }
   if(per == 3){
      printf("3 - O QUE E MESADA ?");
      printf("\n");
      printf("\na: PAGAMENTO DE UM OU MAIS ITENS DE UM ESTABELECIMENTO");
      printf("\nb: VALOR ACORDADO ENTRE PAIS E FILHOS QUE SERA REGULARMENTE");
      printf("\nc: E UM METODO ONDE SE PREVE TER REDUCAO DE GASTOS");
      printf("\n");
   }
   if(per == 4){
      printf("4 - O QUE E FINANCIAMENTO ?");
      printf("\n");
      printf("\na: DIVISAO DO PRECO DE UMA COMPRA ");
      printf("\nb: DINHEIRO EMPRESTADO DE ALGUEM");
      printf("\nc: E QUANDO UMA INSTITUICAO FORNECE RECURSOS PARA UMA PESSOA NA FINALIDADE ESPECIFICA DE ADQUIRIR UM ITEM");
      printf("\n");
   }
   if(per == 5){
      printf("5 - POR QUE FAZER REGISTRO DOS GASTOS ?");
      printf("\n");
      printf("\na: SABER COMO O DINHEIRO ESTA SENDO GASTO E QUAIS GASTOS PODEM SER CORTADOS ");
      printf("\nb: REGISTRAR A QUANTIDADE DE DINHEIRO GANHA EM UM MES, VISANDO SOMENTE OS GANHOS");
      printf("\nc: UTILIZAR PARA TER UMA NOCAO DE GANHOS MENSAIS");
   }
   if(per == 6){
      printf("6 - QUAL DOS SEGUINTES JOGOS PODE ENSINAR EDUCACAO FINANCEIRA ?");
      printf("\n");
      printf("\na: XADREZ ");
      printf("\nb: GAMAO");
      printf("\nc: BANCO IMOBILIARIO");
   }
   if(per == 7){
      printf("7 - O QUE SIGNIFICA TER UM OBJETIVO FINANCEIRO ?");
      printf("\n");
      printf("\na: ESTABELECER UM VALOR PARA DETERMINADO ITEM");
      printf("\nb: TER UMA META PARA COMPRAR DETERMINADO ITEM");
      printf("\nc: UTILIZAR MAIS DINHEIRO QUE O NECESSARIO");
   }
   if(per == 8){
      printf("8 - O QUE E AQUISICAO ?");
      printf("\n");
      printf("\na: GUARDAR MAIS DINHEIRO");
      printf("\nb: ACORDO PARA RECEBER DINHEIRO");
      printf("\nc: ADQUIRIR ALGUM ITEM");
   }
   if(per == 9){
      printf("9 - O QUE DEVE SER PRIOZADO QUANTO A GASTOS ?");
      printf("\n");
      printf("\na: LAZER");
      printf("\nb: GASTOS ESSENCIAIS");
      printf("\nc: INVESTIMENTO A LONGO PRAZO");
   }
   if(per == 10){
      printf("10 - RECENTEMENTE, VOCE ADQUIRIU UM TENIS NOVO, POREM, VOCE PASSA NA FRENTE DE OUTRA LOJA E VE UM TENIS QUE ESTA NA MODA E SENTE VONTA DE EM COMPRAR ELE MESMO TENDO POUCO DINHEIRO, O QUE FAZER ?");
      printf("\n");
      printf("\na: PAGAR DE FORMA PARCELADA");
      printf("\nb: COMPRAR O PRODUTO A VISTA");
      printf("\nc: ESPERAR A SITUACAO MELHORAR");
   }
}
//-----------------------TELA_ABERTURA----------------------------------------
void abertura(){
   //---------------------------------------------------------------------------------------
   char abertura[8][25] = {{219,219,219,219,219,219,219,219,0,0,0,0,0,0,0,0,0,0,0,0,0,0,219,219,219},
   {0,0,0,219,0,0,219,0,0,219,0,0,0,219,0,0,219,0,0,0,0,219,0,0,0},
   {0,0,0,219,0,219,0,219,0,219,219,0,219,219,0,219,0,219,0,0,0,219,0,0,0},
   {0,0,0,219,0,219,219,219,0,219,0,219,0,219,0,219,219,219,0,0,0,219,0,0,0},
   {0,0,0,219,0,219,0,219,0,219,0,0,0,219,0,219,0,219,0,0,0,0,219,219,219}};
   //---------------------------------------------------------------------------------------
   int i = 0;
   int j = 0;
   printf("\n\n\n\n\n\n");
   for(i = 0; i < 8; i++){
      printf("\n");
      printf("\t\t\t");
      for(j = 0; j < 25; j++){
         printf("%c", abertura[i][j]);
      }
   }
   printf("\n\t\t\t\tPRESS START...");
   printf("\n\n\n\n\n\n");
   system("pause");
   system("cls");
   printf("\n\n\n\n\n\n");
   for(i = 0; i < 8; i++){
      printf("\n");
      printf("\t\t\t");
      for(j = 0; j < 25; j++){
         printf("%c", abertura[i][j]);
      }
   }
   printf("\n\t\t\t");
   for(i = 0; i < 28; i++){
      printf("%c",219);       //for para fazer o carregando
      Sleep(100);            //Precisa da windows.h pra funcionar
   }
   printf("\a");
   printf("\n\n\n\n\n\n");
   system("cls");
}
//-----------------------MAIN----------------------------------------
int main(){
   //---------------------------------------------------------------------------------------
   char miyagi[13][13] = {{0,219,219,219,219,219,219,219,219,219,219,219,0},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {0,178,178,178,178,158,158,158,178,178,178,178,0},
   {177,219,0,0,0,0,0,0,0,0,0,219,177},
   {177,219,0,220,220,0,0,0,220,220,0,219,177},
   {177,219,0,0,0,0,0,0,0,0,0,219,177},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {0,219,0,177,177,177,177,177,177,177,0,219,0},
   {0,219,0,177,0,0,0,0,0,177,0,219,0},
   {0,219,219,177,177,177,177,177,177,177,219,219,0},
   {0,0,0,177,177,177,177,177,177,177,0,0,0},
   {0,0,0,0,177,177,177,177,177,0,0,0,0},
   {0,0,0,0,0,177,177,177,0,0,0,0,0}};
   //---------------------------------------------------------------------------------------
   char vaca[13][13] = {{0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,0,219,219,0,0,0,0,0,219,219,0,0},
   {0,0,219,0,219,0,0,0,219,0,219,0,0},
   {0,0,219,0,0,219,219,219,0,0,219,0,0},
   {219,219,219,0,0,0,0,0,0,0,219,219,219},
   {0,219,0,0,219,0,0,0,219,0,0,219,0},
   {0,0,219,0,219,0,0,0,219,0,219,0,0},
   {0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,0,219,177,177,177,177,177,177,177,219,0,0},
   {0,0,177,177,219,177,177,177,219,177,177,0,0},
   {0,0,0,177,177,177,177,177,177,177,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0}};
   //---------------------------------------------------------------------------------------
   char slime[13][13] = {{0,0,0,0,0,0,219,0,0,0,0,0,0},
   {0,0,0,0,0,219,0,219,0,0,0,0,0},
   {0,0,0,0,0,219,0,219,0,0,0,0,0},
   {0,0,0,219,219,0,0,0,219,219,0,0,0},
   {0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {219,0,0,0,219,0,0,0,219,0,0,0,219},
   {219,0,0,0,219,0,0,0,219,0,0,0,219},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {0,0,219,219,0,0,0,0,0,219,219,0,0},
   {0,0,0,0,219,219,219,219,219,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0}};
   //---------------------------------------------------------------------------------------
   //-------------------------------------SPRITES2------------------------------------------
   //---------------------------------------------------------------------------------------
   char miyagi2[13][13] = {{0,219,219,219,219,219,219,219,219,219,219,219,0},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {0,178,178,178,178,158,158,158,178,178,178,178,0},
   {177,219,0,0,0,0,0,0,0,0,0,219,177},
   {177,219,0,196,196,0,0,0,196,196,0,219,177},
   {177,219,0,0,0,0,0,0,0,0,0,219,177},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {0,219,0,177,177,177,177,177,177,177,0,219,0},
   {0,219,0,177,0,0,0,0,0,177,0,219,0},
   {0,219,219,177,177,177,177,177,177,177,219,219,0},
   {0,0,0,177,177,177,177,177,177,177,0,0,0},
   {0,0,0,0,177,177,177,177,177,0,0,0,0},
   {0,0,0,0,0,177,177,177,0,0,0,0,0}};
   //---------------------------------------------------------------------------------------
   char vaca2[13][13] = {{0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,0,219,219,0,0,0,0,0,219,219,0,0},
   {0,0,219,0,219,0,0,0,219,0,219,0,0},
   {0,0,219,0,0,219,219,219,0,0,219,0,0},
   {219,219,219,0,0,0,0,0,0,0,219,219,219},
   {0,219,0,0,219,0,0,0,219,0,0,219,0},
   {0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,0,219,177,177,177,177,177,177,177,219,0,0},
   {0,0,177,177,219,177,177,177,219,177,177,0,0},
   {0,0,0,177,177,177,177,177,177,177,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0}};
   //---------------------------------------------------------------------------------------
   char slime2[13][13] = {{0,0,0,0,0,0,0,219,0,0,0,0,0},
   {0,0,0,0,0,0,219,0,219,0,0,0,0},
   {0,0,0,0,0,219,0,219,0,0,0,0,0},
   {0,0,0,219,219,0,0,0,219,219,0,0,0},
   {0,0,219,0,0,0,0,0,0,0,219,0,0},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {219,0,0,0,219,0,0,0,219,0,0,0,219},
   {219,0,0,0,0,0,0,0,0,0,0,0,219},
   {0,219,0,0,0,0,0,0,0,0,0,219,0},
   {0,0,219,219,0,0,0,0,0,219,219,0,0},
   {0,0,0,0,219,219,219,219,219,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0}};
   int i = 0;
   int j = 0;
   char c;
   int s = 1;
   abertura();
   srand((unsigned)time(NULL));
   ppersonagem* personagem;
   personagem = (ppersonagem*) malloc(sizeof(ppersonagem));
   personagem->id = intro();
   personagem->dinheiro = 100;
   personagem->vida = 100;
   personagem->fome = 100;
   personagem->felicidade = 100;
   while(s != 0){
      system("cls");
      gameover(personagem);
      checagem(personagem);
      delimitaLinha();
      printf("\n   VIDA: %d       DINHEIRO: R$%.2f      ",personagem->vida, personagem->dinheiro);
      printf("\n   FOME: %d       FELICIDADE: %d         ",personagem->fome, personagem->felicidade);
      delimitaLinha();
      if(personagem->id == 0) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", slime[i][j]);
            }
         }
      }
      if(personagem->id == 1) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", vaca[i][j]);
            }
         }
      }
      if(personagem->id == 2) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", miyagi[i][j]);
            }
         }
      }
      delimitaLinha();
      printf("\n|  1-LOJA   2-JOGOS  3-BRINCAR   4-SAIR     |");
      delimitaLinha();
      printf("\n");
      c = getch();
      switch(c){
         case '1':
            loja(personagem);
            break;
         case '2':
            miniGames(personagem);
            break;
         case '3':
            personagem->felicidade += 1;
            personagem->fome -= 1;
            printf("\a");
            break;
         case '4':
            return 0;
            break;
         default:
            break;
      }
      system("cls");
      delimitaLinha();
      printf("\n   VIDA: %d       DINHEIRO: R$%.2f      ",personagem->vida, personagem->dinheiro);
      printf("\n   FOME: %d       FELICIDADE: %d         ",personagem->fome, personagem->felicidade);
      delimitaLinha();
      if(personagem->id == 0) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", slime2[i][j]);
            }
         }
      }
      if(personagem->id == 1) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", vaca2[i][j]);
            }
         }
      }
      if(personagem->id == 2) {
         for(i = 0; i < 13; i++){
            printf("\n");
            printf("\t\t");
            for(j = 0; j < 13; j++){
               printf("%c", miyagi2[i][j]);
            }
         }
      }
      delimitaLinha();
      printf("\n|  1-LOJA   2-JOGOS  3-BRINCAR   4-SAIR     |");
      delimitaLinha();
      sleep(1);
   }
   return 0;
}
