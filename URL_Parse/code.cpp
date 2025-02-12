#include<iostream>
#include <string>
#include <regex>
using namespace std;


int get_starting_index_of_fragment(string url)
{
    for(int i=0;i<url.length();i++)
    {
        if(url[i]=='#')
            return i+1;
    }
    return -1;
}
int get_starting_index_of_query(string url)
{
    for(int i=0;i<url.length();i++)
    {
        if(url[i]=='?')
            return i+1;
    }
    return -1;
}

int get_starting_index_of_port(string url)
{
    for(int i=0;i<url.length();i++)
    {
        if(url[i]==':')
            return i+1;
    }
    return -1;
}

pair<string,string> get_scheme_and_split_url(string url)
{
    size_t pos = url.find("://");
    if (pos != string::npos) {
        return {url.substr(0, pos), url.substr(pos + 3)};
    }
    return {"", url};
}
pair<string,string> get_user_auth_and_rest_of_url(string url)
{
    size_t pos = url.find("@");
    if (pos != string::npos) {
        return {url.substr(0, pos), url.substr(pos + 1)};
    }
    return {"", url};
}
string get_path(string url)
{
    size_t pos = url.find('/');
    
    if (pos != string::npos)
    {
        string path = "";
        for(int i=pos+1;i<url.length()&&url[i]!='?'&&url[i]!='#';i++)
        {
            path+=url[i];
        }
        return path;
    } 
    else 
    {
        return "";
    }
}
string get_host(string url)
{
    string ans = "";
    for(int i=0;i<url.length()&&url[i]!='/'&&url[i]!=':';i++)
    {
        ans+=url[i];
    }
    return ans;
}
string get_port(string url)
{
    int index = get_starting_index_of_port(url);
    if(index!=-1)
    {
        string ans = "";
        for(int i=index;i<url.length()&&url[i]!='/';i++)
        {
            ans+=url[i];
        }
        return ans;
    }
    return "";
}
string get_query(string url)
{
    int index = get_starting_index_of_query(url);
    if(index!=-1)
    {
        string ans = "";
        for(int i=index;i<url.length()&&url[i]!='#';i++)
        {
            ans+=url[i];
        }
        return ans;
    }
    return "";
}
string get_fragment(string url)
{
    int index = get_starting_index_of_fragment(url);
    if(index!=-1)
    {
        return url.substr(index);
    }
    return "";
}

pair<string,string> get_user_auth(string auth)
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
bool url_is_valid(string url)
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

int main()
{
    string url;
    cout<<"Enter URL"<<endl;
    cin>>url;
    if(url_is_valid(url))
    {
        pair<string,string> split_url = get_scheme_and_split_url(url);
        string scheme = split_url.first;
        string url_after_removing_scheme = split_url.second;
        pair<string,string> url_after_removing_auth = get_user_auth_and_rest_of_url(url_after_removing_scheme);
        string auth = url_after_removing_auth.first;
        string new_url = url_after_removing_auth.second;
        string path = get_path(new_url);
        string host = get_host(new_url);
        string port = get_port(new_url);
        string query = get_query(new_url);
        string fragment = get_fragment(new_url);
        pair<string,string> credentials = get_user_auth(auth);
        
        cout<<"scheme----->"<<scheme<<endl;
        cout<<"port----->"<<port<<endl;
        cout<<"fragment----->"<<fragment<<endl;
        cout<<"query----->"<<query<<endl;
        cout<<"path----->"<<path<<endl;
        cout<<"host----->"<<host<<endl;
        cout<<"User----->"<<credentials.first<<endl;
        cout<<"Password----->"<<credentials.second<<endl;
    }
    else
    {
        cout<<"Invalid URL"<<endl;
    }
    return 0;
}