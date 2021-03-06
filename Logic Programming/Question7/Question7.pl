findSum:- Variable=[S,E,N,D,M,O,R,Y],Values=[0,1,2,3,4,5,6,7,8,9],
	variable_value_mapping(Variable,Values), M > 0, S >0,
	        S*1000+E*100+N*10+D+
	        M*1000+O*100+R*10+E=:=
	M*10000+O*1000+N*100+10*E+Y,
	printMapping(['S','E','N','D','M','O','R','Y'],Variable).

%Function for assigning values
assign(H,[H|T],T).
assign(A, [H1|T1],[H1|T2]):- assign(A,T1,T2).

%Calculate Variable Value Mapping
variable_value_mapping([],_).
variable_value_mapping([H|T],Values):- assign(H,Values,List2),variable_value_mapping(T,List2).

%Prints the result.
printMapping([],[]):- true.
printMapping([H1|T1], [H2|T2]):- format('Value of ~s is ~d~n',[H1,H2]),printMapping(T1, T2).
