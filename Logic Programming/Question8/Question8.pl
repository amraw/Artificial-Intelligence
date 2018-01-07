b(I,J):- \+p(x,I,J), \+p(o,I,J).
%Two x in a row, col and diagonal.
twoInaRow(x,R1,C1,C2):- p(x,R1,C1), p(x,R1,C2), \+(C1=C2).
twoInaCol(x,R2,R3,C3) :- p(x,R2,C3), p(x,R3,C3), \+(R2=R3).
twoInaDiag(x,R4,C4):- p(x,R4,R4), p(x,C4,C4), \+(R4=C4).
canWinX(x,R9,C9):-
	twoInaRow(x,R9,C10,C11),\+(C9=C10),\+(C9=C11),b(R9,C9).
canWinX(x,R10,C10):-
	twoInaCol(x,R11,R12,C10),\+(R10=R11),\+(R10=R12),b(R10,C10).
canWinX(x,R13,C13):-
	R13=C13,twoInaDiag(x,R14,C14),\+(R13=R14),\+(R13=C14),b(R13,C13).
canWinX(x,R15,C15):- p(x,1,3), p(x,2,2), R15=3, C15=1,b(R15,C15).
canWinX(x,R16,C16):- p(x,2,2), p(x,3,1), R16=1, C16=3,b(R16,C16).
canWinX(x,R17,C17):- p(x,1,3), p(x,3,1), R17=2, C17=2,b(R17,C17).
canWinItr(x,R,C,I,J):- I<4, J<4, canWinX(x,I,J), R is I, C is J,
	format('Go for win!~n').
canWinItr(x,R,C,I,J):- I < 4, J < 4, K is J+1, canWinItr(x,R,C,I,K).
canWinItr(x,R,C,I,J):- I < 4, J < 4, L is I+1, canWinItr(x,R,C,L,J).
%Two o in row, col and diagonal
twoInaRow(o,R5,C5,C6):- p(o,R5,C5), p(o,R5,C6), \+(C5=C6).
twoInaCol(o,R6,R7,C7) :- p(o,R6,C7), p(o,R7,C7), \+(R6=R7).
twoInaDiag(o,R8,C8):- p(o,R8,R8), p(o,C8,C8), \+(R8=C8).
canWinO(o,R9,C9):-
	twoInaRow(o,R9,C10,C11),\+(C9=C10),\+(C9=C11),b(R9,C9).
canWinO(o,R10,C10):-
	twoInaCol(o,R11,R12,C10),\+(R10=R11),\+(R10=R12),b(R10,C10).
canWinO(o,R13,C13):-
	R13=C13,twoInaDiag(o,R14,C14),\+(R13=R14),\+(R13=C14),b(R13,C13).
canWinO(o,R15,C15):- p(o,1,3), p(o,2,2), R15=3, C15=1,b(R15,C15).
canWinO(o,R16,C16):- p(o,2,2), p(o,3,1), R16=1, C16=3,b(R16,C16).
canWinO(o,R17,C17):- p(o,1,3), p(o,3,1), R17=2, C17=2,b(R17,C17).
canWinItr(o,R,C,I,J):- I<4, J<4, canWinO(o,I,J), R is I, C is J,
	format('move to block opponenet!~n').
canWinItr(o,R,C,I,J):- I < 4, J < 4, K is J+1, canWinItr(o,R,C,I,K).
canWinItr(o,R,C,I,J):- I < 4, J < 4, L is I+1, canWinItr(o,R,C,L,J).
%Predicate for query
ttt_move(x,R,C):- canWinItr(x,R,C,1,1).
ttt_move(x,R,C):- \+canWinItr(x,R,C,1,1), canWinItr(o,R,C,1,1).
%Facts in prolog
p(x,1,1).
p(x,2,1).
p(o,3,2).
p(o,3,3).










