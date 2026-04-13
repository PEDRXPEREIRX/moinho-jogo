#include <stdio.h>

int tabuleiro[24] = {0};

int vizinhos[24][4] = {
    {1,  9, -1, -1},
    {0,  2,  4, -1},
    {1, 14, -1, -1},
    {4, 10, -1, -1},
    {3,  5,  1,  7},
    {4, 13, -1, -1},
    {7, 11, -1, -1},
    {6,  8,  4, -1},
    {7, 12, -1, -1},
    {0, 10, 21, -1},
    {9, 11,  3, 18},
    {10,  6, 15, -1},
    {8, 13, 17, -1},
    {12, 14,  5, 20},
    {13,  2, 23, -1},
    {11, 16, -1, -1},
    {15, 17, 19, -1},
    {16, 12, -1, -1},
    {10, 19, -1, -1},
    {18, 20, 16, 22},
    {19, 13, -1, -1},
    {9, 22, -1, -1},
    {21, 23, 19, -1},
    {22, 14, -1, -1},
};


int moinhos[16][3] = {
    {0,  1,  2},
    {3,  4,  5},
    {6,  7,  8},
    {9, 10, 11},
    {12, 13, 14},
    {15, 16, 17},
    {18, 19, 20},
    {21, 22, 23},
    {0,  9, 21},
    {3, 10, 18},
    {6, 11, 15},
    {1,  4,  7},
    {16, 19, 22},
    {8, 12, 17},
    {5, 13, 20},
    {2, 14, 23},
};

char simbolo(int pos){
    if(tabuleiro[pos] == 1)
        return 'X';
    if(tabuleiro[pos] == 2)
        return 'O';
    return '@';
}

void imprimir_tabuleiro(void) {
    printf("\n          M O I N H O\n\n");
    printf("  %c------------%c------------%c\n", simbolo(0), simbolo(1), simbolo(2));
    printf("  |            |            |\n");
    printf("  |   %c--------%c---------%c  |\n", simbolo(3), simbolo(4), simbolo(5));
    printf("  |   |        |        |   |\n");
    printf("  |   |   %c----%c----%c   |   |\n", simbolo(6), simbolo(7), simbolo(8));
    printf("  |   |   |         |   |   |\n");
    printf("  %c---%c---%c         %c---%c---%c\n", simbolo(9), simbolo(10), simbolo(11), simbolo(12), simbolo(13), simbolo(14));
    printf("  |   |   |         |   |   |\n");
    printf("  |   |   %c----%c----%c   |   |\n", simbolo(15), simbolo(16), simbolo(17));
    printf("  |   |        |        |   |\n");
    printf("  |   %c--------%c---------%c  |\n", simbolo(18), simbolo(19), simbolo(20));
    printf("  |            |            |\n");
    printf("  %c------------%c------------%c\n\n", simbolo(21), simbolo(22), simbolo(23));
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
    printf("  |   |   15---16---17   |   |\n");
    printf("  |   |        |        |   |\n");
    printf("  |   18-------19-------20   |\n");
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
    else if(cont2<3 || bloqueado(2))
        return 1;
    else
        return 0;
}

int colocar_peca(int jogador){
    int pos;

    do{
        imprimir_tabuleiro();

        printf("\nJogador %d, escolha uma posicao: ", jogador);
        scanf("%d", &pos);

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
        scanf("%d", &pos);

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
    int posA, posB;

    do{
        imprimir_tabuleiro();

        printf("Jogador %d, escolha uma peca para mover: ", jogador);
        scanf("%d", &posA);
        printf("Agora escolha uma posicao valida: ");
        scanf("%d", &posB);

        if(!posicao_valida(posA))
            printf("Posicao invalida! Escolha outra: \n");
        else if(!vizinhos_validos(posA, posB))
            printf("Nao e vizinho! Escolha outra: \n");
        else if(tabuleiro[posA] != jogador)
            printf("Nao tem peca na posicao para troca! Escolha outra: ");
        else if(!posicao_vazia(posB))
            printf("Posicao ocupada! Escolha outra: \n");
    } while(!posicao_valida(posA) || !vizinhos_validos(posA, posB) || tabuleiro[posA] != jogador || !posicao_vazia(posB));
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
        if(jogador == 1)
            jogador = 2;
        else if(jogador == 2)
            jogador = 1;
    }

    do{
        mover_peca(jogador);
        if(moinho_valido(jogador, pos))
            remover_peca(jogador);
        vencedor = verificar_vitoria();
        if(jogador == 1)
            jogador = 2;
        else if(jogador == 2)
            jogador = 1;
    } while(vencedor == 0);

    printf("\n\nO vencedor é o Jogador %d !!!\n\n", vencedor);

    return 0;
}
