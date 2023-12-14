#include <stdio.h>
#include <stdlib.h>

void insertionSort(int* array, int length){
    int i;
    for(i=0;i<length;i++){
        int insert_val = array[i];
        int empty_val = i;
        while(empty_val > 0 && array[empty_val-1] > insert_val){
            array[empty_val] = array[empty_val-1];
            empty_val--;
        }
        array[empty_val]=insert_val;
    }
}

void main(){
    int count;
    printf("Please enter how many elements are in the array: ");
    scanf("%i",&count);
    int* array = malloc(sizeof(int)*count);
    int i;
    for(i = 0;i < count;i++){
        int temp;
        printf("Enter element %i: ",i);
        scanf("%i",&temp);
        array[i] = temp;
    }
    printf("Current Array: ");
    for(i = 0; i < count;i++){
        printf("%i ",array[i]);
    }
    printf("\n");

    insertionSort(array,count);
    printf("New Array: ");
    for(i = 0; i < count;i++){
        printf("%i ",array[i]);
    }
    printf("\n");
    
}