#include <stdlib.h>

void f(int n, siginfo_t *n1, void *aux){printf("Entro manej\n");}
int main(int a, char **a1){
	int i,j,k; sigset_t s1;
	struct sigaction sa; siginfo_t v;
	sigemptyset(&s1);
	sigaddset(&s1, SIGALRM);
	sa.sa_flags=SA_SIGINFO;
	sa.sa_sigaction=f;
	sigfillset(&sa.sa_mask);
	sigprocmask(SIG_BLOCK, &s1, NULL);
	alarm(3);
	sigwaitinfo(&s1, &v);
	printf("Alarma llego\n");
}