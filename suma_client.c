//Aquí se recibe la direccion del servidor y nuestros parametros necesarios para nuestro servicio suma
//ademas de crearse el cliente con clnt_create el cual despues de finalizar su tarea es destruido
#include "suma.h" //este es nuestro archivo de cabecera, necesario en los 2 archivos(suma_client.c y suma_server.c)
#include <stdio.h>


void
suma_prog_1(char *host,int a, int b)
{
	CLIENT *clnt;
	int  *result_1;
	dupla_int  suma_1_arg;

	suma_1_arg.a=a;
	suma_1_arg.b=b;

#ifndef	DEBUG
	clnt = clnt_create (host, SUMA_PROG, SUMA_VERS, "udp"); //creación del cliente, parametros (direccion del servidor, numero del programa, version del programa y protocolo de red)
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	} 
		
#endif	/* DEBUG */

	result_1 = suma_1(&suma_1_arg, clnt); //pasamos los dos valores de nuestra estructura y nuestro cliente creado al servicio suma
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	} else {
		printf("result= %d \n",*result_1);
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	/*Aquí en la función main se declaran las variables (que serán recibidas como argumentos) que se utilizaran para ejecutar el servicio suma*/
	char *host; /*Se declara el host de tipo char ya que es un parametro necesario de la función clnt_create */
	int a,b; /*Números enteros pasados como argumento al momento de ejecutar el cliente y lo cuales seran sumados*/

	/*En esta parte se valida el número de argumentos que son pasados al momento de ejecutar el cliente*/
	if (argc != 4) {
		printf ("usage: %s server_host,numA,numB\n", argv[0]);
		exit (1);
	}
	/*Se asigna el segundo argumento como el valor del host*/
	host = argv[1];
	/*Asignación de los argumentos pasados a las variables a y b, además se hace la conversión de los argumentos a enteros y se validan.*/
	if ((a = atoi(argv[2])) == 0 && *argv[2] != '0') {
	fprintf(stderr, "invalid value: %s\n", argv[2]);
	exit(1);
	}
	if ((b = atoi(argv[3])) == 0 && *argv[3] != '0') {
	fprintf(stderr, "invalid value: %s\n", argv[3]);
	exit(1);
	}
	/*Se manda a llamar la función en el mismo código del cliente, la cual se encargará de mandar los paramatros al servicio alojado en el servidor*/
	suma_prog_1(host, a, b);
exit (0);
}
