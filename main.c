#include <string.h>
#include <stdio.h>
#include "binari.h"

void uno() { printf("uno\n"); }
void dos() { printf("dos\n"); }
void tres() { printf("tres\n"); }
void cuatro() { printf("cuatro\n"); }
void cinco() { printf("cinco\n"); }
void seis() { printf("seis\n"); }
void siete() { printf("siete\n"); }
void ocho() { printf("ocho\n"); }
void nueve() { printf("nueve\n"); }
void diez() { printf("diez\n"); }

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    btnode_create("/api/port/1", uno);
    btnode_create("/api/port/2", dos);
    btnode_create("/api/port/3", tres);
    btnode_create("/api/port/4", cuatro);
    btnode_create("/api/vlan/3", seis);
    btnode_create("/api/vlan/7", NULL);

    if (argc < 2)
    {
        return 1;
    }

    BTNode *node = btnode_search(argv[1]);
    if (node != NULL)
    {
        if (node->handle != NULL)
        {
            node->handle();
        }
        else // Not implemented
        {
            printf("Error 501: Not implemented\n");
        }
    }
    else // Not found
    {
        printf("Error 404: Not found\n");
    }

    return 0;
}
