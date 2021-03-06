// Generated by gencpp from file ass_1/GetPosition.msg
// DO NOT EDIT!


#ifndef ASS_1_MESSAGE_GETPOSITION_H
#define ASS_1_MESSAGE_GETPOSITION_H

#include <ros/service_traits.h>


#include <ass_1/GetPositionRequest.h>
#include <ass_1/GetPositionResponse.h>


namespace ass_1
{

struct GetPosition
{

typedef GetPositionRequest Request;
typedef GetPositionResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct GetPosition
} // namespace ass_1


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::ass_1::GetPosition > {
  static const char* value()
  {
    return "abfe9bd3e68b780b1097da81cd948b40";
  }

  static const char* value(const ::ass_1::GetPosition&) { return value(); }
};

template<>
struct DataType< ::ass_1::GetPosition > {
  static const char* value()
  {
    return "ass_1/GetPosition";
  }

  static const char* value(const ::ass_1::GetPosition&) { return value(); }
};


// service_traits::MD5Sum< ::ass_1::GetPositionRequest> should match 
// service_traits::MD5Sum< ::ass_1::GetPosition > 
template<>
struct MD5Sum< ::ass_1::GetPositionRequest>
{
  static const char* value()
  {
    return MD5Sum< ::ass_1::GetPosition >::value();
  }
  static const char* value(const ::ass_1::GetPositionRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::ass_1::GetPositionRequest> should match 
// service_traits::DataType< ::ass_1::GetPosition > 
template<>
struct DataType< ::ass_1::GetPositionRequest>
{
  static const char* value()
  {
    return DataType< ::ass_1::GetPosition >::value();
  }
  static const char* value(const ::ass_1::GetPositionRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::ass_1::GetPositionResponse> should match 
// service_traits::MD5Sum< ::ass_1::GetPosition > 
template<>
struct MD5Sum< ::ass_1::GetPositionResponse>
{
  static const char* value()
  {
    return MD5Sum< ::ass_1::GetPosition >::value();
  }
  static const char* value(const ::ass_1::GetPositionResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::ass_1::GetPositionResponse> should match 
// service_traits::DataType< ::ass_1::GetPosition > 
template<>
struct DataType< ::ass_1::GetPositionResponse>
{
  static const char* value()
  {
    return DataType< ::ass_1::GetPosition >::value();
  }
  static const char* value(const ::ass_1::GetPositionResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // ASS_1_MESSAGE_GETPOSITION_H
