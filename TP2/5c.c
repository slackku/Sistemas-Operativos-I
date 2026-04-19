/* c.
    Escriba, compile y ejecute un programa en C que invoque estas llamadas al sistema,
    combinando si es posible, las dos maneras de invocar. Incluya en el código sendas presentaciones
    por pantallas de los resultados obtenidos.

    Consideraciones:
    Estamos dentro de la carpeta TP2
    Con el siguiente arbol de directorios:
    TP2
    ├── carpeta
    │   └── file.txt
    ├── 5c.c <- Archivo que compilamos
    └── final.exe <- Ejecutable generado de 5c.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main()
{
    // (Low Level)
    struct tms t;
    clock_t start = times(&t);
    printf("Contar desde el inicio");
    

    int buffer_size = 100;
    char *cwd = (char *)malloc(buffer_size * sizeof(char));

    printf("Directorio actual: %s\n", cwd);

    getcwd(cwd, buffer_size);

    printf("Se utiliza el comando chdir con parametro: 'carpeta' ", cwd);

    chdir("carpeta");
    printf("Directorio actual: %s\n", cwd);

    // (High Leve)
    system("echo 'Hola Mundo'");
    return 0;
}