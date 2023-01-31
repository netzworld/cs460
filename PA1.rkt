#lang mystery-languages/arithmetic
; N. Randazzo & M. Vitullo PA1

; Arithmetic Writeup
; +, -, *, /: L1 and L3 do integer addition, L2 adds a floating point.
; Divide by zero: L1 and L3 return a failure, L2 defines it as +infinity with a floating point
; All of the equality and comparison operations are the same, even with variables

; === ALL TEST CASES ===

; Test 1: Basic arithmetic

;     *Test 1a: Addition Operator
(TEST (+ 1 2) 3 3.0 3)

;     *Test 1b: Subtraction Operator
(TEST (- 2 1) 1 1.0 1)

;     *Test 1c: Muliplication Operator with 2 integers
(TEST ( * 3 3) 9 9.0 9)

;     *Test 1d: Multiplication Operator with 1 integer and 1 float
(TEST (* 3.0 3) 9 9.0 9.0)

;     *Test 1e: Division Operator with 2 integers
(TEST (/ 90 10) 9 9.0 9)

;     *Test 1f: Division Operator with 1 integer and 1 float
(TEST (/ 90.0 10) 9 9.0 9.0)

;     *Test 1g: Dividing by Zero
(TEST (/ 1 0) failure +inf.0 failure)

; Test 2: Equality Comparisons
(TEST (< 1 2) #t #t #t)
(TEST (<= 3 900) #t #t #t)
(TEST (> 55 23) #t #t #t)
(TEST (>= 20 22) #f #f #f)
(TEST (= 2000 2000) #t #t #t)
(TEST (<> 80 80) #f #f #f)

; Test 3: Variable Declaration
(defvar x 1)
(TEST x 1 1 1)

; Test 4: Variable Operations
(defvar a 20)

;     *Test 4a: Adding an integer to a variable 
(TEST (+ a 2) 22 22.0 22)

;     *Test 4b: Adding a float to a variable
(TEST (+ a 2.0) 22 22.0 22.0)

;     *Test 4c: Subtracting an integer from a variable 
(TEST (- a 4) 16 16.0 16)

;     *Test 4d: Subtracting a float from a variable
(TEST (- a 4.0) 16 16.0 16.0)

;     *Test 4e: Multiplying an integer to a variable
(TEST (* a 3) 60 60.0 60)

;     *Test 4f: Multiplying a float to a variable
(TEST (* a 3.0) 60 60.0 60.0)

;     *Test 4g: Dividing an integer from a variable
(TEST (/ a 2) 10 10.0 10)

;     *Test 4h: Dividing a float from a variable
(TEST (/ a 2.0) 10 10.0 10.0)


; Test 5: Variable Comparisons (int - int)

;     Test 5a: Not Equal Operator
(TEST (<> a x) #t #t #t)

;     Test 5b: Less Than Operator
(TEST (< a 30) #t #t #t)
