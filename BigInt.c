/*
Name = Nitin Bhatt
BT23CSE107
Assignment1
Concepts in Programming Language
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 309

typedef struct {
    char s[SIZE];
    int sign;
} bigint;

int checkOverflow(const char *s) {
    return strlen(s) >= SIZE;
}

void removeLeadingZeros(bigint *num) {
    int i = 0;
    while (num->s[i] == '0' && num->s[i + 1] != '\0') {
        i++;
    }
    if (i > 0) {
        memmove(num->s, num->s + i, strlen(num->s) - i + 1);
    }
}

bigint subtractbigint(bigint a, bigint b);

bigint addbigint(bigint a, bigint b) {
    bigint ans;
    memset(ans.s, '0', SIZE);
    ans.s[SIZE - 1] = '\0';

    if (a.sign == b.sign) {
        int carry = 0, i = strlen(a.s) - 1, j = strlen(b.s) - 1, k = SIZE - 2;

        while ((i >= 0 || j >= 0 || carry) && k >= 0) {
            int sum = carry;
            if (i >= 0) sum += a.s[i--] - '0';
            if (j >= 0) sum += b.s[j--] - '0';
            ans.s[k--] = '0' + (sum % 10);
            carry = sum / 10;
        }
        if (carry || checkOverflow(ans.s)) {
            printf("Overflow in addition!\n");
            ans.s[0] = '\0';
            return ans;
        }
        memmove(ans.s, ans.s + k + 1, SIZE - k - 1);
        ans.sign = a.sign;
    } else {
        b.sign *= -1;
        return subtractbigint(a, b);
    }
    removeLeadingZeros(&ans);
    return ans;
}

bigint subtractbigint(bigint a, bigint b) {
    bigint ans;
    memset(ans.s, '0', SIZE);
    ans.s[SIZE - 1] = '\0';

    if (a.sign != b.sign) {
        b.sign *= -1;
        return addbigint(a, b);
    }

    int cmp = strcmp(a.s, b.s);
    bigint larger = cmp >= 0 ? a : b;
    bigint smaller = cmp < 0 ? a : b;

    if (cmp < 0) {
        printf("Underflow in subtraction!\n");
    }

    int borrow = 0, i = strlen(larger.s) - 1, j = strlen(smaller.s) - 1, k = SIZE - 2;

    while ((i >= 0 || j >= 0) && k >= 0) {
        int diff = (i >= 0 ? larger.s[i--] - '0' : 0) - (j >= 0 ? smaller.s[j--] - '0' : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        ans.s[k--] = '0' + diff;
    }
    memmove(ans.s, ans.s + k + 1, SIZE - k - 1);
    ans.sign = cmp >= 0 ? a.sign : -a.sign;
    removeLeadingZeros(&ans);
    return ans;
}

bigint multiplybigint(bigint a, bigint b) {
    bigint ans;
    memset(ans.s, '0', SIZE - 1);
    ans.s[SIZE - 1] = '\0';
    ans.sign = a.sign * b.sign;

    int l1 = strlen(a.s), l2 = strlen(b.s);
    if (l1 + l2 - 1 >= SIZE) {
        printf("Overflow in multiplication!\n");
        ans.s[0] = '\0';
        return ans;
    }

    for (int i = l1 - 1; i >= 0; i--) {
        int carry = 0;
        int k = SIZE - (l1 - i);
        for (int j = l2 - 1; j >= 0; j--) {
            int prod = (a.s[i] - '0') * (b.s[j] - '0') + (ans.s[k - 1] - '0') + carry;
            ans.s[k - 1] = '0' + (prod % 10);
            carry = prod / 10;
            k--;
        }
        if (carry > 0) {
            ans.s[k - 1] = '0' + carry;
        }
    }

    removeLeadingZeros(&ans);
    return ans;
}



int main() {
    int choice;
    char continue_flag = 'y';
    
    while (continue_flag == 'y' || continue_flag == 'Y') {
        bigint a, b, result;
        
        printf("\n=== Big Integer Calculator ===\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        
        if (choice == 4) {
            break;
        }
        
        if (choice >= 1 && choice <= 3) {
            printf("\nEnter first number: ");
            scanf("%s", a.s);
            if (a.s[0] == '-') {
                a.sign = -1;
                memmove(a.s, a.s + 1, strlen(a.s));
            } else {
                a.sign = 1;
            }

            printf("Enter second number: ");
            scanf("%s", b.s);
            if (b.s[0] == '-') {
                b.sign = -1;
                memmove(b.s, b.s + 1, strlen(b.s));
            } else {
                b.sign = 1;
            }
        }
        
        switch(choice) {
            case 1:
                printf("\nAddition: ");
                result = addbigint(a, b);
                break;
            case 2:
                printf("\nSubtraction: ");
                result = subtractbigint(a, b);
                break;
            case 3:
                printf("\nMultiplication: ");
                result = multiplybigint(a, b);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }
        
        if (result.s[0] != '\0') {
            if (result.sign == -1) printf("-");
            printf("%s\n", result.s);
        }
        
        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &continue_flag);
    }
    
    printf("\nProgram terminated. Thank you!\n");
    return 0;
}