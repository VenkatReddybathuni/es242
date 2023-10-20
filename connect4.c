#include <stdio.h>
#include <assert.h>
#include <stdint.h>

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

int has_won(board_t board, player_t player)
{
    for(int col = 0; col < 5; col++){
        if(board[0][col] == player &&
           board[1][col] == player &&
           board[2][col] == player &&
           board[3][col] == player) return 1;  
    }

    for(int i = 0; i < 2; i++){
        for(int row = 0; row < 4; row++){
            if(board[row][0+i] == player &&
           board[row][1+i] == player &&
           board[row][2+i] == player &&
           board[row][3+i] == player ) return 1;  
        }
    }

    for(int i = 0; i < 2; i++){
        if(board[0][0+i] == player &&
           board[1][1+i] == player &&
           board[2][2+i] == player &&
           board[3][3+i] == player) return 1;
    }

    for(int i = 0; i < 2; i++){
        if(board[3][0+i] == player &&
           board[2][1+i] == player &&
           board[1][2+i] == player &&
           board[0][3+i] == player) return 1;
    }
    return 0;
}
typedef struct {
    int row;
    int col;
    int score;
} move_t;
#define MAX_ORD (28629151*2)

uint8_t computed_moves[MAX_ORD+1];

uint8_t encode_move(move_t m)
{
    uint8_t b = 0;
    assert(0 <= m.row && m.row <= 3);
    b |= m.row;
    assert(0 <= m.col && m.col <= 4);
    b |= m.col << 2;

    switch (m.score) {
    case -1: b |= 1 << 7; break;
    case 0: b |= 1 << 6; break;
    case 1: b |= 1 << 5; break;
    }

    return b;
}
move_t decode_move(uint8_t b)
{
    move_t m;

    m.row = b & 0x3;
    m.col = (b & 0x1C) >> 2;
    if (b & 0x20) m.score = 1;
    if (b & 0x40) m.score = 0;
    if (b & 0x80) m.score = -1;
    return m;
}
int colord(board_t board, int col){
    if(board[3][col]=='.'){
        return 0;
    }
    else if(board[2][col]=='.'){
        if(board[3][col]=='R'){
            return 1;
        } else{
            return 2;
        }
    }
    else if(board[1][col]=='.'){
        if(board[3][col]=='R'){
            if(board[2][col]=='R'){
                return 3;
            }
            else{
                return 4;
            }
        }
        else{
            if(board[2][col]=='R'){
                return 5;
            }
            else{
                return 6;
            }
        }
    }
    else if(board[0][col]=='.'){
        if(board[3][col]=='R' && board[2][col]=='R'){
            if(board[1][col]=='R'){
                return 7;
            }
            else{
                return 8;
            }
        }
        if(board[3][col]=='R' && board[2][col]=='B'){
            if(board[1][col]=='R'){
                return 9;
            }
            else{
                return 10;
            }
        }
        if(board[3][col]=='B' && board[2][col]=='R'){
            if(board[1][col]=='R'){
                return 11;
            }
            else{
                return 12;
            }
        }
        if(board[3][col]=='B' && board[2][col]=='B'){
            if(board[1][col]=='R'){
                return 13;
            }
            else{
                return 14;
            }
        }
    }
    else {
        if(board[3][col]=='R' && board[2][col]=='R'){
            if(board[1][col]=='R' && board[0][col]=='R'){
                return 15;
            }
            else if(board[1][col]=='R' && board[0][col]=='B'){
                return 16;
            }
            else if(board[1][col]=='B' && board[0][col]=='R'){
                return 17;
            }
            else{
                return 18;
            }
        }
        if(board[3][col]=='R' && board[2][col]=='B'){
            if(board[1][col]=='R' && board[0][col]=='R'){
                return 19;
            }
            else if(board[1][col]=='R' && board[0][col]=='B'){
                return 20;
            }
            else if(board[1][col]=='B' && board[0][col]=='R'){
                return 21;
            }
            else{
                return 22;
            }
        }
        if(board[3][col]=='B' && board[2][col]=='R'){
            if(board[1][col]=='R' && board[0][col]=='R'){
                return 23;
            }
            else if(board[1][col]=='R' && board[0][col]=='B'){
                return 24;
            }
            else if(board[1][col]=='B' && board[0][col]=='R'){
                return 25;
            }
            else{
                return 26;
            }
        }
        if(board[3][col]=='B' && board[2][col]=='B'){
            if(board[1][col]=='R' && board[0][col]=='R'){
                return 27;
            }
            else if(board[1][col]=='R' && board[0][col]=='B'){
                return 28;
            }
            else if(board[1][col]=='B' && board[0][col]=='R'){
                return 29;
            }
            else{
                return 30;
            }
        }
    }
}
long ord(board_t board)
{
    long i=0;
    i=(colord(board,4)*1)+(colord(board,3)*31)+(colord(board,2)*31*31)+(colord(board,1)*31*31*31)+(colord(board,0)*31*31*31*31);
    return i;
}

int is_full(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if(board[row][col]=='.'){
                return 0;
            }
        }
    }
    return 1;
}
player_t other_player(player_t player)
{
    if(player == 'R') return 'B';
    else return 'R';
}

void print_board(board_t board)
{
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 5; col++){
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

void init_board(board_t board){
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            board[i][j]='.';
        }
    }
}
void addto_col(board_t board,int col,player_t player){
    for(int i=3;i>=0;i--){
        if(board[i][col]=='.'){
            board[i][col]=player;
            break;
        }
    }
    return;
}
void rem_col(board_t board,int col){
    for(int i=0;i<4;i++){
        if(board[i][col]!='.'){
            board[i][col]='.';
            break;
        }
    }
    return;
}
move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;
    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));
    long o = ord(board);
    if (computed_moves[o]) {
        return decode_move(computed_moves[o]);
    }
    for(int col=0;col<5;col++){
        if(board[0][col]=='.'){
            addto_col(board,col,player);
            if (has_won(board,player)){
                rem_col(board,col);
                int row=0;
                for(int i=0;i<4;i++){
                    if(board[i][col]!='.'){
                        row=i;
                        break;
                    }
                }
                computed_moves[o] = encode_move(candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 1
                        });
                return candidate;
            }
            rem_col(board,col);
        }
    }
    for(int col=0;col<5;col++){
        if(board[0][col]=='.'){
            addto_col(board,col,player);
            if(is_full(board)){
                rem_col(board,col);
                int row=0;
                for(int i=0;i<4;i++){
                    if(board[i][col]!='.'){
                        row=i;
                        break;
                    }
                }
                computed_moves[o] = encode_move(candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 0
                        });
                    return candidate;
            }
            response = best_move(board, other_player(player));
            rem_col(board,col);
            int row=0;
            for(int i=0;i<4;i++){
                    if(board[i][col]!='.'){
                        row=i;
                        break;
                    }
                }
            if (response.score == -1) {
                computed_moves[o] = encode_move(candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 1
                        });
                    return candidate;
                } else if (response.score == 0) {
                    candidate = (move_t) {
                        .col = col,
                        .score = 0
                    };
                    no_candidate = 0;
                } else { /* response.score == +1 */
                    if (no_candidate) {
                        candidate = (move_t) {
                            .col = col,
                            .score = -1
                        };
                        no_candidate = 0;
                    }
                }
            }
        }
    computed_moves[o] = encode_move(candidate);
    return candidate;
}
int main()
{
    int move;
    board_t board;
    move_t response;
    player_t current;
    player_t pl;
    printf("Enter: 'R' for player 1 or 'B' for player 2:\n");
    scanf("%c", &current);
    pl=current;
    init_board(board);
    while (1) {
        print_board(board);
        printf("------------------------\n");
        if (current == 'R') {
            printf("Enter your move: ");
            scanf("%d", &move);
            addto_col(board,move,current);
        } else{
            response = best_move(board, current);
            printf("Computer move: %d\n",response.col);
            addto_col(board,response.col,current);
        }
        if (has_won(board, current)) {
            print_board(board);
            if(current=='R'){
                printf("You won!!\n");
            }
            else{
                printf("Computer won\n");
            }
            break;
        } else if (is_full(board)) {
            print_board(board);
            printf("Draw.\n");
            break;
        }
        current = other_player(current);
        printf("------------------------\n");
    }
    return 0;
}