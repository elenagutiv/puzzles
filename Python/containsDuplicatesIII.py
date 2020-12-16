from sortedcontainers import SortedList

# Given an array of integers, find out whether there are two distinct indices
# i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.

class Solution(object):
	A = [1,2,3,1]
	t=0
	k=3

# ht = {A[i]:i}
# Remember, given the current element A[i] we want to find the highest element already visited that is lower or equal than A[i]
#											   			   the lowest element already visited that is greater or equal than A[i]
# Balanced Search Tree!

# Time Complexity: O(n log(min(n,k))) where n = len(A). Note that we take the min(n,k) just in case n < k
# Space Complexity: O(min(n,k))	
	def containsDuplicatesIII(A,k,t):
		
		bst = SortedList()
		def floor(x, bst):
			le = bst.bisect_right(x)-1 # bisect_right(value) returns an index to insert value in the sorted list. IP, if value exists in the list,
									   # bisect_right returns the index just on the right
									   # Time complexity: O(log(n)) where n is the # of elements of bst
			if le >= 0:
				return bst[le]
			else: 
				None
				
		def ceiling(x,bst):
			ge = bst.bisect_right(x)
			if ge < len(bst):
				return bst[ge]
			else:
				None

		for i in range(len(A)):
			if ((floor(A[i], bst) != None) and (A[i] - floor(A[i], bst) <= t)) or ((ceiling(A[i], bst) != None) and (ceiling(A[i], bst) - A[i] <= t)):
				return True
			bst.add(A[i]) # Time Complexity: O(log(n))
			if len(bst) > k: 
				bst.remove(A[i-k]) # Time Complexity: O(log(n))
		return False

	print(containsDuplicatesIII(A,k,t))


