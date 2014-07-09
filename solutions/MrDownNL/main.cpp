#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

  #include <windows.h>

  inline void Wait( unsigned long ms )
    {
    Sleep( ms );
    }
void ClearScreen()
      {
          HANDLE                     hStdOut;
          CONSOLE_SCREEN_BUFFER_INFO csbi;
          DWORD                      count;
          DWORD                      cellCount;
          COORD                      homeCoords = { 0, 0 };

          hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
          if (hStdOut == INVALID_HANDLE_VALUE) return;

          /* Get the number of cells in the current buffer */
          if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
          cellCount = csbi.dwSize.X *csbi.dwSize.Y;

          /* Fill the entire buffer with spaces */
          if (!FillConsoleOutputCharacter(
                      hStdOut,
                      (TCHAR) ' ',
                      cellCount,
                      homeCoords,
                      &count
                      )) return;

          /* Fill the entire buffer with the current colors and attributes */
          if (!FillConsoleOutputAttribute(
                      hStdOut,
                      csbi.wAttributes,
                      cellCount,
                      homeCoords,
                      &count
                      )) return;

          /* Move the cursor home */
          SetConsoleCursorPosition( hStdOut, homeCoords );
                                    }
#else  /* presume POSIX */

    #include <unistd.h>

    inline void Wait( unsigned long ms )
    {
        usleep( ms * 1000 );
    }
    
    #include <stdlib.h>
    void ClearScreen()
    {
        system("clear");
    }   
#endif

using namespace std;

typedef std::vector<char> rowsVec;
typedef std::vector<rowsVec> Grid;
//Grid grid(gridSizeX, IntVec(gridSizeY));

Grid readFile (const char* filename)
{
    Grid g;
    rowsVec row;
    char c;
    fstream infile(filename, fstream::in);
    while (infile >> noskipws >> c)
    {
        switch (c)
        {
            case '\n'   : g.push_back(row); row.clear();    break;
            case ' '    : row.push_back(' ');               break;
            case 'X'    : row.push_back('X');               break;
            default     : cout << "file not good";exit(-1);
        }
    }
    g.pop_back();
    infile.close();
    cout << "height: " << g.size() << endl;
    cout << "width: " << g[0].size() << endl;
    return g;
}
void Print (Grid g)
{
    ClearScreen();
    for (int i = 0; i < g.size(); i++)
    {
        cout << "|";
        for (int j = 0; j < g[i].size(); j++)
        {
            cout << g[i][j];
        }
        cout << "|" << endl;
    }
}

void Iterate(Grid &g)
{
    Grid temp = g;
    for (int i = 0; i < g.size(); ++i)
    {
        for (int j = 0; j < g[i].size(); ++j)
        {
            int liveneigbours = 0;
            int k, kmax, l, lmax;

            if (i == 0) k = i;
            else k = i - 1;
            if (i == g.size() - 1) kmax = g.size() - 1;
            else kmax = i + 1;

            for (; k <= kmax; k++)
            {
                if (j == 0) l = j;
                else l = j - 1;
                if (j == g[i].size() - 1) lmax = g[i].size() - 1;
                else lmax = j + 1;

                for (; l <= lmax; l++)
                {
                    if (g[k][l] == 'X' && !(i == k && j == l))
                    {
                        liveneigbours++;
                    }
                }
            }

            if (g[i][j] == ' ')
            {
                if (liveneigbours == 3)
                {
                    temp[i][j] = 'X';
                }
            }
            else if (g[i][j] == 'X')
            {
                if (liveneigbours < 2 || liveneigbours > 3)
                {
                    temp[i][j] = ' ';
                }
            }
            liveneigbours = 0;
        }
    }
    g = temp;
    return;
}

int main(int argc, char *argv[])
{
    Grid g;
    if (argc == 2)
    {
        g = readFile (argv[1]);
    }
    else
    {
        cout << "Please get me started with a file:" << endl;
        string filename;
        cin >> filename;
        cin.ignore();
        g = readFile (filename.c_str());
    }
    cout << "Read file and did not crash! Yay!" << endl;
    cout << "Does this look right?" << endl;
    Print (g);
    cout << "I will assume it is right, and totally ignore your anwser!";
    cout << "Please input the speed of the iterations now (in ms delay): " << endl;
    int delay = 0;
    cin >> delay;
    cout << "DISCLAIMER: If you have put in a really large number, you are going to be sitting there for a while!" << endl;
    cout << "please input the number of wanted iterations" << endl;
    int iterations = 1;
    cin >> iterations;
    for (int i = 0; i < iterations; i++)
    {
        Wait(delay);
        Iterate(g);
        Print(g);
    }
    cout << "Bye";
    return 0;
}

