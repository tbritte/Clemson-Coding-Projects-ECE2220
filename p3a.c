#include <stdio.h>

#define MAXLINE 80
#define MAXOPER 10

//Define boolean types just to simplify some conditionals
typedef int bool;
#define true 1
#define false 0

// named constants and strings
enum operations { NOOP, ADD, SUB, MUL, DIV };
const char *operation_str[] = {"Invalid", "+", "-", "*", "/"};

// function prototypes
int process_input(const char *input, char *op_left, char *op_right);
void calc_output(const char *op_l, int op, const char *op_r, char *result);

/* Just sees if the character is within the ASCII threshold of lower case letters
 * Input: Single character to be checked
 * Output: True if lower case, false if not.
 */
bool isLowerCase(char c) {
    return (c >= 97 && c <= 122 ? true : false);
}

/* Calculates an integer value between 2 single ASCII characters
 *
 * Input: Single characters for the left and right comparison, then the
 *        operator of which to apply to the integer ASCII values.
 * Output: Value of the character-operator-character, in integer form.
 *
 */
int applyOperator(const char l, int op, const char r) {
    //ex. test = 97
    // (test - 'a' + 1) is 1
    if (op == ADD) {
        return ((l - 'a' + 1) + (r - 'a' + 1)) - 1;
    }
    else if (op == SUB) {
        return ((l - 'a' + 1) - (r - 'a' + 1)) - 1;
    }
    else if (op == MUL) {
        return ((l - 'a' + 1) * (r - 'a' + 1)) - 1;
    }
    else if (op == DIV) {
        return ((l - 'a' + 1) / (r - 'a' + 1)) - 1;
    }
    else {
        return 0;
    }
}

// do not change any code in main.  We are grading based on the format
// of the output as given in the printfs in main.
int main() {
    char line[MAXLINE];
    char left_operand[MAXOPER];
    char right_operand[MAXOPER];
    char answer[MAXOPER];
    int  operator;

    printf("\nMP3: Pseudo arithmetic with + - * / on lowercase letters\n");
    printf("Commands:\n\tabc+aab\n\tturtle/frog\n");
    printf("\tOperands are no more than 9 letters and no spaces\n");
    printf("\tCtrl-d to quit\n\n");
    printf("Input>");

    // each call to fgets, collects one line of input and stores in line
    while (fgets(line, sizeof line, stdin) != NULL) {

        // clear for next round
        left_operand[0] = right_operand[0] = answer[0] = '\0';

        // check for valid grammar
        operator = process_input(line, left_operand, right_operand);
        if (operator == ADD || operator == SUB
                || operator == MUL || operator == DIV) {

            // print parsed input
            printf("'%s'", left_operand);
            printf(" %s ", operation_str[operator]);
            printf("'%s' => ", right_operand);

            // perform pseudo arithmetic
            calc_output(left_operand, operator, right_operand, answer);

            // print result
            printf("'%s'\n\n", answer);
        }
        else {
            printf("Bad input: %s\n", line);
        }

        printf("Input>");
    }

    printf("Goodbye\n");
    return 0;
}

/* Parse input of the form SOS where S is a string and O is a character.
 *
 * A string S must consist of one to nine lowercase letters.
 * The operand O must be one character from: + - * /
 * Any other characters found in the input, including spaces, are
 * grammatically incorrect and invalidate the input.
 *
 * There must be no spaces anywhere in the input, including between
 * either SO, OS, or leading or trailing spaces.
 *
 * Input: The input string is collected using fgets.  Recall the end-of-line
 *        character is included in the input string and marks the end of
 *        the input.  This string must not be changed.
 *
 * Output: There are three outputs from this function.
 *
 *   The return value is one of NOOP, ADD, SUB, MUL, DIV, which are
 *      named constants.  If the input is invalid for any reason
 *      then the output must be NOOP.  Otherwise the return value
 *      corresponds to operand O.
 *
 *   If the input is grammatically correct, then two strings are also
 *   returned, one for each of the left and right operands.  If the input
 *   in invalid the two output strings are undefined.
 */
int process_input(const char *input, char *op_left, char *op_right) {
    enum operations operatorEnum = NOOP;
    int leftLength = 0;
    int rightLength = 0;
    //until we get to the new line
    while (*input != '\n') {
        //if we don't have an operator, continue to read into the left operand
        if (operatorEnum == NOOP) {
            //current input
            if (*input == *operation_str[MUL]) {
                operatorEnum = MUL;
                *op_left = '\0';
            }
            else if (*input == *operation_str[DIV]) {
                operatorEnum = DIV;
                *op_left = '\0';
            }
            else if (*input == *operation_str[ADD]) {
                operatorEnum = ADD;
                *op_left = '\0';
            }
            else if (*input == *operation_str[SUB]) {
                operatorEnum = SUB;
                *op_left = '\0';
            }
            //not an operator yet, so keep reading into left operand
            else {
                //is it lowercase? if not then it's bad input
                if (!isLowerCase(*input)) {
                    return NOOP;
                }
                *op_left = *input;
                leftLength++;
                op_left++;
            }
        }
        //We have an operator and the left side seems to be valid
        else {
            if (!isLowerCase(*input)) {
                return NOOP;
            }
            //we have the operator and have filled the left operand
            *op_right = *input;
            rightLength++;
            op_right++;
        }
        input++;
    }
    //be sure to add the null character
    *op_right = '\0';

    //see if the lengths are >= 1 and <= 9
    if (!(leftLength >= 1 && leftLength <= 9) || !(rightLength >= 1 && rightLength <= 9)) {
        return NOOP;
    }

    return operatorEnum;
}

/* Pseudo mathematical opertions on the two operands work as follows.
 *
 * Each character is converted to an integer in the range 1...26, where a is 1,
 * b is 2, c is 3, ..., z is 26.  The operation is then performed using integer
 * math with no carries.  If the result is greater than or equal to 1 and less
 * than or equal to 26, the the output character should be the corresponding
 * lowercase letter.  However, if the result is outside the range 1-26, then
 * the output character should be the uppercase version of the input character
 * from the _left_ string.
 *
 * If the two input strings are not the same length, then each output character
 * beyond the length of the shorter string should be a copy of the character
 * from the longer string.
 *
 * Input: The two operand strings and the operator are assumed to be valid (and
 *        are verified as valid in the parse_input function).
 *
 * Output: The final string generated by the above rules is stored in the
 *         output string named result.  The input strings must not be
 *         changed.
 */
void calc_output(const char *l_op, int op, const char *r_op, char *result) {
    bool creatingResult = true;
    while (creatingResult) {
        //if both sides are valid characters
        if (*r_op != '\0' && *l_op != '\0') {
            int cValue = applyOperator(*l_op, op, *r_op);
            //value is outside the lower case, so just take the
            //left side and make it capital
            if (cValue < 0 || cValue >= 26) {
                *result = *l_op - ('a' - 'A');
            }
            else {
                *result = cValue + 'a';
            }
            result++;
        } else {
            //one side isn't valid, so we need to fill the rest of the result
            //with the valid string side.

            //left side is invalid
            if (*l_op == '\0') {
                while (*r_op != '\0') {
                    *result = *r_op;
                    result++;
                    r_op++;
                }
            }
            //right side is invalid
            else if (*r_op == '\0') {
                while (*l_op != '\0') {
                    *result = *l_op;
                    result++;
                    l_op++;
                }
            }
        }
        //both inputs have been exhaused, add null
        //character to result and exit the loop
        if (*l_op == '\0' && *r_op == '\0') {
            *result = '\0';
            creatingResult = false;
        }
        //while one isn't null, increment it.
        if (*l_op != '\0') l_op++;
        if (*r_op != '\0') r_op++;
    }
}
