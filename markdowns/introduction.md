# Introduction



# A word about simulation

## Why should I care about bitboards ?

When making some AI, Bitboards come to be a **method for state representation** using the **BitArray data structure**. No no, stay here, I will explain. But before that, let's make a brief introduction on agents and environments.

## Agent and Environment in AI

When creating some artificial intelligence (AI), we have to carry about two things:
* The **environment**: where the agent will act and evolve. it defines the relation between a state, an action of the agent, and the resulting next state.
* The **agent**: anything that can perceive its environment through sensors and acts upon that

![Agent and environment](http://cs-alb-pc3.massey.ac.nz/notes/59302/fig02.01.gif)

> _That's cool ! Why are we talking about that_ ?

The reason is: with bitboards we're not gonna make an agent, but an **efficient environment or simulation of the environment** in order to power up our simulation-based algorithms.

## Importance of simulations

Creating an AI means creating an agent that is able to act reasonably in the environment. In most of the currently existing intelligent algorithms, **we need to simulate the environment response** to an agent action.

**The more states we simulate, the more accurate will be our agent**.

> _OK, so at the end of the tutorial I could get an AI better than the world chess champion ?_

Don't be on a rush !

No, I really don't think so, for two reasons:
* Improving the number of states simulations is very important, **but not as many as improving the algorithm**. This tutorial will be useful only when you'll have an efficient algorithm, and you think that only the simulations could be improved.
* Bitboards cannot be implemented without a lot of condition, and we will see later that it is not always the response to every problem. However, it remains a powerful tool that you should know about !
