# Say you have an array for which the ith element is the price of a given stock on day i.
# If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
# Note that you cannot sell a stock before you buy one.

# Key idea: update minValley whenever you find a valley that is lower than the lowest you've seen
# If current price compared to the minValley (A[i] - minValley) is greater than the maxProfit seen
# update maxProfit.
# Time complexity: O(n) one pass through the list
# Space complexity: O(1) - 2 variables are needed throughout the loop
class Solution(object):
	A = [1,2,3,4,5]
	
	def maxProfit(A):
		if len(A) == 0:
			return 0
		minValley = A[0]
		maxProfit = 0
		for i in range(len(A)):
			if A[i] < minValley:		
				minValley = A[i]
			elif A[i] - minValley > maxProfit:
				maxProfit = A[i] - minValley
		return maxProfit
	print(maxProfit(A))