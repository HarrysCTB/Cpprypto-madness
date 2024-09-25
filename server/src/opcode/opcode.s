
.data

.align 8
function_table_op_code:
    .quad 0x000000010000e86c  // handleAuthCommand
    .quad 0x000000010003de6c  // handleCreaCommand
    .quad 0x000000010003e954  // handleDecoCommand
    .quad 0x000000010003eb9c  // handleMessCommand


.text

.global _callOpCodeFunc
_callOpCodeFunc:
    // x0 : pointeur vers l'objet (this)
    // x1 : opcode (int)
    // x2 : pointeur vers clientData (void*)
    // x3 : référence à std::vector<std::string> (pointeur vers le vecteur)

    cmp x1, #0x04
    b.ge error_opcode

    lsl x4, x1, #3 
    ldr x5, =function_table_op_code 
    ldr x6, [x5, x4]

    mov x1, x2 
    mov x2, x3

    blr x6 

error_opcode:
    mov x0, #0
    ret
