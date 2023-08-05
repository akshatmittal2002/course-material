;recursive quick sort
(defun quick-sort (arr left right)
	(if (>= left right)
		() ;if left >= right -> Do Nothing
		(let ((n-pair (partition arr left right))) ;Else find partition index
			(quick-sort arr left (car n-pair)) ;Sort left partition
			(quick-sort arr (cdr n-pair) right) ;Sort right partition
			;car excess first ptr while cdr excess second ptr of memory construct n-pair
		)
	)
)

;partition function to divide array according to pivot
(defun partition (arr left right)
	(let ((pivot (aref arr left)) (curr left)) ;pivot = arr[left]; curr = left
 		(loop while (<= left right) do ;while left <= right
  			(cond
    			((< pivot (aref arr left)) ;if pivot < arr[left]
     				(swap arr left right) ;swap arr[left] and arr[right]
				 	(decf right) ;right--
				)
    			((> pivot (aref arr left)) ;else if pivot > arr[left]
     				(swap arr curr left) ;swap arr[curr] and arr[left]
				 	(incf curr) ;curr++
				 	(incf left) ;left++
				)
    			(t ;else
     				(incf left) ;left++
				)
			)
		)
		(decf curr) ;curr--
    	(cons curr left) ;return memory construct with two values - curr and left
		;last expression evaluated is return value
	)
)

;swap two elements of array
(defun swap (arr i j)
	(let ((tmp (aref arr i))) ;tmp = arr[i]
		(setf (aref arr i) (aref arr j)) ;arr[i] = arr[j]
		(setf (aref arr j) tmp) ;arr[j] = tmp
	)
)

;main function
;read size of array
(format t"Enter Size of Array: ")
(setq n (read))

;read array
(setq arr (make-array n))
(format t"Enter Array: ")
(dotimes (i n)
	(setf (aref arr i) (read))
)

;call quick sort function
(quick-sort arr 0 (- n 1))

;print sorted array
(format t"Sorted Array: ")
(dotimes (i n)
	(format t"~D "(aref arr i))
)
(write-line "")