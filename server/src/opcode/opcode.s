.text

.extern __ZN7Command17handleAuthCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
.extern __ZN7Command17handleCreaCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
.extern __ZN7Command17handleMessCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
.extern __ZN7Command17handleDecoCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE

.global _callOpCodeFunc

_callOpCodeFunc:
    // x0 : pointeur vers l'objet (this)
    // x1 : opcode (int)
    // x2 : pointeur vers clientData (void*)
    // x3 : référence à std::vector<std::string> (pointeur vers le vecteur)

    cmp x1, #0x04
    b.gt .exit

    lsl x4, x1, #3
    ldr x5, =function_table_op_code
    ldr x6, [x5, x4]
    cbz x6, .exit

    mov x1, x2
    mov x2, x3

    blr x6

.exit:
    ret

.data
.align 3
function_table_op_code:
    .quad __ZN7Command17handleAuthCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
    .quad __ZN7Command17handleCreaCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
    .quad __ZN7Command17handleMessCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
    .quad __ZN7Command17handleDecoCommandEP10ClientDataNSt3__16vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEE
