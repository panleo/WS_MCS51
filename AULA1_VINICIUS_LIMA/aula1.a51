ORG 0000h          ; Define o endere�o de in�cio do programa

; Inicializa��o dos registradores
MOV R0, #0         ; Inicializa R0 (contador de n�meros menores que R7)
MOV R1, #0         ; Inicializa R1 (contador de n�meros maiores que R7)
MOV R2, #0         ; Inicializa R2 (contador de m�ltiplos de R7)
MOV R7, #2         ; Define o valor de refer�ncia em R7

; Aponta para o in�cio da lista
MOV DPTR, #LISTA   ; Carrega o endere�o da lista em DPTR

; Loop para percorrer a lista
MOV R3, #12        ; R3 � o contador de itens na lista (12 n�meros)
LOOP:
    MOV A, #0      ; Zera o acumulador
    MOVC A, @A+DPTR; L� o valor da lista apontado por DPTR
    INC DPTR       ; Incrementa DPTR para o pr�ximo item da lista

    ; Compara o valor lido com R7
    CJNE A, 07h, COMPARE ; Compara A com R7 (valor de refer�ncia)
    JMP IGUAL       ; Se A = R7, salta para IGUAL

    COMPARE:
        JC MENOR    ; Se A < R7, salta para MENOR
        JMP MAIOR   ; Se A > R7, salta para MAIOR

    MENOR:
        INC R0      ; Incrementa o contador de n�meros menores
        JMP NEXT    ; Vai para o pr�ximo n�mero

    MAIOR:
        INC R1      ; Incrementa o contador de n�meros maiores
        JMP NEXT    ; Vai para o pr�ximo n�mero

    IGUAL:
        ; Se A = R7, n�o incrementa nenhum contador
        JMP NEXT    ; Vai para o pr�ximo n�mero

    NEXT:
        DJNZ R3, LOOP ; Decrementa R3 e repete o loop se R3 != 0

; Verifica m�ltiplos
MOV DPTR, #LISTA   ; Reinicia DPTR para o in�cio da lista
MOV R3, #12        ; Reinicia o contador de itens na lista
LOOP_MULT:
    MOV A, #0      ; Zera o acumulador
    MOVC A, @A+DPTR; L� o valor da lista apontado por DPTR
    INC DPTR       ; Incrementa DPTR para o pr�ximo item da lista

    ; Verifica se A � m�ltiplo de R7
    MOV B, R7      ; Move R7 para B
    DIV AB         ; Divide A por B (R7)
    MOV A, B       ; Move o resto da divis�o para A
    JZ MULTIPLO    ; Se o resto for zero, A � m�ltiplo de R7
    JMP NEXT_MULT  ; Caso contr�rio, vai para o pr�ximo n�mero

    MULTIPLO:
        INC R2     ; Incrementa o contador de m�ltiplos

    NEXT_MULT:
        DJNZ R3, LOOP_MULT ; Decrementa R3 e repete o loop se R3 != 0

; Fim do programa
SJMP $             ; Loop infinito para finalizar o programa

; Lista de n�meros
LISTA:
    DB 210, 8, 103, 54, 31, 1, 9, 36, 81, 2, 15, 27

END