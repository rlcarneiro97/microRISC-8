#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cpu.h"
#include "memory.h"

int main(){

	setlocale(LC_ALL, "Portuguese_Brazil");
	
	CPU cpu = {0}; // inicializa a estrutura do processador
	MEMORY memory = {0}; // inicializa a estrutura da memoria

	runCPU(&cpu, &memory); // inicializa o processador

	return 0;

}