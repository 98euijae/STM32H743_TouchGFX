#ifndef GRAPHPRESENTER_HPP
#define GRAPHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GraphView;

class GraphPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GraphPresenter(GraphView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~GraphPresenter() {};

private:
    GraphPresenter();

    GraphView& view;
};

#endif // GRAPHPRESENTER_HPP
