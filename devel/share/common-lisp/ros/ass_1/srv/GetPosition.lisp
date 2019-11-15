; Auto-generated. Do not edit!


(cl:in-package ass_1-srv)


;//! \htmlinclude GetPosition-request.msg.html

(cl:defclass <GetPosition-request> (roslisp-msg-protocol:ros-message)
  ((my_position_x
    :reader my_position_x
    :initarg :my_position_x
    :type cl:float
    :initform 0.0)
   (my_position_y
    :reader my_position_y
    :initarg :my_position_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass GetPosition-request (<GetPosition-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPosition-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPosition-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ass_1-srv:<GetPosition-request> is deprecated: use ass_1-srv:GetPosition-request instead.")))

(cl:ensure-generic-function 'my_position_x-val :lambda-list '(m))
(cl:defmethod my_position_x-val ((m <GetPosition-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ass_1-srv:my_position_x-val is deprecated.  Use ass_1-srv:my_position_x instead.")
  (my_position_x m))

(cl:ensure-generic-function 'my_position_y-val :lambda-list '(m))
(cl:defmethod my_position_y-val ((m <GetPosition-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ass_1-srv:my_position_y-val is deprecated.  Use ass_1-srv:my_position_y instead.")
  (my_position_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPosition-request>) ostream)
  "Serializes a message object of type '<GetPosition-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'my_position_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'my_position_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPosition-request>) istream)
  "Deserializes a message object of type '<GetPosition-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'my_position_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'my_position_y) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPosition-request>)))
  "Returns string type for a service object of type '<GetPosition-request>"
  "ass_1/GetPositionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPosition-request)))
  "Returns string type for a service object of type 'GetPosition-request"
  "ass_1/GetPositionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPosition-request>)))
  "Returns md5sum for a message object of type '<GetPosition-request>"
  "abfe9bd3e68b780b1097da81cd948b40")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPosition-request)))
  "Returns md5sum for a message object of type 'GetPosition-request"
  "abfe9bd3e68b780b1097da81cd948b40")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPosition-request>)))
  "Returns full string definition for message of type '<GetPosition-request>"
  (cl:format cl:nil "float64 my_position_x~%float64 my_position_y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPosition-request)))
  "Returns full string definition for message of type 'GetPosition-request"
  (cl:format cl:nil "float64 my_position_x~%float64 my_position_y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPosition-request>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPosition-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPosition-request
    (cl:cons ':my_position_x (my_position_x msg))
    (cl:cons ':my_position_y (my_position_y msg))
))
;//! \htmlinclude GetPosition-response.msg.html

(cl:defclass <GetPosition-response> (roslisp-msg-protocol:ros-message)
  ((target_x
    :reader target_x
    :initarg :target_x
    :type cl:integer
    :initform 0)
   (target_y
    :reader target_y
    :initarg :target_y
    :type cl:integer
    :initform 0)
   (vel_x
    :reader vel_x
    :initarg :vel_x
    :type cl:integer
    :initform 0)
   (vel_y
    :reader vel_y
    :initarg :vel_y
    :type cl:integer
    :initform 0))
)

(cl:defclass GetPosition-response (<GetPosition-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GetPosition-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GetPosition-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ass_1-srv:<GetPosition-response> is deprecated: use ass_1-srv:GetPosition-response instead.")))

(cl:ensure-generic-function 'target_x-val :lambda-list '(m))
(cl:defmethod target_x-val ((m <GetPosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ass_1-srv:target_x-val is deprecated.  Use ass_1-srv:target_x instead.")
  (target_x m))

(cl:ensure-generic-function 'target_y-val :lambda-list '(m))
(cl:defmethod target_y-val ((m <GetPosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ass_1-srv:target_y-val is deprecated.  Use ass_1-srv:target_y instead.")
  (target_y m))

(cl:ensure-generic-function 'vel_x-val :lambda-list '(m))
(cl:defmethod vel_x-val ((m <GetPosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ass_1-srv:vel_x-val is deprecated.  Use ass_1-srv:vel_x instead.")
  (vel_x m))

(cl:ensure-generic-function 'vel_y-val :lambda-list '(m))
(cl:defmethod vel_y-val ((m <GetPosition-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ass_1-srv:vel_y-val is deprecated.  Use ass_1-srv:vel_y instead.")
  (vel_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GetPosition-response>) ostream)
  "Serializes a message object of type '<GetPosition-response>"
  (cl:let* ((signed (cl:slot-value msg 'target_x)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'target_y)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'vel_x)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'vel_y)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GetPosition-response>) istream)
  "Deserializes a message object of type '<GetPosition-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'target_x) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'target_y) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vel_x) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vel_y) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GetPosition-response>)))
  "Returns string type for a service object of type '<GetPosition-response>"
  "ass_1/GetPositionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPosition-response)))
  "Returns string type for a service object of type 'GetPosition-response"
  "ass_1/GetPositionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GetPosition-response>)))
  "Returns md5sum for a message object of type '<GetPosition-response>"
  "abfe9bd3e68b780b1097da81cd948b40")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GetPosition-response)))
  "Returns md5sum for a message object of type 'GetPosition-response"
  "abfe9bd3e68b780b1097da81cd948b40")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GetPosition-response>)))
  "Returns full string definition for message of type '<GetPosition-response>"
  (cl:format cl:nil "int64 target_x~%int64 target_y~%int64 vel_x~%int64 vel_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GetPosition-response)))
  "Returns full string definition for message of type 'GetPosition-response"
  (cl:format cl:nil "int64 target_x~%int64 target_y~%int64 vel_x~%int64 vel_y~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GetPosition-response>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GetPosition-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GetPosition-response
    (cl:cons ':target_x (target_x msg))
    (cl:cons ':target_y (target_y msg))
    (cl:cons ':vel_x (vel_x msg))
    (cl:cons ':vel_y (vel_y msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GetPosition)))
  'GetPosition-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GetPosition)))
  'GetPosition-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GetPosition)))
  "Returns string type for a service object of type '<GetPosition>"
  "ass_1/GetPosition")