#include<bits/stdc++.h>
using namespace std;

map<int, set<int>> key_to_set;
map<set<int>, int> set_to_key;

bool compare(int a, int b)
{
    return (key_to_set[a] < key_to_set[b]);
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

    vector<pair<int, int>> funcDep;
    vector<bool> done;
    vector<int> cand_keys;

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
        funcDep.push_back(make_pair(set_to_key[left_att], set_to_key[right_att]));
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
            cand_keys.push_back(i);
            for(int j=i+1; j<num_subsets; j++)
            {
                if(check_subset(i, j)) done[j] = true;
            }
        }
    }
    
    vector<int> norm_schema;
    set<int> curr_relation;
    curr_subset.clear();
    bool ans;
    for(auto i : attributes)
    {
        curr_subset.insert(i);
    }
    norm_schema.push_back(set_to_key[curr_subset]);
    for(auto i : funcDep)
    {
        if(find(cand_keys.begin(),cand_keys.end(),i.first)!=cand_keys.end()) continue;
        ans = false;
        curr_subset = key_to_set[i.first];
        curr_relation = key_to_set[norm_schema[0]];
        for(auto j : key_to_set[i.first])
        {
            if(curr_relation.count(j)==0)
            {
                ans = true;
                break;
            }
        }
        if(ans) continue;
        for(auto j : key_to_set[i.second])
        {
            curr_subset.insert(j);
            if(curr_relation.count(j)==0)
            {
                ans = true;
                break;
            }
            curr_relation.erase(j);
        }
        if(ans) continue;
        norm_schema[0] = set_to_key[curr_relation];
        norm_schema.push_back(set_to_key[curr_subset]);
    }

    curr_subset.clear();
    for(auto i : norm_schema)
    {
        curr_subset.insert(i);
    }
    norm_schema.clear();
    for(auto i : curr_subset)
    {
        norm_schema.push_back(i);
    }
    sort(norm_schema.begin(), norm_schema.end(), compare);
    cout<<norm_schema.size()<<"\n";
    for(auto i : norm_schema)
    {
        curr_subset = key_to_set[i];
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
