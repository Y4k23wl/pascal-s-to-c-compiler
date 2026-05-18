program arr;
var
  a : array[1..5] of integer;
  m : array[0..2, 0..3] of real;
  i : integer;
begin
  for i := 1 to 5 do
    a[i] := i * i;
  m[0, 0] := 1.5
end.
