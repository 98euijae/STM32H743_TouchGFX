#include <gui/containers/Graph1.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

Graph1::Graph1()
{
    circleCnt = 0;
    prevX = 0;
    prevY = 0;
}

void Graph1::initialize()
{
    Graph1Base::initialize();
}

void Graph1::setSensorTextVisible(bool flag)
{
    ch1SensorText.setVisible(flag);
    ch1SensorText.invalidate();
}

void Graph1::addCircle(int x, int y, int centerX, int centerY)
{
//    Circle newCircle;
//    PainterRGB565 circlePainter;
//    circlePainter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
//    
//    newCircle.setPosition(x / 2, y / 2, 5, 5);
//    newCircle.setCenter(1, 1);
//    newCircle.setRadius(2);
//    newCircle.setArc(0, 360);
//    newCircle.setPainter(circlePainter);
    
//    add(newCircle);
//    newCircle.invalidate();
    
//    Rect circleRect;
//    circleRect = getAbsoluteRect();
//    newCircle.draw(circleRect);
//    newCircle.invalidate();
    int newX, newY;
    circleCnt++;
    
    Line newLine;
    PainterRGB565 linePainter;
    linePainter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    newX = (int)round((double)x / 3000.0f * ((double)Graph1().getWidth() / 2)) + (Graph1().getWidth() / 2) + centerX;
    newY = (int)round((double)y / 3000.0f * ((double)Graph1().getHeight() / 2)) + (Graph1().getHeight() / 2) + centerY;
//    if(circleCnt > 1)
//    {        
//        newLine.setStart(0, 0);
//        newLine.setEnd(x / 2 - prevX, y / 2);
//        newLine.setPosition(prevX, prevY, x / 2, y / 2);
//        newLine.setPainter(linePainter);
//        newLine.setLineWidth(1);
//        newLine.setLineEndingStyle(touchgfx::Line::SQUARE_CAP_ENDING);
//    
//        Rect newRect = Rect(prevX - 2, prevY - 2, x / 2 + 2, y / 2 + 2);
//        newLine.draw(newRect);
//        newLine.invalidate();
//    }
    
    if(circleCnt > 1)
    {
        
        if(prevX > newX)
        {
            if(prevY > newY)
            {
                newLine.setPosition(newX, newY, prevX - newX + 1, prevY - newY + 1);
                newLine.setStart(0, 0);
                newLine.setEnd(prevX - newX, prevY - newY);
            }
            else
            {
                newLine.setPosition(newX, prevY, prevX - newX + 1, newY - prevY + 1);
                newLine.setStart(0, newY-prevY);
                newLine.setEnd(prevX - newX, 0);
            }
        }
        else
        {
            if(prevY > newY)
            {
                newLine.setPosition(prevX, newY, newX - prevX + 1, prevY - newY + 1);
                newLine.setStart(0, prevY - newY);
                newLine.setEnd(newX - prevX, 0);
            }
            else
            {
                newLine.setPosition(prevX, prevY, newX - prevX + 1, newY - prevY + 1);
                newLine.setStart(0, 0);
                newLine.setEnd(newX - prevX, newY - prevY);
            }
        }
        newLine.setPainter(linePainter);
        newLine.setLineWidth(1);
        newLine.setLineEndingStyle(touchgfx::Line::SQUARE_CAP_ENDING);
        
        Rect newRect = newLine.getMinimalRect();
        newLine.draw(newRect);
        
        
    }
    
    
    
    prevX = newX;
    prevY = newY;
}