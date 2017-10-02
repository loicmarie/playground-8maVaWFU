# II.1 Single cell operations

We will now see how to:
* get the value of a cell
* set the value of a cell

**Rappel**: dans ce tutorial (qui est en C++), le type `Bitboard` a été défini comme un entier non signé de 64bits (correspondant au type `uint64_t`)

# Cells and positions

We have said that a position is of type `Bitboard`. So how is defined a cell ?

Response is... a Bitboard ! Yes, that's pretty confusing.

> _I don't get the difference ?_

In fact a bitboard representing a cell is a sequence with only **1 bit at 1** and **the other at 0**. This type of binary vector is often used in different computing domains and is called "**one-hot encoding**".

!(Cell)[img/cell.png]

# Get a cell

```C++ runnable
int main() {
    Bitboard cell;
}
```
