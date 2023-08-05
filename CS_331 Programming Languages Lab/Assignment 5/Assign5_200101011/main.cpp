#include <bits/stdc++.h>
using namespace std;

class MergeSortTree{
private:
    int size;
    vector<vector<int>> tree;
    vector<int> arr;
    vector<int> merge_util(vector<int>& a1, vector<int>& a2){
        vector<int> ans;
        int i = 0, j = 0;
        while(i<a1.size() && j<a2.size()){
            if(a1[i]<=a2[j]){
                ans.push_back(a1[i]);
                i++;
            }
            else{
                ans.push_back(a2[j]);
                j++;
            }
        }
        while(i<a1.size()){
            ans.push_back(a1[i]);
            i++;
        }
        while(j<a2.size()){
            ans.push_back(a2[j]);
            j++;
        }
        return ans;
    }
    void build(int start, int end, int index){
        if(start == end){
            tree[index] = {arr[start]};
            return;
        }
        int mid = (start+end)/2;
        build(start, mid, 2*index+1);
        build(mid+1, end, 2*index+2);
        tree[index] = merge_util(tree[2*index+1], tree[2*index+2]);
    }
    int query_util(int index, int start, int end, int L, int R, int K){
        int ans;
        if(start > R || end < L){
            ans = 0;
        }
        else if(L <= start && end <= R){
            ans = lower_bound(tree[index].begin(), tree[index].end(), K) - tree[index].begin();
        }
        else{
            int mid = (start + end)/2;
            int left = query_util(2*index + 1, start, mid, L, R, K);
            int right = query_util(2*index + 2, mid+1, end, L, R, K);
            ans = left + right;
        }
        return ans;
    }

public:
    MergeSortTree(vector<int> &_arr){
        arr = _arr;
        size = arr.size();
        tree.resize(4*size);
        build(0, size-1, 0);
    }
    int query(int L, int R, int K){
        return query_util(0, 0, size-1, L, R, K);
    }
    void display(){
        for(int i=0; i<4*size; i++){
            for(int j=0; j<tree[i].size(); j++){
                cout<<tree[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
};

int main(){
    int n;
    cout<<"Enter Array Size: ";
    cin >> n;
    vector<int> arr(n);
    cout<<"Enter Array: ";
    for(int i=0; i<n; i++) cin>>arr[i];
    MergeSortTree mst(arr);
    cout<<"\nMerge Sort Tree:\n";
    mst.display();
    int q,l,r,k;
    cout<<"Enter Number of Queries: ";
    cin>>q;
    for(int i=0; i<q; i++){
        cout<<"Query "<<i+1<<": ";
        cin>>l>>r>>k;
        cout<<"Ans "<<i+1<<": "<< mst.query(l-1,r-1,k)<<"\n";
    }
}