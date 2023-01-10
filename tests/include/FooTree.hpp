#ifndef __FOO_TREE_HPP__
#define __FOO_TREE_HPP__

#include <QOlm/QOlm.hpp>

class FooTree: public qolm::QOlm<FooTree>
{
    Q_OBJECT
    Q_PROPERTY(int foo READ getFoo WRITE setFoo NOTIFY fooChanged)

    int _foo = 1;

public:
    FooTree(int foo, QObject* parent = nullptr) :
      _foo(foo), qolm::QOlm<FooTree>(parent)
    {
        //qDebug("Constructor");
    }
    ~FooTree()
    {
        //qDebug("Destructor");
    }
    int getFoo() const { return _foo; }
    void setFoo(int foo)
    {
        if(foo != _foo)
        {
            _foo = foo;
            emit fooChanged();
        }
    }
signals:
    void fooChanged();
};

#endif
