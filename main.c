#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct jucator
{ int **info;
  int scor;
  int lung;
  int pers;
};

struct jeton
{
    int val;
    char litera;
};
struct patrat
{
    int cuv,lit,nr;
    struct jeton jet;
    int juc;
};

int comp(const void *a, const void *b)
{
    struct jeton *x=(struct jeton*)a;
    struct jeton *y=(struct jeton*)b;
    if(x->litera>y->litera)
        return 1;
    return -1;
}

void citire(struct jeton **jetoane, char nume[])
{
    FILE *f;
    int i;
    f=fopen(nume,"r");
    struct jeton *aux;
    aux=(struct jeton*)malloc(27*sizeof(struct jeton));
    for(i=0; i<26; i++)
        fscanf(f,"%c %d\n",&aux[i].litera,&aux[i].val);
    qsort(aux,26,sizeof(struct jeton),comp);
    *jetoane=aux;
    fclose(f);
}

void citire_tabla (struct patrat ***tabla, char fisier[])
{
    FILE *f;
    f=fopen(fisier,"r");
    struct patrat **tab;
    int n;
    fscanf(f,"%d",&n);
    int i, j;
    tab=(struct patrat**)malloc(n*sizeof(struct patrat*));
    for(i=0; i<n; i++)
    {
        tab[i]=(struct patrat*)malloc(n*sizeof(struct patrat));
        for(j=0; j<n; j++)
        {
            tab[i][j].cuv=1;
            tab[i][j].lit=1;
            tab[i][j].nr=n;
            tab[i][j].juc=0;
        }
    }
    char s[20],d;
    int c;

    while(!feof(f))
    {
        fscanf(f,"%s %c%d\n",&s,&d,&c);
        int l=d;
        if(strcmp(s,"roz")==0)
            tab[l-97][c-1].cuv=2;
        if(strcmp(s,"rosu")==0)
            tab[l-97][c-1].cuv=3;
        if(strcmp(s,"bleu")==0)
            tab[l-97][c-1].lit=2;
        if(strcmp(s,"albastru")==0)
            tab[l-97][c-1].lit=3;
    }
    *tabla=tab;
    fclose(f);
}

int val_jet(struct jeton *jetoane,char c)
{
    int i,ok=-1;
    for(i=0; i<26; i++)
        if(jetoane[i].litera==c)
            ok=jetoane[i].val;

    return ok;
}

void citire_cuv(struct patrat***tab, char fisier[], struct jeton *jetoane,struct jucator*unu,struct jucator*doi)
{
    FILE *f;
    int j,i;
    struct patrat **tabla;
    struct jucator juc1;
    struct jucator juc2;
    tabla=*tab;
    f=fopen(fisier,"r");
    char d[4],e[20];
    int c,coloana,linie;
    juc1.lung=1;
    juc1.pers=1;
    juc2.lung=1;
    juc2.pers=1;
    juc1.info=(int**)malloc(juc1.lung*sizeof(int*));
    juc2.info=(int**)malloc(juc2.lung*sizeof(int*));
    while(!feof(f))
    {
        fscanf(f,"%d %s %s\n",&c,&d,&e);
        int ok=0;
        if(d[0]>='a' && d[0]<='z' && ok==0)
            if(strlen(d)==3)
            {
                linie=d[0];
                linie=linie-97;
                strcpy(d,d+1);
                coloana=atoi(d)-1;
                ok=1;
            }
            else
            {
                linie=d[0];
                linie=linie-97;
                strcpy(d,d+1);
                coloana=d[0]-'0'-1;
                ok=1;
            }
        if(d[0]>='1' && d[0]<='9' &&ok==0)
            if(strlen(d)==3)
            {
                linie=d[2];
                linie=linie-97;
                strcpy(d+2,d+3);
                coloana=atoi(d)-1;
                ok=2;
            }
            else
            {
                linie=d[1];
                linie=linie-97;
                ok=2;
                strcpy(d+1,d+2);
                coloana=d[0]-'0'-1;
            }
        if(ok==1)
        {
            int k=0;
            for(j=coloana; j<coloana+strlen(e); j++)
            {   if(tabla[linie][j].juc==0)
                tabla[linie][j].juc=c;
                tabla[linie][j].jet.litera=e[k];
                if(e[k]>='a'&&e[k]<='z')
                    tabla[linie][j].jet.val=0;
                else
                    tabla[linie][j].jet.val=val_jet(jetoane,e[k]);
                k=k+1;
            }
        }
        else if(ok==2)
        {
            int k=0;
            for(j=linie; j<linie+strlen(e); j++)
            {   if(tabla[j][coloana].juc==0)
                  tabla[j][coloana].juc=c;
                tabla[j][coloana].jet.litera=e[k];
                if(e[k]>='a'&&e[k]<='z')
                    tabla[j][coloana].jet.val=0;
                else
                    tabla[j][coloana].jet.val=val_jet(jetoane,e[k]);

                k=k+1;
            }

        }
         if (c==1)
        if(juc1.lung==1)
        {juc1.info[juc1.lung-1]=(int*)malloc(4*sizeof(int));
         juc1.info[juc1.lung-1][0]=coloana;
         juc1.info[juc1.lung-1][1]=linie;
         juc1.info[juc1.lung-1][2]=ok;
         juc1.info[juc1.lung-1][3]=strlen(e);
         juc1.lung=juc1.lung+1;
        }
        else
        {juc1.info=realloc(juc1.info,juc1.lung*sizeof(int*));
         juc1.info[juc1.lung-1]=(int*)malloc(4*sizeof(int));
         juc1.info[juc1.lung-1][0]=coloana;
         juc1.info[juc1.lung-1][1]=linie;
         juc1.info[juc1.lung-1][2]=ok;
         juc1.info[juc1.lung-1][3]=strlen(e);
         juc1.lung=juc1.lung+1;
        }
         if (c==2)
        if(juc2.lung==1)
        {juc2.info[juc2.lung-1]=(int*)malloc(4*sizeof(int));
         juc2.info[juc2.lung-1][0]=coloana;
         juc2.info[juc2.lung-1][1]=linie;
         juc2.info[juc2.lung-1][2]=ok;
         juc2.info[juc2.lung-1][3]=strlen(e);
         juc2.lung=juc2.lung+1;
        }
        else
        {juc2.info=realloc(juc2.info,juc2.lung*sizeof(int*));
         juc2.info[juc2.lung-1]=(int*)malloc(4*sizeof(int));
         juc2.info[juc2.lung-1][0]=coloana;
         juc2.info[juc2.lung-1][1]=linie;
         juc2.info[juc2.lung-1][2]=ok;
         juc2.info[juc2.lung-1][3]=strlen(e);
         juc2.lung=juc2.lung+1;
        }


    }
    int t;
    juc1.lung--;
    juc2.lung--;
    *tab=tabla;
    *unu=juc1;
    *doi=juc2;
    fclose(f);
}
int calc_scor(struct jucator unu,struct patrat**tabla)
{  int i,j;
   int scorf=0;
   int mult=1;
   int rep=0;
   for(i=0;i<unu.lung;i++)
   { int scor=0;
       if(unu.info[i][2]==1)
   { int k=unu.info[i][0];
     int l=unu.info[i][1];
     int h=unu.info[i][3];
     mult=1;
     rep=0;
     for(j=k;j<k+h;j++)
     {
         if(tabla[l][j].juc==unu.pers)
          {
              scor=scor+tabla[l][j].jet.val*tabla[l][j].lit;
              mult=mult*tabla[l][j].cuv;
              rep=rep+1;
          }
          else
        scor=scor+tabla[l][j].jet.val;
     }
    scor=scor*mult;
    if(rep==7)
        scor=scor+50;
   }
   if(unu.info[i][2]==2)
   { int k=unu.info[i][0];
     int l=unu.info[i][1];
     int h=unu.info[i][3];
     rep=0;
     mult=1;
     for(j=l;j<l+h;j++)
     {
         if(tabla[j][k].juc==unu.pers)
          {
              scor=scor+tabla[j][k].jet.val*tabla[j][k].lit;
              mult=mult*tabla[j][k].cuv;
              rep++;
          }
        else
        scor=scor+tabla[j][k].jet.val;

     }
    scor=scor*mult;
    if(rep==7)
        scor=scor+50;
   }
scorf=scorf+scor;
   }
  return scorf;
}
void castigator(struct jucator unu,struct jucator doi,struct patrat**tabla, int*pers,int*scor)
{
        int cast=calc_scor(unu,tabla);
    int cast1=calc_scor(doi,tabla);
    if(cast>cast1)
    {*pers=1;
     *scor=cast;
    }
    else
        {*pers=2;
     *scor=cast1;
    }

}
int main()
{
    char fisier[]="jetoane.txt",fisier2[]="tabla.txt",fisier3[]="joc.txt";
    struct jeton *jetoane;
    int t, j;
    struct patrat **tabla;
    citire(&jetoane,fisier);
    citire_tabla(&tabla,fisier2);
    int i,n;
    struct jucator unu;
    struct jucator doi;
    citire_cuv(&tabla,fisier3,jetoane,&unu,&doi);
int    pers=0;
   int scor=0;

        for(t=3;t<tabla[0][0].nr;t++)
    {for(j=3;j<tabla[0][0].nr;j++)
    printf("%c  ",tabla[t][j].jet.litera);
    printf("\n");
    }
    castigator(unu,doi,tabla,&pers,&scor);
    printf("Jucatorul %d a castigat cu %d puncte",pers,scor);
    printf("\n");



    return 0;
}
