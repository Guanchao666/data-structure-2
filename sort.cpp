#include<iostream>
#include<vector>

using namespace std;

/* ----------------------------- 1. 插入排序类 ---------------------*/
class InsertionSort {
public:

    // 直接插入排序法，对容器 nums 进行排序
    void sInsertion(vector<int> &nums) {
        int len = nums.size();

        for(int i = 1; i < len; i++) {              // 以第一个数（nums[0]）为已排好序的部分，将之后的记录进行插入
            if(nums[i] < nums[i - 1]) {
                int temp = nums[i];                 // 临时变量，用于存储 nums[i]
                int j = i - 2;
                nums[i]  = nums[i - 1];

                while(j >= 0 && temp < nums[j]) {   // 从后往前，寻找 temp 应插入的位置
                    nums[j + 1] = nums[j];          // 记录后移
                    j--;
                }
                nums[j + 1] = temp;                 // 插入正确的位置
            }
        }
    }

    // 折半插入排序法，对容器 nums 进行排序
    void bInsertSort(vector<int> &nums) {
        int len = nums.size();

        for(int i = 1; i < len; i++) {
            int temp = nums[i];
            int low = 0, high = i - 1;          // nums[0 ~ i - 1] 为有序部分

            while(low <= high) {                // 寻找 0 ~ i-1 中， nums[i]应插入的位置
                int m = (low + high) / 2;
                if(nums[m] > temp) {            // 插入位置在低半区
                    high = m - 1;
                } else {
                    low  = m + 1;               // 插入位置在高半区
                }
            }

            for(int j = i - 1; j >= low; j--) { // 记录后移，插入位置为 high+1 或 low
                nums[j + 1] = nums[j];
            }
            nums[low] = temp;                   // 插入
        }
    }

    // 二路插入排序法，对容器 nums 进行排序
    void p2_InsertSort(vector<int> &nums) {
        int len = nums.size();
        int i, j, first, last, mid;
        vector<int> d;
        d.resize(len);          // 生成 len 个记录的临时空间
        d[0] = nums[0];
        first = last = 0;       // first和last分别指示 d 中排好序的记录的第一个和最后一个位置

        for(i = 1; i < len; i++) {
            if(first > last) {
                j = len;        // j 是调整系数
            } else {
                j = 0;
            }
            mid = ( (first + last + j) / 2 ) % len;  // d 的中间记录的位置
            if(nums[i] < d[mid]) {                   // -- 待插记录应插在 d 的前半部分
                j = first;                           // j 指向 d 的第一个记录
                first = (first - 1 + len) % len;     // first 前移。取余是为了实现循环数组效果
                while(nums[i] > d[j]) {              // 待插记录大于 j 所指记录
                    d[(j - 1 + len) % len] = d[j];   // j 所指记录前移。取余是为了实现循环数组效果
                    j = (j + 1) % len;               // j 指向下一个记录
                }
                d[(j - 1 + len) % len] = nums[i];    // 移动结束，待插记录插在[j]前
            } else {                                  // -- 待插记录应插在 d 的后半部分
                j = last;                            // j 指向当前的最后一个记录
                last++;                              // last后移，指向插入后的最后一个记录
                while(nums[i] < d[j]) {              // 待插记录小于 j 所指记录
                    d[(j + 1 ) % len] = d[j];        // j 所指记录后移
                    j = (j - 1 + len) % len;         // j 指向上一个记录
                }
                d[(j + 1) % len] = nums[i];          // 待插记录不小于 j 所指记录，插在 j 后
            }// end else
        }// end for
        for(i = 0; i < len; i++) {                   // 把在 d 中排好序的记录依次赋给nums
            nums[i] = d[(first + i) % len];
        }
    }


    // 希尔排序法，对容器 nums 进行排序
    void shellSort(vector<int> &nums) {
        int len = nums.size();
        int gap = len;              // 增量，初始设为len

        do {
            gap = gap / 3 + 1;      // 计算增量，形成增量序列
            for(int i = gap ; i < len; ++i) {
                if(nums[i] < nums[i - gap]) {            // 当 nums[i] 小于当前增量序列的前一个记录时
                    int temp = nums[i];                  // 暂存 nums[i] ，确定其该插入的位置后再插入
                    int j = i - gap;                     // 从当前增量序列的前一个记录开始遍历
                    while(j >= 0 && temp < nums[j]) {    // 继续与前面的其他记录相比较（相距同一增量的其他记录），确定nums[i]应插入（交换）的位置
                        nums[j + gap] = nums[j];         // 大的记录后移
                        j -= gap;
                    }
                    nums[j + gap] = temp;                // 插入
                }
            }
        } while(gap > 1);
    }
};


/*  ----------------------------- 2. 交换排序类 ----------------------------  */
class ExchangeSort {
public:

    // 冒泡排序法，对容器nums进行排序
    void bubbleSort(vector<int> &nums) {
        int len = nums.size();
        bool isChange = true;       // 是否有记录交换的标志位，防止后面的记录已经是有序的还执行循环
        for(int i = 0; i < len - 1 && isChange; i++) {
            isChange = false;
            for(int j = i + 1; j < len; j++) {  // 遍历 nums[i]之后的记录
                if(nums[j] < nums[i]) {         // 存在小于 numsp[i] 的记录时，交换两记录
                    swap(nums[i], nums[j]);
                    isChange = true;
                }
            }
        }
    }


    // --- 快速排序法的划分函数，对数组或集合 nums 进行划分，并返回枢轴所在位置。已优化不必要的交换（枢轴的交换）
    int partition(vector<int> &nums, int low, int high) {
        int len = nums.size();
        int pivot;             // 存储枢轴的值
        pivot = nums[low];     // 确定枢轴的值，需优化（使用三数取中或其他方法）

        while(low < high) {
            while(low < high && nums[high] >= pivot) {
                high--;
            }
            nums[low] = nums[high];   // 将右端小于枢轴的记录放入左端

            while(low < high && nums[low] <= pivot) {
                low++;
            }
            nums[high] = nums[low];   // 将左端大于枢轴的记录放入右端
        }
        nums[low] = pivot;            // 放入枢轴的值
        return low;                   // 返回枢轴所在位置
    }

    // -- 快速排序法，对容器 nums 中 [low, high] 之间的记录进行快速排序
    void qSort(vector<int> &nums, int low, int high) {
        int pivotkey;   // 枢轴的位置
        if(low < high) {
            pivotkey = partition(nums, low, high);
            qSort(nums, low, pivotkey - 1);
            qSort(nums, pivotkey + 1, high);
        }

    }

    // - 快速排序法的包装函数，对容器nums进行排序
    void quickSort(vector<int> &nums) {
        int len = nums.size();
        qSort(nums, 0, len);
    }

};


/* ----------------------------- 3. 选择排序类 --------------------  */
class SelectionSort {
public:

    // 简单选择排序法，对容器nums进行排序
    void sSelectionSort(vector<int> &nums) {
        int len = nums.size();
        for(int i = 0; i < len - 1; i++) {
            int currMinIndex = i;                 // 最小记录的下标
            for(int j = i + 1; j < len; j++ ) {
                if(nums[j] < nums[currMinIndex]) {
                    currMinIndex = j;
                }
            }
            swap(nums[i], nums[currMinIndex]);    // 将最小记录与当前记录nums[i]进行交换。
        }
    }



    // 堆排序法，对容器 nums 进行排序
    void heapSort(vector<int> &nums) {
        int len = nums.size();
        int i;
        for(i = len / 2 - 1; i >= 0; i--) {                     // 从最后一个非叶子子结点到[0]，即 0 ~ [len/2 - 1] 都是非叶子结点。将这些分叶子结点看成子树(子堆)，分别进行调整
            heapAdjust(nums, i, len - 1);                       // 调整 nums[i]，nums[i ~ len-1] 成为大顶堆
        }

        for(i = len - 1; i > 0; i--) {                          // -- 大顶堆创建完成，开始排序。排序过程为从后往前排，不断将大顶堆的顶部记录放到容器后面，然后调整前面的记录保持为大顶堆。
            swap(nums[0], nums[i]);                             // 交换堆顶记录[0]和未完全排序的nums[1 ~ i]中的最后一个记录[i]
            heapAdjust(nums, 0, i - 1);                         // 调整 nums[0]，使 num[0 ~ i-1]重新成为大顶堆
        }
    }
    // 堆排序法的堆调整函数，已知 nums[low ~ high] 中的记录除 nums[low]之外均满足大顶堆的定义，
    // 向下调整 nums[low]， 使 nums[low ~ high] 中记录均满足大顶堆的定义
    void heapAdjust(vector<int> &nums, int low, int high) {
        int temp = nums[low];                                    // 利用临时变量存储待调整数据
        for(int j = 2 * low + 1; j <= high; j = 2 * j + 1) {     // j 指向 nums[low] 的左孩子，沿值较大的孩子结点向下筛选(因为下标从0开始，所以结点i的左孩子为2i+1)
            // 该 for 循环的目的是找到以当前 nums[low] 为根结点的子树(子堆)中的最大值，再将此最大值和 nums[low]交换。
            if( j < high && nums[j] < nums[j + 1]) {             // 左孩子小于右孩子
                j++;                                            // j 为值较大的记录的下标，即 j 指向[low]的右孩子
            }
            if(temp >= nums[j]) {                                // nums[low]的值大于或等于左右子树的值
                break;                                          // 不必再调整，跳出for循环
            }
            nums[low] = nums[j];                                 // 否则，nums[j]为当前最大值，将它上移插入nums[low]的当前位置
            low = j;                                             // 同时 nums[low] 下移到 nums[j] 处，因为还需将它与剩下的结点作比较。
        }
        nums[low] = temp;                                        // 最终找到 temp 应插入的位置，将其插入nums[low]
    }



};



/* ----------------------------- 4. 归并排序类 --------------------  */
class MergingSort {
public:

    // --------- 递归实现部分 start
    // 2路归并排序法的包装函数，对容器 nums 进行排序，递归法
    void mergeSort(vector<int> &nums) {
        int len = nums.size();
        mSort(nums, 0, len - 1);   // 将无序的nums[0 ~ len-1] 归并排序为有序
    }

    // 2路归并排序法，对 nums[low ~ high] 进行归并排序，递归实现
    void mSort(vector<int> &nums, int low, int high) {
        if(low < high) {                    // 有不只一个元素待归并
            int m = (low + high) / 2;
            mSort(nums, low, m);            // 递归将nums[low ~ m]归并为有序的 nums[low ~ m]
            mSort(nums, m + 1, high);       // 递归将nums[m+1 ~ high]归并为有序的 nums[m+1 ~ high]
            Merge(nums, low, m, high);      // 将有序的 nums[low ~ m] 和 nums[m+1 ~ high] 归并到 nums[low ~ high]
        }
    }
    // --------- 递归实现部分 end


    // --------- 迭代实现部分 start
    // 2路归并排序法的包装函数，对容器 nums 进行排序，迭代法
    void mergeSort2(vector<int> &nums) {
        int len = nums.size();
        int currLen = 1;                    // 归并长度从 1 开始，迭代增加
        while( currLen < len) {
            mSort2(nums, currLen, len);     // 分别对数组 nums 中长度为 1、2、4、8……的子序列进行归并排序
            currLen *= 2;
        }
    }

    // 2路归并排序法，依次将 nums 中长度为 subseqLen 的子序列进行归并排序。迭代实现
    // subseqLen：子序列长度， numsLen：数组长度
    void mSort2(vector<int> &nums, int subseqLen, int numsLen) {
        int currLow = 0;
        int currHigh = currLow + 2 * subseqLen - 1;
        while( currHigh < numsLen) {
            int m = (currLow + currHigh) / 2;
            Merge(nums, currLow, m, currHigh);
            currLow  = currLow + 2 * subseqLen;
            currHigh = currLow + 2 * subseqLen - 1;
        }
        if(currLow < numsLen - subseqLen + 1) {   // 若有剩下的单独子序列在最后，将最后两个子序列进行归并排序，防止漏掉
            Merge(nums, currLow, currLow + subseqLen - 1, numsLen - 1);
        }
    }
    // --------- 迭代实现部分 end


    // --------- 归并排序递归法和迭代法共有的合并函数
    // 2路归并排序法的合并函数，将有序的 nums[low ~ m] 与 nums[m+1 ~ high] 合并为有序的 nums[low ~ high]
    void Merge(vector<int> &nums, int low, int m, int high) {
        int len = nums.size();
        vector<int> temp;             // 临时容器，用于暂存排好序的记录
        temp.resize(len);             // 设置临时容器大小
        int i = low;                  // nums[low ~ m] 范围内的下标
        int j = m + 1;                // nums[m+1 ~ high] 范围内的下标
        int k = low;                  // temp[low ~ high]的下标
        while(i <= m && j <= high) {
            if(nums[i] < nums[j]) {
                temp[k] = nums[i++];
            } else {
                temp[k] = nums[j++];
            }
            k++;
        }

        while(i <= m) {                // 若temp[low ~ m] 还剩下数据，直接放到temp之后
            temp[k++] = nums[i++];
        }

        while(j <= high) {             // 若temp[m+1 ~ high] 还剩下数据，直接放到temp之后
            temp[k++] = nums[j++];
        }

        for(i = low; i <= high; i++) { // 将归并好的记录放回 nums
            nums[i] = temp[i];
        }
    }

};

int main() {
    vector<int> nums = {5, 2, 1, 3, 4, 6, 4, 7, 8, 9, 0, 8};
    InsertionSort iSort;
    ExchangeSort  eSort;
    SelectionSort sSort;
    MergingSort   mSort;


    //iSort.sInsertion(nums);
    iSort.bInsertSort(nums);
    //iSort.p2_InsertSort(nums);
    //iSort.shellSort(nums);

//    eSort.bubbleSort(nums);
//    eSort.quickSort(nums);

//    sSort.sSelectionSort(nums);
//    sSort.heapSort(nums);

//   mSort.mergeSort(nums);
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}
