#include <iostream>
#include <cstdlib>
using namespace std;
class Rectangle{
    private:
        double width;
        double length;
    public:
        inline double area() const{return width*length;}
        inline  Rectangle & display(){cout<<"Length:"<<length<<"Width"<<width<<endl;return *this;}
        Rectangle &operator>(Rectangle & other){
            return ((area()>other.area()) ? *this : other);
        }
        Rectangle()=default;
        Rectangle(double x,double y):length(x),width(y){};
};
int main()
{
    Rectangle a(5,6);
    Rectangle b(4,5);
    cout<<a.area()<<endl;
    a.display();
    (a>b).display();
    system("Pause");
    return 0;
}