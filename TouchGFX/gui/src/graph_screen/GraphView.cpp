#include <gui/graph_screen/GraphView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/Color.hpp>
#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include "cmsis_os2.h"

extern "C" 
{
    extern osEventFlagsId_t SDEventHandle;
}


GraphView::GraphView()
{
    sensorFlag = false;
}

void GraphView::setupScreen()
{
    GraphViewBase::setupScreen();
}

void GraphView::tearDownScreen()
{
    GraphViewBase::tearDownScreen();
}

void GraphView::setGraph(int dataX[DATA_SIZE], int dataY[DATA_SIZE], int dataCnt)
{
//    Circle newCircle;
//    PainterRGB565 circlePainter;
//    circlePainter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
//    
//    for(int i = 0; i < DATA_SIZE; i++)
//    {
//        newCircle.setCircle((int)((double)dataX[DATA_SIZE] * 0.1f), 
//                            (int)((double)dataY[DATA_SIZE] * 0.1f),
//                            2);
//        newCircle.setPainter(circlePainter);
//        CH1graph.add(newCircle);
//    }
//    CH1graph.invalidate();
    uint32_t start = osKernelGetTickCount();
    uint32_t end;
    
    for(int i = 0; i < dataCnt; i++)
    {
        CH1graph.addCircle(dataX[i], dataY[i], CH1graph.getX(), CH1graph.getY());
        CH2graph.addCircle(dataX[i], dataY[i], CH2graph.getX(), CH2graph.getY());
        CH3graph.addCircle(dataX[i], dataY[i], CH3graph.getX(), CH3graph.getY());
        CH4graph.addCircle(dataX[i], dataY[i], CH4graph.getX(), CH4graph.getY());
    }
    end = osKernelGetTickCount();
    end = end - start;
}

void GraphView::sensorAlarmFunc()
{
    if(sensorFlag)
        sensorFlag = false;
    else
        sensorFlag = true;
    
    CH1graph.setSensorTextVisible(sensorFlag);
    CH2graph.setSensorTextVisible(sensorFlag);
    CH3graph.setSensorTextVisible(sensorFlag);
    CH4graph.setSensorTextVisible(sensorFlag);
}