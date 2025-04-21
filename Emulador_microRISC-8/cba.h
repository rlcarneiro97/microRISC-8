#ifndef CBA_H
#define CBA_H

#include <stdio.h>

//CHIP BUS CONTROLLER

// ele quem controla o mapeamento de memoria pelo visto, pois dependendo do range de memoria, ele liga ou desliga o chip
// que vai se comunicar com o processador, portanto, ele tem que se comunicar com:
//	
//	 * ROM
//	 * RAM
//	 * I/O

//para as interrupcoes, tem as flags do registrador de status SR, onde tem 2 bits indicando se tem interrupcao critica
//ou interrupcao normal, então em vez de verificar todos dispositivos pra ver se tem interrupcoes, só verificamos 2 bits
//true/false no laco de repeticao do processador

int CBACheckChip(unsigned short int address){

    if(address <= 49151){
        return 0; // Endereço dentro do intervalo da ROM
    }else if(address >= 49152 && address <= 57343){
        return 1; // Endereço dentro do intervalo da RAM
    }else{
        return -1; // Endereço fora dos intervalos especificados
    }

}

#endif //CBA_H