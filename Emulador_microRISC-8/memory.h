// Tamanho da ROM é de 49152 -> vai de 0 a 49151
// Tamanho da RAM é de  8192 -> vai de 49152 a 57343
// Tamanho para uma expansão -> vai de 57344 a 65471 (~8128 bytes)
// Tamanho de I/O é 64 bytes -> vai de 65472 a 65535
// Memória mapeada vai de 0 a 65535

#ifndef MEMORY_H
#define MEMORY_H

#define SIZE_TOTAL_ADDRESS 65536
#define SIZE_ROM 49152

// (não vai ate 65532, pois vou deixar um espaco reservado para futuros upgrades como mapear uma PPU ou APU)
#define SIZE_RAM 8192

//--------------------------- ESTRUTURA DA MEMORIA ---------------------------

typedef struct {
    unsigned char ADDRESS[SIZE_TOTAL_ADDRESS];
} MEMORY;

//--------------------------------- FUNCOES ----------------------------------

int readWordBinFile(const char* fileName, unsigned char* byteWord) {
    
    FILE* file = fopen(fileName, "rb");  // Abre o arquivo binário para leitura
    
    if (file == NULL) {
        printf("Erro ao abrir o arquivo da ROM.\n");
        return 1;
    }

    // Ler o arquivo byte a byte e armazenar na matriz
    for (int i = 0; i < SIZE_ROM; i++) {
        int byte = fgetc(file); // Lê um byte (8 bits) do arquivo

        if (byte == EOF) {
            // Se chegou ao final do arquivo antes de preencher a matriz
            // printf("Arquivo da ROM menor que o esperado...\n\n");
            break;
        }

        byteWord[i] = (unsigned char) byte; // Armazena o byte na matriz
    }

    // Fechar o arquivo
    fclose(file);

    return 0;  //Sucesso
    
}

#endif //MEMORY_H