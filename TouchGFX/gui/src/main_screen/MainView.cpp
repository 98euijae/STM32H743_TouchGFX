#include <gui/main_screen/MainView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

MainView::MainView()
{
    m_iCircleBtn = 0;
    m_iBGBtn = 0;
}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::circleFlagBtnClicked()
{
    TypedText tt;
    
    if(m_iCircleBtn == 0)
    {
        m_iCircleBtn = 1;
        circleFlagBtn.setLabelText(T_CIRCLEBTNSTOP);
        circleFlagBtn.invalidate();
    }
    else
    {
        m_iCircleBtn = 0;
        circleFlagBtn.setLabelText(T_CIRCLEBTNMOVE);
        circleFlagBtn.invalidate();
    }
}


void MainView::circleMove()
{
    int16_t x, y, width, height;
    x = redCircle.getX();
    y = redCircle.getY();
    width = redCircle.getWidth();
    height = redCircle.getHeight();
    
    if(m_iCircleBtn == 1)
    {
        redCircle.invalidate();
        if(x < 500)
            redCircle.setPosition(x + 20, y, width, height);
        else
            redCircle.setPosition(50, y, width, height);
        redCircle.invalidate();
    }
}

void MainView::changeBGBtnClicked()
{
    if(m_iBGBtn == 0)
    {
        background.setColor(colortype(0x00FF00));
        background.invalidate();
        m_iBGBtn = 1;
    }
    else
    {
        background.setColor(colortype(0xFFFFFF));
        background.invalidate();
        m_iBGBtn = 0;
    }
}