#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

class Board
{
public:
    using storage_type = std::vector<bool>;

    Board(std::size_t size);
    Board(std::size_t width_, std::size_t height_);

    Board(const Board&) = delete;
    Board(Board&&) = delete;

    std::size_t height() const;
    std::size_t width() const;

    bool operator()(std::size_t x, std::size_t y) const;
    storage_type::reference operator()(std::size_t x, std::size_t y);

    void update();

    std::size_t aliveNeighbours(std::size_t x, std::size_t y) const;

    bool updatedCellValue(std::size_t x, std::size_t y) const;

    void toggle(std::size_t x, std::size_t y);

private:
    std::size_t m_width;
    std::size_t m_height;
    storage_type m_cells;
};

#endif // BOARD_HPP
