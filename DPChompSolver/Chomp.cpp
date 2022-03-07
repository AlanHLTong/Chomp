#include "Chomp.h"

Chomp::Chomp(int n) : n(n){
    create();
}
bool Chomp::isValid(int a, int b, int c, int d, int e) {
    array<int, M + 1> rows = { N, a, b, c, d, e };
    for (int i = 1; i <= M; i++) {
        if (rows[i] > rows[i - 1])
            return false;
    }
    return true;
}

bool Chomp::setTrue(int a, int b, int c, int d, int e) {
    if (!isValid(a, b, c, d, e))
        return false;
    WIN[a][b][c][d][e] = True;
    return true;
}

bool Chomp::setFalse(int a, int b, int c, int d, int e) {
    if (!isValid(a, b, c, d, e))
        return false;
    WIN[a][b][c][d][e] = False;
    return true;
}

bool Chomp::report(int a, int b, int c, int d, int e) {
    if (!isValid(a, b, c, d, e)) {
        cerr << "ERROR: Reporting invalid position!!" << endl;
        exit(1);
    }
    if (WIN[a][b][c][d][e] == True)
        return true;
    else
        return false;
}


bool Chomp::validmove(int a, int b, int c, int d, int e,
    int f, int g, int h, int i, int j)
{
    int adiff = a - f;
    int bdiff = b - g;
    int cdiff = c - h;
    int ddiff = d - i;
    int ediff = e - j;
    if (f == a && g == b && h == c && i == d && j == e) //ignore self case;
    {
        return false;
    }
    else if (f == 1 && g == 0 && h == 0 && i == 0 && j == 0) //check if position can reach {1,0,0,0,0} in 1 move legally
    {

        if (a > 0 && b == 0 && c == 0 && d == 0 && e == 0)
        {
            return true;
        }
        else if (a > 1 || b > 1 || c > 1 || d > 1 || e > 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else //all other cases to check if it is a valid move
    {
        if (ediff > 0)
        {
            if ((adiff || bdiff || cdiff || ddiff) == 0)
            {
                return true;
            }
            else if ((adiff || bdiff || cdiff) == 0)
            {
                if (j == i)
                    return true;
            }
            else if ((adiff || bdiff) == 0)
            {
                if (h == i && i == j)
                    return true;
            }
            else if ((adiff) == 0)
            {
                if (g == h && h == i && i == j)
                    return true;
            }
            else
            {
                if (f == g && g == h && h == i && i == j)
                    return true;
            }
        }
        else if (ddiff > 0)
        {
            if ((adiff || bdiff || cdiff) == 0)
            {
                if (i < h)
                    return true;
            }
            else if ((adiff || bdiff) == 0)
            {
                if (h == i)
                    return true;
            }
            else if ((adiff) == 0)
            {
                if (g == h && h == i)
                    return true;
            }
            else
            {
                if (f == g && g == h && h == i)
                    return true;
            }
        }
        else if (cdiff > 0)
        {
            if ((adiff || bdiff) == 0)
            {
                if (h < g)
                    return true;
            }
            else if ((adiff) == 0)
            {
                if (h == g)
                    return true;
            }
            else
            {
                if (h == g && g == f)
                    return true;
            }
        }
        else if (bdiff > 0)
        {
            if ((adiff) == 0)
            {
                if (g < f)
                    return true;
            }
            else
            {
                if (g == f)
                    return true;
            }
        }
        else if (adiff > 0)
        {
            if (f >= g)
            {
                return true;
            }
        }
        return false;
    }
}

void Chomp::create()
{
    setFalse(1, 0, 0, 0, 0);
    //abcde loop to loop through all legal positions to fill truth table
    for (int a = 1; a <= n; a++)
    {
        for (int b = 0; b <= a; b++)
        {
            for (int c = 0; c <= b; c++)
            {
                for (int d = 0; d <= c; d++)
                {
                    for (int e = 0; e <= d; e++)
                    {

                        bool win = false;

                        //fghij loop to loop thought all legal positions BEFORE current position x
                        for (int f = 1; f <= a; f++)
                        {
                            for (int g = 0; g <= b && g <= f; g++)
                            {
                                for (int h = 0; h <= c && h <= g; h++)
                                {
                                    for (int i = 0; i <= d && i <= h; i++)
                                    {
                                        for (int j = 0; j <= e && j <= i; j++)
                                        {
                                            //checks if {f,g,h,i,j} is part of Next(x) where x = {a,b,c,d,e}
                                            //if it is not part of Next(x) then continue
                                            if (!validmove(a, b, c, d, e, f, g, h, i, j))
                                            {
                                                continue;
                                            }
                                            //all elements that will be checked are part of Next(x)
                                            //check all of them to see if ANY are Losing (False)
                                            //if any of them are false then we can conclude 
                                            //instantly (breaking all loops) that current position 
                                            //is Winning(True)
                                            //else if there are no Losing (False) elements, meaning all of
                                            //Next(x) is Winning(true) then we can conclude that the
                                            //the current position X is losing
                                            if (report(f, g, h, i, j) == false)
                                            {
                                                win = true;
                                                break;
                                            }
                                        }
                                        //if there is a single Losing(False) position just break all loops
                                        if (win)
                                            break;
                                    }
                                    if (win)
                                        break;
                                }
                                if (win)
                                    break;
                            }
                            if (win)
                                break;
                        }
                        //if else loop to set x to True of False depending if the position is winning ot losing
                        if (win)
                            setTrue(a, b, c, d, e);
                        else
                            setFalse(a, b, c, d, e);
                    }
                }
            }
        }
    }
}

void Chomp::print() {
    for (int a = 1; a <= n; a++)
    {
        for (int b = 0; b <= a; b++)
        {
            for (int c = 0; c <= b; c++)
            {
                for (int d = 0; d <= c; d++)
                {
                    for (int e = 0; e <= d; e++)
                    {
                        cout << "[" << a << "," << b << "," << c << "," << d << "," << e << "] is ";
                        if (report(a, b, c, d, e))
                            cout << "Win";
                        else
                            cout << "Loss";

                        cout << endl;
                    }
                }
            }
        }
    }
}
