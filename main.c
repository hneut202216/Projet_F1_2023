#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include "structures.h"
#include "affichage.c"
#include "lecture_csv.c"

int compare(const void *a, const void *b) {
    struct Pilote *piloteA = (struct Pilote *)a;
    struct Pilote *piloteB = (struct Pilote *)b;

    return (piloteA->temps - piloteB->temps);
}

int main(int argc, char **argv) {
    FILE *file;
    //srand(time(NULL));
    struct stat fileStats;
    char *fileContent;
    char *listeCourses;
    // struct Course course;

    file = fopen("Listes_circuits_de_F1_2023.csv", "r");
    if (file == NULL)
    {
        printf("pas lu");
        return 0;
    }
    // pour retrouver le file descriptor
    int f = fileno(file);
    int indice = 0;
    fstat(f, &fileStats);
    off_t taille = fileStats.st_size;
    char *listeTemp = (char *)malloc(sizeof(char) * taille);
    struct Course *listeFinale = (struct Course *)calloc(taille, sizeof(struct Course));

    fgets(listeTemp, taille, file);

    while (fgets(listeTemp, taille, file) != NULL)
    {
        listeFinale[indice].num = atoi(strtok(listeTemp, ";"));
        strcpy(listeFinale[indice].ville, strtok(NULL, ";"));
        strtok(NULL, ";");
        strcpy(listeFinale[indice].pays, strtok(NULL, ";"));
        strcpy(listeFinale[indice].circuit, strtok(NULL, ";"));
        strcpy(listeFinale[indice].taille, strtok(NULL, ";"));
        strcpy(listeFinale[indice].gp, strtok(NULL, ";"));
        strtok(NULL, ";");
        strcpy(listeFinale[indice].date, strtok(NULL, ";"));
        afficheCourse(listeFinale[indice]);
        indice++;

        if (feof(file))
        {
            break;
        }
    }

    FILE *filePilote;
    struct stat fileStatsPilote;
    char *filePiloteContent;
    filePilote = fopen("Liste_des_pilotes.csv", "r");
    int numFilePilote = fileno(filePilote);
    fstat(numFilePilote, &fileStatsPilote);
    off_t tailleListePilote = fileStats.st_size;
    char *listeTempPilote = (char *)malloc(sizeof(char) * tailleListePilote);
    // struct Pilote *listePilotes = (struct Pilote*) calloc(tailleListePilote,sizeof(struct Pilote));
    int shmid = shmget(77, 21 * sizeof(struct Pilote), IPC_CREAT | 0666);
    struct Pilote *listePilotes = shmat(shmid, 0, 0);

    fgets(listeTempPilote, tailleListePilote, filePilote);
    int indicePilote = 0;
    int trash;
    while (fgets(listeTempPilote, tailleListePilote, filePilote) != NULL)
    {
        trash = atoi(strtok(listeTempPilote, ";"));

        // listePilotes[indice].num = atoi(strtok(listeTempPilote,";"));
        listePilotes[indicePilote].num = atoi(strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].prenom, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].nom, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].team, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].bday, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].nation, strtok(NULL, ";"));
        affichePilote(listePilotes[indicePilote]);
        indicePilote++;
    }
    // printf(" test : %c",listePilotes[0].nom); pq pas bon ?
    int p_id;
    // printf("shmid = %d",shmid);
    // struct Pilote listeAffichage[20];
    for (int i = 0; i < indicePilote; i++)
    {
        // sleep(10);
        int totalF = 0;
        int a = 0;
        srand(time(NULL));
        sleep(1);
        p_id = fork();
        if (p_id == 0)
        {
            //srand(time(NULL));
            
            while (a < 3)
        {
            
            int random = rand() % 20001;
            int finaleR = 25000 + random;
            totalF += finaleR;
            listePilotes[i].tempsTour[a] = finaleR;
            //printf("%d ms        ",finaleR);
            a++;
            
        }

            // listePilotes[i].id = i+1 ;

            listePilotes[i].temps = totalF;
            // usleep(1000000);

            return 0;
            // printf("%d\n",totalF);
            // dup2(fd[1],1);
            // afficheTemps(listePilotes[i]);
            // sleep();
        }

        else if (p_id < 0)
        {
            printf("pas bon erreur");
            return -1;
        }
        else
        {
            // close(fd[1]);
            // wait(NULL);
            // printf("Je suis le padré\n");
            char result[3000];
            // close(fd[1]);
            // read(fd[0],result,sizeof(result));
            // printf("%s",result);
            // affichePilote(listePilotes[i]);
            // afficheTemps(listePilotes[i]);
            // sleep(2);
        }
        // affichePilote(listePilotes[i]);
        afficheTemps(listePilotes[i]);
    }


    qsort(listePilotes, indicePilote+1, sizeof(struct Pilote), compare);
    for (int i = 0; i < indicePilote; i++)
    {
        printf("trié à l'indice : %d \n", i);
        printf("Le temps du pilote num %d est de : %d \n", listePilotes[i].num, listePilotes[i].temps);
    }
	afficherDonnees(listePilotes, 20);
    shmdt(listePilotes);
}