#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Запуск cat /etc/shadow через sudo.\n");
    system("sudo cat /etc/shadow");
    return 0;
}
