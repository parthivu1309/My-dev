//Tic Tac Toe Project
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>


#define n 3


int in=1;
int num;
int count=0;
int board[3][3] = {
    {-1,-2,-3},
    {-4,-5,-6},
    {-7,-8,-9}
};
int duplicate[3][3]= {
    {1,2,3},{4,5,6},{7,8,9}
};


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void frontend() {
    char display[n][n];
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(board[i][j]==1) {
                display[i][j]='x';
            }
            else if(board[i][j]==0) {
                display[i][j]='o';
            }
            else {
                display[i][j]=duplicate[i][j]+48;
            }
        }
    }


    //for displaying
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            printf("%c ",display[i][j]);
        }
        printf("\n");
    }
}
int read() {


    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(duplicate[i][j] == num) {
                break;
            }
        }
        if(j<n) break;
    }
    if(board[i][j]==1||board[i][j]==0) {
        printf("\033[31mThis element is already taken\033[0m\nplease give the valid input");
        return 0;
    }
    else {
        if(count%2) {
            board[i][j]=1;
        }
        else {
            board[i][j]=0;
        }
        return 1;
    }


    return -1;//for safe case
}


int checkWinner() {


    int i,j;


    // check rows
    for(i=0; i<n; i++) {
        int same = 1;
        for(j=1; j<n; j++) {
            if(board[i][j] != board[i][j-1]) {
                same = 0;
                break;
            }
        }
        if(same) return 1;
    }


    // check columns
    for(j=0; j<n; j++) {
        int same = 1;
        for(i=1; i<n; i++) {
            if(board[i][j] != board[i-1][j]) {
                same = 0;
                break;
            }
        }
        if(same) return 1;
    }


    // main diagonal
    int same = 1;
    for(i=1; i<n; i++) {
        if(board[i][i] != board[i-1][i-1]) {
            same = 0;
            break;
        }
    }
    if(same) return 1;


    // anti diagonal
    same = 1;
    for(i=1; i<n; i++) {
        if(board[i][n-i-1] != board[i-1][n-i]) {
            same = 0;
            break;
        }
    }
    if(same) return 1;


    // draw
    if(count == n*n) {
        printf("This game is draw\n");
        printf("Thanks for playing\n");
        printf("This game is made by PARTHIV UPADHYAY");
        return 0;
    }


    return 0;
}




int main() {


    printf("Hello,Welcome to this game\nWrite start to start the game\n");
    char str[10];
    char name1[30];
    char name2[30];


    scanf("%s",str);
    if(strcmp(str,"start")==0) {
        printf("This game is tic tac toe.\nTheir is two user user1 and user2 who play this game.\n");
        printf("User1 please enter your name :");
        scanf(" %s",name1);
        printf("User2 please enter your name :");
        scanf(" %s",name2);
        printf("%s can only enter 'o'\n",name1);
        printf("%s can only enter 'x'\n",name2);


        while(1) {
            frontend();
            if(count%2) {
                printf("%s which block you want to fill\n",name2);
                scanf("%d",&num);
                if(num>0&&num<10) {
                    if(read()) {
                        count++;
                    }


                    if(checkWinner()) {
                        printf("\033[1;35m %s Wins the Game! \033[0m\n", name2);
                        printf("Thanks for playing\n");
                        printf("This game is made by PARTHIV UPADHYAY");
                        break;
                    }
                    else {
                        continue;
                    }


                }
                else {
                    printf("\033[31minvalid input\033[0m\ngive the vaid input\n");
                    clearBuffer();
                }
            }
            else {
                printf("%s which block you want to fill\n",name1);
                scanf("%d",&num);
                if(num>0&&num<10) {
                    if(read()) {
                        count++;
                    }


                    if(checkWinner()) {
                        printf("\033[1;35m %s Wins the Game! \033[0m\n", name1);
                        printf("Thanks for playing\n");
                        printf("This game is made by PARTHIV UPADHYAY");
                        break;
                    }
                    else {
                        continue;
                    }


                }
                else {
                    printf("\033[31minvalid input\033[0m\ngive the valid input\n");
                    clearBuffer();


                }
            }


        }
    }


    else {
        printf("\033[31minvalid input\033[0m\nyou must write start to start the game");
    }


    return 0;
}