
#include <frontier/opengl.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/tabs.h>
#include <frontier/widgets/terminal.h>

GLfloat g_xRotated = 0.0;
GLfloat g_yRotated = 0.0;
GLfloat g_zRotated = 0.0;
GLdouble g_size = 1;
GLdouble g_speed = 0.01;

class DemoWindow : public Frontier::OpenGLWindow
{
 protected:

 public:
    DemoWindow(Frontier::FrontierApp* app);
    virtual ~DemoWindow();

    bool init();

    void faster(Frontier::Widget* widget);
    void slower(Frontier::Widget* widget);
};

using namespace std;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

OpenGLApp* g_app = NULL;
DemoWindow* g_mainWindow = NULL;

DemoWindow::DemoWindow(FrontierApp* app) : OpenGLWindow(app)
{
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
    colourFrame->add(new Button(getApp(), L"Red!"));
    colourFrame->add(new Button(getApp(), L"Blue!"));
    colourFrame->add(new Button(getApp(), L"Green!"));
    tabs->addTab(L"Colour", colourFrame);

    Frame* sizeFrame = new Frame(getApp(), false);
    sizeFrame->add(new Button(getApp(), L"Smaller!"));
    sizeFrame->add(new Button(getApp(), L"Bigger!"));
    tabs->addTab(L"Size", sizeFrame);

    Terminal* terminal = new Terminal(getApp());
    terminal->run("/usr/bin/top");
    tabs->addTab(L"Terminal", terminal);

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

void display()
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -4.5);

    // Red
    glColor3f(0.8, 0.2, 0.1); 

    // Rotate
    glRotatef(g_xRotated, 1.0, 0.0, 0.0);
    glRotatef(g_yRotated, 0.0, 1.0, 0.0);
    glRotatef(g_zRotated, 0.0, 0.0, 1.0);

    //glScalef(1.0, 1.0, 1.0);

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
    g_app->mouseButton(g_mainWindow, x, y, frnButton, direction);
}

void mouseMotionCallback(int x, int y)
{
    g_app->mouseMotion(g_mainWindow, x, y);
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

