# recursive_descent_parser_pl0
PL/0 EBNF - resursive descent parsing
1. sample PL/0 code:
--------------------
  var x, squ;
  procedure square;
  begin
    squ := x * x
  end;

  begin
    x := 1;
    while x <= 10 do
    begin
      call square;
      ! squ;
      x := x + 1
    end
  end
  .

2. EBNF form:
Terminals are expressed in quotes. Each non-terminal is defined
by a rule in the grammar, except for *ident* and *number*, which
are assumed to be implicitly defined. Things in {...} can be 
repeated 0+ times.

program = block "." .
block =
  ["const" ident "=" number {"," ident "=" number} ";"]
  ["var" ident {"," ident} ";"]
  ["procedure" ident ";" block ";"} statement .

statement =
  ident ":=" expression
  | "?" ident
  | "!" expression
  | "begin" statement {";" statement} "end"
  | "if" condition "then" statement
  | "while" condition "do" statement .

condition =
  "odd" expression
  | expression ("="|"#"|"<"|"<="|">"|">=") expression .

expression = ["+"|"-"] term {("+"|"-") term} .

term = factor {("*"|"/") factor} .

factor = 
  ident
  | number
  | "(" expression ")" .
