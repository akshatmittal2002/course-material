# CS561 Assignment 2
This assignment is a combined work by:
1. Akshat Mittal (200101011, m.akshat@iitg.ac.in)
2. Dhananjai (200101029, dhananjai@iitg.ac.in)

## Exercise 1: Robot localisation
- The objective of this exercise is to apply Hidden Markov Models to localization problem.
- Given a map of world and sequence of percepts and actions, we have to estimate the current position of robot and determine most likely path followed to reach that position.
- The corresponding code can be found in `Exercise_1.ipynb` file that uses `Python 3.11.8` version.
- `We assume that the robot has a correct map.`
- Prior probability is taken to be equally likely at any of the available square.
- All assumptions mentioned in the problem description are taken.

### Some Variables Used
1. `grid(X,Y)`: X x Y dimension 2-D matrix representing the world; 1 denotes free square while 0 denotes obstacle.
2. `free_squares`: All free squares of world listed as 1-D list. Total number of free squares be N.
3. `transition_matrix`: The N x N matrix representing transition probabilities.
4. `sensor_matrix`: The N x N matrix represting sensor model at time t.
- Use of all other variables is mentioned with the code.

### Our Assumptions
- We assume that at point of time, robot makes a random move to any of the neighbouring free square, since the observed path was not given.
- Similarily, at any point of time, we take a random reading for the four sensors to evaluate sensor model. `These values can also be given as input`. Basically, we first find the correct sensor reading and then with probability equal to sensor error rate, flip the values to get an observation.
- We run the HMM algorithm for some number of iterations (`by default 500`) and average out the localisation error and path accuracy values, since the observations are generated at random.