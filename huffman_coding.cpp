#include<iostream>
#include<stack>
#include<vector>
#include<assert.h>
using namespace std;

// 哈夫曼树结点定义
typedef struct {
    char data;
    int weight;
    int parent, left, right;
}HuffTreeNode, *HuffmanTree;



// 返回哈夫曼树前 i 个结点中权值最小和次小的两棵树的根结点序号 s1 和 s2，并创建该俩结点的双亲结点
void select(vector<HuffTreeNode> &hTree, int i, int &s1, int &s2){
    int j, m;
    for(j = 0; j < i && hTree[j].parent != -1; j++);                           // 找到第一个可能的根结点
    s1 = j;
    for(j = s1 + 1; j < i && hTree[j].parent != -1; j++);                      // 找到第二个可能的根结点
    s2 = j;
    if(hTree[s1].weight > hTree[s2].weight){                                   // 若第二个结点的权值小于第一个结点，交换俩结点
        int temp = s1;
        s1 = s2;
        s2 = temp;
    }
    for(m = j + 1; m < i; m++){
        if(hTree[m].parent == -1 && hTree[m].weight < hTree[s1].weight){        // 若还有比 s1 的权值更小的结点，交换 s1、s2和m
            s2 = s1;
            s1 = m;
        }else if(hTree[m].parent == -1 && hTree[m].weight < hTree[s2].weight){  // 若还有只比 s2 的权值小的结点，只需交换 s2 和 m
            s2 = m;
        }
    }
}


// 从根到叶子，求每一个字符的哈夫曼编码
// hTree：建好的哈夫曼树， n : 叶子结点数
void huffmanCodingLeaf(vector<HuffTreeNode> &hTree, int n){
    string str = "";
    string *hCode = new string[n];              // 分配 n 个字符串数组，用于存放每个字符的编码
    assert(hCode != NULL);
    vector<int> nodeStatus(hTree.size(), 0);    // 哈夫曼树中每个结点的状态容器，初始为0，表示左右孩子未被访问过

    int i = hTree.size() - 1;                   // i 指向根结点
    while(i >= 0){
        if(nodeStatus[i] == 0){                 // 当前结点的左右孩子都未被访问过
            nodeStatus[i] = 1;                  // 从左孩子开始，1 表示左孩子已被访问
            if(hTree[i].left > -1){             // 有左孩子
                i = hTree[i].left;
                str += '0';                     // 在尾部添加编码 0
            }else{                              // 没有左孩子，即为叶子结点
                hCode[i] = str;                 // 该字符编码结束，存储该字符的编码
                i = hTree[i].parent;            // 退回该字符的父结点
                str.erase(str.size() - 1, 1);   // 初始化 str
            }
        }else if(nodeStatus[i] == 1){           // 左孩子已访问过，右孩子不曾被访问
            nodeStatus[i] = 2;                  // 左右孩子都被访问过的标志
            i = hTree[i].right;
            str += '1';                         // 串尾追加编码1
        }else{                                  // 左右孩子都被访问过
            i = hTree[i].parent;
            if(i >= 0){                         // 根结点没有父结点，不加此判断会产生访问越界错误
               str.erase(str.size() - 1, 1);    // 初始化字符串
            }
        }

    }
    cout << endl << "-----------------------编码完成---------------------" << endl << endl;
    cout << "每个字符的编码为：" << endl;
    for(int j = 0; j < n; j++){
        cout << hTree[j].data << " : " <<  hCode[j] << endl;
    }
    delete[] hCode;
}


// 创建哈夫曼树 hTree
void createHuffTree(vector<HuffTreeNode> &hTree){
    int n, s1, s2, len;
    char c;     // 字符
    int weight; // 字符权值

    cout << "请输入字符集大小（即叶子数）：" << endl;
    cin >> n;
    len = 2 * n - 1;  // 哈夫曼树的结点数
    hTree.resize(len);
    cout << n << "个字符及其的权值是：(输入格式如：a1 b5 d23，空格分隔)" << endl;
    for(int i = 0; i < n; i++){
        cin >> c >> weight;
        hTree[i].data   = c;
        hTree[i].weight = weight;
        hTree[i].parent = -1;
        hTree[i].left   = -1;
        hTree[i].right  = -1;
    }
    for(int i = n; i < len; i++){
        hTree[i].parent = -1;                                   // vector中的其余结点的双亲域初始化为 -1
    }
    cout << endl << "------------------开始创建哈夫曼树------------------" << endl << endl;
    for(int i = n; i < len; i++){                               // 创建哈夫曼树
        select(hTree, i, s1, s2);                               // 选出当前没有双亲的最小和次小的结点
        hTree[s1].parent = hTree[s2].parent = i;                // 设置当前 i 为选出的结点的双亲结点
        hTree[i].left    = s1;                                  // 设置结点 i 的左右孩子
        hTree[i].right   = s2;
        hTree[i].weight  = hTree[s1].weight + hTree[s2].weight; // 双亲结点的权值为两孩子结点权值之和
    }
    cout << "------------------哈夫曼树创建完成------------------" << endl;
    cout << endl << "-----------------------开始编码---------------------" << endl;
    huffmanCodingLeaf(hTree, n);
}





int main(){
    vector<HuffTreeNode> hTree;
    createHuffTree(hTree);   // 创建哈夫曼树，并进行编码 a5 b29 c7 d8 f14 g23 h3 y11

    return 0;
}
