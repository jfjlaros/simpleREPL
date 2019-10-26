Simple REPL for C++
===================

Examples
--------

Demo
~~~~

We show how to use simple functions in the demo_ program. In this program we
export two functions.

::

    $ ./demo
    > greet world
    Hi world.
    > inc 2
    3
    > exit

Calculator
~~~~~~~~~~

In the calculator_ program we show how to use class methods. In this program we
export some simple arithmetic functions.

::

    $ ./calculator 
    > show
    0
    > add 10
    > sub 2
    > show
    8
    > exit


.. _demo: https://github.com/jfjlaros/simpleREPL/blob/master/examples/demo/demo.cc
.. _calculator: https://github.com/jfjlaros/simpleREPL/blob/master/examples/calculator/calculator.cc
