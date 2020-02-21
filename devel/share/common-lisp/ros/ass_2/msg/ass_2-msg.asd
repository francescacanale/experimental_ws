
(cl:in-package :asdf)

(defsystem "ass_2-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Translation" :depends-on ("_package_Translation"))
    (:file "_package_Translation" :depends-on ("_package"))
  ))