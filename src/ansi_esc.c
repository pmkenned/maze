#include "ansi_esc.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

void
ansi_set(FILE * fp, int n, ...)
{
    if (!isatty(fileno(fp)))
        return;
    int i;
    va_list args;
    fprintf(fp, ANSI_ESC);
    va_start(args, n);

    for (i = 0; i < n; i++) {
        if (i > 0)
            fprintf(fp, ";");
        const char * s = va_arg(args, const char *);
        fprintf(fp, "%s", s);
    }
    fprintf(fp, "m");
    va_end(args);
}

void
ansi_reset(FILE * fp)
{
    if (!isatty(fileno(fp)))
        return;
    fprintf(fp, ANSI_RESET);
}
