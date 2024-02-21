#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define COMLEN 10
#define MAX_ELEMENTS_NUM 1000000


typedef struct {
    int key;
}element;

element MAXheap[MAX_ELEMENTS_NUM+1];
element MINheap[MAX_ELEMENTS_NUM+1];
int MINheap_num = 0;
int MAXheap_num = 0;
int MINheap2_num=0;
int MAXheap2_num=0;

void insert_MAXheap(element data, int* MAXheap_num);
void insert_MINheap(element data, int* MINheap_num);
element delete_MAXheap(element* heap, int* MAXheap2_num);
element delete_MINheap(element* heap, int* MINheap2_num);


int main(int argc, char* argv[]) {
    clock_t start, end;
    double running_time;
    start = clock();

    //Check if correct numbers of arguments are given.
    if (argc != 2) {
	fprintf(stderr, "usage: ./hw2 input_filename\n");
	exit(1);
    }
	
    //Open the input file.
    FILE* inFp;
    inFp = fopen(argv[1], "r");
    //Check if the input file exists.
    if (inFp == NULL) {
        fprintf(stderr, "The input file does not exist.\n");
        exit(1);
    }


    element input;
    int i;
    FILE* outFp = fopen("hw2_result.txt", "w");
    char command[COMLEN];
    int scan_result;

    while ((scan_result = fscanf(inFp, "%s %d", command, &input.key))!=0) {
        
        if(scan_result==2) {
            if (strcmp(command, "INSERT") == 0) {
                insert_MAXheap(input, &MAXheap_num);
                insert_MINheap(input, &MINheap_num);
            }
        }

        else if (scan_result==1) {

            //"ASCEND" command is inputed.
            if (strcmp(command, "ASCEND") == 0) {
 		     		
                //Copy the MINheap to MINheap2
		element* MINheap2= (element*)malloc(sizeof(element)*(MINheap_num+1));
                for (i = 1; i <= MINheap_num; i++) {
                    MINheap2[i] = MINheap[i];
                }
	

                //Delete the first element of heap and print it out
                MINheap2_num = MINheap_num;
                for (i = 1; i <= MINheap_num; i++) {
                    element item_deleted = delete_MINheap(MINheap2, &MINheap2_num);
                    fprintf(outFp, "%d ", item_deleted.key);
                }
		fprintf(outFp, "\n");
		free(MINheap2);
               
            }

            //"DESCEND" command is inputed
            else if (strcmp(command, "DESCEND") == 0) {
 		
                //Copy the MAXheap to MAXheap2
		element* MAXheap2= (element*)malloc(sizeof(element)*(MAXheap_num+1));
                for (i = 1; i <= MAXheap_num; i++) {
                    MAXheap2[i] = MAXheap[i];
                }
	

                //Delete the first element of heap and print it out
                MAXheap2_num = MAXheap_num;
                for (i = 1; i <= MAXheap_num; i++) {
                    element item_deleted = delete_MAXheap(MAXheap2, &MAXheap2_num);
                    fprintf(outFp, "%d ", item_deleted.key);
                }
		fprintf(outFp, "\n");
                free(MAXheap2);
            }
        }
        else break;
    }

    end = clock();
    running_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("output written to hw2_result.txt.\n");
    printf("running time: %lf seconds\n", running_time);

    fclose(inFp);
    fclose(outFp);
    return 0;

}

void insert_MAXheap(element data, int* MAXheap_num) {
    if ((*MAXheap_num) == MAX_ELEMENTS_NUM - 1) {
        fprintf(stderr, "The MAX heap is full.\n");
        exit(1);
    }
    ++(*MAXheap_num);

    int i = (*MAXheap_num);
    while (1) {
        if (i == 1) break;
        if (data.key <= MAXheap[i / 2].key) break;
        MAXheap[i] = MAXheap[i / 2];
        i /= 2;
    }
    MAXheap[i] = data;
}



void insert_MINheap(element data, int* MINheap_num) {
    if ((*MINheap_num) == MAX_ELEMENTS_NUM - 1) {
        fprintf(stderr, "The MIN heap is full.\n");
        exit(1);
    }
    ++(*MINheap_num);

    int i = (*MINheap_num);
    while (1) {
        if (i == 1) break;
        if (data.key >= MINheap[i / 2].key) break;
        MINheap[i] = MINheap[i / 2];
        i /= 2;
    }
    MINheap[i] = data;
}

element delete_MAXheap(element* heap, int* MAXheap2_num) {

    if ((*MAXheap2_num) == 0) {
        fprintf(stderr, "The heap is empty.\n");
        exit(1);
    }


    //Save first element in 'first'
    element first = heap[1];
    //Save the last element in 'last'
    element last = heap[(*MAXheap2_num)];
    (*MAXheap2_num)--;

    //Starting point of parent and child
    int parent = 1, child = 2;
    
    while (1) {
        if (child > *MAXheap2_num) break;

        //Check which one is bigger among left child and right child
        if (child <= (*MAXheap2_num)-1 ) {
            if (heap[child + 1].key > heap[child].key) ++child;
        }

        //Find the place where 'last' should be inputed
        if (last.key >= heap[child].key) break;

        //Move the 'child' up to 'parent'
        heap[parent] = heap[child];

        //Move to down in the heap
        parent = child;
        child = child * 2;
    }

    //Input the 'last' into the place where we had found in previous process
    heap[parent] = last;

    //Return the element what we have removed from the heap
    return first;
}


element delete_MINheap(element* heap, int* MINheap2_num) {
    if ((*MINheap2_num) == 0) {
        fprintf(stderr, "The heap is empty.\n");
        exit(1);
    }

    //Save first element in 'first'
    element first = heap[1];

    //Save the last element in 'last'
    element last = heap[(*MINheap2_num)];
    (*MINheap2_num)--;

    //Starting point of parent and child
    int parent = 1, child = 2;

    while (1) {
        if (child > *MINheap2_num) break;

        //Check which one is smaller among left child and right child
        if (child <= (*MINheap2_num) - 1) {
            if (heap[child + 1].key < heap[child].key) ++child;
        }

        //Find the place where 'last' should be inputed
        if (last.key <= heap[child].key) break;

        //Move the 'child' up to 'parent'
        heap[parent] = heap[child];

        //Move to down in the heap
        parent = child;
        child = child * 2;
    }

    //Input the 'last' into the place where we had found in previous process
    heap[parent] = last;

    //Return the element what we have removed from the heap
    return first;
}
