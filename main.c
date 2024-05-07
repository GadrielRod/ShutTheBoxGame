#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

// Fun��o para gerar um n�mero aleat�rio entre min e max
int randRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Fun��o para exibir o tabuleiro com os n�meros dispon�veis
void displayBoard(bool numbers[]) {
    printf("  -------------\n");
    for (int i = 1; i <= 9; i++) {
        if (i == 4 || i == 7) {
            printf(" |-------------|\n");
        }
        if (numbers[i]) {
            printf(" |\x1b[36m %d \x1b[0m", i);
        } else {
            printf(" |\x1b[31m X \x1b[0m");
        }
        if (i == 3 || i == 6 || i == 9) {
            printf("|\n");
        }
    }
    printf("  -------------\n\v");
}

// Fun��o para verificar se o jogo acabou
bool isGameOver(bool numbers[], int targetSum) {
    for (int i = 1; i <= 9; i++) {
        if (numbers[i] && (i == targetSum || i + targetSum == 11)) {
            return false;
        }
        for (int j = i + 1; j <= 9; j++) {
            if (numbers[i] && numbers[j] && i + j == targetSum) {
                return false;
            }
        }
    }
    return true;
}

// Fun��o para jogar o jogo
void playGame() {
    bool numbers[10]; // Array para armazenar os n�meros dispon�veis
    srand(time(NULL)); // Seed para gera��o de n�meros aleat�rios

    // Inicializando o array de n�meros dispon�veis
    for (int i = 1; i <= 9; i++) {
        numbers[i] = true;
    }

    // Loop principal do jogo
    while (true) {
        int roll1 = rand() % 6 + 1;
        int roll2 = rand() % 6 + 1;
        int targetSum = roll1 + roll2;
        printf("\x1b[33mDados rolados: %d + %d = %d\x1b[0m\n", roll1, roll2, targetSum);

        displayBoard(numbers);

        bool validInput = false;
        int input1 = -1, input2 = -1;

        while (!validInput) {
            printf("\x1b[32mSelecione o primeiro n�mero para fechar: ");
            if (scanf("%d", &input1) != 1) {
                printf("\x1b[31mEntrada inv�lida. Insira um n�mero inteiro.\n");
                // Limpar o buffer de entrada
                while (getchar() != '\n');
                continue;
            }
            if (input1 == 0) {
                printf("\x1b[31mVoc� n�o pode pular a sele��o do primeiro n�mero.\n");
            } else if (numbers[input1]) {
                if (input1 == targetSum || numbers[targetSum - input1]) {
                    if (input1 == targetSum) {
                        numbers[input1] = false;
                        validInput = true;
                    } else {
                        printf("\x1b[32mEscolha o segundo n�mero para fechar: ");
                        if (scanf("%d", &input2) != 1) {
                            printf("\x1b[31mEntrada inv�lida. Insira um n�mero inteiro.\n");
                            // Limpar o buffer de entrada
                            while (getchar() != '\n');
                            continue;
                        }
                        if (input2 == 0) {
                            printf("Voc� n�o pode pular a sele��o do segundo n�mero.\n");
                        } else if ((numbers[targetSum - input1] && input2 == targetSum - input1) || (numbers[input2] && input1 + input2 == targetSum)) {
                            numbers[input1] = false;
                            numbers[input2] = false;
                            validInput = true;
                        } else {
                            printf("\x1b[31mOs n�meros selecionados n�o correspondem � soma dos dados.\n");
                        }
                    }
                } else {
                    printf("\x1b[31mVoc� n�o pode selecionar nenhum n�mero para igualar a soma da pr�xima jogada.\n");
                    return 1;
                }
            } else {
                printf("\x1b[31mN�mero inv�lido. Tente novamente.\n");
            }
        }

        // Verifica se o jogo terminou
        if (isGameOver(numbers, targetSum)) {
            displayBoard(numbers);
            printf("\x1b[31mGame over! Voc� n�o pode selecionar mais nenhum n�mero para igualar a soma da pr�xima jogada.\n");
            printf("Voc� perdeu!\n");
            return;
        }

        // Verifica se o jogador ganhou o jogo
        bool allNumbersClosed = true;
        for (int i = 1; i <= 9; i++) {
            if (numbers[i]) {
                allNumbersClosed = false;
                break;
            }
        }
        if (allNumbersClosed) {
            displayBoard(numbers);
            printf("Parab�ns! Voc� fechou todos os n�meros. Voc� ganhou!\n");
            return;
        }
    }
}

// Fun��o para exibir as regras do jogo
void displayRules() {
    printf("\x1b[33m");
    printf("=====================================================================================================================\v\n");
    printf("\x1b[0m");
    printf("\t\t\t\t\tBem-vindo ao Shut the Box!\n\v");
    printf("1 - O objetivo do jogo � fechar todos os n�meros.\n");
    printf("2 - A cada rodada s�o jogado dois dados e voc� deve selecionar um ou dois n�meros que somados deem total dos dados.\n");
    printf("3 - Se voc� n�o puder selecionar nenhum n�mero para igualar a soma dos dados, voc� perde.\n\v");
    printf("\t\t\tPressione qualquer tecla para retornar ao menu principal.\n\v");
    printf("\x1b[33m");
    printf("=====================================================================================================================\v\n");
    getchar(); // Limpar o buffer de entrada
    getchar(); // Aguardar entrada do usu�rio antes de continuar
    system("cls");
}

int main() {
    int escolha;
    setlocale(LC_ALL, "Portuguese");

    while (true) {
        printf("\x1b[32m");
        printf("\t\t\t\t ====================================================\n\v");
        printf("\x1b[34m");
        printf("\t\t\t\t\t    Bem-vindo ao Shut the Box!\n\v");
        printf("\x1b[36m");
        printf("\t\t\t\t\t\t1. Jogar o jogo\n");
        printf("\t\t\t\t\t\t2. Ver as regras\n");
        printf("\t\t\t\t\t\t3. Sair\n\v");
        printf("\x1b[32m");
        printf("\t\t\t\t ====================================================\n");
        printf("\x1b[0m");
        scanf("%d", &escolha);
        system("cls");

        switch (escolha) {
            case 1:
                playGame();
                break;
            case 2:
                displayRules();
                break;
            case 3:
                printf("At� logo!\n");
                return 0;
            default:
                printf("Escolha inv�lida. Por favor, tente novamente.\n");
        }
    }

    return 0;
}
