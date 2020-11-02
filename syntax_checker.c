/* Created by MajorGamerJay under the MIT licenese
 * This is the solution to an exercise in
 * "The C Programming Language" - Brian Kernighan and Dennis Ritchie
 * on chapter 1, 1.10 - External Variables
 * Exercise 1-24.
 */

#include <stdio.h>

#define MAXCHARS 100000

char line[MAXCHARS];

int brackets_state;
int brackets_errlines_c;

int parenthesis_state;
int parenthesis_errlines_c;

int braces_state;
int braces_errlines_c;

int quotes_single_state;
int quotes_single_errlines_c;

int quotes_double_state;
int quotes_double_errlines_c;

get_stream();
void print_err(char err_msg[], int nest, int line);
check_if_in_quotes(char check, int pos);
check_brackets(int errlines[]);
check_parenthesis(int errlines[]);
check_braces(int errlines[]);
check_quotes_single(int errlines[]);
check_quotes_double(int errlines[]);

main()
{
    extern int brackets_errlines_c;
    extern int brackets_state;
    extern int parenthesis_errlines_c;
    extern int parenthesis_state;
    extern int braces_state;
    extern int braces_errlines_c;
    extern int quotes_single_state;
    extern int quotes_single_errlines_c;
    extern int quotes_double_state;
    extern int quotes_double_errlines_c;

    int bracket_errlines[20];
    int parenthesis_errlines[20];
    int braces_errlines[20];
    int quotes_single_errlines[20];
    int quotes_double_errlines[20];

    int total_chr         = get_stream();
    int bad_bracket       = check_brackets(bracket_errlines);
    int bad_parenth       = check_parenthesis(parenthesis_errlines);
    int bad_braces        = check_braces(braces_errlines);
    int bad_quotes_single = check_quotes_single(quotes_single_errlines);
    int bad_quotes_double = check_quotes_double(quotes_double_errlines);

    // printf("Bracket tests 1: %d\n", bracket_errlines[0]); Produces garbage
    printf("Hey shitass! Wanna code for real?\n");
    printf("---------------------------------\n");
    printf("Total characters: %d\n", total_chr);

    /* Please see to this anomaly
     * bad_bracket has to start from 1, not 0 as bad_bracket[0] always displays
     * garbage numbers whenever check_quotes_double() is called. This is very
     * weird and should be taken note of
     */

    if(bad_bracket != 0)
        for(int i = 1; i < brackets_errlines_c; ++i)
            if(bracket_errlines[i] != 0)
                print_err("Unclosed bracket, please check", brackets_state, bracket_errlines[i]);
    if(bad_parenth != 0)
        for(int i = 0; i < parenthesis_errlines_c; ++i)
            if(parenthesis_errlines[i] != 0)
                print_err("Unclosed parenthesis, please check", parenthesis_state, parenthesis_errlines[i]);
    if(bad_braces != 0)
        for(int i = 0; i < braces_errlines_c; ++i)
            if(braces_errlines[i] != 0)
                print_err("Unclosed braces, please check", braces_state, braces_errlines[i]);
    if(bad_quotes_single != 0)
        for(int i = 0; i < quotes_single_errlines_c; ++i)
            if(quotes_single_errlines[i] != 0)
                print_err("Unclosed single quotes, please check", quotes_single_state, quotes_single_errlines[i]);
    if(bad_quotes_double != 0)
        for(int i = 0; i < quotes_double_errlines_c; ++i)
            if(quotes_double_errlines[i] != 0)
                print_err("Unclosed double quotes, please check", quotes_double_state, quotes_double_errlines[i]);
}

get_stream()
{
    extern char line[];
    int c, i;

    for(i = 0; (c = getchar()) != EOF; ++i)
        line[i] = c;

    line[i] = '\0';
    return i;
}

void print_err(char err_msg[], int nest, int line)
{
    printf("On line: %d, Total unclosed: %d, Comment: %s\n", line, nest, err_msg);
}

check_if_in_quotes(char check, int pos)
{
    /* state 0 = out
     * state 1 = in
     */
    extern char line[];
    int i, state;
    int ignore = 0;
    state = 0;
    for(i = 0; line[i] == '\0'; ++i)
    {
        if(state == 0 && line[i] == '"' && i < pos)
            state = 1;
        else if(state == 1 && line[i] == '"' && i > pos)
            state = 0;
        else {
            if(state == 1 && line[pos] == check)
                ignore = 1;
        }
    }
    return ignore;
}

check_brackets(int errlines[])
{
    extern char line[];
    extern int brackets_state;
    extern int brackets_errlines_c;
    int tmp;
    int i, line_c;

    for(i = 0, line_c = 1, brackets_errlines_c = 1, brackets_state = 0; line[i] != '\0'; ++i) {
        if(line[i] == '\n')
            ++line_c;

        if(line[i] == '(') {
            int is_quoted = check_if_in_quotes('(', i);
            if(is_quoted == 0) {
                ++brackets_state;
                errlines[brackets_errlines_c] = line_c;
                tmp = brackets_errlines_c;
                ++brackets_errlines_c;
            }
        }

        else if(line[i] == ')') {
            int is_quoted = check_if_in_quotes(')', i);
            if(is_quoted == 0) {
                --brackets_state;
                errlines[tmp] = 0;
            }
        }
    }

    if(brackets_state != 0)
        return 1;
    else
        return 0;
}

check_parenthesis(int errlines[])
{
    extern char line[];
    extern int parenthesis_state;
    extern int parenthesis_errlines_c;
    int tmp;
    int i, line_c;

    for(i = 0, line_c = 1, parenthesis_errlines_c = 1, parenthesis_state = 0; line[i] != '\0'; ++i) {
        if(line[i] == '\n')
            ++line_c;

        if(line[i] == '{') {
            int is_quoted = check_if_in_quotes('{', i);
            if(is_quoted == 0) {
                ++parenthesis_state;
                errlines[parenthesis_errlines_c] = line_c;
                tmp = parenthesis_errlines_c;
                ++parenthesis_errlines_c;
            }
        }

        else if(line[i] == '}') {
            int is_quoted = check_if_in_quotes('}', i);
            if(is_quoted == 0) {
                --parenthesis_state;
                errlines[tmp] = 0;
            }
        }
    }

    if(parenthesis_state != 0)
        return 1;
    else
        return 0;
}

check_braces(int errlines[])
{
    extern char line[];
    extern int braces_state;
    extern int braces_errlines_c;
    int tmp;
    int i, line_c;

    for(i = 0, line_c = 1, braces_errlines_c = 1, braces_state = 0; line[i] != '\0'; ++i) {
        if(line[i] == '\n')
            ++line_c;

        if(line[i] == '[') {
            int is_quoted = check_if_in_quotes('[', i);
            if(is_quoted == 0) {
                ++braces_state;
                errlines[braces_errlines_c] = line_c;
                tmp = braces_errlines_c;
                ++braces_errlines_c;
            }
        }

        else if(line[i] == ']') {
            int is_quoted = check_if_in_quotes(']', i);
            if(is_quoted == 0) {
                --braces_state;
                errlines[tmp] = 0;
            }
        }
    }

    if(braces_state != 0)
        return 1;
    else
        return 0;
}

check_quotes_single(int errlines[])
{
    extern char line[];
    extern int quotes_single_state;
    extern int quotes_single_errlines_c;
    int tmp;
    int i, line_c;

    for(i = 0, line_c = 1, quotes_single_errlines_c = 1, quotes_single_state = 0; line[i] != '\0'; ++i) {
        if(line[i] == '\n')
            ++line_c;

        if(quotes_single_state == 0 && line[i] == '\'') {
            int is_quoted = check_if_in_quotes('\'', i);
            if(is_quoted == 0) {
                ++quotes_single_state;
                errlines[quotes_single_errlines_c] = line_c;
                tmp = quotes_single_errlines_c;
                ++quotes_single_errlines_c;
            }
        }

        else if(quotes_single_state > 0 && line[i] == '\'') {
            int is_quoted = check_if_in_quotes('\'', i);
            if(is_quoted == 0) {
                --quotes_single_state;
                errlines[tmp] = 0;
            }
        }
    }

    if(quotes_single_state != 0)
        return 1;
    else
        return 0;
}

check_quotes_double(int errlines[])
{
    extern char line[];
    extern int quotes_double_state;
    extern int quotes_double_errlines_c;
    int tmp;
    int i, line_c;

    for(i = 0, line_c = 1, quotes_double_errlines_c = 1, quotes_double_state = 0; line[i] != '\0'; ++i) {
        if(line[i] == '\n')
            ++line_c;

        if(quotes_double_state == 0 && line[i] == '"') {
            ++quotes_double_state;
            errlines[quotes_double_errlines_c] = line_c;
            tmp = quotes_double_errlines_c;
            ++quotes_double_errlines_c;
        }

        else if(quotes_double_state > 0 && line[i] == '"') {
            --quotes_double_state;
            errlines[tmp] = 0;
            }
        }

    if(quotes_double_state != 0)
        return 1;
    else
        return 0;
}
