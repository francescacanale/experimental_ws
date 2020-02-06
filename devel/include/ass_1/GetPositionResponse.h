// Generated by gencpp from file ass_1/GetPositionResponse.msg
// DO NOT EDIT!


#ifndef ASS_1_MESSAGE_GETPOSITIONRESPONSE_H
#define ASS_1_MESSAGE_GETPOSITIONRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ass_1
{
template <class ContainerAllocator>
struct GetPositionResponse_
{
  typedef GetPositionResponse_<ContainerAllocator> Type;

  GetPositionResponse_()
    : target_x(0)
    , target_y(0)
    , vel_x(0)
    , vel_y(0)  {
    }
  GetPositionResponse_(const ContainerAllocator& _alloc)
    : target_x(0)
    , target_y(0)
    , vel_x(0)
    , vel_y(0)  {
  (void)_alloc;
    }



   typedef int64_t _target_x_type;
  _target_x_type target_x;

   typedef int64_t _target_y_type;
  _target_y_type target_y;

   typedef int64_t _vel_x_type;
  _vel_x_type vel_x;

   typedef int64_t _vel_y_type;
  _vel_y_type vel_y;





  typedef boost::shared_ptr< ::ass_1::GetPositionResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ass_1::GetPositionResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetPositionResponse_

typedef ::ass_1::GetPositionResponse_<std::allocator<void> > GetPositionResponse;

typedef boost::shared_ptr< ::ass_1::GetPositionResponse > GetPositionResponsePtr;
typedef boost::shared_ptr< ::ass_1::GetPositionResponse const> GetPositionResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ass_1::GetPositionResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ass_1::GetPositionResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace ass_1

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::ass_1::GetPositionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ass_1::GetPositionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ass_1::GetPositionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ass_1::GetPositionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ass_1::GetPositionResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ass_1::GetPositionResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ass_1::GetPositionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "920d1466c409692386b7901cf3d5d205";
  }

  static const char* value(const ::ass_1::GetPositionResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x920d1466c4096923ULL;
  static const uint64_t static_value2 = 0x86b7901cf3d5d205ULL;
};

template<class ContainerAllocator>
struct DataType< ::ass_1::GetPositionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ass_1/GetPositionResponse";
  }

  static const char* value(const ::ass_1::GetPositionResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ass_1::GetPositionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 target_x\n\
int64 target_y\n\
int64 vel_x\n\
int64 vel_y\n\
\n\
";
  }

  static const char* value(const ::ass_1::GetPositionResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ass_1::GetPositionResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.target_x);
      stream.next(m.target_y);
      stream.next(m.vel_x);
      stream.next(m.vel_y);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetPositionResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ass_1::GetPositionResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ass_1::GetPositionResponse_<ContainerAllocator>& v)
  {
    s << indent << "target_x: ";
    Printer<int64_t>::stream(s, indent + "  ", v.target_x);
    s << indent << "target_y: ";
    Printer<int64_t>::stream(s, indent + "  ", v.target_y);
    s << indent << "vel_x: ";
    Printer<int64_t>::stream(s, indent + "  ", v.vel_x);
    s << indent << "vel_y: ";
    Printer<int64_t>::stream(s, indent + "  ", v.vel_y);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ASS_1_MESSAGE_GETPOSITIONRESPONSE_H