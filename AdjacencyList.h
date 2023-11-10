#pragma once
#include <string>
#include <vector>
using namespace std;

struct Website{
    struct Link{
        Link* next;
        Website* parent;
        Link();
    };

    string name;
    float out_degree;
    float rank;
    Website* next;
    Link* head_link;

    Website(string site_name);
    void Add(Link* from);
    float GenRank();
};



class AdjacencyList
{
    private:
        Website* head_site;
        float web_count;
        Website* AddSite(string name);
    public:
        AdjacencyList();
        void AddLink(string from, string to);
        void PageRank(int power);
        ~AdjacencyList();
};

AdjacencyList::AdjacencyList(){
    head_site = nullptr;
    web_count = 0;
}
AdjacencyList::~AdjacencyList(){
    //loop through and destroy each link & website
}

Website* AdjacencyList::AddSite(string name){
    Website* current = head_site;
    Website* new_site = new Website(name);
    while(current != nullptr){
        if(current->name.compare(name) < 0 || current->next == nullptr){
            new_site->next = current->next;
            current->next = new_site;
            web_count++;
            return new_site;
        }
        current = current->next;
    }
    head_site = new_site;
    web_count++;
    return new_site;
}

void AdjacencyList::AddLink(string from, string to){
    Website* current = head_site;
    Website::Link* from_to_link = new Website::Link();
    bool from_exist = false;
    bool to_exist = false;
    while(current != nullptr){
        if(current->name.compare(to) == 0){
            to_exist = true;
            current->Add(from_to_link);
        }
        if(current->name.compare(from)==0){
            from_exist = true;
            from_to_link->parent = current;
            current->out_degree +=1.0;
        }
        current = current->next;
    }

    if(!from_exist){
        Website* new_site = AddSite(from);
        from_to_link->parent = new_site;
        new_site->out_degree +=1.0;
    }
    if(!to_exist){
        Website* new_site = AddSite(to);
        new_site->Add(from_to_link);
    }
}

void AdjacencyList::PageRank(int power){
    for(int i = 0; i<power;i++){
        Website* current = head_site;
        while(current != nullptr){
            if(i==0){
                current->rank = 1.0/web_count;
            }else{
                current->rank = current->GenRank();
            }
            current = current->next;
        }
    }
    Website* current = head_site;
    while(current != nullptr){
        int rank = int(current->rank * 100 +.5);
        cout<<current->name<<" "<< float(rank/100) <<endl;
        current = current->next;
    }
}

Website::Website(string site_name){
    name = site_name;
    out_degree = 0;
    next = nullptr;
    head_link = nullptr;
}

void Website::Add(Link* from){
    if(head_link == nullptr){
        head_link = from;
    }else{
        Link* compare = head_link;
        from->next = compare;
        head_link = from;
    }
}

float Website::GenRank(){
    Link* current = head_link;
    float tot = 0;
    while(current!=nullptr){
        tot += (rank)/(current->parent->out_degree);
        current = current->next;
    }
    return tot;
}

Website::Link::Link(){
    next = nullptr;
}