
#include <frontier/engines/opengl.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/tabs.h>
#include <frontier/widgets/terminal.h>
#include <frontier/widgets/colourbutton.h>

#ifdef MPV_FOUND
#include <frontier/widgets/video.h>
#endif

GLfloat g_xRotated = 0.0;
GLfloat g_yRotated = 0.0;
GLfloat g_zRotated = 0.0;
GLdouble g_size = 1;
GLdouble g_speed = 0.10;

class DemoWindow : public Frontier::FrontierWindow
{
 protected:
    Geek::Gfx::Colour m_colour;

    void onColourSelected(Geek::Gfx::Colour colour);

 public:
    DemoWindow(Frontier::FrontierApp* app);
    virtual ~DemoWindow();

    bool init();

    void faster(Frontier::Widget* widget);
    void slower(Frontier::Widget* widget);

     Geek::Gfx::Colour getColour() { return m_colour; }
};

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

OpenGLApp* g_app = NULL;
DemoWindow* g_mainWindow = NULL;

DemoWindow::DemoWindow(FrontierApp* app) : FrontierWindow(app, L"OpenGL Demo", WINDOW_NORMAL)
{
    setSize(Size(150, 100));

    m_colour = Colour(255, 0, 0);
}

DemoWindow::~DemoWindow()
{
}

bool DemoWindow::init()
{
    Tabs* tabs = new Tabs(getApp(), true, TAB_TOP);

    Frame* speedFrame = new Frame(getApp(), false);
    Button* faster = new Button(getApp(), L"Faster!");
    faster->clickSignal().connect(sigc::mem_fun(*this, &DemoWindow::faster));
    Button* slower = new Button(getApp(), L"Slower!");
    slower->clickSignal().connect(sigc::mem_fun(*this, &DemoWindow::slower));
    speedFrame->add(faster);
    speedFrame->add(slower);
    tabs->addTab(L"Speed", speedFrame);

    Frame* colourFrame = new Frame(getApp(), false);
    ColourButton* colourButton = new ColourButton(getApp(), m_colour);
    colourButton->colourSelectedSignal().connect(sigc::mem_fun(*this, &DemoWindow::onColourSelected));

    colourFrame->add(colourButton);
    tabs->addTab(L"Colour", colourFrame);

    Frame* sizeFrame = new Frame(getApp(), false);
    sizeFrame->add(new Button(getApp(), L"Smaller!"));
    sizeFrame->add(new Button(getApp(), L"Bigger!"));
    tabs->addTab(L"Size", sizeFrame);

#ifdef MPV_FOUND
    Frame* videoFrame = new Frame(getApp(), false);
    videoFrame->add(new Label(getApp(), L"A video!"));
    VideoWidget* video;
    videoFrame->add(video = new VideoWidget(getApp()));
    video->setFile("../src/demo_opengl/file_example_MP4_480_1_5MG.mp4");
    video->play();
    videoFrame->add(new Label(getApp(), L"Yay!"));
    tabs->addTab(L"Video", videoFrame);
#endif

    setContent(tabs);
    
    return true;
}

void DemoWindow::faster(Widget* widget)
{
    g_speed *= 1.5;
}

void DemoWindow::slower(Widget* widget)
{
    g_speed *= 0.5;
}

void DemoWindow::onColourSelected(Geek::Gfx::Colour colour)
{
    m_colour = colour;
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -4.5);

    Colour c = g_mainWindow->getColour();
    glColor3f(c.redFloat(), c.greenFloat(), c.blueFloat());

    // Rotate
    glRotatef(g_xRotated, 1.0, 0.0, 0.0);
    glRotatef(g_yRotated, 0.0, 1.0, 0.0);
    glRotatef(g_zRotated, 0.0, 0.0, 1.0);

    // Draw our teapot!
    glutSolidTeapot(g_size);

    // Draw our Frontier UI
    g_app->draw();

    glFlush();
}

void reshapeCallback(int w, int h)
{
    if (h == 0 || w == 0)
    {
        return;  //Nothing is visible then, so return
    }

    g_app->setScreenSize(Size(w, h));

    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();

    gluPerspective(40.0, (GLdouble)w / (GLdouble)h, 0.5, 20.0);
 
    glViewport(0, 0, w, h);
}

void keyboardCallback(unsigned char key, int x, int y)
{
}

void mouseCallback(int button, int stat, int x, int y)
{
    int frnButton = BUTTON_LEFT;
    if (button == 0)
    {
        frnButton = BUTTON_LEFT;
    }
    else if (button == 2)
    {
        frnButton = BUTTON_RIGHT;
    }
    bool direction = !stat;
    g_app->mouseButton(x, y, frnButton, direction);
}

void mouseMotionCallback(int x, int y)
{
    g_app->mouseMotion(x, y);
}

void idleFunc(void)
{
    g_yRotated += g_speed;
     
    display();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Frontier OpenGL Demo");

    g_app = new OpenGLApp();
    g_app->init();
    g_app->setScreenSize(Size(500, 500));

    g_mainWindow = new DemoWindow(g_app);
    g_mainWindow->show();
    g_mainWindow->setPosition(Vector2D(0, 0));

    g_xRotated = 33;
    g_yRotated = 40;
    g_zRotated = 30.0;

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshapeCallback);
    //glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);
    glutPassiveMotionFunc(mouseMotionCallback);
    glutMotionFunc(mouseMotionCallback);

    glutIdleFunc(idleFunc);

    glutMainLoop();

    return 0;
}

