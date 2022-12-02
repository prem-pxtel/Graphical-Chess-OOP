#ifndef PIECE_H
#define PIECE_H

class Piece {
 public:
  char piece;
  bool firstMove;
  bool lastmovecapture = false;
  char capturedpiece;
  bool capturedfirst;
  bool capturedpiececolour;
  Piece(char piece) : piece{piece} {}
  virtual ~Piece() {}
  virtual void move(char colOld, int rowOld, 
                    char colNew, int rowNew, char newPiece) = 0;
  virtual void revertmove(char colOld, int rowOld, 
                    char colNew, int rowNew, char newPiece) = 0;                    
  virtual void capture(int oldRow, char oldCol, int newRow, char newCol) = 0;
  virtual bool isValidMove(char oldPiece, char oldCol, int oldRow, char newCol, int newRow) = 0;
  virtual int getObsRow() = 0;
  virtual char getObsCol() = 0;
  virtual void clearObs() = 0;
};

class InvalidMove {};

#endif
