#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 8

int value(int state[2*N-1]);
int costos(int target,int state[2*N-1]);
void begin(int state[2*N-1]);
void printState(int state[2*N-1]);
void newState(int old[2*N-1],int new[2*N-1]);
void simulatedAnnealing(int state[2*N-1],int target);
///////////////////////main////////////////////////////////////////////////
main()
{
    int target;
    int state[2*N-1],i;
    srand(time(NULL));
    
    begin(state);
   /* for(i=0;i<2*N-1;i++){
        if(i%2==1){
        
            state[i]='+';
    }
    }
    state[1]='-';*/
    
    //begin(state);
    
    printState(state);

    
    printf("Stoxos= ");
    scanf("%d",&target);

    printState(state);

    simulatedAnnealing(state,target);

    printState(state);
    
    system("pause");

    //return 0;
}



///////////////////////////  value  //////////////////////////////


int value(int state[2*N-1]){
    int val=0,i,flag=-2;
    int num=0;

	num=state[0];
	val=0;
	flag=0;
	for(i=1;i<2*N-2;i+=2){
		if(state[i]==-1){
			num=num*10+state[i+1];
		}
		else if(state[i]=='+'){
			if(flag==0){
				val=num;
			}
			else{
				
				val=val+num*flag;
				
			}	
			num=state[i+1];
			flag=1;			
		}
		else if(state[i]=='-'){
			if(flag==0){
				val=num;
			}
			else{
				
				val=val+num*flag;
				
			}
			num=state[i+1];
			flag=-1;			
		}
	}
	//num=num*10+state[2*N-2];
	if(flag==0){
		val=num;
	}
	else{
		val=val+flag*num;
    }
	return(val);
}

int costos(int target,int state[2*N-1]){
    return(abs(target-value(state)));
}
/////////////////////  begin  /////////////////////////////
void begin(int state[2*N-1]){
    int i;
    int eisodos,num;
    printf("*****************************************************************************\n");
    printf("Mporeite na dwsete 8 tixaious arithmous i na afisete to sistima na epilexei tixaia\n");
    printf("pieste 1 gia na epileksete eseis i 2 gia tixaia epilogi:");
    scanf("%d",&eisodos);
    if(eisodos==1){
        for(i=0;i<2*N-1;i++){
            if(i%2==1){
             state[i]=-1;
            }
        else{
             printf("dwste arithmo\n");
             scanf("%d",&state[i]);
             
        }
    }         
                   
    }else{

    for(i=0;i<2*N-1;i++){
        if(i%2==1){
            state[i]=-1;
        }
        else{
            state[i]= (rand()%10);
        }
    }
}
}


//////////////////////  printState  //////////////////////////////////

void printState(int state[2*N-1]){
    int i;

    for(i=0;i<2*N-1;i++){
        if(state[i]>-1 && state[i]<10){
            printf("%c",'0'+ state[i]);
        }
        else if(state[i]!=-1){
            printf("%c",state[i]);

        }
    }
    printf("=%d\n",value(state));
}

/////////////////////////////    newState   ///////////////////////////////

void newState(int old[2*N-1],int new[2*N-1]){
    int i,s,j;

    for(i=0;i<2*N-1;i++){
        new[i]=old[i];
    }

    i=rand()%(N-1);


    do{
        j=rand()%3;
        if(j==0){
            s=-1;
        }
        else if(j==1){
            s='+';
        }
        else{
            s='-';
        }
    }while(old[2*i+1]==s);

    new[2*i+1]=s;

}
/////////////////////////////// simulatedAnnealing  ///////////////////////////


void simulatedAnnealing(int state[2*N-1],int target){
    int new[2*N-1];
    int tries=0;
    int dc,i,j,flag=0;

    int fail=0;
    float T=10.0,p;

    while(fail<9*N){
        for(i=0;i<3*N;i++){
            if(costos(target,state)==0){
                flag=1;
                break;
            }
            newState(state,new);

            dc=costos(target,new)-costos(target,state);
            if(dc<=0){
                fail=0;
                for(j=0;j<2*N-1;j++){
                    state[j]=new[j];
                }
            }
            else{
                p=exp(-dc/T);
                if(rand()/(float)RAND_MAX < p){
                    fail=0;
                    for(j=0;j<2*N-1;j++){
                        state[j]=new[j];
                    }
                }
                else{
                    fail++;
                }
            }
        }

        printf("fails %d  T %f   ",fail,T);
        printState(state);
        if(flag==1){
            break;
        }
        T=T*0.999;
    }
}
