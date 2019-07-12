#include <stdio.h>
#include <signal.h>

void manej(int sig, siginfo_t *info, void *p){printf("ENTRA MANEJ\n");}

int main(int narg, char **args)
{
	sigset_t sigs; struct sigaction acc; siginfo_t info;
	
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGALRM);
	sigprocmask(SIG_BLOCK, &sigs, NULL);
	acc.sa_flags=SA_SIGINFO;
	acc.sa_sigaction=manej;
	sigemptyset(&acc.sa_mask);
	sigaction(SIGALRM, &acc, NULL);
	
	alarm(3); printf("Se ha puesto alarma de 3 segundos\n");
	sigwaitinfo(&sigs, &info);
	printf("ALARMA LLEGO\n"); 
}
	