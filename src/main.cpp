#include <iostream>
#include <memory>
#include <mutex>

class Resource{
    private:
    static int instances;
    int number=-1;
    Resource(int number){
        this->number = number;
    }
    public:
    void printInstanceNumber(){
        std::cout<<number<<std::endl;
    }
    static Resource* createResource();
};
int Resource::instances = 0;
Resource* Resource::createResource(){
    return new Resource(++instances);
}
class Lock{
    private:
    std::mutex *ptr;
    public:
    explicit Lock(std::mutex *m):ptr(m){
        ptr->lock();
        std::cout<<"mutex locked"<<std::endl;
    }
    Lock(const Lock& lock) = delete;
    Lock& operator = (const Lock&) = delete;
    ~Lock(){
        ptr->unlock();
        std::cout<<"mutex unlocked"<<std::endl;
    }
};
struct deleter{
    void operator()(std::mutex* m)const{
        m->unlock();
        std::cout<<"mutex unlocked"<<std::endl;
        delete m;
    }
};
class SharedLock{
    private:
    std::shared_ptr<std::mutex> ptr;
    public:
    explicit SharedLock(std::mutex *m):ptr(m,deleter()){
        ptr.get()->lock();
        std::cout<<"mutex locked"<<std::endl;
    }
    SharedLock(const SharedLock& sharedLock)=delete;
    SharedLock& operator = (const SharedLock& sharedlock)=delete;
};
int main () {
    Resource *res1 = Resource::createResource();
    delete res1;
    std::cout<<std::endl;
    {
        std::cout<<"-------------"<<std::endl;
        std::auto_ptr<Resource> res2(Resource::createResource());
        res2->printInstanceNumber();
        std::cout<<"-------------"<<std::endl;
        std::auto_ptr<Resource> res3(res2);
        if(res2.get())res2->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        if(res3.get())res3->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        std::cout<<"-------------"<<std::endl;
        res2 = res3;
        if(res2.get())res2->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        if(res3.get())res3->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        std::cout<<"-------------"<<std::endl;
    }
    std::cout<<std::endl;
    {
        std::cout<<"-------------"<<std::endl;
        std::shared_ptr<Resource> res2(Resource::createResource());
        res2->printInstanceNumber();
        std::cout<<"-------------"<<std::endl;
        std::shared_ptr<Resource> res3(res2);
        if(res2.get())res2->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        if(res3.get())res3->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        std::cout<<"-------------"<<std::endl;
        res2 = res3;
        if(res2.get())res2->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        if(res3.get())res3->printInstanceNumber();
        else std::cout<<"NULL"<<std::endl;
        std::cout<<"-------------"<<std::endl;
    }
    std::cout<<std::endl;
    std::mutex mutex1;
    {
        Lock lock(&mutex1);
    }
    std::cout<<std::endl;
    std::mutex mutex2;
    {
        SharedLock sharedLock(&mutex2);
    }
    return 0;
}
