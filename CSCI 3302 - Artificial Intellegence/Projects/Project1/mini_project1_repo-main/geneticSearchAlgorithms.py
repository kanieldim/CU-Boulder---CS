from makeRandomExpressions import generate_random_expr
from fitnessAndValidityFunctions import is_viable_expr, compute_fitness
from random import choices 
import math 
from crossOverOperators import random_expression_mutation, random_subtree_crossover
from geneticAlgParams import GAParams
from matplotlib import pyplot as plt 

class GASolver: 
    def __init__(self, params, lst_of_identifiers, n):
        # Parameters for GA: see geneticAlgParams
        # Also includes test data for regression and checking validity
        self.params = params
        # The population size 
        self.N = n
        # Store the actual population (you can use other data structures if you wish)
        self.pop = []
        # A list of identifiers for the expressions
        self.identifiers = lst_of_identifiers
        # Maintain statistics on best fitness in each generation
        self.population_stats = []
        # Store best solution so far across all generations
        self.best_solution_so_far = None
        # Store the best fitness so far across all generations
        self.best_fitness_so_far = -float('inf')

    # Please add whatever helper functions you wish.

    # TODO: Implement the genetic algorithm as described in the
    # project instructions.
    # This function need not return anything. However, it should
    # update the fields best_solution_so_far, best_fitness_so_far and
    # population_stats
    
    def run_ga_iterations(self, n_iter=1000):
        
        # YOUR CODE HERE
        
        # self.N denotes the population size. Your population must have N expressions.        
        # Iterate until you have self.N viable expressions in your population
        while len(self.pop) != self.N:
            
            # Generate a expr using the function generate_random_expr (see description above). You can use self.params.depth for your 
            # expressions or hardcode a "reasonable" value such as "3" for depth.
            # generate_random_expr(depth, lst_of_identifiers, params)
            random_expr = generate_random_expr(self.params.depth,self.identifiers,self.params)
            
            # Check if the expr generated is "viable" using the function is_viable_expr
            # is_viable_expr(fun_expr, lst_of_identifiers, params)
            viable = is_viable_expr(random_expr, self.identifiers, self.params)
            
            # If an expression is not viable, do not add it to the population.
            if viable:
                
                self.pop.append(random_expr)
                
        
        fitness_result = []
        weight_result = []
        
        for pop in self.pop:
            
            # compute_fitness(fun_expr, lst_of_identifiers, params)
            fitness_score = compute_fitness(pop, self.identifiers, self.params)
            fitness_result.append(fitness_score)
            
            weight_result.append(math.exp(fitness_score / self.params.temperature))
          
        
        dict = {}
        
        for i in range(len(self.pop)):
            dict[self.pop[i]] = fitness_result[i]
        
        # This fraction can be used to select k as (elitism_fraction * self.N). In this case, the top 20% of the population will continue to 
        # live for one more generation.
        k = self.params.elitism_fraction * self.N
        
        # TODO: Elitism
        # Sort the current population by descending order fitness and choose top-k elites.
        sorted(dict,key=dict.get,reverse = True)
        top_k = list(dict.keys())
        top_k = top_k[:int(k)]
            
        next_gen = top_k
        
        # TODO: Implement Mutation/Crossover
        # Gerate the process below until we generate N-k expressions
        while len(next_gen) != self.N:
            
            # Select two expressions e1 and e2 from the current population with the probability of selecting an element proportional to  
            # 𝑒−fitness/temperature . We have a parameter params.temperature that you can use. Unlike simulated annealing, the temperature 
            # does not change.
            e1 = choices(self.pop, weights = weight_result , k = 1)
            e2 = choices(self.pop, weights = weight_result, k = 1)
            e1 = e1[0]
            e2 = e2[0]
            
            # Crossover e1 and e2 using the method provided for this purpose: random_subtree_crossover. Use copy=True and you will get a new 
            # pair of expressions e1_cross and e2_cross as a result.
            # random_subtree_crossover(e1, e2, copy = True)
            e1_cross, e2_cross = random_subtree_crossover(e1, e2, copy = True)
            
            # Mutate e1_cross and e2_cross separately. Use the method provided for this purpose: random_expression_mutation
            # random_expression_mutation(e_orig, lst_of_identifiers, params, copy=True)
            e1_cross = random_expression_mutation(e1_cross, self.identifiers, self.params, copy=True)
            e2_cross = random_expression_mutation(e2_cross, self.identifiers, self.params, copy=True)
            
            # Check whether they are viable using the method is_viable_expr.
            # is_viable_expr(fun_expr, lst_of_identifiers, params)
            e1_viable = is_viable_expr(e1_cross, self.identifiers, self.params)
            e2_viable = is_viable_expr(e2_cross, self.identifiers, self.params)
            
            # If yes, add the viable ones to the result, otherwise reject any expression that is not viable.
            if e1_viable:
                next_gen.append(e1_cross)
            if e2_viable:
                next_gen.append(e2_cross)

        
        # TODO: Next Generation Population
        # We need to maintain the best solution so far. Make sure to update these fields: best_solution_so_far and best_fitness_so_far.
        for i in next_gen:
            
            # compute_fitness(fun_expr, lst_of_identifiers, params)
            fitness_score = compute_fitness(i,self.identifiers,self.params)
            
            if fitness_score > self.best_fitness_so_far:
                self.best_fitness_so_far = fitness_score
                self.best_solution_so_far = i
                
            # We have provided a field called population_stats. You should append the best fitness at each iteration to generate a plot at
            # the end that tracks how fitness changes across iterations.
            self.population_stats.append(self.best_fitness_so_far)

## Function: curve_fit_using_genetic_algorithms
# Run curvefitting using given parameters and return best result, best fitness and population statistics.
# DO NOT MODIFY
def curve_fit_using_genetic_algorithm(params, lst_of_identifiers, pop_size, num_iters):
    solver = GASolver(params, lst_of_identifiers, pop_size)
    solver.run_ga_iterations(num_iters)
    return (solver.best_solution_so_far, solver.best_fitness_so_far, solver.population_stats)


# Run test on a toy problem.
if __name__ == '__main__':
    params = GAParams()
    params.regression_training_data = [
       ([-2.0 + 0.02*j], 5.0 * math.cos(-2.0 + 0.02*j) - math.sin((-2.0 + 0.02*j)/10.0)) for j in range(201)
    ]
    params.test_points = list([ [-4.0 + 0.02 * j] for j in range(401)])
    solver = GASolver(params,['x'],500)
    solver.run_ga_iterations(100)
    print('Done!')
    print(f'Best solution found: {solver.best_solution_so_far.simplify()}, fitness = {solver.best_fitness_so_far}')
    stats = solver.population_stats
    niters = len(stats)
    plt.plot(range(niters), [st[0] for st in stats] , 'b-')
    plt.show()



