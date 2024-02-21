#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_SIZE 100
#define MAX_PAT_SIZE 30

int* nFind(FILE* inFp_str, FILE* inFp_pat);

int main() {
	
	FILE* inFp_string = fopen("D://string.txt", "r");
	FILE*inFp_pat = fopen("D://pattern.txt", "r");

	if (inFp_string == NULL || inFp_pat == NULL) {
		printf("The string file does not exist.\n");
		return 1;
	}

	int* result = nFind(inFp_string, inFp_pat);
	printf("%d\n", result[0]);
	for (int i = 1; i<(result[0]+1); i++) {
		printf("%d ", result[i]);
	}
	printf("\n");
	

	FILE* outFp = fopen("D://result_naive.txt", "w");
	if (outFp == NULL) {
		printf("Output file open error!\n");
		return 1;
	}

	fprintf(outFp, "%d\n", result[0]);
	for (int i = 1; i<(result[0]+1) ; i++) {
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



int* nFind(FILE* inFp_string, FILE* inFp_pat) {
	char* string = malloc(sizeof(char) * MAX_STR_SIZE);
	char* pat = malloc(sizeof(char) * MAX_PAT_SIZE);
	int* result = malloc(sizeof(int) * MAX_STR_SIZE);
	result[0] = 0; 

	fgets(string, MAX_STR_SIZE, inFp_string);
	printf("%s\n", string);

	fgets(pat, MAX_PAT_SIZE, inFp_pat);
	printf("%s\n", pat);

	int j = 0, i=0, x = 1;
	int start_match = 0; //매칭을 시작할 위치 초기화
	int last_string = strlen(string) - 1; //string의 마지막 위치 설정
	int last_pat = strlen(pat) - 1; //pat의 마지막 위치 설정
	int end_match = last_pat; //매칭이 끝나는 위치를 pat의 마지막 위치로 설정

	for (i=0; end_match <= last_string; end_match++, start_match++) {  //end_match와 last_string이 같아질 때까지 start_match와 end_match 1씩 증가하며 반복문
		if (string[end_match] == pat[last_pat]) { //만일 pat의 마지막 글자와 string[end_match]가 같으면
			for (i = start_match, j = 0; string[i] == pat[j] && j < last_pat && string[i] != ' ' && pat[j] != ' '; i++, j++);//다른 앞의 글자들도 pat과 string이 일치하는지 확인하기
			if (j == last_pat) { //만일 j와 last_pat이 같다면 끝까지 다 매칭된다는 뜻이므로, 매칭의 시작 위치인 start_match를 result배열에 알맞은 인덱스에 각각 저장, 매칭횟수인 result[0]의 값을 1 증가시킴
				result[0] = result[0] + 1; //매칭횟수 증가
				result[x] = start_match; //매칭 성공이 x번째라면, 그 x번째 매칭의 시작점을 result[x]에 저장
				x++;
			}
			
		}
	}
	return result; 
}

