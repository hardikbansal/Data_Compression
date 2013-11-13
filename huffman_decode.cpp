#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
struct node{
    char ch;
    struct node *left;
    struct node *right;
};
typedef struct node node;
node *tree;
node* make_node(){
    node *temp;
    temp=(node*)calloc(1,sizeof(node));
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
void make_tree(int num,char * a){
    node * temp=tree;
    for(int i=0;i<strlen(a);i++){
            if(a[i]=='0'){
                if(temp->left==NULL){
                    temp->left=make_node();
                }
                temp=temp->left;
            }
            if(a[i]=='1'){
                if(temp->right==NULL){
                    temp->right=make_node();
                }
                temp=temp->right;
            }
    }
    temp->ch=(char)num;
}
int main(){
    int numi;
    char ch[256],ch1;
    ifstream fc ("output_code.txt");
    ifstream fi ("output.txt");
	tree=make_node();
    while(!fc.eof()){
        fc>>numi;
        fc>>ch;
        make_tree(numi,ch);
    }
    int length;
	if (fi) {
		fi.seekg (0, fi.end);
		length = fi.tellg();
		fi.seekg (0, fi.beg);
	}
	node *temp=tree;
	bool arr[8];
	int ch2;
	for(int j=0;j<length;j++){
		ch1=fi.get();
		ch2=ch1;
        if(ch1<0) {ch2=ch1+256;}
        for(int i=7;i>=0;i--){
            arr[i]=ch2%2;
            ch2=ch2/2;
        }
	for(int i=0;i<8;i++){
            if(arr[i]==0){
                if(temp->left!=NULL) temp=temp->left;
                else{
                    cout<<temp->ch;
                    temp=tree;
                    i--;
                }
            }
	    else if(arr[i]==1){
                if(temp->right!=NULL) temp=temp->right;
                else{
                    cout<<temp->ch;
                    temp=tree;
                    i--;
                }
            }
        }
	}
}
