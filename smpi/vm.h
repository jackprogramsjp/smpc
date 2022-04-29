#ifndef HEADER_SMPI_VM_H
#define HEADER_SMPI_VM_H

#include <stddef.h>
#include "../bytecode.h"

typedef int SMPI_ValType;

typedef struct SMPI_Register {
    SMP_BYTE code[SMP_BYTE_SIZE];
    SMPI_ValType *r;
    size_t pos, rpos;
} SMPI_Register;

typedef enum {
    SMPI_NoError,
    SMPI_MaxBytes,
    SMPI_StoreMustHaveArgument,
    SMPI_PrintMustHaveArgument,
} SMPI_RegisterError;

SMPI_Register *SMPI_Register_init(void);
SMPI_RegisterError SMPI_Register_push(SMPI_Register *, SMP_BYTE);
const char *SMPI_RegisterError_str(SMPI_RegisterError);
SMPI_RegisterError SMPI_Register_run(SMPI_Register *);

SMPI_RegisterError SMPI_Register_print(SMPI_Register *, SMP_BYTE);
SMPI_RegisterError SMPI_Register_store(SMPI_Register *, SMP_BYTE, SMP_BYTE);

void SMPI_Register_free(SMPI_Register *);

#endif /* HEADER_SMPI_VM_H */
