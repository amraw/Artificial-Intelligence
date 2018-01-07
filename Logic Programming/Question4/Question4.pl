prime(2):-true.
prime(3):-true.
prime(N):- L is N-1, has_no_divisors_below(N,L-1).
divisible(_,0):-false.
divisible(N,X) :-X>0, M is N mod X,M=0.
sqrtFunc(N,X):- X is floor(sqrt(N)).
factor(2,[2]).
factor(3,[3]).
factor(P,[]):- P=<1.
factor(N,M):- N <50,Z is N, Z>2, findFactors(N,M,Z).
factor(N,M):- N >=50, sqrtFunc(N,Z), Z>2, findFactors(N, M,Z).
findFactors(1,[],_):- true.
findFactors(0,[],_):- true.
findFactors(N,[Z|T],Z):- N>=2,Z>=2, divisible(N,Z), prime(Z),X is div(N,Z),findFactors(X,T,Z).
findFactors(N,List,Z):- N>=2,Z>=2, \+divisible(N,Z),Q is Z-1, findFactors(N,List,Q).
findFactors(N,List,Z):- N>=2,Z>=2, divisible(N,Z), \+prime(Z),Q is Z-1,findFactors(N,List,Q).
findFactors(N,List,Z):- N>=2,Z>=2, \+divisible(N,Z), \+prime(Z),Q is Z-1,findFactors(N,List,Q).
has_no_divisors_below(_, 1):- true.
has_no_divisors_below(_, 0):- true.
has_no_divisors_below(N,L):- L>0, \+divisible(N,L), M is L-1,has_no_divisors_below(N,M).







