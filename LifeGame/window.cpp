#include "glwidget.h"
#include "widget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

Window::Window()
{
    setWindowTitle(tr("Life Game"));
    resize(1024,768);
    Widget *native = new Widget(&helper, this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    timer->start(50);
}
