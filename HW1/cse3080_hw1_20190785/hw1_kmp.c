#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 10000000
#define MAX_PAT_SIZE 3000

char string[MAX_STR_SIZE];
char pat[MAX_PAT_SIZE];
int failure[MAX_PAT_SIZE];
int result[MAX_STR_SIZE];

void fail(char* pat);
int* kmp(FILE* inFp_str, FILE* inFp_pat);

int main() {

    FILE* inFp_string = fopen("string.txt", "r");
    FILE* inFp_pat = fopen("pattern.txt", "r");

    if (inFp_string == NULL || inFp_pat == NULL) {
        printf("The string file does not exist.\n");
        return 1;
    }
    
    int* result = kmp(inFp_string, inFp_pat);


    FILE* outFp = fopen("result_kmp.txt", "w");
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


void fail(char* pat) {
    int len_pat = strlen(pat);
    failure[0] = -1;
    int x;

    for (int i = 1; i < (len_pat-1); i++) {
        x = failure[i - 1];
        while ((pat[i] != pat[x + 1]) && (x >= 0))  x = failure[x];
        if (pat[i] == pat[x + 1]) failure[i] = x + 1;
        else failure[i] = -1;
    }
}

int* kmp(FILE* inFp_string, FILE* inFp_pat) {
    result[0] = 0;

    fgets(string, MAX_STR_SIZE, inFp_string);
    fgets(pat, MAX_PAT_SIZE, inFp_pat);
    fail(pat);
    int len_pat = strlen(pat)-1;
    int len_string = strlen(string)-1;
    int i, j, x=1;
    for (i = 0, j = 0; i < len_pat && j < len_string;) {
        if (pat[i] == string[j]) {
            i++;
            j++;
            if (i == len_pat) {
                result[0]++;
                result[x] = j - len_pat;
                x++;
                i = failure[i - 1] + 1;
            }
        }
        else if (i == 0) j++;
        else i = failure[i - 1] + 1;
        
        
    }

    return result;
}

