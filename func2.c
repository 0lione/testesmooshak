/*BY JOAO CORREIA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib2.h"

/*Compares if the 2 dates are the same */
int datacompar(int dia, int mes,int ano, struct Voo voo){
    if (ano == voo.PartidaT.Anos ){
        if (mes == voo.PartidaT.Meses){
            if (dia == voo.PartidaT.Dias){
                return 0;
            }
        }
    }
    return 1;
}

/*Deletes a node that has codigo in it */
link1 apagaelemlista(link1 head,char codigo[], int index){
    link1 temp= head, prev = NULL;
    while (temp != NULL){
        if (strcmp(temp->codigo_reserva,codigo) == 0){
            if (temp == head){
                head= temp->next;
            }
            else {
                prev->next = temp->next;
            }
            voos[index].Vagas += temp->npassageiros;
            free(temp->codigo_reserva);
            free(temp);
            break;
        }
        prev= temp;
        temp= temp->next;
    }
    return head;
}

/*Deletes every element of the list*/
void apagalista(link1 head,int *M,int*N,int total_voos){
    link1 curr = head, prox;
    while (curr != NULL){
        prox = curr->next;
        apagahash(curr->codigo_reserva,M,N,total_voos);
        free(curr->codigo_reserva);
        free(curr);
        curr = prox;
    }
    head= NULL;
}

/*Inserts at the beginning of the list*/
link1 insert(link1 head,char codigo[],int passageiros,int *M,int total_voos,int *N){
    link1 new= malloc(sizeof(struct node1));
    char *reserva = malloc(sizeof(char) * (strlen(codigo)+1));
    mymalloc(new,M,total_voos,N);
    mymalloc(reserva,M,total_voos,N);
    strcpy(reserva,codigo);
    new->codigo_reserva = reserva;
    new->npassageiros = passageiros;
    new->next= head;
    return new;
}

/*Inserts after the node which has codigo in it*/
void insertafter(link1 curr, char codigo[],int passageiros,int *M,int total_voos,int *N){
    link1 new= malloc(sizeof(struct node1));
    char *reserva = malloc(sizeof(char) * (strlen(codigo)+1));
    mymalloc(new,M,total_voos,N);
    mymalloc(reserva,M,total_voos,N);
    strcpy(reserva,codigo);
    new->codigo_reserva= reserva;
    new->npassageiros = passageiros;
    new->next = curr->next;
    curr->next = new;
}


/*Inserts in the linked list in alpha order*/
link1 insertsort(link1 head, char codigo[],int passageiros,int *M,int total_voos,int *N){
    link1 curr = head;
    if (head == NULL || strcmp(head->codigo_reserva,codigo) > 0){  /* If the list is empty or the code is before head */
        return insert(head, codigo,passageiros,M,total_voos,N);
    }
    while (curr->next != NULL){
        if (strcmp(curr->next->codigo_reserva,codigo) > 0){
            insertafter(curr,codigo,passageiros,M,total_voos,N);
            return head;
        }
        curr= curr->next;
    }
    insertafter(curr,codigo,passageiros,M,total_voos,N);
    return head;
}

/*Hash function*/
unsigned long hash_reserva(char *codigo,int *M){
    unsigned int i = 0, length = strlen(codigo);
    unsigned long hash = 0;
    while (i != length) {
        hash += codigo[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash % *M;
}

/*Inserts a Reservation in the hashtable*/
void inserehash(char cod[],int *M, int *N,int total_voos,int index){
    unsigned long i= hash_reserva(cod,M);
    while (reservashash[i] != NULL){
        i= (i+1) % *M;
    }
    reservashash[i] = malloc(sizeof(struct Reservas));
    reservashash[i]->cod = malloc(sizeof(char) * strlen(cod) +1);
    mymalloc(reservashash[i],M,total_voos,N);
    mymalloc(reservashash[i]->cod,M,total_voos,N);
    strcpy(reservashash[i]->cod,cod);
    reservashash[i]->index = index;
    if ((*N)++ > (*M)/2){
        expande(M,N,total_voos);
    }
}
/*Deletes a Reservation which has cod has its reservation code from the hashtable*/
void apagahash(char cod[],int *M, int*N,int total_voos){
    int j;
    unsigned long i=hash_reserva(cod,M);
    ptrreservas aux;
    while (reservashash[i] != NULL){
        if (!strcmp(reservashash[i]->cod,cod)) break;
        else i= (i+1) % (*M);
    }
    if (reservashash[i] == NULL) return;
    free(reservashash[i]->cod);
    free(reservashash[i]);
    reservashash[i] = NULL;
    --(*N);
    for (j = (i+1) % (*M); reservashash[j] != NULL;j= (j+1) % (*M)){
        aux = reservashash[j];
        reservashash[j] = NULL;
        inserehash(aux->cod,M,N,total_voos,aux->index);
        free(aux->cod);
        free(aux);
    }
}

/*Searches the Reservation with cod in the hashtable*/
char * procurahash(char cod[],int *M){
    unsigned long i= hash_reserva(cod,M);
    while (reservashash[i] != NULL){
        if (!strcmp(reservashash[i]->cod,cod)){
            return reservashash[i]->cod;
        }
        else {
            i = (i+1) % (*M);
        }
    }
    return NULL;
}

/*Returns the index of the flight which has a Reservation with cod as its reservation code*/
int indexreserva(char cod[],int*M){
    unsigned long i= hash_reserva(cod,M);
    while (reservashash[i] != NULL){
        if (!strcmp(reservashash[i]->cod,cod)){
            return reservashash[i]->index;
        }
        else {
            i = (i+1) % (*M);
        }
    }
    return -1;
}

/*Resizes the hashtable when is halffull*/
void expande(int*M,int*N,int total_voos){
    int i;
    ptrreservas*t= reservashash;
    *M= 2* (*M) + 1;
    hashinit(M,N,total_voos);
    for (i=0; i < (*M)/2;++i){
        if (t[i] != NULL){
            inserehash(t[i]->cod,M,N,total_voos,t[i]->index);
            free(t[i]->cod);
            free(t[i]);
        }
    }
    free(t);
}

/*Creates the hashtable*/
void hashinit(int *M,int *N,int total_voos){
    int i;
    reservashash= malloc((*M) * sizeof(ptrreservas));
    mymalloc(reservashash,M,total_voos,N);
    for (i=0;i < *M;++i){
        reservashash[i]= NULL;
    }
    *N=0;
}

/*Prints every element of the list*/
void printlista(link1 head){
    link1 curr = head;
    while (curr != NULL){
        printf("%s %d\n",curr->codigo_reserva, curr->npassageiros);
        curr = curr->next;
    }
}
/*Lists the reservations*/
void listareservas(int *index){
    printlista(voos[*index].head);
}
/*Creates a Reservation by creating a node and a element in the hashtable*/
void criareserva(int *index, char reserva[],int passageiros, int *M,int *N,int total_voos){
    inserehash(reserva,M,N,total_voos,*index);
    voos[*index].head= insertsort(voos[*index].head,reserva,passageiros,M,total_voos,N);
    voos[*index].Vagas= voos[*index].Vagas - passageiros;
}

/*Reservation code Checker*/
int verificadorcodreserva(char reserva[]){
    int i, len= strlen(reserva);
    if (len < 10){
        printf("invalid reservation code\n");
        return 1;
    }
    for (i=0;i < len;++i){
        if(reserva[i] < '0' || reserva[i] > 'Z'){
            printf("invalid reservation code\n");
            return 1;
        }
        if (reserva[i] > '9' && reserva[i] <'A'){
            printf("invalid reservation code\n");
            return 1;
        }
    }
    return 0;
}

/*Date checker*/
int verificadordata(struct Voo voo,struct Time data){
    if (datecheckeerfuturo(data,voo.PartidaT) || datecheckerpassado(data,voo.PartidaT)){
        return 1;
    }
    return 0;
}

/*Passenger Checker*/
int verificadorpassageiros(int passageiros){
    if (passageiros <= 0){
        printf("invalid passenger number\n");
        return 1;
    }
    return 0;
}

/* Creating Reservation Checkers*/
int verificadorcria(char reserva[],char cod[],int passageiros,int dia,int mes, int ano,int*M,int total_voos,int *index, struct Time data){
    int i, estado= 0;
    if (verificadorcodreserva(reserva)) return 1;
    for (i=0; i< total_voos;++i){
        if (strcmp(cod,voos[i].Codigo) == 0 && datacompar(dia,mes,ano,voos[i]) == 0){
            *index=i;
            estado= 1;
            break;
        } 
    }
    if (!estado){
        printf("%s: flight does not exist\n", cod);
        return 1;
    }
    if (procurahash(reserva,M)){
        printf("%s: flight reservation already used\n",reserva);
        return 1;
    }
    if (passageiros > voos[*index].Vagas){
        printf("too many reservations\n");
        return 1;
    }
    if (verificadordata(voos[*index],data)) return 1;
    if (verificadorpassageiros(passageiros)) return 1;
    return 0;    
}
/*Checkers for listing reservation*/
int verificadorlista(char cod[],int dia,int mes,int ano,int total_voos,int *index,struct Time data){
    int i, estado=0;
    for (i=0; i< total_voos;++i){
        if ((strcmp(cod,voos[i].Codigo)) == 0 && (datacompar(dia,mes,ano,voos[i])) == 0){
            *index=i;
            estado= 1;
            break;
        }
    }
    if (!estado){
        printf("%s: flight does not exist\n", cod);
        return 1;
    }
    if (verificadordata(voos[*index],data)) return 1; 
    return 0;         
}
/*Comand for Reservations*/
void comandoreservas(char cmd[],int total_voos,int *M, int *N,struct Time data){
    int dia, mes, ano, passageiros,index;
    char buffer[Dim_cmdr], cod[Dim_codigo],letra;
    if (sscanf(cmd,"%c %s %02d-%02d-%d %s %d",&letra,cod,&dia,&mes,&ano,buffer,&passageiros) == 7){
        if (verificadorcria(buffer,cod,passageiros,dia,mes,ano,M,total_voos,&index,data) == 1) return;
        criareserva(&index,buffer,passageiros,M,N,total_voos);
    }
    else  if (sscanf(cmd,"%c %s %02d-%02d-%d %s %d",&letra,cod,&dia,&mes,&ano,buffer,&passageiros) == 5){
        if (verificadorlista(cod,dia,mes,ano,total_voos,&index,data) == 1) return;
        listareservas(&index);
    }
}

/* Comand for deleting Reservations and flight codes*/
void comandoelimina(char cmd[], int *total_voos,int *M,int * N){
    int i, procura = 0,index; /*"procura" 0 means the search was not succsefull */
    char buffer[Dim_cmdr],letra;
    sscanf(cmd,"%c %s",&letra, buffer);
    if (procurahash(buffer,M)){ /* Its a Reservation code */
        voos[indexreserva(buffer,M)].head = apagaelemlista(voos[indexreserva(buffer,M)].head,buffer,indexreserva(buffer,M)); 
        apagahash(buffer,M,N,*total_voos);
        procura = 1 ;
    }
    else {
        for (i=0;i < *total_voos; ++i){
            if (strcmp(buffer,voos[i].Codigo) == 0){ /*Its a flight code */
                apagalista(voos[i].head,M,N,*total_voos);
                for (index= i;index < *total_voos;++index) voos[index] = voos[index+1];
                *total_voos = * total_voos -1;
                --i;                
                procura = 1;
            }
        }
    }
    if (procura == 0) printf("not found\n");
}

/*Frees all the memory*/
void libertamemoria(int *M,int total_voos,int *N){
    link1 temp;
    int i;
    for (i=0; i < total_voos;++i){
        while(voos[i].head != NULL){
            temp= voos[i].head;
                apagahash(temp->codigo_reserva,M,N,total_voos);
            
            free(temp->codigo_reserva);
            voos[i].head= voos[i].head->next;
            free(temp);
        }
    }
    free(reservashash);
}
/*Checks if the malloc was successful*/
void mymalloc(void *ptr,int *M,int total_voos,int *N){
    /*Acabar com exit(2) */
    if (!ptr){
        libertamemoria(M,total_voos,N);
        printf("No memory.\n");
        exit(2);
    }
}





