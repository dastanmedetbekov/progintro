{ 2.03. Что напечатает следующая программа? }

program demo1;
var
    x, y, z: integer;
begin
    x := 5;
    y := 10;
    z := x + y;
    x := z * 3;
    writeln(x)
end.
