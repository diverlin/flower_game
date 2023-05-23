#include "grid.h"

#include <iostream>

Grid::Grid(int rows, int columns)
    :
    m_rows(rows),
    m_columns(columns),
    m_array(rows*columns)
{
    std::cout << "m_array.capacity=" << m_array.capacity() << std::endl;
}

Grid::~Grid()
{

}
