/*BY JOAO CORREIA*/
#ifndef LIB
#define LIB
#define Dim_cmd 65536 
#define Dim_id 4 
#define Dim_pais 31
#define Dim_cidade 51 
#define Dim_codigo 7
#define Dim_aeroportos 40
#define Dim_voos 30000
#define Dim_cmdr 65536

/*Linked List*/
typedef struct node1{
    char *codigo_reserva;
    int npassageiros;
    struct node1 *next;
} *link1;
link1 *heads;

/*Reservation for hashtable*/
typedef struct Reservas{
    char *cod;
    int index;
} *ptrreservas;

/*Hashtable*/
ptrreservas * reservashash;



struct Time
{
    int Horas;
    int Minutos;
    int Dias;
    int Meses;
    int Anos;
};

struct Aeroporto
{
    char Id[Dim_id];
    char Pais[Dim_pais];
    char Cidade[Dim_cidade];
    
}aeroportos[Dim_aeroportos];

struct Voo
{
    char Codigo[Dim_codigo];
    struct Aeroporto Partida;
    struct Aeroporto Chegada;
    struct Time PartidaT;
    struct Time ChegadaT;
    int Passageiros;
    int Vagas;
    link1 head;

}voos[Dim_voos];


/*Memory Leaking*/
void libertamemoria(int*M,int total_voos,int *N);
void mymalloc(void *ptr,int *M,int total_voos,int *N);

/*Hastable*/
void hashinit(int *M,int *N,int total_voos);
void apagahash(char cod[],int *M, int*N,int total_voos);
void expande(int*M,int*N,int total_voos);

/*Date checkers from proj1*/
int datecheckeerfuturo(struct Time data, struct Time datavoo);
int datecheckerpassado(struct Time data,struct Time datavoo);

/*New comands*/
void comandoreservas(char cmd[],int total_voos,int *M, int *N,struct Time data);
void comandoelimina(char cmd[], int *total_voos,int *M,int * N);






#endif

