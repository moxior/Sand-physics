#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>


using namespace std;



class Cell{
public:
    string type;
    string displayCharacter;
    int x,y;
    bool rendered = false;
    Cell(string InitialType){
       type = InitialType;
       if(type == "Empty"){displayCharacter=" ";}
       else if(type == "Sand"){displayCharacter = "#";}
       else if(type == "Obstacle"){displayCharacter = "x";}

    }

};

class Table{

public:
    int tableSize;
    vector<vector<Cell>> table;
    void constructTable(){
        for(int y = 0;y<tableSize;y++){
            vector<Cell> row;

            for(int x = 0;x<tableSize;x++){

                Cell emptyCell = Cell("Empty");
                emptyCell.x = x;
                emptyCell.y = y;
                row.push_back(emptyCell);

            }
            table.push_back(row);
        }
    }
    void displayTable(){
        for(int y = 0;y<tableSize;y++){
            string row = "";
            for(int x = 0;x<tableSize;x++){

                row+=table[y][x].displayCharacter;


            }
            cout<<row<<endl;
        }

    }
    bool cellExists(int x, int y){

        if ((0<=x && x<tableSize)&&(0<=y &&y<tableSize)){
            return true;
        }
        return false;
    }
    void moveCell(Cell cell, int x, int y){
        int newX,newY;
        newX = x;
        newY = y;
        Cell placeholder = Cell("Empty");


        if (true){
            table[cell.y][cell.x] = placeholder;
        }
        cell.y = newY;
        cell.x = newX;
        cell.rendered = true;
        table[newY][newX] = cell;



    }
    void renderFrame(){
        for(int i = 0; i<tableSize;i++){
            for(int j = 0;j<tableSize;j++){
                table[j][i].rendered = false;
            }
        }
    }
    void calculateNextSandCollision(Cell cell){
        int x,y;
        x = cell.x;
        y = cell.y;
        if(cellExists(x,y+1) && getCell(x,y+1).type == "Empty"){
            moveCell(cell,x,y+1);
        }
        else if(cellExists(x+1,y+1) && getCell(x+1,y+1).type == "Empty"){
            moveCell(cell,x+1,y+1);
        }
        else if(cellExists(x-1,y+1) && getCell(x-1,y+1).type == "Empty"){
            moveCell(cell,x-1,y+1);
        }


    }
    void randomizeCellSpread(Cell cell, int amount){
        for (int i = 0;i<amount;i++){
            int x,y;
            x = rand() % tableSize;
            y = rand() % tableSize;
            moveCell(cell,x,y);
        }
    }
    void spawnCell(Cell cell,int x,int y){

        cell.x = 0;
        cell.y = 0;
        moveCell(cell,x,y);

    }
    Cell getCell(int x,int y){
        return table[y][x];
    }

    Table(int tsize){
        tableSize = tsize;
    }
};
int main()
{

    Table grid = Table(40);
    grid.constructTable();

    int iterations = 0;
    grid.displayTable();
    int renderStep = 8;

    Cell obs = Cell("Obstacle");
    grid.randomizeCellSpread(obs,60);

    while (true){
        iterations +=1;
        if (iterations%3 == 0){
            Cell cell = Cell("Sand");
            grid.spawnCell(cell,3,1);
        }
        for (int y = 0;y<grid.tableSize;y++){
            for(int x = 0;x<grid.tableSize;x++){
                Cell currentCell = grid.getCell(x,y);
                if (currentCell.type == "Sand" && currentCell.rendered == false){

                    grid.calculateNextSandCollision(currentCell);

                }
            }
        }
        grid.displayTable();
        Sleep(1000/renderStep);

        system("cls");
        grid.renderFrame();




    }

    return 0;
}
