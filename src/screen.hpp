#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>

#include <QWidget>

class Board;

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget* parent_ = 0);
    virtual ~Screen();

    bool isRunning() const;

protected:
    virtual void mousePressEvent(QMouseEvent* evt) override;
    virtual void paintEvent(QPaintEvent* evt) override;

private:
    struct ScreenFeatures
    {
        double resolution;
        int xMargin;
        int yMargin;
    };

    std::unique_ptr<Board> m_board;
    QTimer* m_updateTimer;

    ScreenFeatures computeScreenFeatures() const;

    void fillCells(QPainter& p) const;

public slots:
    void start();
    void stop();

private slots:
    void updateBoard();
};

#endif // SCREEN_HPP
