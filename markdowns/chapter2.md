# Basic operations  

We will see:
1. [Board representation](markdowns/board.md), the correlation between a 2D board and a 64bits integer
2. [Coordinates definition](markdowns/coordinates.md). There is in fact several ways of defining coordinates (cartesian, bit position or bitboard).
3. [Accessing and setting](markdowns/single_cell_operations.md) values at coordinates.

All along this tutorial, we will the basis concerning the **logical** and **bitwise** common operations. If you're not comfortable with this operators, you will probably need a reminder (that is there).

# Reminder: logical and bitwise operators

You can find here all the logic we'll need in the next pages. We will also use some math symbolic:
* AND : \wedge
* OR : \vee
* NOT : \neg
* XOR : \oplus
* Left shift : \ll
* Right shift : \gg

## Logical operators

![Logical operators](http://shukaiyang.myweb.hinet.net/cpp/figures/bitwiseops.gif)

The mathematical symbols we will sometimes use:
* AND : \

## Bitwise operators

![Bitwise operators](http://www.circuitsgallery.com/wp-content/uploads/2012/07/Bitwise-operators-in-C.png)

Now, let's take a look at how is defined the board when it comes to bitboard theory.
