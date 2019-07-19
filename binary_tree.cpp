#include<iostream>
#include<stack>
using namespace std;
typedef struct BiTreeNode{
    char data;
    BiTreeNode *left;
    BiTreeNode *right;
    BiTreeNode(char c) : data(c), left(NULL), right(NULL) {}
}BiTreeNode, *BiTree;

// 按照前序顺序建立二叉树， c++
void createBiTree(BiTree &t){
    char c;
    cin >> c;
    if(c == '.'){           // 当遇到'.'时，令该节点为NULL，从而结束该分支的递归
        t = NULL;
    }else{
        t = new BiTreeNode(c);
        createBiTree(t->left);
        createBiTree(t->right);
    }
}

// 按照前序顺序建立二叉树， c
void createBiTree2(BiTree &root){
	char c;
	scanf("%c", &c);
	if(c =='.'){            // 当遇到'.'时，令该节点为NULL，从而结束该分支的递归
		root = NULL;
	}
	else{
		root = (BiTreeNode *)malloc(sizeof(BiTreeNode));
		root->data = c;
		createBiTree2(root->left);
		createBiTree2(root->right);
	}
}

// 先序遍历二叉树，递归算法
void preOrderTraverse(BiTree root){
    if(root != NULL){
        cout << root->data << ' ';       // 访问根结点
        preOrderTraverse(root->left);    // 先序遍历根的左子树
        preOrderTraverse(root->right);   // 先序遍历根的右子树
    }
}

// 先序遍历二叉树，非递归算法，迭代实现
void preOrderTraverse2(BiTree root){
    stack<BiTreeNode *> s;               // 存储二叉树结点的栈
    BiTreeNode *t  = root;
    s.push(NULL);                        // 先压入一个空指针作为标记
    while(t != NULL){
        cout << t->data << ' ';          // 访问当前节点
        if(t->right != NULL){            // 先把右孩子压入栈（先处理左子树）
            s.push(t->right);
        }
        if(t->left != NULL){
            t = t->left;                 // t 指向其左孩子
        }else{                           // 左孩子为空
            t = s.top();                 // 获得栈顶元素即右孩子指针
            s.pop();
        }
    }
}


// 中序遍历二叉树，递归算法
void inOrderTraverse(BiTree root){
    if(root != NULL){
        inOrderTraverse(root->left);     // 中序遍历根的左子树
        cout << root->data << ' ';       // 访问根结点
        inOrderTraverse(root->right);    // 中序遍历根的右子树
    }
}

// 中序遍历二叉树，非递归算法，迭代实现
void inOrderTraverse2(BiTree root){
    stack<BiTreeNode *> s;               // 存储二叉树结点的栈
    BiTreeNode *t  = root;

    while(t != NULL || !s.empty()){
        if(t != NULL){
            s.push(t);                   // 将 t 压入栈，先访问其左子树
            t = t->left;
        }else{                           // 若 t 为空
            t = s.top();                 // 取出 栈顶元素，即树或子树的根结点
            s.pop();
            cout << t->data << ' ';      // 访问当前结点
            t = t->right;                // 指向其右孩子
        }
    }
}


// 后序遍历二叉树递归算法
void postOrderTraverse(BiTree root){
    if(root != NULL){
        postOrderTraverse(root->left);    // 后序遍历根的左子树
        postOrderTraverse(root->right);   // 后序遍历根的右子树
        cout << root->data << ' ';        // 访问根结点
    }
}

// 后序遍历非递归算法需要使用的结构体
enum Tags {Left, Right};                  // 枚举类型标志位，stackNode使用
typedef struct {
    BiTreeNode *p;                        // 结点指针
    Tags flag;                            // 标志位
}stackNode;

// 后序遍历二叉树，非递归算法，迭代实现
void postOrderTraverse2(BiTree root){
    stack<stackNode > s;                  // 存储二叉树结点的栈
    stackNode sNode;                      // 栈元素
    BiTreeNode *t  = root;

    while(t != NULL || !s.empty()){
        while(t != NULL){                 // t 非空，入栈根结点，继续向左，找到最左的根结点的左孩子（空指针）
            sNode.p = t;
            sNode.flag = Left;            // 设置标志位为 Left，表示其出栈时已访问过左子树
            s.push(sNode);
            t = t->left;
        }
        sNode = s.top();
        s.pop();
        t = sNode.p;
        if(sNode.flag == Left){           // 已访问过左子树
            sNode.flag = Right;           // 标志位设为 Right，表示其出栈时已访问过左子树
            s.push(sNode);
            t = t->right;
        }else{                            // 已访问过右子树
            cout << t->data << ' ';
            t = NULL;                     // 设置 t 为空，以便继续出栈
        }
    }
}


// 销毁 t 所指二叉树或子树
void destroyBiTree(BiTree t){
    if(t != NULL){
        destroyBiTree(t->left);           // 递归销毁左子树
        destroyBiTree(t->right);          // 递归销毁右子树
        delete t;                         // 释放 t 所指结点
        t = NULL;
    }
}

int main(){
    BiTree root;
    createBiTree(root);  // ABD..EG...C.F..     AB.DF..G..C.E.H..
    cout << "创建二叉树完成" << endl;
    cout << endl << "先序遍历：" << endl;
    preOrderTraverse2(root);
    cout << endl << "中序遍历：" << endl;
    inOrderTraverse2(root);
    cout << endl << "后序遍历：" << endl;
    postOrderTraverse2(root);
    return 0;
}
