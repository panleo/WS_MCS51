ORG 0000h          ; Define o endereço de início do programa

; Inicialização dos registradores
MOV R0, #0         ; Inicializa R0 (contador de números menores que R7)
MOV R1, #0         ; Inicializa R1 (contador de números maiores que R7)
MOV R2, #0         ; Inicializa R2 (contador de múltiplos de R7)
MOV R7, #2         ; Define o valor de referência em R7

; Aponta para o início da lista
MOV DPTR, #LISTA   ; Carrega o endereço da lista em DPTR

; Loop para percorrer a lista
MOV R3, #12        ; R3 é o contador de itens na lista (12 números)
LOOP:
    MOV A, #0      ; Zera o acumulador
    MOVC A, @A+DPTR; Lê o valor da lista apontado por DPTR
    INC DPTR       ; Incrementa DPTR para o próximo item da lista

    ; Compara o valor lido com R7
    CJNE A, 07h, COMPARE ; Compara A com R7 (valor de referência)
    JMP IGUAL       ; Se A = R7, salta para IGUAL

    COMPARE:
        JC MENOR    ; Se A < R7, salta para MENOR
        JMP MAIOR   ; Se A > R7, salta para MAIOR

    MENOR:
        INC R0      ; Incrementa o contador de números menores
        JMP NEXT    ; Vai para o próximo número

    MAIOR:
        INC R1      ; Incrementa o contador de números maiores
        JMP NEXT    ; Vai para o próximo número

    IGUAL:
        ; Se A = R7, não incrementa nenhum contador
        JMP NEXT    ; Vai para o próximo número

    NEXT:
        DJNZ R3, LOOP ; Decrementa R3 e repete o loop se R3 != 0

; Verifica múltiplos
MOV DPTR, #LISTA   ; Reinicia DPTR para o início da lista
MOV R3, #12        ; Reinicia o contador de itens na lista
LOOP_MULT:
    MOV A, #0      ; Zera o acumulador
    MOVC A, @A+DPTR; Lê o valor da lista apontado por DPTR
    INC DPTR       ; Incrementa DPTR para o próximo item da lista

    ; Verifica se A é múltiplo de R7
    MOV B, R7      ; Move R7 para B
    DIV AB         ; Divide A por B (R7)
    MOV A, B       ; Move o resto da divisão para A
    JZ MULTIPLO    ; Se o resto for zero, A é múltiplo de R7
    JMP NEXT_MULT  ; Caso contrário, vai para o próximo número

    MULTIPLO:
        INC R2     ; Incrementa o contador de múltiplos

    NEXT_MULT:
        DJNZ R3, LOOP_MULT ; Decrementa R3 e repete o loop se R3 != 0

; Fim do programa
SJMP $             ; Loop infinito para finalizar o programa

; Lista de números
LISTA:
    DB 210, 8, 103, 54, 31, 1, 9, 36, 81, 2, 15, 27

END