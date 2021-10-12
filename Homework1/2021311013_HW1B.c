#include <stdio.h>

int N, X;
int sum;
int arr[6];

void recursiveFunc(int cnt, int sum) {
    if(cnt == N) {
        if(sum == X) {
            for(int i = 0; i<N; i++) {
                printf("%d", arr[i]);
            }
            printf("\n");
            return;
        }
        else {
            return;
        }
    }
    for(int i = 0; i<4; i++) {
        arr[cnt] = i;
        recursiveFunc(cnt+1, sum+i);
    }
}

int main() {
    scanf("%d %d", &N, &X);

    recursiveFunc(0, 0);
}