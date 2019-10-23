#include "my_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*------------- AVENTURA 1--------------*/

/*---- RETO 1 ----*/

size_t my_strlen(const char *str) {
    const char *aux = str; //puntero auxiliar

    while (*aux) { //recorremos hasta encontrar \0
        aux++;
    }

    return aux - str; //la resta de las direcciones es igual a longitud del str
}

int my_strcmp(const char *str1, const char *str2) {

    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

char *my_strcpy(char *dest, const char *src) {
    char *res = dest;
    memset(dest,0,sizeof(*dest));

    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    dest = res;
    return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
    char *res = dest;
    memset(dest, 0, sizeof(*dest));

    while (n > 0 && *src) {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    //*dest = '\0';
    dest = res;
    return dest;
}

char *my_strcat(char *dest, const char *src) {
    char *res = dest;
    while (*dest) {
        dest++;
    }
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    //*dest = '\0';
    dest = res;
    return dest;
}

/* ---- RETO 2 ----*/

struct my_stack *my_stack_init(int size) {
    //reservamos el espacio para una pila
    struct my_stack *aux_stack = malloc(sizeof(struct my_stack));
    //inicializamos sus variables
    aux_stack->size = size;
    aux_stack->first = NULL;

    return aux_stack;
}

int my_stack_push(struct my_stack *stack, void *data) {
    //comprobamos que los datos pasados son correctos
    if (stack == NULL || data <= 0) return -1;

    //reservamos el espacio para el nodo
    struct my_stack_node *aux_node = malloc(sizeof(struct my_stack_node));
    //inicializamos las variables
    aux_node->data = data;
    aux_node->next = stack->first;
    stack->first = aux_node;
    return 0;
}

void *my_stack_pop(struct my_stack *stack) {
    //comprobamos que la pila no está vacía
    if (stack->first == NULL) return NULL;

    //creamos un puntero auxiliar y la variable de retorno
    struct my_stack_node *aux_node;
    void *return_data;
    //guardamos el valor de data del primer nodo
    return_data = stack->first->data;
    //liberamos el nodo
    aux_node = stack->first;
    stack->first = aux_node->next;
    free(aux_node);

    return return_data;
}
int my_stack_len(struct my_stack *stack) {
    //creamos e inicializamos un puntero auxiliar y la variable de retorno
    int len = 0;
    struct my_stack_node *aux_node;
    aux_node = stack->first;

    //recorremos la pila hasta el final
    while(aux_node != NULL) {
        aux_node = aux_node->next;
        len++;
    }

    return len;
}

struct my_stack *my_stack_read(char *filename) {
    //creamos las variables necesarias
    struct my_stack *aux_stack;
    int *data, file, size;

    //abrimos el file
    file = open(filename, O_RDONLY);

    //leemos el tamaño de los datos
    read(file, &size, sizeof(int));
    //reservamos espacio para los datos
    data = malloc(size);
    //inicializamos el stack
    aux_stack = my_stack_init(size);

    //leemos los datos y los metemos en la pila
    while(read(file, data, size) > 0) {
        my_stack_push(aux_stack, data);
        data = malloc(size);
    }

    free(data);
    close(file);

    return aux_stack;
}

int my_stack_write(struct my_stack *stack, char *filename) {
    //usaremos una pila auxiliar para volcar los datos
    struct my_stack *aux_stack;
    aux_stack = my_stack_init(stack->size);

    struct my_stack_node *aux_node; // = malloc(sizeof(struct my_stack_node));
    aux_node = stack->first;

    int file, elementos;

    //volcamos el stack en aux_stack, inviertiendo los datos
    while(aux_node != NULL) {
        my_stack_push(aux_stack, aux_node->data);
        aux_node = aux_node->next;
    }

    aux_node = aux_stack->first;

    //abrimos el file
    file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    //si ha habido error
    if (file == -1) {
        return file;
    }

    //si ha ido bien
    //escribimos el tamaño de los datos (int)
    write(file, &aux_stack->size, sizeof(int));

    //escribimos los datos
    while(aux_node != NULL) {
        write(file, aux_node->data, stack->size);
        aux_node = aux_node->next;
        elementos++;
    }

    close(file);

    return elementos;
}

int my_stack_purge(struct my_stack *stack) {
    struct my_stack_node *aux_node;
    void *data;
    int contador = 0;

    aux_node = stack->first;

    //recorremos el stack liberando los nodos y los datos
    while(aux_node != NULL) {
        data = aux_node->data;
        free(data);
        stack->first = aux_node->next;
        free(aux_node);
        aux_node = stack->first;
        contador++;
    }

    free(stack);

    return ((contador*sizeof(struct my_stack_node))+sizeof(struct my_stack));
}