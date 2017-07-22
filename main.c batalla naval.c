#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef WIN32
	#include <windows.h>	
	#define Esperar(x) Sleep(x)
	#define Limpiar_Pantalla system("cls")
#endif 


#define AGUA '^'
#define TOCADO '*'
#define OCULTA 'O'
#define PORTAVIONES 5
#define ACORAZADO 3
#define ACORAZADO1 3
#define ACORAZADO2 3
#define SUBMARINO 4
#define SUBMARINO1 4
#define SUBMARINO2 4
#define DESTRUCTOR 2
#define DESTRUCTOR1 2

typedef struct
{
	char letra;
	int numero;
}Casilla;

char TableroJ1[10][10],TableroJ2[10][10],Aux[10][10],frase[50]="\0";
int Barcos[9]={PORTAVIONES,ACORAZADO,ACORAZADO1,ACORAZADO2,SUBMARINO,SUBMARINO1,SUBMARINO2,DESTRUCTOR,DESTRUCTOR1};
Casilla Lista[100];
int aux=0,contador=0,tocadosJ1=0,tocadosJ2=0;


void IniciarTablero(char[10][10],char);
void IniciarTableroJ2();
void DibujarTablero(char[10][10]);
void PedirCasilla(int);
int VerificarCasilla(char[10][10],Casilla,int,char);
void Almacenar(char[10][10],int,Casilla,char);
void TurnoJ1();
void TurnoJ2();
char AtacarCasilla(char[10][10],Casilla);
void GenerarLista();


int main()
{
	int res;
    system("color 70");
 
    printf("\n\n\t    ~BATALLA NAVAL~\n\n\t\t#\n\t\t#|\n\t\t#|#\n\t\t#|##\n\t\t#|###\n\t\t#|####");
    printf("\n\t\t#|#####\n\t\t#|######\n\t#########################\n\t _______________________");
    printf("\n\t  ####/)###############\n\t   ###(/##############\n\t    #################\n\t     ###############");
    printf("\n\n\n\t1- JUGAR\n\n\t2- SALIR\n\n\n\tIngresa una opcion:");
    scanf("%d", &res);
    system("cls");
       
    switch(res)
    { 
       
       case 1:
       {
    IniciarTablero(TableroJ1,AGUA); 
	DibujarTablero(TableroJ1);

    printf ("\n Turno de colocar tu  flota\n\n\n");
	strcpy(frase,"Ingrese Casillas del Portaviones (5 casillas)\n");
	printf("%s",frase);
	PedirCasilla(PORTAVIONES);
	strcpy(frase,"Ingrese Casillas del Acorazado (3 casillas)\n\0");
	printf("%s",frase);
	PedirCasilla(ACORAZADO);
	strcpy(frase,"Ingrese Casillas del 2do Acorazado (3 casillas)\n");
	printf("%s",frase);
	PedirCasilla(ACORAZADO1);
	strcpy(frase,"Ingrese  Casillas del 3er Acorazado (3 casillas)\n");
	printf("%s",frase);
	PedirCasilla(ACORAZADO2);
	strcpy(frase,"Ingrese  Casillas del Submarino (4 casillas)\n\0");
	printf("%s",frase);
	PedirCasilla(SUBMARINO);
	strcpy(frase,"Ingrese Casillas del 2do Submarino (4 casillas)\n");
	printf("%s",frase);
	PedirCasilla(SUBMARINO1);
	strcpy(frase,"Ingrese Casillas del 3er Submarino (4 casillas)\n");
	printf("%s",frase);
	PedirCasilla (SUBMARINO2);
	strcpy(frase,"Ingrese Casillas del Destructor (2 casillas)\n");
	printf("%s",frase);
	PedirCasilla(DESTRUCTOR);
	strcpy(frase,"Ingrese Casillas del 2do Destructor2 (2 casillas)]\n");
	printf("%s",frase);
	PedirCasilla(DESTRUCTOR1);
	printf("     TABLERO CREADO\n");
	Esperar(1500);

	Limpiar_Pantalla;
	printf("Generando tablero oponente...");
	IniciarTablero(Aux,OCULTA); 
	IniciarTableroJ2(); 
	GenerarLista();
	Limpiar_Pantalla;
	printf("\n\n\n\n\n\n                              EMPIEZA EL JUEGO\n");
	Esperar(2000);

	
	while (1)
	{
		TurnoJ1(); 
		if (tocadosJ1 == 17) 
		{					 
			Limpiar_Pantalla;
			printf(" GANASTE\n");
			return 0;
		}

		TurnoJ2(); 
		if (tocadosJ1 == 17) 
		{					 
			Limpiar_Pantalla;
			printf(" PERDISTE\n");
			return 0;
		}
	}}
}
}


void IniciarTablero(char Tablero[10][10],char simbolo)
{
	int i,j;

	for(i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
			Tablero[i][j]=simbolo;
	}
}


void IniciarTableroJ2()
{
	Casilla aleatoria;
	char pos,posicion[2]={'v','h'};
	int i;

	IniciarTablero(TableroJ2,AGUA); 
	srand(time(NULL));
	for (i=0;i<9;i++)
	{
		do
		{
			aleatoria.letra=(rand()%10)+65; 
			aleatoria.numero=(rand()%10)+1; 
			pos=posicion[rand()%2]; 
		}while(!VerificarCasilla(TableroJ2,aleatoria,Barcos[i],pos)); 
		Almacenar(TableroJ2,Barcos[i],aleatoria,pos); 
	}
}


void DibujarTablero(char Tablero[10][10])
{
	int i,j,letra=65;
	
	Limpiar_Pantalla;
	printf("        1 2 3 4 5 6 7 8 9 10\n\n");
	for (i=0;i<10;i++,letra++)
	{
		printf("     %c  ",letra);
		for (j=0;j<10;j++)
			printf("%c ",Tablero[i][j]);
		printf("\n\n");
	}
	printf("%s",frase);
}


void PedirCasilla(int barco)
{
	Casilla cas;
	char posicion;
	int valida;

	do {
		valida=0;
		fflush(stdin);
		printf("Letra: ");
		scanf("%c",&cas.letra);
		cas.letra=toupper(cas.letra);
		if (cas.letra < 65 || cas.letra > 74) 
			valida++;
		printf("Numero: ");
		scanf("%d",&cas.numero);
		if (cas.numero < 1 || cas.numero > 10) 
			valida++;
		printf("Vertical u horizontal (v/h): ");
		fflush(stdin);
		scanf("%c",&posicion);
		if (posicion != 'v' && posicion != 'h') 
			valida++;
		if (!VerificarCasilla(TableroJ1,cas,barco,posicion))	
			valida++;
		if (valida > 0) 
		{				
			printf("La celda señalada no existe, intente otra vez:\n");
			Esperar(1000);
		}
		DibujarTablero(TableroJ1);
	}while(valida > 0); 
	Almacenar(TableroJ1,barco,cas,posicion); 
	strcpy(frase,"\0");
	DibujarTablero(TableroJ1); 
}


int VerificarCasilla(char Tablero[10][10],Casilla cas,int barco,char posicion)
{
	int fila,columna,i,cont=0,tope;

	fila=cas.letra-65;
	columna=cas.numero-1;
	if (Tablero[fila][columna] != AGUA) 
		return 0;
	if (posicion == 'h') 
	{					 
		tope=columna+barco;
		for (i=columna;i<10 && i<tope;i++)
		{
			if (Tablero[fila][i] == AGUA) 
				cont++;					  
			else
				return 0;
		}
		if (cont < barco) 
			return 0;
		return 1;
	}
	else 
	{
		tope=fila+barco;
		for (i=fila;i<10 && i<tope;i++)
		{
			if (Tablero[i][columna] == AGUA)
				cont++;
			else
				return 0;
		}
		if (cont < barco)
			return 0;
		return 1;
	}
}

void Almacenar(char Tablero[10][10],int barco,Casilla cas,char posicion)
{
	int i,fila,columna,tope;
	char tipo;

	fila=cas.letra-65;
	columna=cas.numero-1;
	switch(barco) 
	{
		case PORTAVIONES:
			tipo='A';
			break;
		case SUBMARINO:
			if (aux == 0)
			{
				tipo='S';
				aux++;
			}
			else if(aux==1){
                 tipo='S';
                 aux++;
            }else 
                  tipo='S';
			break;
		case ACORAZADO:
			if (aux == 0)
			{
				tipo='A';
				aux++;
			}
			else if(aux==1){
                 tipo='A';
                 aux++;
            }else 
                  tipo='A';
			break;
		case DESTRUCTOR:
			if (aux == 0)
			{
				tipo='D';
				aux++;
            }else 
                tipo='D';
            break;
	}
	
	
	if (posicion == 'h')
	{
		tope=columna+barco;
		for (i=columna;i<tope;i++)
			Tablero[fila][i]=tipo;
	}
	else
	{
		tope=fila+barco;
		for (i=fila;i<tope;i++)
			Tablero[i][columna]=tipo;
	}
}


void TurnoJ1()
{
	Casilla cas;
	int valida,fila,columna;

	strcpy(frase,"Tu turno\n");
	DibujarTablero(Aux);
	do {
		valida=0;
		fflush(stdin);
		printf("Letra: ");
		scanf("%c",&cas.letra);
		cas.letra=toupper(cas.letra);
		if (cas.letra < 65 || cas.letra > 74) 
			valida++;
		printf("Numero: ");
		scanf("%d",&cas.numero);
		if (cas.numero < 1 || cas.numero > 10) 
			valida++;
		fila=cas.letra-65;
		columna=cas.numero-1;
		if (Aux[fila][columna] != OCULTA) 
			valida++;
		if (valida > 0) 
		{				
			printf("Casilla no valida\n");
			Esperar(1000);
		}
		DibujarTablero(Aux); 
	}while(valida > 0);
	Aux[fila][columna]=AtacarCasilla(TableroJ2,cas); 
	if (Aux[fila][columna] == TOCADO) 
	{
		strcpy(frase,"                 Tocado\n");
		tocadosJ1++;
	}
	else 
		strcpy(frase,"                  Agua\n");
	DibujarTablero(Aux); 
	system("pause");
}


void TurnoJ2()
{
	char letra[10]={'A','B','C','D','E','F','G','H','I','J'};
    Casilla cas;
	int fila,columna;

	strcpy(frase,"Turno de tu oponente\n");
	DibujarTablero(TableroJ1);
	cas=Lista[contador++];
	fila=letra[rand()%10];
	columna=(1+ rand()%(11-1));
	TableroJ1[fila][columna]=AtacarCasilla(TableroJ1,cas);
	if (TableroJ1[fila][columna] == TOCADO) 
	{
		strcpy(frase,"                 Tocado\n");
		tocadosJ2++;
	}
	else 
		strcpy(frase,"                  Agua\n");
	DibujarTablero(TableroJ1); 
	system("pause");
}


char AtacarCasilla(char Tablero[10][10],Casilla cas)
{
	int fila,columna;

	fila=cas.letra-65;
	columna=cas.numero-1;
	if (Tablero[fila][columna] == 'P' || Tablero[fila][columna] == 'A' || Tablero[fila][columna] == 'S' || Tablero[fila][columna] == 'C' || Tablero[fila][columna] == 'D')
		return TOCADO; 
	return AGUA;
}


void GenerarLista()
{
	int i,j,num;
	Casilla aux;

	for (i=0;i<100;i++)
	{
		for (j=1;j<11;j++)
		{
			Lista[i].letra=j+64; 
			Lista[i].numero=j;  
		}
	}
	srand(time(NULL));
	for (i=0;i<100;i++)
	{
		num=rand()%100;
		aux=Lista[i];
		Lista[i]=Lista[num];
		Lista[num]=aux;
	}
  system("PAUSE");	
  }


