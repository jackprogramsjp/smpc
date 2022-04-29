#include <stdio.h>
#include <stdlib.h>
#include "vm.h"

int main(void) {
    SMPI_Register *reg = SMPI_Register_init();
    SMPI_RegisterError error = SMPI_NoError;

    SMPI_Register_store(reg, 0, 15);
    SMPI_Register_store(reg, 1, 20);
    SMPI_Register_print(reg, 0);
    SMPI_Register_print(reg, 1);

    if ((error = SMPI_Register_run(reg)) != SMPI_NoError) {
        fprintf(stderr, "%s\n", SMPI_RegisterError_str(error));
        fflush(stderr);
    }

    return 0;
}
