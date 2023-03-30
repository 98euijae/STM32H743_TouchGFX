#ifndef MAIN_1VIEW_HPP
#define MAIN_1VIEW_HPP

#include <gui_generated/main_1_screen/Main_1ViewBase.hpp>
#include <gui/main_1_screen/Main_1Presenter.hpp>

class Main_1View : public Main_1ViewBase
{
public:
    Main_1View();
    virtual ~Main_1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void circleFlagBtnClicked2();
    virtual void circleMove2();
    virtual void changeBGBtnClicked2();
protected:
    int m_iCircleBtn;
    int m_iBGBtn;
};

#endif // MAIN_1VIEW_HPP
