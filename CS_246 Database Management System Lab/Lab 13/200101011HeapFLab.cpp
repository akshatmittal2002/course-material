#include <bits/stdc++.h>
using namespace std;

class page{
    public:
        int num_records,free_space_add;
        page *prev_page, *next_page;
        int page_id , empty_space;
        vector<pair<int,int>> record_directory;
        page(int id, page *prev, int size){
            page_id = id;
            prev_page = prev;
            num_records = 0;
            free_space_add = 0;
            next_page = nullptr;
            empty_space = size-16;
        }
        bool insert_page(int rec_size, int n);
        int search_page(int n);
};

bool page::insert_page(int rec_size,int n){
    if(empty_space < (rec_size + 4)){
        return false;
    }
    record_directory.push_back(make_pair(n,rec_size));
    num_records++;
    free_space_add += rec_size;
    empty_space -= (rec_size + 4);
    sort(record_directory.begin(),record_directory.end());
    return true;
}

int page::search_page(int n){
    for(int i=0; i<num_records; i++){
        if(record_directory[i].first == n){
            return i;
        }
    }
    return -1;
}

class heap_file{
    int page_size;
    page* head;
    public:
        int num_pages;
        heap_file(int size){
            page_size = size;
            head = nullptr;
            num_pages = 0;
        }
        bool insert(int rec_size,int n);
        bool search(int n);
        void display();
};

void heap_file::display(){
    cout<<num_pages;
    page* curr = head;
    while(curr != nullptr){
        cout<<" "<<(curr->num_records);
        curr = curr->next_page;
    }
    cout<<"\n";
}

bool heap_file::search(int n){
    page* curr = head;
    while(curr != nullptr){
        int slot = curr->search_page(n);
        if(slot != -1){
            cout<<curr->page_id<<" "<<slot<<"\n";
            return true;
        }
        curr = curr->next_page;
    }
    cout<<"-1 -1\n";
    return false;
}

bool heap_file::insert(int rec_size,int n){
    page* curr = head;
    page* maxx = curr;
    page* last = nullptr;
    while(curr != nullptr){
        last = curr;
        if((curr->empty_space) > (maxx->empty_space)){
            maxx = curr;
        }
        curr = curr->next_page;
    }
    if(maxx != nullptr){
        if(maxx->empty_space >= (rec_size+4)){
            return maxx->insert_page(rec_size,n);
        }
    }
    num_pages++;
    page* new_page;
    if(head == nullptr){
        new_page = new page(0,nullptr,page_size);
        head = new_page;
        return new_page->insert_page(rec_size,n);
    }
    else{
        new_page = new page((last->page_id)+1,last,page_size);
        last->next_page = new_page;
        return new_page->insert_page(rec_size,n);
    }
}

int main(){
    int page_size;
    cin>>page_size;
    heap_file h(page_size);
    int t, rec_size, val;
    cin>>t;
    while(t != 4){
        if(t == 1){
            cin>>rec_size>>val;
            h.insert(rec_size,val);
        }
        else if(t == 2){
            h.display();
        }
        else if(t == 3){
            cin>>val;
            h.search(val);
        }
        cin>>t;
    }
}