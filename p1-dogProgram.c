#include <stdio.h>
#include <stdlib.h>

struct dogType{
	int llave; //Identificador del registro
	int escrito; //Permite saber si contiene o no datos la estructura
	char nombre;
	int edad;
	char raza;
	float peso;
	char sexo;
	struct dogType *siguiente;
};

struct dogType *asignar_memoria(struct dogType *a){
	a = malloc(sizeof(struct dogType));
	return a;
};

FILE *cargar_archivo_escribir(FILE *a){
	a = fopen("dataDogs.dat","w+");
	if( a == NULL ){
		perror("Error al abrir el archivo");
		exit(-1);
	}
	return a;
};
FILE *cargar_archivo_leer(FILE *a){
	a = fopen("dataDogs.dat","r");
	if( a == NULL ){
		perror("Error al abrir el archivo");
		exit(-1);
	}
	return a;
};

void liberar_memoria(struct dogType *a){
	free(a);
};

void escribir_archivo(FILE *a, struct dogType *c){
	size_t w;
	w = fwrite(c, sizeof(*c), 1, a);
	if(w != 1){
			perror("Error al escribir el archivo");
			exit(-1);
	}
};

void leer_archivo(FILE *a, struct dogType *c){
	size_t w;
	w = fread(c, sizeof(*c), 1,a);
	if( w != 1){
		perror("Error al leer el archivo");
		exit(-1);
	}
};

void cerrar_archivo(FILE *a){
	size_t w;
	w = fclose(a);
	if(w != 0 ){
		perror("Error al cerrar el archivo");
		exit(-1);
	}
};

void ingresar_registro(){
	printf("-----------------------------------------\n");
	struct dogType *datos = asignar_memoria(datos);
	printf("Nombre del animal: ");
	scanf("%c",&datos->nombre);
	while(getchar()!='\n');
	printf("\nEdad del animal: ");
	scanf("%d",&datos->edad);
	while(getchar()!='\n');
	printf("\nRaza del animal: ");
	scanf("%c",&datos->raza);
	while(getchar()!='\n');
	printf("\nPeso del animal: ");
	scanf("%f",&datos->peso);
	while(getchar()!='\n');
	printf("\nSexo del animal: ");
	scanf("%c",&datos->sexo);
	while(getchar()!='\n');
	datos->llave = 1;
	datos->escrito = 1;
	datos->siguiente = asignar_memoria(datos->siguiente);
	datos->siguiente->llave = datos->llave + 1;
	datos->siguiente->escrito = 0;
	FILE *archivo = cargar_archivo_escribir(archivo);
	escribir_archivo(archivo,datos);
	cerrar_archivo(archivo);
	liberar_memoria(datos);
	printf("\nRegistro bien realizado\n");
	//Falta lectura de tecla
	//scanf("%d")
	//while(getchar()!='\n');
};

void lista_registro(struct dogType *a){
	printf("-----------------------------------------\n");
	printf("Lista de registros:\n");
	while(a->llave != 0 && a->escrito == 1){
		printf("Registro No. %i\n",a->llave);
		a = a->siguiente;
	}	
};

int ver_opcion(struct dogType *a){
	int n;
	printf("Digite registro a ver: ");
	scanf("%d",&n);
	while(n != a->llave && a->escrito == 1) a = a->siguiente;
	if(a->llave != 0){
		printf("Nombre del animal: %c\n",a->nombre);
		printf("Edad del animal: %i\n",a->edad);
		printf("Peso del animal: %f\n",a->peso);
		printf("Raza del animal: %c\n",a->raza);
		printf("Sexo del animal: %c\n",a->sexo);
		printf("Numero de registro: %i\n",a->llave);
		return 1;
	}else return 0;
};

void ver_registro(){
	FILE *archivo = cargar_archivo_leer(archivo);
	struct dogType *datos = asignar_memoria(datos);
	leer_archivo(archivo,datos);
	cerrar_archivo(archivo);
	lista_registro(datos);
	liberar_memoria(datos); //Metodo ineficiente :S
	datos = asignar_memoria(datos);
	leer_archivo(archivo,datos);
	if(ver_opcion(datos) == 1) printf("Registro mostrado exitosamente");
	else printf("No se pudo mostrar el registro solicitado");
	liberar_memoria(datos);
	//Falta la tecla de espera :(
};

void menu(){
	printf("-----------------------------------------\n");
	printf("Veterinaria la nacho\n\n");
	printf("Menu de opciones (Seleccione oprimiendo el numero de la opcion)\n");
	printf("1.Ingresar registro\n");
	printf("2.Ver registro\n");
	printf("3.Borrar registro\n");
	printf("4.Buscar registro\n");
	printf("5.Salir\n");
	printf("\nIntroduzca opcion: ");
};

int opciones(){
	menu();
	int op;
	scanf("%d",&op);
	while(getchar()!='\n');
	if(op == 1){
		ingresar_registro();
		opciones();
		return 0;
	}else if(op == 2){
		ver_registro();
		opciones();
		return 0;
	}
	else if(op == 3) return 3;
	else if(op == 4) return 4;
	else if(op == 5) return 5;
	else return 0;
};

int main(){
	opciones();
	return(0);
};
