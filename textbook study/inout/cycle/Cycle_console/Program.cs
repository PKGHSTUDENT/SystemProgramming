
// tast 1;
int i;
for (i = 0; i < 20; i++)
{
    Console.Write($"{Math.Pow(2, i)} ");
}

// task 2;

Console.Write("Enter x: ");
double x = Convert.ToDouble(Console.ReadLine());
Console.Write("Enter e: ");
double e = Convert.ToInt32(Console.ReadLine());
double s = 0, temp = 1;

i = 1;
while (true)
{
    temp = (i / Math.Pow(x, i)) - (++i / Math.Pow(x, i));
    if (Math.Abs(temp) <= e)
    {
        break;
    }
    s += temp;
    ++i;
}

Console.WriteLine(s);

Console.ReadKey();