#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>  // Usar ncurses.h no Linux
#include "memory.h"
#include <string.h> // P/ manipulação de strings
#include <stdlib.h>

void init_terminal(int CLOCK_FREQUENCY){

    // Limpa a tela e exibe o terminal
    system("cls || clear");
    putchar('M');
    Sleep(CLOCK_FREQUENCY);
    putchar('i');
    Sleep(CLOCK_FREQUENCY);
    putchar('c');
    Sleep(CLOCK_FREQUENCY);
    putchar('r');
    Sleep(CLOCK_FREQUENCY);
    putchar('o');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('R');
    Sleep(CLOCK_FREQUENCY);
    putchar('I');
    Sleep(CLOCK_FREQUENCY);
    putchar('S');
    Sleep(CLOCK_FREQUENCY);
    putchar('C');
    Sleep(CLOCK_FREQUENCY);
    putchar('-');
    Sleep(CLOCK_FREQUENCY);
    putchar('8');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('V');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('r');
    Sleep(CLOCK_FREQUENCY);
    putchar('s');
    Sleep(CLOCK_FREQUENCY);
    putchar('i');
    Sleep(CLOCK_FREQUENCY);
    putchar('o');
    Sleep(CLOCK_FREQUENCY);
    putchar('n');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('1');
    Sleep(CLOCK_FREQUENCY);
    putchar('.');
    Sleep(CLOCK_FREQUENCY);
    putchar('0');
    Sleep(CLOCK_FREQUENCY);
    putchar('\n');

    Sleep(CLOCK_FREQUENCY);
    putchar('C');
    Sleep(CLOCK_FREQUENCY);
    putchar('o');
    Sleep(CLOCK_FREQUENCY);
    putchar('p');
    Sleep(CLOCK_FREQUENCY);
    putchar('y');
    Sleep(CLOCK_FREQUENCY);
    putchar('r');
    Sleep(CLOCK_FREQUENCY);
    putchar('i');
    Sleep(CLOCK_FREQUENCY);
    putchar('g');
    Sleep(CLOCK_FREQUENCY);
    putchar('h');
    Sleep(CLOCK_FREQUENCY);
    putchar('t');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('(');
    Sleep(CLOCK_FREQUENCY);
    putchar('C');
    Sleep(CLOCK_FREQUENCY);
    putchar(')');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('2');
    Sleep(CLOCK_FREQUENCY);
    putchar('0');
    Sleep(CLOCK_FREQUENCY);
    putchar('2');
    Sleep(CLOCK_FREQUENCY);
    putchar('5');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('b');
    Sleep(CLOCK_FREQUENCY);
    putchar('y');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('R');
    Sleep(CLOCK_FREQUENCY);
    putchar('A');
    Sleep(CLOCK_FREQUENCY);
    putchar('F');
    Sleep(CLOCK_FREQUENCY);
    putchar('A');
    Sleep(CLOCK_FREQUENCY);
    putchar('E');
    Sleep(CLOCK_FREQUENCY);
    putchar('L');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('C');
    Sleep(CLOCK_FREQUENCY);
    putchar('A');
    Sleep(CLOCK_FREQUENCY);
    putchar('R');
    Sleep(CLOCK_FREQUENCY);
    putchar('N');
    Sleep(CLOCK_FREQUENCY);
    putchar('E');
    Sleep(CLOCK_FREQUENCY);
    putchar('I');
    Sleep(CLOCK_FREQUENCY);
    putchar('R');
    Sleep(CLOCK_FREQUENCY);
    putchar('O');
    Sleep(CLOCK_FREQUENCY);
    putchar('\n');

    Sleep(CLOCK_FREQUENCY);
    putchar('8');
    Sleep(CLOCK_FREQUENCY);
    putchar('1');
    Sleep(CLOCK_FREQUENCY);
    putchar('9');
    Sleep(CLOCK_FREQUENCY);
    putchar('2');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('B');
    Sleep(CLOCK_FREQUENCY);
    putchar('y');
    Sleep(CLOCK_FREQUENCY);
    putchar('t');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('s');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('F');
    Sleep(CLOCK_FREQUENCY);
    putchar('r');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('\n');
    Sleep(CLOCK_FREQUENCY);
    putchar('\n');
    Sleep(CLOCK_FREQUENCY);

    putchar('R');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('a');
    Sleep(CLOCK_FREQUENCY);
    putchar('d');
    Sleep(CLOCK_FREQUENCY);
    putchar('y');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('(');
    Sleep(CLOCK_FREQUENCY);
    putchar('P');
    Sleep(CLOCK_FREQUENCY);
    putchar('r');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('s');
    Sleep(CLOCK_FREQUENCY);
    putchar('s');
    Sleep(CLOCK_FREQUENCY);
    putchar(' ');
    Sleep(CLOCK_FREQUENCY);
    putchar('E');
    Sleep(CLOCK_FREQUENCY);
    putchar('n');
    Sleep(CLOCK_FREQUENCY);
    putchar('t');
    Sleep(CLOCK_FREQUENCY);
    putchar('e');
    Sleep(CLOCK_FREQUENCY);
    putchar('r');
    Sleep(CLOCK_FREQUENCY);
    putchar(')');
    Sleep(CLOCK_FREQUENCY);
    putchar('\n');
    Sleep(CLOCK_FREQUENCY);

    getchar(); // Aguarda a entrada do usuário
    system("cls || clear"); // Limpa a tela e exibe o terminal novamente

}

void draw_fix_terminal(){
    
    // Limpa a tela e exibe o terminal
    system("cls || clear");
    printf("Micro RISC-8 Version 1.0\n"); // Micro RISC 8 Bits
    printf("Copyright (C) 2025 by RAFAEL CARNEIRO\n");
    printf("8192 Bytes Free\n\n");
    printf("Ready\n\n");

}

void input_handler(MEMORY *memory){

    static char operacao[4] = {0}; // 3 caracteres + '\0'
    static unsigned char input_state = 0; // Variável para armazenar o caractere lido

    // Se uma tecla foi pressionada
    if (_kbhit()) {

        input_state = _getch(); // Captura a tecla sem ENTER

        // ------------------ parte para lidar com o inteiro lido ------------------

        // Se pressionar Enter, encerra a leitura
        if (input_state == '\r') { // No Windows, Enter é '\r'. No Linux, seria '\n'

            // se pressionar a tecla e o status char estiver igual a 1, significa que o char já foi lido
            if(memory->ADDRESS[65531]){
                memory->ADDRESS[65531] = 0; // Reseta o status do char para não lido
            } else {
                memory->ADDRESS[65531] = 1; // Seta o status do char para lido
            }

            input_state = (unsigned short int) atoi(operacao);

            memory->ADDRESS[65534] = input_state; // Armazena o valor lido na memória de entrada
            memory->ADDRESS[65533] = 1; // input tá pronto

            draw_fix_terminal(); // Desenha o terminal novamente
            memset(operacao, 0, sizeof(char) * 4); // Zera o array

            return;

        }

        // Se pressionar Backspace, apaga o último caractere
        if (input_state == '\b') {
            int len = strlen(operacao);
            if (len > 0) {
                operacao[len - 1] = '\0';  // Apaga o último caractere
            }

            memory->ADDRESS[65532] = '\0'; // Reseta o caractere lido

            draw_fix_terminal(); // Desenha o terminal novamente
            printf("%s", operacao); // Exibe a string atualizada

            return;

        }

        // Adiciona o caractere ao final da string
        int len = strlen(operacao);

        // Evita estouro do buffer
        if (len < 3){
            operacao[len] = input_state;
            operacao[len + 1] = '\0';  // Garante o final da string

            // ------------------ parte para lidar com o caractere lido ------------------

            memory->ADDRESS[65532] = input_state; // Armazena o caractere lido na memória de entrada

            draw_fix_terminal(); // Desenha o terminal novamente
            printf("%s", operacao); // Exibe a string atualizada

            return;

        }

    }

}

void output_handler(MEMORY *memory, unsigned char R0){

    unsigned char output_state = R0;

    // Se o registrador de saída estiver diferente do valor atual
    if (output_state != memory->ADDRESS[65535]) {
        // Atualiza o valor da saída
        memory->ADDRESS[65535] = output_state;
    }
}

void draw_char(unsigned char output){
    
    putchar(output); // Exibe o valor da memoria de saída sem pular linha
    fflush(stdout); // Garante que o caractere apareca imediatamente

}

void draw_output(unsigned char output){

    // Exibe o valor da memoria de saída sem pular linha
    printf("%d", output); // Exibe o inteiro

}

#endif //IO_H