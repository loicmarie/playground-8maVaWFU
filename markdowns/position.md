# Position

Now we can find ourselves in a 2D board, we will see how to **access** and **modify** cells.

First of all, we will study how to use cartesian coordinates (x,y) with **absolute position**. In the next chapter, we will do the same thing using **relative position** this time.

To well understand how to deal with absolute positioning, we will see:
- How to [define a cell with absolute coordinates](#cells-and-absolute)
- How to [get a cell value](#get-cell)
- How to [set a cell value](#set-cell)

**Reminder**: in this tutorial (which uses C++), the `Bitboard` type has been defined as an unsigned 64bits integer (corresponding to the `uint64_t` type)

# <a name="cells-and-absolute"></a>  Cells and absolute positioning

We have said that a position is of type `Bitboard`. So how is defined a cell ?

Response is... a Bitboard ! Yes, that's pretty confusing.

> _I don't get the difference ?_

In fact a bitboard representing a cell is a sequence with only **1 bit at 1** and **the other at 0**. This type of binary vector is often used in different computing domains and is called "**one-hot encoding**".

![Cell](img/cell.png)

# <a name="get-cell"></a> Getting cell value

Now we simply want to transform (x,y) to bit position and vice-versa.

#### Cartesian coordinates and bit position

The formula is quite simple and is highly used when working with 1D vector instead of 2D arrays.

```math
\begin{equation}
  \tag{Cartesian to bit position}
  bitpos = y * W + x
\end{equation}
```

Alternatively, we can deduce the cartesian coordinates from the bit position. The following formula is the direct inverse of the above:

```math
\begin{equation}
  \tag{Bit position to cartesian}
    \left \{
    \begin{array}{l l l}
      x  & = & bitpos & \mod & W \\
      y  & = & bitpos & \div & W
    \end{array}
    \right .
\end{equation}
```

At this point we know all the necessary conversions from bit position to (x,y) coordinates. We can now begin to write our engine methods.
