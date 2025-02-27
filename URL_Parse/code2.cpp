#include<iostream>
#include <regex>
using namespace std;

struct URL {
    string scheme, host, port, path, query, fragment, user, password;
};

class URLUtils{
    public:
    static pair<string,string> get_scheme_and_split_url(string url)
    {
        size_t pos = url.find("://");
        if (pos != string::npos) {
            return {url.substr(0, pos), url.substr(pos + 3)};
        }
        return {"", url};
    }

    static int get_starting_index_of_char(string url, char c)
    {
        for(int i=0;i<url.length();i++)
        {
            if(url[i]==c)
                return i+1;
        }
        return -1;
    }

    static pair<string,string> get_user_auth_and_rest_of_url(string url)
    {
        size_t pos = url.find("@");
        if (pos != string::npos) {
            return {url.substr(0, pos), url.substr(pos + 1)};
        }
        return {"", url};
    }

    static string find_path(string curr_url)
    {        
        size_t pos = curr_url.find('/');
        string path = "";
        if (pos != string::npos)
        {
            
            for(int i=pos+1;i<curr_url.length()&&curr_url[i]!='?'&&curr_url[i]!='#';i++)
            {
                path+=curr_url[i];
            }
           
        } 
        return path;
    }

    static string find_host(string curr_url)
    {
        string ans = "";
        for(int i=0;i<curr_url.length()&&curr_url[i]!='/'&&curr_url[i]!=':';i++)
        {
            ans+=curr_url[i];
        }
        return ans;
    }

    static string find_port(string curr_url)
    {
        int index = URLUtils::get_starting_index_of_char(curr_url, ':');
        string ans = "";
        if(index!=-1)
        {
            for(int i=index;i<curr_url.length()&&curr_url[i]!='/';i++)
            {
                ans+=curr_url[i];
            }
        }
        return ans;
    }

    static string find_query(string curr_url)
    {
        int index = URLUtils::get_starting_index_of_char(curr_url, '?');
        string ans = "";
        if(index!=-1)
        {
            
            for(int i=index;i<curr_url.length()&&curr_url[i]!='#';i++)
            {
                ans+=curr_url[i];
            }
            
        }
       return ans;
    }

    static string find_fragment(string curr_url)
    {
        int index = URLUtils::get_starting_index_of_char(curr_url, '#');
        if(index!=-1)
        {
            return curr_url.substr(index);
        }
        else{
            return "";
        }
    }
};

class ParsingStrategy
{
    public:
    virtual void parse_url(string scheme) = 0;
    virtual void show_url_components() = 0;
    virtual ~ParsingStrategy() {}
    
};

class HttpParser: public ParsingStrategy
{
    URL myUrl;
    string url;
    public:
    HttpParser(string url)
    {
        this->url = url;
    }
    
    void parse_url(string scheme)
    {
        this->myUrl.scheme = scheme;
        this->myUrl.port = URLUtils::find_port(this->url);
        this->myUrl.path = URLUtils::find_path(this->url);
        this->myUrl.host = URLUtils::find_host(this->url);
        this->myUrl.fragment = URLUtils::find_fragment(this->url);
        this->myUrl.query = URLUtils::find_query(this->url);
    }

    void show_url_components()
    {
        cout<<"Scheme-->"<<this->myUrl.scheme<<endl;
        cout<<"Host-->"<<this->myUrl.host<<endl;
        cout<<"Port-->"<<this->myUrl.port<<endl;
        cout<<"Path-->"<<this->myUrl.path<<endl;
        cout<<"Fragment-->"<<this->myUrl.fragment<<endl;
        cout<<"Query-->"<<this->myUrl.query<<endl;
    }
};

class FtpParser: public ParsingStrategy
{
    URL myUrl;
    string url;
    public:
    FtpParser(string url)
    {
        this->url = url;
    }
    
    void parse_url(string scheme)
    {
        pair<string,string> url_after_removing_auth = URLUtils::get_user_auth_and_rest_of_url(this->url);
        string auth = url_after_removing_auth.first;
        string new_url = url_after_removing_auth.second;
        this->url = new_url;
        this->myUrl.scheme = scheme;
        this->myUrl.port = URLUtils::find_port(this->url);
        this->myUrl.path = URLUtils::find_path(this->url);
        this->myUrl.host = URLUtils::find_host(this->url);
        this->myUrl.fragment = URLUtils::find_fragment(this->url);
        this->myUrl.query = URLUtils::find_query(this->url);
        pair<string,string> credentials = find_user_password(auth);
        this->myUrl.user = credentials.first;
        this->myUrl.password = credentials.second;
    }

    void show_url_components()
    {
        cout<<"Scheme-->"<<this->myUrl.scheme<<endl;
        cout<<"Host-->"<<this->myUrl.host<<endl;
        cout<<"Port-->"<<this->myUrl.port<<endl;
        cout<<"Path-->"<<this->myUrl.path<<endl;
        cout<<"Fragment-->"<<this->myUrl.fragment<<endl;
        cout<<"Query-->"<<this->myUrl.query<<endl;
        cout<<"User-->"<<this->myUrl.user<<endl;
        cout<<"Password-->"<<this->myUrl.password<<endl;
    }

    pair<string,string> find_user_password(string auth)
    {
        size_t pos = auth.find(':');
        
        if (pos != string::npos)
        {
            string user = auth.substr(0,pos);
            string password = auth.substr(pos+1);
            
            return {user,password};
        } 
        else 
        {
            return {"",""};
        }
    }

};

class URLParsingfactory{
    public:
    static ParsingStrategy* assign_parsing_strategy(string scheme, string url)
    {
        if (scheme == "http" || scheme == "https") {
            return new HttpParser(url);
        } 
        else if (scheme == "ftp") {
            return new FtpParser(url);
        }
        else
            return nullptr;
    }
};

class InputManager
{
    
    public:
    static string take_url_input()
    {
        string url;
        while(true)
        {
            cout<<"Enter URL"<<endl;
            cin>>url;
            if(is_url_valid(url))
            {
                break;
            }
            else{
                cout<<"Invalid URL"<<endl;
            }
        }
        return url;
        
    }
     
    static bool is_url_valid(string url)
    {
        regex pattern(R"(^(https?|ftp):\/\/([a-zA-Z0-9._%+-]+(:[a-zA-Z0-9._%+-]+)?@)?([a-zA-Z0-9.-]+)(:[0-9]+)?(\/[^/\s][^\s]*)?(\?[^\s]*)?(#[^\s]*)?$)");

        if (regex_match(url, pattern)) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }

};

int main()
{
    string url = InputManager::take_url_input();
    pair<string,string> components = URLUtils::get_scheme_and_split_url(url);
    ParsingStrategy *obj = URLParsingfactory::assign_parsing_strategy(components.first, components.second);
    if(obj != nullptr)
    {
        obj->parse_url(components.first);
        obj->show_url_components();
        delete obj;
    }
    else{
        cout<<"Unrecognised Scheme";
    }
    
    return 0;
}