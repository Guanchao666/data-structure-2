#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

// ——————————串的定长顺序存储表示————————————————
#define MAXSTRLEN 255     //最大串长
typedef char SString[MAXSTRLEN+1];


/*  *******************模式匹配算法1*************************  */
/*
 * 求子串位置的定位函数, 朴素模式匹配算法/简单匹配算法（Brute-Force算法，简称BF算法）
 * s : 主串
 * t : 子串，也称模式串
 * pos : 开始匹配的位置
 * return : 子串t在主串s中第pos个字符之后的位置。若不存则返回0
 *
 * 时间复杂度：设主串长n； 子串长m。
 * 可能匹配成功的位置（1 ~ n-m+1)，最坏情况下的平均时间复杂度为O(n*m)。
 *
 */
// C语言实现
int index(SString s, SString t, int pos){
    // t非空， 1 <= pos <= strlen(s)
    int i = pos;
    int j = 0;
    int sLen = strlen(s);
    int tLen = strlen(t);
    while(i < sLen && j < tLen){
        if(s[i] == t[j]){
            i++;
            j++;
        }else{
            i = i - j + 2;
            j = 1;
        }
    }
    if(j >= tLen){
        return i - tLen;
    }else{
        return 0;
    }
}

// C++实现
int index2(string s, string t, int pos){
    // t非空， 1 <= pos <= Strlength(s)
    int i = pos;
    int j = 0;
    int sLen = s.length();
    int tLen = t.length();
    while(i < sLen && j < tLen){ // s[0]、t[0]为串长度
        if(s[i] == t[j]){
            i++;
            j++;
        }else{
            i = i - j + 2;
            j = 1;
        }
    }
    if(j >= tLen){
        return i - tLen;
    }else{
        return 0;
    }
}



/*  *******************模式匹配算法2*************************  */
/*
 * 求子串位置的定位函数, KMP算法
 * s : 主串
 * t : 子串，也称模式串
 * pos : 开始匹配的位置
 * return : 子串t在主串s中第pos个字符之后的位置。若不存则返回0
 *
 * 时间复杂度：设主串长n； 子串(模式串)长m。
 * 算法中求next数组的时间复杂度为O(m),在后面的匹配中因主串s的下标不减即不回溯,比较次数可记为n,所以KMP算法总的时间复杂度为O(n+m)
 */

 /*  ----------------c语言实现start----------------------  */
// 生成next数组，C语言实现
void getNext(int next[], SString t, int pos){
    int i = pos;
    int j = -1;
    int tLen = strlen(t);
    next[0] = -1;
    while( i < tLen-1){
        if( j < 0 || t[i] == t[j]){ // 初始或匹配
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}
// 生成next数组的改进算法，若模式串中相同的子串较多，可以使用此方法，可提高匹配效率。C语言实现
void getNextImprov(int next[], SString t, int pos ){
    int i = pos;
    int j = -1;
    int tLen = strlen(t);
    next[0] = -1;
    while( i < tLen-1){
        if( j < 0 || t[i] == t[j]){ // 初始或匹配
            i++;
            j++;
            if(t[i] != t[j]){  //改进之处
                next[i] = j;
            }else{
                next[i] = next[j];
            }
        }else{
            j = next[j];
        }
    }
}
 // KMP，C语言实现
int indexKMP(SString s, SString t, int pos){
    int i = pos;
    int j = 0;
    int sLen = strlen(s);
    int tLen = strlen(t);
    int next[tLen] = {0};
    //getNext(next, t, pos);
    getNextImprov(next, t, pos); // 使用改进的算法求next数组，根据需要选择
    for(int x=0; x<tLen; x++){
        cout << next[x] << endl;
    }
    while(i < sLen && j < tLen){
        if(j < 0 || s[i] == t[j]){ // 若匹配，或t已移出最左侧
            i++;
            j++;
        }else{
            j = next[j]; // 和BF算法的区别在此
        }
    }
    if(j >= tLen){
        return i - tLen;
    }else{
        return 0;
    }
}
 /*  ----------------c语言实现end----------------------  */


 /*  ----------------c++实现start----------------------  */
// 生成next数组，C++实现
void getNext2(vector<int> &next, string t, int pos){
    int i = pos;
    int j = -1;
    int tLen = t.length();
    next[0] = -1;
    while( i < tLen-1){
        if( j < 0 || t[i] == t[j]){ // 初始或匹配
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}
// 生成next数组的改进算法，若模式串中相同的子串较多，可以使用此方法，可提高匹配效率。 C++实现
void getNextImprov2(vector<int> &next, string t, int pos ){
    int i = pos;
    int j = -1;
    int tLen = t.length();
    next[0] = -1;
    while( i < tLen){
        if( j < 0 || t[i] == t[j]){ // 初始或匹配
            i++;
            j++;
            if(t[i] != t[j]){    //改进之处
                next[i] = j;
            }else{
                next[i] = next[j];
            }
        }else{
            j = next[j];
        }
    }
}
// KMP，C++实现
int indexKMP2(string s, string t, int pos){
    int i = pos;
    int j = 0;
    int sLen = s.length();
    int tLen = t.length();
    vector<int> next(tLen);
//    getNext2(next, t, pos);
    getNextImprov2(next, t, pos); // 使用改进的算法求next数组，根据需要选择

    while(i < sLen && j < tLen){
        if(j < 0 || s[i] == t[j]){ // 若匹配，或t已移出最左侧
            i++;
            j++;
        }else{
            j = next[j]; // 和BF算法的区别在此
        }
    }
    if(j >= tLen){
        return i - tLen;
    }else{
        return 0;
    }
}
 /*  ----------------c++实现end----------------------  */


int main(){
    SString s1 = "ababcabcacbab";
    SString t1 = "aaaab";  //"abcac";//"abaabcac";
    string s2 = "ababcabcacbab";
    string t2 = "abcac";
    cout << indexKMP(s1, t1, 0) << endl;
    //cout << indexKMP2(s2, t2, 0) << endl;
    return 0;
}

