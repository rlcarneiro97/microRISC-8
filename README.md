## microRISC-8 e Assembler microRISC-8

**microRISC-8** é um processador de arquitetura RISC de 8 bits, que foi idealizado e implementado em linguagem C e com arquitetura documentada (ISA - Instruction Set Architecture). Inspirado nos microprocessadores clássicos dos anos 80, ele foi projetado para ser simples, funcional e educativo.

**Assembler microRISC-8** é um montador (assembler) feito em Java, simples e direto. Ele simplesmente converte os mnemônicos em dados binários e não faz nenhuma verificação de sintaxe (confiando muito na capacidade do programador). Assim, você pode testar seus códigos com o mínimo de dignidade, sem a necessidade de fazer conversão dos mnemônicos em binário no braço (como faziam os antigos Incas rsrs).

---

## 📌 Especificações Gerais

- **Arquitetura**: RISC (Reduced Instruction Set Computer)
- **Tamanho**: 8 bits
- **Clock Estimado**: 2 MHz a 4 MHz
- **Clock Real**: Igual ao clock do processador que o emula. 
- **Registradores**:
  - **14 Registradores Gerais**: R1 a R14 (8 bits)
  - **Acumulador**: ACC ou R0 (8 bits)
  - **Registrador Zero**: RZ ou R15 (8 bits) — valor sempre `0x00`
  - **Program Counter (PC)**: 16 bits — (Por padrão vale: `0x0000`)
  - **Instruction Register (IR)**: 8 bits
  - **Status Register (SR)**: 8 bits
    - Bit 0: Carry (C)
    - Bit 1: Zero (Z)
  - **Stack Pointer (SP)**: 16 bits (Pilha decrescente. Inicia em: `0xE000`)
  - **Global Pointer (GP)**: 16 bits (valor padrão: `0xC000`)
  - **Memory Address Register (MAR)**: 16 bits
  - **Memory Data Register (MDR)**: 8 bits

---

## 🧠 Organização da Memória (64 KB)

| Faixa de Endereço  | Descrição              | Tamanho   |
|--------------------|------------------------|-----------|
| 0x0000 – 0xBFFF    | ROM (somente leitura)  | 48 KB     |
| 0xC000 – 0xDFFF    | RAM (leitura/escrita)  | 8 KB      |
| 0xE000 – 0xFFBF    | Área para expansão     | ~8 KB     |
| 0xFFC0 – 0xFFFF    | I/O (Entrada/Saída)    | 64 B      |

### 🧾 Mapeamento I/O

| Endereço  | Função                  								|
|-----------|-------------------------------------------------------|
| 0xE000    | Stack Pointer da sub-rotina							|
| 0xFFFB    | DATA_STATE do INPUT 						 			|
| 0xFFFC    | Valor do INPUT		     							|
| 0xFFFD    | INPUT_MODE (1 = Char Immediate, 2 = Char, 3 = Integer)|
| 0xFFFE    | OUTPUT_MODE (1 = Char, 2 = Integer)  					|
| 0xFFFF    | Valor do OUTPUT        		 						|

- OBS: Como esse processador não tem interrupções como os processadores modernos, o funcionamento dele é por `Polling`, ou seja, sempre está verificando a mudança dos status em pontos mapeados na memória.

---

## 🧮 Modos de Endereçamento

- **Registradores**: acesso direto ao conteúdo de registradores (ex: `R1`, `ACC`)
- **Imediatos**: valores constantes embutidos na instrução (ex: `#10`, `#-3`)
- **Caracteres**: caracteres ASCII entre aspas simples (ex: `'A'`)
- **Endereço absoluto de memória**: acesso direto via endereço fixo (ex: `&49152`)
- **Labels**: nomes simbólicos para endereços (ex: `CALL SOMA`)

---

## ⚙️ Instruções e Opcodes

| Opcode | Instrução   											| Descrição                                 | Ciclos |
|--------|------------------------------------------------------|-------------------------------------------|--------|
| 0      | `LDA`       											| Load from address                        	| 4      |
| 1      | `LDI`       											| Load immediate                           	| 3      |
| 2      | `STA`       											| Store to address                         	| 4      |
| 3      | `MOV`       											| Move entre registradores            		| 2      |
| 4–7    | `ADD`, `ADD.I`, `SUB`, `SUB.I` 						| Operações aritméticas    					| 2–3    |
| 8–9    | `SHT.L`, `SHT.R` 									| Shift lógico                       		| 2      |
| 10     | `HLT`       											| Halt                                		| 1      |
| 11     | `JMP`       											| Salto incondicional                		| 3      |
| 12–13  | `CMP`, `CMP.I` 										| Comparação                          		| 2–3    |
| 14–19  | `BEQ`, `BNE`, `BLE`, etc. 							| Saltos condicionais absolutos 			| 3      |
| 20–25  | `BEQ.R`, `BNE.R`, etc. 								| Saltos condicionais relativos    			| 2      |
| 26–29  | `AND`, `OR`, `XOR`, `NOT` 							| Lógicas entre registradores   			| 2      |
| 30     | `END`       											| Finaliza execução                			| 1      |
| 31–33  | `IN`, `OUT` 											| I/O                                 		| 1      |
| 34–35  | `CALL`, `RET` 										| Sub-rotinas com pilha                     | 1–3    |
| 36–41  | `INI.P`, `SET.P`, `GET.P`, `UPD.P`, `UPI.P` 			| Manipulação do ponteiro GP				| 1–3 	 |

---

## 🧾 Exemplo de Assembly

```asm
LDI R0, #0
LDI R1, #0
LDI R2, #0
LDI R3, #0
LDI R4, #0
LDI R5, #0

CALL TEXT
CALL READ_INTEGER
MOV R1, R0
CALL TEXT
CALL READ_INTEGER
MOV R2, R0
ADD R1, R2
MOV R0, R1
CALL MODO_INTEGER_OUT
OUT
HLT

CALL MODO_CHAR_OUT
LDI R0, #13
OUT
LDI R0, #13
OUT
CALL TEXT
CALL READ_CHAR
OUT
HLT

CALL MODO_CHAR_OUT
LDI R0, #13
OUT
LDI R0, #13
OUT
CALL TEXT
CALL READ_CHAR_I
OUT

END

TEXT:
	CALL MODO_CHAR_OUT
	LDI R0, 'D'
	OUT
	LDI R0, 'I'
	OUT
	LDI R0, 'G'
	OUT
	LDI R0, 'I'
	OUT
	LDI R0, 'T'
	OUT
	LDI R0, 'E'
	OUT
	LDI R0, ':'
	OUT
	LDI R0, ' '
	OUT
	RET

;---------------------------------------------------------------------------------------------

MODO_CHAR_OUT:
	LDI R5, #1 ; CARREGA O VALOR DO MODO DE OUTPUT (char - modo 1)
	STA R5, &65534 ; INSERE O VALOR DO OUTPUT_MODE NA MEMORIA
	RET

MODO_INTEGER_OUT:
	LDI R5, #2 ; CARREGA O VALOR DO MODO DE OUTPUT (inteiro - modo 2)
	STA R5, &65534 ; INSERE O VALOR DO OUTPUT_MODE NA MEMORIA
	RET

;---------------------------------------------------------------------------------------------

MODO_CHAR_I:
	LDI R4, #1 ; CARREGA O VALOR DO MODO DE INPUT (char - modo 1)
	STA R4, &65533 ; INSERE O VALOR DO INPUT_MODE NA MEMORIA
	RET

MODO_CHAR:
	LDI R4, #2 ; CARREGA O VALOR DO MODO DE INPUT (char - modo 2)
	STA R4, &65533 ; INSERE O VALOR DO INPUT_MODE NA MEMORIA
	RET
	
MODO_INTEGER:
	LDI R4, #3 ; CARREGA O VALOR DO MODO DE INPUT (inteiro - modo 3)
	STA R4, &65533 ; INSERE O VALOR DO INPUT_MODE NA MEMORIA
	RET

;---------------------------------------------------------------------------------------------

READ_CHAR_I:
	CALL MODO_CHAR_I ; SETA O MODO DE INPUT PARA CARACTERE IMEDIATO
	LDA R3, &65531 ; CARREGA O DATA_STATE DE INPUT VERIFICANDO SE ESTA PRONTO
	CMP.I R3, #0
	BEQ.R #-7
	IN
	RET

READ_CHAR:
	CALL MODO_CHAR ; SETA O MODO DE INPUT PARA CARACTERE
	LDA R3, &65531 ; CARREGA O DATA_STATE DE INPUT VERIFICANDO SE ESTA PRONTO
	CMP.I R3, #0
	BEQ.R #-7
	IN
	RET
	
READ_INTEGER:
	CALL MODO_INTEGER ; SETA O MODO DE INPUT PARA INTEIRO
	LDA R3, &65531 ; CARREGA O DATA_STATE DE INPUT VERIFICANDO SE ESTA PRONTO
	CMP.I R3, #0
	BEQ.R #-7
	IN
	RET

```
## 🖥️ Instruções de Execução do Emulador

- Para rodar o **microRISC-8**, abra o terminal de sua preferência em `Emulador_microRISC-8/output` e execute o `main.exe`. 
- Lembre-se de deixar o arquivo `ROM.bin` sempre na mesma pasta, pois como o nome já diz, ele é o arquivo da memoria ROM e que o emulador irá ler e executar inicialmente.

## 🛠️ Instruções de Execução do Assembler e Criação do Arquivo Binário

- Antes de rodar o programa, certifique-se de deixar o arquivo `main.asm` na pasta raiz do projeto em `/Assembler_microRISC-8`.
- Para rodar o **Assembler microRISC-8**, segue a mesma ideia do emulador, abra o terminal de sua preferência em `/Assembler_microRISC-8` e execute o comando `java assembler.java -a` ou `java assembler.java -a main.asm`.
- Por padrão, o programa irá buscar o arquivo `main.asm`, mas você pode executa-lo usando outro nome. Para isso, passe o nome dele depois do parâmetro `-a` na hora da execução, por exemplo, se meu Assembly for `meu-assembly.asm`, você colocará `java assembler.java -a meu-assembly.asm`
- O Assembler só permite gerar um binário com o nome `ROM.bin`, sendo este o nome do binário da memória de leitura.
- O menu de ajuda pode ser acessado escrevendo `java assembler.java -h` ou `java assembler.java -help`.

## 📦 Instruções de Execução de um Novo Arquivo Binário

- Para rodar seu binário personalizado, realize o passo passado de gerar o `ROM.bin` pelo Assembler.
- Com o `ROM.bin` gerado, basta copia-lo para dentro da pasta `Emulador_microRISC-8/output`. Se já houver um arquivo de nome igual, ou você renomeia-o para não perde-lo, ou você copia, cola e substitui este pelo novo arquivo. Depois, basta executar o emulador!