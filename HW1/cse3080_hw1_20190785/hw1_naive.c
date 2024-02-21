#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 10000000
#define MAX_PAT_SIZE 3000

char string[MAX_STR_SIZE];
char pat[MAX_PAT_SIZE];
int result[MAX_STR_SIZE];
int* naive(FILE* inFp_str, FILE* inFp_pat);

int main() {

    FILE* inFp_string = fopen("string.txt", "r");
    FILE* inFp_pat = fopen("pattern.txt", "r");

    if (inFp_string == NULL || inFp_pat == NULL) {
        printf("The string file does not exist.\n");
        return 1;
    }

    int* result = naive(inFp_string, inFp_pat);
   
    FILE* outFp = fopen("result_naive.txt", "w");
    if (outFp == NULL) {
        printf("Output file open error!\n");
        return 1;
    }

    fprintf(outFp, "%d\n", result[0]);
    for (int i = 1; i < (result[0] + 1); i++) {
        fprintf(outFp, "%d ", result[i]);
    }
    fprintf(outFp, "\n");




    int close_string = fclose(inFp_string);
    int close_pat = fclose(inFp_pat);
    int close_output = fclose(outFp);

    if (close_string == EOF) {
        printf("String file close error!\n");
        return 1;
    }
    if (close_pat == EOF) {
        printf("Pattern file close error!\n");
        return 1;
    }
    if (close_output == EOF) {
        printf("Output file close error!\n");
        return 1;
    }
   
    return 0;
}



int* naive(FILE* inFp_string, FILE* inFp_pat) {
    result[0] = 0;

    fgets(string, MAX_STR_SIZE, inFp_string);
    fgets(pat, MAX_PAT_SIZE, inFp_pat);

    int i,j;
    int x = 1;
    int start_match = 0;

    int last_pat = strlen(pat) - 2;
    int end_match = last_pat;
    int last_string = strlen(string) -1;

    for (i=0; end_match <= last_string; start_match++, end_match++) {
        if (string[end_match] == pat[last_pat]) {
            for (i = start_match, j=0; string[i] == pat[j] && j < last_pat; i++, j++);
            if (j == last_pat) {
                result[0] = result[0] + 1;
                result[x] = start_match;
                x++;
            }

        }
    }
    return result;
}

