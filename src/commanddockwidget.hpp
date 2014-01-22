#ifndef COMMANDDOCKWIDGET_HPP
#define COMMANDDOCKWIDGET_HPP

#include <QDockWidget>

class QPushButton;

class CommandDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit CommandDockWidget(QWidget* parent_ = 0);

signals:
    void start();
    void stop();

private slots:
    void onStartClicked();
    void onStopClicked();

private:
    QPushButton* m_buttonStart;
    QPushButton* m_buttonStop;

};

#endif // COMMANDDOCKWIDGET_HPP
