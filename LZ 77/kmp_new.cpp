#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
char input[3000000];
ifstream::pos_type size;
char * memblock;
int *compute_prefix_function(char *pattern, int psize)
{
	int k = -1;
	int i = 1;
	int*pi = (int*)calloc(psize,sizeof(int));
	if (!pi)
		return NULL;

	pi[0] = k;
	for (i = 1; i < psize; i++) {
		while (k > -1 && pattern[k+1] != pattern[i])
			k = pi[k];
		if (pattern[i] == pattern[k+1])
			k++;
		pi[i] = k;
	}
	return pi;
}
int kmp(char* target, int tsize, char *pattern, int psize,int *len2)
{
	int i;
	int *pi = compute_prefix_function(pattern, psize);
	int k = -1;
	int max=-1;
	int ans=-1;
	if (!pi)
		return -1;
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			free(pi);
			*len2=psize;
			return i-k;
		}
		if(k>max){
			max=k;
			ans=i-k;
		}
	}
	free(pi);
	*len2=max;
	return ans;
}
int main(int argc, const char *argv[])
{
	ifstream fi ("input.txt",ios::in|ios::binary|ios::ate);

	int length;
	if (fi) {
		fi.seekg (0, fi.end);
		length = fi.tellg();
		fi.seekg (0, fi.beg);
		//		cout<<length;
//		length=min(length,100000);
		fi.read (input,length);
	}
	ofstream fo;
	char line[50];
	fo.open("output.txt");
	int len1=strlen(input),point1=0,point2=0,mat=-1,len2=1;
	int i;
	for(i=1;i<min(4096,len1);i++){
		mat=kmp(input,i,input+i,min(100,(int)strlen(input+i)),&len2);
		if(len2>=9){
			fo<<"{"<<i-mat<<","<<len2<<"}";
			i+=len2-1;
		} else fo<<input[i];
	}
//	cout<<input;
	printf("%d",i);
	for(;i<length;i++){
		mat=kmp(input+i-4096,4096,input+i,min(100,(int)strlen(input+i)),&len2);
		if(len2>=9){
			fo<<"{"<<4096-mat<<","<<len2<<"}";
			i+=len2-1;
		}else fo<<input[i];
	}
	fo.close(),fi.close();
	/*
	//	i = kmp(target, strlen(target), pattern, strlen(pattern));
	//	if (i >= 0)
	//		printf("matched @: %s\n", ch + i);*/
	return 0;
}
