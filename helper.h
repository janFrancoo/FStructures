#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int minimum(int *arr, int n) {
    int min = arr[0];
    for (int i=1; i<n; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

int maximum(int *arr, int n) {
    int max = arr[0];
    for (int i=1; i<n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int max(int num1, int num2) {
    return num1 > num2 ? num1 : num2;
}

void printBlank(int len) {
    char *blank = malloc(sizeof(char) * (len + 1));
    for(int i=0; i<len; i++)
        blank[i] = ' ';
    blank[len] = '\0';
    printf("%s", blank);
}

void selectionSort(int arr[], int n) {
    for (int i=0; i<n-1; i++) {
        int min_idx = i;
        for (int j=i+1; j<n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

// CAN BE APPLIED A BETTER SOLUTION USING SIEVE METHOD!!!
// CAN BE APPLIED A BETTER SOLUTION USING SIEVE METHOD!!!
// CAN BE APPLIED A BETTER SOLUTION USING SIEVE METHOD!!!
int generatePrimes(int n) {
    int j, prime;
    for (int i=2; i<n; i++) {
        for (j=2; j<i-1; j++)
            if (i % j == 0) {
                break;
            }
        if (i == (j + 1))
            prime = i;
    }
    return prime;
}

#endif // HELPER_H_INCLUDED
