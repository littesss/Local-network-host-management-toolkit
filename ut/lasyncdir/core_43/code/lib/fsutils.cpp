#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "fsutils.h"

int fsutils::abspath(char* input, char* output)
{
    if(!input)
    {
        return 0;
    }

    realpath(input, output);
    return strlen(output);
}
