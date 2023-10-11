#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

typedef enum { false, true } bool;

const char usage[] = "To use the counter, please do --stopwatch or -s for a stopwatch that counts up\nOr --timer or -t for a timer that counts down. For the timer, specify the time with --seconds or -sc\nYou can also specify the seconds for the stopwatch and it will always stop after that amount of seconds\nExample counter -t -sc 30 will count down 30 seconds";

int main(int argc, char *argv[])
{
    bool count_up;
    int seconds = INT_MAX;

    if (argc < 2) {
        fprintf(stderr,"too few arguments\n");
        printf("%s\n",usage);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")) {
            printf("%s\n",usage);
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[i],"-s") || !strcmp(argv[i],"--stopwatch")) {
            count_up = true;
        }
        else if (!strcmp(argv[i],"-t") || !strcmp(argv[i],"--timer")) {
            count_up = false;
            seconds = 0;
        }
        else if (!strcmp(argv[i],"-sc") || !strcmp(argv[i],"--seconds")) {
            seconds = atoi(argv[++i]);
        }
    }
    /* 
       If count up is true, true is 1 and we want it to go from 0 to seconds, otherwise we want it to go from seconds to 0 
       */
    int init = count_up ? 0 : seconds;
    int end = count_up ? seconds : 0;
    int jump = count_up ? 1 : -1;
    if (end == INT_MAX) {
        printf("counting from %d to infinity\n",init);
    }
    else {
        printf("counting from %d to %d\n",init,end);
    }
    for (int k = init; (jump*k)<end; k += jump) {
        printf("\r          ");
        printf("\r%d",k + count_up);
        fflush(stdout);
        sleep(1);

    }
    printf("\n");
    return EXIT_SUCCESS;
}
