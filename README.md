# Graphical Chess using OOP

A graphical chess application with multiple game modes and classical AI.

## Contributors: Prem Patel, Aviral Sharma

As a high-level overview of our project, we implement an Observer design pattern, with a Subject abstract class responsible for providing methods for attaching, detaching and notifying observers. There is also an abstract observer class which contains a notify method that is inherited by our concrete observers. In our implementation, we have our concrete Subject being a Board class which has the actual chess board (stored as a 2D vector), accessor and mutator methods, as well as corresponding board information such as the number of turns, number of wins, whether the white or black king is in check, etc. This allows for us to instantiate a Text observer and Graphical observer (TextOb and GraphicalOb), both observing our board object. All three instances of these objects are created in main.cc.

As a chess board is comprised of pieces, we naturally have an abstract Piece superclass, pointers of which are used to fill our 2D vector board, with the 6 specific chess pieces (Pawn, Rook, Knight, Bishop, Queen, King) represented as derived classes of Piece, along with a Blank derived class for empty spots on the chess board. This allows for individual pieces to store information that can be unique to each instance of a piece on the chess board, such as whether the piece has had its first move already. In addition to this, methods in the Piece class are pure virtual methods which allows for functions like move, capture, and isValidMove to be overridden in each concrete Piece class, allowing for unique movement, captures, etc., depending on the piece. 

![image](https://github.com/prem-pxtel/Graphical-Chess-OOP/assets/45958082/ad694914-ad9b-49a4-b224-500fff9b284a)

Graphical chess board in text form, updated through the use of a concrete text observer

![image](https://github.com/prem-pxtel/Graphical-Chess-OOP/assets/45958082/91d565ef-c06a-4a2f-b9f6-a1b3a3e14360)

Chess board in text form, updated through the use of a concrete text observer

### See UML diagram for detailed class information:
[uml.pdf](https://github.com/prem-pxtel/Graphical-Chess-OOP/files/12641574/uml.pdf)
