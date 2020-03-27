#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *energy_file;
    char buff[255];
    char *energy = "energy";

    energy_file = fopen(energy, "r");
    if (!energy_file) {
        printf("something went wrong file doesnt exist");
        return 0;
    }

    fscanf(energy_file, "%s", buff);
    printf("1 : %s\n", buff );
    fscanf(energy_file, "%s", buff);
    printf("1 : %s\n", buff );

    fclose(energy_file);

    return 0;
}
