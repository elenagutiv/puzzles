# Say you have an array for which the ith element is the price of a given stock on day i.
# If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
# Note that you cannot sell a stock before you buy one.
class Solution(object):
	A = [2,7,1,4]

	# Time complexity: O(n) as only one pass is needed
	# Space complexity O(1) as we only need to store 3 variables: im, jm and maxProfit
	def maxProfit(A):
		(i,j) = (len(A)-2, len(A)-1)
		maxProfit = 0
		#for i,j in zip(range(len(A)), range(len(A)-1, -1, -1)):
		while i >= 0 :
			diff = A[j] - A[i]
			if diff > 0:
				if maxProfit < diff:
					maxProfit = diff
					(im, jm) = (i,j)
				i = i-1
			else:
				j = j-1
				if i == j:
					i = i-1

		return maxProfit

	print(maxProfit(A))