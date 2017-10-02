# Introduction

Bitboard is a **method for representing states** in game engine, and particularly in **2D board games**. 

It uses the **bit array data structure** and transform all usual searching/testing methods into **binary** and **logical** operations.

It allows to:
1. use only one bit where common data structure use one byte
2. perform high efficiency operations

If you already know why you are here, you can go to the first section and see a short example of bitboard application.

Otherwise, you should probably read the next section about the importance of making a good game engine in Artificial Intelligence (AI) concern.

# A word about simulation

## Agent and Environment in AI

When creating some artificial intelligence (AI), we have to carry about two things:
* The **environment**: where the agent will act and evolve. it defines the relation between a state, an action of the agent, and the resulting next state.
* The **agent**: anything that can perceive its environment through sensors and acts upon that

![Agent and environment](http://cs-alb-pc3.massey.ac.nz/notes/59302/fig02.01.gif)

> _That's cool ! Why are we talking about that_ ?

The reason is: most of the algorithms need to **predict the future** (make **simulations**) to be efficient.

With bitboards we're not gonna make an agent, but an **efficient perception of the environment** in order to power up our simulation-based algorithms.

## The relative importance of simulations

Creating an AI means creating an agent that is able to act reasonably in the environment. In most of the currently existing intelligent algorithms, **we need to simulate the environment response** to an agent action.

**The more states we simulate, the more accurate will be our agent**.

> So, at the end of the tutorial I could make an AI better than the world chess champion ?_

Don't be on a rush ! For two reasons:

#### You should always improve the algorithm first

Improving the number of states simulations is very important, **but not as many as improving the algorithm**. 

This tutorial will be useful only once you have had an efficient algorithm.

#### Bitboards are not the response to everything

Bitboards cannot be implemented without a lot of condition, and is sometimes very fastidious to set up. 

However, it remains a powerful tool that you should know about !
