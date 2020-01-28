#include <stdio.h>
#include <stdlib.h>

#define N 4

struct list {
    char state[N][N];
    int isDeleted;
    int depth,h;
    struct list *parent;
    struct list *next;
};

struct list *head=NULL;

struct list *newNode(int type,int dir,struct list *old);
int check(struct list *node1,struct list *node2);
void insert(struct list *new);
void print(struct list *sol);
int isFinal(struct list *temp);
int h(struct list *temp);
struct list *begin();
int isValid(char c,int counter[N]);
struct list *findNext();
void aastro();

//////////////////////  main  /////////////////////////
int main()
{
    head=begin();
    aastro();
        return 0;
        system("pause");
}


/*
to type grammi h stili (0-N-1 grammes, >N-1 sthles)
dir: 1 aristera h panw , -1 de3ia h katw
*/


/////////////////////new node////////////////////////////
struct list *newNode(int type,int dir,struct list *old){
    struct list *temp;
    int i,j;

    temp=(struct list *)malloc(sizeof(struct list));
    if(temp==NULL){
        printf("Error allocating memory\n");
        exit(0);
    }
    temp->next=NULL;
    temp->parent=old;
    temp->depth=old->depth+1;
    temp->isDeleted=0;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            temp->state[i][j]=old->state[i][j];
        }
    }
    if(type<N){
		
        for(i=0;i<N;i++){
            temp->state[type][i]=old->state[type][(i+dir)%N];
        }
    }
    else{
		type=type-N;
        for(i=0;i<N;i++){
            temp->state[i][type]=old->state[(i+dir)%N][type];
        }
    }
    temp->h=h(temp);

    return(temp);
};


/////////////////////////////check////////////////////////////
int check(struct list *node1,struct list *node2){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(node1->state[i][j]!=node2->state[i][j]){
                return(0);
            }
        }
    }
    return(1);
}
////////////////////////insert//////////////////////////////////
void insert(struct list *new){
    struct list *temp=head;
    int flag=1;
    
    
    if(head==NULL){
        head=new;
    }
    else{
        while(temp->next!=NULL){
            if(check(temp,new)==1){
                flag=0;
                break;
            }
            temp=temp->next;
        }
        if(flag==1){
            temp->next=new;
        }
    }
}
//////////////////////////print/////////////////////////////////////

void print(struct list *sol){
    struct list *temp=sol->parent,*parent=NULL;
    int i,j;
	sol->parent=NULL;
    while(temp!=NULL){
        parent=temp->parent;
        temp->parent=sol;
        sol=temp;
        temp=parent;
    }

	printf("Arxiki\n");
    temp=head;
    while(temp!=NULL){
		printf("va8os=%d h=%d\n",temp->depth,temp->h);
        for(i=0;i<N;i++){
            printf("\n");
            for(j=0;j<N;j++){
                printf("%c ",temp->state[i][j]);
            }
        }
		printf("\n\n");
        temp=temp->parent;
    }
}

/////////////////////////////isfinal/////////////////////////////


int isFinal(struct list *temp){
    int i,j;
    for(i=0;i<N;i++){
        if(temp->state[0][i]!='R' && temp->state[0][i]!='r'){
            return(0);
        }
    }
    for(i=0;i<N;i++){
        if(temp->state[1][i]!='G' && temp->state[1][i]!='g'){
            return(0);
        }
    }
    for(i=0;i<N;i++){
        if(temp->state[2][i]!='B' && temp->state[2][i]!='b'){
            return(0);
        }
    }
    for(i=0;i<N;i++){
        if(temp->state[3][i]!='Y' && temp->state[3][i]!='y'){
            return(0);
        }
    }
    return(1);
}
/*
Metrame ta la8os grammata sta tetragwna. Ean 8ewrhsoyme oti me ka8e kinish diorthwnetai ena la8os
xwris na dimhioyrghtai ena kainourio tote xreiazomaste toylaxiston toses kinhseis osa kai ta la8h.
Omws se ka8e kinhsh mporoyme na diorthwsoyme mexri 4 la8h.
Diaroume ton ari8mo twn la8wn me to 4.
Einai apodekth h eyretikh giati
1. dinei 0 gia telikh
2. dinei >0 gia alles katastaseis
3. einai ypoektimhsh ka8ws thn exoyme ypologizei gia thn kalyterh periptwsh, otan dld diorthwnei
    4 la8h mazi kai den prokyptoyn alla nea
*/
int h(struct list *temp){
    int i,counter=0;

    for(i=0;i<N;i++){
        if(temp->state[0][i]!='R' && temp->state[0][i]!='r'){
            counter++;
        }
    }
    for(i=0;i<N;i++){
        if(temp->state[1][i]!='G'&& temp->state[1][i]!='g'){
            counter++;
        }
    }
    for(i=0;i<N;i++){
        if(temp->state[2][i]!='B'&& temp->state[2][i]!='b'){
            counter++;
        }
    }
    for(i=0;i<N;i++){
        if(temp->state[3][i]!='Y'&& temp->state[3][i]!='y'){
            counter++;
        }
    }

    return(counter/N);
}
/////////////////////////////////begin////////////////////////////////
struct list *begin(){
    int i,j;
    char c,c1;
    int counter[N];
    struct list *temp;
    temp=(struct list *)malloc(sizeof(struct list));
    if(temp==NULL){
        printf("Error allocating memory\n");
        exit(0);
    }
    for(i=0;i<N;i++){
        counter[i]=0;
    }
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            do{
                printf("state[%d][%d]= ",i,j);
                
                c=getc(stdin);
                c1=getc(stdin);
            }while(!isValid(c,counter));
            temp->state[i][j]=c;
        }
    }
	
	/*for(i=0;i<N;i++){
		temp->state[0][i]='r';
		temp->state[1][i]='g';
		temp->state[2][i]='b';
		temp->state[3][i]='y';
	}
	temp->state[1][0]='r';
	temp->state[2][0]='g';
	temp->state[3][0]='b';
	temp->state[0][0]='y';
	*/
    temp->parent=NULL;
    temp->h=h(temp);
    temp->depth=0;
    temp->next=NULL;
    temp->isDeleted=0;
}
///////////////////////////////isvalid/////////////////////////
int isValid(char c,int counter[N]){
    if((c=='R' || c=='r') && counter[0]<N){
        counter[0]++;
        return(1);
    }
    if((c=='G' || c=='g') && counter[1]<N){
        counter[1]++;
        return(1);
    }
    if((c=='B' || c=='b') && counter[2]<N){
        counter[2]++;
        return(1);
    }
    if((c=='Y' || c=='y') && counter[3]<N){
        counter[3]++;
        return(1);
    }


    return(0);
}
///////////////////////////findnext/////////////////////////
struct list *findNext(){
    struct list *temp=head,*found=NULL;
    while(temp->isDeleted==1){
        temp=temp->next;
    }
    found=temp;
    
    while(temp!=NULL){
        if(temp->isDeleted==0){
            if(temp->depth+temp->h<found->depth+found->h){
                found=temp;
            }
        }
        temp=temp->next;
    }
    
    found->isDeleted=1;
    return(found);
}
//////////////////////////aastro//////////////////////////////////
void aastro(){
    struct list *node,*node1;
    int i;

    while(1){
        node=findNext();
        
        if(isFinal(node)){
            break;
        }
        for(i=0;i<2*N;i++){
            node1=newNode(i,1,node);    
            insert(node1);
        }
        for(i=0;i<2*N;i++){
            node1=newNode(i,-1,node);
            insert(node1);
        }
    }
    print(node);
}
