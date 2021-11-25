#include <iostream>

class Number{
    private:
    int* value;
    public:
    Number(int value){
        this->value = new int(value);
    }
    Number(const Number& number)=delete;
    Number& operator=(const Number& number){
        if(this == &number) return *this;
        setParameters(*number.value);
        return *this;
    }
    Number& operator+=(const Number& number){
        setParameters(*this->value + *number.value);
        return *this;
    }
    void details(){
        std::cout<<"Value = "<<*value<<std::endl;
    }
    private:
    void setParameters(int value){
        delete this->value;
        this->value = new int(value);
    }
};
class ColouredNumber:public Number{
    private:
    std::string* color;
    public:
    ColouredNumber(int value,std::string color):Number(value){
        this->color=new std::string(color);
    }
    ColouredNumber(const ColouredNumber& colouredNumber)=delete;
    ColouredNumber& operator=(const ColouredNumber& colouredNumber){
        if(this == &colouredNumber) return *this;
        Number::operator=(colouredNumber);
        setParameters(*colouredNumber.color);
        return *this;
    }
    ColouredNumber& operator+=(const ColouredNumber& colouredNumber){
        Number::operator+=(colouredNumber);
        setParameters(*this->color+*colouredNumber.color);
        return *this;
    }
    void details(){
        Number::details();
        std::cout<<"Color = "<<*color<<std::endl;
    }
    private:
    void setParameters(std::string color){
        delete this->color;
        this->color = new std::string(color);
    }
};

int main () {
    Number nr1(1);
    Number nr2(2);
    nr1.details();
    nr2.details();
    std::cout<<std::endl;
    nr1=nr1;
    nr1=nr2;
    nr1.details();
    nr2.details();
    std::cout<<std::endl;
    nr1+=nr1;
    nr1+=nr2;
    nr1.details();
    nr2.details();
    std::cout<<std::endl;
    ColouredNumber nr3(3,"red");
    ColouredNumber nr4(4,"blue");
    nr3.details();
    nr4.details();
    std::cout<<std::endl;
    nr3=nr3;
    nr3=nr4;
    nr3.details();
    nr4.details();
    std::cout<<std::endl;
    nr3+=nr3;
    nr3+=nr4;
    nr3.details();
    nr4.details();
    std::cout<<std::endl;
    return 0;
}