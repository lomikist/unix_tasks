#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0) {
        double  a,
                b,
                c,
                half_per,
                area;

        printf("Child >> enter a triangle sides (a, b, c): ");
        scanf("%lf %lf %lf", &a, &b, &c);
        if (a + b < c || a + c < b || b + c < a)
            printf("Child: can't create triangle :\n");
        else
        {
            half_per = (a + b + c) / 2;
            area = sqrt(half_per * (half_per - a) * (half_per - b) * (half_per - c));
            printf("Triangle area: %lf\n", area);
        };
    } else {
        wait(NULL);
        double  a,
                b,
                area;
        printf("Parent >> enter a rect sides (a, b) : ");
        scanf("%lf %lf", &a, &b);
        if (a > 0 && b > 0)
        {
            area = a * b;
            printf("Parent: rect area is : %lf\n", area);
        }
        else 
            printf("Parent: not valid input :\n");

    }
    return 0;
}

