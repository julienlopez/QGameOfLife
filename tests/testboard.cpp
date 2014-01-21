#include <board.hpp>

#include <gtest/gtest.h>

TEST(TestBoard, CreateEmptyBoard)
{
    Board board(0);
    ASSERT_EQ(0, board.width());
    ASSERT_EQ(0, board.height());
    for(std::size_t x = 0; x < board.width(); x++)
        for(std::size_t y = 0; y < board.height(); y++)
            EXPECT_FALSE(board(x, y));
}

TEST(TestBoard, CreateSquareBoard)
{
    Board board(10);
    ASSERT_EQ(10, board.width());
    ASSERT_EQ(10, board.height());
    for(std::size_t x = 0; x < board.width(); x++)
        for(std::size_t y = 0; y < board.height(); y++)
            EXPECT_FALSE(board(x, y));
}

TEST(TestBoard, CreateRectangularBoard)
{
    Board board(7, 8);
    ASSERT_EQ(7, board.width());
    ASSERT_EQ(8, board.height());
    for(std::size_t x = 0; x < board.width(); x++)
        for(std::size_t y = 0; y < board.height(); y++)
            EXPECT_FALSE(board(x, y));
}

TEST(TestBoard, AliveNeighboursOnEmptyBoard)
{
    Board board(5);
    for(std::size_t x = 0; x < board.width(); x++)
        for(std::size_t y = 0; y < board.height(); y++)
            EXPECT_EQ(0, board.aliveNeighbours(x, y));
}
