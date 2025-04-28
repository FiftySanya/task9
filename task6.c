#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

// Функція для виведення прав доступу у формі, схожій на ls -l
void print_permissions(mode_t mode) {
    printf("%c", (S_ISDIR(mode)) ? 'd' : '-');
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}

// Отримання імені власника
char* get_owner_name(uid_t uid) {
    struct passwd *pw = getpwuid(uid);
    return pw ? pw->pw_name : "unknown";
}

// Отримання назви групи
char* get_group_name(gid_t gid) {
    struct group *gr = getgrgid(gid);
    return gr ? gr->gr_name : "unknown";
}

// Функція для тестування доступу до файлу (читання, запис, виконання)
void test_file_access(const char *path) {
    struct stat st;
    
    if (stat(path, &st) == -1) {
        printf("Помилка доступу до %s: %s\n", path, strerror(errno));
        return;
    }
    
    printf("\n=== Тест доступу до файлу: %s ===\n", path);
    
    printf("Права: ");
    print_permissions(st.st_mode);
    printf("\nВласник: %s\nГрупа: %s\n", get_owner_name(st.st_uid), get_group_name(st.st_gid));
    
    // Спроба читання
    printf("\nСпроба читання: ");
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ПОМИЛКА: %s\n", strerror(errno));
    } 
    else {
        printf("УСПІХ\n");
        char buffer[10];
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            printf("  Початок файлу: %s\n", buffer);
        }
        close(fd);
    }
    
    // Спроба запису
    printf("\nСпроба запису: ");
    fd = open(path, O_WRONLY | O_APPEND);
    if (fd == -1) {
        printf("ПОМИЛКА: %s\n", strerror(errno));
    } 
    else {
        const char test_data[] = "test";
        if (write(fd, test_data, sizeof(test_data) - 1) == -1) {
            printf("ПОМИЛКА при записі: %s\n", strerror(errno));
        } else {
            printf("УСПІХ\n");
        }
        close(fd);
    }
    
    // Спроба виконання
    printf("\nСпроба виконання: ");
    if (access(path, X_OK) == 0) {
        printf("УСПІХ\n");
    } 
    else {
        printf("ПОМИЛКА: %s\n", strerror(errno));
    }
}

int main() {
    uid_t uid = getuid();
    gid_t gid = getgid();
    
    printf("Поточний користувач: %s (UID=%d, GID=%d)\n", get_owner_name(uid), uid, gid);
    
    char home_path[512];
    snprintf(home_path, sizeof(home_path), "%s/.profile", getenv("HOME") ? getenv("HOME") : "/tmp");
    
    test_file_access(home_path); // Файл у домашньому каталозі
    test_file_access("/bin/ls"); // Шлях до команди ls у FreeBSD
    test_file_access("/etc/master.passwd"); // Системний конфігураційний файл
    
    return 0;
}
