#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h> /*siempre que use boleeanos tengo que declar esta librería*/

struct fechaNac{
int dia;
int mes;
int anio;
};

struct fechaTurnos{
int dia;
int mes;
int anio;
};

struct usuarios{
char Usuario[10];
char Contrasenia[10];
char apeNom[60];
};


struct profesionales{
char apeNom[60];
int idPro;
int dni;
char telefono[25];
bool borrado;
};

struct pacientes{
	char apeNom [60];
	char domicilio[60];
	int dniPac;
	char localidad[60];
	fechaNac Fecha;
	char telefono[25];
	float peso; /*agrego en este archivo*/
    float altura;/*agrego en este archivo*/
};

struct turnos{
	int idPro;
	fechaTurnos fecha;
	int dniPaciente;
	char detalleAtencion[380];	
};



void iniciarSesion(FILE *PUNTEROUSE ,bool &inicio);
void listado(FILE *PUNTEROTURNO,FILE *PUNTEROPAC);

main(){
	system("COLOR 0A");
	FILE *PUNTEROPRO,*PUNTEROTURNO,*PUNTERORECEP,*PUNTEROUSE,*PUNTEROPAC;
	

     bool inicio=false;
     int num;
     
     
    PUNTEROUSE = fopen("Usuarios.dat","ab"); /* clientes*/
	fclose(PUNTEROUSE);
	PUNTEROPRO = fopen("Profesionales.dat","ab");
	fclose(PUNTEROPRO);
	PUNTEROTURNO = fopen("Turnos.dat","ab");
	fclose(PUNTEROTURNO);
	PUNTEROPAC = fopen("Pacientes.dat","ab");
	fclose(PUNTEROPAC); 
     
do
	{
		system("cls");
		printf("\nModulo consultorios\n");
    	printf("================================================");
		printf("\n\nIngrese el numero de opcion\n\n");
		printf("1.- Iniciar Sesion\n");
		printf("2.- Visulizar lista de espera de turnos (Informe)\n");
		printf("3.- Cerrar la aplicacion\n");
		
		
		printf("\nOpcion a seleccionar: ");
		scanf("%d",&num);	
		
		switch(num)
		{
			case 1: 
					system("cls");
					printf("\nUsted ha elegido la opcion 'Iniciar Sesion'\n");
				    PUNTEROUSE= fopen("Usuarios.dat","rb");
					iniciarSesion(PUNTEROUSE,inicio); /*llamado a la función va sin tipo de dato para el booleano, el tipo de dato de los 
					                                   parametros solo va en prototipo y declaración de la función. */ 
					fclose(PUNTEROUSE);
					system("pause");
			        break;
			case 2:
					system("cls");
					if(inicio == true)
					{
						printf("\nUsted ha elegido la opcion 'Visulizar lista de espera de turnos (Informe)'\n");
						PUNTEROTURNO = fopen("Turnos.dat","rb");
						PUNTEROPAC = fopen("Pacientes.dat","rb");
						listado(PUNTEROTURNO,PUNTEROPAC);
						fclose(PUNTEROTURNO);
						fclose(PUNTEROPAC);
						printf("\n\n");
						system("pause");
						
					}
					else
					{
						printf("\nUsted no ha iniciado sesion.");
						printf("\n\n");
				  		system("pause");
					}
			        break;
			case 4:
					system("cls");
					printf("Fin del Programa\n");
					break;
					
					
			default:
					printf("Error eligio una opcion no existente\n");
					system("pause");			
		}
	}
	while(num!=3);
	
}


void iniciarSesion(FILE *PUNTEROUSE ,bool &inicio){
	

     struct usuarios use;

    char nombreDeUsuario[10];
	char clave[10];
	char nom[20];
	
	printf("\nNombre de usuario: ");
	_flushall();
	gets(nombreDeUsuario);
	
	printf("\nContrasenia: ");
	_flushall();
	gets(clave);
	
PUNTEROUSE = fopen("Usuarios.dat","rb"); /*rb: leer y comparar datos unicamente.*/	

 fread(&use,sizeof(usuarios),1,PUNTEROUSE); /*ME POSICIONO PARA LEER EL ARCHIVO*/
	while(!feof(PUNTEROUSE))
	{
		if(strcmp(use.Usuario,nombreDeUsuario)==0)/*==0 es true*/  /*	Compara cadenas de caracteres*/
		{
			if(strcmp(use.Contrasenia,clave) == 0)      
			{
				inicio=true;
				printf("\nSesion iniciada correctamente, ");			
				break;
			}	
		}
        fread(&use,sizeof(usuarios),1,PUNTEROUSE);
	}
	
	
    	                       
	if(inicio == false)
	{
		printf("\nNo se ha podido iniciar sesion.\n\n");
	
	}
	fclose(PUNTEROUSE);
}


void listado(FILE *PUNTEROTURNO,FILE *PUNTEROPAC)
{
    fechaTurnos buscar;
    turnos paciente; 
	pacientes registro;
	int fechaturno,c=0,i=0,aux;
	
    printf("\nIngrese la fecha: ");
    printf("\n\nDia: ");
    scanf("%d",&buscar.dia);
    printf("Mes: ");
    scanf("%d",&buscar.mes);
    printf("Año: ");
    scanf("%d",&buscar.anio);

	system("cls");
	printf("Pacientes para ser atendidos: ");
	printf("\n\n===========================================");
	
	fread(&paciente,sizeof(turnos),1,PUNTEROTURNO); /*puntero turno*/
	while(!feof(PUNTEROTURNO))
    {
    		if(buscar.dia == paciente.fecha.dia && buscar.mes == paciente.fecha.mes && buscar.anio == paciente.fecha.anio)
    		{
    			aux=paciente.dniPaciente; /*paciente es turno en mi caso*/
    			fread(&registro,sizeof(pacientes),1,PUNTEROPAC); /*puntero2 es paciente*/
    			while(!feof(PUNTEROPAC))
    			{
    				if(registro.dniPac == aux) /*registro es cliente o paciente en mi caso*/
    				{
    					printf("\nApellido y nombres: ");
    					puts(registro.apeNom);
    					printf("\nDni: %d",registro.dniPac);
    					printf("\n\nDomicilio: ");
    					puts(registro.domicilio);
    					printf("\nEdad: %d",2022-registro.Fecha.anio);
						printf("\n\nPeso: %f",registro.peso);
						printf("\n\altura: %f",registro.altura);	
						printf("\n===========================================");	
    				}
    				fread(&registro,sizeof(pacientes),1,PUNTEROPAC);		
    			} 	
    		}
    	
    	fread(&paciente,sizeof(turnos),1,PUNTEROTURNO);
    } 	
}

	
	




   