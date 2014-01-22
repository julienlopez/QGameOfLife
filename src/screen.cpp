#include "screen.hpp"

#include <board.hpp>

#include <cmath>

#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

Screen::Screen(QWidget* parent_) :
    QWidget(parent_), m_board(new Board(50))
{
    //just a small example
    m_board->toggle(4, 5);
    m_board->toggle(5, 5);
    m_board->toggle(6, 5);
    m_board->toggle(6, 4);
    m_board->toggle(5, 3);

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(100);
    connect(m_updateTimer, &QTimer::timeout, this, &Screen::updateBoard);

    setMinimumSize(800, 600);
}

Screen::~Screen()
{}

bool Screen::isRunning() const
{
    return m_updateTimer->isActive();
}

void Screen::mousePressEvent(QMouseEvent* evt)
{
    if(isRunning()) return;
    if(evt->buttons() != Qt::LeftButton) return;

    auto features = computeScreenFeatures();
    QPointF click = evt->localPos() - QPoint(features.xMargin, features.yMargin);
    click /= features.resolution;
    QPoint p(floor(click.x()), floor(click.y()));
    m_board->toggle(p.x(), p.y());
    update();
}

void Screen::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);

    auto features = computeScreenFeatures();

    QPainter p(this);
    p.translate(features.xMargin, features.yMargin);
    p.scale(features.resolution, features.resolution);

    QPen pen = p.pen();
    pen.setColor(Qt::black);
    pen.setWidthF(0.02);
    p.setPen(pen);

    QBrush b = p.brush();
    b.setColor(Qt::white);
    p.setBrush(b);

    fillCells(p);
}

Screen::ScreenFeatures Screen::computeScreenFeatures() const
{
    int w = width() - 2;
    int h = height() - 2;

    double xResolution = (double)w/m_board->width();
    double yResolution = (double)h/m_board->height();

    double resolution = std::min(xResolution, yResolution);

    int xMargin = w - resolution * m_board->width() + 2;
    int yMargin = h - resolution * m_board->height() + 2;

    return {resolution, xMargin/2, yMargin/2};
}

void Screen::fillCells(QPainter& p) const
{
    std::size_t boardWidth = m_board->width();
    std::size_t boardHeight = m_board->width();

    static QBrush blackBrush(Qt::black);
    static QBrush whiteBrush(Qt::white);

    for(std::size_t i = 0; i < boardWidth; i++)
        for(std::size_t j = 0; j < boardHeight; j++)
        {
            p.setBrush((*m_board)(i,j)?blackBrush:whiteBrush);
            p.drawRect(i, j, 1, 1);
        }
}

void Screen::start()
{
    m_updateTimer->start();
}

void Screen::stop()
{
    m_updateTimer->stop();
}

void Screen::updateBoard()
{
    if(m_board)
        m_board->update();
    update();
}
