# Bind expressions and standard functors 

Bind expressions for arithmetic expressions (x = first argument, y = second argument) by using standard functors and functions.

## Project Setup for Cevelop

1. Install [Cevelop](http://cevelop.com/)
2. Open the repository as a workspace
3. Import as existing projects into workspace

## Build Project

You can use Eclipse to build the project or the provided makefile.

```
make
```

## Run Tests

We use [CUTE](http://cute-test.com/) for our unit tests.
To run the tests you need to compile the tests and then simply run the
executable. This will output the test results to the console
and a XML file.

```
make test
```
