/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/graph_screen/GraphViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

GraphViewBase::GraphViewBase() :
    frameCountSensorAlarmFuncInterval(0),
    buttonCallback(this, &GraphViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 640, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    bg.setPosition(0, 0, 640, 480);
    bg.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(bg);

    button1.setXY(0, 0);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_PRESSED_ID));
    button1.setAction(buttonCallback);
    add(button1);

    graphContainer.setPosition(0, 56, 640, 424);
    CH4graph.setXY(320, 214);
    graphContainer.add(CH4graph);

    CH3graph.setXY(0, 214);
    graphContainer.add(CH3graph);

    CH2graph.setXY(320, 0);
    graphContainer.add(CH2graph);

    CH1graph.setXY(0, 0);
    graphContainer.add(CH1graph);

    add(graphContainer);
}

GraphViewBase::~GraphViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void GraphViewBase::setupScreen()
{
    CH4graph.initialize();
    CH3graph.initialize();
    CH2graph.initialize();
    CH1graph.initialize();
}

void GraphViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction1
        //When button1 clicked change screen to Main
        //Go to Main with no screen transition
        application().gotoMainScreenNoTransition();
    }
}

void GraphViewBase::handleTickEvent()
{
    frameCountSensorAlarmFuncInterval++;
    if(frameCountSensorAlarmFuncInterval == TICK_SENSORALARMFUNC_INTERVAL)
    {
        //sensorAlarmFunc
        //When every N tick call virtual function
        //Call sensorAlarmFunc
        sensorAlarmFunc();
        frameCountSensorAlarmFuncInterval = 0;
    }
}
