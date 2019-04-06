# Road Design Simulation

*Last updated: February 6, 2019*

## Contents
- [Motivation](#motivation)
- [Classes](#classes)
- [Usage](#usage)
- [Development Process](#development-process)
	- [Phase 1](#phase-1)
	- [Phase 2](#phase-2)
	- [Phase 3](#phase-3)

## Motivation
[Agent-Based Modelling (ABM) (1)](http://www.agent-based-models.com/blog/2010/03/30/agent-based-modeling) is the intersection between empirical observations and algorithmic thinking, which ultimately aims to simulate a complex system. In this project, this modelling aims to simulate a traffic system.

1. “Agent-Based Modeling: An Introduction | Agent-Based Models.” AgentBased Models RSS, www.agent-based-models.com/blog/2010/03/30/agent-based-modeling/. 

## Classes

![Class Organization](/assets/ObjectsUML.png)

*Classes in the image are generally organized such that the classes at the bottom are more 'tangible' while the classes above are more for logical flow*

**`Tile`** is the abstract class for the building blocks of this simulation. It has x,y-coordinates as well as a pointer to its neighbours. **`Hub`**, **`Obst`** and **`Empty`** are concrete derived classes of `Tile`.

To organize classes that can hold cars, an abstract derived class of `Tile` is created: **`Traversable`**. It has additional fields to keep track of cars currently on it. There are also methods (member functions) that coordinates the transfer of cars when cars move. Two concrete derived classes of `Traversable` are: **`Road`** and **`Home`**.

**`Car`** is the main agent in this simulation. It initially begins in a `Home` object, where the path will be determined (see `PathFinder`). It can only travel on `Road`.

**`Trigger`** provides the framework for logic of motions and synchronous coordination. This class adopts a software engineering design pattern called *Observer Pattern* or *Pub-Sub* (click [here](https://sourcemaking.com/design_patterns/observer) to learn more). Its derived classes are: **`TimeStep`** and **`Waiting`**. `TimeStep` moves all `Car` stored within it in a sequential manner, until cars reaches its destination. `Waiting`, on the other hand, reads a predefined instruction (see [Usage](#usage)) and loads `Home` with `Car`, and adds pointers of `Car` to `TimeStep` when it is time for a `Car` to start moving.

**`Simulation`** is the core class that ties everything above together. It owns and stores instances of these classes and connects them in a logical flow.

**`CommandLoop`** is a command-line interface to control the direction of the `Simulation`. This is the entry point of the simulation, i.e. *main.cc* should only call methods of this class.

**`Map`** assists `Simulation` in loading data from files. Subsequently, **`CSVParser`** assists `Map` in reading and parsing CSV files.

**`PathFinder`** is an implementation of the [A* Search Algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm), which is called to find a path for `Car`. **`OpenElement`** is an encapsulation of important data for `PathFinder`, simply for convenience and time efficiency.

## Usage

### Files
There are three files that needs to be loaded into the `/datasets` directory:

- map.txt
- order.csv
- profile.txt

##### Map
This is the file that designs the layout of the Ground.
It must be in a rectangular format containing only:

- % - obstacle
- \+ - road
- H - home
- h - hub
- &nbsp; &nbsp; - empty (whitespace)

##### Order
This file specifies where and when a car departs, and where is its destination.
There are 5 columns in this file, all separated by comma.

- Column 0 - timestep to depart
- Column 1 - x-coordinate of origin
- Column 2 - y-coordinate of origin
- Column 3 - x-coordinate of destination
- Column 4 - y-coordinate of destination

##### Profile
The contents of this file have to correspond to the contents of the Map file.
Each character in this file specifies a certain characteristics of Tiles in its corresponding character in the Map file.

- \+ - maximum capacity of cars the Road can handle
- H - (currently doesn't mean anything but in later version, this value would mean average cars departing from this Home, and cars will be generated based on Poisson distribution)

For all other symbols, the characters should be defaulted to 0 by convention.

### Main File
Using the API for basic usage simply requires a *main.cc* with:
```
#include "commandLoop.h"
int main() {
	CommandLoop cmd;
	cmd.loadGuide("guide.txt");
	cmd.loadLegend("legend.txt");
	cmd.loadFiles("./datasets/map1.txt", "./datasets/profile1.txt", "./datasets/order1.csv");
	cmd.run();
}
```

### Command Line Interface
The commands for the interface are:

* `help`      - shows all commands
* `legend`    - shows all legends when previewing the tiles
* `show`      - shows all tiles
* `init`      - begins simulation
* `setStream` - changes output stream (either `cout` or `file NAME_OF_FILE`)
* `quit (q)`  - quits program
* `dev`       - enters development mode

The commands inside the development mode are:

* `show`                   - shows all tiles
* `get timestep`           - get description of cars currently in TimeStep
* `get waiting`            - get description of cars currently in Waiting
* `get car <X> <Y>`        - get path of car
* `get neighbours <X> <Y>` - get neighbour coordinates of Tile at <X>,<Y>
* `stepRun`                - runs one round/step of simulation
  * `stop`         - stops stepRun
  * `get timestep` - get description of cars currently in TimeStep
  * `get waiting`  - get description of cars currently in Waiting
  * `ENTER KEY`    - takes another step of stepRun
* `quit (q)`               - exits development mode (goes back to the usual CLI)

## Development Process

![Process Design](/assets/ProcessDesign.png)

Progress as of *January 27, 2019*:

 - [x] Phase 1
 - [x] Phase 2
 - [ ] Phase 3

### Phase 1
#### Setting Up Environment
An environment that is robust has to be made to handle agents and deep learning models. It should integrate well with agents and provide a highly abstract yet efficient interface for the deep learning model to run and train.

Metrics and constants should also be defined well here, while still giving flexibility to redefine them.

### Phase 2
#### Creating Intelligent Agent
The agent must have access to realistic amounts of information in the environment. With that, they must possess powerful algorithms to make decision processes to optimize the challenges in the environment.

*As of January 27, 2019*, there are no plans to load a machine learning model into the decision process of the agent, although there could be in future works.

### Phase 3
#### Deep Learning Model
Entering this phase would redefine the objective of this project, from simulating agents in an environment to engineering a design to optimize agents in an environment.

~~*As of January 27, 2019*, the current plan of attack is using a combination of [Convolutional Neural Network](http://cs231n.github.io/convolutional-networks/) and [Long Short Term Memory (LSTM) networks](http://colah.github.io/posts/2015-08-Understanding-LSTMs/).~~

*As of February 6, 2019*, work will begin on using [U-Net](https://arxiv.org/pdf/1505.04597.pdf) for the deep learning model.
