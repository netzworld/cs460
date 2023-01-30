#lang mystery-languages/conditionals
; N. Randazzo & M. Vitullo PA1

;Conditional Writeup
; IF
; AND: L1 requires #t and #f, while L2 and L3 work with both constant numbers (0/1) and #t/#f.
; L2 also returns the larger of the two numbers if they are both positive, and the smaller of the two if they are both negative.

; === ALL TEST CASES ===
; Test1: IF with Constants

; Test1-E: IF with Variables


; Test2: AND with Constants
(TEST (and #t #t) #t #t #t)

;   Test2-A:
(TEST (and #f #t) #f #f #f)

;    Test2-B:
(TEST (and 0 1) #f #f #f)

;     Test2-C:
(TEST (and 1 1) #t #t #t)

; Test2-E: AND with Variables
(defvar a 1)
(defvar b -43)
(defvar t #t)
(defvar f #f)
(defvar x 0)
(TEST (and a b) #t #t #t) ; L2 returns the larger number (42 in this case)
(TEST (and t f) #f #f #f)

(and a b) ; L2 returns the smallest number if both negative.
; L2 returned -43 when (and -1 -43) was inputted. Strange.

; Test3: OR
(TEST (or 0 1) #t 1 #t) ;L1 does not accept numerical boolean values and throws errors
(TEST (or 1 1) #t 1 #t) ;L1 does not accept numerical boolean values and throws errors.
(TEST (or #t #t) #t #t #t)
(TEST (or #f #f) #f #f #f)
(TEST (or #f #t) #t #t #t)
