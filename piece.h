#ifndef PIECE_H
#define PIECE_H

class Piece {
 public:
  char piece;
  bool firstMove;
  bool lastMoveCapture = false;
  char capturedPiece;
  bool capturedFirst;
  bool capturedPieceColour;
  Piece(char piece) : piece{piece} {}
  virtual ~Piece() {}
  virtual void move(char colOld, int rowOld, 
                    char colNew, int rowNew, char newPiece) = 0;
  virtual void revertMove(char colOld, int rowOld, char colNew, 
                          int rowNew, char newPiece) = 0;                    
  virtual void capture(int oldRow, char oldCol, int newRow, char newCol) = 0;
  virtual bool isValidMove(char oldPiece, char oldCol, 
                           int oldRow, char newCol, int newRow) = 0;
  virtual bool isInDiagonalPath(char oldPiece, char oldCol, int oldRow, 
                                char newCol, int newRow) = 0;
  virtual int getObsRow() = 0;
  virtual char getObsCol() = 0;
  virtual void clearObs() = 0;
};

class InvalidMove {
 public:
  std::string errMsg;
  InvalidMove(std::string errMsg = "Invalid Command.") : errMsg{errMsg} {}
};

#endif
