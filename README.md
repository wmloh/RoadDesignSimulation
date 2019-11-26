# Road Design Simulation

*Last updated on November 25, 2019*

### Purpose

Unlike supervised and unsupervised learning, the potential of reinforcement learning has yet to be recognized in industries. This can be attributed to the enormous amount of resources needed to be channeled into the project. Reinforcement learning environment requires more than datasets; it requires extensive software development knowledge, massive compute power as well as statistical analysis of the environment to be studied.



This project aims to prototype an application of reinforcement learning beyond the land of gaming AI and toy datasets in hopes to demonstrate the potential of data science in decision-making.



### Development Process

- [x] [Phase 1](#phase-1)
- [x] [Phase 2](#phase-2)
- [ ] [Phase 3](#phase-3)

#### Phase 1

##### Setting Up Environment

An environment that is robust and scalable is constructed that can handle agents and search algorithms. It should provide an abstracted and efficient interface for the agent to interface with. The environment should be available as a mathematical representation (i.e. `numpy` arrays) for further integration with other functionality.

Metrics and constants should also be defined here.



#### Phase 2

##### Creating Intelligent Agent

The agent must have access to realistic amounts of information in the environment and equipped with efficient algorithms that can make highly optimized decisions to maximum certain rewards.



#### Phase 3

##### Deep Learning Integration

This phase should replace the role of  human to design the road systems. While this can be solved with backtracking, it is clearly not scalable for a generalized road system problem. 

The proposed solution is the use of Monte-Carlo Tree Search (MCTS) and an actor-critic model-free deep reinforcement learning algorithm. However, there will be considerations for a model-based agent if it proves to have greater value.

This design is heavily inspired by Google Deepmind's AlphaGo research papers.

