#ifndef HEADER_SMP_FAILURE_H
#define HEADER_SMP_FAILURE_H

#include <stdio.h>
#include <stdlib.h>

#define SMP_FAILURE(msg) fputs(msg, stderr); fflush(stderr); abort()

#endif
