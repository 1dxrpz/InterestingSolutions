#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
void output(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

int main() {
    int n, data[NMAX];
    if (!input(data, &n)) {
        printf("n/a");
        return 0;
    }
    output(data, n);
    return 0;
}
int input(int *a, int *n) {
    if (!scanf("%d", n)) return 0;
    for (int *p = a; p - a < *n; p++) {
        if (!scanf("%d", p)) return 0;
    }
    return 1;
}
double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += *p;
    }
    return sum / (double)n;
}
double variance(int *a, int n) {
    double m = mean(a, n);
    double result = 0;
    for (int *p = a; p - a < n; p++) {
        result += (*p - m) * (*p - m);
    }
    return result / (n);
}
void output(int *a, int n) {
    double mean_v = mean(a, n);
    double variance_v = variance(a, n);
    for (int *p = a; p - a < n; p++) {
        if (*p % 2 == 0 && *p >= mean_v && *p <= mean_v + 3 * sqrt(variance_v) && *p != 0) {
            printf("%d", *p);
            return;
        }
    }
    printf("0");
}
