#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>

#include "queue.hpp"
//0 for top, 
//1 for bottom, 
//2 for up, 
//3 for right, 
//4 for down, 
//5 for left, 
//6 for empty space
struct board {
    int e[3][3];
};
void print_board(const board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            printf("%3d", b.e[r][c]);
        }
        printf("\n");
    }
}
void read_board(board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            scanf("%d", &b.e[r][c]);
        }
    }
}
void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}
std::tuple<int, int> find_space(const board& b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (b.e[r][c] == 6) return { r, c };
    assert(0);
}
board up(const board& b)
{
    const auto [r, c] = find_space(b);
    if (r == 0) return b;
    board o = b;
    switch(o.e[r-1][c]){
        case 0: o.e[r-1][c]=4; break;
        case 1: o.e[r-1][c]=2; break;
        case 2: o.e[r-1][c]=0; break;
        case 3: o.e[r-1][c]=3; break;
        case 4: o.e[r-1][c]=1; break;
        case 5: o.e[r-1][c]=5; break;
        default: assert(0);
    }
    swap(o.e[r-1][c], o.e[r][c]);
    
    return o;
}
board down(const board& b)
{
    const auto [r, c] = find_space(b);
    if (r == 2) return b;
    board o = b;
    switch(o.e[r+1][c]){
        case 0: o.e[r+1][c]=2; break;
        case 1: o.e[r+1][c]=4; break;
        case 2: o.e[r+1][c]=1; break;
        case 3: o.e[r+1][c]=3; break;
        case 4: o.e[r+1][c]=0; break;
        case 5: o.e[r+1][c]=5; break;
        default: assert(0);
    }
    swap(o.e[r+1][c], o.e[r][c]);
    
    return o;
}
board left(const board& b)
{
    const auto [r, c] = find_space(b);
    if (c == 0) return b;
    board o = b;
    switch(o.e[r][c-1]){
        case 0: o.e[r][c-1]=3; break;
        case 1: o.e[r][c-1]=5; break;
        case 2: o.e[r][c-1]=2; break;
        case 3: o.e[r][c-1]=1; break;
        case 4: o.e[r][c-1]=4; break;
        case 5: o.e[r][c-1]=0; break;
        default: assert(0);
    }
    swap(o.e[r][c-1], o.e[r][c]);
    
    return o;
}
board right(const board& b)
{
    const auto [r, c] = find_space(b);
    if (c == 2) return b;
    board o = b;
    switch(o.e[r][c+1]){
        case 0: o.e[r][c+1]=5; break;
        case 1: o.e[r][c+1]=3; break;
        case 2: o.e[r][c+1]=2; break;
        case 3: o.e[r][c+1]=0; break;
        case 4: o.e[r][c+1]=4; break;
        case 5: o.e[r][c+1]=1; break;
        default: assert(0);
    }
    swap(o.e[r][c+1], o.e[r][c]);
    
    return o;
}
bool is_same(const board& a, const board &b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (a.e[r][c] != b.e[r][c]) return false;

    return true;
}
enum move { L = 1, R = 2, U = 3, D = 4 };
int ord(const board& board){
    int a=0;
    int k=1;
    for(int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            a+=(board.e[row][col]*k);
            k=k*7;
        }
    }
    return a;
}
/*
 * Return a shortest path from src to dest.
 */
#define maxi (40353608)
std::vector<int> solve(const board& src, const board& dest)
{
    queue<board, maxi> q;
    int visited[maxi];
    board parent[maxi];

    enqueue(q, src);
    visited[ord(src)] = L;

    while (!is_empty(q)) {
        board u = dequeue(q);
        if (is_same(u, dest)) {
            /* return the moves to get to u from src. */
            std::vector<int> moves;
            board c = u;
            int o = ord(c);
            while (!is_same(c, src)) {
                moves.push_back(visited[o]);
                c = parent[o];
                o = ord(c);
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = up(u);
        board b = down(u);
        board c = left(u);
        board d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);

        if (!visited[aord]) {
            visited[aord] = U;
            parent[aord] = u;
            enqueue(q, a);
        }
        if (!visited[bord]) {
            visited[bord] = D;
            parent[bord] = u;
            enqueue(q, b);
        }
        if (!visited[cord]) {
            visited[cord] = L;
            parent[cord] = u;
            enqueue(q, c);
        }
        if (!visited[dord]) {
            visited[dord] = R;
            parent[dord] = u;
            enqueue(q, d);
        }
    }
    printf("Not solvable\n");
    assert(0);
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case L: printf("L "); break;
        case R: printf("R "); break;
        case U: printf("U "); break;
        case D: printf("D "); break;
        }
    }
    printf("\n");
}

int main()
{
    board src, dest;
    // read_board(src);
    // read_board(dest);
    src.e[0][0] = 1;
    src.e[0][1] = 1;
    src.e[0][2] = 1;
    src.e[1][0] = 1;
    src.e[1][1] = 6;
    src.e[1][2] = 1;
    src.e[2][0] = 1;
    src.e[2][1] = 1;
    src.e[2][2] = 1;
    dest.e[0][0] = 0;
    dest.e[0][1] = 0;
    dest.e[0][2] = 0;
    dest.e[1][0] = 0;
    dest.e[1][1] = 6;
    dest.e[1][2] = 0;
    dest.e[2][0] = 0;
    dest.e[2][1] = 0;
    dest.e[2][2] = 0;
    auto moves = solve(src, dest);
    print_moves(moves);
    return 0;
}
