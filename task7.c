#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libutil.h>

int main() {
    // Змінюємо назву процесу для приховування
    setproctitle("innocent_process");

    // Виконуємо task7.sh
    execl("/bin/sh", "sh", "-c", "source ~/task7.sh", NULL);

    perror("execl");
  
    return 1;
}

// Скомпілювати gcc -Wall -lutil task7.c -o task7
// У свій ~/.bashrc додаємо в кінець: ~/task7
// Виконуємо source ~/.bashrc
