/*BY JOAO CORREIA*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib2.h"
int meses[]={31,28,31,30,31,30,31,31,30,31,30,31};



/*Checks if the first date of arrival given is before the second, if it is returns 1 else returns 0*/
int datamenorchegada(struct Voo data1, struct Voo data2){
    if (data1.ChegadaT.Anos < data2.ChegadaT.Anos)
        return 1;
    else if (data1.ChegadaT.Anos == data2.ChegadaT.Anos){
        if (data1.ChegadaT.Meses < data2.ChegadaT.Meses)
            return 1;
        else if (data1.ChegadaT.Meses == data2.ChegadaT.Meses ){
            if (data1.ChegadaT.Dias < data2.ChegadaT.Dias)
                return 1;
            else if (data1.ChegadaT.Dias == data2.ChegadaT.Dias){
                if (data1.ChegadaT.Horas < data2.ChegadaT.Horas)
                    return 1;
                else if (data1.ChegadaT.Horas == data2.ChegadaT.Horas)
                    if (data1.ChegadaT.Minutos < data2.ChegadaT.Minutos)
                        return 1;
            }
        }
    }
    return 0;
}

/*Checks if the first date of departure given is before the second, if it is returns 1 else returns 0*/
int datamenorpartida(struct Voo data1, struct Voo data2){
    if (data1.PartidaT.Anos < data2.PartidaT.Anos)
        return 1;
    else if (data1.PartidaT.Anos == data2.PartidaT.Anos){
        if (data1.PartidaT.Meses < data2.PartidaT.Meses)
            return 1;
        else if (data1.PartidaT.Meses == data2.PartidaT.Meses ){
            if (data1.PartidaT.Dias < data2.PartidaT.Dias)
                return 1;
            else if (data1.PartidaT.Dias == data2.PartidaT.Dias){
                if (data1.PartidaT.Horas < data2.PartidaT.Horas)
                    return 1;
                else if (data1.PartidaT.Horas == data2.PartidaT.Horas)
                    if (data1.PartidaT.Minutos < data2.PartidaT.Minutos)
                        return 1;
            }
        }
    }
    return 0;
}
/* Insertion sort sorts flights by dates of departure */
void datasortp(struct Voo list[Dim_voos],int total_voos)
{
    int i,j;
    struct Voo temp;
    for (i=1; i <= total_voos-1; ++i){
        temp= list[i];
        j = i -1;
        while ( j >= 0 && datamenorpartida(temp,list[j]) == 1){
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = temp;
    }
}
/* Insertion sort sorts flights by dates of arrival */
void datasortche(struct Voo list[Dim_voos],int total_voos)
{
    int i,j;
    struct Voo temp;
    for (i=1; i <= total_voos -1 ; ++i){
        temp= list[i];
        j = i -1;
        while ( j >= 0 && datamenorchegada(temp,list[j]) == 1){
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = temp;
    }
}
/* Bubble sort sorts airports by ID (alpha) */
void bubble(struct Aeroporto list[Dim_aeroportos],int total_aero)
{
    int i,j,done;
    struct Aeroporto temp;
    for(i= 0;i < total_aero - 1;++i ){
        done=1;
        for (j=0; j < (total_aero -1 - i); ++j){
            if (strcmp(list[j].Id,list[j+1].Id)>0){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
                done=0;
            }
        }
        if (done) break;
        
    }
}
/*Checks flightcode*/
int codecgecker(char cod[Dim_codigo])
{
    char alfa[3], nums[5];
    sscanf(cod,"%[a-zA-z]%s",alfa,nums);
    if (strlen(alfa) != 2){
        printf("invalid flight code\n");
        return 1;
    }
    if (alfa[0]< 'A' || alfa[1] < 'A' || alfa[0] > 'Z' || alfa[1] > 'Z'){
        printf("invalid flight code\n");
        return 1;
    }
    if(atoi(nums) < 1 || atoi(nums) > 9999 || nums[0] == '0') {
        printf("invalid flight code\n");
        return 1;
    }
    return 0;
}
/*Checks if the there is another flight in the same day which has the same flightcode */
int flightchecker(char cod[Dim_codigo], struct Time datavoo,int total_voos)
{
    int counter;
    for (counter=0; counter < total_voos;++counter){
        if (strcmp(voos[counter].Codigo,cod) == 0){
            if(voos[counter].PartidaT.Dias == datavoo.Dias){
                if (voos[counter].PartidaT.Meses == datavoo.Meses){
                    if (voos[counter].PartidaT.Anos == datavoo.Anos){
                        printf("flight already exists\n");
                        return 1;
                    }
                }
                
            }
        }
    }
    return 0;
}
/*Checks if there is space to a new flight LIM= 30k */
int dimflightchecker(int total_voos)
{
    if (total_voos == Dim_voos){
        printf("too many flights\n");
        return 1;
    }
    return 0;
}
/*Checks if the flight date(datavoo) is one year or more into the future (compared with the current date(data)) --> TRUE=1 V FALSE= 0 */
int datecheckeerfuturo(struct Time data, struct Time datavoo){
    if (datavoo.Anos - data.Anos == 1){
        if (datavoo.Meses > data.Meses){
            printf("invalid date\n");
            return 1;
        }
        else if (datavoo.Meses == data.Meses)
            if (datavoo.Dias > data.Dias){
                printf("invalid date\n");
                return 1;
            }
    }
    else if (datavoo.Anos > data.Anos){
        printf("invalid date\n");
        return 1;
    }
    return 0;
}
/*Checks if the flight date(datavoo) is in the past (compared with the current date(data)) --> TRUE=1 V FALSE= 0*/
int datecheckerpassado(struct Time data,struct Time datavoo){
    if (datavoo.Anos == data.Anos){
        if (datavoo.Meses < data.Meses){
            printf("invalid date\n");
            return 1;
        }
        else if (datavoo.Meses == data.Meses)
            if (datavoo.Dias < data.Dias){
                printf("invalid date\n");
                return 1;
            }
    }
    else if (datavoo.Anos < data.Anos){
        printf("invalid date\n");
        return 1;
    }
    return 0;
}
/*Checks if the date is valid --> TRUE= 0 V False = 1 */
int datechecker(struct Time data,struct Time datavoo){
    if (datecheckeerfuturo(data,datavoo) == 1){
        return 1;
    }
    if (datecheckerpassado(data,datavoo) == 1){
        return 1;
    }
    return 0;
}

/*Same datechecker but receives pointer */
int datechecker1futuro(struct Time *data,struct Time datavoo){
    if (datavoo.Anos - data->Anos == 1){
    if (datavoo.Meses > data->Meses){
        printf("invalid date\n");
        return 1;
    }
    else if (datavoo.Meses == data->Meses){
        if (datavoo.Dias > data->Dias){
            printf("invalid date\n");
            return 1;
        }
    }
    }
    else if (datavoo.Anos > data->Anos){
        printf("invalid date\n");
        return 1;
    }
    return 0;
}
/*Same datechecker but receives pointer */
int datechecker1passado(struct Time *data,struct Time datavoo){
    if (datavoo.Anos == data->Anos){
    if (datavoo.Meses < data->Meses){
        printf("invalid date\n");
        return 1;
    }
    else if (datavoo.Meses == data->Meses){
        if (datavoo.Dias < data->Dias){
            printf("invalid date\n");
            return 1;
        }
    }
    }
    else if (datavoo.Anos < data->Anos){
        printf("invalid date\n");
        return 1;
    }
    return 0;
}
/*Same datechecker but receives pointer */
int datechecker1(struct Time *data,struct Time datavoo){
    if (datechecker1futuro(data,datavoo) == 1){
        return 1;
    }
    if (datechecker1passado(data,datavoo) == 1){
        return 1;
    }
    return 0;
}
/*Checks if it is a valid airport id --> TRUE=0 V FALSE=1*/
int idchecker(char id[Dim_id], int total_aero)
{
    int counter,statepar=1;
    for (counter=0; counter < total_aero;++counter){
        if (strcmp(id,aeroportos[counter].Id) == 0){
            statepar= 0;
        }
    }
    if (statepar == 1){
        printf("%s: no such airport ID\n",id);
        return 1;
    }
    return 0;

}
/*Checks if it is a valid duration --> TRUE=0 V FALSE=1 */
int durationchecker(struct Time dur)
{
    if (dur.Horas > 12){
        printf("invalid duration\n");
        return 1;
    }
    else if (dur.Horas == 12){
        if (dur.Minutos > 0){
            printf("invalid duration\n");
            return 1;
        }
    }
    return 0;
}
/*Checks if it is a valid capacity --> TRUE=0 V FALSE=1*/
int capacitychecker(int capc)
{
    if (capc < 10 ){
        printf("invalid capacity\n");
        return 1;
    }
    return 0;
}
/*Calculates the arrival date by adding the duration to the departure date*/
void datachegadacalc(struct Time *data, struct Time dur){
    if (data->Minutos + dur.Minutos >= 60){
        data->Minutos= data->Minutos + dur.Minutos - 60;
        ++data->Horas;
    }
    else {
        data->Minutos+= dur.Minutos;
    }
    if (data->Horas+ dur.Horas >= 24){
        data->Horas= data->Horas + dur.Horas - 24;
        ++data->Dias;
    }
    else {
        data->Horas+= dur.Horas;
    }
    if (data->Dias > meses[data->Meses - 1]){
        data->Dias= data->Dias - meses[data->Meses -1];
        ++data->Meses;
    }
    if (data->Meses > 12){
        data->Meses= 1;
        ++data->Anos;
    }
}
/*Checks the airport ID/If there is space to a new airport LIM= 40/If already exists the same airport ID --> TRUE = 0 V FALSE= 1*/
int cmdacheckers(char id[], int total_aero){
    int counter=0;
    for (counter=0; counter < Dim_id-1;++counter){
        if (id[counter] <'A' || id[counter] > 'Z'){
            printf("invalid airport ID\n");
            return 1;
        }
    }
    if (total_aero == Dim_aeroportos){
        printf("too many airports\n");
        return 1;
    }
    else{
        for (counter=0; counter < total_aero; ++counter){    
            if (strcmp(id,aeroportos[counter].Id) == 0){
                printf("duplicate airport\n");
                return 1;
            }
        }   
        }
    return 0;
}
/*Command-a INPUT:ID PAIS CIDADE OUTPUT: ID airport*/
int cmda(char cmd[Dim_cmd], int total_aero){   
    char id[Dim_id], pais[Dim_pais], cidade[Dim_cidade], space[2];
    sscanf(cmd, "%s %s %s %[^\n]", space, id, pais, cidade);
    if (cmdacheckers(id,total_aero) == 1){
        return 1;
    }
    printf("airport %s\n", id);
    strcpy(aeroportos[total_aero].Id, id);
    strcpy(aeroportos[total_aero].Pais, pais);
    strcpy(aeroportos[total_aero].Cidade,cidade); 
    return 0;
}
/*Command-l alpha sort INPUT: OUTPUT:(alpha sorted airports)*/
void cmdlsort(int total_aero, int total_voos){
    int counter,i,nvoos;
    bubble(aeroportos,total_aero);
        for(counter=0;counter < total_aero; ++counter){
            nvoos=0;
            for (i=0; i < total_voos;++i){
                if (strcmp(aeroportos[counter].Id,voos[i].Partida.Id) == 0){
                    ++nvoos;
                }
                }
            printf("%s %s %s %d\n",aeroportos[counter].Id, 
            aeroportos[counter].Cidade, aeroportos[counter].Pais,nvoos);    
        }   
}
/*Command-l non alpha sort INPUT:[ID] OUTPUT:ID PAIS CIDADE #VOOS*/
void cmdlnonsort(char cmd[],int total_aero, int total_voos){
    int counter,i,nvoos;
    char *partion;
    partion= strtok(cmd," ");
    partion= strtok(NULL, " ");
    while (partion != NULL){
        if (idchecker(partion,total_aero) == 0){
            for(counter=0;counter < total_aero; ++counter){
                if (strcmp(aeroportos[counter].Id, partion) == 0){
                    nvoos=0;
                    for (i=0; i < total_voos;++i){
                        if (strcmp(aeroportos[counter].Id,
                                voos[i].Partida.Id)== 0){
                            ++nvoos;
                        }
                    }
                    printf("%s %s %s %d\n",aeroportos[counter].Id, 
                    aeroportos[counter].Cidade, 
                    aeroportos[counter].Pais,nvoos);
                }
            }
        }
        partion= strtok(NULL," ");
    }
}
/*Command-l depends on input Command-l sort V Command-l non sort*/
void cmdl(char cmd[Dim_cmd], int total_aero, int total_voos){
    if(cmd[1] == '\0'){
        cmdlsort(total_aero,total_voos);
    }
    else{
        cmdlnonsort(cmd,total_aero,total_voos);
    }
}
/*OUTPUT:FlightCode ID1 ID2 DATE TIME*/
void cmdvlist(int total_voos){
    int counter;
    for (counter=0; counter < total_voos;++counter){
        printf("%s %s %s %02d-%02d-%d %02d:%02d\n",voos[counter].Codigo,
        voos[counter].Partida.Id,voos[counter].Chegada.Id,
        voos[counter].PartidaT.Dias,voos[counter].PartidaT.Meses,
        voos[counter].PartidaT.Anos,voos[counter].PartidaT.Horas,
        voos[counter].PartidaT.Minutos);
    }
}
/*Checks Flightcode/If there is space to a new flight/Both IDS/If there is a duplicated flight/Duration/Date/Capacity --> TRUE= 0 V FALSE= 1*/
int cmdvcheckers(char cod[],char idpar[],char idche[],struct Time datavoo,
struct Time dur,struct Time data, int total_voos,int total_aero ,int capc){
    int checker , checker1;
    if(codecgecker(cod) == 1 || flightchecker(cod,datavoo,total_voos) == 1){
        return 1;
    }
    checker= idchecker(idpar, total_aero);
    checker1 = idchecker(idche,total_aero);
    if (checker == 1 || checker1 == 1){
        return 1;
    }
    if (dimflightchecker(total_voos) == 1 || datechecker(data, datavoo) == 1){
        return 1;
    }
    if (durationchecker(dur) == 1 || capacitychecker(capc) == 1 ){
        return 1;
    }
    return 0;
}
/*Creats a new flight*/
void criastructv(int total_voos,char cod[],char idpar[],char idche[],
struct Time datavoo,struct Time dur,int capc){
    strcpy(voos[total_voos].Codigo,cod);
    strcpy(voos[total_voos].Partida.Id,idpar);
    strcpy(voos[total_voos].Chegada.Id,idche);
    voos[total_voos].PartidaT.Dias = datavoo.Dias;
    voos[total_voos].PartidaT.Meses = datavoo.Meses;
    voos[total_voos].PartidaT.Anos = datavoo.Anos;
    voos[total_voos].PartidaT.Horas = datavoo.Horas;
    voos[total_voos].PartidaT.Minutos = datavoo.Minutos;
    datachegadacalc(&datavoo, dur);
    voos[total_voos].ChegadaT.Dias = datavoo.Dias;
    voos[total_voos].ChegadaT.Meses = datavoo.Meses;
    voos[total_voos].ChegadaT.Anos = datavoo.Anos;
    voos[total_voos].ChegadaT.Horas = datavoo.Horas;
    voos[total_voos].ChegadaT.Minutos = datavoo.Minutos;
    voos[total_voos].Passageiros = capc;
    voos[total_voos].Vagas = capc;
    voos[total_voos].head = NULL;
    
}
/*Command-v INPUT:FlightCode ID1 ID2 DATE TIME CAPACITY OUTPUT:*/
int cmdvcria(char cmd[Dim_cmd],int total_voos,int total_aero,struct Time data){
    int capc;
    char cod[Dim_codigo], idpar[Dim_id],space[2],idche[Dim_id];
    struct Time datavoo, dur;         
    sscanf(cmd,"%s %s %s %s %d-%d-%d %d:%d %d:%d %d",space,cod,idpar,
    idche,&datavoo.Dias,&datavoo.Meses,&datavoo.Anos,&datavoo.Horas,
    &datavoo.Minutos,&dur.Horas,&dur.Minutos,&capc);
    if(cmdvcheckers(cod,idpar,idche,datavoo,dur,
    data,total_voos,total_aero,capc)==1){
        return 1;
    }
    criastructv(total_voos,cod,idpar,idche,datavoo,dur,capc);
    return 0;
}
/*Command-v depends on input Command-v Lists V Command-v Creates */
int cmdv(char cmd[Dim_cmd], int total_voos,int total_aero,struct Time data){
    if(cmd[1] == '\0'){
        cmdvlist(total_voos);
        return 1;
    }
    else{   
        if(cmdvcria(cmd,total_voos,total_aero,data) == 1){
            return 1;
        }
    }
    return 0;
}
/*Command-p INPUT: ID(DEPARTURE) OUTPUT:FlightCode ID(ARRIVAL) DATE TIME*/
void cmdp(char cmd[Dim_cmd],int total_voos,int total_aero){
    char space[2], id[Dim_id];
    int i,counter=0;
    struct Voo copy[Dim_voos];
    sscanf(cmd,"%s %s",space, id);
    idchecker(id,total_aero);
    for (i=0;i< total_voos;++i){
        if (strcmp(voos[i].Partida.Id,id) == 0){
            copy[counter] = voos[i];
            ++counter;
        }
    }
    datasortp(copy,counter);
    for (i=0; i < counter;++i){
            printf("%s %s %02d-%02d-%d %02d:%02d\n",copy[i].Codigo,
            copy[i].Chegada.Id,copy[i].PartidaT.Dias, 
            copy[i].PartidaT.Meses, copy[i].PartidaT.Anos,
            copy[i].PartidaT.Horas,copy[i].PartidaT.Minutos);
        }
}
/*Command-c INPUT: ID(ARRIVAL) OUTPUT:FlightCode ID(DEPARTURE) DATE TIME*/
void cmdc(char cmd[Dim_cmd], int total_voos,int total_aero){
    char space[2], id[Dim_id];
    int i,counter=0;
    struct Voo copy[Dim_voos];
    sscanf(cmd,"%s %s",space, id);
    idchecker(id,total_aero);
    for (i=0;i < total_voos;++i){
        if(strcmp(voos[i].Chegada.Id,id) == 0){
            copy[counter]=voos[i];
            ++counter;
        }
    }
    datasortche(copy,counter);
    for (i=0; i < counter;++i){
            printf("%s %s %02d-%02d-%d %02d:%02d\n",
            copy[i].Codigo,copy[i].Partida.Id,copy[i].ChegadaT.Dias,
            copy[i].ChegadaT.Meses, copy[i].ChegadaT.Anos,
            copy[i].ChegadaT.Horas,copy[i].ChegadaT.Minutos);
    }
}


/*Command-t INPUT:DATE OUTPUT:DATE*/
void cmdt(char cmd[Dim_cmd],struct Time *data){
    struct Time newdate;
    char space[2];
    sscanf(cmd,"%s %d-%d-%d",space,&newdate.Dias,&newdate.Meses,&newdate.Anos);
    if (datechecker1(data,newdate) == 0){
        data->Dias = newdate.Dias;
        data->Meses = newdate.Meses;
        data->Anos = newdate.Anos;
        printf("%02d-%02d-%d\n",data->Dias , data->Meses,data->Anos);
    }
}

int main(){
    int  total_aero=0,total_voos=0,c,i=0,M=199,N=0;
    char cmd[Dim_cmd];
    struct Time data = {0,0,1,1,2022};
    hashinit(&M,&N,total_voos);
    c = getchar();
    for (i=0; (i < (Dim_cmd-1) && c!= EOF && c != '\n'); i++){
        cmd[i]= c;
        c= getchar();
    }
    cmd[i] = '\0';
    while (cmd[0] != 'q'){
        switch (cmd[0]){
            case 'a':
                if(cmda(cmd, total_aero) == 0)
                    ++total_aero;
                break;
            case 'l': cmdl(cmd, total_aero,total_voos); break;
            case 'v':
                if(cmdv(cmd,total_voos,total_aero,data) == 0)
                    ++total_voos;
                break;
            case 'p':cmdp(cmd,total_voos,total_aero); break;
            case 'c' :cmdc(cmd,total_voos,total_aero); break;
            case 'r': comandoreservas(cmd,total_voos,&M,&N,data); break;
            case 'e' : comandoelimina(cmd,&total_voos,&M,&N); break;
            case 't' :cmdt(cmd,&data); break;
    }
        c = getchar();
        for (i=0; (i < (Dim_cmd-1) && c!= EOF && c != '\n'); i++){
            cmd[i]= c;
            c= getchar();   
        }
        cmd[i] = '\0';
    }
    libertamemoria(&M,total_voos,&N);
    return 0;
}

