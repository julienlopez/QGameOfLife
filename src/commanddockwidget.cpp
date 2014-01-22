#include "commanddockwidget.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>

CommandDockWidget::CommandDockWidget(QWidget* parent_) :
    QDockWidget(parent_)
{
    QVBoxLayout* vl = new QVBoxLayout;

    QGroupBox* gb = new QGroupBox(tr("Actions"));
    QVBoxLayout* l = new QVBoxLayout;

    m_buttonStart = new QPushButton(tr("Start"));
    connect(m_buttonStart, &QPushButton::clicked, this, &CommandDockWidget::onStartClicked);
    l->addWidget(m_buttonStart);

    m_buttonStop = new QPushButton(tr("Stop"));
    connect(m_buttonStop, &QPushButton::clicked, this, &CommandDockWidget::onStopClicked);
    m_buttonStop->setEnabled(false);
    l->addWidget(m_buttonStop);

    gb->setLayout(l);

    vl->addWidget(gb);
    vl->addStretch();

    QWidget* w = new QWidget;
    w->setLayout(vl);
    setWidget(w);
}

void CommandDockWidget::onStartClicked()
{
    m_buttonStart->setEnabled(false);
    m_buttonStop->setEnabled(true);
    emit start();
}

void CommandDockWidget::onStopClicked()
{
    m_buttonStart->setEnabled(true);
    m_buttonStop->setEnabled(false);
    emit stop();
}
