#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void circleFlagBtnClicked();
    virtual void circleMove();
    virtual void changeBGBtnClicked();
protected:
    int m_iCircleBtn;
    int m_iBGBtn;
};

#endif // MAINVIEW_HPP
