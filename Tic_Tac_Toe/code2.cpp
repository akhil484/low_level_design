#include<iostream>
#include<vector>
using namespace std;

class Board
{
    int size;
    vector<vector<char>> board;
    public:

        Board(int size)
        {
            this->size = size;
            board.resize(size, vector<char>(size, '*')); 
        }

        int get_size()
        {
            return this->size;
        }

        void print_board()
        {
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<this->size;j++)
                {
                    cout<<this->board[i][j]<<" | ";
                }
                cout<<endl;
                for(int j=0;j<this->size;j++)
                {
                    if(j==this->size-1)
                        cout<<"---"<<endl;
                    else
                        cout<<"---+";
                }
                
            }
        }

        void make_move(int i, int j, char c)
        {
            this->board[i][j] = c;
        }
        bool is_spot_filled(int i, int j)
        {
            return this->board[i][j] != '*';
        }

        bool check_win(char c)
        {
            int d=0;
            for(int i=0;i<size;i++)
            {
                int row=0;
                for(int j=0;j<size;j++)
                {
                    if(this->board[i][j]==c)
                        row++;
                }
                if(row==size)
                    return true;
            }
            for(int i=0;i<size;i++)
            {
                int col=0;
                for(int j=0;j<size;j++)
                {
                    if(this->board[j][i]==c)
                    {
                        col++;
                        if(i+j==size-1)
                        {
                            d++;
                        }
                    }
                }
                if(col==size)
                    return true;
            }
            if(d==size)
                return true;
            d = 0;
            for(int i=0;i<size;i++)
            {
                if(this->board[i][i]==c)
                    d++;
            }
            if(d==size)
                return true;
           
            
                
            return false;
            
        }

        bool is_board_completely_filled()
        {
            int emptyspots = 0;
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                {
                    if(this->board[i][j]=='*')
                        emptyspots++;
                }
            }
            return emptyspots == 0;
        }

        bool is_coordinates_valid(int i, int j)
        {
            if(i<0 || j<0 || i>=this->size || j>=this->size)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
};
class Player
{
    public:
    virtual void assign_symbol(char symbol, int id) = 0;
    virtual char get_symbol()=0;
    virtual int get_id()=0;
    virtual pair<int,int> get_move(Board *board) = 0;
    virtual ~Player()
    {
        cout<<"Player class Destructor called"<<endl;
    }
};

class Human: public Player
{
    public:
        char symbol;
        int id;
    
        void assign_symbol(char symbol, int id) override
        {
            this->symbol = symbol;
            this->id=id;
            cout<<"Symbol Assigned"<<endl;
        }

        char get_symbol()
        {
            return this->symbol;
        }
        int get_id()
        {
            return this->id;
        }

        pair<int,int> get_move(Board *board) override
        {
            int i,j;
            pair<int,int> ans = {-1,-1};
            while(true)
            {
                cout<<"Player "<<this->id<<"'s turn"<<endl;
                cout<<"Enter row and column between 0 and "<<board->get_size()-1<<endl;
                cin>>i;
                cin>>j;
                if(!board->is_coordinates_valid(i,j))
                {
                    cout<<"Incorrect Input. Please make sure row and column values are between "<<0<<" and "<<board->get_size()-1<<endl;
                }
                else if(board->is_spot_filled(i,j))
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

};


class Bot: public Player
{
    public:
        char symbol;
        int id;
    
        void assign_symbol(char symbol, int id) override
        {
            this->symbol = symbol;
            this->id=id;
        }
        char get_symbol()
        {
            return this->symbol;
        }
        int get_id()
        {
            return this->id;
        }

        pair<int,int> get_move(Board *board) override{
            pair<int,int> ans = {-1,-1};
            cout<<"Player "<<this->id<<"'s turn"<<endl;
            for(int i=0;i<board->get_size();i++)
            {
                for(int j=0;j<board->get_size();j++)
                {
                    if(!board->is_spot_filled(i,j))
                    {
                        ans.first = i;
                        ans.second = j;
                        break;
                    }
                }
            }
            return ans;
        }

         
};


void play_game(Board *board, vector<Player*> player_list)
{
    pair<int,int> coordinates;
    int turn=0;
    while(true)
    {
        
        coordinates = player_list[turn]->get_move(board);
        
        board->make_move(coordinates.first,coordinates.second, player_list[turn]->get_symbol());

        board->print_board();

        if(board->check_win(player_list[turn]->get_symbol()))
        {
            cout<<"Player "<<player_list[turn]->get_id()<<" won."<<endl;
            break;
        }

        if(board->is_board_completely_filled())
        {
            cout<<"Game Over"<<endl;
            break;
        }
        
        turn = 1-turn;
        
    }
}

class GameManager
{   
    public:
    static pair<int,int> Welcome()
    {
        cout<<"Welcome to Tic Tac Toe"<<endl;
        int choice, size;

        while(true)
        {
            cout<<"1. Play against Bot"<<endl;
            cout<<"2. Play against against another player"<<endl;
            cin>>choice;
            if(choice > 0 or choice < 3)
                break;
            cout<<"Please select correct mode from above options"<<endl;
        }
        while(true)
        {
            cout<<"Size of the board"<<endl;
            
            cin>>size;
            if(size >= 3 and size <= 10)
                break;
            cout<<"Please enter a number between 3 and 10"<<endl;
        }
        return {choice,size};
    }
};

class Modes{
    public:
    virtual vector<Player*> initialize_game() = 0;
};

class Player_vs_Player: public Modes
{
    public:
    vector<Player*> initialize_game()
    {
        Player *p1 = new Human();
        p1->assign_symbol('O', 1);
        Player *p2 = new Human();
        p2->assign_symbol('X', 2);

        vector<Player*> players_list;
        players_list.push_back(p1);
        players_list.push_back(p2);
        return players_list;
    }
};

class Player_vs_Bot: public Modes
{
    public:
    vector<Player*> initialize_game()
    {
        Player *p1 = new Human();
        p1->assign_symbol('O', 1);
        Player *p2 = new Bot();
        p2->assign_symbol('X', 2);

        vector<Player*> players_list;
        players_list.push_back(p1);
        players_list.push_back(p2);
        return players_list;
    }
};

class Game
{
    int choice;
    Board *board;
    public:
    Game(int choice, Board *board)
    {
        this->choice = choice;
        this->board = board;
    }
    void start_game()
    {
         vector<Player*> players_list;
        if(this->choice == 2)
        {
            Modes *mode = new Player_vs_Player();
            players_list = mode->initialize_game();
        }
        else
        {
            Modes *mode = new Player_vs_Bot();
            players_list = mode->initialize_game();
        }
        play_game(this->board,players_list);
        for (Player* player : players_list)
        {
            delete player;
        }

        players_list.clear();
    }

};


int main()
{
    pair<int,int> game_info = GameManager::Welcome();
    
    Board *board = new Board(game_info.second);
    Game *game = new Game(game_info.first, board);
    game->start_game();
    delete board;
    delete game;

}