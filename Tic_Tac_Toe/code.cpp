#include<iostream>
#include<vector>
using namespace std;


void printBoard(vector<vector<char>> &board)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<board[i][j]<<" | ";
        }
        cout<<endl;
        cout << "---+---+---" << endl;
    }
}

bool is_board_completely_filled(vector<vector<char>> &board)
{
    int emptyspots = 0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]=='*')
                emptyspots++;
        }
    }
    return emptyspots == 0;
}

bool check_win(vector<vector<char>> &board, char c)
{
    int d=0;
    for(int i=0;i<3;i++)
    {
        int row=0;
        for(int j=0;j<3;j++)
        {
            if(board[i][j]==c)
                row++;
        }
        if(row==3)
            return true;
    }
    for(int i=0;i<3;i++)
    {
        int col=0;
        for(int j=0;j<3;j++)
        {
            if(board[j][i]==c)
                col++;
        }
        if(col==3)
            return true;
    }
    
    for(int i=0;i<3;i++)
    {
        if(board[i][i]==c)
            d++;
    }
    if(d==3)
        return true;

    if(board[1][1] == c && board[1][1] == board[0][2] && board[0][2] == board[2][0])
        return true;
        
    return false;
    
}

pair<int,int> get_bot_move(vector<vector<char>> &board)
{
    pair<int,int> ans = {-1,-1};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[i][j]=='*')
            {
                ans.first = i;
                ans.second = j;
                break;
            }
        }
    }
    return ans;
}

void make_move(vector<vector<char>> &board, int i, int j, char c)
{
    board[i][j] = c;
    return;
}

pair<int,int> get_player_move(vector<vector<char>> &board, int player)
{
    int i,j;
    pair<int,int> ans = {-1,-1};
    while(true)
    {
        cout<<"Player "<<player<<"'s turn"<<endl;
        cout<<"Enter row and column between 0 and 2"<<endl;
        cin>>i;
        cin>>j;
        if(i<0 || j<0 || i>=3 || j>=3)
        {
            cout<<"Incorrect Input. Please make sure row and column values are between 0 and 2"<<endl;
        }
        else if(board[i][j]!='*')
        {
            cout<<"This spot is already filled. Please choose another spot"<<endl;
        }
        else
        {
            ans = {i,j};
            break;
        }
    }
    return ans;
    
}

void player_vs_player(vector<vector<char>> &board)
{
    int player = 1;
    int i,j;
    while(true)
    {
        
        get_player_move(board, player);
        
        make_move(board,i,j,(player-1)+'0');

        printBoard(board);

        if(check_win(board, (player-1)+'0'))
        {
            cout<<"Player "<<player<<" won."<<endl;
            break;
        }

        if(is_board_completely_filled(board))
        {
            cout<<"Game Over"<<endl;
            break;
        }
        
        player = player ^ 3;
        
    }
}

void player_vs_bot(vector<vector<char>> &board)
{
    int turn = 1;   // 1 means Player's turn and 0 means bot's turn
    int i,j;
    while(true)
    {
        if(turn == 1)
        {
            cout<<"Your Turn"<<endl;
            cout<<"Enter row and column between 0 and 2"<<endl;
            cin>>i;
            cin>>j;
        }
        else{
            cout<<"Bot's Turn"<<endl;
            pair<int,int> index = get_bot_move(board);
            i=index.first;
            j=index.second;
        }

        if(i>=0&&j>=0&&i<3&&j<3)
        {
            if(board[i][j]=='*')
            {
                make_move(board,i,j,turn + '0');
                printBoard(board);
                if(check_win(board, turn + '0'))
                {
                    if(turn)
                        cout<<"You won."<<endl;
                    else
                        cout<<"Bot Won!!!"<<endl;
                    break;
                }
                if(is_board_completely_filled(board))
                {
                    cout<<"Game Over"<<endl;
                    break;
                }
                turn  = 1-turn;
            }
            else
            {
                cout<<"This spot is already filled. Please choose another spot"<<endl;
            }
        }
        else
        {
            cout<<"Incorrect Input. Please make sure row and column values are between 0 and 2"<<endl;
        }
    }
}

int main()
{
    cout<<"Welcome to Tic Tac Toe"<<endl;
    vector<vector<char>> board(3,vector<char>(3,'*'));
    int choice;

    while(true)
    {
        cout<<"1. Play against Bot"<<endl;
        cout<<"2. Play against against another player"<<endl;
        cin>>choice;
        if(choice == 1 or choice == 2)
            break;
        cout<<"Please select correct mode from above options"<<endl;
    }

    if(choice == 2)
    {
        player_vs_player(board);
    }
    else
    {
        player_vs_bot(board);
    }
    
    
    return 0;
}               