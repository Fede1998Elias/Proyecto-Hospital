#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct fechaNac {
    int dia;
    int mes;
    int anio;
};

struct fechaTurnos {
    int dia;
    int mes;
    int anio;
};

struct usuarios {
    char Usuario[10];
    char Contrasenia[32];
    char apeNom[60];
};

struct profesionales {
    char apeNom[60];
    int idPro;
    int dni;
    char telefono[25];
    bool borrado;
};

struct pacientes {
    char apeNom[60];
    char domicilio[60];
    int dniPac;
    char localidad[60];
    struct fechaNac Fecha;
    char telefono[25];

};

struct turnos {
    int idPro;
    struct fechaTurnos fecha;
    int dniPaciente;
    char detalleAtencion[380];
};


struct Atenciones
{
	int idProfesional;
	int cantidad;		
};

void registrarProfesional(FILE*PUNTEROPRO);
void registrarRecepcionista();
void atenciones(FILE *PUNTEROTUR);
void ranking();
void bajaLogica();


int main() {
	system("COLOR 0A");
    int op = 0;
	FILE *PUNTEROPRO, *PUNTEROREC, *PUNTEROUSE, *PUNTEROTUR;
	PUNTEROPRO = fopen("Profesionales.dat", "ab");
	fclose(PUNTEROPRO);
	PUNTEROREC = fopen("Recepcionistas.dat", "ab");
	fclose(PUNTEROREC);
	PUNTEROUSE = fopen("Usuarios.dat","ab");
	fclose(PUNTEROUSE);
	PUNTEROTUR = fopen("Turnos.dat", "ab");
	fclose(PUNTEROTUR);
	
    do {
        printf("1--Registrar profesionales\n");
        printf("2--Registrar Usuario Recepcionista\n");
        printf("3--Atenciones por Profesional\n");
        printf("4--Ranking de Profesionales por Atenciones\n");
        printf("5--Baja Logica\n");
        printf("6--Cerrar la aplicacion\n");

        printf("Ingrese opcion a elegir: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
            	printf("Ud eligio la opcion de cargar profesionales al sistema..\n");
            	system("pause");
                system("cls");
              PUNTEROPRO = fopen("Profesionales.dat", "ab");
              registrarProfesional(PUNTEROPRO);
              fclose(PUNTEROPRO);
              system("cls");
                break;
            case 2:
            	printf("Ud eligio la opcion de cargar recepcionistas al sistema..\n");
            	system("pause");
                system("cls");
             	registrarRecepcionista();
             	system("cls");
                break;
            case 3:
                system("cls");
                 printf("Ud eligio la opción de atención por profesional. \n");
                 PUNTEROTUR= fopen("Turnos.dat","rb");
                 atenciones(PUNTEROTUR);
                 fclose(PUNTEROTUR);
                 system("pause");
                 system("cls");
                break;
            case 4:
                system("cls");
                ranking();
                system("pause");
                system("cls");
                break;
            case 5:
            	printf("Ud eligio la opcion de baja logica para profesionales del sistema..\n");
            	system("pause");
                system("cls");
              	bajaLogica();
              	system("cls");
                break;
            case 6:
                system("cls");
                	printf("Ud eligio la opcion de Ranking por profesionales del sistema..\n");
               ranking();
                break;
            default:
                printf("La opcion ingresada no es valida.\n");
                break;
        }
    } while (op!=6);


}

void registrarProfesional(FILE *PUNTEROPRO) {
    int bandera = 0;
	 profesionales pro;
     usuarios use;
	FILE*PUNTEROUSE;
    char nombreUsuario[10];
    char contrasenia[32];


    do {
        printf("NOMBRE DE USUARIO\n\n");
        printf("Condiciones para nombre de usuario\n\n");
        printf("> Cantidad minima 6 caracteres.\n");
        printf("> Cantidad maxima 10 caracteres\n");
        printf("> Podran ser letras, nmeros y/o simbolos del conjunto {+,-,/,*,?,Â¿,!,Â¡}\n");
        printf("> Ser unico para cada usuario registrado.\n");
        printf("> Comenzar con una letra minuscula.\n");
        printf("> Tener al menos 2 letras mayusculas.\n");
        printf("> Tener como maximo 3 digitos.\n\n");

        printf("Ingrese nombre de usuario: \n");
        _flushall();
        gets(nombreUsuario);
		
		PUNTEROUSE = fopen("Usuarios.dat", "rb");
		fread(&use, sizeof(usuarios), 1 ,PUNTEROUSE);
		
		bandera=0;
		while(!feof(PUNTEROUSE)){
			if(strcmp(use.Usuario,nombreUsuario) == 0){
				bandera=1;
				break;
			}
			fread(&use, sizeof(usuarios), 1 , PUNTEROUSE);
		}
		if(bandera==1){
			printf("El usuario ya existe ingrese otro.");
			system("pause");
			system("cls");
		}
		
}while(bandera==1);
		fclose(PUNTEROUSE);
		
		PUNTEROUSE = fopen("Usuarios.dat", "ab");

    printf("CONTRASENIA DE USUARIO\n\n");
    printf("Condiciones para contrasenia de usuario\n\n");
    printf("> Cantidad minima 6 caracteres. Cantidad maxima 32 caracteres.\n");
    printf("> Debe contener al menos una mayuscula, una minuscula y un numero.\n");
    printf("> No puede contener ningun caracter de puntuacion, ni acentos, ni espacios. Solo caracteres alfanumericos.\n");
    printf("> No debe tener mas de 3 caracteres numericos consecutivos\n");
    printf("> No debe tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente).\n\n");
    
    printf("Ingrese la contrasenia: ");
    _flushall();
    gets(contrasenia);
    
    strcpy(use.Usuario,nombreUsuario);
    strcpy(use.Contrasenia,contrasenia);
    fwrite(&use, sizeof(usuarios), 1, PUNTEROUSE);

		
		printf("\nIngrese el nombre del profesional: ");
		gets(pro.apeNom);
		
	 	printf("\nIngrese id del medico: ");
	    scanf("%d", &pro.idPro);
	
	    printf("\nIngrese dni del medico: ");
	    scanf("%d", &pro.dni);
	
	    printf("\nIngrese telefono del medico: ");
	    _flushall();
	    gets(pro.telefono);
	
	    pro.borrado = false;
	
	    fwrite(&pro, sizeof(struct profesionales), 1, PUNTEROPRO);
   
}


void registrarRecepcionista() {
    struct usuarios use;
	int bandera = 0;
    char nombreUsuario[11];
    char contrasenia[11]; 

    FILE *PUNTERORECEP;

    do {
        printf("NOMBRE DE USUARIO\n\n");
        printf("Condiciones para nombre de usuario\n\n");
        printf("> Cantidad minima 6 caracteres.\n");
        printf("> Cantidad maxima 10 caracteres\n");
        printf("> Podran ser letras, numeros y/o simbolos del conjunto {+,-,/,*,?,¿,!,¡}\n");
        printf("> Ser unico para cada usuario registrado.\n");
        printf("> Comenzar con una letra minuscula.\n");
        printf("> Tener al menos 2 letras mayusculas.\n");
        printf("> Tener como maximo 3 digitos.\n\n");

        printf("Ingrese nombre de usuario: ");
        fflush(stdin); 
        gets(nombreUsuario);

        PUNTERORECEP = fopen("Recepcionistas.dat", "rb");
        if (PUNTERORECEP == NULL) {
            printf("Error al abrir el archivo Recepcionistas.dat\n");
            exit(1); 
        }
        
        bandera=0;
        fread(&use, sizeof(struct usuarios), 1, PUNTERORECEP);
        while (!feof(PUNTERORECEP)) {
            if (strcmp(use.Usuario, nombreUsuario) == 0) {
                bandera = 1;
                break;
            }
            fread(&use, sizeof(struct usuarios), 1, PUNTERORECEP);
        }
        fclose(PUNTERORECEP);

        if (bandera == 1) {
            printf("Usuario ingresado ya existe.\n");
            system("pause");
            system("cls");
        }
    } while (bandera == 1);

    PUNTERORECEP = fopen("Recepcionistas.dat", "ab");
    if (PUNTERORECEP == NULL) {
        printf("Error al abrir el archivo Recepcionistas.dat\n");
        exit(1); 
    }

    printf("CONTRASEÑA DE USUARIO\n\n");
    printf("Condiciones para contraseña de usuario\n\n");
    printf("> Cantidad minima 6 caracteres. Cantidad máxima 10 caracteres.\n");
    printf("> Debe contener al menos una mayuscula, una minuscula y un numero.\n");
    printf("> No puede contener ningun caracter de puntuacion, ni acentos, ni espacios. Solo caracteres alfanumericos.\n");
    printf("> No debe tener mas de 3 caracteres numericos consecutivos.\n");

    printf("Ingrese contraseña: ");
    fflush(stdin); 
    gets(contrasenia);
    printf("\n\n");
   
    strcpy(use.Usuario, nombreUsuario);
    strcpy(use.Contrasenia, contrasenia);

    printf("Ingrese el nombre del recepcionista: ");
    gets(use.apeNom);

    fwrite(&use, sizeof(struct usuarios), 1, PUNTERORECEP);

    fclose(PUNTERORECEP);
}

void bajaLogica() {
    bool borrado = false;
    int bandera = 0;
    struct profesionales pro;
    int id;

    printf("Ingrese id del medico: ");
    scanf("%d", &id);

   FILE *PUNTEROPRO = fopen("Profesionales.dat", "r+b"); //r+b el archivo se abre en modo lectura escritura.
    fread(&pro, sizeof(struct profesionales), 1, PUNTEROPRO);
    while (!feof(PUNTEROPRO) && bandera == 0) {
        if (id == pro.idPro && pro.borrado==false) {
            pro.borrado = true;
            fwrite(&pro, sizeof(struct profesionales), 1, PUNTEROPRO);
            bandera = 1;
        }
        fread(&pro, sizeof(struct profesionales), 1, PUNTEROPRO);
    }
    
    if(bandera==1){
    printf("Registro borrado exitosamente.\n");
    system("pause");
	}else{
		printf("El registro a dar de baja no se encontro o ya fue borrado previamente...\n");
		system("pause");
	}
    fclose(PUNTEROPRO);	
}




void atenciones(FILE *PUNTEROTUR)
{
	int mes,b=0;
	turnos reg;
	
	printf("\n\nIngrese el mes para mostrar las atenciones: ");
	scanf("%d",&mes);
	
	fread(&reg,sizeof(turnos),1,PUNTEROTUR);
	while(!feof(PUNTEROTUR))
	{
		if((mes==reg.fecha.mes))
		{
			b=1;
			printf("\nId profesional: %d",reg.idPro);
			printf("\nFecha de turno");
			printf("\nDia: %d",reg.fecha.dia);
			printf("\nMes: %d",reg.fecha.mes);
			printf("\nAnio: %d",reg.fecha.anio);
			printf("\nDNI del cliente: %d",reg.dniPaciente);
			printf("\n===========================================\n");
		}
		fread(&reg,sizeof(turnos),1,PUNTEROTUR);
	}

	if(b==1)
	{
		printf("\n\n");
	}
	if(b==0)
	{
		printf("\nNo hay turnos registrados para el mes ingresado\n\n");
	}
}

void ranking()
{
    FILE *arch; /*arch PUNTEROTUR*/
    profesionales regPro[50];
    turnos regTurnos[50];
    Atenciones regAtenciones[50];   //atenciones tiene 2 campos  int idProfesional; int cantidad
    Atenciones auxiliar;
    int numPro = 0, numTurnos = 0, contador = 0;

    arch = fopen("Profesionales.dat", "rb");

    if (arch == NULL)
    {
        printf("\nEl archivo 'Profesionales.dat' no fue creado o se elimino.");
       exit(1); //salida
    }

    fread(regPro, sizeof(profesionales), 50, arch);
    numPro = ftell(arch) / sizeof(profesionales); // ftell(arch): determina la posición actual de la variable puntero despúes de haber leido todos las casillas(registros)
                                                 //numPro: define la cantidad de elementos que tiene mi vector. 
    fclose(arch);

    arch = fopen("Turnos.dat", "rb"); // arch PUNTEROTUR

    if (arch == NULL)
    {
        printf("\nEl archivo 'Turnos.dat' no fue creado o se elimino");
        exit(1);
    }

    fread(regTurnos, sizeof(turnos), 50, arch);
    numTurnos = ftell(arch) / sizeof(turnos);

    fclose(arch);

    for (int i = 0; i < numPro; i++)
    {
        contador = 0;
        for (int k = 0; k < numTurnos; k++)
        {
            if (regPro[i].idPro == regTurnos[k].idPro)
            {
                contador++;
            }
        }
        regAtenciones[i].idProfesional = regPro[i].idPro;
        regAtenciones[i].cantidad = contador;
    }

    // Ordena el ranking de mayor a menor:
    for (int i = 0; i < numPro - 1; i++)
    {
        for (int j = 0; j < numPro - i - 1; j++)
        {
            if (regAtenciones[j].cantidad< regAtenciones[j + 1].cantidad)
            {
                auxiliar = regAtenciones[j];
                regAtenciones[j] = regAtenciones[j + 1];
                regAtenciones[j + 1] = auxiliar;
            }
        }
    } 

    // Muestra el ranking
    for (int i = 0; i < numPro; i++)
    {
        printf("\nPuesto %d:", i + 1);
        printf("\nId del profesional: %d", regAtenciones[i].idProfesional); 
        printf("\nCantidad de atenciones: %d", regAtenciones[i].cantidad);
        printf("\n=============================================");
    }
}

