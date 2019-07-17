#include<iostream>
#include<vector>

using namespace std;

/* ----------------------------- 1. 插入排序类 ---------------------*/
class InsertionSort{
public:
    int compareCount ;    // 比较次数
    int moveCount;        // 移动次数

    // 初始化比较次数和移动次数，调用各个排序函数前调用
    void initCount(){
        compareCount = 0;
        moveCount    = 0;
    }

    // 直接插入排序法，对容器或数组nums进行排序
    void sInsertion(vector<int> &nums){
        int len = nums.size();

        for(int i = 1; i < len; i++){               // 以第一个数（nums[0]）为已排好序的部分，将之后的记录进行插入
            compareCount++;
            if(nums[i] < nums[i-1]){
                int temp = nums[i];                 // 临时变量，用于存储nums[i]
                int j = i - 2;
                nums[i]  = nums[i-1];
                moveCount++;

                while(j >= 0 && temp < nums[j]){    // 从后往前，寻找temp应插入的位置
                    nums[j+1] = nums[j];            // 记录后移
                    j--;
                    compareCount++;
                    moveCount++;
                }
                nums[j+1] = temp;                   // 插入正确的位置
                moveCount++;
            }
            compareCount++;
        }
        printf("插入排序——直接插入排序法，数组长度：%d ，比较次数：%d，移动次数: %d 。\n", len, compareCount, moveCount);
    }

    // 折半插入排序法，对容器或数组nums进行排序
    void bInsertSort(vector<int> &nums){
        int len = nums.size();

        for(int i = 1; i < len; i++){
            int temp = nums[i];
            int low = 0, high = i - 1;

            while(low <= high){                 // 寻找 0 ~ i-1 中， nums[i]应插入的位置
                compareCount++;
                int m = (low + high) / 2;
                if(nums[m] > temp){             // 插入位置在低半区
                    high = m - 1;
                }else {
                    low  = m + 1;               // 插入位置在高半区
                }
                compareCount++;
            }

            for(int j = i - 1; j >= low; j--){  // 记录后移，插入位置为 high+1 或 low
                nums[j+1] = nums[j];
                moveCount++;
                compareCount++;
            }
            nums[low] = temp;                   // 插入
            moveCount++;
            compareCount++;
        }
        printf("插入排序——折半插入排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }

    // 二路插入排序法，对容器或数组nums进行排序
    void p2_InsertSort(vector<int> &nums){
        int len = nums.size();
        int i, j, first, last, mid;
        vector<int> d;
        d.resize(len);          // 生成 len 个记录的临时空间
        d[0] = nums[0];
        first = last = 0;       // first和last分别指示 d 中排好序的记录的第一个和最后一个位置

        for(i = 1; i < len; i++){
            if(first > last){
                j = len;        // j 是调整系数
            }else{
                j = 0;
            }
            compareCount++;
            mid = ( (first + last + j) / 2 ) % len;  // d 的中间记录的位置
            if(nums[i] < d[mid]){                    // 待插记录应插在 d 的前半部分
                j = first;                           // j 指向 d 的第一个记录
                first = (first - 1 + len) % len;     // first 前移，取余是为了实现循环数组效果
                while(nums[i] > d[j]){               // 待插记录大于 j 所指记录
                    d[(j - 1 + len) % len] = d[j];   // j 所指记录前移，取余是为了实现循环数组效果
                    j = (j + 1) % len;               // j 指向下一个记录
                    compareCount++;
                    moveCount++;
                }
                d[(j - 1 + len) % len] = nums[i];    // 移动结束，待插记录插在[j]前
            }else{                                   // 待插记录应插在 d 的后半部分
                j = last;                            // j 指向当前的最后一个记录
                last++;                              // last 指向插入后的最后一个记录
                while(nums[i] < d[j]){               // 待插记录小于 j 所指记录
                    d[(j + 1 ) % len] = d[j];        // j 所指记录后移
                    j = (j - 1 + len) % len;         // j 指向上一个记录
                    compareCount++;
                    moveCount++;
                }
                d[(j + 1) % len] = nums[i];          // 待插记录不小于 j 所指记录，插在 j 后
            }// end else
            compareCount++;
            moveCount++;
        }// end for
        for(i = 0; i < len; i++){                    // 把在 d 中排好序的记录依次赋给nums
            nums[i] = d[(first + i) % len];
            moveCount++;
            compareCount++;
        }
        printf("插入排序——2-路插入排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }


    // 希尔排序法，对容器或数组nums进行排序
    void shellSort(vector<int> &nums){
        int len = nums.size();
        int gap          = len; // 增量，初始设为len

        do{
            gap = gap/3 + 1;    // 计算增量，形成增量序列
            for(int i = gap; i < len; i++){
                compareCount++;
                if(nums[i] < nums[i-gap]){
                    int temp = nums[i];               // 当前数据暂存在temp
                    int j = i - gap;
                    while(j >= 0 && temp < nums[j]){  // 与在当前增量条件下的子序列的其他记录相比较，确定nums[i]应插入（交换）的位置
                        nums[j + gap] = nums[j];      // 记录后移
                        j -= gap;
                        compareCount++;
                        moveCount++;
                    }
                    nums[j + gap] = temp;             // 插入
                    moveCount++;
                }
                compareCount++;
            }
            compareCount++;
        }while(gap > 1);

        printf("插入排序——希尔排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }
};


/*  ----------------------------- 2. 交换排序类 ----------------------------  */
class ExchangeSort{
public:
    int compareCount ;    // 比较次数
    int moveCount;        // 移动次数

    // 初始化比较次数和移动次数，调用各个排序函数前调用
    void initCount(){
        compareCount = 0;
        moveCount    = 0;
    }

    // 冒泡排序法，对容器或数组nums进行排序
    void bubbleSort(vector<int> &nums){
        int len = nums.size();
        bool isChange    = true; // 是否有记录交换的标志位，防止后面的记录已经是有序的还执行循环
        for(int i = 0; i < len - 1 && isChange; i++){
            isChange = false;
            for(int j = i + 1; j < len; j++){   // 遍历 nums[i]之后的记录
                compareCount++;
                if(nums[j] < nums[i]){          // 存在小于 numsp[i] 的记录时，交换两记录
                    swap(nums[i], nums[j]);
                    isChange = true;
                    moveCount++;
                }
                compareCount++;
            }
            compareCount++;
        }
        printf("交换排序——冒泡排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }


    // --- 快速排序法的划分函数，对数组或集合 nums 进行划分，并返回枢轴所在位置
    int partition(vector<int> &nums, int low, int high){
        int len = nums.size();
        int pivot;      // 枢轴的值
        int temp;       // 临时变量，用于存储枢轴

        pivot = nums[low];     // 确定枢轴的值，需优化
        temp  = pivot;    // 存储枢轴的值，避免多余的交换

        while(low < high){
            while(low < high && nums[high] >= pivot){
                high--;
                compareCount++;
            }
            nums[low] = nums[high];   // 将右端小于枢轴的记录放入左端
            moveCount++;

            while(low < high && nums[low] <= pivot){
                low++;
                compareCount++;
            }
            nums[high] = nums[low];   // 将左端大于枢轴的记录放入右端
            moveCount++;

            compareCount++;
        }
        nums[low] = temp;             // 放入枢轴的值
        moveCount++;
        return low;                   // 返回枢轴所在位置
    }

    // -- 快速排序法，对数组或容器 nums 中 [low, high] 之间的记录进行快速排序
    void qSort(vector<int> &nums, int low, int high){
        int pivotkey;   // 枢轴的位置
        if(low < high){
            pivotkey = partition(nums, low, high);
            qSort(nums, low, pivotkey - 1);
            qSort(nums, pivotkey + 1, high);
        }

    }

     // - 快速排序法的容器函数，对容器或数组nums进行排序
    void quickSort(vector<int> &nums){
        int len = nums.size();
        qSort(nums, 0, len);
        printf("交换排序——快速排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }

};


/* ----------------------------- 3. 选择排序类 --------------------  */
class SelectionSort{
public:
    int compareCount ;    // 比较次数
    int moveCount;        // 移动次数

    // 初始化比较次数和移动次数，调用各个排序函数前调用
    void initCount(){
        compareCount = 0;
        moveCount    = 0;
    }

    // 简单选择排序法，对容器或数组nums进行排序
    void sSelectionSort(vector<int> &nums){
        int len = nums.size();
        for(int i = 0; i < len - 1; i++){
            int currMinIndex = i;                 // 最小记录的下标
            for(int j = i + 1; j < len; j++ ){
                compareCount++;
                if(nums[j] < nums[currMinIndex]){
                    currMinIndex = j;
                }
                compareCount++;
            }
            swap(nums[i], nums[currMinIndex]);    // 将最小记录与当前记录nums[i]进行交换。
            moveCount++;

            compareCount++;
        }
        printf("选择排序——简单选择排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }




    // 堆排序法的堆调整函数，已知nums[low ~ high] 中的记录除 nums[low]之外均满足大顶堆的定义，
    // 向下调整 nums[low]， 使 nums[low ~ high] 中记录均满足大顶堆的定义
    void heapAdjust(vector<int> &nums, int low, int high){
       int temp = nums[low];                                    // 利用临时变量存储待调整数据
       for(int j = 2 * low + 1; j <= high; j = 2 * j + 1){      // 沿值较大的孩子结点向下筛选
           compareCount++;
           if( j < high && nums[j] < nums[j + 1]){              // 左孩子小于右孩子
                j++;                                            // j 为值较大的记录的下标，即 j 指向[low]的右孩子
           }
           compareCount++;
           if(temp >= nums[j]){                                 // [low]的值大于或等于[j]的值
                break;                                          // 不必再调整，跳出for循环
           }
           nums[low] = nums[j];                                 // 否则，[j]为大顶，插入[low]
           low = j;                                             // [low]的位置向下移到[j]，即原左或右孩子处
           moveCount++;
           compareCount++;
       }
       nums[low] = temp;                                        // 将待调整的记录插入[low]
       moveCount++;
       compareCount++;
    }

    // 堆排序法，对容器或数组nums进行排序
    void heapSort(vector<int> &nums){
        int len = nums.size();
        int i;
        for(i = len / 2 - 1; i >= 0; i--){                        // 从最后一个非叶子子结点到[0]
            heapAdjust(nums, i, len - 1);                        // 调整nums[i]，使nums[i ~ len-1] 成为大顶堆
        }

        for(i = len - 1; i > 0; i--){
            swap(nums[0], nums[i]);                              // 交换堆顶记录[0]和未完全排序的nums[1 ~ i]中的最后一个记录[i]
            moveCount++;
            heapAdjust(nums, 0, i - 1);                             // 调整nums[0]，使num[0 ~ i-1]重新成为大顶堆
        }
        printf("选择排序——堆排序法，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }

};



/* ----------------------------- 4. 归并排序类 --------------------  */
class MergingSort{
public:
    int compareCount ;    // 比较次数
    int moveCount;        // 移动次数

    // 初始化比较次数和移动次数，调用各个排序函数前调用
    void initCount(){
        compareCount = 0;
        moveCount    = 0;
    }

    // 2路归并排序法，对容器或数组nums进行排序，递归法
    void mergeSort(vector<int> &nums){
        int len = nums.size();
        mSort(nums, 0, len);   // 将无序的nums[0 ~ len] 归并排序为有序
        printf("选择排序——简单选择排序法递归实现，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }

    // 2路归并排序法，将nums[low ~ high] 归并排序为 temp[low ~ high]
    void mSort(vector<int> &nums, int low, int high){
        if(low < high){                     // 有不只一个元素待归并
            int m = (low + high) / 2;
            mSort(nums, low, m);            // 递归将nums[low ~ m]归并为有序的 nums[low ~ m]
            mSort(nums, m + 1, high);       // 递归将nums[m+1 ~ high]归并为有序的 nums[m+1 ~ high]
            Merge(nums, low, m, high);      // 将 nums[low ~ m] 和 nums[m+1 ~ high] 归并到 nums[low ~ high]
        }
    }

    // 2路归并排序法的合并函数，将有序的nums[low ~ m]与nums[m+1 ~ high] 合并为有序的nums[low ~ high]
    void Merge(vector<int> &nums, int low, int m, int high){
        int len = nums.size();
        vector<int> temp;             // 临时容器，用于暂存排好序的记录
        temp.resize(len);             // 设置临时容器大小
        int i = low;                  // nums[low ~ m] 范围内的下标
        int j = m + 1;                // nums[m+1 ~ high] 范围内的下标
        int k = low;                  // temp[low ~ high]的下标
        while(i <= m && j <= high){
            if(nums[i] < nums[j]){
                temp[k] = nums[i++];
            }else{
                temp[k] = nums[j++];
            }
            k++;
        }

        while(i <= m){                 // 若temp[low ~ m] 还剩下数据，直接放到temp之后
            temp[k++] = nums[i++];
        }

        while(j <= high){              // 若temp[m+1 ~ high] 还剩下数据，直接放到temp之后
            temp[k++] = nums[j++];
        }

        for(i = low; i <= high; i++){  // 将归并好的记录放回nums
            nums[i] = temp[i];
        }
    }


    // 2路归并排序法，对容器或数组nums进行排序，迭代法
    void mergeSort2(vector<int> &nums){
        int len = nums.size();
        int currLen = 1;  // 归并长度从1开始
        while( currLen < len){
            mSort2(nums, currLen, len);
            currLen *= 2;
        }  // 将无序的nums[0 ~ len] 归并排序为有序
        printf("选择排序——简单选择排序法迭代实现，数组长度：%d ，比较次数：%d，移动次数: %d。\n", len, compareCount, moveCount);
    }

    // 2路归并排序法，依次将nums中长度为currLen的子序列进行合并排序
    void mSort2(vector<int> &nums, int subseqLen, int numsLen){
        int currLow = 0;
        int currHigh = currLow + 2 * subseqLen - 1;
        for(int i = 0; currHigh < numsLen; i++){
            int m = (currLow + currHigh) / 2;
            Merge(nums, currLow, m, currHigh);
            currLow  = currLow + 2 * subseqLen;
            currHigh = currLow + 2 * subseqLen - 1;
        }

    }

};

int main(){
    vector<int> nums = {5, 2, 1, 3, 4, 6, 4, 7, 8, 9};
    InsertionSort iSort;
    ExchangeSort  eSort;
    SelectionSort sSort;
    MergingSort   mSort;

    iSort.initCount();
    eSort.initCount();
    sSort.initCount();
    mSort.initCount();
    //iSort.sInsertion(nums);
    //iSort.bInsertSort(nums);
    //iSort.p2_InsertSort(nums);
    //iSort.shellSort(nums);

//    eSort.bubbleSort(nums);
//    eSort.quickSort(nums);

//    sSort.sSelectionSort(nums);
//    sSort.heapSort(nums);

    mSort.mergeSort(nums);
    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }
    return 0;
}
