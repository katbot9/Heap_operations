#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int id;
    char name[30];
    int priority;
}info;

void swap(info*s,info*m){
    info temp;
    temp = *s;
    *s = *m;
    *m = temp;
}

int add_heap(info heap[], info toadd, int *nstudents, int size){
    int index;
    if(*nstudents == size){
        return 2;
    }
    index = (*nstudents)++;
    heap[index] = toadd;
    while(index>=1 && heap[index].priority>heap[(index-1)/2].priority){
        swap(&heap[index], &heap[(index-1)/2]);
        index = (index-1)/2;
    }
    return 1;
}

int findmaxindex(info maxheap[], int in, int ind){
    if(maxheap[in].priority>maxheap[ind].priority)
        return in;
    return ind;
}

void heapify(info heap[], int parent_index, int last_index){
    int right_index, left_index, maxindex;
    if(parent_index>(last_index-1)/2)
        return;
    right_index = parent_index*2+2;
    left_index = parent_index*2+1;
    if(right_index>last_index)
        maxindex = findmaxindex(heap, parent_index, left_index);
    else{
        maxindex = findmaxindex(heap, left_index, right_index);
        maxindex = findmaxindex(heap, maxindex, parent_index);
    }
    if(maxindex == parent_index)
        return 
    swap(&heap[maxindex], &heap[parent_index]);
    heapify(heap,maxindex,last_index);

}
int construct_heap(FILE* infp, info heap[]){
    int i = 0, n_students, last_index;
    char line[50];
    while(!feof(infp)){
        fgets(heap[i].name,50,infp);
        fscanf(infp,"%d\n",&heap[i].id);
        fgets(line,60,infp);
        i++;
    }
    n_students = i;
    last_index = n_students - 1;
    for(i = (last_index-1)/2;i>=0;i--){
        heapify(heap, i, last_index);
    }
    return n_students;
}

info deleteh(info heap[], int *n_students){
    info deleted;
    int last_index, right_index, left_index, index = 0, maxindex;
    deleted = heap[0];
    heap[0] = heap[*n_students-1];
    last_index = --(*n_students)-1;
    
    right_index = index*2+2;
    left_index = index*2+1;

    while(index<=(last_index-1)/2){
        if(right_index>last_index){
            maxindex = findmaxindex(heap,index,left_index);
        }else{
            maxindex = findmaxindex(heap, index, left_index);
            maxindex = findmaxindex(heap, maxindex, right_index);
        }

        if(maxindex == index)
            break;
        else{
            swap(&heap[index], &heap[maxindex]);
            index = maxindex;
        }
    }
    
}

void printsorted(info heap[], int n_students){
    info temp[10], deleted;
    int tempn = n_students;

    for(int i = 0; i<n_students;i++){
        temp[i] = heap[i];
    }
    while(tempn>0){
        deleted = deleteh(heap, &tempn);
        printf("%s ", deleted.name);
    }
}
