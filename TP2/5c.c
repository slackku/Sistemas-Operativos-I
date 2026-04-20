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
#include <sys/times.h>
#include <time.h>

int main()
{
    sleep(4);
    // (Low Level)
    struct tms t_start, t_end;
    clock_t start_ticks, end_ticks;
    long ticks_per_sec = sysconf(_SC_CLK_TCK);
    if (ticks_per_sec <= 0)
    {
        perror("sysconf");
        return 1;
    }
    
    /* Punto de Inicio */
    printf("Contar desde el inicio {LOW LEVEL}\n");
    start_ticks = times(&t_start);
    if (start_ticks == (clock_t)-1)
    {
        perror("times start");
        return 1;
    }
    
    int buffer_size = 100;
    char *cwd = (char *)malloc(buffer_size * sizeof(char));
    sleep(4);
    
    getcwd(cwd, buffer_size);
    printf("Directorio actual: %s\n", cwd);
    
    printf("Se utiliza el comando chdir con parametro: 'carpeta'\n");
    chdir("carpeta");
    getcwd(cwd, buffer_size);
    printf("Directorio actual: %s\n", cwd);
    
    chdir("..");
    sleep(4);
    /* Punto Final */
    end_ticks = times(&t_end);
    if (end_ticks == (clock_t)-1)
    {
        perror("times end");
        return 1;
    }
    
    double real_sec = (double)(end_ticks - start_ticks) / ticks_per_sec;
    double user_sec = (double)(t_end.tms_utime - t_start.tms_utime) / ticks_per_sec;
    double sys_sec = (double)(t_end.tms_stime - t_start.tms_stime) / ticks_per_sec;
    double child_user_sec = (double)(t_end.tms_cutime - t_start.tms_cutime) / ticks_per_sec;
    double child_sys_sec = (double)(t_end.tms_cstime - t_start.tms_cstime) / ticks_per_sec;
    printf("Elapsed (real) time: %.6f s\n", real_sec);
    printf("User CPU time:       %.6f s\n", user_sec);
    printf("System CPU time:     %.6f s\n", sys_sec);
    printf("Child user CPU time: %.6f s\n", child_user_sec);
    printf("Child sys CPU time:  %.6f s\n", child_sys_sec);
    free(cwd);
    sleep(4);
    // (High Leve)
    
    /* Punto de inicio */
    printf("Contar desde el inicio {HIGH LEVEL}\n");
    
    clock_t cpu_start = clock();
    time_t real_start = time(NULL);
    
    if (cpu_start == (clock_t)-1 || real_start == (time_t)-1)
    {
        perror("Error al obtener tiempo inicial");
        return 1;
    }
    
    cwd = malloc(buffer_size);
    
    if (cwd == NULL)
    {
        perror("malloc");
        return 1;
    }
    
    if (getcwd(cwd, buffer_size) == NULL)
    {
        perror("getcwd");
        free(cwd);
        return 1;
    }
    sleep(4);
    
    printf("Directorio actual: %s\n", cwd);
    
    printf("Se utiliza el comando chdir con parametro: 'carpeta'\n");
    if (chdir("carpeta") != 0)
    {
        perror("chdir");
        free(cwd);
        return 1;
    }
    
    if (getcwd(cwd, buffer_size) == NULL)
    {
        perror("getcwd");
        free(cwd);
        return 1;
    }
    
    sleep(4);
    printf("Directorio actual: %s\n", cwd);

    /* Punto final */
    clock_t cpu_end = clock();
    time_t real_end = time(NULL);

    if (cpu_end == (clock_t)-1 || real_end == (time_t)-1)
    {
        perror("Error al obtener tiempo final");
        free(cwd);
        return 1;
    }

    double cpu_time = (double)(cpu_end - cpu_start) / CLOCKS_PER_SEC;
    double real_time = difftime(real_end, real_start);

    printf("Elapsed (real) time: %.6f s\n", real_time);
    printf("CPU time:            %.6f s\n", cpu_time);

    free(cwd);
    return 0;
}