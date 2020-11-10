# hasm
A simple 15 instruction set programming language. It runs on a 1024 cell memory tape and has 4 pointers. Cells are referenced as 'c' followed by the cell number with no space in between. Pointers are referenced as 'p' followed by the pointer number.

| command                   | description                                                                                                                                      |
|---------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------|
| set cell1 cell2/int       | sets the value at cell1 to the value of cell2 or int                                                                                             |
| stc cell char             | sets the value at cell to the integer value for char                                                                                             |
| dis cell                  | prints the integer value held by cell to the console                                                                                             |
| dsc cell                  | prints the ascii character with the value held by cell to the console, %128                                                                      |
| add cell1 cell2           | adds the value at cell2 to cell1                                                                                                                 |
| sub cell1 cell2           | subtracts the value at cell2 from cell1                                                                                                          |
| mul cell1 cell2           | multiplies the value at cell1 by cell2                                                                                                           |
| div cell1 cell2           | divides the value at cell1 by cell2                                                                                                              |
| mod cell1 cell2           | sets cell1 to the mod of the value at cell1 by cell2                                                                                             |
| cpr cell1 cell2 cell3     | if cell2 = cell3, sets cell1 to 0 if cell2 > cell3, sets cell1 to 1 if cell2 < cell3, sets cell1 to -1                                           |
| lbl label                 | creates label at current line labels are created before anything else happens,   so you can refer to labels that the program has not reached yet |
| gto label                 | goes to a label                                                                                                                                  |
| cgt cell label            | if the value at cell is not 0, goes to label                                                                                                     |
| gtc cell                  | gets a character from cin and sets the value at cell to the integer value                                                                        |
| ptr pointer cell1 (cell2) | sets pointer to point to cell1,   if cell2 is present offsets the pointer by the value at cell2 
