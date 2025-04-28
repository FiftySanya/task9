#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Створюємо файл від звичайного користувача
    system("echo 'Test content' > myfile.txt");

    // Копіюємо від root у домашній каталог
    system("sudo cp myfile.txt ~/root_copy.txt");

    // Спроба редагування від звичайного користувача
    printf("Спроба редагування...\n");
    system("echo 'New content' >> ~/root_copy.txt");

    // Спроба видалення від звичайного користувача
    printf("Спроба видалення...\n");
    system("rm ~/root_copy.txt");

    return 0;
}
