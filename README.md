# Interpreter_CS280
This repository is for the class in which I created a lexical analyzer, parser, and a basic interpreter for a small made up programming language.

Below, I included some examples of how the interpreter works, with the fake programming language and the output of executing the fake programming language script.

# Example Executions
## Example 1: Clean Program
    PROGRAM circle;
      (*Clean Program*)
    VAR
      (*Variable declarations*)
      r, a, p, b : REAL; 
      i, j, sum : INTEGER;
      str1, str2: STRING;	
    BEGIN
      i := 8;
      p := 6;
      a := 0;
      sum := 0;
      str1 := 'Hello World!';
      j := -3;
      IF ( p > 5) THEN
          a := (3.14) + j * - p
      ELSE
        IF (p = 0 ) THEN str1 := 'Hello';


      (*Display the results*)
      WRITELN  ('The output results are: ' , p, ' ', str1, ' ', a, ' ', i, ' ', j);
    END
### Output:
![Output1](https://user-images.githubusercontent.com/89932319/201484476-ada3f8ab-a117-4ab6-a6e9-10cc35004d7d.png)

## Example 2: String Concatenation

    PROGRAM circle;
      (*Testing string concatenation*)
    VAR
      (*Variable declarations*)
      r, p, a : REAL; 
      str1, str2 : String;
    BEGIN
      str1 := 'Good Morning';
      str2 := str1 + ' ' + 'NJIT' ;

      (*Display the results*)
      WRITELN  ('The output results are ' , str1, ', ', str2);
    END
### Output:
![Output2](https://user-images.githubusercontent.com/89932319/201484802-44b4cd65-07f9-4082-b429-d21cf53908d1.png)

## Example 3: Errors in Program (Illegal Mixed Type Operands)

    PROGRAM circle;
      (*Testing Illegal mixed type operands in expressions*)
    VAR
      (*Variable declarations*)
      r, p, a : REAL; 
      str : String;
    BEGIN
      r := 8;
      p := 'Hello World!' + r;
      IF ( p = 5) THEN
          a := (3.14) + r * p
      ELSE
        a := p;

      (*Display the results*)
      WRITELN  ('The output results are ' , r, ' ', p, ' ', a);
    END
### Output:
![Output3](https://user-images.githubusercontent.com/89932319/201485318-b4cf9cc6-827e-44aa-8310-bdf650c14b4b.png)


## Example 4: Errors in Program (Mixed Type Operands)

    PROGRAM circle;
      (*Testing Mixed Types Operands for a Logic Expression*)
    VAR
      (*Variable declarations*)
      r, p, a : REAL; 
      str : String;
    BEGIN
      r := 8;
      p := 4;
      str := 'Hello';
      IF ( str = 5) THEN
          a := (3.14) + r * p
      ELSE
        a := p;

      (*Display the results*)
      WRITELN  ('The output results are ' , r, ' ', p, ' ', a);
    END
 ### Output:
![Output4](https://user-images.githubusercontent.com/89932319/201485600-c7bd8374-9bff-4505-b988-d36bcfc90d22.png)


## Example 5: Errors in Program (Division by Zero)

    PROGRAM circle;
      (*Testing divide by zero execution error*)
    VAR
      (*Variable declarations*)
      r, p, a : REAL; 
      str : String;
    BEGIN
      r := 8;
      p := 0 ;
      a := r/p;
      IF ( p = 5) THEN
          a := (3.14) + r * p
      ELSE
        a := p;

      (*Display the results*)
      WRITELN  ('The output results are ' , r, ' ', p, ' ', a);
    END
### Output:
![Output5](https://user-images.githubusercontent.com/89932319/201485789-a414ee40-9aed-4cc3-a922-fd122f14cf20.png)

## Example 6: Clean Program

    PROGRAM circle;
      (*Testing expression evaluation*)
    VAR
      (*Variable declarations*)
      r, p, a : REAL; 
      i, j : INTEGER;
    BEGIN
      r := 5.25;
      p := 6.75 ;
      i := 25;
      j := i / r;

      (*Display the results*)
      WRITELN  ('The output results are ' , (i / r), ', ', j);
    END
### Output:
![Output6](https://user-images.githubusercontent.com/89932319/201485919-76fa4246-831e-4282-bfb5-3f976c92dfd9.png)

