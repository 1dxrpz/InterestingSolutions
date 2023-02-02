#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (!input(data, &n)) {
        printf("n/a");
        return 0;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}
int input(int *a, int *n) {
    if (!scanf("%d", n)) return 0;
    for (int *p = a; p - a < *n; p++) {
        if (!scanf("%d", p)) return 0;
    }
    return 1;
}
void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);
        if (p - a != n - 1) printf(" ");
    }
}
int max(int *a, int n) {
    int m = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p > m) m = *p;
    }
    return m;
}
int min(int *a, int n) {
    int m = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p < m) m = *p;
    }
    return m;
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
void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("\n%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}
