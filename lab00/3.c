#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

int tm = 5; //tamano matriz

#include <assert.h>  /* assert() */

#define CELL_MAX (tm * tm - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[tm][tm])
{
    int cell = 0;

    print_sep(tm);
    for (int row = 0; row < tm; ++row) {
        for (int column = 0; column < tm; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(tm);
    }
}

char get_winner(char board[tm][tm])
{
    char winner = '-';
    int hayGanador = 0;
    int i,j,contX, contO;
    // chequeo fila 

    for (i=0; i<tm && hayGanador==0; i++){
        contX = 0, contO = 0;
        for (j=0; j<tm && hayGanador==0; j++){
            if (board[i][j] == 'X' && hayGanador==0){
                contX++;
            }
            else if(board[i][j] == 'O' && hayGanador==0){
                contO++;
            }
        }
        if (contX==tm){
            hayGanador = 1;
            winner='X';        
        }
        else if (contO==tm){
            hayGanador = 1;
            winner='O';        
        }
        else{
            contX = 0, contO = 0;
        }
    }

    // chequeo para columna

    for (i=0; i<tm && hayGanador==0; i++){
        contX = 0, contO = 0;
        for (j=0; j<tm && hayGanador==0; j++){
            if (board[j][i] == 'X'){
                contX++;
            }
            else if (board[j][i] == 'O'){
                contO++;
            }
        }
        if (contX==tm){
            hayGanador = 1;
            winner = 'X';
        }
        else if (contO==tm){
            hayGanador = 1;
            winner='O';        
        }
        else{
            contX = 0, contO = 0;
        }
    }

    // chequeo diagonal

    contX = 0, contO = 0;
    for (i=0; i<tm && hayGanador==0; i++){
        if (board[i][i]=='X'){
            contX++;
        }
        else if (board[i][i]=='O'){
            contO++;        
        }
        if (contX==tm){
            hayGanador = 1;
            winner = 'X';
        }
        else if (contO==tm){
            hayGanador = 1;
            winner='O';        
        }
    }

    // chequeo inversa de diagonal

    contX = 0, contO = 0;
    j = tm-1;
    for (i=0; i<tm && hayGanador==0; i++){
        if (board[i][j]=='X'){
            contX++;
        }
        else if(board[i][j]=='O'){
            contO++;
        }
        if (contX==tm){
            hayGanador = 1;
            winner = 'X';
        }
        else if (contX==tm){
            hayGanador = 1;
            winner='O';        
        }
        j--;
    }


    //
    return winner;
}

bool has_free_cell(char board[tm][tm])
{
    bool free_cell;
    //
    free_cell = 1;
    int i,j;
    int cont = 0;

    for (i=0;i<tm;i++){
        for (j=0;j<tm;j++){
            if (board[i][j] != '-'){
                cont++;
            }
        }
    }
    if (cont==(tm*tm)){
        free_cell = 0;
    }
    
    return free_cell;
}


int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[tm][tm];
    int i,j;
    for (i=0;i<tm;i++){
        for (j=0;j<tm;j++){
            board[i][j]='-';
        }
    }

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / tm;
            int colum = cell % tm;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}