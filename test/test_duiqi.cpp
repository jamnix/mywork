#include <iostream>
using namespace std;
//#pragma pack(4)    //ÉÖ4×½ڶÔë/#pragma pack()     //ȡÏ4×½ڶÔë
typedef struct node
{
     
}S;
 
typedef struct node1
{
    int a;
    char b;
    short c;
}S1;
 
typedef struct node2
{
    char a;
    int b;
    short c;
}S2;
 
typedef struct node3
{
    int a;
    short b;
    static int c;
}S3;
 
typedef struct node4
{
    bool a;
    S1 s1;
    short b;
}S4;
 
typedef struct node5
{
    bool a;
    S1 s1;
    double b;
    int c;
}S5;
 
 
 
int main(int argc, char *argv[])
{
    cout<<sizeof(char)<<" "<<sizeof(short)<<" "<<sizeof(int)<<" "<<sizeof(float)<<" "<<sizeof(double)<<endl;
    S s;
    S1 s1;
    S2 s2;
    S3 s3;
    S4 s4;
    S5 s5;
    cout<<sizeof(S3)<<endl;
    cout<<sizeof(s)<<" "<<sizeof(s1)<<" "<<sizeof(s2)<<" "<<sizeof(s3)<<" "<<sizeof(s4)<<" "<<sizeof(s5)<<endl;
    return 0;
}
