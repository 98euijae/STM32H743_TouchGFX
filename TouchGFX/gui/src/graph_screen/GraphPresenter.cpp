#include <gui/graph_screen/GraphView.hpp>
#include <gui/graph_screen/GraphPresenter.hpp>

GraphPresenter::GraphPresenter(GraphView& v)
    : view(v)
{

}

void GraphPresenter::activate()
{

}

void GraphPresenter::deactivate()
{

}

void GraphPresenter::graphChanged()
{
    view.setGraph(model->getDataX(), model->getDataY(), model->getReadSize());
}