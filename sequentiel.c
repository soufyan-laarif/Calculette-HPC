#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<unistd.h>
#include<time.h> // Pour calculer le temps d'exécution

int main(int argc, char* argv[]){

	clock_t t;
	t = clock();
	// Sauvegarder les variables passé en parametres
	int a      = atoi(argv[1]);
        int b      = atoi(argv[2]);
        char* op1  = argv[3];
        int c      = atoi(argv[4]);
        int d      = atoi(argv[5]);
        char* op2  = argv[6];
        char* op3  = argv[7];

        // Intialiser les resultats de calculs
        int resultat_a_b   = 0;
        int resultat_c_d   = 0;
        int resultat_total = 0;

	// Calculer : resultat_a_b
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
	printf("\n---Opération entre a et b : %d---\n", resultat_a_b);

	// Calculer : resultat_c_d
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
	printf("\n---Opération entre c et d : %d---\n", resultat_c_d);

	// Calculer : resultat_a_b
        switch(*op3){
	        case ('*'):
                        resultat_total = resultat_a_b * resultat_c_d;
                        break;
                case ('+'):
                        resultat_total = resultat_a_b + resultat_c_d;
                        break;
                case ('-'):
                        resultat_total = resultat_a_b - resultat_c_d;
                        break;
	        case ('/'):
        	        resultat_total = resultat_a_b / (float)resultat_c_d;
			break;
	}
	printf("\n---Resultat Total : %d---\n", resultat_total);

	/*
	printf("a : %d\n",a);
	printf("operation entre a et b : %c\n", *op1);
	*/

	t = clock() - t; 

	double temps_seq = ((double)t)/CLOCKS_PER_SEC; // in seconds
	printf("Le programme séquentiel prend %f secondes en exécution\n", temps_seq);
	// Création du fichier temps_sequentiel_seq.txt
	FILE *seq_ptr;
	seq_ptr = fopen("temps_execution_seq.txt", "w+");
	fprintf(seq_ptr,"%f", temps_seq);
	printf("After creation of temps_seq file");

	return 0;
}

