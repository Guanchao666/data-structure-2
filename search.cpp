#include<iostream>
#include<vector>

using namespace std;

/* ----------------------------- 1. 折半查找法（二分查找法） ---------------------*/
// 在 nums 中寻找 target，若找到，返回目标所在的下标，否则返回 -1
int binarySearch(vector<int> nums, int target){
    int len = nums.size();
    int low = 0;
    int high = len - 1;
    int mid;
    while(low <= high){
        mid = (low + high) / 2;   // 若 nums 中元素的值分布均匀，使用改进的插值查找法 mid = low + (target - nums[low]) / (nums[high] - nums[low]) * (high - low)
        if(target < nums[mid]){
            high = mid - 1;
        }else if(target > nums[mid]){
            low = mid + 1;
        }else{
            return mid;
        }
    }
    return -1;
}

// 二叉树结点结构的定义
typedef struct BiTNode{
    int data;
    BiTNode *lchild, *rchild;
    BiTNode(int n = 0) : data(n), lchild(nullptr), rchild(nullptr){}
}BiTNode, *BiTree;

/* ----------------------------- 2. 二叉排序树（二叉搜索树） ---------------------*/
class BSTree{
public:
    // 二叉排序树的查找操作，递归查找二叉排序树 T 中是否存在 key
    // parent 指向 T 的双亲
    // p 指向查找成功的结点或指向查找路径上访问的最后一个结点。
    bool searchBST(BiTree T, int key, BiTNode *parent, BiTNode **p){
        if(!T){                    // 树遍历结束都没有找到 key， 查找失败。
            *p = parent;
            return false;
        }else if(key == T->data){  // 查找成功
            *p = T;
            return true;
        }else if(key < T->data){
            return searchBST(T->lchild, key, T, p);
        }else{
            return searchBST(T->rchild, key, T, p);
        }
    }

    // 二叉排序树的插入操作1，使用 searchBST 实现
    // 当二叉排序树 T 中不存在关键字等于 key 的元素时插入 key 并返回 true，否则返回 false
    bool insertBST(BiTree *T, int key){
        BiTNode *p;
        if(!searchBST(*T, key, NULL, &p)){  // 若 key 不存在树中，则插入
            BiTNode *new_node = new BiTNode(key);
            if(!p){                         // 树为空，则 T 应为根结点
                *T = new_node;
            }else if(key < p->data){        // 插入左子树
                p->lchild = new_node;
            }else{                          // 插入右子树
                p->rchild = new_node;
            }
            return true;
        }else{
            return false;

        }
    }

    // 二叉排序树的插入操作2，使用递归实现
    // 当二叉排序树 T 中不存在关键字等于 key 的元素时插入 key 并返回 true，否则返回 false
    bool insertBST2(BiTree *T, int key){
        if(!(*T)){
            BiTNode *new_node = new BiTNode(key);
            *T = new_node;
            return true;
        }else if(key < (*T)->data){         // 插入左子树
            insertBST2( &(*T)->lchild, key);
        }else if(key > (*T)->data){         // 插入右子树
            insertBST2( &(*T)->rchild, key);
        }else{                              // 存在相同元素
            return false;
        }
    }

    // 二叉排序树的删除操作
    // 递归查找，若二叉排序树中存在与 key 值相等的结点，则将其删除并返回 true ，否则返回 false;
    bool deleteBST(BiTree *T, int key){
        if(!*T){
            return false;
        }else{
            if( (*T)->data == key){                     // 若当前结点值和 key 相等，则删除
                return deleteNode(T);
            }else if(key < (*T)->data){
                return deleteBST(&(*T)->lchild, key);   // 查找左子树
            }else{
                return deleteBST(&(*T)->rchild, key);   // 查找右子树
            }
        }
    }
    // 从二叉排序树中删除 p 结点，并重接它的左右子树
    // 使用方法2，用 s 结点的值替代 p 结点的值，再将 s 结点删除，原 s 结点的左子树改为 s 的父结点 q 的右子树。
    bool deleteNode(BiTree *p){
        BiTree q, s;
        if((*p)->lchild == nullptr){        // 只有右子树的时候，直接重连右子树
            q = *p;
            *p = (*p)->rchild;
            delete(q);
        }else if((*p)->rchild == nullptr){  // 只有左子树的时候，直接重连左子树
            q = *p;
            *p = (*p)->lchild;
            delete(q);
        }else{                              // 左右子树都不为空
            q = *p;
            s = (*p)->lchild;
            while(s->rchild){               // 转左，并向右走到尽头（即找到待删结点的前驱）
                q = s;
                s = s->rchild;
            }
            (*p)->data = s->data;           // 用 s 结点的值替代 p 结点的值
            if(q != *p){
                q->rchild = s->lchild;
            }else{
                q->lchild = s->lchild;
            }
            delete(s);
        }
    }


    // 二叉树的中序遍历
    void midReverse(BiTree T){
        if(!T){
            return;
        }else{
            midReverse(T->lchild);
            cout << T->data << endl;
            midReverse(T->rchild);
        }
    }

};

int main(){
    vector<int> nums = {61, 88, 58, 47, 35, 73, 51, 99, 37, 94};
    BiTree T = nullptr;
    BSTree bst;
    for(int i = 0; i < nums.size(); i++){
        cout << bst.insertBST2(&T, nums[i]) << endl;
    }
    cout << bst.deleteBST(&T, 35) << endl;
    bst.midReverse(T);
    return 0;
}
