#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include "maze.h"

using namespace std;

int main(int argc, char* argv[])
{
    string line;
    string lineContents;
    int mHeight;
    int mWidth;
    int mLayers;
    int value;
    int i = 0;
    int j = 0;
    int k = 0;



    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;

    ifstream in(argv[1]);

    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;

    ofstream out(argv[2]);

    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    in >> mHeight;
    in >> mWidth;
    in >> mLayers;
    Maze MyMaze(mHeight, mWidth, mLayers);
    //int populateArr[item1][item2][item3];

    for (i = 0; i < mLayers; ++i)
    {
        for (j = 0; j < mHeight; ++j)
        {
            for (k = 0; k < mWidth; ++k)
            {
                in >> value;
                MyMaze.setValue(j, k, i, value);
            }
        }
    }


    out << "Solve Maze:" << endl;
    out << MyMaze;

    if (!MyMaze.find_maze_path())
    {
        out << "No Solution Exists!";
    }

    else
    {
        out << "Solution:" << endl;
        MyMaze.find_maze_path();
        out << MyMaze;
    }






return 0;
}
