#include <stdio.h>

int N, X;
int sum;
int arr[6];
int flag;

void recursiveFunc(int cnt, int sum) {
    if(cnt == N) {
        if(sum == X) {
            for(int i = 0; i<N; i++) {
                if(arr[i] != arr[N-1-i]) {
                    flag = 1;
                    break;
                }   
            }
            if(flag != 1) {
                for(int i = 0; i<N; i++) {
                    printf("%d", arr[i]);
                }
                printf("\n");
            }

            flag = 0;
            
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