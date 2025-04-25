#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <windows.h>
#include "memory.h"
#include "cba.h"
#include "io.h"

#define CLOCK_FREQUENCY 0 // X milissegundos

//--------------------------------- REGISTRADORES DO PROCESSADOR ---------------------------------

typedef struct{	

	bool C;
	bool Z;
	
} status_register;

typedef struct{
	
	// sem o unsigned, os valores de char sao tratados como signed, então são limitados

	unsigned char REG[16]; // registradores gerais de 8 bits + (ACC[R0] e RZ[R15])
	unsigned short int PC; // program counter de 16 bits
	unsigned char IR; // registrador de instrucao de 8 bits
	status_register SR; // registrador de status de 8 bits booleanos
	unsigned short int SP; // stack pointer de 16 bits
	unsigned short int GP; // global pointer de 16 bits
	unsigned short int MAR; // registrador de endereco de memoria de 16 bits
	unsigned char MDR; // registrador de dados da memoria de 8 bits
	
} CPU;

//------------------------------------------- FUNCOES --------------------------------------------

void runCPU(CPU* cpu, MEMORY* memory) {

	unsigned short int reset = 0; 		// Reset do processador
	unsigned short int result_16 = 0; 	// Resultado de operacoes que podem resultar em 16 bits
	unsigned char result_8 = 0; 		// Resultado de operacoes que podem resultar em 8 bits
	unsigned char reg1, reg2; 			// Registradores de operacao
	unsigned char shift_amount; 		// Quantidade de deslocamentos
	
	cpu->PC = 0; 				// Inicializa o Program Counter com 0
	cpu->IR = 0; 				// Inicializa o Registrador de Instrucao com 0
	cpu->SP = 57344; 			// Inicializa o Stack Pointer com o endereco do final da "RAM+1", ou seja, (57344)
	cpu->GP = 49152; 			// Inicializa o Global Pointer com 49152 (inicio da RAM)
	cpu->MAR = 0; 				// Inicializa o Registrador de Endereco de Memoria com 0
	cpu->MDR = 0; 				// Inicializa o Registrador de Dados da Memoria com 0
	cpu->SR.C = 0; 				// Inicializa o Carry Flag com 0
	cpu->SR.Z = 0; 				// Inicializa o Zero Flag com 0
	cpu->REG[15] = 0; 			// Inicializa o Registrador RZ[R15] com 0
	memory->ADDRESS[65532] = 0; // Inicializa o endereco de data_state com 0
	memory->ADDRESS[65533] = 0; // Inicializa o endereco do input com 0
	memory->ADDRESS[65534] = 0; // Inicializa o endereco do input_mode com 0
	memory->ADDRESS[65535] = 0; // Inicializa o endereco do output com 0

	// Carrega as palavras binarias da ROM e joga dentro do array memory
	int fileError = readWordBinFile("ROM.bin", memory->ADDRESS);
	Sleep(CLOCK_FREQUENCY);

	// Verifica se houve erro ao carregar a ROM
	if(!fileError) {

		draw_fix_terminal(); // Desenha o terminal fixo

		// iniciar o ciclo de busca, decodificacao e execucao
		while(!reset && cpu->PC < SIZE_ROM) {

			input_handler(memory); // Verifica se houve entrada de dados
			output_handler(memory, cpu->REG[0]); // Verifica se houve saida de dados

			cpu->MAR = cpu->PC; // carrega o endereco da instrucao no MAR
			cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o dado da memoria no MDR
			cpu->IR = cpu->MDR; // carrega a instrucao/opcode no IR

			// verifica qual instrucao/opcode foi lida | ULA
			switch(cpu->IR){

				case 0:
					// printf("Instrucao LDA | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco do registrador destino
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario do registrador destino

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(cpu->MDR == 15){
						cpu->PC += 4;
						break;
					}

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM/RAM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM/RAM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					cpu->REG[cpu->MDR] = memory->ADDRESS[cpu->MAR]; // carrega o valor da memoria no registrador destino

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (cpu->REG[cpu->MDR] == 0); // Define a flag Zero (Z) se o resultado for 0

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 4; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 1:
					// printf("Instrucao LDI | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco do registrador destino

					/* aqui parece ser em 2 ciclos, pois aparentemente o processador colocaria o endereco de 8 em 8 bits 
					no MAR, porem, aqui não há necessidade disso, pois o MAR tem 16 bits lidos diretamente, então pra 
					simplificar, vamos fazer em 1 ciclo */
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario do registrador destino

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(cpu->MDR == 15){
						cpu->PC += 3;
						break;
					}

					cpu->MAR++; // incrementa o MAR para ler o endereco do valor imediato

					cpu->REG[cpu->MDR] = memory->ADDRESS[cpu->MAR]; // carrega o valor imediato no registrador destino

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (cpu->REG[cpu->MDR] == 0); // Define a flag Zero (Z) se o resultado for 0

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 3; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 2:
					// printf("Instrucao STA | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler valor do registrador
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario do registrador

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria RAM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da RAM
						- Desloca 8 bits para a esquerda
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );
					
					// Se não estiver dentro do intervalo da RAM e de periféricos, pula a instrucao
					// if(CBACheckChip(cpu->MAR) == 0){
					// 	cpu->PC += 4;
					// 	break;
					// }

					memory->ADDRESS[cpu->MAR] = cpu->REG[cpu->MDR]; // carrega o valor da do registrador na memoria

					cpu->PC += 4; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 3:
					// printf("Instrucao MOV | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores destino e origem

					// tratando os operandos com as mascaras de bits
					// o "destino" recebe os 4 bits mais significativos
					// a "origem" recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					cpu->REG[reg1] = cpu->REG[reg2]; // salva o valor do registrador origem no registrador destino

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (cpu->REG[reg1] == 0); // Define a flag Zero (Z) se o resultado for 0

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 4:
					// printf("Instrucao ADD | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores destino e origem

					// tratando os operandos com as mascaras de bits
					// o "destino" recebe os 4 bits mais significativos
					// a "origem" recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					result_16 = cpu->REG[reg1] + cpu->REG[reg2]; // guarda o resultado para analise do SR
					result_8 = (unsigned char) result_16; // converte o resultado para 8 bits

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (result_8 == 0); // Define a flag Zero (Z) se o resultado for 0
					cpu->SR.C = (result_16 > 0xFF); // Define a flag Carry (C) se houve carry, ou seja, se o resultado excedeu 255

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->REG[reg1] = result_8; // salva o valor do registrador 1 no registrador 2;

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 5:
					// printf("Instrucao ADD.I | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o registrador 1

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(cpu->MDR == 15){
						cpu->PC += 3;
						break;
					}

					reg1 = cpu->MDR;

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o valor imediato
					reg2 = cpu->MDR;

					result_16 = cpu->REG[reg1] + reg2; // guarda o resultado para analise do SR
					result_8 = (unsigned char) result_16; // converte o resultado para 8 bits

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (result_8 == 0); // Define a flag Zero (Z) se o resultado for 0
					cpu->SR.C = (result_16 > 0xFF); // Define a flag Carry (C) se houve carry, ou seja, se o resultado excedeu 255

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->REG[reg1] = result_8; // salva o valor imediato no registrador 1;

					cpu->PC += 3; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 6:
					// printf("Instrucao SUB | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores destino e origem

					// tratando os operandos com as mascaras de bits
					// o "destino" recebe os 4 bits mais significativos
					// a "origem" recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					result_8 = cpu->REG[reg1] - cpu->REG[reg2]; // guarda o resultado para analise do SR

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (result_8 == 0); // Define a flag Zero (Z) se o resultado for 0
					cpu->SR.C = (cpu->REG[reg1] < cpu->REG[reg2]); // Define a flag Carry (C) se houve carry, ou seja, indica underflow

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->REG[reg1] = result_8; // salva o valor do registrador 1 no registrador 2;

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 7:
					// printf("Instrucao SUB.I | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registrador 1

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(cpu->MDR == 15){
						cpu->PC += 3;
						break;
					}

					reg1 = cpu->MDR;

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o valor imediato
					reg2 = cpu->MDR;

					result_8 = cpu->REG[reg1] - reg2; // guarda o resultado para analise do SR

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (result_8 == 0); // Define a flag Zero (Z) se o resultado for 0
					cpu->SR.C = (cpu->REG[reg1] < reg2); // Define a flag Carry (C) se houve carry, ou seja, indica underflow

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->REG[reg1] = result_8; // salva o valor imediato no registrador 1;

					cpu->PC += 3; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 8:
					// printf("Instrucao SHT.L | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 

					// tratando os operandos com as mascaras de bits
					// o registrador 1 recebe os 4 bits mais significativos
					// o numero de "shifts" é representado pelo registrador 2 com os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4; 
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					shift_amount = (cpu->REG[reg2]); // shift_amount = (cpu->REG[reg2] & 0x07); // Máx. 7 shifts
					
					// shift_amount = shift_amount == 0 ? 1 : shift_amount; // Garante que o shift_amount seja pelo menos 1

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					// Se houver pelo menos um shift, armazena o bit mais significativo antes do deslocamento
					if (shift_amount > 0) {
						cpu->SR.C = (cpu->REG[reg1] & (1 << (8 - shift_amount))) != 0; // Para SLL, Carry é o MSB que sai
					}

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->REG[reg1] <<= shift_amount; // realiza o shift left logic no registrador 1 com base no registrador 2

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

    				cpu->SR.Z = (cpu->REG[reg1] == 0); // Atualiza a flag Z (Zero) se o resultado for zero

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 9:
					// printf("Instrucao SHT.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 

					// tratando os operandos com as mascaras de bits
					// o registrador 1 recebe os 4 bits mais significativos
					// o numero de "shifts" é representado pelo registrador 2 com os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4; 
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					shift_amount = (cpu->REG[reg2]); // shift_amount = (cpu->REG[reg2] & 0x07); // Máx. 7 shifts
					
					// shift_amount = shift_amount == 0 ? 1 : shift_amount; // Garante que o shift_amount seja pelo menos 1

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					// Se houver pelo menos um shift, armazena o bit mais significativo antes do deslocamento
					if (shift_amount > 0) {
						cpu->SR.C = (cpu->REG[reg1] & 0x01) != 0; // Para SRL, Carry é o LSB que sai
					}

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->REG[reg1] >>= shift_amount; // realiza o shift left logic no registrador 1 com base no registrador 2

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

    				cpu->SR.Z = (cpu->REG[reg1] == 0); // Atualiza a flag Z (Zero) se o resultado for zero

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 10:
					// printf("Instrucao HLT | PC (%d)\n", cpu->PC);
					
					printf("\n\nHLT | Pressione a tecla \"Enter\" para continuar. . .\n");
					getchar();
					
					cpu->PC += 1; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 11:
					// printf("Instrucao JMP | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					cpu->PC = cpu->MAR; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 12:
					// printf("Instrucao CMP | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 1 e 2

					// tratando os operandos com as mascaras de bits
					// o reg1 recebe os 4 bits mais significativos
					// a reg2 recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					result_8 = cpu->REG[reg1] - cpu->REG[reg2]; // guarda o resultado para analise do SR

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (result_8 == 0); // Define a flag Zero (Z) se o resultado for 0
					cpu->SR.C = (cpu->REG[reg1] < cpu->REG[reg2]); // Define a flag Carry (C) se houve carry, ou seja, indica underflow

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 13:
					// printf("Instrucao CMP.I | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o valor do registrador

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o valor do registrador
					reg1 = cpu->MDR; // guarda o resultado para o CMP

					cpu->MAR++; // incrementa o MAR para ler o valor imediato

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o valor imediato
					result_8 = cpu->REG[reg1] - cpu->MDR; // guarda o resultado para analise do SR

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (result_8 == 0); // Define a flag Zero (Z) se o resultado for 0
					cpu->SR.C = (cpu->REG[reg1] < cpu->MDR); // Define a flag Carry (C) se houve carry, ou seja, indica underflow

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 3; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 14:
					// printf("Instrucao BEQ | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(cpu->SR.Z){
						cpu->PC = cpu->MAR;
					}else{
						cpu->PC += 3;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 15:
					// printf("Instrucao BNE | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(!cpu->SR.Z){
						cpu->PC = cpu->MAR;
					}else{
						cpu->PC += 3;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 16:
					// printf("Instrucao BLE | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(cpu->SR.Z || cpu->SR.C){
						cpu->PC = cpu->MAR;
					}else{
						cpu->PC += 3;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 17:
					// printf("Instrucao BGE | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(!cpu->SR.C){
						cpu->PC = cpu->MAR;
					}else{
						cpu->PC += 3;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 18:
					// printf("Instrucao BLT | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(cpu->SR.C){
						cpu->PC = cpu->MAR;
					}else{
						cpu->PC += 3;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 19:
					// printf("Instrucao BGT | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					/*
						- Carrega os 8 bits mais significativos do endereco da memoria da ROM
						- Desloca 8 bits para a esquerda 
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(!cpu->SR.Z && !cpu->SR.C){
						cpu->PC = cpu->MAR;
					}else{
						cpu->PC += 3;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 20:
					// printf("Instrucao BEQ.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o endereco relativo

					result_16 = cpu->PC + ((signed char) cpu->MDR); // calcula o novo endereco de PC, mesmo que seja um valor negativo

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(cpu->SR.Z){
						cpu->PC = result_16;
					}else{
						cpu->PC += 2;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 21:
					// printf("Instrucao BNE.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o endereco relativo

					result_16 = cpu->PC + (signed char) cpu->MDR; // calcula o novo endereco de PC

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(!cpu->SR.Z){
						cpu->PC = result_16;
					}else{
						cpu->PC += 2;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 22:
					// printf("Instrucao BLE.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o endereco relativo

					result_16 = cpu->PC + (signed char) cpu->MDR; // calcula o novo endereco de PC

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(cpu->SR.Z || cpu->SR.C){
						cpu->PC = result_16;
					}else{
						cpu->PC += 2;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 23:
					// printf("Instrucao BGE.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o endereco relativo

					result_16 = cpu->PC + (signed char) cpu->MDR; // calcula o novo endereco de PC

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(!cpu->SR.C){
						cpu->PC = result_16;
					}else{
						cpu->PC += 2;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 24:
					// printf("Instrucao BLT.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o endereco relativo

					result_16 = cpu->PC + (signed char) cpu->MDR; // calcula o novo endereco de PC

					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(cpu->SR.C){
						cpu->PC = result_16;
					}else{
						cpu->PC += 2;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 25:
					// printf("Instrucao BGT.R | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco da memoria ROM
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o endereco relativo

					result_16 = cpu->PC + (signed char) cpu->MDR; // calcula o novo endereco de PC
					
					// verifica a(s) flag(s) de status, se satisfazer a condicao, o PC salta para o endereco da memoria indicado
					if(!cpu->SR.Z && !cpu->SR.C){
						cpu->PC = result_16;
					}else{
						cpu->PC += 2;
					}

					Sleep(CLOCK_FREQUENCY);
					break;

				case 26:
					// printf("Instrucao AND | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 1 e 2

					// tratando os operandos com as mascaras de bits
					// o reg1 recebe os 4 bits mais significativos
					// a reg2 recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					cpu->REG[reg1] &= cpu->REG[reg2]; // Executa a operação AND entre os dois registradores

					// Atualiza as flags de status
					cpu->SR.Z = (cpu->REG[reg1] == 0); // Z é 1 se o resultado for zero
					cpu->SR.C = 0; // AND não gera carry

					cpu->PC += 2;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 27:
					// printf("Instrucao OR | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 1 e 2

					// tratando os operandos com as mascaras de bits
					// o reg1 recebe os 4 bits mais significativos
					// a reg2 recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					cpu->REG[reg1] |= cpu->REG[reg2]; // Executa a operação OR entre os dois registradores

					// Atualiza as flags de status
					cpu->SR.Z = (cpu->REG[reg1] == 0); // Z é 1 se o resultado for zero
					cpu->SR.C = 0; // OR não gera carry

					cpu->PC += 2;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 28:
					// printf("Instrucao XOR | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 1 e 2

					// tratando os operandos com as mascaras de bits
					// o reg1 recebe os 4 bits mais significativos
					// a reg2 recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					cpu->REG[reg1] ^= cpu->REG[reg2]; // Executa a operação XOR entre os dois registradores

					// Atualiza as flags de status
					cpu->SR.Z = (cpu->REG[reg1] == 0); // Z é 1 se o resultado for zero
					cpu->SR.C = 0; // XOR não gera carry

					cpu->PC += 2;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 29:
					// printf("Instrucao NOT | PC (%d)\n", cpu->PC);

					cpu->MAR++; // incrementa o MAR para ler o endereco dos operandos

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario dos registradores 1 e 2

					// tratando os operandos com as mascaras de bits
					// o reg1 recebe os 4 bits mais significativos
					// a reg2 recebe os 4 bits menos significativos
					reg1 = (cpu->MDR & 0xF0) >> 4;
					reg2 = cpu->MDR & 0x0F;

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(reg1 == 15){
						cpu->PC += 2;
						break;
					}

					cpu->REG[reg1] = ~cpu->REG[reg2]; // Executa a operação NOT entre os dois registradores

					// Atualiza as flags de status
					cpu->SR.Z = (cpu->REG[reg1] == 0); // Z é 1 se o resultado for zero
					cpu->SR.C = 0; // NOT não gera carry+++

					cpu->PC += 2;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 30:
					// printf("Instrucao END | PC (%d)\n", cpu->PC);

					printf("\n\nEND PROGRAM!\n\n");
					reset = 1;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 31:
					// printf("Instrucao IN - INPUT | PC (%d)\n", cpu->PC);

					// verifica se o data_state é 1, ou seja, se o dado está pronto para ser lido
					if(memory->ADDRESS[65532]){
						cpu->REG[0] = memory->ADDRESS[65533]; // carrega o valor do dado no registrador 0 ou ACC
						memory->ADDRESS[65532] = 0; // reseta o data_state para 0
						memory->ADDRESS[65534] = 0; // reseta o input_mode para 0
					}
					
					cpu->PC += 1;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 32:
					// printf("Instrucao DRAW | PC (%d)\n", cpu->PC);

					memory->ADDRESS[65535] = cpu->REG[0]; // envia um valor de output na memoria RAM(65535) para ser exibido na tela

					draw_char(memory->ADDRESS[65535]); // exibe char da memoria de saida
					
					cpu->PC += 1;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 33:
					// printf("Instrucao OUT | PC (%d)\n", cpu->PC);

					memory->ADDRESS[65535] = cpu->REG[0]; // envia um valor de output na memoria RAM(65535) para ser exibido na tela

					draw_output(memory->ADDRESS[65535]); // exibe inteiro na memoria de saida

					cpu->PC += 1;

					Sleep(CLOCK_FREQUENCY);
					break;

				case 34:
					// printf("Instrucao CALL | PC (%d)\n", cpu->PC);

					result_16 = cpu->PC + 3; // Próxima instrução após CALL + endereço

					cpu->SP--;
					memory->ADDRESS[cpu->SP] = (result_16 & 0xFF);

					cpu->SP--;
					memory->ADDRESS[cpu->SP] = ((result_16 >> 8) & 0xFF);

					// cpu->PC += 3; // Incrementa o PC para o próximo endereço de instrução

					// cpu->SP--; // Decrementa a pilha antes de armazenar o próximo byte
					// memory->ADDRESS[cpu->SP] = (cpu->PC & 0xFF); // Armazena o byte menos significativo do PC na pilha
					
					// cpu->SP--; // Decrementa a pilha antes de armazenar o próximo byte
					// memory->ADDRESS[cpu->SP] = ((cpu->PC >> 8) & 0xFF); // Armazena o byte mais significativo do PC na pilha

					cpu->MAR++; // incrementa o MAR para ler o endereco da subrotina
					
					/*
						- Carrega os 8 bits mais significativos do endereco de memoria
						- Desloca 8 bits para a esquerda
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					cpu->PC = cpu->MAR; // Salta para o endereço da subrotina

					Sleep(CLOCK_FREQUENCY);
					break;

				case 35:
					// printf("Instrucao RET | PC (%d)\n", cpu->PC);

					/*
						- Carrega os 8 bits mais significativos do endereco de memoria
						- Desloca 8 bits para a esquerda
						- Realiza o OR lógico binario
					*/
					cpu->PC = ( (memory->ADDRESS[cpu->SP] << 8) | (memory->ADDRESS[cpu->SP+1]));
					cpu->SP += 2; // Atualiza o topo da pilha

					Sleep(CLOCK_FREQUENCY);
					break;

				case 36:
					// printf("Instrucao INI.P | PC (%d)\n", cpu->PC);
					// (INITIALIZE POINTER)	- INICIALIZA PONTEIRO PASSANDO UM ENDERECO DE MEMORIA

					cpu->MAR++; // incrementa o MAR para ler o endereco de memoria
					
					/*
						- Carrega os 8 bits mais significativos do endereco de memoria
						- Desloca 8 bits para a esquerda
						- Realiza o OR lógico binario
					*/
					cpu->MAR = ( (memory->ADDRESS[cpu->MAR] << 8) | (memory->ADDRESS[cpu->MAR+1]) );

					cpu->GP = cpu->MAR; // inicializa o valor do GP (General Pointer) com o endereco de memoria

					cpu->PC += 3; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;
				
				case 37:
					// printf("Instrucao SET.P | PC (%d)\n", cpu->PC);
					// (SET POINTER) - SETA UM VALOR (DE 8 BITS) AO ENDERECO DE GP (semelhante ao STA)

					cpu->MAR++; // incrementa o MAR para ler o registrador
					
					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario do registrador
					
					cpu->MAR = cpu->GP; // carrega o endereco de memoria do GP (General Pointer)

					// Se não estiver dentro do intervalo da RAM, pula a instrucao
					if(CBACheckChip(cpu->MAR) != 1){
						cpu->PC += 2;
						break;
					}

					memory->ADDRESS[cpu->MAR] = cpu->REG[cpu->MDR]; // carrega o valor da do registrador na memoria

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;
					
				case 38:
					// printf("Instrucao GET.P | PC (%d)\n", cpu->PC);
					// GET.P (GET POINTER) - PEGA  O VALOR (DE 8 BITS) NO ENDERECO DE GP (semelhante ao LDA)

					cpu->MAR++; // incrementa o MAR para ler o endereco do registrador destino

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // carrega o binario do registrador destino

					// verifica se o registrador destino é o R15, ou seja, o RZ (Register Zero). Se sim, pula a instrucao
					if(cpu->MDR == 15){
						cpu->PC += 2;
						break;
					}

					cpu->MAR = cpu->GP; // carrega o endereco de memoria do GP (General Pointer)

					cpu->REG[cpu->MDR] = memory->ADDRESS[cpu->MAR]; // carrega o valor da memoria no registrador destino

					// ----------------------- VERIFICACAO DO REGISTRADOR DE STATUS -----------------------

					cpu->SR.Z = (cpu->REG[cpu->MDR] == 0); // Define a flag Zero (Z) se o resultado for 0

					// ---------------------------- FINAL DA VERIFICACAO do SR ----------------------------

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;
				
				case 39:
					// printf("Instrucao UPD.P | PC (%d)\n", cpu->PC);
					// UPD.P (UPDATE POINTER) - ATUALIZA PONTEIRO COM O VALOR DE UM REGISTRADOR (POSITIVO OU NEGATIVO)

					cpu->MAR++; // incrementa o MAR para ler o valor do registrador

					cpu->MDR = cpu->REG[cpu->MAR]; // captura o valor do registrador

					result_16 = cpu->GP + ((signed char) cpu->MDR); // calcula o novo endereco de GP, mesmo que seja um valor negativo

					cpu->GP = result_16; // atualiza o GP (General Pointer) com o novo endereco de memoria

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

					Sleep(CLOCK_FREQUENCY);
					break;

				case 40:
					// printf("Instrucao UPI.P | PC (%d)\n", cpu->PC);
					// UPI.P (UPDATE IMMEDIATE POINTER) - ATUALIZA PONTEIRO COM UM VALOR IMEDIATO (POSITIVO OU NEGATIVO)

					cpu->MAR++; // incrementa o MAR para ler o valor imediato

					cpu->MDR = memory->ADDRESS[cpu->MAR]; // captura o valor imediato

					result_16 = cpu->GP + ((signed char) cpu->MDR); // calcula o novo endereco de GP, mesmo que seja um valor negativo

					cpu->GP = result_16; // atualiza o GP (General Pointer) com o novo endereco de memoria

					cpu->PC += 2; //PC recebe o endereco da proxima instrucao

				Sleep(CLOCK_FREQUENCY);
				break;

				case 41:
					// printf("Instrucao GETC | PC (%d)\n", cpu->PC);

					// verifica o endereco de memoria que armazena o status do input de caracteres
					// se no endereco for true, armazena o valor da memoria RAM(65532) no ACC(R0) e zera o status do input char
					if(memory->ADDRESS[65531]){
						cpu->REG[0] = memory->ADDRESS[65532];
						memory->ADDRESS[65531] = 0; // Reseta o status do input char
					}
					
					cpu->PC += 1;

					Sleep(CLOCK_FREQUENCY);
					break;
				
				default:
					// printf("Instrucao nao encontrada: %d | Program Counter: %d\n\n", cpu->IR, cpu->PC);
					
					reset = 1;
					Sleep(CLOCK_FREQUENCY);
					break;

			}

		}

	}else {
		printf("Erro ao carregar a ROM.\n");
	}

}

#endif //CPU_H