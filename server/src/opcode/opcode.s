.extern __ZN7Command22function_table_op_codeE  // Déclaration de la table externe

.global _callOpCodeFunc
_callOpCodeFunc:
    cmp x1, #0x04              // Compare x1 avec 4
    b.ge error_opcode           // Si x1 >= 4, aller à l'erreur

    ldr x5, =__ZN7Command22function_table_op_codeE  // Charger l'adresse de la table d'opcode
    ldr x6, [x5, x1, lsl #3]    // Charger l'adresse de la fonction

    cbz x6, error_opcode        // Si l'adresse est nulle, aller à l'erreur

    mov x1, x2                  // Préparer les arguments
    mov x2, x3

    blr x6                      // Appeler la fonction via le pointeur

error_opcode:
    mov x0, #0                  // Retourner 0 en cas d'erreur
    ret
