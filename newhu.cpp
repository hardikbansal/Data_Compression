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
void print_codes(node *root,int k,ostream& fc){
    char ch2=root->ch;
    if(ch2<0) ch2=ch2+256;
	if(root->right!=NULL){
		arr[k]=0;
		print_codes(root->right,k+1,fc);
	}
	if(root->left!=NULL){
		arr[k]=1;
		print_codes(root->left,k+1,fc);
	}
	if(is_leaf(root)){
		fc<<(int)ch2<<" ";
		for(int i=0;i<k;i++){
			fc<<arr[i];
			code[ch2][i]=arr[i];
		}
        cnt[ch2]=k;
//		cout<<code[root->ch];
		fc<<endl;
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
	ofstream fc ("output_code.txt");
	ifstream fi ("world95.txt",ios::in|ios::binary|ios::ate);
	int length;
	if (fi) {
		fi.seekg (0, fi.end);
		length = fi.tellg();
		fi.seekg (0, fi.beg);
	}
//	fc.open("output.txt");
	char ch,ch2;
	int j=1;
	for(int i=0;i<length;i++){
		ch=fi.get();
		ch2=ch;
        if(ch<0) {ch2=ch+256;}
		if(index[ch2]==0){
			index[ch2]=j;
			ins(j,ch);
			j++;
		}
		else{
			inc(index[ch2]);
		}
	}
	fi.close();
	heap_size=j-1;
	build_min_heap(heap_size);
	build_huffman_tree();
	print_codes(heap+1,0,fc);
	ifstream fn ("world95.txt",ios::in|ios::binary|ios::ate);
	if (fn) {
		fn.seekg (0, fn.end);
		length = fn.tellg();
		fn.seekg (0, fn.beg);
	}
	int k=0,val=0;
	for(int i=0;i<length;i++){
		ch=fn.get();
	//	cout<<ch;
		ch2=ch;
        if(ch<0) {ch2=ch+256;}
        for(int j=0;j<cnt[ch2];j++){
//                cout<<cnt[ch2];
            val=val*2+code[ch2][j];
            k++;
            if(k==8){
                k=0;
                fo<<static_cast<char>(val);
                val=0;
            }
        }
	}
	return 0;
}
