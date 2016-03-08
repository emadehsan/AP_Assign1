#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

/**
    Copied Pointer Implementation
*/
class StringBuffer{

public :
    StringBuffer()  //default constructor
    {
        _strbuf = NULL;
        _length = 0;
        _refcount = 1;
    }

    ~StringBuffer()                //destructor; would delete the allocated buffer
    {
        if (_refcount == 0) {
            delete[] _strbuf;
            _length = 0;
            _strbuf = NULL;
        }
    }

    StringBuffer(const StringBuffer& obj)              //constructor for shallow copying
    {
        // copying
        _strbuf = new char[obj._length];
        _length = obj._length;

        strcpy(_strbuf, obj._strbuf);
        _refcount++;
    }

    StringBuffer(char* c,int l)   //constructor to convert a char* to StringBuffer
    {
        // convert array to string?
        reserve(l);
        strcpy(_strbuf, c);
        _refcount = 1;
    }

    char charAt(int i) const   //returns the character at the passed index
    {
        return _strbuf[i];
    }

    int length() const                            //returns the length of the buffer
    {
        return _length;
    }

    void reserve(int l)                             //allocates memory for the string, according to the passed character length
    {
        if (_length != 0 && _length < 10000) {
            char *tmp = new char[_length];
            strcpy(tmp, _strbuf);

            // increase the size of buffer
            _strbuf = new char[_length+l];
            _length = _length + l;
            // copy back the text
            strcpy(_strbuf, tmp);
        }
        else {
            _strbuf = new char[l];
            _length = l;
        }
    }

    void append(char c)                          //appends a single character at the end
    {
        reserve(1);
        _strbuf[_length - 1] = c;
    }

    void display()
    {
        for (int i = 0; i < _length; i++) {
            cout << _strbuf[i] ;
        }

        cout << "\n\nReference count: " << _refcount << endl;
    }

    int _refcount;

private:
    char* _strbuf;                                   //buffer to store the original string
    int _length;                                       //length of the string
};

int main()
{
//    StringBuffer str(new StringBuffer("Hello", 5));
    StringBuffer str("Hello World", 11);

    cout << "inal String: \n";
    str.display();

    str.append(' ');
    str.append('!');
    str.append('h');
    str.append('w');

    cout << "\n\nAfter Appending: \n";

    str.display();

    cout << "\n\nAfter copying: \n";
    StringBuffer s1(str);
    s1.display();

    return 0;
}
