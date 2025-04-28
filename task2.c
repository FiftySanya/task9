#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Запуск cat /etc/master.passwd через sudo.\n");
    system("sudo cat /etc/master.passwd");

    return 0;
}
