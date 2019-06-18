#include <iostream>
#include <stdio.h>

#define LEFT(i) (2*i+1)


/**
 * 最大堆
 * 理解，第一步就是要保持堆的性质，递归跟左右子树比较找到最大的那个交换，如果有变动，就递归，没有则停止。
 * 第二步就是构建堆，从2/n-1处向左不断的调用max_heapity, 这样，整个堆就完成了，最大的在堆的顶部。
 * 第三步就是排序，把堆顶最大值跟最右边交换，然后右边的索引左移，保持堆的性质，这样就可以从小到大排序。
 */

/**
 * 保持堆的性质,跟左右子树比较，找到最大值的交换，递归。没有则停止
 */
void max_heapity(int* arr, int i, int n){
    int left = LEFT(i);
    int right = left + 1;
    int largest = i;
    if (left <=n-1 && arr[left] > arr[largest]){
        largest = left;
    }
    if (right <=n-1 && arr[right] > arr[largest]){
        largest = right;
    }
    if (largest != i){
        std::swap(arr[largest],arr[i]);
        max_heapity(arr, largest, n);
    }
}

//建堆
void build_heap(int* arr, int n){
    for (int i = n/2-1; i>=0; i--){
        max_heapity(arr, i, n);
    }
}

//堆排序
void heap_sort(int* arr, int n){
    build_heap(arr, n);
    int idx = n;
    for (int i = n -1; i>=1; i--){
        std::swap(arr[i],arr[0]);
        max_heapity(arr,0, --idx);
    }
}


int main()
{
    int len = 10;
	int arr[len] = {16,14,10,8,7,9,3,2,4,1};
	heap_sort(arr,len);
	for(int i = 0 ; i <len; i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}

//g++ -o test heap_sort.cpp