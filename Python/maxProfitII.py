# Say you have an array for which the ith element is the price of a given stock on day i.
# If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
# Note that you cannot sell a stock before you buy one.
class Solution(object):
	A = [7,1,5,3,6,4]

	# SIMPLE SOLUTION I
	def maxProfitII(A):
		(peak, valley) = (A[0], A[0])
		maxProfit = 0
		i = 0

		while i < len(A)-1:
			while (i < (len(A) - 1)) and (A[i] >= A[i+1]): # climbing down
				i = i + 1
			valley = A[i]
			while (i < (len(A) - 1)) and (A[i] <= A[i+1]): # climbing up
				i = i + 1
			peak = A[i]
			maxProfit = maxProfit + (peak - valley)
		return maxProfit

	print(maxProfitII(A))

	# SIMPLE & *CLEAN* SOLUTION II
	def maxProfitIIClean(A):

		(peak, valley) = (A[0], A[0])
		maxProfit = 0
		i = 0

		while i < len(A)-1:
			if A[i] < A[i+1]:
				maxProfit = maxProfit + (A[i+1] - A[i])
			i = i + 1
		return maxProfit
	print(maxProfitIIClean(A))