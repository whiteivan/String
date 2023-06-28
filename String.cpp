#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;


class String
{
    friend istream& operator>>(istream& is,String& s);
    friend istream& getline(istream& is, String& s);    
private:
    size_t sz = 0;
    char* str = nullptr;
    size_t length(const char* ptr ){
        size_t lenght = 0;
    while(*ptr){
        lenght++;
        ptr++;
    }
    return lenght;
    }
public:
    void low_case(){
        for (size_t i = 0; i !=sz; i++)
        {
            if (str[i] < 97)
            {
                str[i]+=32;
            }
        }
    }
    String() = default;
    String(const char* ptr);
    String(int i,const char ch);
    String(String&& s);
    ~String();
    String(const String&s);
    size_t size()const{return sz;}
    String& operator=(const String& s){
        if (this != &s)
        {
            sz = s.sz;
            delete[] str;
            str = new char[sz+1];
            for (size_t i = 0; i != sz+1; i++)
            {
                str[i] = s.str[i];
            }
        }
        return *this;
    }
    String& operator+=(const String& s){
        size_t tsz = sz;
        sz+=s.sz;
        char* temp = new char[sz];
        for (size_t i = 0; i !=tsz; i++)
        {
            temp[i] = str[i];
        }
        for (size_t i = 0; i != s.sz+1 ; i++)
        {
            temp[tsz+i] = s.str[i];
        }
        delete [] str;
        str = temp;
        return *this;
    }
    String operator+(const String& s){
        String string;
        string+=*this;
        string+=s;
        return string;
    }
    bool operator<(const String& s) const {
        size_t len1 = sz;
        size_t len2 = s.sz;
        size_t minLen = min(len1, len2);
        for (size_t i = 0; i < minLen; i++) {
            if (str[i] > s.str[i])
                return true;
            else if (str[i] < s.str[i])
                return false;
        }
        return len1 > len2;
    }
    bool operator!=(const String& s){
        if (s.sz!=sz)
        {
            return true;
        }
        for (size_t i = 0; i !=sz; i++)
        {
            if (str[i]!=s.str[i])
            {
                return true;
            }
        }
        return false;
    }
    bool operator!=(const char* ptr){
        if (length(ptr)!=sz)
        {
            return true;
        }
        for (size_t i = 0; i !=sz; i++)
        {
            if (str[i]!=ptr[i])
            {
                return true;
            }
        }
        return false;
    }
    bool operator!=(const char ch){
        if (sz != 1)
        {
            return true;
        }
        if (str[0]!=ch)
        {
            return true;
        }
        return false;
    }
    char& operator[](const size_t index){
    return str[index];
    }
    char operator[](const size_t index)const {
        return str[index];
    }
};

istream& getline(istream& is, String& s){
    delete[] s.str;
    const size_t max = 1000;
    char* buffer = new char[max];
    s.sz = 0;
    char ch;
    while (is.get(ch))
    {
        if(ch=='\n'){break;}
        buffer[s.sz] = ch;
        ++s.sz;
    }
    s.str = new char[s.sz+1];
    for (size_t i = 0; i !=s.sz; i++)
    {
        s.str[i] = buffer[i];
    }
    delete [] buffer;
    s.str[s.sz+1] = '\0';
    return is;
}

istream& operator>>(istream& is,String& s){
    delete[] s.str;
    const size_t max = 1000;
    char buffer[max];
    s.sz = 0;
    char ch;
     while (is.get(ch))
    {
        if(ch=='\n'||ch==' '){break;}
        buffer[s.sz] = ch;
        ++s.sz;
    }
    s.str = new char[s.sz+1];
    for (size_t i = 0; i !=s.sz; i++)
    {
        s.str[i] = buffer[i];
    }
    s.str[s.sz+1] = '\0';
    return is;
}

ostream& operator<<(ostream& os,const String& s){
    for (size_t i = 0; i < s.size(); i++)
    {
        os<<s[i];
    }
    return os;
}

String::String(String&& s):str(s.str),sz(s.sz){
    s.str = nullptr;
    s.sz = 0;
}

String::String(const char* ptr):str(new char[sz+1]),sz(length(ptr))
{
    for (size_t i = 0; i!= sz; i++)
        {
            str[i] = ptr[i];
        }
        str[sz] = '\0';
}

String::String(int i,const char ch):sz(i),str(new char[sz+1]){
    for (size_t i = 0; i !=sz; i++)
    {
        str[i] = ch;
    }
    str[sz] = '\0';
}

String::String(const String& s):sz(s.sz),str(new char[sz+1]){
    for (size_t i = 0; i !=sz; i++)
    {
        str[i] = s.str[i];
    }
    str[sz] = '\0';
}

String::~String()
{
    delete[] this->str;
}

bool compareStrings(const String& s1, const String& s2) {
    return s2 < s1;
}

void sort(vector<String>::iterator beg, vector<String>::iterator end) {
    for (auto i = beg; i != end; i++)
    {
        for (auto j = i;j != end; j++)
        {
            if (compareStrings(*i,*(j)))
            {
                auto temp = *i;
                *i = *(j);
                *(j) = temp;
            }else if (!(*(i) != *(i+1))){
                continue;
            }
        }
    }
}

int main(){
    vector<String> strings;
    String s;
    cout<<"Введите список строк.\nВведите 'end' коода закончите"<<endl;
    while (getline(cin,s)&&s!="end")
    {
        s.low_case();
        strings.push_back(s);
    }
    sort(strings.begin(),strings.end());
    for (auto i = strings.begin(); i !=strings.end(); i++)
    {
        cout<<(*i)<<endl;
    }
    return 0;
}