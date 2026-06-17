#include "ReadFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

/*
 * computed using echo '2^20 -1'|bc
 * This program has limited need for files. There should never be a file,
 * whether a config for a set of keys, that will be 1MiB is size. This is
 * profusely generous.
 */
#define MAX_FILE_SIZE    1048575

/*
 * TLO 1.6 - General understanding of using library functions.
 */
int ReadFile(const char* file, void **contents, uint32_t *size)
{
    int ret = -EINVAL;
    FILE *fin = NULL;
    uint8_t *tContents = NULL;

    if (file && contents && !*contents && size && *size > 0 && *size < MAX_FILE_SIZE)
    {
        fin = fopen(file, "rb");
        if (!fin)
        {
            goto exit_ReadFile;
        }

        struct stat fileInfo = {0};

        ret = fstat(fileno(fin), &fileInfo);
        if (ret < 0)
        {
            goto exit_ReadFile;
        }

        tContents = malloc(fileInfo.st_size);
        if (!tContents)
        {
            ret = -ENOMEM;
            goto exit_ReadFile;
        }

        ret = fread(tContents, sizeof(*tContents), fileInfo.st_size, fin);
        if (ret == fileInfo.st_size)
        {
            ret = 0;
            *size = fileInfo.st_size;
            *contents = tContents;
        }
        else
        {
            /* Some sort of error so release the memory and return the error */
            *size = 0;
            free(tContents);
            if (feof(fin))
            {
                ret = -EBADF;
            }
            else
            {
                ret = errno;
            }
        }
    }

exit_ReadFile:
    if (fin) fclose(fin);

    return ret;

}
