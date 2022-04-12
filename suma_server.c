//Aquí se detallan las operaciones que nuestro servicio debe realizar, en este caso sumar dos números enteros

#include "suma.h" //archivo de cabecera, necesario en los 2 archivos(suma_client.c y suma_server.c)

int *
suma_1_svc(dupla_int *argp, struct svc_req *rqstp)
{
	static int  result;

	printf("El procedimiento ha sido invocado remotamente\n");
	printf("parameters: %d, %d\n", argp->a, argp->b);
	result = argp->a + argp->b;
	printf("returning: %d\n", result);

	return &result;
}
