#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

enum COLORS {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

enum BACKGROUND_COLORS {
    _BLACK = 0,
    _BLUE = 16,
    _GREEN = 32,
    _CYAN = 48,
    _RED = 64,
    _MAGENTA = 80,
    _BROWN = 96,
    _LIGHTGRAY = 112,
    _DARKGRAY = 128,
    _LIGHTBLUE = 144,
    _LIGHTGREEN = 160,
    _LIGHTCYAN = 176,
    _LIGHTRED = 192,
    _LIGHTMAGENTA = 208,
    _YELLOW = 224,
    _WHITE = 240
};

void TextColor(int letras, int fundo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + fundo);
}

void ResetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | _BLACK);
}

void linhaCol(int lin, int col) {
    COORD coord;
    coord.X = col - 1;
    coord.Y = lin - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fun��o para desenhar uma caixa (box) no console
void box(int lin1, int col1, int lin2, int col2) {
    const char HORIZONTAL = 196; // -
    const char VERTICAL = 179;   // �
    const char TOP_LEFT = 218;   // +
    const char TOP_RIGHT = 191;  // +
    const char BOTTOM_LEFT = 192;// +
    const char BOTTOM_RIGHT = 217;// +

    int i;

    // Linhas horizontais
    for (i = col1; i <= col2; i++) {
        linhaCol(lin1, i);
        printf("%c", HORIZONTAL);
        linhaCol(lin2, i);
        printf("%c", HORIZONTAL);
    }

    // Linhas verticais
    for (i = lin1; i <= lin2; i++) {
        linhaCol(i, col1);
        printf("%c", VERTICAL);
        linhaCol(i, col2);
        printf("%c", VERTICAL);
    }

    // Cantos
    linhaCol(lin1, col1);
    printf("%c", TOP_LEFT);
    linhaCol(lin1, col2);
    printf("%c", TOP_RIGHT);
    linhaCol(lin2, col1);
    printf("%c", BOTTOM_LEFT);
    linhaCol(lin2, col2);
    printf("%c", BOTTOM_RIGHT);
}

// Fun��o para criar um menu
int menu(int lin1, int col1, int qtd, char lista[][40]) {
    int opc = 1;
    int lin2, col2, linha, i, tamMaxitem, tecla;

    tamMaxitem = strlen(lista[0]);

    for (i = 1; i < qtd; i++) {
        if (strlen(lista[i]) > tamMaxitem) {
            tamMaxitem = strlen(lista[i]);
        }
    }

    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxitem + 4;

    TextColor(WHITE, _BLUE);
    setlocale(LC_ALL, "C");
    box(lin1, col1, lin2, col2);
    setlocale(LC_ALL, "");

    while (1) {
        linha = lin1 + 2;
        for (i = 0; i < qtd; i++) {
            if (i + 1 == opc)
                TextColor(BLACK, _LIGHTGREEN);
            else
                TextColor(WHITE, _BLUE);

            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        linhaCol(1, 1);
        tecla = getch();

        // Controle do menu com as setas do teclado
        if (tecla == 80) { // Seta para baixo
            opc++;
            if (opc > qtd) opc = 1;
        } else if (tecla == 72) { // Seta para cima
            opc--;
            if (opc < 1) opc = qtd;
        } else if (tecla == 13) { // Enter
            return opc;
        }
    }
}

int main() {
    int opc;
    char lista[3][40] = {"Cadastrar", "Alterar", "Excluir"};

    setlocale(LC_ALL, "");
    while (1) {
        opc = menu(10, 10, 3, lista);

        linhaCol(24, 1);
        TextColor(WHITE, _BLACK);
        printf("Op��o escolhida: %d\n\t", opc);
        break; // Finaliza o loop ap�s selecionar
    }

    ResetColor();
    return 0;
}

