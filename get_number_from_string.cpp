#include <sstream>
using namespace std ; 
typedef int item ;  



int getnumber(item item[], string str)
{
    stringstream ss(str);
    int top = 0 ; 
    while (ss.peek() != EOF) {
        if (isdigit(ss.peek()) || ss.peek() == '-') ss >> item[top++];
        else ss.get();
    }
    return top ; 
}
