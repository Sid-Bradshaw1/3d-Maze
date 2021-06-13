#ifndef INC_3DMAZE_MAZE_H
#define INC_3DMAZE_MAZE_H
#include <string>
#include "mazeinterface.h"
#define LEFT r,c-1,l
#define RIGHT r,c+1,l
#define UP r-1,c,l
#define DOWN r+1,c,l
#define OUT r,c,l-1
#define IN r,c,l+1

using namespace std;

enum cells {OPEN, BLOCKED, VISITED, PATH, EXIT};
class Maze : public MazeInterface
{
public:
    Maze(int h, int w, int l)
    {
        height = h;
        layers = l;
        width = w;
        ;
        mazeVal = new int**[height];
        for (int i = 0; i < height; ++i)
        {
            mazeVal[i] = new int*[width];
            for (int j = 0; j < width; ++j)
                mazeVal[i][j] = new int[layers];
        }
    }

    ~Maze(void)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
                delete[] mazeVal[i][j];
            delete[] mazeVal[i];
        }
        delete[] mazeVal;
    }




    int height; //row
    int width; //col
    int layers;
    int*** mazeVal;
    //int mazeSolv[][][];

    void setValue(int height, int width, int layer, int value)
    {
        mazeVal[height][width][layer] = value;
    }

   /* void setMazeSolv(int maze)
    {
        mazeSolv[length][width][height];
    }*/

    /** Solve maze
       @return true if solveable, else false
    */
    bool find_maze_path()
    {
        if (recFinder(0, 0, 0))
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    bool recFinder(size_t r = 0, size_t c = 0, size_t l = 0)
    {
        //prevents segfault
        if (((r < 0) || (r >= height)) || ((c < 0) || (c >= width)) ||
                ((l < 0) || (l >= layers)))
        {
            return false;
        }

        if (mazeVal[r][c][l] != OPEN)
        {
            return false;
        }

        mazeVal[r][c][l] = PATH;

        //if it finds the exit it returns true
        if ((r == height - 1) && (c == width - 1) && (l == layers - 1))
        {
            mazeVal[r][c][l] = EXIT;
            mazeVal[r][c][l] = 10;
            return true;
        }


       if (recFinder(LEFT))
        {
            mazeVal[r][c][l] = 3;
            return true;
        }

        else if (recFinder(RIGHT))
        {
            mazeVal[r][c][l] = 4;
            return true;
        }

        else if (recFinder(UP))
        {
            mazeVal[r][c][l] = 5;
            return true;
        }
        else if (recFinder(DOWN))
        {
            mazeVal[r][c][l] = 6;
            return true;
        }
        else if (recFinder(OUT))
        {
            mazeVal[r][c][l] = 7;
            return true;
        }
        else if (recFinder(IN))
        {
            mazeVal[r][c][l] = 8;
            return true;
        }
        else
       {
            mazeVal[r][c][l] = VISITED;
            mazeVal[r][c][l] = 2;
            return false;
       }

    }

    /** Output maze (same order as input maze)
      @return string of 2D layers
    */
     std::string toString() const
    {
         int layerCount = 0;
         ostringstream out;
         for (int i = 0; i < layers; ++i)
         {
             layerCount++;
             out << "Layer " << layerCount << endl;
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < width; ++k)
                {
                    out << " ";
                    if (mazeVal[j][k][i] == 0)
                    {
                        out << "_";
                    }

                    else if (mazeVal[j][k][i] == 3)
                    {
                        out << "L";
                    }
                    else if (mazeVal[j][k][i] == 4)
                    {
                        out << "R";

                    }
                    else if (mazeVal[j][k][i] == 5)
                    {
                        out << "U";

                    }
                    else if (mazeVal[j][k][i] == 6)
                    {
                        out << "D";

                    }
                    else if (mazeVal[j][k][i] == 7)
                    {
                        out << "O";

                    }
                    else if (mazeVal[j][k][i] == 8)
                    {
                        out << "I";

                    }
                    else if (mazeVal[j][k][i] == 9)
                    {
                        out << "E";

                    }
                    else if (mazeVal[j][k][i] == 2)
                    {
                        out << "*";
                    }
                    else if (mazeVal[j][k][i] == 10)
                    {
                        out << "E";
                    }
                    else
                    {
                        out << "X";
                    }

                }
                out << endl;
            }
         }
         out << endl;

         return out.str();
    }

    friend ostream& operator<< (std::ostream& os, Maze& maze){
        os << maze.toString();
        return os;
    }




};

#endif //INC_3DMAZE_MAZE_H
