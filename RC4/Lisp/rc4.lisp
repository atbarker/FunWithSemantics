;;;define a global state for our algorithm
(defvar rc4-i 0)
(defvar rc4-j 0)
(defvar state (make-array '(256) :element-type '(unsigned-byte 8)))
(defun initialize ()
    ;;(interactive)
    (setf rc4-i 0)
    (setf rc4-j 0)
    (let (i)
    (dotimes (i 256)
            (setf (aref state i) i))))

;;;Simple variable swap function
(defun swap (i j)
    (let ((temp (aref state i)))
        (setf (aref state i) (aref state j))
        (setf (aref state j) temp)))

;;;RC4 key scheduling algorithm
(defun ksa (key)
    (let ((j 0) i)
        (dotimes (i 256 state)
            (setf j (mod (+ j
                (aref state i)
                (aref key (mod i (length key)))) 256))
            (swap i j))))

;;;PRGA for rc4
(defun prga ()
    (setf rc4-i (mod (+ 1 rc4-i) 256))
    (setf rc4-j (mod (+ rc4-j (aref state rc4-i)) 256))
    (swap (aref state rc4-i) (aref state rc4-j))
    (aref state (mod (+ (aref state rc4-i)
                      (aref state rc4-j)) 256)))

;;;encrypt or decrypt some text
(defun encdec (data cipher key len)
    (initialize)
    (ksa key)
    (let (c)
    (loop for c from 0 to len do 
        (setf (aref cipher c) (logxor (aref data c) (prga))))))

;;;Read in a file
(defun file-get-contents (filename)
    (with-open-file (stream filename)
        (let ((contents (make-string (file-length stream))))
            (read-sequence contents stream)
            contents)))

(defun string-bytes (in)

    (map '(simple-array (unsigned-byte 8) (*)) 'char-code in))

(defvar key (string-bytes (file-get-contents "key.txt")))
(defvar data (string-bytes (file-get-contents "data.txt")))
(defvar len (length data))
(defvar cipher (make-array (length data) :element-type '(unsigned-byte 8)))
(defvar unenc (make-array (length data) :element-type '(unsigned-byte 8)))
(time (encdec data cipher key (- len 1)))
;;;(print data)
;;;(print cipher)
;;;(encdec data cipher key)
;;;(print cipher)
;;;(encdec cipher unenc key)
;;;(print unenc)
