program complex(input, output);
var
  a : array[1..3] of integer;
  x : integer;

procedure inctwice(var v : integer; delta : integer);
begin
  v := v + delta;
  v := v + delta
end;

function plusone(n : integer) : integer;
begin
  plusone := n + 1
end;

begin
  x := plusone(1);
  inctwice(x, 2);
  a[1] := x
end.
