#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/unistd.h>

#define NRED 8
#define NYEL 9
#define NGRE 4
#define NPIN 2
#define NVIO 3
#define NMARBLES 26

#define MAX_TRIALS 500

int main() {

    /*
     * A bag contains 8 red, 9 yellow, 4 green, 2 pink and 3 violet marbles.
     * Six marbles are drawn from the bag WITH replacement.
     * Create a simulation to determine the probability of getting 2 red, 2 yellow OR 1 green.
     * Create a computer simulation to determine this probability.
     */

    typedef struct Results {
        int validCount;
        int totalCount;
        double probabiliy;
    } results;

    typedef struct Draw {
        int red;
        int yellow;
        int green;
        int pink;
        int violet;
    } draw;

    float probRed = (float) NRED/NMARBLES * 100;
    float probYel = (float) NYEL/NMARBLES * 100;
    float probGre = (float) NGRE/NMARBLES * 100;
    float probPin = (float) NPIN/NMARBLES * 100;
    float probVio = (float) NVIO/NMARBLES * 100;

    struct Results game1, *game;
    struct Draw currentDraw1, *currentDraw;

    game = &game1;
    currentDraw = &currentDraw1;

    game->validCount = 0;
    game->totalCount = 0;

    double temp;

    for (int i = 0; i < MAX_TRIALS; ++i) {

        currentDraw->red = 0;
        currentDraw->yellow = 0;
        currentDraw->green = 0;
        currentDraw->pink = 0;
        currentDraw->violet = 0;

        for (int j = 0; j < 6; ++j) {
            sleep(1);
            srand(time(NULL));
            temp = rand() % 100;
            printf ("Rand is %f\n", temp);

            if (temp < probRed) (currentDraw->red)++;
            else if (temp < (probRed + probYel)) (currentDraw->yellow)++;
            else if (temp < (probRed + probYel + probGre)) (currentDraw->green)++;
            else if (temp < (probRed + probYel + probGre + probPin)) (currentDraw->pink)++;
            else if (temp < (probRed + probYel + probGre + probPin + probVio)) (currentDraw->violet)++;
            else {
                printf("Error : Returning\n");
                return 1;
            }
        }

        if (currentDraw->red == 2 || currentDraw->yellow == 2 || currentDraw->green == 1) (game->validCount)++;

        (game->totalCount)++;

    }

    game->probabiliy = (float) game->validCount / (float) game->totalCount;

    printf ("\nThe probability of winning is : %lf\n", game->probabiliy);

    return 0;
}
