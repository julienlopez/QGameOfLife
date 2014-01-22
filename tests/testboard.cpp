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

TEST(TestBoard, AliveNeighboursOnBoardWithTwoAliveCellsNextToEachOther)
{
    Board board(5);
    board(0, 1) = true;
    board(0, 0) = true;
    EXPECT_TRUE(board(0, 0));
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        std::size_t count = b.aliveNeighbours(x,y);
        if(x == 0 && y < 3)
            return count == 1;
        if(x == 1)
        {
            if(y<2) return count == 2;
            if(y == 2) return count == 1;
        }
        return count == 0;
    }, true));
}

TEST(TestBoard, UpdatedCellValueOnlyOneCellWillBecomeAlive)
{
    Board board(3, 1);
    board(0, 0) = true;
    board(2, 0) = true;
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b.updatedCellValue(x,y) == (x == 2 && y == 2);
    }, true));
}

TEST(TestBoard, UpdatedCellValueCellWillDieIfLessThanTwoNeighbours)
{
    Board board(3);
    board(1, 1) = true;
    ASSERT_TRUE(checkForEachCell(board, std::bind(&Board::updatedCellValue, _1, _2, _3), false));
}

TEST(TestBoard, UpdatedCellValueCellWillStayAliveIfTwoNeighbours)
{
    Board board(3, 1);
    board(0, 0) = true;
    board(1, 0) = true;
    board(2, 0) = true;
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b.updatedCellValue(x,y) == (x == 1 && y == 0);
    }, true));
}

TEST(TestBoard, UpdatedCellValueCellWillStayAliveIfThreeNeighbours)
{
    Board board(3, 2);
    board(0, 0) = true;
    board(1, 0) = true;
    board(2, 0) = true;
    board(1, 1) = true;
    ASSERT_TRUE(checkForEachCell(board, std::bind(&Board::updatedCellValue, _1, _2, _3), true));
}

TEST(TestBoard, UpdatedCellValueCellWillDieIfMoreThanThreeNeighbours)
{
    Board board(3, 3);
    board(1, 0) = true;
    board(0, 1) = true;
    board(1, 1) = true;
    board(2, 1) = true;
    board(1, 2) = true;
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b.updatedCellValue(x,y) != (x == 1 && y == 1);
    }, true));
}

TEST(TestBoard, UpdateSimpleBlock)
{
    Board board(4);
    board.toggle(1, 1);
    board.toggle(1, 2);
    board.toggle(2, 1);
    board.toggle(2, 2);
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b(x,y) == ((x == 1 || x == 2) && (y == 1 || y == 2));
    }, true));
    board.update();
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b(x,y) == ((x == 1 || x == 2) && (y == 1 || y == 2));
    }, true));
}

TEST(TestBoard, UpdateSimpleBlinker)
{
    Board board(5);
    board.toggle(1, 2);
    board.toggle(2, 2);
    board.toggle(3, 2);
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b(x,y) == ((x == 1 || x == 2 || x == 3) && y == 2);
    }, true));
    board.update();
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b(x,y) == (x == 2 && (y == 1 || y == 2 || y == 3));
    }, true));
    board.update();
    ASSERT_TRUE(checkForEachCell(board, [](const Board& b, std::size_t x, std::size_t y)
    {
        return b(x,y) == ((x == 1 || x == 2 || x == 3) && y == 2);
    }, true));
}
