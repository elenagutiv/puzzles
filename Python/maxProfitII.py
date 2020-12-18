# Say you have an array for which the ith element is the price of a given stock on day i.
# If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
# Note that you cannot sell a stock before you buy one.
class Solution(object):
	A = [7,1,5,3,6,4]

	# Time complexity: O(n) as only one pass is needed
	# Space complexity O(1) as we only need to store 3 variables: im, jm and maxProfit
	def maxProfit(A):
		(i,j) = (len(A)-2, len(A)-1)
		(totalProfit, prev_diff, diff) = (0, 0, -1)
		#for i,j in zip(range(len(A)), range(len(A)-1, -1, -1)):
		while i >= 0 :
			diff = A[j] - A[i]
			if diff < 0 or prev_diff > diff: # reset
				totalProfit = totalProfit + prev_diff			
				(j, i) = (i, j-1)
				prev_diff = 0
			else: #diff >= 0 and prev_diff <= diff:
				i = i-1
				prev_diff = diff
		if diff >= 0 and prev_diff <= diff:
			totalProfit = totalProfit + prev_diff	
		return totalProfit

	print(maxProfit(A))