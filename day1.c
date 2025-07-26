#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void merge(int arr[], int l, int m, int r)
{

    int i, j, k;
    int left_amount = m - l + 1;
    int right_amount = r - m;
    int L[left_amount], R[right_amount];

    for (i = 0; i < left_amount; i++)
    {
        L[i] = arr[l + i];
    }

    for(j = 0; j < right_amount; j++){
        R[j] = arr[m + j + 1];
    }

    i = 0;
    j = 0;
    k = l;
    while(i < left_amount && j < right_amount){
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < left_amount){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < right_amount){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r){
    
    if (l < r){
        int m = l + (r-l)/2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
    
}


int main()
{
    FILE *file;
    file = fopen("input.txt", "r");
    
    char buffer[256];
    int line_count = 0;
    while(fgets(buffer, 256, file)){
        line_count++;
    }

    int size = line_count;
    int left[line_count];
    int right[line_count];
    int total = 0;

    file = fopen("input.txt", "r");

    line_count = 0;

    while(fgets(buffer, 256, file)){
        int num1 = atoi(strtok(buffer, " "));
        int num2 = atoi(strtok(NULL, " "));
        left[line_count] = num1;
        right[line_count] = num2;

        line_count++;
    }

    merge_sort(left, 0, size - 1);
    merge_sort(right, 0, size - 1);

    int cur_left = 0;
    int cur_right = 0;
    int m_c = 0; // mutliple counter
    while(cur_left < size && cur_right < size){
        m_c = 0;
        if(left[cur_left] > right[cur_right]){
            cur_right++;
        }
        else if(left[cur_left] < right[cur_right]){
            cur_left++;
        }
        else{ // they are equal
            while(left[cur_left] == right[cur_right]){
                m_c++;
                cur_right++;
            }
            total += m_c * left[cur_left];
        }
    }

    printf("Total: %d\n", total);
    return 0;
}