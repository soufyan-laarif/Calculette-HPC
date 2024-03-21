#include"ipcsem.h"
#include"stdlib.h"
#include"string.h"
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<time.h> // Pour calculer le temps d'exécution

int Num;
// prototype des fonctions
void P1(int a, int b, char* op1);//processuse 1
void P2(int c, int d, char* op2);//processuse 2
void P3(char* op3);//processuse 3

/* Structure pour envoyer ou recevoir les msgs */
typedef struct{
	long mtype;
	int mcontent;
}msg;
msg msg1, msg2, msg3;
#define LGMES sizeof(msg1.mcontent)

int main(int argc, char* argv[])
{
	clock_t t;
	t = clock();
	/* ---- Calculer le temps d'exécution du programme IPC ---- */
	//clock_t start, end;
	//double cpu_time_used;
	//start = clock();

	/* ---------------------------------------------------------*/
	// declartion semaphore unix
	CreerSem(100,2);
	InitSem(0, 0);
	InitSem(1, 0);
	//pipe(tub1);
	//pipe(tub2);
	//pipe(tub3);

	// intialiser les resultats de calculs
	int resultat     = 0;
	int resultat_a_b = 0;
	int resultat_c_d = 0;

	// sauvegarder les variables passé en parametres.
	int a      = atoi(argv[1]);
	int b      = atoi(argv[2]);
	char* op1  = argv[3];
	int c      = atoi(argv[4]);
	int d      = atoi(argv[5]);
	char* op2  = argv[6];
	char* op3  = argv[7];

	P1(a, b, op1);
	P2(c, d, op2);
	P3(op3);
	int p;
	//read(tub3[0],&p,4);

	for(int i=0;i<3;i++)wait(0);
	//FILE *fpt;
	//fpt = fopen("MyFile.txt", "w+");
	//fprintf(fpt,"%d",p);

	//fclose(fpt);
	
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("Le programme IPC a pris %f secondes en exécution \n", time_taken);
	FILE *ipc_ptr;
	ipc_ptr = fopen("temps_execution_ipc.txt", "w+");
	fprintf(ipc_ptr,"%f", time_taken);


	return 0;
}
void P1(int a, int b, char* op1){
	if(fork()==0){
		int resultat_a_b;
		int numfms=msgget(10,IPC_CREAT|0666);
		printf("id interne de P1 : %d\n", numfms);
		if(numfms==-1){
			perror("case 1 erreur msgget");
			exit(1);
		}
		// Calculer l'opération entre a et b
		switch(*op1){
			case ('*'):
				resultat_a_b = a*b;
				break;
			case ('+'):
				resultat_a_b = a+b;
				break;
			case ('-'):
				resultat_a_b = a-b;
				break;
			case ('/'):
				resultat_a_b = a/(float)b;
				break;
		}
		msg1.mtype = 100;
		msg1.mcontent = resultat_a_b;
		if(msgsnd(numfms,&msg1,LGMES,IPC_NOWAIT)==-1){
			perror("case 4 erreur msgsnd");
		}
		//write(tub1[1],&a,4);
		V(0);
		exit(0);
	}
}
void P2(int c, int d, char* op2){

	if(fork()==0){
		int numfms = msgget(10,IPC_CREAT|0666);
		printf("id interne de P2 : %d\n", numfms);
		if(numfms==-1){
			perror("case 1 erreur msgget");
			exit(1);
		}
		int resultat_c_d;
		switch(*op2){
			case ('*'):
				resultat_c_d = c*d;
				break;
			case ('+'):
				resultat_c_d = c+d;
				break;
			case ('-'):
				resultat_c_d = c-d;
				break;
			case ('/'):
				resultat_c_d = c/(float)d;
				break;
		}
		msg2.mtype = 200;
		msg2.mcontent = resultat_c_d;
		if(msgsnd(numfms,&msg2,LGMES,IPC_NOWAIT)==-1){
			perror("case 4 erreur msgsnd");
		}
		//write(tub2[1],&b,4);
		V(1);
		exit(0);
	}
}

void P3(char* op3){
	if(fork()==0){
		//attent processus P1 et P2 en utilise semaphore unix pour excute processus P3
		P(0);
	        P(1);
	        //int a,b;
	        int resultat;
		int numfms = msgget(10,IPC_CREAT|0666);
		printf("id interne de P3 : %d\n", numfms);
		int n1=msgrcv(numfms,&msg1,LGMES,100,IPC_NOWAIT); /* type determine */
		int n2=msgrcv(numfms,&msg2,LGMES,200,IPC_NOWAIT); /* type determine */
		if((n1 < 0) || (n2 < 0)){
			perror("case 5 erreur msgrcv");
			exit(4);
		}

		//read(tub1[0],&a,4);
	        //read(tub2[0],&b,4);

	        if(strcmp(op3, "+") == 0)
		        resultat = msg1.mcontent + msg2.mcontent;
	        else if(strcmp(op3, "-") == 0)
	        	resultat = msg1.mcontent - msg2.mcontent;
	        else if(strcmp(op3, "*") == 0)
		        resultat = msg1.mcontent * msg2.mcontent;
	        else if(strcmp(op3, "/") == 0)
			resultat = msg1.mcontent / (float)msg2.mcontent;
		//write(tub3[1],&r,4);
		printf("\n-----Resultat total : %d-----\n", resultat);
		/* Ecrire les resultats dans un fichier, pour les lires depuis java */
		FILE *fpt;
		fpt = fopen("MyFile.txt", "w+");
		fprintf(fpt,"%d",resultat);
		fclose(fpt);
		exit(0);
	}
}


void CreerSem(key_t cle, int N) {
	Num=semget(cle, N, 0600 | IPC_CREAT);
	if(Num==-1)
	{
	perror("Pb CreerSem");exit(1);
	}
}
/* Detruit le groupe de semaphores Num */
void DetruireSem() {
	semctl(Num, 0, IPC_RMID, 0);
}
/* Initialier le semaphore N du groupe Num a la valeur V */
void InitSem(int N, int V) {
	semctl(Num, N, SETVAL, V);
}
/* Realise P sur le semaphore N du groupe Num */
void P(int N) {
	struct sembuf Tabop; /* une seule operation */
	Tabop.sem_num=N;
	Tabop.sem_op=-1;
	Tabop.sem_flg=0; /* bloquant */
	semop(Num, &Tabop,1);
}
/* Realise V sur le semaphore N du groupe Num */
void V(int N) {
	struct sembuf Tabop; /* une seule operation */
	Tabop.sem_num=N;
	Tabop.sem_op=1;
	Tabop.sem_flg=0;
	semop(Num, &Tabop, 1);
}

void attente(int N)
{
	sleep(rand() % N);
}
