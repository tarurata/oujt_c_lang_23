#include <stdio.h>
#include <assert.h>

#define MAX_ROWS 16
#define BITS 16

void to_binary(unsigned int num, int binary[BITS]) {
    for (int i = 0; i < BITS; i++) {
        binary[i] = (num >> (BITS - 1 - i)) & 1;
    }
}

unsigned int to_decimal(int binary[BITS]) {
    int decimal = 0;
    for (int i = 0; i < BITS; i++) {
        decimal = (decimal << 1) | binary[i];
    }
    return decimal;
}

void binary_sum(int binary_numbers[MAX_ROWS][BITS], int sum_binary[BITS]) {
    int carry = 0; // For carrying in case of overflow

    // Initialize the sum as all zeros
    for (int i = 0; i < BITS; i++) {
        sum_binary[i] = 0;
    }

    // Loop from rightmost bit to leftmost bit
    for (int i = BITS - 1; i >= 0; i--) {
        int column_sum = carry; // start with the carry from previous step
        for (int j = 0; j < MAX_ROWS; j++) {
            column_sum += binary_numbers[j][i];
        }

        // Compute sum and carry
        sum_binary[i] = column_sum % 2; // if column_sum is 2, the sum is 0, if it's 3, the sum is 1
        carry = column_sum / 2; // if column_sum is 2 or 3, we have a carry of 1
    }

    // If there's a carry left after the last step, the sum has overflowed
    if (carry != 0) {
        printf("Overflow!\n");
        return;
    }

    // Print the binary sum
    printf("The binary sum is:\n{ ");
    for (int i = 0; i < BITS; i++) {
        printf("%d", sum_binary[i]);
        if (i < BITS - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
}


int multi(unsigned int num1, unsigned int num2) {
    // Convert given numbers to binary bits.
    int num1_binary[BITS] = {0};
    int num2_binary[BITS] = {0};

    to_binary(num1, num1_binary);
    to_binary(num2, num2_binary);

    // Then, calculate the result of multiplication by using the binary bits.
    int result_binary[MAX_ROWS][BITS];
    int row = 0;

    // Initialize result_binary with zeros
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < BITS; j++) {
            result_binary[i][j] = 0;
        }
    }

    for (int i = BITS-1; i >= 0; i--) {
        if (num1_binary[i] == 1) {
            if (row >= MAX_ROWS) {
                printf("Error: result_binary is full\n");
                return -1;
            }
            // Shift num2_binary by i places to the left and add to result_binary
            for (int j = i ; j >= 0; j--) {
                result_binary[row][j] = num2_binary[BITS - 1 - (i - j)];
            }
            row++;
        }
    }

    // Print the content of result_binary
    printf("The content of result_binary is:\n");
    for (int i = 0; i < row; i++) {
        printf("{ ");
        for (int j = 0; j < BITS; j++) {
            printf("%d", result_binary[i][j]);
            if (j < BITS - 1) {
                printf(", ");
            }
        }
        printf(" }\n");
    }

    // Convert the result to decimal number and return it.
    int result_sum_binary[BITS] = {0};
    binary_sum(result_binary, result_sum_binary);
    unsigned int result_decimal = to_decimal(result_sum_binary);
    printf("The result of multiplication is: %d\n\n", result_decimal);
    return result_decimal;
}

int main() {
    // Assert some patterns.
    assert(multi(100, 100) == 10000);
    assert(multi(0, 0) == 0);
    assert(multi(5, 6) == 30);
    assert(multi(5, 11) == 55);
    assert(multi(3, 2) == 6);
    assert(multi(0, 9) == 0);
   // Accept 2 numbers from user and print the result of multiplication.
    unsigned int num1, num2;
    printf("正の整数1 > ");
    scanf("%d", &num1);
    printf("正の整数2 > ");
    scanf("%d", &num2);
    multi(num1, num2);
    printf("%d * %d = %d\n", num1, num2, multi(num1, num2));
    return 0;
}