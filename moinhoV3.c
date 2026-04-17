#include <stdio.h>

int tabuleiro[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int vizinhos[24][4] = { // Vizinhos de cada posicao:
    {1, 9, -1, -1},     // 00
    {0, 2, 4, -1},      // 01
    {1, 14, -1, -1},    // 02
    {4, 10, -1, -1},    // 03
    {3, 5, 1, 7},       // 04
    {4, 13, -1, -1},    // 05
    {7, 11, -1, -1},    // 06
    {6, 8, 4, -1},      // 07
    {7, 12, -1, -1},    // 08
    {0, 10, 21, -1},    // 09
    {9, 11, 3, 18},     // 10
    {10, 6, 15, -1},    // 11
    {8, 13, 17, -1},    // 12
    {12, 14, 5, 20},    // 13
    {13, 2, 23, -1},    // 14
    {11, 16, -1, -1},   // 15
    {15, 17, 19, -1},   // 16
    {16, 12, -1, -1},   // 17
    {10, 19, -1, -1},   // 18
    {18, 20, 16, 22},   // 19
    {19, 13, -1, -1},   // 20
    {9, 22, -1, -1},    // 21
    {21, 23, 19, -1},   // 22
    {22, 14, -1, -1},   // 23
};


int moinhos[16][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {9, 10, 11},
    {12, 13, 14},
    {15, 16, 17},
    {18, 19, 20},
    {21, 22, 23},
    {0, 9, 21},
    {3, 10, 18},
    {6, 11, 15},
    {1, 4, 7},
    {16, 19, 22},
    {8, 12, 17},
    {5, 13, 20},
    {2, 14, 23},
};

char sinal(int pos){
    if(tabuleiro[pos] == 1)
        return 'X';
    if(tabuleiro[pos] == 2)
        return 'O';
    return '#';
}

void imprimir_tabuleiro(void) {
    printf("\n             MOINHO\n\n");
    printf("  %c------------%c------------%c\n", sinal(0), sinal(1), sinal(2));
    printf("  |            |            |\n");
    printf("  |   %c--------%c--------%c   |\n", sinal(3), sinal(4), sinal(5));
    printf("  |   |        |        |   |\n");
    printf("  |   |   %c----%c----%c   |   |\n", sinal(6), sinal(7), sinal(8));
    printf("  |   |   |         |   |   |\n");
    printf("  %c---%c---%c         %c---%c---%c\n", sinal(9), sinal(10), sinal(11), sinal(12), sinal(13), sinal(14));
    printf("  |   |   |         |   |   |\n");
    printf("  |   |   %c----%c----%c   |   |\n", sinal(15), sinal(16), sinal(17));
    printf("  |   |        |        |   |\n");
    printf("  |   %c--------%c--------%c   |\n", sinal(18), sinal(19), sinal(20));
    printf("  |            |            |\n");
    printf("  %c------------%c------------%c\n\n", sinal(21), sinal(22), sinal(23));
    printf("  Jogador 1: X    Jogador 2: O\n\n");

    printf("          REFERENCIA\n\n");
    printf("  0------------1------------2\n");
    printf("  |            |            |\n");
    printf("  |   3--------4--------5   |\n");
    printf("  |   |        |        |   |\n");
    printf("  |   |   6----7----8   |   |\n");
    printf("  |   |   |         |   |   |\n");
    printf("  9---10--11        12--13--14\n");
    printf("  |   |   |         |   |   |\n");
    printf("  |   |   15---16---17  |   |\n");
    printf("  |   |        |        |   |\n");
    printf("  |   18-------19-------20  |\n");
    printf("  |            |            |\n");
    printf("  21-----------22-----------23\n\n");
}

int posicao_valida(int pos){
    return (pos >=0 && pos <= 23);
}

int posicao_vazia(int pos){
    return (tabuleiro[pos] == 0);
}

int vizinhos_validos(int vem, int vai){
    for(int i=0; i<4; i++)
        if(vizinhos[vem][i] == vai)
            return 1;
    return 0;
}

int moinho_valido(int jogador, int pos){
    for(int i=0; i<16; i++)
        for(int j=0; j<3; j++)
            if(moinhos[i][j] == pos)
                if(tabuleiro[moinhos[i][0]] == jogador && tabuleiro[moinhos[i][1]] == jogador && tabuleiro[moinhos[i][2]] == jogador)
                    return 1;
    return 0;
}

int todas_no_moinho(int oponente){
    for(int i=0; i<24; i++)
        if(tabuleiro[i] == oponente && !moinho_valido(oponente, i))
            return 0;
    return 1;
}

int bloqueado(int jogador){
    for(int i=0; i<24; i++)
        if(tabuleiro[i] == jogador)
            for(int j=0; j<4; j++)
                if(vizinhos[i][j] != -1 && posicao_vazia(vizinhos[i][j]))
                    return 0;
    return 1;
}

int verificar_vitoria(void){
    int cont1=0, cont2=0;
    for(int i=0; i<24; i++){
        if(tabuleiro[i] == 1)
            cont1++;
        if(tabuleiro[i] == 2)
            cont2++;
    }
    if(cont1<3 || bloqueado(1))
        return 2;
    if(cont2<3 || bloqueado(2))
        return 1;
    return 0;
}

int colocar_peca(int jogador){
    int pos;

    do{
        imprimir_tabuleiro();

        printf("\nJogador %d, escolha uma posicao: ", jogador);
        while(scanf("%d", &pos) != 1){
            printf("Digite um valor inteiro: ");
            while (getchar() != '\n');
        }

        if(!posicao_valida(pos))
        printf("\nPosicao invalida! Escolha outra: \n");
        else if(!posicao_vazia(pos))
            printf("\nPosicao ocupada! Escolha outra: \n");

    } while(!posicao_valida(pos) || !posicao_vazia(pos));

    tabuleiro[pos] = jogador;
    return pos;
}

void remover_peca(int jogador){
    int pos, oponente=1;

    if(jogador==1)
        oponente = 2;

    do{
        imprimir_tabuleiro();

        printf("\nJogador %d, escolha uma peca para remover: ", jogador);
        while(scanf("%d", &pos) != 1){
            printf("Digite um valor inteiro: ");
            while (getchar() != '\n');
        }

        if(!posicao_valida(pos))
            printf("Posicao invalida! Escolha outra: \n");
        else if(tabuleiro[pos] != oponente)
            printf("Nenhuma peca do oponente aqui! Escolha outra: \n");
        else if(moinho_valido(oponente, pos) && !todas_no_moinho(oponente))
            printf("Peca esta em moinho! Escolha outra: \n");
    } while(!posicao_valida(pos) || tabuleiro[pos] != oponente || (moinho_valido(oponente, pos) && !todas_no_moinho(oponente)));
    tabuleiro[pos] = 0;
}

int mover_peca(int jogador){
    int posA, posB = -1;

    do{
        imprimir_tabuleiro();

        printf("Jogador %d, escolha uma peca para mover: ", jogador);
        while(scanf("%d", &posA) != 1){
            printf("Digite um valor inteiro: ");
            while (getchar() != '\n');
        }

        if(!posicao_valida(posA))
            printf("Posicao invalida!\n");
        else if(tabuleiro[posA] != jogador)
            printf("Nao e sua peca para mover!");
    } while(!posicao_valida(posA) || tabuleiro[posA] != jogador);

    do{
        printf("Escolha a posicao valida: ");
        while(scanf("%d", &posB) != 1){
            printf("Digite um valor inteiro: ");
            while (getchar() != '\n');
        }
        if(!posicao_valida(posB))
            printf("Posicao e invalida!\n");
        else if(!posicao_vazia(posB))
            printf("Posicao ocupada!\n");
        else if(!vizinhos_validos(posA, posB))
            printf("Nao sao vizinhos!\n");
    } while(!posicao_valida(posB) || !posicao_vazia(posB) || !vizinhos_validos(posA, posB));

    tabuleiro[posB] = jogador;
    tabuleiro[posA] = 0;

    return posB;
}

int main(){
    int jogador = 1, pos, vencedor;

    for(int i=0; i<18; i++){
        pos = colocar_peca(jogador);
        if(moinho_valido(jogador, pos))
            remover_peca(jogador);
        jogador = (jogador==1) ? 2:1;
    }

    do{
        pos = mover_peca(jogador);
        if(moinho_valido(jogador, pos))
            remover_peca(jogador);
        vencedor = verificar_vitoria();
        jogador = (jogador==1) ? 2:1;
    } while(vencedor == 0);

    printf("\n\nO vencedor é o Jogador %d !!!\n\n", vencedor);

    return 0;
}
