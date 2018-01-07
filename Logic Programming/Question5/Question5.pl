generateBit(0,[]):-true.
bitvec(0,[]):- true.
bitvec(N,K):- generateBit(N,K).
generateBit(N,[0|T]) :-  N >0, M is N-1 , generateBit(M,T).
generateBit(N,[1|T]) :- N >0,  M is N-1 , generateBit(M,T).
%Code Generator
code(N,L,X):- generateCodeBit(N,L,X).
generateCodeBit(0,_,[]):- true.
generateCodeBit(N,L,[0|T]):- N > 0, M is N-1, N >L,generateCodeBit(M,L,T).
generateCodeBit(N,L,[1|T]):- N > 0, M is N-1, L >0,P is L-1, generateCodeBit(M,P,T).
