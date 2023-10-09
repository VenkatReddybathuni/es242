#include <stdio.h>
#include <assert.h>

enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */
player_t other_player(player_t player)
{
    switch (player) {
    case RED: return BLUE;
    case BLUE: return RED;
    default: assert(0);
    }
}


int is_full(board_t board)
{
    int p=1;
    for(int i=0;i<15;i++){
        if(board[i]==NO){
            p=0;
            return p;
        }
    }
    return p;
}
typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

int has_won(board_t board, player_t player)
{
    player_t pl2=other_player(player);
    int k=0;
    for(int j=0;j<4;j++){
        k+=(4-j);
        if(board[j]==pl2){
            
            for(int i=j+1;i<5;i++){
                
                if((board[i]==pl2)&&(board[i+k]==pl2)){
                    return 1;
                }
            }
        }
    }
    int l=0;
    for(int j=5;j<8;j++){
        l+=(8-j);
        if(board[j]==pl2){
            
            for(int i=j+1;i<9;i++){
                
                if((board[i]==pl2)&&(board[i+l]==pl2)){
                    return 1;
                }
            }
        }
    }
    int m=0;
    for(int j=9;j<11;j++){
        m+=(11-j);
        if(board[j]==pl2){
            
            for(int i=j+1;i<12;i++){
                
                if((board[i]==pl2)&&(board[i+m]==pl2)){
                    return 1;
                }
            }
        }
    }
    if((board[12]==pl2)&&(board[13]==pl2)){
        if(board[14]==pl2){
            return 1;
        }
    }
    return 0;
}
move_t best_move(board_t board, player_t player)
{   move_t candidate;
    move_t response;
    
    int c=100;
    candidate.score=-1;
    candidate.line=-1;
    for(int i=0; i<15;i++){
      if (board[i]!=0){
        continue;
      }
      board[i]=player;
      if (has_won(board,other_player(player))){
        board[i]=0;
        if (candidate.line==-1){
          candidate.line=i;
        }
        continue;
      }
      response=best_move(board, other_player(player));
      if (response.score<0){
        candidate.line=i;
        candidate.score=1-response.score;
        board[i]=0;
        return candidate;
      }
      else{
        int s=-1-response.score;
        if (s<c){
          candidate.score=s;
          c=s;
          candidate.line=i;
        }
      }
      board[i]=0;
    }
    return candidate;
}
void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        case NO: printf("N  ");break;
        }
    }
    printf("\n");
}
void init_board(board_t board){
    for(int i=0;i<15;i++){
        board[i]=NO;
    }
    return;
}   
int main() {
    board_t game;
    init_board(game);
    printf("Choose your player (1 for Red, 2 for Blue): ");
    int pl;
    int done=0;
    player_t current;
    player_t human;
    player_t computer;
    scanf("%d",&pl);
    if (pl==1){
        human =1;
        computer=2;
        current = human; 
    }
    else{
        human=2;
        computer=1; 
        current = computer; 
    }
    
    printf("Who should play first?\n");
    printf("Enter 1 for user\n");
    printf("Enter 2 for Computer\n");
    
    scanf("%d",&pl);
    
    if (pl==1){
        current=human;
    }
    else{
        current=computer;
    }
    
    while (!done) {
        if (current == human) {
            int userMove;
            printf("Your move (Enter a number between 0 and 14): ");
            scanf("%d", &userMove);
            
            game[userMove] = human;
        } else {
            move_t computerMove = best_move(game, computer);
            game[computerMove.line] = computer;
            printf("Computer's move: %d\n", computerMove.line);
        }
        
        print_board(game);
        
        if (has_won(game,human)) {
            printf("User has won!\n");
            done = 1;
            break;
        } 
        else if(has_won(game,computer)){
            printf("Computer has won!\n");
            done =1;
            break;
        }
        else if (is_full(game)) {
            printf("It's a draw!\n");
            done = 1;
            break;
        }
        
        current = other_player(current);
    }
    
    printf("Game over.\n");
    
    return 0;
}