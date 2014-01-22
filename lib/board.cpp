#include "board.hpp"

Board::Board(std::size_t size): m_width(size), m_height(size), m_cells(m_width*m_height, false)
{}

Board::Board(std::size_t width_, std::size_t height_): m_width(width_), m_height(height_), m_cells(m_width*m_height, false)
{}

std::size_t Board::height() const
{
    return m_height;
}

std::size_t Board::width() const
{
    return m_width;
}

bool Board::operator()(std::size_t x, std::size_t y) const
{
    return m_cells[y*m_width + x];
}

Board::storage_type::reference Board::operator()(std::size_t x, std::size_t y)
{
    return m_cells[y*m_width + x];
}

void Board::update()
{
    Board newValues(m_width, m_height);
    for(std::size_t x = 0; x < m_width; x++)
        for(std::size_t y = 0; y < m_height; y++)
            newValues(x, y) = updatedCellValue(x, y);
    m_cells = std::move(newValues.m_cells);
}

std::size_t Board::aliveNeighbours(std::size_t x, std::size_t y) const
{
    std::size_t minX = (x == 0 ? 0 : x-1);
    std::size_t maxX = (x >= m_width-1 ? m_width : x+2);

    std::size_t minY = (y == 0 ? 0 : y-1);
    std::size_t maxY = (y >= m_height-1 ? m_height : y+2);

    std::size_t count = 0;

    for(std::size_t i = minX; i < maxX; i++)
        for(std::size_t j = minY; j < maxY; j++)
            if((x != i || y != j) && (*this)(i, j))count++;

    return count;
}

bool Board::updatedCellValue(std::size_t x, std::size_t y) const
{
    bool actualValue = (*this)(x, y);
    std::size_t nbOfAliveNeighbours = aliveNeighbours(x, y);
    if(actualValue)
        return nbOfAliveNeighbours >= 2 && nbOfAliveNeighbours <= 3;
    else
        return nbOfAliveNeighbours == 3;
}

void Board::toggle(std::size_t x, std::size_t y)
{
    (*this)(x, y) = !(*this)(x, y);
}
