#include <iostream>
#include <vector>
#include<utility>
#include <string.h>
using namespace std;


#define N 26

typedef struct TrieNode TrieNode;

struct TrieNode {
    
    char data; 
    int count;
    TrieNode* children[N];
    int is_leaf;
};



TrieNode* make_trienode(char data) {
    
    TrieNode* node = (TrieNode*) calloc (1, sizeof(TrieNode));
    for (int i=0; i<N; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->count=1;
    node->data = data;
    return node;
}

void free_trienode(TrieNode* node) {
    
    for(int i=0; i<N; i++) {
        if (node->children[i] != NULL) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}



int search_trie(TrieNode* root, string word)
{
    
    TrieNode* temp = root;

    for(int i=0; word[i]!='\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 0;
}

void print_trie(TrieNode* root) 
{
    
    if(!root)
    return;

    for(int i=0;i<N;i++)
    {
        if(root->children[i])
        cout<<root->children[i]->data<<" - "<<root->children[i]->count<<"\n";
    }
    cout<<"\n_____________________________________\n";
    for(int i=0;i<N;i++)
    print_trie(root->children[i]);
}



vector<vector<string >> db={
                            {"E","K","M","N","O","Y"},
                            {"D","E","K","N","O","Y"},
                            {"A","E","K","M"},
                            {"C","K","M","U","Y"},
                            {"C","E","I","K","O","O"}
                            };

vector<vector<string >> ordered_fi;
vector<pair<string,int>> frequent_patt;
vector<string > conditional_patt;
vector<vector<string> > conditional_patt_base;
vector<vector<string> > conditional_freq_patt_tree;
vector<pair<string,int> >itemset;

int min_support=3;

void calc_frequency(void)
{
    vector<int >freq(26,0);
    for(int i=0;i<db.size();i++)
        for(int j=0;j<db[i].size();j++)
            freq[db[i][j][0]-'A']++;
    
    for(int i=0;i<26;i++)
    {
        if(freq[i]>0 && freq[i]>=min_support)
        itemset.push_back(make_pair(string(1,'A'+i),freq[i]));
    }
    
}

void sort_itemset(void)
{
    int i, j,n=itemset.size();    
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (itemset[j].second < itemset[j + 1].second)
                {
                    pair<string , int >temp;
                    temp.first=itemset[j].first;
                    itemset[j].first=itemset[j+1].first;
                    itemset[j+1].first=temp.first;

                    temp.second=itemset[j].second;
                    itemset[j].second=itemset[j+1].second;
                    itemset[j+1].second=temp.second;
                }

    for(int i=0;i<itemset.size();i++)
    cout<<itemset[i].first<<"- "<<itemset[i].second<<"\n";
}

void build_ordered_i(void)
{
    int n=itemset.size();
    vector<string >temp;
    for(int i=0;i<db.size();i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<db[i].size();k++)
            if(itemset[j].first==db[i][k])
            {
                temp.push_back(itemset[j].first);
                break;
            }
            
        }
        ordered_fi.push_back(temp);
        temp.clear();
    }
    cout<<"ID       ITEMS\n";
    for(int i=0;i<ordered_fi.size();i++)
    {
        cout<<i+1<<".       ";
        for(int j=0;j<ordered_fi[i].size();j++)
        cout<<ordered_fi[i][j]<<" ";
        cout<<"\n";
    }
}

TrieNode* insert_trie(TrieNode* root, string word) {

    TrieNode* temp = root;

    for (int i=0; word[i] != '\0'; i++) {
        int idx = (int) word[i] - 'A';
        if (temp->children[idx] == NULL) {
            
            temp->children[idx] = make_trienode(word[i]);
        }
        else {
            
            temp->children[idx]->count++;
        }
        
        temp = temp->children[idx];
    }
    
    temp->is_leaf = 1;
    return root;
}

void generate_freq_pattern(TrieNode* root)
{
    for(int i=0;i<N;i++)
    {
        if(root->children[i])
        generate_freq_pattern(root->children[i]);
    }
}

void generate_cntl_patt(struct TrieNode* root, char str[], int level)
{
    
    if (root->is_leaf==1)
    {
        string temp="";
        temp+=str[level-1];
        temp+=root->count+'0';
        str[level] = '\0';
        int i=0;
        while(str[i+1]!='\0')
        {
            temp+=str[i];
            i++;
        }
        
        conditional_patt.push_back(temp);
        
    }
 
    int i;
    for (i = 0; i <N; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'A';
            generate_cntl_patt(root->children[i], str, level + 1);
        }
    }
}

void build_cntl_patt_base(void)
{
    for(int i=0;i<itemset.size();i++)
    {
        vector<string>x;
        conditional_patt_base.push_back(x);
    }
    for(int i=0;i<itemset.size();i++)
    {
        conditional_patt_base[i].push_back(itemset[i].first);
    }

    for(int i=0;i<conditional_patt_base.size();i++)
    {
        char x=conditional_patt_base[i][0][0];
        for(int j=0;j<conditional_patt.size();j++)
        {
            if(x==conditional_patt[j][0])
            {
                string temp="";
                if(conditional_patt_base[i].size()==1)
                {
                    temp=string(1,conditional_patt[j][1]);
                
                    conditional_patt_base[i].push_back(temp);
                    temp="";
                }
                
                
                for(int k=2;k<conditional_patt[j].size();k++)
                temp+=conditional_patt[j][k];
                conditional_patt_base[i].push_back(temp);
            }
        }
    }
    cout<<"     ITEMS     FREQUENCY   CONDITIONAL FREQUENT BASE\n";
    for(int i=0;i<conditional_patt_base.size();i++)
    {
        cout<<i+1<<".     ";
        for(int j=0;j<conditional_patt_base[i].size();j++)
        {
            cout<<conditional_patt_base[i][j];
            if(j<=1)cout<<"             ";
            else cout<<",";
        }
        cout<<"\b \n";
    }

    
}

string common_prefix(vector<string> comp)
{
    
    string res="";
    int ind=0;
    int min_len=itemset.size();

    for(int i=0;i<comp.size();i++)
    if(comp[i].length()<min_len)
    min_len=comp[i].length();
    int alpha[26]={0};
    for(int i=0;i<comp.size();i++)
    {
        for(int j=0;j<min_len;j++)
        {
            alpha[comp[i][j]-'A']++;
            
        }
    }
    
    for(int i=0;i<26;i++)
    {
        if(alpha[i]==comp.size())
        {
            char tmp=i+'A';
            res+=tmp;
        }
            
    }
    
    return res;
}

void build_conditional_freq_patt_tree(void)
{
    for(int i=0;i<conditional_patt_base.size();i++)
    {
        vector<string>x;
        conditional_freq_patt_tree.push_back(x);
    }
    for(int i=0;i<conditional_freq_patt_tree.size();i++)
    {
        conditional_freq_patt_tree[i].push_back(conditional_patt_base[i][0]);
        //cout<<conditional_freq_patt_tree[i][0];
    }
    for(int i=0;i<conditional_patt_base.size();i++)
    {
        for(int j=0;j<conditional_patt_base[i].size();j++)
        {
            
            if(j==1)
            {
                string temp=conditional_patt_base[i][j];
                conditional_freq_patt_tree[i].push_back(temp);
            }
        }
    }

    for(int i=0;i<conditional_patt_base.size();i++)
    {
        vector<string>comp;
        for(int j=0;j<conditional_patt_base[i].size();j++)
        {
            
            if(j>1)
            {
                string temp=conditional_patt_base[i][j];
                if(temp.length()>0)
                comp.push_back(temp);
            }
        }
        if(comp.size()>0)
        {
            string final_freq_patt_tree=common_prefix(comp);
            conditional_freq_patt_tree[i].push_back(final_freq_patt_tree);
            comp.clear();
        }
        
    }
    cout<<"     ITEMS     FREQUENCY   CONDITIONAL FREQUENT PATTERN TREE\n";
    for(int i=0;i<conditional_freq_patt_tree.size();i++)
    {
        cout<<i+1<<".     ";
        for(int j=0;j<conditional_freq_patt_tree[i].size();j++)
        {
            cout<<conditional_freq_patt_tree[i][j]<<"             ";
        }
        cout<<"\n";
    }
}

void generate_freq_pattern_rules(void)
{
    cout<<"     ITEMS     FREQUENCY   CONDITIONAL FREQUENT PATTERN RULES\n";
    for(int i=0;i<conditional_freq_patt_tree.size();i++)
    {
        
        char x=conditional_freq_patt_tree[i][0][0];
        cout<<i+1<<".     "<<x<<"             ";
        if(conditional_freq_patt_tree[i].size()==1)
        {
            cout<<"\n";
            continue;
        }
        
        
        for(int j=0;j<conditional_freq_patt_tree[i].size();j++)
        {
            if(j==1)
            cout<<conditional_freq_patt_tree[i][j]<<"             ";
            else if(j>1)
            {
                cout<<string(1,x)+conditional_freq_patt_tree[i][j]<<"             ";
                if(conditional_freq_patt_tree[i][j].length()>1)
                for(int k=0;k<conditional_freq_patt_tree[i][j].size();k++)
                cout<<string(1,x)+conditional_freq_patt_tree[i][j][k]<<"             ";
            }
            
        }
        cout<<"\n";
    }
}
int main() 
{
    cout<<"TRANSACTION DATABASE---\n\n";
    cout<<"ID.      ITEMS\n";
    for(int i=0;i<db.size();i++)
    {
        cout<<i+1<<".       ";
        for(int j=0;j<db[i].size();j++)
        {
            cout<<db[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    TrieNode* root = make_trienode('\0');
    cout<<"\nMinimum support count = "<<min_support<<"\n";
    cout<<"\nFrequent Pattern Set---\n";
    calc_frequency();
    sort_itemset();
    cout<<"\nOrdered Itemset\n";
    build_ordered_i();

    cout<<"\n--Inserting Ordered Itemsets into Trie Data Structure--\n";
    string temp="";
    for(int i=0;i<ordered_fi.size();i++)
    {
        for(int j=0;j<ordered_fi[i].size();j++)
        temp+=ordered_fi[i][j];
        root=insert_trie(root,temp);
        temp="";
    }
    char res[20];
    //print_trie(root);
    cout<<"--Traversing the Trie and generating frequent patterns--\n\n";
    cout<<"\nConditional pattern Base generated---\n";
    generate_cntl_patt(root,res,0);
    build_cntl_patt_base();
    cout<<"\nConditional pattern Tree generated---\n";
    build_conditional_freq_patt_tree();
    cout<<"\nConditional pattern Rules generated---\n";
    generate_freq_pattern_rules();
    return 0;
}