candidate(X,Y):- visited(A,B), X is A-1, Y is B, X>0, \+visited(X,Y).
candidate(X,Y):- visited(A,B), X is A, Y is B+1, Y<5, \+visited(X,Y).
candidate(X,Y):- visited(A,B), X is A+1, Y is B, X<5, \+visited(X,Y).
candidate(X,Y):- visited(A,B), X is A, Y is B-1, Y>0, \+visited(X,Y).
%Find safe location
safe(X,Y):- Z is X-1, Z >0, \+breeze(Z,Y),\+stench(Z,Y),visited(Z,Y).
safe(X,Y):- Z is X+1, Z <5, \+breeze(Z,Y),\+stench(Z,Y),visited(Z,Y).
safe(X,Y):- U is Y-1, U >0, \+breeze(X,U),\+stench(X,U),visited(X,U).
safe(X,Y):- U is Y+1, U <5, \+breeze(X,U),\+stench(X,U),visited(X,U).

safe(X,Y):-  A is Y-1, A >0, B is X-1, B >0, breeze(X,A),stench(B,Y).
safe(X,Y):-  A is Y-1, A >0, B is Y+1, B <5, breeze(X,A),stench(X,B).
safe(X,Y):-  A is Y-1, A >0, B is X+1, B <5, breeze(X,A),stench(B,Y).

safe(X,Y):-  A is X-1, A >0, B is X+1, B <5, breeze(A,Y),stench(B,Y).
safe(X,Y):-  A is X-1, A >0, B is Y+1, B <5, breeze(A,Y),stench(X,B).
safe(X,Y):-  A is X-1, A >0, B is Y-1, B >0, breeze(A,Y),stench(X,B).

safe(X,Y):-  A is Y+1, A <5, B is X-1, B >0, breeze(X,A),stench(B,Y).
safe(X,Y):-  A is Y+1, A <5, B is X+1, B <5, breeze(X,A),stench(B,Y).
safe(X,Y):-  A is Y+1, A <5, B is Y-1, B >0, breeze(X,A),stench(X,B).

safe(X,Y):-  A is X+1, A <5, B is X-1, B >0, breeze(A,Y),stench(B,Y).
safe(X,Y):-  A is X+1, A <5, B is Y+1, B <5, breeze(A,Y),stench(X,B).
safe(X,Y):-  A is X+1, A <5, B is Y-1, B >0, breeze(A,Y),stench(X,B).
%Find pit at location X, Y
pit(X,Y):- C is X-1, D is Y-1, C =0, D =0, breeze(X,Y+1), breeze(X+1,Y).
pit(X,Y):- E is Y-1, E=0, breeze(X+1,Y), breeze(X,Y+1),breeze(X-1,Y).
pit(X,Y):- G is X+1, F is Y-1,F=0, G>4, breeze(X-1,Y), breeze(X,Y+1).
pit(X,Y):- H is X-1, H=0, breeze(X+1,Y), breeze(X,Y+1), breeze(X,Y-1).
pit(X,Y):- I is X-1, J is Y+1, I=0, J>4, breeze(X+1,Y), breeze(X,Y-1).
pit(X,Y):- K is Y+1, K > 4, breeze(X-1,Y), breeze(X+1,Y), breeze(X,Y-1).
pit(X,Y):- L is X+1, M is Y+1, L >4, M > 4, breeze(X-1,Y), breeze(X,Y-1).
pit(X,Y):- breeze(X-1,Y), breeze(X+1,Y),breeze(X,Y-1), breeze(X,Y+1).
%Find wumpus at location X, Y
wumpus(X,Y):- C is X-1, D is Y-1, C =0, D =0, stench(X,Y+1), stench(X+1,Y).
wumpus(X,Y):- E is Y-1, E=0, breeze(X+1,Y), stench(X,Y+1),stench(X-1,Y).
wumpus(X,Y):- G is X+1, F is Y-1,F=0, G>4, stench(X-1,Y), stench(X,Y+1).
wumpus(X,Y):- H is X-1, H=0, breeze(X+1,Y), stench(X,Y+1), stench(X,Y-1).
wumpus(X,Y):- I is X-1, J is Y+1, I=0, J>4, stench(X+1,Y), stench(X,Y-1).
wumpus(X,Y):- K is Y+1, K > 4, breeze(X-1,Y), stench(X+1,Y), stench(X,Y-1).
wumpus(X,Y):- L is X+1, M is Y+1, L >4, M > 4, stench(X-1,Y), stench(X,Y-1).
wumpus(X,Y):- stench(X-1,Y), stench(X+1,Y),stench(X,Y-1), stench(X,Y+1).
%move function
move(X,Y):- candidate(X,Y), safe(X,Y),\+pit(X,Y),\+wumpus(X,Y).
%Fact for wumpus world
visited(1,1).
visited(2,1).
visited(1,2).
stench(2,1).
breeze(1,2).
visited(2,2).





