#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s Name PhoneNumber\n", argv[0]);
        return 1;
    }

    FILE *file = fopen("phonebook.txt", "a"); //append
    if (file == NULL) {
        printf("Error: fopen faild");
        return 1;
    }

    fprintf(file, "%s,%s\n", argv[1], argv[2]);
    fclose(file);

    return 0;
}
