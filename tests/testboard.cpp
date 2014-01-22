#include <board.hpp>

#include <gtest/gtest.h>

#include <functional>
#include <cmath>

using namespace std::placeholders;

template<class PREDICAT, class RESULT>
::testing::AssertionResult checkForEachCell(const Board& board, PREDICAT predicat, RESULT expected)
{
    for(std::size_t x = 0; x < board.width(); x++)
        for(std::size_t y = 0; y < board.height(); y++)
            if(predicat(board, x, y) != expected)
                return ::testing::AssertionFailure() << "predicat failed at " << std::to_string(x) << ", " << std::to_string(y);
    return ::testing::AssertionSuccess();
}

TEST(TestBoard, CreateEmptyBoard)
{
    Board board(0);
    ASSERT_EQ(0, board.width());
    ASSERT_EQ(0, board.height());
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y){ return b(x,y); }, true));
}

TEST(TestBoard, CreateSquareBoard)
{
    Board board(10);
    ASSERT_EQ(10, board.width());
    ASSERT_EQ(10, board.height());
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y){ return b(x,y); }, false));
}

TEST(TestBoard, CreateRectangularBoard)
{
    Board board(7, 8);
    ASSERT_EQ(7, board.width());
    ASSERT_EQ(8, board.height());
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y){ return b(x,y); }, false));
}

TEST(TestBoard, AliveNeighboursOnEmptyBoard)
{
    Board board(5);
    ASSERT_TRUE(checkForEachCell(board, std::bind(&Board::aliveNeighbours, _1, _2, _3), 0));
}

TEST(TestBoard, AliveNeighboursOnBoardWithOneAliveCell)
{
    Board board(5);
    board(0, 0) = true;
    EXPECT_TRUE(board(0, 0));
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        int dist = pow(x, 2) + pow(y,2);
        return b.aliveNeighbours(x,y) == ((dist > 0 && dist <= 2) ? 1 : 0);
    }, true));
}
