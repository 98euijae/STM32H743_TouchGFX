#ifndef GRAPHVIEW_HPP
#define GRAPHVIEW_HPP

#include <gui_generated/graph_screen/GraphViewBase.hpp>
#include <gui/graph_screen/GraphPresenter.hpp>

class GraphView : public GraphViewBase
{
public:
    GraphView();
    virtual ~GraphView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void graphBtnClicked();
    virtual void addPointBtnClicked();
    virtual void sensorTextAlarm();
    virtual void changeBoxColorBtnClicked();
    virtual void transStart();
    virtual void transEnd();
protected:
    int m_iGraphVisible;
    int m_iSensorFlag;
};

#endif // GRAPHVIEW_HPP
