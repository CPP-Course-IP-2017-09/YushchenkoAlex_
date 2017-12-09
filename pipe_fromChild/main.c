#include "stdio.h"
#include "string.h"      // strlen strrchr
#include "stdlib.h"      // for exit
#include <sys/wait.h>    // for wait_pid
#include <unistd.h>      // for pipe, dup2, execl, fork, sleep


#define	DEF_PAGER	"/bin/more"		/* default pager program */
#define	DEF_PROC	"/sbin/ifconfig"		/* default process */
#define MAXLINE 4096

#define err_quit(a) \
{printf("ERROR!! %s \n", a);\
exit(0);}

#define err_sys(a) \
{printf("ERROR!! %s \n", a);\
exit(0);}

/*
void err_sys(const char * a, char * par = 0)
{
    char sBuff[200];
    if (par == 0)
        printf("ERROR!! %s \n", a);
    else
    {
        sprintf(sBuff, a, par);
        printf("ERROR!! %s \n", sBuff);
    }
    exit(0);
}
*/

int
main(int argc, char *argv[])
{
    int		fd[2];
    pid_t	pid;
    char	*proc, *argv0;
    char	sBuff[MAXLINE];

    printf("arguments count = %d \n", argc);
    if (argc != 2)
    {
        proc = DEF_PROC;
        printf("usage: a.out <path to program> \n");
        printf("the -ifconfig- will be launched \n");
    }
    else
        proc = argv[1];

    if (pipe(fd) < 0)
        err_sys("pipe error");
    printf("pipe OK \n");

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    }
   else if (pid > 0)								           /* parent */
   {
        close(fd[1]);	                        	           /* close write end */
        printf("fork OK in parent \n");
        if(waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
                                                     /* parent reads child's output */
        int nBytes = 1, nTotal = 0;
        while(nBytes != 0 && nTotal < MAXLINE - 1)   // -1 to place 0 at the str end
        {
            nBytes = read(fd[0], sBuff + nTotal, MAXLINE - 1 - nTotal);
            nTotal += nBytes;
        }
        sBuff[nTotal] = 0;
        if(nBytes > 0)
            printf("Not all data was readed from pipe... \n");
        else
            printf("Data readed from pipe:\n\n%s\n", sBuff);

        close(fd[0]);	/* close read end of pipe*/
        exit(0);
    } else                                               /* child */
    {
        close(fd[0]);	/* close read end */
        if (fd[1] != STDOUT_FILENO) {
            if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO)
                err_sys("dup2 error to stdout");
            close(fd[1]);	/* don't need this after dup2 */
        }

        /* get arguments for execl() */
        if ((argv0 = strrchr(proc, '/')) != NULL)
            argv0++;		/* step past rightmost slash */
        else
            argv0 = proc;	/* no slash in pager */

        if (execl(proc, argv0, (char *)0) < 0)
            //err_sys("execl error for %s", pager);
            err_sys("execl error for  pager");
    }
    exit(0);
}
