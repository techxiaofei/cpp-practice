#include <iostream>
#include <algorithm>
#include <stack>

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
/**
 * 快排递归实现 
 */
void quick_sort(int *arr, int left, int right){
    if (left < right){
        int mid = partition(arr, left, right);
        quick_sort(arr, left, mid-1);
        quick_sort(arr, mid+1, right);
    }
}

/**
 * 快排非递归实现
 */
void quick_sort2(int *arr, int left, int right){
    std::stack<int> st;
    if (left < right){
        st.push(left);
        st.push(right);
        /*
        int mid = partition(arr, left, right);
        if (left < mid - 1){
            st.push(left);
            st.push(mid-1);
        }
        if (mid + 1 < right){
            st.push(mid+1);
            st.push(right);
        }
        */

        while(!st.empty()){
            int r = st.top();
            st.pop();
            int l = st.top();
            st.pop();
            int mid = partition(arr, l, r);
            if (l<mid-1){
                st.push(l);
                st.push(mid-1);
            }
            if(mid+1<r){
                st.push(mid+1);
                st.push(r);
            }
        }
    }
}

int main(){
    int len = 10;
    int a[len] = {3,2,5,1,7,8,6,9,4,0};
    int b[len] = {102,234,45,74,3,12,345,1001,543,2};
 
   quick_sort2(a, 0, len-1);
   quick_sort2(b, 0, len-1);
 
   printf("after: ");
   for(int i = 0; i < len; ++i) {
     printf("%d ", a[i]);
   }
   printf("\n");
   for(int i = 0; i < len; ++i) {
     printf("%d ", b[i]);
   }
   printf("\n");
 
   return 0;
}

//g++ -o test quick_sort.cpp