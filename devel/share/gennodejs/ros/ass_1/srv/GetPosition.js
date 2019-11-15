// Auto-generated. Do not edit!

// (in-package ass_1.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class GetPositionRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.my_position_x = null;
      this.my_position_y = null;
    }
    else {
      if (initObj.hasOwnProperty('my_position_x')) {
        this.my_position_x = initObj.my_position_x
      }
      else {
        this.my_position_x = 0.0;
      }
      if (initObj.hasOwnProperty('my_position_y')) {
        this.my_position_y = initObj.my_position_y
      }
      else {
        this.my_position_y = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPositionRequest
    // Serialize message field [my_position_x]
    bufferOffset = _serializer.float64(obj.my_position_x, buffer, bufferOffset);
    // Serialize message field [my_position_y]
    bufferOffset = _serializer.float64(obj.my_position_y, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPositionRequest
    let len;
    let data = new GetPositionRequest(null);
    // Deserialize message field [my_position_x]
    data.my_position_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [my_position_y]
    data.my_position_y = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a service object
    return 'ass_1/GetPositionRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4ba0213a9ddcaa2833e00c0e4c331c63';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 my_position_x
    float64 my_position_y
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetPositionRequest(null);
    if (msg.my_position_x !== undefined) {
      resolved.my_position_x = msg.my_position_x;
    }
    else {
      resolved.my_position_x = 0.0
    }

    if (msg.my_position_y !== undefined) {
      resolved.my_position_y = msg.my_position_y;
    }
    else {
      resolved.my_position_y = 0.0
    }

    return resolved;
    }
};

class GetPositionResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.target_x = null;
      this.target_y = null;
      this.vel_x = null;
      this.vel_y = null;
    }
    else {
      if (initObj.hasOwnProperty('target_x')) {
        this.target_x = initObj.target_x
      }
      else {
        this.target_x = 0;
      }
      if (initObj.hasOwnProperty('target_y')) {
        this.target_y = initObj.target_y
      }
      else {
        this.target_y = 0;
      }
      if (initObj.hasOwnProperty('vel_x')) {
        this.vel_x = initObj.vel_x
      }
      else {
        this.vel_x = 0;
      }
      if (initObj.hasOwnProperty('vel_y')) {
        this.vel_y = initObj.vel_y
      }
      else {
        this.vel_y = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GetPositionResponse
    // Serialize message field [target_x]
    bufferOffset = _serializer.int64(obj.target_x, buffer, bufferOffset);
    // Serialize message field [target_y]
    bufferOffset = _serializer.int64(obj.target_y, buffer, bufferOffset);
    // Serialize message field [vel_x]
    bufferOffset = _serializer.int64(obj.vel_x, buffer, bufferOffset);
    // Serialize message field [vel_y]
    bufferOffset = _serializer.int64(obj.vel_y, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GetPositionResponse
    let len;
    let data = new GetPositionResponse(null);
    // Deserialize message field [target_x]
    data.target_x = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [target_y]
    data.target_y = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [vel_x]
    data.vel_x = _deserializer.int64(buffer, bufferOffset);
    // Deserialize message field [vel_y]
    data.vel_y = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a service object
    return 'ass_1/GetPositionResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '920d1466c409692386b7901cf3d5d205';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 target_x
    int64 target_y
    int64 vel_x
    int64 vel_y
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GetPositionResponse(null);
    if (msg.target_x !== undefined) {
      resolved.target_x = msg.target_x;
    }
    else {
      resolved.target_x = 0
    }

    if (msg.target_y !== undefined) {
      resolved.target_y = msg.target_y;
    }
    else {
      resolved.target_y = 0
    }

    if (msg.vel_x !== undefined) {
      resolved.vel_x = msg.vel_x;
    }
    else {
      resolved.vel_x = 0
    }

    if (msg.vel_y !== undefined) {
      resolved.vel_y = msg.vel_y;
    }
    else {
      resolved.vel_y = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: GetPositionRequest,
  Response: GetPositionResponse,
  md5sum() { return 'abfe9bd3e68b780b1097da81cd948b40'; },
  datatype() { return 'ass_1/GetPosition'; }
};
