#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

// Вывод статистики по потокам
void pthrintstat(){
    time_t ts;
    time(&ts);
    struct tm * time = localtime(&ts);
    int pid = getpid(); 
    int ppid = getppid();
    printf("3. Дочерний процесс: N%d, PID Процесса: %d, PID родителя: %d, Время: %02d:%02d:%02d\n", pthread_self(), pid, ppid, time->tm_hour, time->tm_min, time->tm_sec);
}


int main(){
    // Создаю идентификаторы потоков
    pthread_t thread1, thread2;

    // Запускаю потоки с вызовом функции
    pthread_create(&thread1, NULL, pthrintstat, NULL);
    pthread_create(&thread2, NULL, pthrintstat, NULL);

    // Ожидание завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}