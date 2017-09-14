#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "miscutils.h"

int miscutils::getexitcode(int exitstatus)
{
    if (WIFEXITED(exitstatus)) 
    {
        return WEXITSTATUS(exitstatus);
    } else if (WIFSIGNALED(exitstatus)) 
    {
        return  WTERMSIG(exitstatus);
    }
    return 0;
}
