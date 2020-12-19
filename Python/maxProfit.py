# Say you have an array for which the ith element is the price of a given stock on day i.
# If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
# Note that you cannot sell a stock before you buy one.
class Solution(object):
	A = [5,4,3,2,1]

	
	def maxProfit(A):
		(peak,valley) = (A[0], A[0])
		i = 0
		maxProfit = 0

		while(i < len(A) -1):
			while (i < len(A) - 1) and (A[i] >= A[i+1]): # climb down
				i = i + 1
			valley = A[i]
			while(i < len(A) - 1) and (A[i] <= A[i+1]): # climb up
				i = i + 1
			peak = A[i]
			if maxProfit < (peak - valley): # update max profit
				maxProfit = peak - valley
		return maxProfit

	print(maxProfit(A))