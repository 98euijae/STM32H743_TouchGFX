#ifndef GRAPHVIEW_HPP
#define GRAPHVIEW_HPP

#include <gui_generated/graph_screen/GraphViewBase.hpp>
#include <gui/graph_screen/GraphPresenter.hpp>
#include <main.h>

class GraphView : public GraphViewBase
{
public:
    GraphView();
    virtual ~GraphView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void setGraph(int dataX[DATA_SIZE], int dataY[DATA_SIZE], int dataCnt);
    virtual void sensorAlarmFunc();
protected:
    bool sensorFlag;
};

#endif // GRAPHVIEW_HPP
