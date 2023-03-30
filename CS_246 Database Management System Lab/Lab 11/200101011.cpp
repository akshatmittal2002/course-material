#include <bits/stdc++.h>
using namespace std;

class Bucket{
    private:
        int depth,size;
        Bucket* overflow;
        bool is_over;
        vector<int> values;
    public:
        Bucket(int depth, int size);
        int insert(int key);
        int isFull();
        int isEmpty();
        pair<bool,Bucket*> getoverflow();
        void updateoverflow(pair<bool,Bucket*> x);
        int changeDepth(int quantity);
        vector<int> copy();
        void clear();
};

class Directory{
    private:
        int global_depth, bucket_size, M;
        vector<Bucket*> buckets;
        int hash(int n);
        int pairIndex(int bucket_no, int depth);
        void grow();
        void split(int bucket_no);
        string bucket_id(int n);
    public:
        Directory(int depth, int bucket_size, int M);
        void insert(int key);
        void display();
        virtual ~Directory();
};

int main(){
    int max_bucket_size, global_depth, M;
    int key;
    int choice;
    cin>>global_depth>>max_bucket_size>>M;
    Directory d(global_depth,max_bucket_size,M);
    cin>>choice;
    while(choice != 6){
        switch(choice){
            case 2:{
                cin>>key;
                d.insert(key);
                break;
            }
            case 5:{
                d.display();
                break;
            }
        }
        cin>>choice;
    }
    return 0;
}

Directory::Directory(int depth, int bucket_size, int M)
{
    this->global_depth = depth;
    this->bucket_size = bucket_size;
    this->M = M;
    for(int i = 0 ; i < 1<<depth ; i++){
        buckets.push_back(new Bucket(depth,bucket_size));
    }
}

int Directory::hash(int n){
    return n&((1<<global_depth)-1);
}

int Directory::pairIndex(int bucket_no, int depth){
    return bucket_no^(1<<(depth-1));
}

void Directory::grow(void){
    int n = buckets.size();
    for(int i = 0 ; i < 1<<global_depth ; i++) buckets.push_back(buckets[i]);
    global_depth++;
    for(int i=0; i<n; i++){
        int local_depth = buckets[i]->changeDepth(1);
        int pair_index = pairIndex(i,local_depth);
        buckets[pair_index] = new Bucket(local_depth,bucket_size);
        vector<int> temp = buckets[i]->copy(), temp2;
        if((buckets[i]->getoverflow()).first) temp2 = (buckets[i]->getoverflow()).second->copy();
        buckets[i]->clear();
        int index_diff = 1<<local_depth;
        int dir_size = 1<<global_depth;
        for(int j=pair_index-index_diff ; j>=0 ; j-=index_diff ) buckets[j] = buckets[pair_index];
        for(int j=pair_index+index_diff ; j<dir_size ; j+=index_diff ) buckets[j] = buckets[pair_index];
        // cout<<"Split3\n";
        for(auto it=temp.begin();it!=temp.end();it++) insert((*it));
        for(auto it=temp2.begin();it!=temp2.end();it++) insert((*it));
        // cout<<"Split4\n";
    }
}

void Directory::split(int bucket_no){
    int pair_index,index_diff,dir_size;
    int local_depth = buckets[bucket_no]->changeDepth(0);
    if(local_depth==global_depth){
        int over=0;
        for(auto i : buckets){
            if((i->getoverflow()).first) over++;
        }
        int size=0;
        string s;
        set<string> shown;
        for(int i=0;i<buckets.size();i++){
            s = bucket_id(i);
            if(shown.find(s)==shown.end()){
                shown.insert(s);
                if(buckets[i]->isEmpty() == 0) size++;
            }
        }
        shown.clear();
        if((over*100)/size >= M){
            // cout<<"Start Growing!";
            grow();
            // cout<<"Grown!";
        }
    }
    else if(local_depth<global_depth){
        local_depth = buckets[bucket_no]->changeDepth(1);
        pair_index = pairIndex(bucket_no,local_depth);
        buckets[pair_index] = new Bucket(local_depth,bucket_size);
        vector<int> temp = buckets[bucket_no]->copy(), temp2;
        if((buckets[bucket_no]->getoverflow()).first) temp2 = (buckets[bucket_no]->getoverflow()).second->copy();
        buckets[bucket_no]->clear();
        index_diff = 1<<local_depth;
        dir_size = 1<<global_depth;
        for(int i=pair_index-index_diff ; i>=0 ; i-=index_diff ) buckets[i] = buckets[pair_index];
        for(int i=pair_index+index_diff ; i<dir_size ; i+=index_diff ) buckets[i] = buckets[pair_index];
        // cout<<"Split1\n";
        for(auto it=temp.begin();it!=temp.end();it++) insert((*it));
        for(auto it=temp2.begin();it!=temp2.end();it++) insert((*it));
        // cout<<"Split2\n";
    }
}

string Directory::bucket_id(int n){
    int d;
    string s;
    d = buckets[n]->changeDepth(0);
    s = "";
    while(n>0 && d>0){
        s = (n%2==0?"0":"1")+s;
        n/=2;
        d--;
    }
    while(d>0){
        s = "0"+s;
        d--;
    }
    return s;
}

void Directory::insert(int key){
    int bucket_no = hash(key);
    int status = buckets[bucket_no]->insert(key);
    if(status==0){
        if((buckets[bucket_no]->getoverflow()).first==false){
            (buckets[bucket_no]->updateoverflow({true,new Bucket(0,100)}));
            // cout<<"Created Overflow Bucket!\n";
        }
        (buckets[bucket_no]->getoverflow()).second->insert(key);
        // cout<<"Inserted "<<key<<" Into Overflow Bucket of "<<bucket_no<<"\n";
        split(bucket_no);
    }
    // else if(status == 1) cout<<"Inserted "<<key<<" Successfully in "<<bucket_no<<"\n";
    // else cout<<key<<" Already Exists!\n";
}

void Directory::display(){
    int size=0;
    string s;
    set<string> shown;
    for(int i=0;i<buckets.size();i++){
        s = bucket_id(i);
        if(shown.find(s)==shown.end()){
            shown.insert(s);
            if(buckets[i]->isEmpty() == 0) size++;
        }
    }    
    cout<<global_depth<<" "<<size<<"\n";
    shown.clear();
}

Directory::~Directory(){
    for(int i=0; i<buckets.size(); i++){
        if(buckets[i] == nullptr) continue;
        if((buckets[i]->getoverflow()).second != nullptr){
            ((buckets[i]->getoverflow()).second)->clear();
        }
        buckets[i]->clear();
        delete(buckets[i]);
    }
    buckets.clear();
}

Bucket::Bucket(int depth, int size){
    this->depth = depth;
    this->size = size;
    this->is_over = false;
    this->overflow = nullptr;
}

int Bucket::insert(int key){
    auto it = find(values.begin(),values.end(),key);
    if(it!=values.end()) return -1;
    if(isFull()) return 0;
    values.push_back(key);
    return 1;
}

int Bucket::isFull(void){
    if(values.size()==size) return 1;
    else return 0;
}

int Bucket::isEmpty(void){
    if(values.size()==0) return 1;
    else return 0;
}

pair<bool,Bucket*> Bucket::getoverflow(){
    return {is_over,overflow};
}

void Bucket::updateoverflow(pair<bool,Bucket*> a){
    this->is_over = a.first;
    this->overflow = a.second;
}

int Bucket::changeDepth(int quantity){
    depth += quantity;
    return depth;
}

vector<int> Bucket::copy(void){
    vector<int> temp(values.begin(),values.end());
    return temp;
}

void Bucket::clear(void){
    values.clear();
    is_over = false;
    if(overflow!=nullptr){
        delete(overflow);
        overflow = nullptr;
    }
}