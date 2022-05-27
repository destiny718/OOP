#include <iostream>
#include<cstring>
using namespace std;

struct Gra{
    char nam[201][21];
    int tim[201];
    int mem[201];
    bool check;
};
class Task{
    public:
    int d,n,m;
    char s[30];
        Task(char a[30],int D,int N,int M){
            d=N;n=M;m=D;
            strcpy(s,a);
        }
};
class Server{
    int n,m;
    public:
        Gra gra[101]={};
        Server(int N,int M):n(N),m(M){}
        void tick();
        bool submit_task(Task a);
        bool cancel_task(char a[30]);
};
void Server::tick(){
    for(int i=1;i<=n;++i){
        if(gra[i].check){
            int push_time=0;
            int push_flag[50]={1};
            for(int j=1;j<=gra[i].tim[0];j++){
                gra[i].tim[j]--;
                if(gra[i].tim[j]==0){
                    push_time++;
                    push_flag[push_time]=j;
                }    
            }
            if(push_time>0){
                for(int j=1;j<=push_time;j++){
                    gra[i].mem[0]-=gra[i].mem[push_flag[j]];
                    for(int k=push_flag[j];k<gra[i].tim[0];k++){
                        strcpy(gra[i].nam[k],gra[i].nam[k+1]);
                        gra[i].tim[k]=gra[i].tim[k+1];
                        gra[i].mem[k]=gra[i].mem[k+1];
                    }
                    for(int k=j;k<=push_time;++k){
                        push_flag[k]--;
                    }
                    gra[i].tim[gra[i].tim[0]]=0;
                    gra[i].mem[gra[i].tim[0]]=0;
                    memset(gra[i].nam[gra[i].tim[0]],0,sizeof(gra[i].nam[gra[i].tim[0]]));
                    gra[i].tim[0]--;
                }
            }
            if(gra[i].tim[0]==0){
                gra[i].check=false;
            }
        }
    }
}
bool Server::submit_task(Task a){
    //check graphics
    int free_gras=0;
    bool flags[101];
    for(int i=1;i<101;++i){
        flags[i]=false;
    }
    bool check_gras=false;
    for(int i=1;i<=n;++i){
        if((m-gra[i].mem[0])>=a.n){
            free_gras++;
            flags[i]=true;
        }   
        if(free_gras==a.d){
            check_gras=true;
            break;
        }
    }
    if(!check_gras)
        return false;     
    //submit task
    else{
        int times=0;
        for(int i=1;i<=n;++i){
            if(flags[i]){
                gra[i].tim[0]++;
                strcpy(gra[i].nam[gra[i].tim[0]],a.s);
                gra[i].tim[gra[i].tim[0]]=a.m;
                gra[i].mem[0]+=a.n;
                gra[i].mem[gra[i].tim[0]]=a.n;
                gra[i].check=true;
                times++;
            }
            if(times==a.d)  break;
        }
        return true;
    }
}
bool Server::cancel_task(char a[30]){
    //check task
    bool check_task=false;
    for(int i=1;i<=n;++i){
        bool break_or_not=false;
        for(int j=1;j<=gra[i].tim[0];j++){
            if(strcmp(gra[i].nam[j],a)==0){
                check_task=true;
                break_or_not=true;
                break;
            }  
        }
        if(break_or_not)    break;
    }
    if(!check_task)  return false;
    //cancel task
    else{
        for(int i=1;i<=n;++i){
            for(int j=1;j<=gra[i].tim[0];++j){
                if(strcmp(gra[i].nam[j],a)==0){
                    gra[i].mem[0]-=gra[i].mem[j];
                    for(int k=j;k<gra[i].tim[0];k++){
                        strcpy(gra[i].nam[k],gra[i].nam[k+1]);
                        gra[i].mem[k]=gra[i].mem[k+1];
                        gra[i].tim[k]=gra[i].tim[k+1];
                    }
                    gra[i].tim[gra[i].tim[0]]=0;
                    gra[i].mem[gra[i].tim[0]]=0;
                    memset(gra[i].nam[gra[i].tim[0]],0,sizeof(gra[i].nam[gra[i].tim[0]]));
                    gra[i].tim[0]--;
                }
            }
            if(gra[i].tim[0]==0){
                gra[i].check=false;
            }
        }
        return true;
    }
}
int main()
{
    int N;
    int M;
    cin >> N >> M;
    Server server(N, M);
    int o;
    cin >> o;
    int cur_time = 0;
    for(int i = 0; i < o; i++) 
    {
        int t, d, n, m;
        char o;
        char s[30];
        cin >> t >> o;
        scanf("%s", s);
        for (int j = 0; j < t - cur_time; j++)
            server.tick();
        cur_time = t;
        if(o == 's')
        {
            cin >> n >> m >> d;
            Task task(s, d, n, m);
            if(server.submit_task(task))
            {
                cout << "Accepted " << s << endl;
            }
            else
            {
                cout << "Rejected " << s << endl;
            }
        }
        else if(o == 'c')
        {
            if(server.cancel_task(s))
            {
                cout << "Cancelled " << s << endl;
            }
            else
            {
                cout << "Not found " << s << endl;
            }
        }
        else
        {
            cout << "Invalid operation" << endl;
        }
    }
    return 0;
}