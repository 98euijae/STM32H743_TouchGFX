#include <gui/graph_screen/GraphView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "stm32h7xx_hal_tim.h"

extern uint32_t TIMStart;
extern uint32_t TIMEnd;
extern TIM_HandleTypeDef htim2;
extern int dataX[100];
extern int dataY[100];
double d_tim;

GraphView::GraphView()
{
    srand(time(NULL));
    m_iGraphVisible = 1;
    m_iSensorFlag = 1;
}

void GraphView::setupScreen()
{
    GraphViewBase::setupScreen();
}

void GraphView::tearDownScreen()
{
    GraphViewBase::tearDownScreen();
}

void GraphView::graphBtnClicked()
{
    if(m_iGraphVisible == 1)
    {
        graphContainer.setVisible(false);
        graphTextContainer.setVisible(false);
        graphBtn.setLabelText(T_GRAPHBTNON);
        m_iGraphVisible = 0;
    }
    else
    {
        graphContainer.setVisible(true);
        graphTextContainer.setVisible(true);
        graphBtn.setLabelText(T_GRAPHBTNOFF);
        m_iGraphVisible = 1;
    }
    graphContainer.invalidate();
    graphTextContainer.invalidate();
    graphBtn.invalidate();
}

void GraphView::addPointBtnClicked()
{
//    srand(time(NULL));
//    int randomX[4];
//    int randomY[4];
//    
//    for(int i = 0; i < 4; i++)
//    {
//        randomX[i] = rand() % 200 - 100;
//        randomY[i] = rand() % 200 - 100;
//    }
//    
//    ch1Graph.addDataPointScaled(randomX[0], randomY[0]);
//    ch2Graph.addDataPointScaled(randomX[1], randomY[1]);
//    ch3Graph.addDataPointScaled(randomX[2], randomY[2]);
//    ch4Graph.addDataPointScaled(randomX[3], randomY[3]);
    for(int i = 0; i < 30; i++)
    {
        ch1Graph.addDataPointScaled(dataX[i], dataY[i]);
    }
}

void GraphView::sensorTextAlarm()
{
    if(m_iSensorFlag == 1)
    {
        ch1SensorText.setVisible(true);
        ch2SensorText.setVisible(true);
        ch3SensorText.setVisible(true);
        ch4SensorText.setVisible(true);
        m_iSensorFlag = 0;
    }
    else
    {
        ch1SensorText.setVisible(false);
        ch2SensorText.setVisible(false);
        ch3SensorText.setVisible(false);
        ch4SensorText.setVisible(false);
        m_iSensorFlag = 1;
    }
    graphTextContainer.invalidate();
}

void GraphView::changeBoxColorBtnClicked()
{
    box2.setColor((box2.getColor() ^ 0x00FF00));
    box2.invalidate();
}

void GraphView::transStart()
{
    TIMStart = htim2.Instance->CNT;
}

void GraphView::transEnd()
{
    TIMEnd = htim2.Instance->CNT;
    d_tim = (TIMEnd - TIMStart) / 200000000.f;
}