#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>

char *trace_file_name;
int s,E,b,verbose_flag;
int number_miss=0,number_hit=0,number_eviction=0;
typedef struct{
    int valid;
    int tag;
    int lru_flag;
}line;
typedef struct{
    line* cache_line;
}set;
typedef struct{
    set* sets;
    int set_number;
    int line_number;
}cache;

void print_help_menu();
long get_set_index(long address){return (address>>b)&((0x1<<s)-1);}
long get_tag(long address){return address>>(s+b);}
void data_load(cache *my_cache,long addr,int sz,int set_ind,int ln_tag);
void data_store(cache *my_cache,long addr,int sz,int set_ind,int ln_tag);
void data_modify(cache *my_cache,long addr,int sz,int set_ind,int ln_tag);
bool data_hit(cache *my_cache,int set_ind,int ln_tag);
bool update_cache(cache *my_cache,int set_ind,int ln_tag);
int choose_replaced_cache_by_lru(cache *my_cache,int set_ind,int ln_tag);
void update_cache_lru_flag(cache *my_cache,int set_ind,int ln_tag,int rep_cache);
int main(int argc,char **argv){
    cache my_cache;
    //get command from user
    if(argc==1){
        print_help_menu();
        exit(0);
    }
    char temp;
    while((temp=getopt(argc,argv,"hvs:E:b:t:"))!=-1){
        if(temp!='v'&&temp!='s'&&temp!='E'&&temp!='b'&&temp!='t'){
            print_help_menu();
            exit(0);
        }
        if(temp=='h'){
            print_help_menu();
            exit(0);
        }
        else if(temp=='v')
            verbose_flag=1;
        else if(temp=='s')
            s=atoi(optarg);
        else if(temp=='E')
            E=atoi(optarg);
        else if(temp=='b')
            b=atoi(optarg);
        else if(temp=='t')
            trace_file_name=optarg;
        else {
            print_help_menu();
            exit(0);
        }
    }
    //initialize cache
    my_cache.set_number=2<<s;
    my_cache.line_number=E;
    my_cache.sets=(set*)malloc(my_cache.set_number*sizeof(set));
    for(int i=0;i<my_cache.set_number;++i){
        my_cache.sets[i].cache_line=(line*)malloc(my_cache.line_number*sizeof(line));
        for(int j=0;j<my_cache.line_number;++j){
            my_cache.sets[i].cache_line[j].tag=0;
            my_cache.sets[i].cache_line[j].valid=0;
            my_cache.sets[i].cache_line[j].lru_flag=0;
        }
    }
    //read tracefile
    FILE *trace_file;
    char operation[3];
    long address;
    int size;
    if((trace_file=fopen(trace_file_name,"r"))==NULL){
        printf("%s: No such file or directory",trace_file_name);
    }
    while(fscanf(trace_file,"%s %lx,%d",operation,&address,&size)!=EOF){
        int set_index=get_set_index(address);
        int line_tag=get_tag(address);
        if(operation[0]=='I') continue; 
        if(verbose_flag== 1) printf("%s %lx,%d ",operation,address,size);
        if(operation[0]=='L'){
            data_load(&my_cache,address,size,set_index,line_tag);
        }
        if(operation[0]=='S'){
            data_store(&my_cache,address,size,set_index,line_tag);
        }
        if(operation[0]=='M'){
            data_modify(&my_cache,address,size,set_index,line_tag);
        }
        if(verbose_flag== 1) {
            printf("\n");
        }
    }
    printSummary(number_hit, number_miss, number_eviction);
    fclose(trace_file);
    return 0;
}

void print_help_menu(){
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("-h         Print this help message.\n");
    printf("-v         Optional verbose flag.\n");
    printf("-s <num>   Number of set index bits.\n");
    printf("-E <num>   Number of lines per set.\n");
    printf("-b <num>   Number of block offset bits.\n");
    printf("-t <file>  Trace file.\n\n\n");
    printf("Examples:\n");
    printf("linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}
void data_load(cache *my_cache,long addr,int sz,int set_ind,int ln_tag){
    if(data_hit(my_cache,set_ind,ln_tag)){
        if(verbose_flag==1){
            printf("hit ");
        }
        ++number_hit;
    }
    else{
        bool eviction_flag=update_cache(my_cache,set_ind,ln_tag);
        if(verbose_flag==1){
            printf("miss ");
        }
        ++number_miss;
        if(eviction_flag){
            if(verbose_flag==1){
                printf("eviction ");
            }
            ++number_eviction;
        }
    }
}
void data_store(cache *my_cache,long addr,int sz,int set_ind,int ln_tag){
    data_load(my_cache,addr,sz,set_ind,ln_tag);
}
void data_modify(cache *my_cache,long addr,int sz,int set_ind,int ln_tag){
    data_store(my_cache,addr,sz,set_ind,ln_tag);
    data_load(my_cache,addr,sz,set_ind,ln_tag);
}
bool data_hit(cache *my_cache,int set_ind,int ln_tag){
    for(int i=0;i<my_cache->line_number;++i){
        if(my_cache->sets[set_ind].cache_line[i].valid==1&&my_cache->sets[set_ind].cache_line[i].tag==ln_tag){
            update_cache_lru_flag(my_cache,set_ind,ln_tag,i);
            return 1;
        }
    }
    return 0;
}
bool update_cache(cache *my_cache,int set_ind,int ln_tag){
    //judge cache full
    bool full_flag=1;
    int empty_location=-1;
    int eviction_flag=0;
    for(int i=0;i<my_cache->line_number;++i){
        if(my_cache->sets[set_ind].cache_line[i].valid==0){
            full_flag=0;//unfull
            empty_location=i;
            break;
        }
    }
    //unfull
    if(full_flag==0){
        my_cache->sets[set_ind].cache_line[empty_location].valid=1;
        my_cache->sets[set_ind].cache_line[empty_location].tag=ln_tag;
        update_cache_lru_flag(my_cache,set_ind,ln_tag,empty_location);
    }
    //full
    else{
        if(!data_hit(my_cache,set_ind,ln_tag)){
           eviction_flag=1;
        }
        int rep_cache_lru=choose_replaced_cache_by_lru(my_cache,set_ind,ln_tag);
        my_cache->sets[set_ind].cache_line[rep_cache_lru].valid=1;
        my_cache->sets[set_ind].cache_line[rep_cache_lru].tag=ln_tag;
        update_cache_lru_flag(my_cache,set_ind,ln_tag,rep_cache_lru);
    }
    return eviction_flag;
}
int choose_replaced_cache_by_lru(cache *my_cache,int set_ind,int ln_tag){
    int min_tag=1000000;
    int rep_item;
    for(int i=0;i<my_cache->line_number;++i){
        if(my_cache->sets[set_ind].cache_line[i].lru_flag<min_tag){
            min_tag=my_cache->sets[set_ind].cache_line[i].lru_flag;
            rep_item=i;
        }
    }
    return rep_item;    
}
void update_cache_lru_flag(cache *my_cache,int set_ind,int ln_tag,int rep_cache){
    my_cache->sets[set_ind].cache_line[rep_cache].lru_flag=999999;
    for(int i=0;i<my_cache->line_number;++i){
        if(i!=rep_cache){
            --my_cache->sets[set_ind].cache_line[i].lru_flag;
        }
    }
}