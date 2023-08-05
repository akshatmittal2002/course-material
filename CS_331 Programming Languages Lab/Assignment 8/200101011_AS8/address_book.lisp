;Search Address Book
(defun search-book ()
	(format t"Enter Name to search: ")
	(setf name (read-line))
	(with-open-file (file "address_book.txt"
		:if-does-not-exist :create)
		(setq found 0)
		(loop for entry = (read-line file nil)
			while entry do
			(setq start 0)
			(setq end 0)
			(loop while (char/= (char entry end) #\,) do (incf end))
			(setf tmp (subseq entry start end))
			(when (string-equal name tmp)
				(setq found 1)
				(incf end)
				(setq start end)
				(loop while (char/= (char entry end) #\,) do (incf end))
				(setf tmp (subseq entry start end))
				(format t"Phone: ~A~%" tmp)
				(incf end)
				(setq start end)
				(setf tmp (subseq entry start))
				(format t"Email: ~A~%" tmp)
			)
		)
		(if (= found 0) (write-line "Not Found!"))
	)
)

;Insert into Address Book
(defun insert-book ()
	(format t"Enter Name: ")
	(setf name (read-line))
	(format t"Enter Phone Number: ")
	(setf phone (read-line))
	(format t"Enter Email Address: ")
	(setf email (read-line))
	(with-open-file (file "address_book.txt"
		:direction :output
		:if-exists :append
		:if-does-not-exist :create)
		(format file"~A,~A,~A~%" name phone email)
	)
)

;Print Address Book
(defun print-book ()
	(with-open-file (file "address_book.txt"
		:if-does-not-exist :create)
		(loop for entry = (read-line file nil)
			while entry do (format t"~A~%" entry)
		)
	)
)

;main function
(write-line "Use the following codes to operate Address Book:")
(write-line "1: Insert New Entry")
(write-line "2: Search By Name")
(write-line "3: Print Address Book")
(write-line "4: Exit")

(setq code 0)
(format t"Enter Code: ")
(loop while (/= (setq code (read)) 4) do
	(cond
		((= code 1) (insert-book))
		((= code 2) (search-book))
		((= code 3) (print-book))
		(t (write-line "Invalid Code"))
	)
	(format t"Enter Code: ")
)