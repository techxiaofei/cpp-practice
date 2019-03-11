#include <iostream>
#include <algorithm>

int partition(int *arr, int left, int right){
    int tmp = arr[left];
    int i = left;
    int j = right;

    while (i<j){
        while (arr[j]>=tmp && i < j)j--;
        while(arr[i]<=tmp && i<j)i++;
        if(i<j){
            std::swap(arr[i],arr[j]);
        }
    }
    if (left < i){
        std::swap(arr[left],arr[i]);
    }
    return i;
}

void quick_sort(int *arr, int left, int right){
    if (left < right){
        int mid = partition(arr, left, right);
        quick_sort(arr, left, mid-1);
        quick_sort(arr, mid+1, right);
    }
}

int main(){
    int len = 10;
    int a[len] = {3,2,5,1,7,8,6,9,4,0};
 
   printf("before: ");
   for(int i = 0; i < len; ++i) {
     printf("%d ", a[i]);
   }
   printf("\n");
 
   quick_sort(a, 0, len-1);
 
   printf("after: ");
   for(int i = 0; i < len; ++i) {
     printf("%d ", a[i]);
   }
   printf("\n");
 
   return 0;
}