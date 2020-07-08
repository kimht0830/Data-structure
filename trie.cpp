#ifndef bits
#define bits
#include<bits/stdc++.h>
#endif
using namespace std;
typedef struct node{
	char alpha;
	node * parent;
	node* next[28];
}Node;
Node * insert_node(Node* parent,char val){
	Node * son=(Node *)malloc(sizeof(Node));
	if(val=='\0'){
		son->alpha=val;
		parent->next[27]=son;
	}
	else if(val==' '){
		son->alpha=val;
		parent->next[26]=son;
	}
	else{
		son->alpha=val;
		parent->next[val-'a']=son;
	}
	for(int i=0;i<28;i++)
		son->next[i]=NULL;
	son->parent=parent;
	return son;
}
Node * make_trie(){
	Node * head=(Node*)malloc(sizeof(Node));
	head->alpha=-1;
	for(int i=0;i<28;i++){
		head->next[i]=NULL;
	}
	head->parent=NULL;
	return head;
}
void insert_string(Node* head,char get[]){
	int l=strlen(get);
	Node* now=head;
	for(int i=0;i<l;i++){
		if(get[i]==' '){
			if(now->next[26]!=NULL){
				now=now->next[26];
			}
			else{
				now=insert_node(now,get[i]);
			}
		}
		else{
			if(now->next[get[i]-'a']!=NULL){
				now=now->next[get[i]-'a'];
			}
			else{
				now=insert_node(now,get[i]);
			}
		}
	}
	insert_node(now,'\0');
}
bool unuse_node(Node * a){
	for(int i=0;i<28;i++){
		if(a->next[i]!=NULL)
			return false;
	}
	return true;
}
void delete_string(Node * head, char get[]){
	int l=strlen(get);
	Node* now=head;
	for(int i=0;i<l;i++){
		if(get[i]==' '){
			now=now->next[26];
		}
		else{
			now=now->next[get[i]-'a'];
		}
	}
	now=now->next[27];
	while(unuse_node(now)){
		if(now==head){
			break;
		}
		Node* p=now->parent;
		char val=now->alpha;
		free(now);
		if(val==' '){
			p->next[26]=NULL;
		}
		else if(val=='\0'){
			p->next[27]=NULL;
		}
		else{
			p->next[val-'a']=NULL;
		}
		now=p;
	}
}
void dfs_tree(Node* start,vector <char>&get){
	if(get.back()=='\0'){
		for(int i=0;i<get.size();i++){
			printf("%c",get[i]);
		}
		printf("\n");
		return;
	}
	for(int i=0;i<28;i++){
		if(start->next[i]==NULL)
			continue;
		if(i==27){
			get.push_back('\0');
		}
		else if(i==26){
			get.push_back(' ');
		}
		else{
			get.push_back('a'+i);
		}
		dfs_tree(start->next[i],get);
		get.pop_back();
	}
}
bool search(Node * head,char get[]){
	int l=strlen(get);
	vector <char> carry;
	Node * now=head;
	for(int i=0;i<l;i++){
		carry.push_back(get[i]);
		if(now==NULL)
			return false;
		if(get[i]==' '){
			now=now->next[26];
		}
		else{
			now=now->next[get[i]-'a'];
		}
	}
	if(now==NULL)
		return false;
	else{
		dfs_tree(now,carry);
		return true;
	}
}
