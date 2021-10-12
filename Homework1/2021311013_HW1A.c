#include <stdio.h>
#include <math.h>

int N, X;
int arr[6];

// 각 자릿수를 분리시켜 sum에 값을 더함
int calcDigit(int num) {
    int sum = 0;
    int add = 0;
    while(num) {
        add = num%10;
        if(add > 3 || add < 0)
            return -1;
        sum += num%10;
        num = num/10;
    }
    return sum;
}

// 몇 자릿수인지 계산
int cntDigit(int num) {
    int cnt = 0;
    while(num) {
        cnt++;
        num = num/10;
    }
    return cnt;
}

// 출력
void zeroAdd(int num) {
    int count = cntDigit(num);
    for(int i = 0; i<N-count; i++) {
        printf("0");
    }
    printf("%d\n", num);

}

int main() {

    scanf("%d %d", &N, &X);

    int end = 0;
    for(int i = 0; i<N; i++) {
        end += 3*pow(10, i);
    }

    for(int i = 0; i<=end; i++) {
        if(X == calcDigit(i)) {
            zeroAdd(i);
        }
        //printf("%d %d\n", i, calcDigit(i));
    }
}