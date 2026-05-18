program subs;
var
  n : integer;

procedure inc(var v : integer; delta : integer);
begin
  v := v + delta
end;

function square(x : integer) : integer;
begin
  square := x * x
end;

begin
  n := 3;
  inc(n, 2);
  n := square(n)
end.
