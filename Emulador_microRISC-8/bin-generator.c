#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void writeWordBinFile(unsigned int value, const char *filename) {

    FILE *file = fopen(filename, "ab+");  // Abre o arquivo para leitura e escrita (append)
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    fwrite(&value, sizeof(unsigned char), 1, file);  // Escreve o número como binário
    fclose(file);  // Fecha o arquivo
}

int main() {

    setlocale(LC_ALL, "Portuguese_Brazil");

	const char *filename = "ROM.bin";

    // Tenta deletar o arquivo
    if (remove(filename) == 0) {
        printf("Arquivo '%s' deletado com sucesso!\n\n", filename);
    } else {
        printf("Erro ao deletar o arquivo '%s'. Arquivo não encontrado!\n\n", filename);
    }

    unsigned char opcode;
	
	// // (LDI R4, 100)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000100;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01100100;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (MOV R1, R4)
	// opcode = 0b00000011;
	// printf("(0%d) MOV", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00010100;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (MOV R2, R4)
	// opcode = 0b00000011;
	// printf("(0%d) MOV", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00100100;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (MOV R3, R4)
	// opcode = 0b00000011;
	// printf("(0%d) MOV", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00110100;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R0, 85)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01010101;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDA R2, 2)
	// opcode = 0b00000000;
	// printf("(0%d) LDA", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf("%d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (STA R0, 49152)
	// opcode = 0b00000010;
	// printf("(0%d) STA", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11000000;
	// printf("%d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	
	// // (LDA R1, 49152)
	// opcode = 0b00000000;
	// printf("(0%d) LDA", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11000000;
	// printf("%d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R5, 25)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000101;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00011001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	
	// // (LDI R6, 50)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00110010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	
	// // (LDI R7, 255)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000111;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111111;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	
	// // (LDI R8, 1)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD R5, R6)
	// opcode = 0b00000100;
	// printf("(0%d) ADD", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01010110;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD R7, R8)
	// opcode = 0b00000100;
	// printf("(0%d) ADD", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01111000;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R5, 25)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000101;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00011001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R7, 255)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000111;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111111;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SUB R6, R5)
	// opcode = 0b00000110;
	// printf("(0%d) SUB", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01100101;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R6, 50)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00110010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SUB R5, R6)
	// opcode = 0b00000110;
	// printf("(0%d) SUB", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01010110;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SUB R8, R7)
	// opcode = 0b00000110;
	// printf("(0%d) SUB", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10000111;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R8, 1)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R9, 3)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SHT.L R8, R9)
	// opcode = 0b00001000;
	// printf("(0%d) SHT.L", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	
	// // (SHT.R R8, R9)
	// opcode = 0b00001001;
	// printf("(0%d) SHT.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R9, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SHT.L R8, R9)
	// opcode = 0b00001000;
	// printf("(0%d) SHT.L", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SHT.R R8, R9)
	// opcode = 0b00001001;
	// printf("(0%d) SHT.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R8, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SHT.L R8, R9)
	// opcode = 0b00001000;
	// printf("(0%d) SHT.L", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (SHT.R R8, R9)
	// opcode = 0b00001001;
	// printf("(0%d) SHT.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	
	// // // (JMP 0)
	// // opcode = 0b00001011;
	// // printf("(0%d) JMP", opcode);
	// // writeWordBinFile(opcode, "ROM.bin");
	// // opcode = 0b00000000;
	// // printf(" %d-", opcode);
	// // writeWordBinFile(opcode, "ROM.bin");
	// // opcode = 0b00000000;
	// // printf("%d\n", opcode);
	// // writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R8, 1)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R9, 3)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R8, R9)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R9, R8)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10011000;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP.I R8, 1)
	// opcode = 0b00001101;
	// printf("(%d) CMP.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP.I R9, 1)
	// opcode = 0b00001101;
	// printf("(%d) CMP.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R9, 1)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R8, R9)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b10001001;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (HLT)
	// opcode = 0b00001010;
	// printf("(0%d) HLT\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE LAÇO DE REPETIÇÃO BLT, BEQ, BGT

	// // (LDI R1, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R2, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD.I R1, 1)
	// opcode = 0b00000101;
	// printf("(0%d) ADD.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R1, R2)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00010010;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BLT 6)
	// opcode = 0b00010010;
	// printf("(%d) BLT", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" %d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BEQ 6)
	// opcode = 0b00001110;
	// printf("(%d) BEQ", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" %d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BGT 6)
	// opcode = 0b00010011;
	// printf("(%d) BGT", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" %d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE LAÇO DE REPETIÇÃO BLE, BGE

	// // (LDI, R3, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI, R4, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000100;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD.I, R3, 1)
	// opcode = 0b00000101;
	// printf("(0%d) ADD.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP, R3, R4)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00110100;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BLE, 6)
	// opcode = 0b00010000;
	// printf("(%d) BLE", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" %d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BGE, 6)
	// opcode = 0b00010001;
	// printf("(%d) BGE", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" %d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE LAÇO DE REPETIÇÃO BNE

	// // (LDI, R3, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI, R4, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000100;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD.I, R3, 1)
	// opcode = 0b00000101;
	// printf("(0%d) ADD.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP, R3, R4)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00110100;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BNE, 6)
	// opcode = 0b00001111;
	// printf("(%d) BNE", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000000;
	// printf(" %d-", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (HLT)
	// opcode = 0b00001010;
	// printf("(0%d) HLT\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE LAÇO DE REPETIÇÃO BLT.R, BEQ.R, BGT.R

	// // (LDI R1, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R2, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD.I R1, 1)
	// opcode = 0b00000101;
	// printf("(0%d) ADD.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R1, R2)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00010010;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BLT.R -5)
	// opcode = 0b00011000;
	// printf("(%d) BLT.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111011;
	// printf(", %d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BEQ.R -7)
	// opcode = 0b00010100;
	// printf("(%d) BEQ.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111001;
	// printf(", %d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BGT.R -9)
	// opcode = 0b00011001;
	// printf("(%d) BGT.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11110111;
	// printf(", %d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE LAÇO DE REPETIÇÃO BLE.R, BGE.R

	// // (LDI R1, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R2, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD.I R1, 1)
	// opcode = 0b00000101;
	// printf("(0%d) ADD.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R1, R2)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00010010;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BLE.R -5)
	// opcode = 0b00010110;
	// printf("(%d) BLE.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111011;
	// printf(", %d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BGE.R -7)
	// opcode = 0b00010111;
	// printf("(%d) BGE.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111001;
	// printf(", %d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE LAÇO DE REPETIÇÃO BNE.R

	// // (LDI R1, 8)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001000;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R2, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (ADD.I R1, 1)
	// opcode = 0b00000101;
	// printf("(0%d) ADD.I", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (CMP R1, R2)
	// opcode = 0b00001100;
	// printf("(%d) CMP", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00010010;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (BNE.R -5)
	// opcode = 0b00010101;
	// printf("(%d) BNE.R", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b11111011;
	// printf(", %d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (HLT)
	// opcode = 0b00001010;
	// printf("(%d) HLT\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// TESTE DE OPERADORES LOGICOS AND, OR, XOR, NOT

	// // (LDI R1, 12)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000001;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001100;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R2, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000010;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R3, 12)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000011;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001100;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R4, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000100;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R5, 12)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000101;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001100;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R6, 10)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000110;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001010;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (LDI R7, 12)
	// opcode = 0b00000001;
	// printf("(0%d) LDI", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00000111;
	// printf(" R%d,", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00001100;
	// printf("%d\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (AND R1, R2)
	// opcode = 0b00011010;
	// printf("(%d) AND", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00010010;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (OR R3, R4)
	// opcode = 0b00011011;
	// printf("(%d)  OR", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b00110100;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (XOR R5, R6)
	// opcode = 0b00011100;
	// printf("(%d) XOR", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01010110;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (NOT R7, R7)
	// opcode = 0b00011101;
	// printf("(%d) NOT", opcode);
	// writeWordBinFile(opcode, "ROM.bin");
	// opcode = 0b01110111;
	// printf(" 0x%02X\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// // (HLT)
	// opcode = 0b00001010;
	// printf("(%d) HLT\n", opcode);
	// writeWordBinFile(opcode, "ROM.bin");

	// (LDI R0, 0)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R1, 0)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000001;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R2, 0)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000010;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R3, 0)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000011;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (CALL 34)
	opcode = 0b00100010;
	printf("(%d) CALL", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" %d-", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00100010;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (CALL 67)
	opcode = 0b00100010;
	printf("(%d) CALL", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" %d-", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01000011;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (MOV R1, R0)
	opcode = 0b00000011;
	printf("(0%d) MOV", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00010000;
	printf(" 0x%02X\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (CALL 34)
	opcode = 0b00100010;
	printf("(%d) CALL", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" %d-", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00100010;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (CALL 67)
	opcode = 0b00100010;
	printf("(%d) CALL", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" %d-", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01000011;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (MOV R2, R0)
	opcode = 0b00000011;
	printf("(0%d) MOV", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00100000;
	printf(" 0x%02X\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (ADD R1, R2)
	opcode = 0b00000100;
	printf("(0%d) ADD", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00010010;
	printf(" 0x%02X\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (MOV R0, R1)
	opcode = 0b00000011;
	printf("(0%d) MOV", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000001;
	printf(" 0x%02X\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (OUT)
	opcode = 0b00100001;
	printf("(%d) OUT\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (END)
	opcode = 0b00011110;
	printf("(%d) END\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R0, 68)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01000100;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R0, 73)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01001001;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R0, 71)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01000111;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R0, 73)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01001001;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDI R0, 84)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01010100;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	
	// (LDI R0, 69)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b01000101;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	
	// (LDI R0, 58)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00111010;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	
	// (LDI R0, 32)
	opcode = 0b00000001;
	printf("(0%d) LDI", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00100000;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (DRAW)
	opcode = 0b00100000;
	printf("(%d) DRAW\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (RET)
	opcode = 0b00100011;
	printf("(%d) RET\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (LDA R3, 65533) ou FFFD
	opcode = 0b00000000;
	printf("(0%d) LDA", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000011;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b11111111;
	printf("%d-", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b11111101;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (CMP.I R3, 0)
	opcode = 0b00001101;
	printf("(%d) CMP.I", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000011;
	printf(" R%d,", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b00000000;
	printf("%d\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (BEQ.R -7)
	opcode = 0b00010100;
	printf("(%d) BEQ.R", opcode);
	writeWordBinFile(opcode, "ROM.bin");
	opcode = 0b11111001;
	printf(", %d\n", (signed char) opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (IN)
	opcode = 0b00011111;
	printf("(%d) IN\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

	// (RET)
	opcode = 0b00100011;
	printf("(%d) RET\n", opcode);
	writeWordBinFile(opcode, "ROM.bin");

    printf("\nValor gravado em binário no arquivo output.bin\n");
    return 0;
}
