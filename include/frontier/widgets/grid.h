#ifndef __FRONTIER_WIDGETS_GRID_H_
#define __FRONTIER_WIDGETS_GRID_H_

#include <frontier/widgets.h>

namespace Frontier
{
struct GridItem
{
    int x;
    int y;
    uint32_t background;
    Widget* widget;
};

/**
 * \brief A layout Widget that displays Widgets in a Grid
 *
 * \ingroup widgets
 */
class Grid : public Frontier::Widget
{
 protected:
    std::vector<GridItem*> m_grid;

    int* m_colMinSizes;
    int* m_colMaxSizes;
    int* m_rowMinSizes;
    int* m_rowMaxSizes;

    void freeSizes();
    void clearChildren();

    virtual void calculateSize();
    virtual void layout();

 public:
    Grid(FrontierApp* app);
    Grid(FrontierWindow* window);
    virtual ~Grid();

    virtual void put(int x, int y, Widget* widget);
    virtual void put(int x, int y, Widget* widget, uint32_t background);
    GridItem* getGridItem(int x, int y);
    Widget* getItem(int x, int y);
    Size getGridSize();
    void clear();

    virtual bool draw(Geek::Gfx::Surface* surface);

    virtual Widget* handleEvent(Frontier::Event* event);

    virtual void activateNext(Widget* activeChild = NULL);
};

};

#endif
