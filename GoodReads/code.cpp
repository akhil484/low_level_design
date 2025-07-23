#include<iostream>
#include<vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// user
// function or class to add friends
// how to add or associate book to a user i.e user has read that book
// we can declare a global unordered_map to store books and friends for each user
// should I make a class for this
// we get a user id and book id
// book

class User
{
    int id;
    string first_name;
    string last_name;
    string email;
    public:
    User(int id, string first_name, string last_name, string email)
    {
        this->id = id;
        this->first_name = first_name;
        this->last_name = last_name;
        this->email = email;
    }

    virtual ~User()
    {
        cout<<"User class Destructor called"<<endl;
    }
};
class Reviews
{
    int id;
    int rating;
    string comment;
};

class Book
{
    int id;
    string title;
    string author;
    string genre;
    vector<Reviews> reviews;
    public:
    Book(int id, string title, string author, string genre)
    {
        this->id=id;
        this->title=title;
        this->author=author;
        this->genre=genre;
    }
    virtual ~Book()
    {
        cout<<"Book class Destructor called"<<endl;
    }
    string get_title()
    {
        return this->title;
    }
};



class UserBookCollection
{
    private:
    unordered_map<int,vector<Book*>> books_read_by_user;

    public:
        void add_book_to_users_list(int user_id, Book *b)
        {
            books_read_by_user[user_id].push_back(b);
        }

        vector<string> get_all_books_read_by_user(int user_id)
        {
            vector<string> all_books;
            for(auto it:books_read_by_user[user_id])
            {
                all_books.push_back(it->get_title());
            }
            return all_books;
        }
};

class ManageFriendsNetwork
{
    private:
    unordered_map<int,vector<int>> friends_list;

    public:

        void add_friends(int user_id, int friend_id)
        {
            friends_list[user_id].push_back(friend_id);
            friends_list[friend_id].push_back(user_id);
        }

        vector<int> get_friends_of_user(int user_id)
        {
            if(friends_list.find(user_id)!=this->friends_list.end())
                return friends_list[user_id];
            return {};
        }
};

class FriendNetwork
{
    ManageFriendsNetwork& friendsNetwork;

    void dfs(int id, unordered_set<int>& visited) {
        visited.insert(id);
        for (int friend_id : friendsNetwork.get_friends_of_user(id)) {
            if (visited.find(friend_id) == visited.end()) {
                dfs(friend_id, visited);
            }
        }
    }

    public:
        FriendNetwork(ManageFriendsNetwork& net) : friendsNetwork(net) {}

        vector<int> getNetworkOf(int user_id) {
            unordered_set<int> visited;
            dfs(user_id, visited);
            return vector<int>(visited.begin(), visited.end());
        }

        vector<int> getDirectFriendOf(int user_id) {
            return friendsNetwork.get_friends_of_user(user_id);
        }
};

struct BookComparator {
    bool operator()(const pair<int, string>& a, const pair<int, string>& b) const {
        if (a.first == b.first)
            return a.second > b.second;
        return a.first > b.first;
    }
};
class SocialBookService {
private:
    UserBookCollection& bookRepo;
    FriendNetwork& friendNet;

public:
    SocialBookService(UserBookCollection& collection, FriendNetwork& graph)
    : bookRepo(collection), friendNet(graph) {}



     vector<string> getBooksReadByUserNetwork(int user_id) {
        set<string> books;
        vector<int> network = friendNet.getNetworkOf(user_id);
        for (int uid : network) {
            vector<string> user_books = bookRepo.get_all_books_read_by_user(uid);
            books.insert(user_books.begin(), user_books.end());
        }
        return vector<string>(books.begin(), books.end());
    }

    vector<string> getBooksReadByUser(int user_id) {
        set<string> books;
        
        vector<string> user_books = bookRepo.get_all_books_read_by_user(user_id);
        books.insert(user_books.begin(), user_books.end());
        
        return vector<string>(books.begin(), books.end());
    }
    vector<string> getTopKBooksFromFriends(int userId, int K)
    {
        
        unordered_map<string, int> bookFrequency;
        priority_queue<pair<int, string>, vector<pair<int, string>>, BookComparator> minHeap;
        vector<int> friends = friendNet.getDirectFriendOf(userId);
        for(int i=0;i<friends.size();i++)
        {
            vector<string> user_books = bookRepo.get_all_books_read_by_user(friends[i]);
            for(auto book:user_books)
                bookFrequency[book]++;
        }

        for (const auto& entry : bookFrequency) {
            minHeap.push({entry.second, entry.first});
            if (minHeap.size() > K)
                minHeap.pop();
        }

        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
        }
    vector<string> getTopKBooksFromNetwork(int userId, int K)
    {
         
        unordered_map<string, int> bookFrequency;
        priority_queue<pair<int, string>, vector<pair<int, string>>, BookComparator> minHeap;
        vector<int> friends = friendNet.getNetworkOf(userId);
        for(int i=0;i<friends.size();i++)
        {
            vector<string> user_books = bookRepo.get_all_books_read_by_user(friends[i]);
            for(auto book:user_books)
                bookFrequency[book]++;
        }

        for (const auto& entry : bookFrequency) {
            minHeap.push({entry.second, entry.first});
            if (minHeap.size() > K)
                minHeap.pop();
        }

        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
};

int main()
{
    vector<Book*> books = {
        new Book(1, "A Game of Thrones", "George R. R. Martin", "Fantasy"),
        new Book(2, "The Hobbit", "J.R.R. Tolkien", "Fantasy"),
        new Book(3, "Dune", "Frank Herbert", "Sci-Fi"),
        new Book(4, "1984", "George Orwell", "Dystopian"),
        new Book(5, "The Name of the Wind", "Patrick Rothfuss", "Fantasy"),
        new Book(6, "Neuromancer", "William Gibson", "Cyberpunk"),
        new Book(7, "The Catcher in the Rye", "J.D. Salinger", "Literary"),
        new Book(8, "Frankenstein", "Mary Shelley", "Gothic Horror"),
        new Book(9, "The Road", "Cormac McCarthy", "Post-Apocalyptic"),
        new Book(10, "Dracula", "Bram Stoker", "Horror")
    };


    vector<User*> users;
    for (int i = 1; i <= 10; i++) {
        users.push_back(new User(i, "First" + to_string(i), "Last" + to_string(i), "user" + to_string(i) + "@mail.com"));
    }

    UserBookCollection bookcollection;
    ManageFriendsNetwork friendsnetwork;

    bookcollection.add_book_to_users_list(1, books[1]);
    bookcollection.add_book_to_users_list(1, books[4]);
    bookcollection.add_book_to_users_list(1, books[3]);
    bookcollection.add_book_to_users_list(1, books[0]);
    bookcollection.add_book_to_users_list(1, books[8]);
    bookcollection.add_book_to_users_list(1, books[2]);

    bookcollection.add_book_to_users_list(2, books[2]);
    bookcollection.add_book_to_users_list(2, books[3]);
    bookcollection.add_book_to_users_list(2, books[4]);
    bookcollection.add_book_to_users_list(2, books[5]);

    bookcollection.add_book_to_users_list(3, books[2]);
    bookcollection.add_book_to_users_list(3, books[3]);
    bookcollection.add_book_to_users_list(3, books[4]);
    bookcollection.add_book_to_users_list(3, books[5]);

    bookcollection.add_book_to_users_list(4, books[2]);
    bookcollection.add_book_to_users_list(4, books[3]);
    bookcollection.add_book_to_users_list(4, books[4]);
    bookcollection.add_book_to_users_list(4, books[5]);
    bookcollection.add_book_to_users_list(7, books[8]);
    bookcollection.add_book_to_users_list(6, books[9]);

    friendsnetwork.add_friends(1, 2);
    friendsnetwork.add_friends(1, 3);
    friendsnetwork.add_friends(1, 4);
    friendsnetwork.add_friends(1, 5);
    friendsnetwork.add_friends(1, 6);
    friendsnetwork.add_friends(1, 7);

    FriendNetwork networkTraversal(friendsnetwork);
    SocialBookService bookService(bookcollection, networkTraversal);

    vector<string> result = bookService.getBooksReadByUserNetwork(1);
    for (const string& title : result) {
        cout << title << endl;
    }

    vector<string> topBooks = bookService.getTopKBooksFromFriends(1, 3);
    for (const string& title : topBooks)
        cout << "Top: " << title << endl;

    for (Book* b : books) delete b;
    for (User* u : users) delete u;

    return 0;
}