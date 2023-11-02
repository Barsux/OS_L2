#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void printstat(int num){
    time_t ts;
    time(&ts);
    struct tm * time = localtime(&ts);
    int pid = getpid(); 
    int ppid = getppid();
    if (num == 0) printf("PID Родительского Процесса: %d, Время: %02d:%02d:%02d\n", pid, time->tm_hour, time->tm_min, time->tm_sec);
    else printf("Дочерний процесс: N%d, PID Процесса: %d, PID родителя: %d, Время: %02d:%02d:%02d\n", num, pid, ppid, time->tm_hour, time->tm_min, time->tm_sec);
}

int main() {
    pid_t child1, child2;
    child1 = fork(); // Создание первого дочернего процесса
    
    if (child1 < 0) {
        perror("Ошибка при создании первого дочернего процесса.\n");
        return 1;
    } 
    else if (child1 == 0) {
        // Код для первого дочернего процесса
        printstat(1);
    } 
    else {
        child2 = fork(); // Создание второго дочернего процесса
        
        if (child2 < 0) {
            perror("Ошибка при создании второго дочернего процесса.\n");
            return 1;
        } else if (child2 == 0) {
            printstat(2);
            // Замещаем процесс другой исполняемой программой.
            execl("threads", (char *)NULL);
        } else {
            // Код для родительского процесса
            
            int status;
            
            printstat(0);
            
            printf("Выполнение команды 'ps -x':\n");
            system("ps -x");
            printf("\nВыполнение команды 'route':\n");
            system("route");
            
            waitpid(child1, &status, 0); // Ожидание завершения первого дочернего процесса
            waitpid(child2, &status, 0); // Ожидание завершения второго дочернего процесса
        }
    }
    
    return 0;
}