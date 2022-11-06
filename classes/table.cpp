#include <iostream>
#include <string>
#include <vector>

#include "table.h"

using namespace std;

Table::Table()
{
    table = vector<vector<string>>();
    columnHeaders = vector<string>();
    rowHeaders = vector<string>();
}
void Table::addColumnHeader(string header, int index)
{
    if (index == -1)
    {
        columnHeaders.push_back(header);
    }
    else
    {
        columnHeaders.insert(columnHeaders.begin() + index, header);
    }
}
void Table::addRowHeader(string header, int index)
{
    if (index == -1)
    {
        rowHeaders.push_back(header);
    }
    else
    {
        rowHeaders.insert(rowHeaders.begin() + index, header);
    }
}
void Table::addRow(vector<string> row, int index)
{
    if (index == -1)
    {
        table.push_back(row);
    }
    else
    {
        table.insert(table.begin() + index, row);
    }
}
void Table::addCell(string cell, int row, int column)
{
    table[row][column] = cell;
}
int Table::getNumRows()
{
    int res = table.size();
    if (res < rowHeaders.size())
    {
        res = rowHeaders.size();
    }
    return res;
}
int Table::getNumColumns()
{
    int max = 0;
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].size() > max)
        {
            max = table[i].size();
        }
    }
    if (max < columnHeaders.size())
    {
        max = columnHeaders.size();
    }
    return max;
}
string Table::getCell(int row, int column)
{
    return table[row][column];
}
vector<string> Table::getRow(int row)
{
    return table[row];
}
vector<string> Table::getColumn(int column)
{
    vector<string> columnVector;
    for (int i = 0; i < table.size(); i++)
    {
        columnVector.push_back(table[i][column]);
    }
    return columnVector;
}
string Table::getRowHeader(int row)
{
    return rowHeaders[row];
}
string Table::getColumnHeader(int column)
{
    return columnHeaders[column];
}

int Table::getColumnWidth(int column)
{
    int max = 0;
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][column].length() > max)
        {
            max = table[i][column].length();
        }
    }
    if (max < columnHeaders[column].length())
    {
        max = columnHeaders[column].length();
    }
    return max;
}

string Table::printTable(string delimiter)
{
    string res = "";
    int numColumns = getNumColumns();
    int numRows = getNumRows();
    int columnWidths[numColumns];
    for (int i = 0; i < numColumns; i++)
    {
        columnWidths[i] = getColumnWidth(i);
    }
    int rowHeadersWidth = 0;
    for (int i = 0; i < rowHeaders.size(); i++)
    {
        if (rowHeaders[i].length() > rowHeadersWidth)
        {
            rowHeadersWidth = rowHeaders[i].length();
        }
    }
    // print corner
    res += string(rowHeadersWidth, ' ');

    // print column headers
    for (int i = 0; i < numColumns; i++)
    {
        double halfPadding = (columnWidths[i] - columnHeaders[i].length()) / 2.0;

        res += string(ceil(halfPadding), ' ');
        res += columnHeaders[i];
        res += string(floor(halfPadding), ' ');

        res += delimiter;
    }
    res += "\n";

    // print rows
    for (int i = 0; i < numRows; i++)
    {
        // print row header
        if (i < rowHeaders.size())
        {
            res += rowHeaders[i];
            res += string(rowHeadersWidth - rowHeaders[i].length(), ' ');
            res += delimiter;
        }
        // print row
        for (int j = 0; j < numColumns; j++)
        {
            double halfPadding = (columnWidths[j] - table[i][j].length()) / 2.0;

            res += string(ceil(halfPadding), ' ');
            res += table[i][j];
            res += string(floor(halfPadding), ' ');

            res += delimiter;
        }
        res += "\n";
    }
    return res;
}
