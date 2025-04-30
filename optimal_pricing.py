import numpy as np
from sympy import symbols, solve
import pandas as pd
from tqdm import tqdm



def basic_pricing_strategy(k, customer_valuations):
    n = len(customer_valuations)
        
    fixed_price = 1-(k/n)
    #print(f'Fixed price is: {fixed_price}')
    t = k
    
    total_revenue = 0
    
    for valuation in customer_valuations:  
        if fixed_price<=valuation:
            total_revenue += fixed_price
            t -= 1
        
        if t == 0: #All tickets sold
            break
    
    return total_revenue


def fill_table(k, n):
    #Store the optimal prices in a table while calculating them and then use the table to lookup when running experiment
    #Start at t=0, i=n
    
    price_table = np.zeros((n, k+1))
    expectation_table = np.zeros((n, k+1))
    
    for i in tqdm(reversed(range(n))):
        for t in range(0, k+1):
            if (t==0):
                price_table[i, t] = 0
                expectation_table[i, t] = 0
            elif (n-i <= t): #More tickets left than customers --> set optimal price which is 0.5. +1 since zero indexed
                price_table[i, t] = 0.5
                expectation_table[i, t] = 0.25*t
            else: #To compute at (i,t) we need (i+1, t) and (i+1, t-1) 
                expectation_accept = expectation_table[i+1, t-1]
                expectation_reject = expectation_table[i+1, t]
                p = symbols('p')
                expr = -2*p+1+expectation_reject-expectation_accept #Derivative
                p_optimal = solve(expr)[0]
                expected_revenue = p_optimal*(1-p_optimal)+p_optimal*expectation_reject+(1-p_optimal)*expectation_accept

                price_table[i, t] = p_optimal
                expectation_table[i, t] = expected_revenue
                
    return price_table

def compute_optimal_price(i, t, n):
    #Currently at i'th customer and t tickets left. We compute the optimal price
    # print(f'Compute optimal price called with {i}, {t}, {n}')
    
    
    if(n-i <= t):
        return 0.5
    else: 
        p = symbols('p')
        expectation_accept = compute_expectation(i+1, t-1, n)
        expectation_reject = compute_expectation(i+1, t, n)
        expr = -2*p+1+expectation_reject-expectation_accept #Derivative
        p_optimal = solve(expr)[0]
        return p_optimal

def compute_expectation(i, t, n):
    # print(f'Compute expectation called with: {i}, {t}, {n}')
    if t <= 0: #No more tickets to sell
        return 0
    if (n-i <= t): #Base case, where more tickets than remaining customers
        return 0.25*t
    else:
        p = symbols('p')
        expectation_accept = compute_expectation(i+1, t-1, n)
        expectation_reject = compute_expectation(i+1, t, n)

        expr = -2*p+1+expectation_reject-expectation_accept #Derivative
        p_optimal = solve(expr)[0]
        expected_revenue = p_optimal*(1-p_optimal)+p_optimal*expectation_reject+(1-p_optimal)*expectation_accept
        return expected_revenue
 
def optimal_pricing_strategy_old(k, customer_valuations): 
    n = len(customer_valuations)
    t = k
    total_revenue = 0
    
    for i, valuation in enumerate(customer_valuations):
        #print(f'At i: {i} and tickets left: {t}')
        optimal_price = compute_optimal_price(i, t, n)
        #print(f'Optimal price at {i} is: {optimal_price}')
        if optimal_price<=valuation:
            total_revenue += optimal_price
            t -= 1
        
        if t == 0: #All tickets sold
            break
    
    return total_revenue

def optimal_pricing_strategy(k, customer_valuations, price_table):
    n = len(customer_valuations)
    t = k
    total_revenue = 0
    
    for i, valuation in enumerate(customer_valuations):
        reverse_i = n - i
        optimal_price = price_table[-reverse_i, t] #(25, 10)
        if optimal_price<=valuation:
            total_revenue += optimal_price
            t -= 1
    
        if t == 0: #All tickets sold
            break
        
    return total_revenue


def experiment():
    #Assuming k<n/2
    
    price_table = fill_table(k=500, n=1000)

    k_array = [10, 15, 25, 40, 60, 85, 105, 140, 180, 225, 275, 325, 375, 425, 475, 499]
    n_array = [21, 30, 45, 70, 100, 135, 200, 270, 350, 400, 500, 600, 700, 800, 900, 999]


    results = []

    for n in n_array:
        print(f'Current n: {n}')
        for k in k_array:
            if(k >= n/2): #Assumption in exercise
                continue
            print(f'Current k: {k}')
            basic_prices_revenue = []
            optimal_prices_revenue = []
            for i in range(1000):
                customer_valuations = np.random.uniform(0, 1, size=n)
                basic_strategy_revenue = basic_pricing_strategy(k, customer_valuations)
                optimal_strategy_revenue = optimal_pricing_strategy(k, customer_valuations, price_table)
                basic_prices_revenue.append(basic_strategy_revenue)
                optimal_prices_revenue.append(optimal_strategy_revenue)
               
            basic_avg = np.mean(basic_prices_revenue)
            basic_std = np.std(basic_prices_revenue)

            optimal_avg = np.mean(optimal_prices_revenue)
            optimal_std = np.std(optimal_prices_revenue)

            results.append({
                'n': n,
                'k': k,
                'basic_strategy_avg': basic_avg,
                'basic_strategy_std': basic_std,
                'optimal_strategy_avg': optimal_avg,
                'optimal_strategy_std': optimal_std
            })


    df_results = pd.DataFrame(results)

    # Optional: save to CSV for later use
    df_results.to_csv('pricing_strategy_results.csv', index=False)



experiment()    
    
