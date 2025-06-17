#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = VALOR_AGUA;
        }
    }
}

// Função para posicionar navio horizontal
void posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (coluna + i < TAM_TABULEIRO) {
            tabuleiro[linha][coluna + i] = VALOR_NAVIO;
        }
    }
}

// Função para posicionar navio vertical
void posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha + i < TAM_TABULEIRO) {
            tabuleiro[linha + i][coluna] = VALOR_NAVIO;
        }
    }
}

// Função para criar a matriz de habilidade em forma de cone
void criarHabilidadeCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE / 2 - i) && j <= (TAM_HABILIDADE / 2 + i)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar habilidade em forma de cruz
void criarHabilidadeCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar habilidade em forma de octaedro (losango)
void criarHabilidadeOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a matriz de habilidade ao tabuleiro
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                                   int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                                   int origemLinha, int origemColuna) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linhaTab = origemLinha + i - TAM_HABILIDADE / 2;
            int colTab = origemColuna + j - TAM_HABILIDADE / 2;
            if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                colTab >= 0 && colTab < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colTab] == VALOR_AGUA) {
                    tabuleiro[linhaTab][colTab] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == VALOR_AGUA)
                printf(". ");
            else if (tabuleiro[i][j] == VALOR_NAVIO)
                printf("N ");
            else if (tabuleiro[i][j] == VALOR_HABILIDADE)
                printf("* ");
            else
                printf("? ");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    posicionarNavioHorizontal(tabuleiro, 1, 2);  // Ex: linha 1, colunas 2-4
    posicionarNavioVertical(tabuleiro, 5, 7);    // Ex: coluna 7, linhas 5-7

    // Cone
    criarHabilidadeCone(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 2, 2);

    // Cruz
    criarHabilidadeCruz(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 5, 5);

    // Octaedro
    criarHabilidadeOctaedro(habilidade);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidade, 7, 2);

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
