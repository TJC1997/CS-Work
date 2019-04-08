%Author:Yuhang Chen 933190490
%AUthor:DianXiong Zhang 932994919


% Here are a bunch of facts describing the Simpson's family tree.
% Don't change them!

female(mona).
female(jackie).
female(marge).
female(patty).
female(selma).
female(lisa).
female(maggie).
female(ling).

male(abe).
male(clancy).
male(herb).
male(homer).
male(bart).

married_(abe,mona).
married_(clancy,jackie).
married_(homer,marge).

married(X,Y) :- married_(X,Y).
married(X,Y) :- married_(Y,X).

parent(abe,herb).
parent(abe,homer).
parent(mona,homer).

parent(clancy,marge).
parent(jackie,marge).
parent(clancy,patty).
parent(jackie,patty).
parent(clancy,selma).
parent(jackie,selma).

parent(homer,bart).
parent(marge,bart).
parent(homer,lisa).
parent(marge,lisa).
parent(homer,maggie).
parent(marge,maggie).

parent(selma,ling).



%%
% Part 1. Family relations
%%

% 1. Define a predicate `child/2` that inverts the parent relationship.

child(X,Y) :- parent(Y,X).

% 2. Define two predicates `isMother/1` and `isFather/1`.

isMother(X) :- female(X),parent(X,_).
isFather(X) :- male(X),parent(X,_).

% 3. Define a predicate `grandparent/2`.

grandparent(X,Z) :- parent(X,Y),parent(Y,Z).

% 4. Define a predicate `sibling/2`. Siblings share at least one parent.

sibling(X,Y) :- child(X,Z),child(Y,Z),X\=Y.

% 5. Define two predicates `brother/2` and `sister/2`.

sister(X,Y) :- sibling(X,Y),female(X).
brother(X,Y) :- sibling(X,Y),male(X).

% 6. Define a predicate `siblingInLaw/2`. A sibling-in-law is either married to
%    a sibling or the sibling of a spouse.

siblingInLaw(X,Y) :- sibling(X,Z),married(Y,Z).
siblingInLaw(X,Y) :- sibling(Y,Z),married(X,Z).

% 7. Define two predicates `aunt/2` and `uncle/2`. Your definitions of these
%    predicates should include aunts and uncles by marriage.

aunt(X,Y) :- female(X),sibling(X,Z),parent(Z,Y).
aunt(X,Y) :- female(X),siblingInLaw(X,Z),parent(Z,Y).
uncle(X,Y) :- male(X),sibling(X,Z),parent(Z,Y).
uncle(X,Y) :- male(X),siblingInLaw(X,Z),parent(Z,Y).

% 8. Define the predicate `cousin/2`.

cousin(X,Y):- uncle(Z,X),parent(Z,Y).
cousin(X,Y):- aunt(Z,X),parent(Z,Y).

% 9. Define the predicate `ancestor/2`.

ancestor(X,Y):- grandparent(X,Y).
ancestor(X,Y):- parent(X,Y).

% Extra credit: Define the predicate `related/2`.

decendents(X,Y):-parent(X,Y).
decendents(X,Y):-parent(X,A),parent(A,Y).


%parent generation
related(X,Y):-parent(Y,X).
related(X,Y):-parent(A,X),married(Y,A).

%current generation
related(X,Y):-married(X,Y).
related(X,Y):-sibling(X,Y).
related(X,Y):-siblingInLaw(X,Y).
related(X,Y):-cousin(X,Y).
related(X,Y):-parent(X,A),married(A,B),parent(Y,B).

%child generation
related(X,Y):-parent(X,Y).
related(X,Y):-siblingInLaw(X,A),parent(A,Y).
related(X,Y):-sibling(A,X),parent(A,Y).

%recursive call siblinginlaw,parent generation and child generation
related(X,Y):-siblingInLaw(X,A),related(A,Y).
related(X,Y):-parent(A,X),related(A,Y).
related(X,Y):-parent(X,A),related(A,Y).


%%
% Part 2. Language implementation (see course web page)
%%
expr(t).
expr(f).

cmd(X,Y,[X|Y]):-number(X). %number
cmd(X,Y,[X|Y]):-string(X). %string
cmd(X,Y,[X|Y]):-expr(X). %bool
cmd(add,[F,S|S1],[X|S1]):-X is (F+S).
cmd(lte,[F,S|S1],[t|S1]):-(F=<S).
cmd(lte,[F,S|S1],[f|S1]):-(F>S).
cmd(if([A],[_]),[t|S],[A|S]).
cmd(if([_],[B]),[f|S],[B|S]).

prog([],S,S).
prog([C|RS],S1,S2):-cmd(C,S1,S3),prog(RS,S3,S2).
