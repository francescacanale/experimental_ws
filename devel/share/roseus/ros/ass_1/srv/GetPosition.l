;; Auto-generated. Do not edit!


(when (boundp 'ass_1::GetPosition)
  (if (not (find-package "ASS_1"))
    (make-package "ASS_1"))
  (shadow 'GetPosition (find-package "ASS_1")))
(unless (find-package "ASS_1::GETPOSITION")
  (make-package "ASS_1::GETPOSITION"))
(unless (find-package "ASS_1::GETPOSITIONREQUEST")
  (make-package "ASS_1::GETPOSITIONREQUEST"))
(unless (find-package "ASS_1::GETPOSITIONRESPONSE")
  (make-package "ASS_1::GETPOSITIONRESPONSE"))

(in-package "ROS")





(defclass ass_1::GetPositionRequest
  :super ros::object
  :slots (_my_position_x _my_position_y ))

(defmethod ass_1::GetPositionRequest
  (:init
   (&key
    ((:my_position_x __my_position_x) 0.0)
    ((:my_position_y __my_position_y) 0.0)
    )
   (send-super :init)
   (setq _my_position_x (float __my_position_x))
   (setq _my_position_y (float __my_position_y))
   self)
  (:my_position_x
   (&optional __my_position_x)
   (if __my_position_x (setq _my_position_x __my_position_x)) _my_position_x)
  (:my_position_y
   (&optional __my_position_y)
   (if __my_position_y (setq _my_position_y __my_position_y)) _my_position_y)
  (:serialization-length
   ()
   (+
    ;; float64 _my_position_x
    8
    ;; float64 _my_position_y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _my_position_x
       (sys::poke _my_position_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _my_position_y
       (sys::poke _my_position_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _my_position_x
     (setq _my_position_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _my_position_y
     (setq _my_position_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass ass_1::GetPositionResponse
  :super ros::object
  :slots (_target_x _target_y _vel_x _vel_y ))

(defmethod ass_1::GetPositionResponse
  (:init
   (&key
    ((:target_x __target_x) 0)
    ((:target_y __target_y) 0)
    ((:vel_x __vel_x) 0)
    ((:vel_y __vel_y) 0)
    )
   (send-super :init)
   (setq _target_x (round __target_x))
   (setq _target_y (round __target_y))
   (setq _vel_x (round __vel_x))
   (setq _vel_y (round __vel_y))
   self)
  (:target_x
   (&optional __target_x)
   (if __target_x (setq _target_x __target_x)) _target_x)
  (:target_y
   (&optional __target_y)
   (if __target_y (setq _target_y __target_y)) _target_y)
  (:vel_x
   (&optional __vel_x)
   (if __vel_x (setq _vel_x __vel_x)) _vel_x)
  (:vel_y
   (&optional __vel_y)
   (if __vel_y (setq _vel_y __vel_y)) _vel_y)
  (:serialization-length
   ()
   (+
    ;; int64 _target_x
    8
    ;; int64 _target_y
    8
    ;; int64 _vel_x
    8
    ;; int64 _vel_y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _target_x
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _target_x (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _target_x) (= (length (_target_x . bv)) 2)) ;; bignum
              (write-long (ash (elt (_target_x . bv) 0) 0) s)
              (write-long (ash (elt (_target_x . bv) 1) -1) s))
             ((and (class _target_x) (= (length (_target_x . bv)) 1)) ;; big1
              (write-long (elt (_target_x . bv) 0) s)
              (write-long (if (>= _target_x 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _target_x s)(write-long (if (>= _target_x 0) 0 #xffffffff) s)))
     ;; int64 _target_y
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _target_y (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _target_y) (= (length (_target_y . bv)) 2)) ;; bignum
              (write-long (ash (elt (_target_y . bv) 0) 0) s)
              (write-long (ash (elt (_target_y . bv) 1) -1) s))
             ((and (class _target_y) (= (length (_target_y . bv)) 1)) ;; big1
              (write-long (elt (_target_y . bv) 0) s)
              (write-long (if (>= _target_y 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _target_y s)(write-long (if (>= _target_y 0) 0 #xffffffff) s)))
     ;; int64 _vel_x
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _vel_x (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _vel_x) (= (length (_vel_x . bv)) 2)) ;; bignum
              (write-long (ash (elt (_vel_x . bv) 0) 0) s)
              (write-long (ash (elt (_vel_x . bv) 1) -1) s))
             ((and (class _vel_x) (= (length (_vel_x . bv)) 1)) ;; big1
              (write-long (elt (_vel_x . bv) 0) s)
              (write-long (if (>= _vel_x 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _vel_x s)(write-long (if (>= _vel_x 0) 0 #xffffffff) s)))
     ;; int64 _vel_y
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _vel_y (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _vel_y) (= (length (_vel_y . bv)) 2)) ;; bignum
              (write-long (ash (elt (_vel_y . bv) 0) 0) s)
              (write-long (ash (elt (_vel_y . bv) 1) -1) s))
             ((and (class _vel_y) (= (length (_vel_y . bv)) 1)) ;; big1
              (write-long (elt (_vel_y . bv) 0) s)
              (write-long (if (>= _vel_y 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _vel_y s)(write-long (if (>= _vel_y 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _target_x
#+(or :alpha :irix6 :x86_64)
      (setf _target_x (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _target_x (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _target_y
#+(or :alpha :irix6 :x86_64)
      (setf _target_y (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _target_y (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _vel_x
#+(or :alpha :irix6 :x86_64)
      (setf _vel_x (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _vel_x (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _vel_y
#+(or :alpha :irix6 :x86_64)
      (setf _vel_y (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _vel_y (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass ass_1::GetPosition
  :super ros::object
  :slots ())

(setf (get ass_1::GetPosition :md5sum-) "abfe9bd3e68b780b1097da81cd948b40")
(setf (get ass_1::GetPosition :datatype-) "ass_1/GetPosition")
(setf (get ass_1::GetPosition :request) ass_1::GetPositionRequest)
(setf (get ass_1::GetPosition :response) ass_1::GetPositionResponse)

(defmethod ass_1::GetPositionRequest
  (:response () (instance ass_1::GetPositionResponse :init)))

(setf (get ass_1::GetPositionRequest :md5sum-) "abfe9bd3e68b780b1097da81cd948b40")
(setf (get ass_1::GetPositionRequest :datatype-) "ass_1/GetPositionRequest")
(setf (get ass_1::GetPositionRequest :definition-)
      "float64 my_position_x
float64 my_position_y
---
int64 target_x
int64 target_y
int64 vel_x
int64 vel_y

")

(setf (get ass_1::GetPositionResponse :md5sum-) "abfe9bd3e68b780b1097da81cd948b40")
(setf (get ass_1::GetPositionResponse :datatype-) "ass_1/GetPositionResponse")
(setf (get ass_1::GetPositionResponse :definition-)
      "float64 my_position_x
float64 my_position_y
---
int64 target_x
int64 target_y
int64 vel_x
int64 vel_y

")



(provide :ass_1/GetPosition "abfe9bd3e68b780b1097da81cd948b40")


