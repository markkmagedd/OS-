#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h> 

void *bunnyId(void *arg) {
    pthread_t id = *(pthread_t *)arg;
    printf("     /\\_/\\ \n");
    printf("    ( o.o ) \n");
    printf("    (  \"  ) \n");
    printf(" (id :%ld) \n" , id);
    printf("  /         \\ \n");
    printf(" / /       \\ \\ \n");
    printf("(_)         (_) \n");
    return NULL;
}


void *print_chars() {
    char ch1;
    char ch2;
    printf("Enter The First Character: ");
    scanf(" %c", &ch1); 
    printf("Enter The Second Character: ");
    scanf(" %c", &ch2); 

    while (ch1 <= ch2) {
        printf("%c\n", ch1);
        ch1++;
    }
    return NULL;
}

void *printInt() {
    int x;
    int y;
    int sum = 0;
    int product = 1;
    float avg;
    int c = 0;
    printf("Enter The First Integer: ");
    scanf(" %d", &x); 
    printf("Enter The Second Integer: ");
    scanf(" %d", &y); 

    while (x <= y) {
        sum += x;
        product = product * x;
        c++;
        x++;
    }
    avg = sum / c;
    printf("Sum = %d \n", sum);
    printf("Product = %d \n", product);
    printf("Average = %f \n", avg);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    char ch1, ch2;
    // Define CPU affinity set
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) != 0) {
        perror("sched_setaffinity failed");
        exit(1);
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr); // Initialize thread attributes
    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
    
    pthread_create(&t1, &attr, print_chars, NULL);
    pthread_create(&t2, &attr, bunnyId, (void*)&t2);
    pthread_create(&t3, &attr, printInt, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}