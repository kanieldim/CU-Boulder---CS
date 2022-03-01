# valueIterationAgents.py
# -----------------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


# valueIterationAgents.py
# -----------------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).

import mdp, util


from learningAgents import ValueEstimationAgent
import collections

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*
        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.
          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0
        self.runValueIteration()

    def runValueIteration(self):
        # Write value iteration code here
        "*** YOUR CODE HERE ***"

        # for loop with self.iterations
        for i in range(self.iterations):

            # Use the "batch" version of value iteration where each vector Vk is
            # computed from a fixed vector Vk-1 (like in lecture), not the "online"
            # version where one single weight vector is updated in place.
            values_update = self.values.copy()

            # for loop with getStates...?
            for state in self.mdp.getStates():

                # if state is not terminal it won't work
                if self.mdp.isTerminal(state):
                    continue

                # Get all possible actions
                possible_actions = self.mdp.getPossibleActions(state)

                # Finding the best action using max
                best_action = max( [self.getQValue(state, action) for action in possible_actions] )
                values_update[state] = best_action

            self.values = values_update

    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        """
          Compute the Q-value of action in state from the
          value function stored in self.values.
        """

        "*** YOUR CODE HERE ***"

        """
            - returns the Q-value of the (state, action) pair given by the value function given by self.values
            - Q-values are numbers in square quarters
            -
        """

        q_value = 0
        transition_states_probs = self.mdp.getTransitionStatesAndProbs(state, action)

        for s, probability_T in transition_states_probs:

            # Use self.discount
            # Use getReward
            # Use getValue...?

            q_value += probability_T * (self.getValue(s) * self.discount + self.mdp.getReward(state, action, s))

        # return q_value
        return q_value

    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.
          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"

        """
            - Computes the best action according to the value function given by self.values.
            - You should return the synthesized policy πk+1.

            - Hint: You may optionally use the util.Counter class in util.py, which is a dictionary
              with a default value of zero. However, be careful with argMax: the actual argmax
              you want may be a key not in the counter!
        """

        # Use util.counter
        # Use argMax()

        best_action = util.Counter()
        possible_actions = self.mdp.getPossibleActions(state)

        for temp in possible_actions:

            # Use getQValue..?

            best_action[temp] = self.getQValue(state, temp)

        #return best action
        return best_action.argMax()


    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)

class AsynchronousValueIterationAgent(ValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*
        An AsynchronousValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs cyclic value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 1000):
        """
          Your cyclic value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy. Each iteration
          updates the value of only one state, which cycles through
          the states list. If the chosen state is terminal, nothing
          happens in that iteration.
          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state)
              mdp.isTerminal(state)
        """
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"\

        for index in range(self.iterations):

            get_states = self.mdp.getStates()
            each_state = index % len(get_states)

            state = get_states[each_state]

            # if state is not terminal it won't work
            if self.mdp.isTerminal(state):
                continue

            # Get all possible actions
            possible_actions = self.mdp.getPossibleActions(state)

            # Finding the best action using max
            best_action = max( [self.getQValue(state,action) for action in possible_actions])
            self.values[state] = best_action






class PrioritizedSweepingValueIterationAgent(AsynchronousValueIterationAgent):
    """
        * Please read learningAgents.py before reading this.*
        A PrioritizedSweepingValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs prioritized sweeping value iteration
        for a given number of iterations using the supplied parameters.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100, theta = 1e-5):
        """
          Your prioritized sweeping value iteration agent should take an mdp on
          construction, run the indicated number of iterations,
          and then act according to the resulting policy.
        """
        self.theta = theta
        ValueIterationAgent.__init__(self, mdp, discount, iterations)

    def runValueIteration(self):
        "*** YOUR CODE HERE ***"
