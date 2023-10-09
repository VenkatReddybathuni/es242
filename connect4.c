#include <stdio.h>
#include <assert.h>


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
    for (int col = 0; col < 5; ++col) {
        for (int row = 0; row < 4; ++row) {
            if (board[row][col] != player) {
                goto next_row;
            }
        }
        return 1;
    next_row:
    }
    for (int row = 0; row < 4; ++row) {
        int k=0;
        for (int col = 0; col < 5; ++col) {
            if (board[row][col] == player) {
                k+=1;
            }
            else{
                k--;
            }
        }
        if(k==4){
            return 1;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (board[i][i] != player) goto next_diagonal1;
    }
    return 1;
    next_diagonal1:
    for (int i = 0; i < 4; ++i) {
        if (board[i][i+1] != player) goto next_diagonal2;
    }
    return 1;
next_diagonal2:
    for (int i = 0; i < 4; ++i) {
        if (board[i][4-1-i] != player) goto next_diagonal3;
    }
    return 1;
next_diagonal3:
    for (int i = 0; i < 4; ++i) {
        if (board[i][4-2-i] != player) return 0;
    }
    return 1;

}

int is_full(board_t board)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if(board[row][col]!=EMPTY){
                return 0;
            }
        }
    }
    return 1;
}
player_t other_player(player_t player)
{
    switch (player) {
    case RED: return BLUE;
    case BLUE: return RED;
    }
}
typedef struct {
    int col;
    int score;
} move_t;
void print_board(board_t board)
{
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            printf("%d  ",board[i][j]);
        }
        printf("\n");
    }
}

void init_board(board_t board){
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            board[i][j]=EMPTY;
        }
    }
}
void addto_col(board_t board,int col,player_t player){
    for(int i=3;i>=0;i--){
        if(board[i][col]==EMPTY){
            board[i][col]=player;
            break;
        }
    }
    return;
}
void rem_col(board_t board,int col){
    for(int i=0;i<4;i++){
        if(board[i][col]!=EMPTY){
            board[i][col]=EMPTY;
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
    // printf("Analyzing board.\n");
    // printf("===============.\n");
    // print_board(board);
    // printf("===============.\n");
    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));
    for(int col=0;col<5;col++){
        if(board[0][col]==EMPTY){
            addto_col(board,col,player);
            if (has_won(board,player)){
                rem_col(board,col);
                return (move_t){
                    .col=col,
                    .score=1
                };
            }
            rem_col(board,col);
        }
    }
    for(int col=0;col<5;col++){
        if(board[0][col]==EMPTY){
            addto_col(board,col,player);
            if(is_full(board)){
                rem_col(board,col);
                return (move_t){
                  .col=col,
                  .score=0
                };
            }
            response = best_move(board, other_player(player));
            rem_col(board,col);
            if (response.score == -1) {
                    return (move_t) {
                        .col = col,
                        .score = 1
                    };
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
        return candidate;
}
int main()
{
    int move;
    board_t board;
    move_t response;
    player_t current = RED;
    init_board(board);
    while (1) {
        print_board(board);
        printf("------------------------\n");
        if (current == RED) {
            printf("Enter your move: ");
            scanf("%d", &move);
            addto_col(board,move,current);
        } else {
            response = best_move(board, current);
            addto_col(board,response.col,current);
        }
        if (has_won(board, current)) {
            print_board(board);
            printf("Player %d has won!\n", current);
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