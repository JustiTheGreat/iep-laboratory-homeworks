#include <iostream>

class noCopyAssignmentOperator{
    private:
    noCopyAssignmentOperator& operator = (const noCopyAssignmentOperator&);
};
class Cat:private noCopyAssignmentOperator{
    private:
    static int instance;
    std::string name;
    int catNumber;
    int getInstance(){
        return ++instance;
    }
    public:
    Cat(std::string name){
        catNumber = ++instance;
        this->name = name;
    }
    Cat(const Cat& cat){
        this->catNumber = cat.catNumber;
        this->name = cat.name;
    }
    void setName(std::string name){
        this->name = name;
    }
    //Cat& operator = (const Cat&) = delete;
    void makeSound(){
        std::cout<<catNumber<<" - "<<name<<": meowed!"<<std::endl;
    }
    ~Cat(){
        std::cout<<catNumber<<" - "<<name<<": died!"<<std::endl;
    }
};
int Cat::instance = 0;

int main () {
    Cat cat1("Berlioz");
    Cat cat2("Marie");
    Cat cat3("Toulouse");
    {
        Cat cat4(cat2);
        cat4.setName("Another");
        Cat cat5(cat3);
        cat1.makeSound();
        cat2.makeSound();
        cat3.makeSound();
        cat4.makeSound();
        cat5.makeSound();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    return 0;
}