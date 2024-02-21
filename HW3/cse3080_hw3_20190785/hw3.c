#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define MAX_VERTICES 10000
#define MAX_EDGES 50000000


//Structure for 'node' which is component of 'graph'
struct node{
    int dest;
    int weight;
    struct node* link;
};
typedef struct node* nodePtr;
nodePtr graph[MAX_VERTICES];

//Structure for 'element' which is component of 'min heap' 
typedef struct {
    int from, to;
    int weight;
}element;
int E_num=0;
element E[MAX_EDGES];

void make_minheap(element* E, int* E_num, nodePtr graph[], int vertex_num);
element delete_minheap(element* heap, int* E_num);
int Find(int* parent, int i);
void Union(int* parent, int i, int j);


int main(int argc, char* argv[]) {
    clock_t start, end;
    double running_time;

    //Measure the start time of program
    start = clock();

    
    //Check if correct numbers of arguments are given.
    if (argc != 2) {
        fprintf(stderr, "usage: ./hw3 input_filename\n");
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
 
    //Open the output file to write result 
    FILE* outFp = fopen("hw3_result.txt", "w");


    /************************Read the input file******************************/
    int vertex_num=0, edge_num=0;
    int from, to, wt, num;
    int scan_result;

    //Read 1st, 2nd line to store vertex_num and edge_num
    if (fscanf(inFp, "%d", &num) == 1) {
        if (num > MAX_VERTICES) {
            fprintf(stderr, "The number of vertices is out of range.\n");
            exit(1);
        }
        else vertex_num = num;
    }
    if (fscanf(inFp, "%d", &num) == 1) {
        if (num > MAX_EDGES) {
            fprintf(stderr, "The number of edges is out of range.\n");
            exit(1);
        }
        edge_num = num;
    }


    //Dynmically allocate memory we need to execute kruskal's algorithm
    
    //MST array: store the result of kruskal's algorithm
    element* MST= (element*)malloc((vertex_num) * sizeof(element));

    //parent array: needed to check if cycle creates when add new edge
    int* parent = (int*)malloc((edge_num) * sizeof(int));
    for (int i = 0; i < edge_num; i++) parent[i] = -1;
    


    //Store the information of graph
    nodePtr input; 
    while ((scan_result = fscanf(inFp, "%d %d %d", &from, &to, &wt)) ==3) {
        input = (nodePtr)malloc(sizeof(struct node));
        input->weight = wt; input->dest = to; input->link = graph[from]; graph[from] = input;

        /*Although the input is undirected graph, we make directed graph to make min heap more easily
        input = (nodePtr)malloc(sizeof(struct node));
        input->weight = wt; input->dest = from; input->link = graph[to]; graph[to] = input;*/
    }


    /************************Start of making MST******************************/
    //1st step of MST
    //Sort the edges in ascending order of weight in min heap(E)
    make_minheap(E,&E_num, graph, vertex_num);
    
    //2nd step of MST
    //Union the edges which meet conditions
    int idx = 0;
    int chosen_from, chosen_to;
    
    element data;

    while (idx < (vertex_num - 1) && E_num > 0) {
        data = delete_minheap(E, &E_num);
        chosen_from = data.from; chosen_to = data.to;

        if (Find(parent, chosen_from) != Find(parent, chosen_to)) {
            if (parent[chosen_from] >= 0) chosen_from = Find(parent, chosen_from);
            if (parent[chosen_to] >= 0) chosen_to = Find(parent, chosen_to);
            Union(parent, chosen_from, chosen_to);
            MST[idx++] = data;
            fprintf(outFp, "%d %d %d\n", MST[idx - 1].from, MST[idx - 1].to, MST[idx - 1].weight);
        }
    }

    int sum=0;
       for (int i = 0; i < idx; i++) {
           sum += MST[i].weight;
       }
    fprintf(outFp, "%d\n", sum);

    if (idx < (vertex_num-1)) fprintf(outFp, "DISCONNECTED\n");
    else fprintf(outFp, "CONNECTED\n");
    
    
    end = clock();
    running_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("output written to hw3_result.txt.\n");
    printf("running time: %lf seconds\n", running_time);

    //Free all the memory dynamically allocated
    free(MST);
    free(parent);


    //Close all the file
    fclose(inFp);
    fclose(outFp);
    return 0;
}




void make_minheap(element* E, int* E_num, nodePtr graph[], int vertex_num) {
    if ((*E_num) == MAX_EDGES-1) {
        fprintf(stderr, "The MIN heap is full.\n");
        exit(1);
    }
    ++(*E_num);

    int j, i = (*E_num);
    nodePtr nodeWalker;
    for (j = 0; j < vertex_num; j++) {
        for (nodeWalker = graph[j]; nodeWalker != NULL; nodeWalker = nodeWalker->link) {
            while (1) {
                if (i == 1) break;
                if (nodeWalker->weight >= E[i / 2].weight) break;
                E[i] = E[i / 2];
                i /= 2;
            }
            //Insert the node into min heap
            E[i].from = j;
            E[i].to = nodeWalker->dest;
            E[i].weight = nodeWalker->weight;
            ++(*E_num);
            i = (*E_num);
        }

        
    }

 

    return;
}

element delete_minheap(element* E, int* E_num) {
    if ((*E_num) == 0) {
        fprintf(stderr, "The heap is empty.\n");
        exit(1);
    }

    //Save first element in 'first'
    element first = E[1];

    //Save the last element in 'last'
    element last = E[(*E_num)];
    (*E_num)--;

    //Starting point of parent and child
    int parent = 1, child = 2;

    while (1) {
        if (child >(* E_num)) break;

        //Check which one is smaller among left child and right child
        if (child <= (*E_num) - 1) {
            if (E[child + 1].weight < E[child].weight) ++child;
        }

        //Find the place where 'last' should be inputed
        if (last.weight <= E[child].weight) break;

        //Move the 'child' up to 'parent'
        E[parent] = E[child];

        //Move to down in the heap
        parent = child;
        child = child * 2;
    }

    //Input the 'last' into the place where we had found in previous process
    E[parent] = last;

    //Return the element what we have removed from the heap
    return first;
}

int Find(int* parent, int i) {
    while (parent[i] >= 0) {
        i = parent[i];
    }
    return i;
}

void Union(int* parent, int i, int j) {
    int node_num;
    node_num = parent[i] + parent[j];
    if (parent[i] <= parent[j]) {
        parent[j] = i;
        parent[i] = node_num;
    }
    else {
        parent[i] = j;
        parent[j] = node_num;
    }
    return;
}

