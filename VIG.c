
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
int count=0;
int ceva=0;
int cheie(char m,char alfabet[])
{
for(int i=0 ; i<26;i++)
{if(alfabet[i]==m) return i;
}
return -1;
}
int litera_mica(char c)
{
if( c>='a' && c<='z') return 1;
return 0;
}

int litera_mare(char c)
{
if ( c>='A' && c<='Z') return 1;
return 0;
}

void criptare_mesaj(char  mesaj[] , char alphabet[] , char cheie_cr[])
{
for(int i=0;i<count;i++)
{char p;
p=mesaj[i];
mesaj[i]=alphabet[(cheie(p,alphabet) + cheie(cheie_cr[i%ceva],alphabet))%26];}
}

double frecventa(int i, int arr[] , int lungime)
{
return (double)arr[i]/lungime;
}

double Calculeaza_Index(int count , char sir[],char alfabet[])
{
int vector_frecvente[26];
for(int i=0;i<26;i++)
{vector_frecvente[i]=0;
}
for(int i=0;i<count;i++)
{
vector_frecvente[cheie(sir[i],alfabet)]++;
}

double index=0.0;
for(int j=0;j<26;j++)
{double x=(double)(vector_frecvente[j]-1)/(count-1);
if (x<0.0){ x=0.0;}
index=index+((double)vector_frecvente[j]/count)*x;
}
return index;
}
int Validare(double x)
{
if(x<0.073 && x>0.058) return 1;
return 0;
}
double substr(int m , int lungime_sir, char sir[],char alfabet[])
{char arr[m][lungime_sir/m];
for(int i=0;i<m;i++)
for (int j=0;j<(lungime_sir/m);j++)
{
arr[i][j]=sir[i+j*m];

}
double sum=0;
for(int i=0;i<m;i++)
{//printf("%f\n",Calculeaza_Index(lungime_sir/m,arr[i],alfabet));

sum=sum+Calculeaza_Index(lungime_sir/m,arr[i],alfabet);

}

//if(Validare(Calculeaza_Index(lungime_sir/m,arr[i],alfabet))==0) return 0;
return (sum/m);

}
double Calculeaza_MIC(  int lungime_sir2 , char sir2[] , char alfabet[] )
{
double vector_frecvente1[26];
int vector_frecvente2[26];

for(int i=0;i<26;i++)
{
vector_frecvente1[i]=0.0;
vector_frecvente2[i]=0;
}
for(int i=0;i<lungime_sir2;i++)
{
vector_frecvente2[cheie(sir2[i],alfabet)]++;
}
vector_frecvente1[0]=0.08167;
vector_frecvente1[1]=0.01492;
vector_frecvente1[2]=0.02782;
vector_frecvente1[3]=0.04253;
vector_frecvente1[4]=0.12702;
vector_frecvente1[5]=0.02228;
vector_frecvente1[6]=0.02015;
vector_frecvente1[7]=0.06094;
vector_frecvente1[8]=0.06966;
vector_frecvente1[9]=0.00153;
vector_frecvente1[10]=0.00772;
vector_frecvente1[11]=0.04025;
vector_frecvente1[12]=0.02406;
vector_frecvente1[13]=0.06749;
vector_frecvente1[14]=0.07507;
vector_frecvente1[15]=0.01929;
vector_frecvente1[16]=0.00095;
vector_frecvente1[17]=0.05987;
vector_frecvente1[18]=0.06327;
vector_frecvente1[19]=0.09056;
vector_frecvente1[20]=0.02758;
vector_frecvente1[21]=0.00978;
vector_frecvente1[22]=0.02360;
vector_frecvente1[23]=0.00150;
vector_frecvente1[24]=0.01974;
vector_frecvente1[25]=0.00074;

double index=0.0;
for(int i=0;i<26;i++)
{
index=index+(vector_frecvente1[i])*((double)vector_frecvente2[i]/lungime_sir2);
}
return index;
}
char* shift(int m,char sir[],int lungime_sir,int poz,int s,char alfabet[])
{
char *word=malloc(lungime_sir/m+1);
bzero(word,lungime_sir/m);
for(int i=0;i<lungime_sir/m;i++)
{
word[i]=sir[poz+i*m];
}
for(int j=0;j<lungime_sir/m;j++)
{
if((cheie(word[j],alfabet)-s)>0)
word[j]=alfabet[(cheie(word[j],alfabet)-s)%26];
else word[j]=alfabet[(cheie(word[j],alfabet)-s+26)%26];
}
return word;
}

int main (int argc , char* argv[])
{
int input_fd;
input_fd=open("cript.txt",O_RDONLY);

if(input_fd==-1)
{
printf("Eroare la deschiderea fisierului de criptare");
return -1;
}
unsigned char input_buffer[4096];
int bytes_read;
bytes_read=read(input_fd,input_buffer,4096);
for(int i=0;i<bytes_read;i++)
{printf("%c",input_buffer[i]);}
if(close(input_fd)==-1)
{printf("Eroare la inchiderea fisierului de criptare");
return -1;}
char sir[bytes_read];
bzero(sir,bytes_read);

printf("\n");
for(int i=0;i<bytes_read;i++)
{
if(litera_mare(input_buffer[i])==1 ) {sir[count]=input_buffer[i];count++;}
if(litera_mica(input_buffer[i])==1) {sir[count]=toupper(input_buffer[i]); count++;}
}
for(int i=0;i<count;i++)
{printf("%c",sir[i]);} //sirul de criptat
printf("\n");
char copie[count];
strcpy(copie,sir);
char alfabet[26];
for(int i=0;i<26;i++)
{alfabet[i]='A'+i;
printf("%d...%c\n",i,alfabet[i]);} //alfabetul limbii engleza
//printf("\n");
//printf("%d\n",cheie('C',alfabet));
char cript_key[12];
strcpy(cript_key,"SALUTSALUTP");
ceva=strlen(cript_key);
//printf("%s",cript_key);
//printf("\n");
criptare_mesaj(sir,alfabet,cript_key);
for(int i=0;i<count;i++)
{printf("%c",sir[i]);} // sirul criptat
printf("\n");
//printf("Index shakes: %f\n",Calculeaza_Index(count,copie,alfabet) );
//printf("DACA ESTE VALID :%f\n",substr(5,count,sir,alfabet));
int LUNGIME_CHEIE=0;
do{
LUNGIME_CHEIE++;
}while(Validare(substr(LUNGIME_CHEIE,count,sir,alfabet))==0);
/*
int LUNGIME_CHEIE=0;
int contor=0;
double pr=100.0;
for(contor=1;contor<=26;contor++)
{
if(fabs(pr-0.065)>fabs(substr(contor,count,sir,alfabet)-0.065))
{pr=substr(contor,count,sir,alfabet);
//printf("%f..\n,,,,,",pr);
LUNGIME_CHEIE=contor;
//printf("%d",poz);
}
}
*/
printf("Lungimea cheii este : %d\n",LUNGIME_CHEIE);

//printf("%f\n",Calculeaza_MIC(count,copie,count,copie,alfabet));
double pr=100.0;
int poz;
int s;
printf("Cheia este : ");
for (int i=0;i<LUNGIME_CHEIE;i++)
{pr=100.0;
for(s=0;s<26;s++)
{
if(fabs(pr-0.065)>fabs(Calculeaza_MIC(count/LUNGIME_CHEIE,shift(LUNGIME_CHEIE,sir,count,i,s,alfabet),alfabet)-0.065))
{pr=Calculeaza_MIC(count/LUNGIME_CHEIE,shift(LUNGIME_CHEIE,sir,count,i,s,alfabet),alfabet);
//printf("%f..\n,,,,,",pr);
poz=s;
//printf("%d",poz);
}
}
printf("%c",alfabet[(poz)%26]);
}
printf("\n");


//for(int i=0;i<count/LUNGIME_CHEIE;i++)
//{
//printf("%c",shift(LUNGIME_CHEIE,sir,count,0,18,alfabet)[i]);
//}

return 0;
}