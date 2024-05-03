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
            printf(" | %d ", i);
        } else {
            printf(" | X ");
        }
        if (i == 3 || i == 6 || i == 9) {
            printf("|\n");
        }
    }
    printf("  -------------\n");
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
        displayBoard(numbers);
        int roll1 = randRange(1, 6);
        int roll2 = randRange(1, 6);
        int targetSum = roll1 + roll2;
        printf("Dados rolados: %d + %d = %d\n", roll1, roll2, targetSum);

        bool validInput = false;
        int input1 = -1, input2 = -1;

        while (!validInput) {
            printf("Selecione o primeiro n�mero para fechar: ");
            if (scanf("%d", &input1) != 1) {
                printf("Entrada inv�lida. Insira um n�mero inteiro.\n");
                // Limpar o buffer de entrada
                while (getchar() != '\n');
                continue;
            }
            if (input1 == 0) {
                printf("Voc� n�o pode pular a sele��o do primeiro n�mero.\n");
            } else if (numbers[input1]) {
                if (input1 == targetSum || numbers[targetSum - input1]) {
                    if (input1 == targetSum) {
                        numbers[input1] = false;
                        validInput = true;
                    } else {
                        printf("Escolha o segundo n�mero para fechar: ");
                        if (scanf("%d", &input2) != 1) {
                            printf("Entrada inv�lida. Insira um n�mero inteiro.\n");
                            // Limpar o buffer de entrada
                            while (getchar() != '\n');
                            continue;
                        }else if(input2 == 0){
                            printf("Voc� n�o pode pular a sele��o do segundo n�mero.\n");
                            return;
                        }

                        if ((input2 == 0 && numbers[targetSum - input1]) || (input2 != 0 && (numbers[input2] && (input1 + input2 == targetSum)))) {
                            numbers[input1] = false;
                            if (input2 != 0) numbers[input2] = false;
                            validInput = true;
                        } else {
                            displayBoard(numbers);
                            printf("N�o h� um segundo n�mero dispon�vel para fechar com a soma dos dados.\n");
                            return;
                        }
                    }
                } else {
                    printf("N�o h� um n�mero dispon�vel para fechar com a soma dos dados.\n");
                    return;
                }
            } else {
                printf("N�mero inv�lido. Tente novamente.\n");
            }

            // Verifica se o jogo terminou
        if (isGameOver(numbers, targetSum)) {
            displayBoard(numbers);
            printf("Game over! Voc� n�o pode selecionar nenhum n�mero para igualar a soma dos dados.\n");
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
}

// Fun��o para exibir as regras do jogo
void displayRules() {
    printf("Bem-vindo ao Shut the Box!\n");
    printf("O objetivo do jogo � fechar todos os n�meros.\n");
    printf("A cada rodada, voc� joga dois dados e seleciona um ou dois n�meros que somam ao total dos dados.\n");
    printf("Se voc� n�o puder selecionar nenhum n�mero para igualar a soma dos dados, voc� perde.\n");
    printf("Pressione qualquer tecla para retornar ao menu principal.\n");
    getchar(); // Limpar o buffer de entrada
    getchar(); // Aguardar entrada do usu�rio antes de continuar
    system("cls");
}

int main() {
    int escolha;
    setlocale(LC_ALL, "Portuguese");

    while (true) {
        printf("Bem-vindo ao Shut the Box!\n");
        printf("1. Jogar o jogo\n");
        printf("2. Ver as regras\n");
        printf("3. Sair\n");
        printf("Digite sua escolha: ");
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
