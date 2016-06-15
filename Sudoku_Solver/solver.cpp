#include <iostream>
#include <vector>
#include <math.h>

using namespace std ;

// declaration of types
typedef vector< vector<int> > Matrix ; // 2 dimensions Matrix containing the sudoku
typedef vector< vector< vector<bool> > > Matrix_possibilities ;  // 3 dimensions Matrix of boolean giving the possible digits that can be written in each cell

// declaration of functions
void print(Matrix);
bool test(Matrix);
bool backTracking(Matrix &, Matrix_possibilities &, int);
int getIndex(vector<bool>, int);
void updatePossibilities(Matrix, Matrix_possibilities &);

int main()
{
    // Matrix containing the sudoku
    vector<int> line(9,0);
    Matrix sudoku(9,line);

    // Matrix containing the possibilities of digits for each cell
    vector<bool> p(9,true);
    vector< vector<bool> > line_possibilities(9,p);
    Matrix_possibilities possibility(9,line_possibilities);

    // The sudoku to resolve is hard-coded here
    sudoku[0][3]=6;
    sudoku[0][4]=7;
    sudoku[1][3]=4;
    sudoku[1][5]=9;
    sudoku[1][7]=2;
    sudoku[1][8]=8;
    sudoku[2][1]=2;
    sudoku[2][6]=3;
    sudoku[3][6]=5;
    sudoku[3][8]=6;
    sudoku[4][2]=5;
    sudoku[4][3]=7;
    sudoku[4][5]=4;
    sudoku[4][6]=9;
    sudoku[5][0]=9;
    sudoku[5][2]=1;
    sudoku[6][2]=2;
    sudoku[6][7]=8;
    sudoku[7][0]=8;
    sudoku[7][1]=5;
    sudoku[7][3]=9;
    sudoku[7][5]=6;
    sudoku[7][8]=1;
    sudoku[8][4]=4;
    sudoku[8][5]=5;

    // Update the possibilities for each cells in function of the cells that are already filled
    updatePossibilities(sudoku,possibility);

    // print the sudoku before solving
    print(sudoku);

    // try to solve the sudoku
    if (backTracking(sudoku, possibility, 0)) // if the sudoku has been solved
    {
        print(sudoku);  // print the solved sudoku
        cout << endl << "solved" <<endl;
    }
    else // if the sudoku has not been solved (the initial state didn't contain enough information)
    {
        print(sudoku);  // print the partially solved sudoku
        cout << endl << "failed to solve completely" << endl;
    }

    return 0 ;
}

// backtracking algorithm (make hypothesis and go back if it leads to a mistake)
// make an hypothesis on the cell at the position 'pos', test the sudoku, if wrong goes back, if true make an hypothesis on the position 'pos+1'
bool backTracking(Matrix & sudoku, Matrix_possibilities & possibility, int pos)
{
    int f;
    int buff;
    int k_th;
    if (pos==81) {return true;}
    else
    {
        int i=floor(pos/9);
        int j=pos-9*floor(pos/9);
        buff=0;
        for (int n=0;n<9;n++)
        {
            if(possibility[i][j][n])buff++;
        }
        if(buff>0)
        {
            for (int k=0 ; k<buff; k++)
            {
                if (test(sudoku)) // if the sudoku is correct, make a new hypothesis
                {
                    Matrix_possibilities mbuff = possibility; // duplicate the matrix to be able to go back (backtracking) if mistake
                    k_th=getIndex(possibility[i][j], k);
                    sudoku[i][j] = k_th+1;
                    for (int p=0;p<9;p++)
                    {
                        possibility[p][j][k_th]=false;
                    }
                    for (int q=0;q<9;q++)
                    {
                        possibility[i][q][k_th]=false;
                    }
                    for (int p=3*floor(i/3);p<3*floor(i/3)+3;p++)
                    {
                        for (int q=3*floor(j/3);q<3*floor(j/3)+3;q++)
                        {
                            possibility[p][q][k_th]=false;
                        }
                    }

                    for (int r=0;r<9;r++)
                    {
                        possibility[i][j][r]=false;
                    }
                    if (backTracking(sudoku, possibility, pos+1)) {return true;}

                    // if the hypothesis was wrong:
                    sudoku[i][j] = 0;
                    possibility = mbuff; // go back to the previous state
                    mbuff.clear();
                }
            }
        }
        else
        {
            if (sudoku[i][j]==0){return false;}
            if (backTracking(sudoku, possibility, pos+1)) {return true;}
        }
        return false;
    }
}

// Function to check if the sudoku respects the rules
bool test(Matrix sudoku)
{
    int digit;
    vector<bool> t;
    for (int index=0;index<10;index++)t.push_back(false);

    // test by line
    for (int i=0;i<9;i++)
    {
        for (int j=0;j<9;j++)
        {
            digit=sudoku[i][j];
            if(digit!=0)
            {
                if(t[digit]==false)t[digit]=true;   // the digit has not been used in this line yet
                else return false;  // the digit was already in use in this line -> error
            }
        }
        for (int index=0;index<10;index++)t[index]=false;
    }

    // test by column
    for (int j=0;j<9;j++)
    {
        for (int i=0;i<9;i++)
        {
            digit=sudoku[i][j];
            if(digit!=0)
            {
                if(t[digit]==false)t[digit]=true;   // the digit has not been used in this column yet
                else return false;  // the digit was already in use in this column -> error
            }
        }
        for (int index=0;index<10;index++)t[index]=false;
    }

    // test by 3*3 block
    for (int k=0;k<9;k++)
    {
        for (int i=3*floor(k/3);i<3*floor(k/3)+3;i++)
        {
            for (int j=3*(k-3*floor(k/3));j<3*(k-3*floor(k/3))+3;j++)
            {
                digit=sudoku[i][j];
                if(digit!=0)
                {
                    if(t[digit]==false)t[digit]=true;   // the digit has not been used in this block yet
                    else return false;  // the digit was already in use in this block -> error
                }
            }
        }
        for (int index=0;index<10;index++)t[index]=false;
    }
    return true;
}

// print the sudoku in the console
void print(Matrix Mat)
{
        for (int i=0 ; i<9 ; i++)
        {
            for (int j=0 ; j<9 ; j++)
            {
                if (j==2 || j==5)
                {
                    if (Mat[i][j]!=0)cout << Mat[i][j] << " || " ;
                    else cout << " " << " || " ;
                }
                else
                {
                    if (Mat[i][j]!=0)cout << Mat[i][j] << " | " ;
                    else cout << " " << " | " ;
                }
            }
            if (i==2 ||i==5)cout << endl << "-   -   -    -   -   -    -   -   -";
            cout << endl << "-   -   -    -   -   -    -   -   -"<<endl;
        }
        cout<<endl;
}

// get the index of the k_th 'true' in a vector
int getIndex(vector<bool> vect, int k)
{
    int index=-1;
    int n=vect.size();
    for(int i=0;i<n;i++)
    {
        if(vect[i])index++;
        if(index==k)return i;
    }
    return -1;
}

// Update the lists of digits that can be written 
void updatePossibilities(Matrix sudoku, Matrix_possibilities & possibility)
{
    int digit;
    for (int i=0;i<9;i++)
    {
        for (int j=0;j<9;j++)
        {
            digit=sudoku[i][j];
            if (digit!=0)
            {
                for (int r=0;r<9;r++)possibility[i][j][r]=false;   // a cell that is filled has no more possibilities

                for (int p=0;p<9;p++)possibility[p][j][digit-1]=false;   // the digit of a cell become impossible in the same line
                for (int q=0;q<9;q++)possibility[i][q][digit-1]=false;   // the digit of a cell become impossible in the same column
                for (int p=3*floor(i/3);p<3*floor(i/3)+3;p++)
                {
                    for (int q=3*floor(j/3);q<3*floor(j/3)+3;q++)possibility[p][q][digit-1]=false;   // the digit of a cell become impossible in the same block
                }
            }
        }
    }
}
