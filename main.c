//Written by Yağmur Doğan 10963330588 '21

//!---Comment for the project is in the end of the code---!//
//!---The output of my code is also in the .zip file as "Output.Jpeg"---!//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int array[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
pthread_mutex_t mutex_array[20];

int gBoard();
void *cell();

void visionOfCells() {

    printf("Cell  Value\n------------\n");

    for (int i = 0; i < 20; i++) {

        if (i < 5) printf(" %i: %i\n", i, array[i]);

        else printf(" %i: %i\n", i, array[i]);
    }
}

int sumOfThreadsInCells() {

    int sum = 0;

    for (int i = 0; i < 20; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {

    for (int i = 0; i < 20; i++) {

        pthread_mutex_init(&mutex_array[i], NULL);
    }


    int threadSize = 1000000;
    pthread_t threadId[threadSize];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int control;
    int created = 0;
    srand(time(0));

    for (int i = 0; i < threadSize; i++) {

        control = pthread_create(&threadId[i], &attr, &cell, NULL);

        if (control == 0) {
            created++;
        }
    }

    for (int j = 0; j < created; j++) {
        pthread_join(threadId[j], NULL);
    }

    visionOfCells();

    printf("\n------------\nThreads created: %i\n", created);
    printf("Total threads in the cells: %i\n\n\n", sumOfThreadsInCells());

    return 0;
}

void *cell() {

    int index = gBoard();

    while (pthread_mutex_trylock(&mutex_array[index]) != 0);

    array[index]++;
    pthread_mutex_unlock(&mutex_array[index]);

}

int gBoard() {

    int sum = 0;
    for (int i = 0; i < 19; i++) {

        sum += rand() % 2;
    }
    return sum;
}

/*!
                                           #-|-# Comments #-|-#

    The first thing I've realized when I've run my code a few times straight is that even if the number
of the threads in the cells changes, the total number of the created threads doesn't ever change.
(That number was 32754 for me.)

    The second thing is that the curve that has been formed is shaped like an close-parantheses ). Which means,
the maximum number of threads is in the middle cell -9th or 10th cell in this case. The whole thing reminds
me of the Pascal'sTriangle. Pascal's Triangle model goes like this:

                                          0th row -->       1
                                          1st row -->      1 1
                                          2nd row -->     1 2 1
                                          3rd row -->    1 3 3 1
                                          4th row -->   1 4 6 4 1
                                          5th row --> 1 5 10 10 5 1

    And when we get to 4th row, you can see what I meant earlier. The sequence somehow goes like the distribution
in our Galton Board model.

    Thus, I can say Galton Board is the physical model of the Pascal's Triangle probably.

    Also, the distribution of the Galton Board in large numbers is an example of Normal Distribution.

!*/