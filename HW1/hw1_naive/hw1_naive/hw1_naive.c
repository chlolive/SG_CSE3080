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
	int start_match = 0; //��Ī�� ������ ��ġ �ʱ�ȭ
	int last_string = strlen(string) - 1; //string�� ������ ��ġ ����
	int last_pat = strlen(pat) - 1; //pat�� ������ ��ġ ����
	int end_match = last_pat; //��Ī�� ������ ��ġ�� pat�� ������ ��ġ�� ����

	for (i=0; end_match <= last_string; end_match++, start_match++) {  //end_match�� last_string�� ������ ������ start_match�� end_match 1�� �����ϸ� �ݺ���
		if (string[end_match] == pat[last_pat]) { //���� pat�� ������ ���ڿ� string[end_match]�� ������
			for (i = start_match, j = 0; string[i] == pat[j] && j < last_pat && string[i] != ' ' && pat[j] != ' '; i++, j++);//�ٸ� ���� ���ڵ鵵 pat�� string�� ��ġ�ϴ��� Ȯ���ϱ�
			if (j == last_pat) { //���� j�� last_pat�� ���ٸ� ������ �� ��Ī�ȴٴ� ���̹Ƿ�, ��Ī�� ���� ��ġ�� start_match�� result�迭�� �˸��� �ε����� ���� ����, ��ĪȽ���� result[0]�� ���� 1 ������Ŵ
				result[0] = result[0] + 1; //��ĪȽ�� ����
				result[x] = start_match; //��Ī ������ x��°���, �� x��° ��Ī�� �������� result[x]�� ����
				x++;
			}
			
		}
	}
	return result; 
}

