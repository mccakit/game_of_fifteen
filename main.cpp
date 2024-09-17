#include <iostream>
#include <vector>
#include <algorithm>
#include "random.h"
class Array2D
{
public:
    Array2D(const int row_size, const int col_size):
        m_dimensions{row_size, col_size},
        m_arr(row_size, std::vector<int>(col_size))
    {
        for (int row{}; row < row_size; ++row)
        {
            for (int col{}; col < col_size; ++col)
            {
                m_arr[row][col] = 0;
            }
        }
    }
    void fillOrdered()
    {
        int start{1};
        for (int row{}; row < m_dimensions[0]; ++row)
        {
            for (int col{}; col < m_dimensions[1]; ++col)
            {
                m_arr[row][col] = start;
                ++start;
            }
        }
    }
    void shuffle()
    {
        std::shuffle(m_arr.begin(),m_arr.end(),Random::generate());
        for (auto& arr:m_arr)
        {
            std::shuffle(arr.begin(),arr.end(),Random::generate());
        }
    }
    int& operator()(const int row, const int col)
    {
        return m_arr[row-1][col-1];
    }
    friend std::ostream& operator << (std::ostream& out, const Array2D& arr)
    {
        for (int row{}; row < arr.m_dimensions[0]; ++row)
        {
            for (int col{}; col < arr.m_dimensions[1]; ++col)
            {
               out << arr.m_arr[row][col] << " ";
            }
            out << "\n";
        }
        return out;
    }
    friend std::array<int,2> find(const Array2D& arr, const int searchTarget)
    {
        for (int row{}; row < arr.m_dimensions[0]; ++row)
        {
            for (int col{}; col < arr.m_dimensions[1]; ++col)
            {
                if (arr.m_arr[row][col] == searchTarget)
                {
                    return {row+1,col+1};
                }
            }
        }
        return {-1};
    }
private:
    std::vector<std::vector<int> > m_arr{};
    std::vector<int> m_dimensions{};
};

class Game
{
public:
    Game()
    {
        board.fillOrdered();
        board(4,4) = 0;
        board.shuffle();
        zeroLocation = find(board,0);
    }
    const Array2D& getBoard()
    {
        return board;
    }
    const std::array<int,2>& getZeroLocation() const
    {
        return zeroLocation;
    }
    void swap(char direction)
    {
        switch (direction)
        {
        case 'w':
            if (zeroLocation[0] != 4)
            {
                std::swap(board(zeroLocation[0]+1, zeroLocation[1]), board(zeroLocation[0], zeroLocation[1]));
                zeroLocation[0] += 1;
            }
            break;
        case 's':
            if (zeroLocation[0] != 1)
            {
                std::swap(board(zeroLocation[0]-1, zeroLocation[1]), board(zeroLocation[0], zeroLocation[1]));
                zeroLocation[0] -= 1;
            }
            break;
        case 'd':
            if (zeroLocation[1] != 1)
            {
                std::swap(board(zeroLocation[0], zeroLocation[1]-1), board(zeroLocation[0], zeroLocation[1]));
                zeroLocation[1] -= 1;
            }
            break;
        case 'a':
            if (zeroLocation[1] != 4)
            {
                std::swap(board(zeroLocation[0], zeroLocation[1]+1), board(zeroLocation[0], zeroLocation[1]));
                zeroLocation[1] += 1;
            }
            break;
        default:
            break;
        }
    }
private:
    Array2D board{4,4};
    std::array<int,2> zeroLocation{0};
};

int main()
{
    Game game{};
    std::cout << game.getZeroLocation()[0] << ", " << game.getZeroLocation()[1] << "\n";
    char input{};
    while (true)
    {
        std::cout<< game.getBoard() << "\n";
        std::cin >> input;
        game.swap(input);
        std::cout << game.getZeroLocation()[0] << ", " << game.getZeroLocation()[1] << "\n";
    }

    return 0;
}
