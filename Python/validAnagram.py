# Given two strings s and t , write a function to determine if t is an anagram of s.

# Time Complexity: O(n) since we have to traverse the word (of length n each) twice
# Space Complexity: O(1) since the size of the hash table is at most the size of the alphabet!!
# Key idea: Mantain one hashtable (instead of two)
class Solution(object):
	s = "anagram"
	t = "nagaram"

	def validAnagram(s,t):
		if len(s) != len(t):
			return False
		table = dict()
		# table = {letter: # occurrences}
		for i in range(len(s)): # len(s) = len(st)
			if s[i] in table:
				table[s[i]] = table[s[i]] + 1
			else:
				table[s[i]] = 1
		for i in range(len(t)):
			if t[i] in table:
				table[t[i]] = table[t[i]] - 1
			else:
				return False
			if table[t[i]] < 0:
				return False
		
		return True

	print(validAnagram(s,t))



