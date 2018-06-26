#include <stdio.h>

#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <xlat.h>
#include <syscall.h>
//TODO: Check return value

static int trace_syscall(int pid)
{
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    printxvals(regs.orig_rax, "not known", syscall);
    if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL))
    {
        fprintf(stderr, "an error occured while tracing the programm\n");
        return -1;
    }
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    int status;
    if (!(waitpid(pid, &status, 0) && !WIFEXITED(status)))
        return -1;
    if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL))
    {
        fprintf(stderr, "an error occured while tracing the programm\n");
        return -1;
    }
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    printf(" with return value: %lld\n", regs.rax);
    return 0;
}

static int exec_and_trace(int argc, char **argv)
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    void *str = NULL;
    if (argc == 2)
        execvp(argv[1], str);
    else
        execvp(argv[1], argv + 2);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "too few args");
        return 1;
    }
    int pid;
    if (!(pid = fork()))
    {
        exec_and_trace(argc, argv);
    }
    else
    {
        int status;
        while (waitpid(pid, &status, 0) && !WIFEXITED(status))
            trace_syscall(pid);
        printf("exit with status: %d\n", status);
    }
    return 0;
}
