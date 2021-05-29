#include<bits/stdc++.h>
#include <fstream>
using namespace std;

vector<string> words_with_prefix;
string grid[4][4];
bool vis[4][4];
int num=0;

int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};

struct TrieNode{
	struct TrieNode* ch[26];
	bool wordend;
};
TrieNode* trie = new TrieNode();

void insert(string str){
	TrieNode* node=trie;
	for(int i=0;i<str.size();++i){
		if(node->ch[str[i]-'a']==NULL){
			node->ch[str[i]-'a']=new TrieNode();
		}
		node=node->ch[str[i]-'a'];
	}
	node->wordend=true;
}

void build(){
	string word_in_list;
	ifstream word_list("word_list.txt");
	while(getline(word_list,word_in_list)){
		insert(word_in_list);
	}
	word_list.close();
}

bool search(string str){
	TrieNode* src=trie;
	for(int i=0;i<str.size();++i){
		if(src->ch[str[i]-'a']==NULL) return false;
		src=src->ch[str[i]-'a'];
	}
	if(src->wordend==true) return true;
	return false;
}


void dfs(int i,int j,string word_formed){
	vis[i][j]=true;
	if(search(word_formed)==1){
		cout<<++num<<"). "<<word_formed<<endl;
	}
	for(int idx=0;idx<4;++idx){
		int x = i+dx[idx];
		int y = j+dy[idx];
		if(x>=0 && x<4 && y>=0 && y<4 && vis[x][y]==false){
			dfs(x,y,word_formed+grid[x][y]);
		}
	}
	vis[i][j]=false;
}

int main(){
	build();
	cout<<"-------------Enter the Wordament Puzzle Grid----------------"<<endl;
	for(int l=0;l<4;++l){
		for(int r=0;r<4;++r){
			cin>>grid[l][r];
		}
	}
	cout<<endl;
	cout<<"-------------Valid Words in the Puzzle are-------------------"<<endl;
	for(int n=0;n<4;++n){
		for(int m=0;m<4;++m){
			dfs(n,m,grid[n][m]);
		}
	}
	return 0;
}
