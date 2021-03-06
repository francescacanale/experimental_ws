// Generated by gencpp from file ass_2/Translation.msg
// DO NOT EDIT!


#ifndef ASS_2_MESSAGE_TRANSLATION_H
#define ASS_2_MESSAGE_TRANSLATION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace ass_2
{
template <class ContainerAllocator>
struct Translation_
{
  typedef Translation_<ContainerAllocator> Type;

  Translation_()
    : header()
    , x(0.0)
    , y(0.0)
    , z(0.0)  {
    }
  Translation_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , x(0.0)
    , y(0.0)
    , z(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _x_type;
  _x_type x;

   typedef float _y_type;
  _y_type y;

   typedef float _z_type;
  _z_type z;





  typedef boost::shared_ptr< ::ass_2::Translation_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ass_2::Translation_<ContainerAllocator> const> ConstPtr;

}; // struct Translation_

typedef ::ass_2::Translation_<std::allocator<void> > Translation;

typedef boost::shared_ptr< ::ass_2::Translation > TranslationPtr;
typedef boost::shared_ptr< ::ass_2::Translation const> TranslationConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ass_2::Translation_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ass_2::Translation_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ass_2

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'ass_2': ['/home/experimental_ws/src/ass_2/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ass_2::Translation_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ass_2::Translation_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ass_2::Translation_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ass_2::Translation_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ass_2::Translation_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ass_2::Translation_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ass_2::Translation_<ContainerAllocator> >
{
  static const char* value()
  {
    return "75f40115cb5a29c0ceea66f491a5e1a3";
  }

  static const char* value(const ::ass_2::Translation_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x75f40115cb5a29c0ULL;
  static const uint64_t static_value2 = 0xceea66f491a5e1a3ULL;
};

template<class ContainerAllocator>
struct DataType< ::ass_2::Translation_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ass_2/Translation";
  }

  static const char* value(const ::ass_2::Translation_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ass_2::Translation_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float32 x\n\
float32 y\n\
float32 z\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::ass_2::Translation_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ass_2::Translation_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Translation_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ass_2::Translation_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ass_2::Translation_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "x: ";
    Printer<float>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<float>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<float>::stream(s, indent + "  ", v.z);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ASS_2_MESSAGE_TRANSLATION_H
