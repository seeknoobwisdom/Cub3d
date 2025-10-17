#include "include/cub3d.h"

void    free_array(char **array)
{
    int i;

    i = 0;
    if (array)
    {
        while(array[i])
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
    else
        return;
}

void    ahasna(t_cub3d   *cub3d)
{
    free(cub3d->c);
    free(cub3d->f);
    free(cub3d->no);
    free(cub3d->so);
    free(cub3d->we);
    free(cub3d->ea);
    if (cub3d->map)
        free_array(cub3d->map);
}

/*
0 → Success
1 → General error (catch-all)
2 → Misuse of shell builtins (for shells, optional for general apps)
64 → Command line usage error (invalid arguments)
65 → Data format error (bad input file, corrupted data)
66 → Cannot open input (file not found / permission denied)
67 → Addressee unLknown (often for mail programs)
70 → Internal software error (logic error, assertion failed)
71 → System error (e.g., malloc failed, resource unavailable)
72 → Critical OS file missing (config or dependency missing)
73 → Cannot create output file
74 → I/O error (disk full, read/write failure)
75 → Temporary failure (retry might work, e.g., network issue)
77 → Permission denied (not allowed to access resource)
78 → Configuration error (bad settings, missing environment
*/
void    error(char  *error,int  exitcode, t_cub3d   *cub3d)
{
    ahasna(cub3d);
    printf("\033[31mError\nExit code(%d)->%s\033[0m\n", exitcode, error);
    exit(exitcode);
}