
#include <frontier/widgets/grid.h>

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

Grid::Grid(FrontierApp* app) : Widget(app, L"Grid")
{
    m_colMinSizes = NULL;
    m_colMaxSizes = NULL;
    m_rowMinSizes = NULL;
    m_rowMaxSizes = NULL;
}

Grid::Grid(FrontierWindow* window) : Widget(window, L"Grid")
{
    m_colMinSizes = NULL;
    m_colMaxSizes = NULL;
    m_rowMinSizes = NULL;
    m_rowMaxSizes = NULL;
}

Grid::~Grid()
{
    clearChildren();
}

void Grid::clear()
{
    clearChildren();

    setDirty();
}

void Grid::clearChildren()
{
    for (GridItem* item : m_grid)
    {
        item->widget->decRefCount();
        item->widget->setParent(NULL);
        delete item;
    }

    freeSizes();

    m_grid.clear();
}


void Grid::put(int x, int y, Widget* widget)
{
    put(x, y, widget, m_app->getTheme()->getColour(COLOUR_WINDOW_BACKGROUND));
}

void Grid::put(int x, int y, Widget* widget, uint32_t background)
{
    widget->incRefCount();
    widget->setParent(this);

    GridItem* item = getGridItem(x, y);
    if (item == NULL)
    {
        item = new GridItem();
        item->x = x;
        item->y = y;
        m_grid.push_back(item);
    }
    else
    {
        if (item->widget != NULL)
        {
            item->widget->decRefCount();
            item->widget->setParent(NULL);
        }
    }
    item->widget = widget;
    item->background = background;
}

GridItem* Grid::getGridItem(int x, int y)
{
    for (GridItem* item : m_grid)
    {
        if (item->x == x && item->y == y)
        {
            return item;
        }
    }

    return NULL;
}

Widget* Grid::getItem(int x, int y)
{
    GridItem* item = getGridItem(x, y);
    if (item == NULL)
    {
        return NULL;
    }

    return item->widget;
}

Size Grid::getGridSize()
{
    Size size(0, 0);
    for (GridItem* item : m_grid)
    {
        if (item->x >= size.width)
        {
            size.width = item->x + 1;
        }
        if (item->y >= size.height)
        {
            size.height = item->y + 1;
        }
    }
    return size;
}

void Grid::calculateSize()
{
    freeSizes();

    int margin = (int)getStyle(STYLE_MARGIN);
    int padding = (int)getStyle(STYLE_PADDING);

    Size gridSize = getGridSize();
#if 0
    log(DEBUG, "calculateSize: gridSize=%d,%d", gridSize.width, gridSize.height);
#endif

    m_colMinSizes = new int[gridSize.width];
    m_colMaxSizes = new int[gridSize.width];
    m_rowMinSizes = new int[gridSize.height];
    m_rowMaxSizes = new int[gridSize.height];

    memset(m_colMinSizes, 0, sizeof(int) * gridSize.width);
    memset(m_colMaxSizes, 0, sizeof(int) * gridSize.width);
    memset(m_rowMinSizes, 0, sizeof(int) * gridSize.height);
    memset(m_rowMaxSizes, 0, sizeof(int) * gridSize.height);

    m_minSize.set(0, 0);
    m_maxSize.set(0, 0);

    for (GridItem* item : m_grid)
    {
        item->widget->calculateSize();
        int col = item->x;
        int row = item->y;
        Size minSize = item->widget->getMinSize();
        Size maxSize = item->widget->getMaxSize();

        if (minSize.width > m_colMinSizes[col])
        {
            m_colMinSizes[col] = minSize.width;
        }
        if (maxSize.width > m_colMaxSizes[col])
        {
            m_colMaxSizes[col] = maxSize.width;
        }

        if (minSize.height > m_rowMinSizes[row])
        {
            m_rowMinSizes[row] = minSize.height;
        }
        if (maxSize.height > m_rowMaxSizes[row])
        {
            m_rowMaxSizes[row] = maxSize.height;
        }
    }

    int col;
    for (col = 0; col < gridSize.width; col++)
    {
#if 0
        log(DEBUG, "calculateSize: Column %d: min=%d, max=%d", col, m_colMinSizes[col], m_colMaxSizes[col]);
#endif
        m_minSize.width += m_colMinSizes[col];
        m_maxSize.width += m_colMaxSizes[col];
    }
    int row;
    for (row = 0; row < gridSize.height; row++)
    {
#if 0
        log(DEBUG, "Grid::calculateSize: Row %d: min=%d, max=%d", row, m_rowMinSizes[row], m_rowMaxSizes[row]);
#endif
        m_minSize.height += m_rowMinSizes[row];
        m_maxSize.height += m_rowMinSizes[row];
    }

    m_minSize.width += padding * (gridSize.width - 1);
    m_minSize.height += padding * (gridSize.height - 1);
    m_maxSize.width += padding * (gridSize.width - 1);
    m_maxSize.height += padding * (gridSize.height - 1);

    m_minSize.width += margin;
    m_minSize.height += margin;
    m_maxSize.width += margin;
    m_maxSize.height += margin;
}

void Grid::layout()
{
    Size gridSize = getGridSize();

    int margin = (int)getStyle(STYLE_MARGIN);
    int padding = (int)getStyle(STYLE_PADDING);

    if (gridSize.width == 0 || gridSize.height == 0)
    {
        return;
    }

    int width = m_setSize.width;
    int height = m_setSize.height;
    width -= (2 * margin);
    height -= (2 * margin);

    width -= padding * (gridSize.width - 1);
    height -= padding * (gridSize.height - 1);

    int widthq = width / gridSize.width;
    int heightq = height / gridSize.height;

    int slackableX = 0;
    int minX = 0;
    int col;
    for (col = 0; col < gridSize.width; col++)
    {
        minX += m_colMinSizes[col];
        if (m_colMaxSizes[col] > widthq)
        {
            slackableX++;
        }
    }

    int slackableY = 0;
    int minY = 0;
    int row;
    for (row = 0; row < gridSize.height; row++)
    {
        minY += m_rowMinSizes[row];
        if (m_rowMaxSizes[row] > heightq)
        {
            slackableY++;
        }
    }

    int slackX = width - minX;
    int colSizes[gridSize.width];
    for (col = 0; col < gridSize.width; col++)
    {
        if (widthq > m_colMaxSizes[col])
        {
            colSizes[col] = m_colMaxSizes[col];
        }
        else
        {
            colSizes[col] = m_colMinSizes[col];
        }

        if (colSizes[col] < m_colMaxSizes[col])
        {
            int s = slackX / slackableX;
            slackX -= s;
            slackableX--;

            colSizes[col] += s;
            if (colSizes[col] > m_colMaxSizes[col])
            {
                s = colSizes[col] - m_colMaxSizes[col];
                colSizes[col] = m_colMaxSizes[col];
                slackX += s;
            }
#if 0
            log(DEBUG, "layout: Col %d: Size=%d", col, colSizes[col]);
#endif
        }
    }

    int slackY = height - minY;
    int rowSizes[gridSize.height];
    for (row = 0; row < gridSize.height; row++)
    {
        if (heightq > m_rowMaxSizes[row])
        {
            rowSizes[row] = m_rowMaxSizes[row];
        }
        else
        {
            rowSizes[row] = m_rowMinSizes[row];
        }

        if (rowSizes[row] < m_rowMaxSizes[row])
        {
            int s = slackY / slackableY;
            slackY -= s;
            slackableY--;

            rowSizes[row] += s;
            if (rowSizes[row] > m_rowMaxSizes[row])
            {
                s = rowSizes[row] - m_rowMaxSizes[row];
                rowSizes[row] = m_rowMaxSizes[row];
                slackY += s;
            }
        }
#if 0
        log(DEBUG, "layout: Row %d: Size=%d", row, rowSizes[row]);
#endif
    }

    int y = margin;
    for (row = 0; row < gridSize.height; row++)
    {
        int x = margin;
        for (col = 0; col < gridSize.width; col++)
        {
            GridItem* item = getGridItem(col, row);
            if (item != NULL && item->widget != NULL)
            {
                //Size minSize = item->widget->getMinSize();
                item->widget->setPosition(x, y);
                item->widget->setSize(Size(colSizes[col], rowSizes[row]));
                item->widget->layout();
            }

#if 0
            log(DEBUG, "layout: Set Item: %d, %d, size=%d,%d (%p)", col, row, colSizes[col], rowSizes[row], item);
#endif

            x += colSizes[col] + padding;
        }
        y += rowSizes[row] + padding;
    }
}

bool Grid::draw(Geek::Gfx::Surface* surface)
{
    surface->clear(m_app->getTheme()->getColour(COLOUR_WINDOW_BACKGROUND));
    for (GridItem* item : m_grid)
    {
        Widget* child = item->widget;
        SurfaceViewPort viewport(surface, child->getX(), child->getY(), child->getWidth(), child->getHeight());
        viewport.clear(item->background);
        child->draw(&viewport, Rect(0, 0, child->getWidth(), child->getHeight()));

#if 0
        viewport.drawRect(0, 0, child->getWidth(), child->getHeight(), 0x00ff00);
#endif
    }
    return true;
}

Widget* Grid::handleEvent(Frontier::Event* event)
{
    if (event->is(FRONTIER_EVENT_MOUSE))
    {
        MouseEvent* mouseEvent = (MouseEvent*)event;
        int x = mouseEvent->x;
        int y = mouseEvent->y;

        for (GridItem* item : m_grid)
        {
            Widget* child = item->widget;
            if (child->intersects(x, y))
            {
                return child->handleEvent(event);
            }
        }
        if (event->eventType == FRONTIER_EVENT_MOUSE_MOTION)
        {
            return this;
        }
    }
    return NULL;
}

void Grid::freeSizes()
{
    if (m_colMinSizes != NULL)
    {
        delete[] m_colMinSizes;
        m_colMinSizes = NULL;
    }
    if (m_colMaxSizes != NULL)
    {
        delete[] m_colMaxSizes;
        m_colMaxSizes = NULL;
    }
    if (m_rowMinSizes != NULL)
    {
        delete[] m_rowMinSizes;
        m_rowMinSizes = NULL;
    }
    if (m_rowMaxSizes != NULL)
    {
        delete[] m_rowMaxSizes;
        m_rowMaxSizes = NULL;
    }
}

