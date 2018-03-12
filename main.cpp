//
//  main.cpp
//  ObserverDemo
//
//  Created by 赵祥 on 2018/3/12.
//  Copyright © 2018年 赵祥. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

//观察者基类，用于更新
class Observer
{
public:
    virtual ~Observer(){};
    virtual void Update(const string &name,const string &msg) = 0;
protected:
    Observer(){};
};
//被观察对象的基类，所有需要被观察的对象都要继承于这个类
class Subject
{
public:
    virtual ~Subject(){};
    virtual void registerObserver(Observer *obs) = 0;    //注册需要观察的通知对象
    virtual void removeObserver(Observer *obs) = 0;      //移除需要观察的对象
    virtual void notifyObserver(const string &name,const string &msg) = 0;      //通知观察对象
};
/****************************************************************/
//被观测对象所存放的地方
class Group : public Subject
{
private:
    list<Observer*> *_obsGroup;        //用于存储被观察的对象
public:
    //初始化_obsGroup
    Group() { _obsGroup = new list<Observer*>(); }
    //注册需要观察的通知对象
    void registerObserver(Observer *obs){
        _obsGroup->push_back(obs);
    }
    //移除需要观察的对象
    void removeObserver(Observer *obs){
        _obsGroup->remove(obs);
    }
    //通知观察对象
    void notifyObserver(const string &name,const string &msg){
        std::list<Observer*>::iterator iter = _obsGroup->begin();
        for ( ;iter != _obsGroup->end(); iter++ ) {
            (*iter)->Update(name,msg);
        }
    }
};
/****************************************************************/
//需要观察的对象
class Object : public Observer
{
public:
    Object(const string &msg){
        _name = msg;
    }
    void Update(const string &name,const string &msg)
    {
        if(name == _name){
            cout << "我以前是： " << _name;
            cout << "   我变成了: " << msg << endl;
            _name = msg;
        }
    }
private:
    string _name;
};

int main(int argc, const char * argv[]) {
    
    Group *obGroup = new Group();  //注册存放观察对象的队列
    
    //注册观察的对象
    Object *obj1 = new Object("jack");
    Object *obj2 = new Object("marin");
    Object *obj3 = new Object("faker");
    
    //也可以以注册观察者对象提供一个功能函数来作为统一接口
    /*
     void register(数组){
        for(循环数组){
           obGroup->registerObserver(数组元素);
        }
     }
     */
    obGroup->registerObserver(obj1);
    obGroup->registerObserver(obj2);
    obGroup->registerObserver(obj3);
    
    //根据名字找到需要修改的对象
    //obGroup->notifyObserver(对象名, 修改后的对象名);
    obGroup->notifyObserver("jack", "rouse");
    obGroup->notifyObserver("marin", "pdd");
    obGroup->notifyObserver("faker", "father");
    
    obGroup->notifyObserver("pdd", "1111");
    
    obGroup->notifyObserver("999", "father");

    return 0;
}





















