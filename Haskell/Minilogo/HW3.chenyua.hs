module HW3 where

  import Prelude hiding (Num)
  -- type Prog = [Cmd]
  -- data Cmd
  --    = PushI Int
  --    | PushB Bool
  --    | Add
  --    | Equ
  --    | IfElse Prog Prog
  --   deriving (Eq,Show)

  --Task1
  type Num = Int
  type Var = String
  type Macro = String
  type Prog = [Cmd]
  data Mode = Down | Up
    deriving (Eq,Show)
 
  data Expr= V Var | N Num | Add Expr Expr
    deriving (Eq,Show)

  data Cmd= Pen Mode
          | Move Expr Expr
          | Define Macro [Var] Prog
          | Call Macro [Expr]
    deriving (Eq,Show)
  

  --Task2  
    -- Define line (x1,y1,x2,y2){
    --   Pen up; Move x1 y1;
    --   Pen down; Move x2 y2;
    -- }
  line=Define "line" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2")]
    
  --Task3
    -- Define nix (x,y,w,h){
    --   line(x,y,x+w,y+h);
    --   line(x,y+h,x+w,y);
    -- }
  nix=Define "nix" ["x","y","w","h"] [Call "line" [V "x",V "y",Add (V "x") (V "w"),Add (V "y") (V "h")],Call "line" [V "x",Add (V "y") (V "h"),Add (V "x") (V "w"),V "y"]]
  

  --Task4
  steps :: Int -> Prog
  steps x
    |x==0 = [Pen Up,Move (N 0) (N 0)]
    |x==1 = steps (x-1) ++ [Pen Down,Move (N 0) (N 1),Move (N 1)(N 1)]
    |otherwise = steps (x-1) ++ [Move (N (x-1)) (N x),Move (N x)(N x)]


  --Task5
  checkType :: Cmd -> [Macro]
  checkType (Define name _ p) = [name] ++ macros p
  checkType (Call name _) = [name]
  checkType (Pen _)= []
  checkType (Move _ _)= []

  macros :: Prog -> [Macro]
  macros []=[]
  macros (x:xs)=(checkType x) ++ (macros xs)

  ex1:: Prog
  ex1=[Define "nix" ["x","y","w","h"] [Call "line" [V "x",V "y",Add (V "x") (V "w"),Add (V "y") (V "h")],Call "hello" [V "x",Add (V "y") (V "h"),Add (V "x") (V "w"),V "y"]]]
  --macros ex1
  --output ["nix","line","hello"]
  
  --Task6
  parseParam :: [Var] -> String
  parseParam [x] = x
  parseParam (x:xs)=x ++ "," ++ (parseParam xs)


  parseType :: Expr -> String
  parseType (V s)=s
  parseType (N n)=show n
  parseType (Add a b)="add("++parseType(a) ++ " " ++ parseType(b) ++")"
  
  parseExpr :: [Expr] -> String
  parseExpr [x]=parseType x
  parseExpr (x:xs)=parseType x ++ "," ++ (parseExpr xs)


  parseMove :: Expr -> String
  parseMove (V s)=s
  parseMove (N n)=(show n)
  parseMove (Add a b)="add("++(parseMove a) ++ " " ++ (parseMove b)++")"

  parseFunction :: Cmd -> String
  parseFunction (Define name param prog)="define " ++ name ++ " (" ++ parseParam param ++ ")" ++ "{\n" ++ pretty prog ++"}\n"
  parseFunction (Pen m)
    |m==Up ="\t pen up;\n"
    |otherwise="\t pen down;\n"
  parseFunction (Move a b)="\tmove "++(parseMove (optE a)) ++" " ++ (parseMove (optE b)) ++ ";\n"
  parseFunction (Call name exprList)="\t"++name ++ "(" ++ (parseExpr exprList) ++ ")\n"

  simplifyExpr :: Cmd -> Cmd
  simplifyExpr (Define n l p) = Define n l (optP p)
  simplifyExpr (Call n list) = Call n (loopOptE list)
  simplifyExpr (Move e1 e2)= Move (optE e1) (optE e2)
  simplifyExpr a=a

  pretty :: Prog -> String
  pretty []=[]
  pretty (x:xs)=(parseFunction (simplifyExpr x))++(pretty xs)

  ex2:: Prog
  ex2=[Define "line" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2")],Define "hello" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2")]]
  
  ex3:: Prog
  ex3=[Define "nix" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2"),Call "line" [V "x",V "y",Add (V "x") (V "w"),Add (V "y") (V "h")]]]

  ex4:: Prog
  ex4=[Define "nix" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2"),Call "line" [V "x",V "y",Add (Add (N 1) (N 5)) (V "x"),Add (V "y") (V "h")]]]
  
  ex8:: Prog
  ex8=[Define "line" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2"),Define "hello" ["x1","y1","x2","y2"] [Pen Up ,Move (V "x1") (V "y1"),Pen Down,Move (V "x2") (V "y2")]]]
  
  
  --Task7
  optE :: Expr -> Expr
  optE (N n)=(N n)
  optE (V s)=(V s)
  optE (Add (N a) (N b))=(N (a+b))
  optE (Add (N a) (V b))=(Add (N a) (V b))
  optE (Add (V a) (N b))=(Add (V a) (N b))
  optE (Add (V a) (V b))=(Add (V a) (V b))
  optE (Add (N a) (Add b c))=optE (Add (N a) (optE (Add b c)))
  optE (Add (Add b c) (N a))=optE (Add (optE (Add b c)) (N a))
  optE ((Add (V a) (Add b c)))=optE (Add (V a) (optE (Add b c)))
  optE ((Add (Add b c) (V a)))=optE (Add (optE (Add b c)) (V a))
  optE ((Add (Add a b) (Add c d)))=optE (Add (optE (Add a b)) (optE (Add c d)))

  ex5::Expr
  ex5=Add (Add (N 2) (N 3)) (V "x")

  ex6::Expr
  ex6=Add (Add (N 2) (N 3)) (Add (N 2) (N 3))

  --Task8
  loopOptE :: [Expr] -> [Expr]
  loopOptE []=[]
  loopOptE (x:xs)=[optE x] ++ (loopOptE xs)

  checkExpr :: Cmd -> Prog
  checkExpr (Define n l p) = [Define n l (optP p)]
  checkExpr (Call n list) = [Call n (loopOptE list)]
  checkExpr (Move e1 e2)= [Move (optE e1) (optE e2)]
  checkExpr a=[a]

  optP :: Prog -> Prog
  optP []=[]
  optP (x:xs)=checkExpr x ++ (optP xs)

  ex7:: Prog
  ex7=[Define "line" ["x1","y1","x2","y2"] [Pen Up ,Move (Add (Add (N 2) (N 3)) (V "x")) (V "y1"),Pen Down,Move (V "x2") (Add (V "x") (Add (N 2) (N 3))) ]]
