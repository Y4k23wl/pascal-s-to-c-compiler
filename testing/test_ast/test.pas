program demo;
const
  a = 10;
  b = 3;
var
  i, x : integer;
  y : real;

begin
  x := a + b * 2;
  y := 3.14;

  if x > 10 then
    write(x)
  else
    write(b);

  for i := 1 to 5 do
    write(i)

  read(x);
  write(y)
end.
