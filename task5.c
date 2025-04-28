#include <stdio.h>
#include <stdlib.h>

int main() {
    system("echo 'Temp file' > temp.txt");

    // Зміна власника і прав від root
    system("sudo chown root temp.txt");
    system("sudo chmod 600 temp.txt");

    // Перевірка доступу
    system("cat temp.txt > /dev/null 2>&1 && echo 'Читання можливе' || echo 'Читання неможливе'");
    system("echo 'Test' >> temp.txt 2>&1 && echo 'Запис можливий' || echo 'Запис неможливий'");

    return 0;
}
