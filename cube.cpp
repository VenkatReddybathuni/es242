#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <array>
#include <algorithm>
#include <tuple>
#include "queue.hpp"
#define SIZE 132269747
#define maxi (20005000)
enum move { R = 1, U = 2, F = 3, Ra = 4, Ua = 5, Fa = 6, R2 = 7, U2 = 8, F2 =  9 };
struct board {
    int e[8];
};
struct cube
{
    char e[6][4];
};
struct cubelet{
    char e[8][3];
};
struct cubelets1{
    char e[24][3];    
};
long ord(const board& board)
{
    long a = 0;
    for (int i=0;i<8;i++){
        if (i==6){continue;}
        a=((a*21)+board.e[i]);
    }
    return a;
}

void print_board(const board& b)
{
    for (int r = 0; r < 8; ++r) {
            printf("%d ", b.e[r]);
        }
}

void print_board1(const cube &c){
    for (int i=0;i<6;i++){
        for (int j=0;j<4;j++){
            printf("%c ", c.e[i][j]);
        }
        printf("\n");
    }
    printf("--------\n");
}
void read_board(board& b)
{
    for (int r = 0; r < 8; ++r) {
            scanf("%d", &b.e[r]);
    }
}
void read_board1(cube& c){
    for (int i=0;i<6;i++){
        for (int j=0;j<4;j++){
            scanf(" %c",&c.e[i][j]);
        }
    }
}

char find_opp(char side){
    switch (side)
    {
    case 'y':return 'w';break;
    case 'w':return 'y';break;
    case 'o':return 'r';break;
    case 'g':return 'b';break;
    case 'r':return 'o';break;
    case 'b':return 'g';break;
    default:
    return '0';
        break;
    }
}

cube destination(const cube &c){
    cube temp;
    for (int i=0;i<4;i++){
        temp.e[3][i]=c.e[3][2];
        temp.e[2][i]=c.e[2][3];
        temp.e[5][i]=c.e[5][2];
    }
    for (int i=0;i<4;i++){
        temp.e[0][i]=find_opp(temp.e[2][0]);
        temp.e[1][i]=find_opp(temp.e[3][0]);
        temp.e[4][i]=find_opp(temp.e[5][0]);
    }
    return temp;
}
void swap1(char *str, int i, int j) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}

cubelets1 template_cubelet(cube& c){
    cubelets1 c1;
    char temp1[3];
    c1.e[0][0]=c.e[0][0];
    c1.e[0][1]=c.e[3][1];
    c1.e[0][2]=c.e[4][2];
    c1.e[3][0]=c.e[0][2];
    c1.e[3][1]=c.e[5][0];
    c1.e[3][2]=c.e[3][3];

    c1.e[6][0]=c.e[1][0];
    c1.e[6][1]=c.e[0][1];
    c1.e[6][2]=c.e[4][3];
    c1.e[9][0]=c.e[1][2];
    c1.e[9][1]=c.e[5][1];
    c1.e[9][2]=c.e[0][3];

    c1.e[12][0]=c.e[2][0];
    c1.e[12][1]=c.e[1][1];
    c1.e[12][2]=c.e[4][1];
    c1.e[15][0]=c.e[2][2];
    c1.e[15][1]=c.e[5][3];
    c1.e[15][2]=c.e[1][3];

    c1.e[18][0]=c.e[3][0];
    c1.e[18][1]=c.e[2][1];
    c1.e[18][2]=c.e[4][0];
    c1.e[21][0]=c.e[3][2];
    c1.e[21][1]=c.e[5][2];
    c1.e[21][2]=c.e[2][3];
    for (int i=1;i<24;i++){
        if (i%3==0){
            continue;
        }
        for(int j=0;j<3;j++){
            temp1[j]=c1.e[i-1][j];
        }
        swap1(temp1,0,2);
        swap1(temp1,1,2);
        for (int j=0;j<3;j++){
            c1.e[i][j]=temp1[j];
        }
    }
    return c1;
}

cubelet convert_to_cubelet(const cube &c){
    cubelet c1;
    c1.e[0][0]=c.e[0][0];
    c1.e[0][1]=c.e[3][1];
    c1.e[0][2]=c.e[4][2];
    c1.e[2][0]=c.e[0][2];
    c1.e[2][1]=c.e[5][0];
    c1.e[2][2]=c.e[3][3];

    c1.e[1][0]=c.e[1][0];
    c1.e[1][1]=c.e[0][1];
    c1.e[1][2]=c.e[4][3];
    c1.e[3][0]=c.e[1][2];
    c1.e[3][1]=c.e[5][1];
    c1.e[3][2]=c.e[0][3];

    c1.e[5][0]=c.e[2][0];
    c1.e[5][1]=c.e[1][1];
    c1.e[5][2]=c.e[4][1];
    c1.e[7][0]=c.e[2][2];
    c1.e[7][1]=c.e[5][3];
    c1.e[7][2]=c.e[1][3];

    c1.e[4][0]=c.e[3][0];
    c1.e[4][1]=c.e[2][1];
    c1.e[4][2]=c.e[4][0];
    c1.e[6][0]=c.e[3][2];
    c1.e[6][1]=c.e[5][2];
    c1.e[6][2]=c.e[2][3];
    return c1;
}
int compare(char a[],char b[]){
    for (int j=0;j<3;j++){
        if (a[j]!=b[j]){
            return 0;
        }
    }
    return 1;
}
int search(char a[],const cubelets1 &dic){
    char temp2[3];
    for (int j=0;j<24;j++){
        for (int t=0;t<3;t++){
            temp2[t]=dic.e[j][t];
        }
        if (compare(a,temp2)==1){
            return j;
        }
    }
    return -1;
}
board convert_to_board(cubelet &c1,const cubelets1 &dic){
    board b;
    char temp[3];
    for (int i=0;i<8;i++){
        for(int j=0;j<3;j++){
            temp[j]=c1.e[i][j];
        }
        b.e[i]=search(temp,dic);
    }
    return b;
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

int helper(int k){
    if ((k+1)%3==0){
        return (k-2);
    }
    return (k+1);
}
int helper2(int k){
    if ((k)%3==0){
        return(k+2);
    }
    return (k-1);
}

board Right(const board& b)
{
    board o = b;
    o.e[1]=(b.e[3]);
    o.e[3]=helper(b.e[7]);
    o.e[7]=helper(b.e[5]);
    o.e[5]=helper(b.e[1]);
    return o;
}

board Up(const board& b)
{
    board o = b;
    o.e[0]=b.e[1];
    o.e[1]=b.e[5];
    o.e[4]=b.e[0];
    o.e[5]=b.e[4];
    return o;
}

board Front(const board& b)
{
    board o = b;
    o.e[0]=b.e[2];
    o.e[1]=helper(b.e[0]);
    o.e[2]=helper(b.e[3]);
    o.e[3]=helper(b.e[1]);
    return o;
}
board Right_a(const board& b){
    board o =b;
    o.e[1]=(helper2(b.e[5]));
    o.e[3]=(b.e[1]);
    o.e[7]=helper2(b.e[3]);
    o.e[5]=helper2(b.e[7]);
    return o;

}
board Up_a(const board& b){
    board o = b;
    o.e[0]=b.e[4];
    o.e[1]=b.e[0];
    o.e[4]=b.e[5];
    o.e[5]=b.e[1];
    return o;
}
board Front_a(const board& b){
    board o = b;
    o.e[0]=helper2(b.e[1]);
    o.e[1]=helper2(b.e[3]);
    o.e[2]=(b.e[0]);
    o.e[3]=helper2(b.e[2]);
    return o;
}
board Right2(const board& b){
    board o1=Right(b);
    board o2 =Right(o1);
    return o2;
}
board Up2(const board& b){
    board o1=Up(b);
    board o2 =Up(o1);
    return o2;
}
board Front2(const board& b){
    board o1=Front(b);
    board o2 =Front(o1);
    return o2;
}
bool is_same(const board& a, const board &b)
{
    for (int r = 0; r < 8; ++r){
            if (a.e[r] != b.e[r]) return false;}
    return true;
}
struct DataItem { 
   int key;
   int parent[2];
   int move;
   struct DataItem* next;
};
struct DataItem* hashArray[SIZE]; 
int hashCode(long key) {
   return key % SIZE;
}
void insert(long key,long parent, int move ) {
   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->parent[0] = parent/SIZE;
   item->parent[1] = parent % SIZE;  
   item->key = key/SIZE;
   item->move=move;     
   int hashIndex = hashCode(key);
   if (hashArray[hashIndex]){
   item->next =hashArray[hashIndex];}
   hashArray[hashIndex] = item; 
}
int check(long key){
    int hashIndex=hashCode(key);
    struct DataItem* k=hashArray[hashIndex];
    while(k){
        if(k->key==key/SIZE){
            return 1;
        }
        k=k->next;
    }
    return 0;
}
struct DataItem* find(long key){
    int hashIndex=hashCode(key);
    struct DataItem* k=hashArray[hashIndex];
    while(k){
        if(k->key==key/SIZE){
            return k;
        }
        k=k->next;
    }
    assert(0);
}

std::vector<int> solve(const board& src,const board& dest)
{
    queue<board, maxi> q;

    enqueue(q, src);
    long ss=ord(src);

    while (!is_empty(q)) {
        board v = dequeue(q);
        long l = ord(v);
        if (is_same(v,dest)) {
            /* return the moves to get to u from src. */
            std::vector<int> moves;
            board c = v;
            long o=ord(c);
            while (!(o==ss)) {
                struct DataItem* m=find(o);
                moves.push_back(m->move);
                o= m->parent[0]*SIZE+ m->parent[1];
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board r = Right(v);
        board u = Up(v);
        board f = Front(v);
        board ra = Right_a(v);
        board ua = Up_a(v);
        board fa = Front_a(v);
        board r2 = Right2(v);
        board u2 = Up2(v);
        board f2 = Front2(v);
        
        long r_ord = ord(r);
        long u_ord = ord(u);
        long f_ord = ord(f);
        long ra_ord = ord(ra);
        long ua_ord = ord(ua);
        long fa_ord = ord(fa);
        long r2_ord = ord(r2);
        long u2_ord = ord(u2);
        long f2_ord = ord(f2);

        if (!check(r_ord)) {
            insert(r_ord,l,R);
            enqueue(q, r);
        }
        if (!check(u_ord)) {
            insert(u_ord,l,U);
            enqueue(q, u);
        }
        if (!check(f_ord)) {
            insert(f_ord,l,F);
            enqueue(q, f);
        }
        if (!check(ra_ord)) {
            insert(ra_ord,l,Ra);
            enqueue(q, ra);
        }
        if (!check(ua_ord)) {
            insert(ua_ord,l,Ua);
            enqueue(q, ua);
        }
        if (!check(fa_ord)) {
            insert(fa_ord,l,Fa);
            enqueue(q, fa);
        }
        if (!check(r2_ord)) {
            insert(r2_ord,l,R2);
            enqueue(q, r2);
        }
        if (!check(u2_ord)) {
            insert(u2_ord,l,U2);
            enqueue(q, u2);
        }
        if (!check(f2_ord)) {
            insert(f2_ord,l,F2);
            enqueue(q, f2);
        }
        
    }
    printf("Not solvable \n");
    assert(0);
}
void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case R : printf("R "); break;
        case U : printf("U "); break;
        case F : printf("F "); break;
        case Ra: printf("R' "); break;
        case Ua: printf("U' "); break;
        case Fa: printf("F' "); break;
        case R2: printf("R2 "); break;
        case U2: printf("U2 "); break;
        case F2: printf("F2 "); break;
        }
    }
    printf("\n");
}
int main()
{
    cube src;
    read_board1(src);
    cube dest =destination(src);
    cubelets1 temp = template_cubelet(dest);
    cubelet c1=convert_to_cubelet(src);
    cubelet c2 = convert_to_cubelet(dest);
    board b1=convert_to_board(c1,temp);
    board b2=convert_to_board(c2,temp);
    auto moves = solve(b1, b2);
    print_moves(moves);

    return 0;
}