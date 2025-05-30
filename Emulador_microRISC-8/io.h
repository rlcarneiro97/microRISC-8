#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>  // Usar ncurses.h no Linux
#include "memory.h"
#include <string.h> // P/ manipulação de strings
#include <stdlib.h>

#define DATA_STATE 65531 // Endereço de data_state
#define INPUT 65532 // Endereço de input
#define INPUT_MODE 65533 // Endereço de input_mode
#define OUTPUT_MODE 65534 // Endereço de output_mode
#define OUTPUT 65535 // Endereço de output

void draw_fix_terminal(){
    
    // Limpa a tela e exibe o terminal
    system("cls || clear");
    printf("Micro RISC-8 Version 1.0\n"); // Micro RISC 8 Bits
    printf("Copyright (C) 2025 by RAFAEL CARNEIRO\n");
    printf("8192 Bytes Free\n\n");
    printf("Ready\n\n");

}

void input_handler(MEMORY *memory){

    static char buffer_integer[4] = {0}; // 3 caracteres + '\0'
    static unsigned char input_state = 0; // Variável para armazenar o caractere lido

    // Se uma tecla foi pressionada, entra no if
    if (_kbhit()) {
        
        input_state = _getch(); // Captura a tecla automaticamente

        // LEMBRAR QUE SEMPRE TEM QUE SETAR O INPUT_MODE NO ASSEMBLY COM "STA" ANTES DE REALIZAR O INPUT

        // verifica se o input lido é um char immediate
        if (memory->ADDRESS[INPUT_MODE] == 1) {

            memory->ADDRESS[INPUT] = input_state; // Armazena o valor lido na primeira posição da memória de entrada
            memory->ADDRESS[DATA_STATE] = 1; // Seta o data_state para 1, indicando que o dado foi lido
            draw_fix_terminal(); // Limpa a tela e exibe o terminal

        }

        // verifica se o input lido é um char
        if (memory->ADDRESS[INPUT_MODE] == 2) {

            if(input_state == '\r'){

                memory->ADDRESS[DATA_STATE] = 1; // Seta o data_state para 1, indicando que o dado esta pronto para ser lido
                draw_fix_terminal(); // Limpa a tela e exibe o terminal
                return;

            }

            if(input_state == '\b'){

                memory->ADDRESS[INPUT] = '\0'; // Apaga o valor lido na posição da memória de entrada
                draw_fix_terminal(); // Limpa a tela e exibe o terminal
                // printf("%c", input_state); // Exibe o caractere lido na tela
                putchar(input_state); // Exibe o caractere lido na tela
                return;

            }

            // se não for nem Enter nem Backspace, armazena o valor lido na posição da memória de entrada
            memory->ADDRESS[INPUT] = input_state;
            draw_fix_terminal(); // Limpa a tela e exibe o terminal
            // printf("%c", input_state); // Exibe o caractere lido na tela
            putchar(input_state); // Exibe o caractere lido na tela
            return;
            
        }

        // verifica se o input lido é um inteiro
        if (memory->ADDRESS[INPUT_MODE] == 3) {

            if(input_state == '\r'){
               
                input_state = (unsigned short int) atoi(buffer_integer); // Converte a string para inteiro
                memory->ADDRESS[INPUT] = input_state; // Armazena o valor lido na memória de entrada
                memory->ADDRESS[DATA_STATE] = 1; // input tá pronto

                draw_fix_terminal(); // Desenha o terminal novamente
                memset(buffer_integer, 0, sizeof(char) * 4); // Zera o array
                return;

            }

            if(input_state == '\b'){

                int len = strlen(buffer_integer); // Armazena o tamaho do buffer já usado

                if (len > 0) {
                    buffer_integer[len - 1] = '\0';  // Apaga o último caractere
                }

                draw_fix_terminal(); // Desenha o terminal novamente
                printf("%s", buffer_integer); // Exibe a string atualizada
                return;

            } 

            int len = strlen(buffer_integer); // Armazena o tamaho do buffer já usado

            // Evita estouro do buffer
            if (len < 3){
                buffer_integer[len] = input_state;
                buffer_integer[len + 1] = '\0';  // Garante o final da string

                draw_fix_terminal(); // Desenha o terminal novamente
                printf("%s", buffer_integer); // Exibe a string atualizada
                return;

            }

        }

    }

}

void output_handler(MEMORY *memory, unsigned char output_reg_value){

    // Se o registrador de output estiver diferente do valor da RAM de saída, atualiza a memória de saída
    if (output_reg_value != memory->ADDRESS[OUTPUT]) {
        memory->ADDRESS[OUTPUT] = output_reg_value; // Atualiza o valor da saída
    }
}

void draw_output(MEMORY *memory){

    // Verifica o modo de saída tipo char
    if(memory->ADDRESS[OUTPUT_MODE] == 1){

        putchar(memory->ADDRESS[OUTPUT]); // Exibe o valor da memoria de saída sem pular linha
        fflush(stdout); // Garante que o caractere apareça imediatamente

        return;

    } 
    
    // Verifica o modo de saída tipo integer
    else if(memory->ADDRESS[OUTPUT_MODE] == 2){

        printf("%d", memory->ADDRESS[OUTPUT]); // Exibe o valor do inteiro
        return;

    }

}

#endif //IO_H