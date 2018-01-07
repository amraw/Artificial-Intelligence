%Facts Given in file.
parent(bart,homer).
parent(bart,marge).
parent(lisa,homer).
parent(lisa,marge).
parent(maggie,homer).
parent(maggie,marge).
parent(homer,abraham).
parent(herb,abraham).
parent(tod,ned).
parent(rod,ned).
parent(marge,jackie).
parent(patty,jackie).
parent(selma,jackie).
female(maggie).
female(lisa).
female(marge).
female(patty).
female(selma).
female(jackie).
male(bart).
male(homer).
male(herb).
male(burns).
male(smithers).
male(tod).
male(rod).
male(ned).
male(abraham).
%Rules to define Relations
brother(Person1,Person2) :- male(Person2), parent(Person1,Parent), parent(Person2,Parent),(Person1\=Person2).
sister(Person3, Person4) :- female(Person4), parent(Person3,Parent), parent(Person4,Parent), (Person3\=Person4).
aunt(Person5,Person6):- female(Person6), parent(Person5,Parent), sister(Parent,Person6).
uncle(Person7,Person8):-male(Person8), parent(Person7,Parent), brother(Parent,Person8).
grandfather(Person9, Person10):- male(Person10), parent(Person9,Parent), parent(Parent,Person10).
granddaughter(Person11,Person12):- female(Person12), parent(Person12,Parent), parent(Parent,Person11).
ancestor(Person13,Person14):-parent(Person13,Person14).
ancestor(Person15,Person16):-parent(Person15, Parent), ancestor(Parent,Person16).
descendant(Person17,Person18):-ancestor(Person18,Person17).
unrelated(Person19,Person20):- \+ ancestor(Person19,Person20), \+ (descendant(Person19,Person20)), \+ (brother(Person19,Person20)),\+(sister(Person19,Person20)),\+ (aunt(Person19,Person20)),\+ (uncle(Person19, Person20)),\+ (aunt(Person20,Person19)),\+ (uncle(Person20, Person19)).
