#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 200

typedef struct {
    int id, age, available;
    char name[30], gender[10], bg[5], organ[20], city[20], phone[15];
} Donor;

typedef struct {
    int id, age, urgency, matched;
    char name[30], gender[10], bg[5], organ[20], city[20], phone[15];
} Recipient;

const char *names[] = {"Ramesh","Anita","Rahul","Neha","Arjun","Kavita"};
const char *orgs[] = {"Kidney","Liver","Heart"};
const char *cities[] = {"Hyderabad","Delhi","Mumbai"};
const char *bgs[] = {"A+","B+","O+","AB+"};

int randr(int a,int b){return a+rand()%(b-a+1);} 
void randstr(char *d,const char **arr,int n){strcpy(d,arr[rand()%n]);}

void gen(Donor *d,Recipient *r){
    for(int i=0;i<N;i++){
        d[i].id=100+i; randstr(d[i].name,names,6); d[i].age=randr(18,60);
        strcpy(d[i].gender,(i%2)?"Male":"Female"); randstr(d[i].bg,bgs,4);
        randstr(d[i].organ,orgs,3); randstr(d[i].city,cities,3);
        sprintf(d[i].phone,"9%09d",rand()%1000000000); d[i].available=rand()%2;
        r[i].id=500+i; randstr(r[i].name,names,6); r[i].age=randr(10,70);
        strcpy(r[i].gender,(i%2)?"Male":"Female"); randstr(r[i].bg,bgs,4);
        randstr(r[i].organ,orgs,3); randstr(r[i].city,cities,3);
        sprintf(r[i].phone,"8%09d",rand()%1000000000); r[i].urgency=randr(1,4);
        r[i].matched=0;
    }
}

void match(Donor *d,Recipient *r,int cityMatch){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(!r[i].matched && d[j].available && !strcmp(r[i].bg,d[j].bg) &&
               !strcmp(r[i].organ,d[j].organ) && (!cityMatch || !strcmp(r[i].city,d[j].city))){
                r[i].matched=d[j].id; d[j].available=0;
                printf("Match: %s <- %s | %s %s %s\n",r[i].name,d[j].name,r[i].bg,r[i].organ,r[i].city);
                break;
            }
        }
    }
}

int main(){
    srand(time(0)); Donor d[N]; Recipient r[N]; gen(d,r);
    int ch; while(1){
        printf("1.Match(ignore city)\n");
	printf(" 2.Match with city\n");
	printf(" 3.Exit\n");
        scanf("%d",&ch);
        if(ch==1) match(d,r,0);
        else if(ch==2) match(d,r,1);
        else break;
    }
}
