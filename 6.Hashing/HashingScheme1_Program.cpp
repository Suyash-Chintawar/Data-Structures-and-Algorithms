//Implementing hashing using Linear probing
#include <bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

long long int hash_func(long long int key)
{
    return key%100000;
}

long long int get_index(long long int i,long long int key)
{
    long long int index;
    index=(hash_func(key)+i)%100000;
    return index;
}

//This function below is the key difference in linear and quadratic probing
void insert_key(long long int hash_table[])
{
    long long int index,key,i;
    key=rand();
    for(i=0;;i++)
    {
        index=get_index(i,key);
        if((hash_table[index]!=NULL)&&(hash_table[index]!=-1)) continue;
        else{
            hash_table[index]=key;
            break;
        }
    }
}

void delete_key(long long int hash_table[])
{
    long long int key,i,index;
    key=rand();
    for(i=0;;i++)
    {
        index=get_index(i,key);
        if(hash_table[index]==NULL)
        {
            break;
        }
        else if(hash_table[index]!=key) continue;
        else{
            if(hash_table[index]==key)
            {
                hash_table[index]=-1;
                break;
            }
        }

    }
}

void search_key(long long int hash_table[])
{
    long long int key,i,index;
    key=rand();
    for(i=0;;i++)
    {
        index=get_index(i,key);
        if(hash_table[index]==NULL)
        {
            break;
        }
        else if(hash_table[index]!=key) continue;
        else{
            if(hash_table[index]==key)
            {
                break;
            }
        }

    }
}

int main()
{
    cout<<"**Hashing Implementation using Linear probing**\nHash Table size: 100000\n";
    long long int hash_table[100000],i,cnt_ins=0,cnt_del=0,cnt_search=0,k;
    int f1=0,f2=0,f3=0,f4=0,f5=0,f6=0,f7=0;//These are just flags to note avg time after specific intervals
    float load_fac=0,tot_time=0;
    for(i=0;i<100000;i++) hash_table[i]=NULL;
    for(i=0;;i++)
    {
        if((load_fac>=0.1)&&(f1==0))
        {
            f1=1;
            cout<<"Load fac:0.1    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if((load_fac>=0.2)&&(f2==0))
        {
            f2=1;
            cout<<"Load fac:0.2    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if((load_fac>=0.3)&&(f3==0))
        {
            f3=1;
            cout<<"Load fac:0.3    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if((load_fac>=0.4)&&(f4==0))
        {
            f4=1;
            cout<<"Load fac:0.4    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if((load_fac>=0.5)&&(f5==0))
        {
            f5=1;
            cout<<"Load fac:0.5    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if((load_fac>=0.6)&&(f6==0))
        {
            f6=1;
            cout<<"Load fac:0.6    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if((load_fac>=0.7)&&(f7==0))
        {
            f7=1;
            cout<<"Load fac:0.7    Avg time till now:"<<tot_time/cnt_search<<" microsec\n";
        }
        else if(load_fac>=0.8)
        {
            cout<<"Load fac reached 0.8\n";
            break;
        }
        k=rand()%10;

        switch(k)
        {
            case 0:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();

                }
                break;

            case 1:
                {
                cnt_ins++;//Insert
                insert_key(hash_table);
                load_fac+=(1.0/100000);
                }
                break;

            case 2:
                {
                cnt_del++;//Delete
                delete_key(hash_table);
                }
                break;

            case 3:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();
                }
                break;

            case 4:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();
                }
                break;

            case 5:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();
                }
                break;

            case 6:
                {
                cnt_ins++;//Insert
                insert_key(hash_table);
                load_fac+=(1.0/100000);
                }
                break;

            case 7:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();
                }
                break;

            case 8:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();
                }
                break;

            case 9:
                {
                cnt_search++;//Search
                auto start =high_resolution_clock::now();
                search_key(hash_table);
                auto stop= high_resolution_clock::now();
                auto duration= duration_cast<microseconds>(stop-start);
                tot_time+=duration.count();
                }
                break;


        }
    }
    cout<<"Average Search time: "<<tot_time/cnt_search<<" microsec"<<endl;
    cout<<"Search counts: "<<cnt_search<<endl;
    cout<<"Insert counts: "<<cnt_ins<<endl;
    cout<<"Delete counts: "<<cnt_del<<endl;

}
