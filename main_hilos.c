

#include <stdio.h>
#include <pthread.h>

static int c = 10;
static pthread_mutex_t miMutex;

void *suma(void *arg) 
{
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&miMutex);
        c++;
        pthread_mutex_unlock(&miMutex);
    }
    return NULL;
}

void *resta(void *arg)
{
    for (int i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&miMutex);
        c--;
        pthread_mutex_unlock(&miMutex);
    }
    return NULL;
}

int main() 
{
    pthread_t miHilo1, miHilo2;
    
    //Inicializa mutex con gestion de error
    if (pthread_mutex_init(&miMutex, NULL) != 0)
        return(1);
    


    // Crear un nuevo hilo
    if (pthread_create(&miHilo1, NULL, suma, NULL) != 0)
    {
        fprintf(stderr, "Error al crear el hilo.\n");
        return 1;
    }

    if (pthread_create(&miHilo2, NULL, resta, NULL) != 0)
    {
        fprintf(stderr, "Error al crear el hilo.\n");
        return 1;
    }
        // Esperar a que el hilo termine 
    pthread_join(miHilo1, NULL);
    pthread_join(miHilo2, NULL);
    printf("%d\n", c);
    return(0);
}
