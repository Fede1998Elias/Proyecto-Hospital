#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include <stdbool.h> /*Incluimos la librería para los bool*/

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

void iniciarSesion(FILE *PUNTERORECEP, bool &inicio); 
void registrarPaciente(	FILE *PUNTEROPAC);
void registrarTurno(FILE *PUNTEROTURNO);
void listar(FILE *PUNTEROPRO,FILE *PUNTEROTURNO);
main()
{
	system("COLOR 0A");

	
     bool inicio=false;
     int num;
     
	FILE *PUNTEROPRO,*PUNTEROTURNO,*PUNTERORECEP,*PUNTEROUSE,*PUNTEROPAC;
	
    PUNTEROTURNO = fopen("Turnos.dat","ab"); 
	fclose(PUNTEROTURNO);
    PUNTEROPAC=fopen("Pacientes.dat","ab");
	fclose(PUNTEROPAC);
	
	do
	{
		system("cls");
		printf("\nModulo Recepcion\n");
    	printf("================================================");
		printf("\n\nIngrese el numero de opcion\n\n");
		printf("1.- Iniciar Sesion\n");
		printf("2.- Registrar Paciente\n");
		printf("3.- Registrar Turno\n");
		printf("4.- Listar de Atenciones por Profesional y Fecha\n\n");
		printf("5.- Cerrar la aplicacion");
		
		printf("\n\nOpcion a seleccionar: ");
		scanf("%d",&num);	
		
		switch(num)
		{
			case 1: 
					system("cls");
					printf("\nUsted ha elegido la opcion 'Iniciar Sesion'\n");
				    PUNTERORECEP = fopen("Recepcionistas.dat","rb"); /*rb: leer y comparar datos unicamente.*/	
					iniciarSesion(PUNTERORECEP,inicio);
					fclose(PUNTERORECEP);
					system("pause");
			        break;
			case 2:
					system("cls");
					if(inicio == true)
					{
						printf("\nUsted ha elegido la opcion 'Registrar Paciente'\n");
				    PUNTEROPAC =fopen("Pacientes.dat","ab"); 
				    registrarPaciente(PUNTEROPAC);
				    fclose(	PUNTEROPAC);
				    system("pause");
				   
					}
					else
					{
						printf("\nUsted no ha iniciado sesion.");
						printf("\n\n");
				  		system("pause");
					}
			        break;
			case 3:
					system("cls");
					if(inicio == true)
					{
						printf("\nUsted ha elegido la opcion 'Registrar Turno'\n");
						PUNTEROTURNO=fopen("Turnos.dat","ab"); 
						registrarTurno(PUNTEROTURNO);
						fclose(PUNTEROTURNO);
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
					if(inicio == true)
					{
						printf("\nUsted ha elegido la opcion 'Listar de Atenciones por Profesional y Fecha'\n");
						PUNTEROTURNO = fopen("Turnos.dat","rb");
				  		PUNTEROPRO = fopen("Profesionales.dat","rb");
						listar(PUNTEROTURNO,PUNTEROPRO);
						fclose(PUNTEROTURNO);
						fclose(PUNTEROPRO);
						system("pause");
						printf("\n\n");
					}
				    else
				    {
				    	printf("\nUsted no ha iniciado sesion.");
				    	printf("\n\n");
				  		system("pause");
				    }
					break;	
			
			case 5:
					system("cls");
					printf("Fin del Programa\n");
				     break;
					
			default:
					printf("Error eligio una opcion no existente\n");
					system("pause");	
					break;		
		}
	}
	while(num!=5);
}


void iniciarSesion(FILE *PUNTERORECEP, bool &inicio){ 
  struct usuarios use;

  char nombreDeUsuario[12];
  char clave[12];
  

printf("\nNombre de usuario: ");
_flushall();
gets(nombreDeUsuario); 

printf("Contraseña: \n");
_flushall();
gets(clave);

 /*rb: leer y comparar datos unicamente.*/	

PUNTERORECEP = fopen("Recepcionistas.dat","rb");  
fread(&use,sizeof(usuarios),1,PUNTERORECEP);
    inicio=false;
	while(!feof(PUNTERORECEP)){ 
		
		if(strcmp(use.Usuario,nombreDeUsuario)==0){ 
		    if(strcmp(use.Contrasenia,clave) == 0)      
			{
				inicio=true;
				printf("\nSesion iniciada correctamente, ");	
			
				break;
			}	
		}
		fread(&use,sizeof(usuarios),1,PUNTERORECEP);
	}
	if(inicio==false){
		printf("\nNo se ha podido iniciar sesion.\n\n");
	}

	fclose(PUNTERORECEP);
}

void registrarPaciente(	FILE *PUNTEROPAC){  
   	char salida='s';
	    struct pacientes pac; 
	while(salida=='s'){

	printf("\nREGISTRO DE PACIENTES");
	
	printf("\n\nIngrese el Apellido y Nombre: ");
	_flushall();
    gets(pac.apeNom);
	printf("\nIngrese el Domicilio: ");
	_flushall();
	gets(pac.domicilio);
	printf("\nIngrese el DNI: ");
	_flushall();
	scanf("%d",&pac.dniPac); 
	printf("\nIngrese la localidad: ");
	_flushall();
	gets(pac.localidad);
	printf("\nIngrese la fecha de nacimiento\n");
	printf("\nIngrese el dia: ");
	_flushall();
    scanf("%d",&pac.Fecha.dia);
	printf("Ingrese el mes: ");
	_flushall();
     scanf("%d",&pac.Fecha.mes);
	printf("Ingrese el anio: ");
	_flushall();
     scanf("%d",&pac.Fecha.anio);
    _flushall();
	printf("\nIngrese el peso en KG: ");
	_flushall();
    scanf("%f",&pac.peso);
	printf("\nIngrese el numero de telefono: ");
	_flushall();
	gets(pac.telefono);
   	printf("\nIngrese la altura del paciente en metros: ");
	scanf("%f",&pac.altura);
	_flushall();  
			
	fwrite(&pac,sizeof(pacientes),1,PUNTEROPAC); 
	
	printf("\nPACIENTE REGISTRADO CORRECTAMENTE!\n\n");
	system("cls");
	printf("\n¿Desea seguir ingresando pacientes? s/n: ");
     scanf("%c",&salida);
     _flushall();
     }
     
}


void registrarTurno(FILE *PUNTEROTURNO)
{

	int bandera=0;
	int buscar,buscarDni;
	profesionales pro;
	turnos turno;
	pacientes pac;
	
	FILE *PUNTEROPRO;
	
	PUNTEROPRO=fopen("Profesionales.dat","rb"); 
	
	printf("\nIngrese id del especialista: ");
	scanf("%d",&buscar);
	
	fread(&pro,sizeof(profesionales),1,PUNTEROPRO);
	while(!feof(PUNTEROPRO))
	{
		if(buscar==pro.idPro)
		{
			bandera=1;	
				
			break;
		}
		fread(&pro,sizeof(profesionales),1,PUNTEROPRO);
	}

	if(bandera==0)
	{
		printf("\nEl id del especialista no ha sido encontrado.");
	}
	else
	{	
		FILE *PUNTEROPAC;
		int bandera1=0;
		PUNTEROPAC = fopen("Pacientes.dat","rb"); 
		
		while(bandera1==0)
		{
			printf("\nIngrese el Dni del paciente: ");
			scanf("%d",&buscarDni);
		
			fread(&pac,sizeof(pacientes),1,PUNTEROPAC);
			while(!feof(PUNTEROPAC))
			{
				if(buscarDni==pac.dniPac)
				{
					bandera1=1;		
					break;
				}
			fread(&pac,sizeof(pacientes),1,PUNTEROPAC);
			}
			fclose(PUNTEROPAC);
		}
		
		if(bandera1==1)
		{
			turno.idPro=buscar; 
			turno.dniPaciente=buscarDni; 
			printf("\nIngrese la fecha del turno\n");
			printf("Ingrese el dia: ");
			scanf("%d",&turno.fecha.dia);
			printf("Ingrese el mes: ");
			scanf("%d",&turno.fecha.mes);
			printf("Ingrese el anio: ");
			scanf("%d",&turno.fecha.anio);
			strcpy(turno.detalleAtencion,"Vacio");  
			fwrite(&turno,sizeof(turnos),1,PUNTEROTURNO);  
			printf("\nEl turno ha sido registrado exitosamente!\n\n");
		}
	}	
	
}


void listar(FILE *PUNTEROPRO,FILE *PUNTEROTURNO)
{
	turnos tur;
    profesionales pro;
	int id;	
	fechaTurnos aux;	
		
	printf("\nListado de atenciones\n");
	printf("\nEspecialista");
	printf("\t\tFecha del turno");
	printf("\n===========================================");
		
		
	fread(&tur,sizeof(turnos),1,PUNTEROTURNO);
	while(!feof(PUNTEROTURNO))
    {
    	if(tur.fecha.dia >= 1 && tur.fecha.mes >= 1 && tur.fecha.anio >= 1900)
    	{
    		id=tur.idPro;
    		aux.dia=tur.fecha.dia;
    		aux.mes=tur.fecha.mes;
    		aux.anio=tur.fecha.anio;
    		
    		fread(&pro,sizeof(profesionales),1,PUNTEROPRO);
    		while(!feof(PUNTEROPRO))
			{
				
				printf("\n");
				if(id==pro.idPro)
				{
					printf("%s",pro.apeNom);
					printf("\t\t%d/%d/%d",aux.dia,aux.mes,aux.anio);
						
				}
			  fread(&pro,sizeof(profesionales),1,PUNTEROPRO);	
			}
    	}
    	fread(&tur,sizeof(turnos),1,PUNTEROTURNO);
    } 		
}

