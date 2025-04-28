#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    char line[256];
    uid_t my_uid = getuid(); // UID поточного користувача

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *username = strtok(line, ":");
        strtok(NULL, ":"); // Пропускаємо пароль
        char *uid_str = strtok(NULL, ":");
        int uid = atoi(uid_str);

        if (uid >= 1000 && uid != my_uid) {
            printf("Звичайний користувач: %s (UID: %d)\n", username, uid);
        }
    }

    pclose(fp);
    return 0;
}
