#lang mystery-languages/arithmetic
; N. Randazzo PA1

; Arithmetic Writeup
; +, -, *, /: L1 and L3 do integer addition, L2 adds a floating point.
; Divide by zero: L1 and L3 return a failure, L2 defines it as +infinity with a floating point
; All of the equality comparisons are the same, even with variables

; Conditionals Writeup

; === ALL TEST CASES ===
; Test1: Basic arithmetic
(TEST (+ 1 2) 3 3.0 3)
(TEST (- 2 1) 1 1.0 1)
(TEST ( * 3 3) 9 9.0 9)
(TEST (/ 90 10) 9 9.0 9)

; *Test2: Divide by Zero
(TEST (/ 1 0) failure +inf.0 failure)

; Test3: Equality Comparisons
(TEST (< 1 2) #t #t #t)
(TEST (<= 3 900) #t #t #t)
(TEST (> 55 23) #t #t #t)
(TEST (>= 20 22) #f #f #f)
(TEST (= 2000 2000) #t #t #t)
(TEST (<> 80 80) #f #f #f)

; Test4: Variable Declaration
(defvar x 1)
(TEST x 1 1 1)

; Test5: Variable Operations
(defvar a 20)
(TEST (+ a 2) 22 22.0 22)
(TEST (* a 3) 60 60.0 60)

; Test6: Variable Comparisons
(TEST (<> a x) #t #t #t)
(TEST (< a 30) #t #t #t)
