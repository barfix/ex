/******************************************
* Bar Atuar
* 208648469
* 83-120-04
* Ex 1
******************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 30
#define MIN_SIZE 5

enum Phase // states for a state machine that determines the current game phase
{
    Set_Player_Phase,
    Playing_Phase,
    Cops_Winning_Phase,
    Robber_winning_Phase,
    White_Winning_Phase,
    Black_Winning_Phase,
    Tie_phase
};

enum Turn // states for a state machine that determines whose turn it is in the current game
{
    Cops_Turn,
    Robbers_Turn,
    Whites_Turn,
    Blacks_Turn
};

void ourApp();
void printNames(bool isPlay);
int getNumOfRows();
int getNumOfColumns(int numOfRows);

void copsAndRobbers(int numOfRows, int numOfColumns);
void initializeLocation(int copsLocation[5][2], int numOfCops);
void initializeGameTable(char gameTable[MAX_SIZE][MAX_SIZE], int numOfRows, int numOfColumns);
bool checkGameCell(char gameTable[MAX_SIZE][MAX_SIZE], int chosenRow, int chosenColumn);
void printGameTable(char gameTable[MAX_SIZE][MAX_SIZE], int numOfRows, int numOfColumns);
void printMoves(char gameTable[MAX_SIZE][MAX_SIZE], int copsLocation[5][2], int numOfRows, int numOfColumns, int numOfCops);
int getMoves();
void goFurthestAway(char gameTable[MAX_SIZE][MAX_SIZE], int copsLocation[5][2], int robbersLocation[2], int numOfRows, int numOfColumns, int numOfCops);

void theFourHorseMen();
void movePieces(char gameTable[MAX_SIZE][MAX_SIZE], int piecesLocation[2][2], int moveTo[4]);
bool isWon(char gameTable[MAX_SIZE][MAX_SIZE], int piecesLocation[2][2]);

const char Gcop_Icon = 'C', Grobber_Icon = 'R', Gempty_Cell_Icon = '-';

int main()
{
    ourApp();
    return 0;
}

/**
 * Manages the app
 */
void ourApp()
{
    char answer = 'y';
    int numOfRows, numOfColumns;
    printNames(true);
    printf("Let's choose the size:\n");
    numOfRows = getNumOfRows();
    numOfColumns = getNumOfColumns(numOfRows);
    do
    {
        printf("Do you want to play [y/n]?\n");
        scanf(" %c", &answer); //can get y or n
        if (answer == 'y')
        {
            copsAndRobbers(numOfRows, numOfColumns);
            theFourHorseMen();
        }
    } while (answer == 'y');
    printNames(false);
}

/**
 * Gets the players first and last name
 * @param isPlay determines if to get the players name or to part and say goodbye
 */
void printNames(bool isPlay)
{
    static char firstName[10] = "Place", lastName[10] = "Holder";

    if (isPlay)
    {
        fgets(firstName, 10, stdin);             //max string of 10 characters
        fgets(lastName, 10, stdin);              //max string of 10 characters
        firstName[strcspn(firstName, "\n")] = 0; //gets rid of the new line in firstName
        lastName[strcspn(lastName, "\n")] = 0;   // gets rid of the new line in lastName
        printf("Hello %s %s, welcome to our app!\n", firstName, lastName);
    }
    else
        printf("Bye, %s %s.\n", firstName, lastName);
}

/**
 * Gets from the player the number of rows for the game table
 * @param numOfRows the number of rows for the game table, between MIN_SIZE and MAX_SIZE
 */
int getNumOfRows()
{
    int numOfRows;

    scanf("%d", &numOfRows);
    if (numOfRows > MAX_SIZE)
        numOfRows = MAX_SIZE;
    else if (numOfRows < MIN_SIZE)
        numOfRows = MIN_SIZE;

    return numOfRows;
}

/**
 * Gets from the player the number of columns for the game table
 * @param numOfRows the number of rows for the game table, between MIN_SIZE and MAX_SIZE
 * @param numOfColumns the number of columns for the game table, between MIN_SIZE and MAX_SIZE
 */
int getNumOfColumns(int numOfRows)
{
    int numOfColumns;

    scanf("%d", &numOfColumns);
    if (numOfColumns == -1)
        numOfColumns = numOfRows;
    else if (numOfColumns > MAX_SIZE)
        numOfColumns = MAX_SIZE;
    else if (numOfColumns < MIN_SIZE)
        numOfColumns = MIN_SIZE;

    return numOfColumns;
}

/**
 * Manages the cops and robbers game and it's progress
 * @param numOfRows the number of rows for the game table
 * @param numOfColumns the number of columns for the game table
 */
void copsAndRobbers(int numOfRows, int numOfColumns)
{
    const int Max_Num_Of_Turns = 30;
    const int Robbers_Initial_Location[2] = {(int)(numOfRows - 1) / 2, (int)(numOfColumns - 1) / 2};
    int robbersLocation[2], copsLocation[5][2];
    char gameTable[MAX_SIZE][MAX_SIZE] = {Gempty_Cell_Icon};
    int check;
    int numOfCops, currentCop, chosenRow, chosenColumn, turnNum = 0, i, rowAndColumnSum;
    int copsMove[4]; //consists of {current row, current column, next row, next column}
    bool isOccupied = true, isPlaying = true;
    enum Phase gamePhase = Set_Player_Phase;
    enum Turn playerTurn = Cops_Turn;

    while (isPlaying)
    {
        switch (gamePhase) //a state machine for that manages each game phase
        {
        case Set_Player_Phase: //the state where the player gets to choose the number of cops and put them on the table
            initializeLocation(copsLocation, numOfCops);
            initializeGameTable(gameTable, numOfRows, numOfColumns);
            gameTable[Robbers_Initial_Location[0]][Robbers_Initial_Location[1]] = Grobber_Icon;
            robbersLocation[0] = Robbers_Initial_Location[0];
            robbersLocation[1] = Robbers_Initial_Location[1];

            printf("How many cops (1-5)?\n");
            scanf("%d", &numOfCops); //gets a number between 1 to 5

            for (currentCop = 0; currentCop < numOfCops; currentCop++)
            {

                printf("Let's choose a cell:\n");
                while (isOccupied)
                {
                    scanf("%d%d", &chosenRow, &chosenColumn);
                    isOccupied = checkGameCell(gameTable, chosenRow, chosenColumn);
                }
                copsLocation[currentCop][0] = chosenRow;
                copsLocation[currentCop][1] = chosenColumn;
                gameTable[chosenRow][chosenColumn] = Gcop_Icon;
                isOccupied = !isOccupied;
            }
            printf("Well, Let's play!\nInitial states:\n");
            printGameTable(gameTable, numOfRows, numOfColumns);
            if (numOfCops == 1)
            {
                rowAndColumnSum = copsLocation[0][0] + copsLocation[0][1] + robbersLocation[0] + robbersLocation[1]; //func???
                if (rowAndColumnSum % 2 == 0)
                    gamePhase = Robber_winning_Phase;
            }
            else
                gamePhase = Playing_Phase;
            break;

        case Playing_Phase:     //the sate where the player decides where to move the cops to in each turn
            switch (playerTurn) //a state machine that manages each players turn, cops' or robber's
            {
            case Cops_Turn:

                printf("Cops:\n");
                printMoves(gameTable, copsLocation, numOfRows, numOfColumns, numOfCops);
                for (i = 0; i < 4; i++)
                {
                    copsMove[i] = getMoves();
                }
                if (gameTable[copsMove[2]][copsMove[3]] == Grobber_Icon)
                    gamePhase = Cops_Winning_Phase;

                gameTable[copsMove[2]][copsMove[3]] = gameTable[copsMove[0]][copsMove[1]];
                gameTable[copsMove[0]][copsMove[1]] = Gempty_Cell_Icon;
                for (currentCop = 0; currentCop < numOfCops; currentCop++)
                {
                    if (copsLocation[currentCop][0] == copsMove[0] && copsLocation[currentCop][1] == copsMove[1])
                    {
                        copsLocation[currentCop][0] = copsMove[2];
                        copsLocation[currentCop][1] = copsMove[3];
                    }
                }
                printGameTable(gameTable, numOfRows, numOfColumns);
                turnNum++;
                playerTurn = Robbers_Turn;
                break;

            case Robbers_Turn:

                printf("Rob:\n");
                goFurthestAway(gameTable, copsLocation, robbersLocation, numOfRows, numOfColumns, numOfCops);
                printGameTable(gameTable, numOfRows, numOfColumns);
                turnNum++;
                playerTurn = Cops_Turn;
                break;
            }
            break;

        case Cops_Winning_Phase: //the state where the player won
            printf("The cops won!\n");
            isPlaying = !isPlaying;
            break;

        case Robber_winning_Phase: // the sate where the player lost and the robber won
            printf("The rob managed to escape!\n");
            isPlaying = !isPlaying;
            break;
        }

        if (turnNum == Max_Num_Of_Turns)
            gamePhase = Robber_winning_Phase;
    }
}

/**
 * Initializes all of the cops to an uninitialized state
 * @param copsLocation all of the current cops' location
 */
void initializeLocation(int copsLocation[5][2], int numOfCops)
{
    const int Uninitialized = -1;
    int currentCop, i;
    for (currentCop = 0; currentCop < numOfCops; currentCop++)
    {
        for (i = 0; i < 2; i++)
            copsLocation[currentCop][i] = Uninitialized;
    }
}

/**
 * Initializes the game table
 * @param gameTable the game's table
 * @param numOfRows the number of rows for the game table
 * @param numOfColumns the number of columns for the game table
 */
void initializeGameTable(char gameTable[MAX_SIZE][MAX_SIZE], int numOfRows, int numOfColumns)
{
    int row, column;
    for (row = 0; row < numOfRows; row++)
    {
        for (column = 0; column < numOfColumns; column++)
        {
            gameTable[row][column] = Gempty_Cell_Icon;
        }
    }
}

/**
 * Checks if the chosen location is already occupied by either a robber or the cops, return true if occupied and false if not
 * @param gameTable the games table
 * @param chosenRow the player chosen row for the cop
 * @param chosenColumn the player chosen column for the cop
 * @param isOccupied raises a flag if the chosen cell for the cop is already occupied
 */
bool checkGameCell(char gameTable[MAX_SIZE][MAX_SIZE], int chosenRow, int chosenColumn)
{
    bool isOccupied = true;

    isOccupied = gameTable[chosenRow][chosenColumn] == Gempty_Cell_Icon ? !isOccupied : isOccupied;
    return isOccupied;
}

/**
 * Prints the game table
 * @param gameTable contains the game's table and the players position
 * @param numOfRows the number of rows for the game table
 * @param numOfcolumns the number of columns for the game table
 */
void printGameTable(char gameTable[MAX_SIZE][MAX_SIZE], int numOfRows, int numOfColumns)
{
    int row, column;

    for (row = 0; row < numOfRows; row++)
    {
        for (column = 0; column < numOfColumns; column++)
        {
            printf("%c", gameTable[row][column]);
            if (column == numOfColumns - 1)
                printf("\n");
        }
    }
}

/**
 * Prints all of the available moves of the cops
 * @param gameTable the table of the game
 * @param numOfRows the number of rows of the game table
 * @param numOfColumns the number of columns of the game table
 * @param numOfCops the number of cops in the game
 */
void printMoves(char gameTable[MAX_SIZE][MAX_SIZE], int copsLocation[5][2], int numOfRows, int numOfColumns, int numOfCops)
{
    int copsRow, copsColumn, currentCop = 0, up, down, left, right;

    for (currentCop = 0; currentCop < numOfCops; currentCop++)
    {
        copsRow = copsLocation[currentCop][0];
        copsColumn = copsLocation[currentCop][1];
        up = copsRow == 0 ? copsRow : copsRow - 1;                            //sets the up coordinates from the current cop, if the cop is at the top of the table the up coordinates will stay the say as the cops row coordinates
        down = copsRow == numOfRows - 1 ? copsRow : copsRow + 1;              //sets the down coordinates from the current cop, if the cop is at the bottom of the table the up coordinates will stay the say as the cops row coordinates
        left = copsColumn == 0 ? copsColumn : copsColumn - 1;                 //sets the left coordinates from the current cop, if the cop is at the most left column of the table the left coordinates will stay the say as the cops column coordinates
        right = copsColumn == numOfColumns - 1 ? copsColumn : copsColumn + 1; //sets the right coordinates from the current cop, if the cop is at the most right column of the table the up coordinates will stay the say as the cops column coordinates

        if (gameTable[down][copsColumn] != Gcop_Icon)
            printf("[%d,%d] -> [%d,%d]\n", copsRow, copsColumn, down, copsColumn);
        if (gameTable[up][copsColumn] != Gcop_Icon)
            printf("[%d,%d] -> [%d,%d]\n", copsRow, copsColumn, up, copsColumn);
        if (gameTable[copsRow][right] != Gcop_Icon)
            printf("[%d,%d] -> [%d,%d]\n", copsRow, copsColumn, copsRow, right);
        if (gameTable[copsRow][left] != Gcop_Icon)
            printf("[%d,%d] -> [%d,%d]\n", copsRow, copsColumn, copsRow, left);
    }
}

/**
 * Gets from the player the chosen cop current and new coordinates
 * @param chosenLocation the coordinate that the player chose
 */
int getMoves()
{
    int chosenLocation;

    scanf("%d", &chosenLocation);
    return chosenLocation;
}

/**
 * Calculates which cop is the closest robber and moves him the furthest away from said cop
 * @param gameTable the table of the game
 * @param copsLocation all the cops in the game and their current location
 * @param robbersLocation the robber's location
 * @param numOfRows the number of rows of the game table
 * @param numOfColumns the number of columns of the game table
 * @param numOfCops the number of cops in the game
 */
void goFurthestAway(char gameTable[MAX_SIZE][MAX_SIZE], int copsLocation[5][2], int robbersLocation[2], int numOfRows, int numOfColumns, int numOfCops)
{
    const int Uninitialized = -1;
    int currentCop, up, down, left, right;
    float distance = 0, distanceCheck;
    int closestCop = Uninitialized, robbersNewLocation[2];

    for (currentCop = 0; currentCop < numOfCops; currentCop++)
    {
        distanceCheck = (float)sqrt(pow((copsLocation[currentCop][0] - robbersLocation[0]), 2) + pow((copsLocation[currentCop][1] - robbersLocation[1]), 2));
        if (closestCop == Uninitialized || distanceCheck < distance)
        {
            closestCop = currentCop;
            distance = distanceCheck;
        }
        else if (distanceCheck == distance)
        {
            if (copsLocation[currentCop][0] < copsLocation[closestCop][0])
            {
                closestCop = currentCop;
                distance = distanceCheck;
            }
            else if (copsLocation[currentCop][0] == copsLocation[closestCop][0])
            {
                if (copsLocation[currentCop][1] < copsLocation[currentCop][1])
                {
                    closestCop = currentCop;
                    distance = distanceCheck;
                }
            }
        }
    }

    up = robbersLocation[0] == 0 ? robbersLocation[0] : robbersLocation[0] - 1;                   //sets the up coordinates from the robber, if the robber is at the top of the table the up coordinates will stay the say as the robber's row coordinates
    down = robbersLocation[0] == numOfRows - 1 ? robbersLocation[0] : robbersLocation[0] + 1;     //sets the down coordinates from the robber, if the robber is at the bottom of the table the up coordinates will stay the say as the robber's row coordinates
    left = robbersLocation[1] == 0 ? robbersLocation[1] : robbersLocation[1] - 1;                 //sets the left coordinates from the robber, if the robber is at the most left column of the table the left coordinates will stay the say as the robber's column coordinates
    right = robbersLocation[1] == numOfColumns - 1 ? robbersLocation[1] : robbersLocation[1] + 1; //sets the right coordinates from the robber, if the robber is at the most right column of the table the up coordinates will stay the say as the robber's column coordinates
    robbersNewLocation[0] = robbersLocation[0];
    robbersNewLocation[1] = robbersLocation[1];

    if (copsLocation[closestCop][0] < robbersLocation[0])
    {
        if (gameTable[down][robbersLocation[1]] == Gempty_Cell_Icon)
            robbersNewLocation[0] = down;
    }
    else if (copsLocation[closestCop][0] > robbersLocation[0])
    {
        if (gameTable[up][robbersLocation[1]] == Gempty_Cell_Icon)
            robbersNewLocation[0] = up;
    }
    else if (copsLocation[closestCop][1] < robbersLocation[1])
    {
        if (gameTable[robbersLocation[0]][right] == Gempty_Cell_Icon)
            robbersNewLocation[1] = right;
    }
    else
    {
        if (gameTable[robbersLocation[0]][left] == Gempty_Cell_Icon)
            robbersNewLocation[1] = left;
    }

    gameTable[robbersLocation[0]][robbersLocation[1]] = Gempty_Cell_Icon;
    gameTable[robbersNewLocation[0]][robbersNewLocation[1]] = Grobber_Icon;
    robbersLocation[0] = robbersNewLocation[0];
    robbersLocation[1] = robbersNewLocation[1];
}

/**
 * Manages the four horsemen game and it's progress
 */
void theFourHorseMen()
{
    const int Num_Of_Rows = 3, Num_Of_Columns = 3, Max_Num_Of_Turns = 30;
    const char White_Horse_Icon = 'W', Black_Horse_Icon = 'B';
    char gameTable[MAX_SIZE][MAX_SIZE];
    int whitesLocation[2][2] = {0, 0, 0, 2}, blacksLocation[2][2] = {2, 0, 2, 2};
    int playersMove[4], turnNum = 0, i;
    bool isPlaying = true;
    enum Phase gamePhase = Playing_Phase;
    enum Turn playerTurn = Whites_Turn;

    initializeGameTable(gameTable, Num_Of_Rows, Num_Of_Columns);
    gameTable[whitesLocation[0][0]][whitesLocation[0][1]] = White_Horse_Icon;
    gameTable[whitesLocation[1][0]][whitesLocation[1][1]] = White_Horse_Icon;
    gameTable[blacksLocation[0][0]][blacksLocation[0][1]] = Black_Horse_Icon;
    gameTable[blacksLocation[1][0]][blacksLocation[1][1]] = Black_Horse_Icon;
    printGameTable(gameTable, Num_Of_Rows, Num_Of_Columns);
    while (isPlaying)
    {
        switch (gamePhase)
        {
        case Playing_Phase:
            switch (playerTurn)
            {
            case Whites_Turn:
                printf("W:\n");
                for (i = 0; i < 4; i++)
                {
                    scanf("%d", &playersMove[i]);
                }
                movePieces(gameTable, whitesLocation, playersMove);
                printGameTable(gameTable, Num_Of_Rows, Num_Of_Columns);
                if (isWon(gameTable, blacksLocation))
                {
                    gamePhase = White_Winning_Phase;
                    break;
                }

                turnNum++;
                if (turnNum == Max_Num_Of_Turns)
                {
                    gamePhase = Tie_phase;
                    break;
                }

                playerTurn = Blacks_Turn;
                break;

            case Blacks_Turn:

                printf("B:\n");
                for (i = 0; i < 4; i++)
                {
                    scanf("%d", &playersMove[i]);
                }
                movePieces(gameTable, blacksLocation, playersMove);
                printGameTable(gameTable, Num_Of_Rows, Num_Of_Columns);
                if (isWon(gameTable, whitesLocation))
                {
                    gamePhase = Black_Winning_Phase;
                    break;
                }

                turnNum++;
                if (turnNum == Max_Num_Of_Turns)
                {
                    gamePhase = Tie_phase;
                    break;
                }

                playerTurn = Whites_Turn;
                break;
            }
            break;

        case White_Winning_Phase:
            printf("The whites won!\n");
            isPlaying = !isPlaying;
            break;

        case Black_Winning_Phase:
            printf("The blacks won!\n");
            isPlaying = !isPlaying;
            break;

        case Tie_phase:
            printf("Tie\n");
            isPlaying = !isPlaying;
            break;
        }
    }
}

/**
 * Moves the players pieces to where he chose
 * @param GameTable the table of the game
 * @param piecesLocation the current players games pieces and their locations
 * @param moveTo the player chosen piece to move and it's new locations
 */
void movePieces(char gameTable[MAX_SIZE][MAX_SIZE], int piecesLocation[2][2], int moveTo[4])
{
    const int Num_Of_Pieces = 2;
    int pieceToMove[2], newLocation[2], currentPiece;

    pieceToMove[0] = moveTo[0];
    pieceToMove[1] = moveTo[1];
    newLocation[0] = moveTo[2];
    newLocation[1] = moveTo[3];

    for (currentPiece = 0; currentPiece < Num_Of_Pieces; currentPiece++)
    {
        if (piecesLocation[currentPiece][0] == pieceToMove[0] && piecesLocation[currentPiece][1] == pieceToMove[1])
        {
            gameTable[newLocation[0]][newLocation[1]] = gameTable[pieceToMove[0]][pieceToMove[1]];
            gameTable[pieceToMove[0]][pieceToMove[1]] = Gempty_Cell_Icon;
            piecesLocation[currentPiece][0] = newLocation[0];
            piecesLocation[currentPiece][1] = newLocation[1];
        }
    }
}

/**
 * Checks if the current player won
 * @param gameTalbe the table of the game
 * @param piecesLocation the rival's pieces and their locations
 * @param isWon indicates if the current player won. returns true if he won and false if he didn't win
 */
bool isWon(char gameTable[MAX_SIZE][MAX_SIZE], int piecesLocation[2][2])
{
    const int Num_Of_Rows = 3, Num_Of_Columns = 3, Num_Of_Pieces = 2, Total_Num_Of_Moves = 16, Row = 0, Column = 1, Blocked = -1;
    bool isYouWon = false;
    int currentPiece;
    int dbUp, up, dbDown, down, dbRight, right, dbLeft, left, piecesRow, piecesColumn, timesBlocked = 0;

    for (currentPiece = 0; currentPiece < Num_Of_Pieces; currentPiece++)
    {
        piecesRow = piecesLocation[currentPiece][Row];
        piecesColumn = piecesLocation[currentPiece][Column];

        dbUp = piecesRow < 2 ? Blocked : piecesRow - 2;
        up = piecesRow < 1 ? Blocked : piecesRow - 1;
        dbDown = piecesRow > 0 ? Blocked : piecesRow + 2;
        down = piecesRow > 1 ? Blocked : piecesRow + 1;
        dbLeft = piecesColumn < 2 ? Blocked : piecesColumn - 2;
        left = piecesColumn < 1 ? Blocked : piecesColumn - 1;
        dbRight = piecesColumn > 0 ? Blocked : piecesColumn + 2;
        right = piecesColumn > 1 ? Blocked : piecesColumn + 1;

        if (up == Blocked)
            timesBlocked += 4;
        else
        {
            timesBlocked = (dbLeft == Blocked) || (gameTable[up][dbLeft] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;
            timesBlocked = (dbRight == Blocked) || (gameTable[up][dbRight] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;

            if (dbUp == Blocked)
                timesBlocked += 2;
            else
            {
                timesBlocked = (left == Blocked) || (gameTable[dbUp][left] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;
                timesBlocked = (right == Blocked) || (gameTable[dbUp][right] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;
            }
        }

        if (down == Blocked)
            timesBlocked += 4;
        else
        {
            timesBlocked = (dbLeft == Blocked) || (gameTable[down][dbLeft] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;
            timesBlocked = (dbRight == Blocked) || (gameTable[down][dbRight] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;

            if (dbDown == Blocked)
                timesBlocked += 2;
            else
            {
                timesBlocked = (left == Blocked) || (gameTable[dbDown][left] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;
                timesBlocked = (right == Blocked) || (gameTable[dbDown][right] != Gempty_Cell_Icon) ? timesBlocked + 1 : timesBlocked;
            }
        }
    }

    if (timesBlocked == Total_Num_Of_Moves)
        isYouWon = !isYouWon;

    return isYouWon;
}