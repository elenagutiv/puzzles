# Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
# You may assume that each input would have exactly one solution, and you may not use the same element twice.

class Solution(object):

	A = [-2, 1, 2, 4, 7, 11]
	target = 13

# Time Complexity of O(n^2)
# Space Complexity of O(1)
	def  twoSumBruteForce(A, target):
		for i in range(len(A)):
			for j in range(len(A)-1):
				if A[i] + A[j] == target:
					print(i, j)
					return True
		return False

# Time Complexity of O(n): loop through the array just one time
# Space Complexity of O(n)

# ht = {key:value, ...}
# ht = {A[i]:i, ...} Recall: A[i]'s are all distinct
# ht = {-2:0, 1:1, 2:2, 4:3, 7:5, 11:8}
	def twoSumHashTable(A, target):
		ht = dict()
		for i in range(len(A)):
			if (target - A[i]) in ht: # k in ht checks if k is a key of ht!
				print(A[i], target - A[i])
				return True
			else:
				ht[A[i]] = i

		return False

	

# Alternative proposed by LucidProgramming: note that you cannot retrieve the index value, so it does not
# solve the problem completely
# ht = {(target - A[i]):A[i], ...}
	def twoSumHashTableB(A, target):
		ht = dict()
		for i in range(len(A)):
			if A[i] in ht:
				print(ht.get(A[i]), A[i])
				return True
			else:
				ht[target-A[i]] = A[i]
		return False
	print(twoSumHashTableB(A, target))

# Suppose that the array is **shorted**
# Time Complexity of O(N)
# Space Complexity of O(1)
	def twoSumHashTableShorted(A,target):
		i = 0
		j = len(A) - 1

		while i <= j:
			if A[i] + A[j] == target :
				print(i,j)
				return True
			elif A[i] + A[j] > target:
				j = j-1
			else: # A[i] + A[j] < target
				i = i + 1
		return False









