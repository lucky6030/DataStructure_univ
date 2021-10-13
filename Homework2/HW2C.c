#include <stdio.h> 
#include <string.h>

char count[26];
int idx;

int isPalindrome(char str[]) {
    int len = strlen(str);
    for(int i = 0; i<len; i++) {
        if(str[i] != str[len-i-1])
            return 0;
    }
    return 1;
}

int canPalindrome(char str[]) {
    int oddCnt = 0;

    for(int i = 0; i<strlen(str); i++) {
        count[str[i]-'A']++;
    }
    for(int i = 0; i<26; i++) {
        if(count[i]%2 != 0) {
            oddCnt++;
            idx = i;
        }
    }

    if(oddCnt == 0) return 2;
    else if(oddCnt == 1) return 1;
    else return 0;
}

void swap(char* p1, char* p2) {
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int find(char str[], char ch) {
    for(int i = 0; i<strlen(str); i++) {
        if(str[i] == ch)
            return i;
    }
    return 0;
}

int main() {
    char input[102];
    scanf("%s", input);

    if(isPalindrome(input) == 1) {
        printf("%s\n", input);
        printf("0");
        return 0;
    }
    int flag = canPalindrome(input);
    int len = strlen(input);
    int cnt = 0;
    //printf("%d", flag);
    //printf("idx: %d\n", idx);

    if(flag == 1) {
        int findIdx = find(input, 'A'+idx);
        if(input[findIdx] != input[len/2]) {
            swap(&input[findIdx], &input[len/2]);
            cnt++;
            printf("%s\n", input);
        }
    }
    if(flag == 0) {
        printf("Impossible");
        return 0;
    }

    int left, right;
    int ret = 1;
    for(int i=0; i<len/2; i++) {
        left = i;
        right = len-left-1;
        //printf("left:%d right: %d\n", left, right);
        while(left < right) {
            if(input[left] == input[right]) {
                break;
            }
                
            else {
                right--;
                if(right == len/2 && flag==1) right--;
                ret = 0;
            }
        }
        if(left == right) {
            break;
        }
        if(ret == 0) {
            swap(&input[len-left-1], &input[right]);
            cnt++;
            printf("%s\n", input);
        }
        ret = 1;
    }
    // for(int i =0; i<len; i++) {
    //     if(count[i]) {
    //         printf("%c:%d ", 'A'+i, count[i]);
    //     }
    // }
    // printf("\n");
    // printf("%d\n", len);
    printf("%d", cnt);
}