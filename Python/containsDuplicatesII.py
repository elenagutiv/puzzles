# Given an array of integers and an integer k,
# find out whether there are two distinct indices i and j in the array such that nums[i] = nums[j] and the absolute difference between i and j is at most k.

class Solution(object):

	A = [1,2,3,1,2,3]
	k = 2

# Time Complexity: O(n)
# Space Complexity: O(n)
# ht = {1:0, 2:1, 3:2, 4:3, 1:}
# ht = {A[i]: i}
	def containsDuplicatesII(A,k):
		ht = dict()
		for i in range(len(A)):
			if (A[i] in ht) and (i - ht.get(A[i])) <= k:
				return True
			else: # A[i] not in ht or i' - i > k
				ht[A[i]] = i
		return False

	# print(containsDuplicatesII(A,k))

# Optimized version since len(ht) <= k always.
# Time Complexity: O(n)
# Space Complexity: O(min(n,k)) (it will be n if n < k)
	def containsDuplicatesIIOptimized(A,k):
		ht = dict()
		for i in range(len(A)):
			if (A[i] in ht):
				return True
			ht[A[i]] = i
			if len(ht) > k: # A[i] not in ht and len(ht) >= k
				del ht[A[i-k]]
		return False

	print(containsDuplicatesIIOptimized(A,k))




