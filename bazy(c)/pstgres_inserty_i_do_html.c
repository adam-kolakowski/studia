#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>

char host[20]="127.0.0.1";
char port[7]="5432";//      <port i host zmienić
char dbname[30]="postgres";
char password[30]="postgres";
char user[20]="postgres";


void doSQL(PGconn *conn, char *command)
{
  PGresult *result;

  printf("\n%s\n", command);

  result = PQexec(conn, command);
  printf("status is     : %s\n", PQresStatus(PQresultStatus(result)));
  printf("#rows affected: %s\n", PQcmdTuples(result));
  printf("result message: %s\n", PQresultErrorMessage(result));

  switch(PQresultStatus(result)) {
  case PGRES_TUPLES_OK:
    {
      int n = 0, r = 0;
      int nrows   = PQntuples(result);
      int nfields = PQnfields(result);
      printf("number of rows returned   = %d\n", nrows);
      printf("number of fields returned = %d\n", nfields);
      for(r = 0; r < nrows; r++) {
	for(n = 0; n < nfields; n++)
	  printf(" %s = %s", PQfname(result, n),PQgetvalue(result,r,n));
	printf("\n");
      }
    }
  }
  PQclear(result);
}



int polacz(char *polecenie)
{
PGresult *result;
PGconn   *conn;
char znaki[200]="";
	

	
	strcat(znaki, " dbname=");
	strcat(znaki, dbname);
	strcat(znaki, " user=");
	strcat(znaki, user);
	strcat(znaki, " password=");
	strcat(znaki, password);
  	conn = PQconnectdb(znaki);
  					  

  	if(PQstatus(conn) == CONNECTION_OK) {
  		doSQL(conn, polecenie);
  		PQfinish(conn);
		return 1;
	}	
	
	PQfinish(conn);
	return 0;
}


int count_lines(char *file)
{
int lines=0;
char ch;
FILE *plik;
plik=fopen(file, "r");
	
while ((ch=fgetc(plik)) != EOF){
	if (ch == '\n'){
		lines++;
	}
}

fclose(plik);
return lines;
}

int count_separators(char *file)
{
FILE *plik;
plik=fopen(file,"r");
int separators=0;
char ch;
	
while ((ch=fgetc(plik)) != '\n'){
	if (ch == ';'){
		separators++;
	}
}

fclose(plik);
return separators+1;
}

void load_strings(char *file, int sep, int lin, char *lines, size_t X, size_t Y, size_t Z)
{
size_t linia, separator, k;
FILE *plik;
plik=fopen(file, "r");
	
linia=0;
separator=0;
k=0;
lines[linia*Y*Z+separator*Z+k]='s';
char ch;

while ((ch=fgetc(plik))!=EOF){
	if (ch=='\n'){ linia++; separator=0;k=0; }
	else if (ch==';'){separator++;k=0;}
	else{
		lines[linia*Y*Z+separator*Z+k]=ch;
		k++;
	}
}

fclose(plik);
}


int stworztabele(char *name, size_t N, size_t M,char (*tablica)[N][M])
{
char *komenda=calloc(50000, sizeof(char));

for (int i=0; i<N; i++){
	if (i==0){
		strcat(komenda, "CREATE TABLE ");
		strcat(komenda, name);
		strcat(komenda, "(");
		strcat(komenda, tablica[0][i]);
		strcat(komenda, " VARCHAR(20) UNIQUE, ");
	}
	else if (i==(N-1)){
		strcat(komenda, tablica[0][i]);
		strcat(komenda, " VARCHAR(20))");
	}
	else
	{
		strcat(komenda, tablica[0][i]);
		strcat(komenda, " VARCHAR(20),");
	}

	
}

polacz(komenda);
free(komenda);
return 0;
}


int dodaj_do_tabeli(char *name, int ile_lini, size_t N, size_t M,char (*tablica)[N][M])
{

for (int j=1; j<ile_lini; j++)
{
	char *komenda=calloc(50000, sizeof(char));
	char *komenda2=calloc(2000, sizeof(char));
	char tym[2];

	strcat(komenda, "INSERT INTO ");
	strcat(komenda, name);
	strcat(komenda, " VALUES (");


	for (int i=0; i<N; i++){
		if (i==(N-1)){
			if (strlen(tablica[j][i])>20){
				strcat(komenda2, "ALTER TABLE ");
				strcat(komenda2, name);
				strcat(komenda2, " ALTER COLUMN ");
				strcat(komenda2, tablica[0][i]);
				strcat(komenda2, " TYPE varchar(");
				sprintf(tym, "%d", (int)strlen(tablica[j][i]));
				strcat(komenda2, tym);
				strcat(komenda2, ")");
				polacz(komenda2);
			}
		strcat(komenda, "'");
			if (strcmp(tablica[j][i],"")==0) strcat(komenda, "NULL");
			else strcat(komenda, tablica[j][i]);
		strcat(komenda, "')");
		}
		else{
			if (strlen(tablica[j][i])>20){
				strcat(komenda2, "ALTER TABLE ");
				strcat(komenda2, name);
				strcat(komenda2, " ALTER COLUMN ");
				strcat(komenda2, tablica[0][i]);
				strcat(komenda2, " TYPE varchar(");
				sprintf(tym, "%d", (int)strlen(tablica[j][i]));
				strcat(komenda2, tym);
				strcat(komenda2, ")");
				polacz(komenda2);
			}
			strcat(komenda, "'");
				if (strcmp(tablica[j][i],"")==0) strcat(komenda, "NULL");
				else strcat(komenda, tablica[j][i]);
			strcat(komenda, "', ");
		}
		
	}

polacz(komenda);
free(komenda);
free(komenda2);
}
return 0;
}

int usun(char *nazwa)
{
char komenda[200];

	for (int i=0; i<200; i++) komenda[i]=0;
	strcat(komenda, "DROP TABLE ");
	strcat(komenda, nazwa);
	polacz(komenda);  //protip: przy nazwie funkcji "connect" funkcja PQconnectdb się zapętla. Nie polecam takich błędów :(

}



void czy_dodawac(char *name, int ile_lini, size_t N, size_t M,char (*tablica)[N][M])
{

	char *komenda2=calloc(50000, sizeof(char));
	char tym[200];
	
	strcat(komenda2, "INSERT INTO ");
    printf("%c",komenda2[1]);
	strcat(komenda2, name);
	strcat(komenda2, " VALUES (");

    for (int i=0; i<N; i++){
    		
    	printf("%s:",tablica[0][i]);
    	scanf("%s",&tym);
    	if (i==(N-1)){
    	strcat(komenda2, "'");
			if (strcmp(tym,"")==0) strcat(komenda2, "NULL");
			else strcat(komenda2, tym);
		strcat(komenda2, "')");
		}
		else{
	    	strcat(komenda2, "'");
				if (strcmp(tym,"")==0) strcat(komenda2, "NULL");
				else strcat(komenda2, tym);
			strcat(komenda2, "', ");
		}
	memset(tym,0,strlen(tym));
    }

polacz(komenda2);
free(komenda2);
    
}


void HTMLprint(int ile, char *argv[])
{
  PGconn   *conn;
	char znaki[200]="";
	
	strcat(znaki, " dbname=");
	strcat(znaki, dbname);
	strcat(znaki, " user=");
	strcat(znaki, user);
	strcat(znaki, " password=");
	strcat(znaki, password);

  conn = PQconnectdb(znaki);
	char *nazwa;
	char nazwa2[20];
	PGresult *result;
	char polec[150];
	int i;
	int n;
    int m;
	FILE * druk = fopen(argv[ile-1], "w+");
	fprintf(druk,"<!DOCTYPE html> \n <html lang=\"pl\"> \n <head> \n <meta charset=\"utf-8\"> \n <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> \n <title>Dane z tabel</title> \n <style> \n"); 
	
	fprintf(druk,"table,td,th%c border: 1px solid black%c \n table %cborder-collapse: collapse%c width: 100%c margin: 0 auto%c \n th%c text-align: center%c padding: 5px%c h1%c color:#333%c text-align: center %c\n body%c background-color: aliceblue%c -webkit-font-smoothing: antialiased%c font-smoothing: antialiased %c \n</style></head>\n",123,125,123,59,59,125,123,59,125,123,59,125,123,59,59,125); //znaki specjalne c w ascii
	fprintf(druk,"<body>\n");
	for(i=2;i<ile-1;i++)
	{
		nazwa=argv[i];
		sscanf(nazwa,"%[^.]",nazwa2);
		sprintf(polec,"SELECT * FROM %s",nazwa2);
  		result = PQexec(conn, polec);
  		printf("result message: %s\n", PQresultErrorMessage(result));
  		switch(PQresultStatus(result)) 
		{
  			case PGRES_TUPLES_OK:
   			{
   				fprintf(druk,"<h1>Tabela %s</h1>\n<br>\n",argv[i]);
      			n=0;
      			m=0;
     			int nrows   = PQntuples(result);
     			int nfields = PQnfields(result);
				fprintf(druk,"<table>\n<tr>\n");
				for(n=0;n<nfields;n++)
					fprintf(druk,"<th>%s</th>\n",PQfname(result, n));
				fprintf(druk,"</tr>\n");
      			for(m = 0; m < nrows; m++)
				{
					fprintf(druk,"<tr>\n");
					for(n = 0; n < nfields; n++)
	  					fprintf(druk,"<th>%s</th>\n",PQgetvalue(result,m,n));
					fprintf(druk,"</tr>\n");
      			}
      			fprintf(druk,"</table> <br><br>\n ");
      			printf("Wydrukowano tabele %s do %s\n",argv[i],argv[ile-1]);
    		}
  		}
  		PQclear(result);
  	}
  	fprintf(druk,"</body> \n </html>");
  	fclose(druk);
  	PQfinish(conn);
}



int main(int argc, char **argv)
{
char     odp;
char *dbnametym=argv[1];
char *nazwa=argv[2];
char nazwa2[20];


sscanf(dbnametym,"%[^;]",dbname);
printf("Baza o nazwie: %s\n", dbname);
sscanf(nazwa,"%[^.]",nazwa2);

printf("podaj nazwe uzytkownika:");
scanf("%s",user);
printf("podaj haslo:");
scanf("%s",password);

for (int d=2; d<argc-1; d++){
	nazwa=argv[d];
	sscanf(nazwa,"%[^.]",nazwa2);
	int c_lines=count_lines(nazwa);
	int c_separators=count_separators(nazwa);
	char linie[c_lines][c_separators][512];
	for (int i=0;i<c_lines;i++)
		for (int k=0;k<c_separators;k++)
			for (int j=0;j<512;j++)
				linie[i][k][j]=NULL;
	load_strings(nazwa,2,3,&linie[0][0][0], c_lines, c_separators, 512);
	usun(nazwa2);
	stworztabele(nazwa2, c_separators, 512, linie);
	dodaj_do_tabeli(nazwa2, c_lines, c_separators,512, linie);
	printf("\n\nCzy dodac cos do tabeli %s? (t/n) ", nazwa2);
    while( (scanf(" %c", &odp)) && ((odp == 'T') || (odp == 't')) ) {
		czy_dodawac(nazwa2, c_lines, c_separators,512, linie);
		printf("\n\nCzy dodac cos do tabei %s? (t/n) ", nazwa2);
    }
}
HTMLprint(argc, argv);
return 0;
}