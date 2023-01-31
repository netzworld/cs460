#lang mystery-languages/conditionals
; N. Randazzo & M. Vitullo PA1

;Conditional Writeup
; IF
; AND: L1 requires #t and #f, while L2 and L3 work with both constant numbers (0/1) and #t/#f.
; L2 also returns the larger of the two numbers if they are both positive, and the smaller of the two if they are both negative.

; === ALL TEST CASES ===

; Declaring Variables:

(defvar a 1)
(defvar b -43)
(defvar t #t)
(defvar f #f)
(defvar x -4)
(defvar c 1)

; TEST 1: Boolean AND Expressions:

;     Test 1a: AND with Constants -> 2 True Constants
(TEST (and #t #t) #t #t #t)

;     Test 1b: AND with Constants -> 1 True and 1 False Constant
(TEST (and #f #t) #f #f #f)

;     *Test 1c: AND with Intger Representation of Boolean Values -> 2 True Integers
(TEST (and 1 1) "error" 1 #t) ; Language One does not accept numerical boolean values and throws an error

;     *TEST 1c: AND with Integer Representation of Boolean Values -> 1 True Integer and 1 False Integer
(TEST (and 0 1) "error" 1 #f) ; Language Two says that 1 False and 1 True is True

;     *Test 1d: Using Variables that are equivalent
(TEST (and a c) "error" 1 #t) ; Language One does not accept numerical boolean values and throws an error

;     *Test 1e: Using Variables that are different
(TEST (and a b) "error" -43 #t)

;     *TEST 1f: Using Variables with Negative Integer Values that are Different
(TEST (and b x) "error" -4 #t)

; TEST 2: Boolean OR Expressions:

;     Test 2a: OR with Constants -> 2 True Constants
(TEST (or #t #t) #t #t #t)

;     Test 2b: OR with Constants -> 1 True and 1 False Constant
(TEST (or #f #t) #t #t #t)

;     *Test 2c: OR with Numerical Boolean Value Representation -> 2 True Integers
(TEST (or 1 1) "error" 1 #t)

;     *Test 2c: OR with Numerical Boolean Value Representation -> 1 True and 1 False Integer
(TEST (or 0 1) "error" 0 #t)


; TEST 3: If-Statement Expressions:

;     3a: If True then 1 else 2
(TEST (if #t 1 2) 1 1 1)

;     3b: If true or flase then 1 else 2
(TEST (if (or #t #f) 1 2) 1 1 1)
