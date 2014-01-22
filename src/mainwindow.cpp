#include "mainwindow.hpp"
#include "screen.hpp"
#include "commanddockwidget.hpp"

MainWindow::MainWindow(QWidget* parent_) :
    QMainWindow(parent_)
{
    Screen* screen = new Screen;
    setCentralWidget(screen);

    CommandDockWidget* command = new CommandDockWidget;
    addDockWidget(Qt::RightDockWidgetArea, command, Qt::Vertical);

    connect(command, &CommandDockWidget::start, screen, &Screen::start);
    connect(command, &CommandDockWidget::stop, screen, &Screen::stop);
}
