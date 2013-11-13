#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
struct node{
	struct node *left;
	struct node *right;
	int weight;
	char ch;
};
typedef struct node node;
node heap[256];
void ins(int i,char ch){
	heap[i].weight=1;
	heap[i].ch=ch;
	heap[i].left=NULL;
	heap[i].right=NULL;
}
void inc(int i){
	heap[i].weight++;
}
bool is_leaf(node * nod){
	if(nod->left==NULL && nod->right==NULL)
		return 1;
	else return 0;
}
int heap_size,index[256];
void exchange(int i,int j)
{
	node temp;
	temp=heap[j];
	heap[j]=heap[i];
	heap[i]=temp;
}
void min_heapify(int i){
	int l = 2*i;
	int r = 2*i+1;
	int min;
	if(l<=heap_size&&heap[l].weight<heap[i].weight)
		min=l;
	else min=i;
	if(r<=heap_size&&heap[r].weight<heap[min].weight)
		min=r;
	if(min!=i){
		exchange(i,min);
		min_heapify(min);
	}
}
void build_min_heap(int len){
	for(int i=len/2;i>0;i--){
		min_heapify(i);
	}
}
bool arr[100];
bool code[256][256];
int cnt[256];
void print_codes(node *root,int k){
	if(root->right!=NULL){
		arr[k]=0;
		print_codes(root->right,k+1);
	}
	if(root->left!=NULL){
		arr[k]=1;
		print_codes(root->left,k+1);
	}
	if(is_leaf(root)){
		cout<<root->ch<<" ";
		for(int i=0;i<k;i++){
			cout<<arr[i];
			code[root->ch][i]=arr[i];
		}
        cnt[root->ch]=k;
//		cout<<code[root->ch];
		cout<<endl;
	}
}
void heap_ins(int weight){
	heap_size++;
	int i=heap_size;
	node temp=heap[heap_size];
	while(i!=1 && weight<heap[i/2].weight){
		heap[i]=heap[i/2];
		i=i/2;
	}
	heap[i]=temp;
}
void extract_min(){
	exchange(1,heap_size);
	heap_size=heap_size-1;
	min_heapify(1);
}
node temp[100][2];
void build_huffman_tree(){
	int k=heap_size;
	for(int i=0;i<100&&heap_size!=1;i++){
		extract_min(),extract_min();
		temp[i][0]=heap[heap_size+1],temp[i][1]=heap[heap_size+2];
		heap[heap_size+1].weight=temp[i][0].weight+temp[i][1].weight;
		heap[heap_size+1].left=temp[i];
		heap[heap_size+1].right=temp[i]+1;
		heap_ins(heap[heap_size+1].weight);
	}
}
int main(){
	ofstream fo ("output.txt");
	ifstream fi ("input1.txt",ios::in|ios::binary|ios::ate);
	int length;
	if (fi) {
		fi.seekg (0, fi.end);
		length = fi.tellg();
		fi.seekg (0, fi.beg);
	}
//	fc.open("output.txt");
	char ch;
	int j=1;
	for(int i=0;i<length-1;i++){
		ch=fi.get();
	//	cout<<ch-'a';
		if(index[ch]==0){
			index[ch]=j;
			ins(j,ch);
			j++;
		}
		else{
			inc(index[ch]);
		}
	}
	fi.close();
	heap_size=j-1;
	build_min_heap(heap_size);
	build_huffman_tree();
	print_codes(heap+1,0);
	ifstream fn ("input1.txt",ios::in|ios::binary|ios::ate);
	if (fn) {
		fn.seekg (0, fn.end);
		length = fn.tellg();
		fn.seekg (0, fn.beg);
	}
	int k=0,val=0;
/*	for(int i=0;i<length-1;i++){
		ch=fn.get();
        for(int j=0;j<cnt[ch];j++){
            val=val*2+code[ch][j];
            k++;
            if(k==7){
                k=0;
     //           cout<<val<<endl;
                fo<<static_cast<char>(val);
                val=0;
            }
        }
	}
*/
    char ch1 =static_cast<char>(254);
    cout<<(int)ch1;
	return 0;
}
