#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared global variable to store account balance
int balance = 5000;            

// Mutex lock to protect the shared balance variable
pthread_mutex_t lock;          

// Thread 1: Deposits 1000 (repeats 5 times)
void* deposit1(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);  // Lock before modifying balance
        balance += 1000;
        printf("Thread 1: Deposit 1000 | New Balance: %d\n", balance);
        pthread_mutex_unlock(&lock); // Unlock after modification
        sleep(1);
        
        // Sleep for 1 second to simulate processing time
    }
    return NULL;
}

// Thread 2: Withdraws 500 (repeats 5 times)
void* withdraw1(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);  // Lock before accessing balance
        if (balance >= 500) {       // Check if enough balance is available
            balance -= 500;

            printf("Thread 2: Withdraw 500 | New Balance: %d\n", balance);
        } else {
            printf("Thread 2: Withdraw 500 | Insufficient Balance\n");
        }
        pthread_mutex_unlock(&lock); // Unlock after operation
        sleep(1);
    }
    return NULL;
}

// Thread 3: Deposits 800 (repeats 5 times)
void* deposit2(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);
        balance += 800;

        printf("Thread 3: Deposit 800 | New Balance: %d\n", balance);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

// Thread 4: Withdraws 300 (repeats 5 times)
void* withdraw2(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);


        if (balance >= 300) {// Ensure enough balance
            balance -= 300;
            printf("Thread 4: Withdraw 300 | New Balance: %d\n", balance);
        } else {
            printf("Thread 4: Withdraw 300 | Insufficient Balance\n");
      
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    // Declare 4 thread variables
    pthread_t t1, t2, t3, t4;




    // Initialize mutex
    pthread_mutex_init(&lock, NULL);

    printf("Initial Balance: %d\n", balance);

    // Create 4 threads for deposit and withdraw operations
    pthread_create(&t1, NULL, deposit1, NULL);
    pthread_create(&t2, NULL, withdraw1, NULL);
    pthread_create(&t3, NULL, deposit2, NULL);
    pthread_create(&t4, NULL, withdraw2, NULL);

    // Wait for all threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
`
    // Display final balance after all transactions
    printf("Final Balance: %d\n", balance);

    // Destroy the mutex to release resources
    pthread_mutex_destroy(&lock);

    return 0;
}
