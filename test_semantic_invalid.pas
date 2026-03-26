program bad;
const
  c = 1;
var
  a : array[1..3] of integer;
  x : integer;
  y : real;

procedure p(var v : integer; n : integer);
begin
  v := v + n
end;

function f(n : integer) : integer;
begin
  f := n
end;

begin
  c := 2;
  x := z;
  x := p(x, 1);
  p(1, x);
  p(x);
  if x then
    write(a);
  read(a);
  y := a;
  a := x;
  x := f(x, y)
end.
