
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
    for (GridItem* item : m_grid)
    {
        item->widget->decRefCount();
    }

    freeSizes();
}

void Grid::put(int x, int y, Widget* widget)
{
    widget->incRefCount();
    widget->setParent(this);

    GridItem* item = getGridItem(x, y);
    if (item == NULL)
    {
        item = new GridItem();
        item->x = x;
        item->y = y;
        item->widget = widget;
        m_grid.push_back(item);
    }
    else
    {
        if (item->widget != NULL)
        {
            item->widget->decRefCount();
        }
        item->widget = widget;
    }
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

    m_minSize.width += m_padding * (gridSize.width - 1);
    m_minSize.height += m_padding * (gridSize.height - 1);
    m_maxSize.width += m_padding * (gridSize.width - 1);
    m_maxSize.height += m_padding * (gridSize.height - 1);

    m_minSize.width += m_margin;
    m_minSize.height += m_margin;
    m_maxSize.width += m_margin;
    m_maxSize.height += m_margin;
}

void Grid::layout()
{
    Size gridSize = getGridSize();

    if (gridSize.width == 0 || gridSize.height == 0)
    {
        return;
    }

    int width = m_setSize.width;
    int height = m_setSize.height;
    width -= (2 * m_margin);
    height -= (2 * m_margin);

    width -= m_padding * (gridSize.width - 1);
    height -= m_padding * (gridSize.height - 1);

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
            log(DEBUG, "layout: Col %d: Size=%d", col, colSizes[col]);
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
        log(DEBUG, "layout: Row %d: Size=%d", row, rowSizes[row]);
    }

    int y = m_margin;
    for (row = 0; row < gridSize.height; row++)
    {
        int x = m_margin;
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

            x += colSizes[col] + m_padding;
        }
        y += rowSizes[row] + m_padding;
    }
}

bool Grid::draw(Geek::Gfx::Surface* surface)
{
    for (GridItem* item : m_grid)
    {
        Widget* child = item->widget;
        SurfaceViewPort viewport(surface, child->getX(), child->getY(), child->getWidth(), child->getHeight());
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
    }
    if (m_colMaxSizes != NULL)
    {
        delete[] m_colMaxSizes;
    }
    if (m_rowMinSizes != NULL)
    {
        delete[] m_rowMinSizes;
    }
    if (m_rowMaxSizes != NULL)
    {
        delete[] m_rowMaxSizes;
    }
}

