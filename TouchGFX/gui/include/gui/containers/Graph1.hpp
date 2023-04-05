#ifndef GRAPH1_HPP
#define GRAPH1_HPP

#include <gui_generated/containers/Graph1Base.hpp>

class Graph1 : public Graph1Base
{
public:
    Graph1();
    virtual ~Graph1() {}

    virtual void initialize();
    void setSensorTextVisible(bool flag);
    void addCircle(int x, int y, int centerX, int centerY);
protected:
    int circleCnt;
    int prevX;
    int prevY;
};

#endif // GRAPH1_HPP
