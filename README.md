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
