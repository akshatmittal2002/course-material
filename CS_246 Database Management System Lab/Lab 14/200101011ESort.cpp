#include <bits/stdc++.h>
using namespace std;

int it_num, page_num, m, rec_per_page, total_rec, buffer;
int curr_it = 0;

void merge(vector<vector<int>>& runs, vector<int>& temp){
    vector<int> pointer;
    int num = 0, min, k, i, j;
    for (i = 0; i < runs.size(); i++){
        pointer.push_back(0);
        num += runs[i].size();
    }
    for (i = 0; i < num; i++){
        min = INT_MAX;
        k = 0;
        for (j = 0; j < pointer.size(); j++){
            if (pointer[j] < runs[j].size() && runs[j][pointer[j]] < min){
                min = runs[j][pointer[j]];
                k = j;
            }
        }
        temp.push_back(min);
        pointer[k]++;
    }
}

void external_sort(vector<vector<int>>& runs){
    for (int i = 0; i < runs.size(); i++){
        sort(runs[i].begin(), runs[i].end());
    }
    vector<vector<int>> sorted_runs, temp;
    int k = 0, i = 0;
    vector<int> temp1;
    while (i < runs.size()){
        temp.clear();
        for (k = 0; k < buffer && i + k < runs.size(); k++){
            temp.push_back(runs[i + k]);
        }
        temp1.clear();
        merge(temp, temp1);
        sorted_runs.push_back(temp1);
        i += k;
    }
    runs.clear();
    runs = sorted_runs;
    while (runs.size() > 1){
        if(it_num == curr_it){
            break;
        }
        sorted_runs.clear();
        temp.clear();
        k = 0, i = 0;
        temp1.clear();
        while (i < runs.size()){
            temp.clear();
            for (k = 0; k < m && i + k < runs.size(); k++){
                temp.push_back(runs[i + k]);
            }
            temp1.clear();
            merge(temp, temp1);
            sorted_runs.push_back(temp1);
            i += k;
        }
        runs.clear();
        runs = sorted_runs;
        curr_it++;
    }
    if(curr_it == it_num){
        int pages = 0;
        for(int ii = 0; ii<runs.size(); ii++){
            if((pages + ceil(runs[ii].size()/(double)(rec_per_page))) > page_num ){
                page_num -= pages;
                for(int jj = page_num*rec_per_page; jj < runs[ii].size() && jj < (page_num+1)*rec_per_page; jj++){
                    cout<<runs[ii][jj]<<"\n";
                }
                return;
            }
            else{
                pages += ceil(runs[ii].size()/(double)(rec_per_page));
            }
        }
    }
    else if(curr_it < it_num){
        cout<<"Program Ended in only "<<curr_it<<" iterations but output is asked after "<<it_num<<" iterations.\n";
    }
}

int main(){
    cin >> buffer >> m >> rec_per_page >> total_rec;
    vector<vector<int>> runs;
    int k = 0, i = 0, a;
    vector<int> temp;
    while (i < total_rec){
        temp.clear();
        for (k = 0; k < rec_per_page && i + k < total_rec; k++){
            cin >> a;
            temp.push_back(a);
        }
        runs.push_back(temp);
        i += k;
    }
    cin >> it_num >> page_num;
    external_sort(runs);
    return 0;
}