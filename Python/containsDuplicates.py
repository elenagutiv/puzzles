# Given an array of integers, find if the array contains any duplicates.
# Your function should return true if any value appears at least twice in the array, and it should return false if every element is distinct.

class Solution(object):

	A = [1,2,3,4]

# Time Complexity: O(n)
# Space Complexity: O(n)
# ht = {1:0, 2:1, 3:2, 1:X}
# ht = {A[i]:i}
	def containsDuplicates(A):
		ht = dict()
		for i in range(len(A)):
			if A[i] in ht:
				return True
			ht[A[i]] = i
		return False

	print(containsDuplicates(A))
