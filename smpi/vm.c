#include <stdlib.h>
#include <string.h>
#include "vm.h"
#include "../failure.h"

SMPI_Register *SMPI_Register_init(void) {
    SMPI_Register *reg = (SMPI_Register *)malloc(sizeof *reg);
    if (reg == NULL) {
        SMP_FAILURE("Failed to allocate a SMPI Register based Virtual Machine in memory");
    }
    reg->pos = 0, reg->rpos = 0;
    memset(reg->code, 0, sizeof(reg->code) / sizeof(reg->code[0]));
    reg->r = (SMPI_ValType *)malloc(sizeof *reg->r * 1000); /* for now, 1000 */
    return reg;
}

SMPI_RegisterError SMPI_Register_push(SMPI_Register *reg, SMP_BYTE byte) {
    if (reg->pos < SMP_BYTE_SIZE) {
        reg->code[reg->pos++] = byte;
    } else {
        return SMPI_MaxBytes;
    }

    return SMPI_NoError;
}

SMPI_RegisterError SMPI_Register_store(SMPI_Register *reg, SMP_BYTE regn, SMP_BYTE val) {
    SMPI_RegisterError error = SMPI_NoError;

    if ((error = SMPI_Register_push(reg, SMP_STORE)) != SMPI_NoError) {
        return error;
    }

    if ((error = SMPI_Register_push(reg, regn)) != SMPI_NoError) {
        return error;
    }

    if ((error = SMPI_Register_push(reg, val)) != SMPI_NoError) {
        return error;
    }

    return error;
}

SMPI_RegisterError SMPI_Register_print(SMPI_Register *reg, SMP_BYTE regn) {
    SMPI_RegisterError error = SMPI_NoError;

    if ((error = SMPI_Register_push(reg, SMP_PRINT)) != SMPI_NoError) {
        return error;
    }

    if ((error = SMPI_Register_push(reg, regn)) != SMPI_NoError) {
        return error;
    }

    return error;
}

SMPI_RegisterError SMPI_Register_run(SMPI_Register *reg) {
    size_t codesize = sizeof(reg->code) / sizeof(reg->code[0]);
    size_t regpos;
    for (size_t i = 0; i < codesize; i++) {
        switch (reg->code[i]) {
            case SMP_STORE:
                i++;
                if (i > codesize) {
                    return SMPI_StoreMustHaveArgument;
                }
                regpos = reg->code[i];
                i++;
                if (i > codesize) {
                    return SMPI_StoreMustHaveArgument;
                }
                reg->r[regpos] = reg->code[i];
                break;
            case SMP_PRINT:
                i++;
                if (i > codesize) {
                    return SMPI_PrintMustHaveArgument;
                }
                regpos = reg->code[i];
                printf("%d\n", reg->r[regpos]);
                break;
            case SMP_EXIT:
                return SMPI_NoError;
        }
    }
    
    return SMPI_NoError;
}

const char *SMPI_RegisterError_str(SMPI_RegisterError error) {
    switch (error) {
        case SMPI_NoError:
            return "No error is found in the register";
        case SMPI_MaxBytes:
            return "The SMPI Register machine has maxed out on the number of bytes/instructions it can hold.";
        case SMPI_StoreMustHaveArgument:
            return "The SMPI Store bytecode must have two arguments: register number, and value.";
        case SMPI_PrintMustHaveArgument:
            return "The SMPI Print bytecode must have an argument: register number/position to print.";
    }

    return NULL;
}

void SMPI_Register_free(SMPI_Register *reg) {
    free(reg->r);
    free(reg);
}
