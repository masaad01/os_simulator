using namespace std;

class Table
{
    vector<vector<string>> table;
    vector<string> columnHeaders;
    vector<string> rowHeaders;

public:
    Table();
    void addColumnHeader(string header, int index = -1);
    void addRowHeader(string header, int index = -1);
    void addRow(vector<string> row, int index = -1);
    void addCell(string cell, int row, int column);
    int getNumRows();
    int getNumColumns();
    string getCell(int row, int column);
    vector<string> getRow(int row);
    vector<string> getColumn(int column);
    string getRowHeader(int row);
    string getColumnHeader(int column);
    int getColumnWidth(int column);
    string printTable(string delimiter = " ");
};
