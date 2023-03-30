#include<bits/stdc++.h>
using namespace std;

map<int, set<int>> key_to_set;
map<set<int>, int> set_to_key;

bool compare(int a, int b)
{
    if(key_to_set[a].size() != key_to_set[b].size()) return (key_to_set[a].size() < key_to_set[b].size());
    else return (key_to_set[a] < key_to_set[b]);
}

bool check_subset(int a, int b)
{
    if((a & b) == a) return true;
    else return false;
}

int main()
{
    int num_att;
    cin >> num_att;
    
    vector<int> attributes(num_att);
    for(int i=0; i<num_att; i++) attributes[i] = i+1;

    int num_fd;
    cin >> num_fd;

    set<pair<int, int>> funcDep;
    vector<bool> done;
    vector<int> ans;

    int num_subsets = 1 << num_att;

    set<int> curr_subset;
    int position;

    for(int i=0; i<num_subsets; i++)
    {
        curr_subset.clear();
        for(int j=0; j<num_att; j++)
        {
            position = 1 << j;
            if((i & position) != 0) curr_subset.insert(attributes[j]);
        }
        key_to_set.insert({i, curr_subset});
        set_to_key.insert({curr_subset, i});
        done.push_back(false);
    }
    
    string temp;
    getline(cin, temp);
    
    set<int> left_att;
    set<int> right_att;
    int temp_num;

    for(int i=0; i<num_fd; i++)
    {
        left_att.clear();
        right_att.clear();
        getline(cin, temp);
        stringstream tempstream1(temp);
        while(!tempstream1.eof())
        {
            tempstream1 >> temp;
            if(stringstream(temp) >> temp_num) left_att.insert(temp_num);
        }
        getline(cin, temp);
        stringstream tempstream2(temp);
        while(!tempstream2.eof())
        {
            tempstream2 >> temp;
            if(stringstream(temp) >> temp_num) right_att.insert(temp_num);
        }
        funcDep.insert(make_pair(set_to_key[left_att], set_to_key[right_att]));
    }

    int prev;
    int curr;

    for(int i=0; i<num_subsets; i++)
    {
        if(done[i]) continue;
        done[i] = true;
        curr_subset = key_to_set[i];
        prev = -1;
        curr = i;
        while(prev != curr)
        {
            prev = curr;
            for(auto it = funcDep.begin(); it != funcDep.end(); it++)
            {
                if(check_subset(it->first, curr)) curr = (curr | it->second);
            }
        }
        if(curr == (num_subsets - 1))
        {
            ans.push_back(i);
            for(int j=i+1; j<num_subsets; j++)
            {
                if(check_subset(i, j)) done[j] = true;
            }
        }
    }

    sort(ans.begin(), ans.end(), compare);
    
    cout<<ans.size()<<"\n";
    for(auto i=ans.begin(); i!=ans.end(); i++)
    {
        curr_subset = key_to_set[*i];
        cout<<*(curr_subset.begin());
        for(auto j=curr_subset.begin();;)
        {
            j++;
            if(j == curr_subset.end()) break;
            cout<<" "<<*(j);
        }
        cout<<"\n";
    }
    return 0;
}