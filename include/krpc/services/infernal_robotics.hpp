#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <krpc/decoder.hpp>
#include <krpc/encoder.hpp>
#include <krpc/error.hpp>
#include <krpc/event.hpp>
#include <krpc/object.hpp>
#include <krpc/service.hpp>
#include <krpc/stream.hpp>

namespace krpc {
namespace services {

class InfernalRobotics : public Service {
 public:
  explicit InfernalRobotics(Client* client);

  // Class forward declarations
  class Servo;
  class ServoGroup;

  /**
   * Returns the servo group in the given vessel with the given name,
   * or null if none exists. If multiple servo groups have the same name, only one of them is returned.
   * @param vessel Vessel to check.
   * @param name Name of servo group to find.
   */
  InfernalRobotics::ServoGroup servo_group_with_name(SpaceCenter::Vessel vessel, std::string name);

  /**
   * A list of all the servo groups in the given vessel.
   */
  std::vector<InfernalRobotics::ServoGroup> servo_groups(SpaceCenter::Vessel vessel);

  /**
   * Returns the servo in the given vessel with the given name or
   * null if none exists. If multiple servos have the same name, only one of them is returned.
   * @param vessel Vessel to check.
   * @param name Name of the servo to find.
   */
  InfernalRobotics::Servo servo_with_name(SpaceCenter::Vessel vessel, std::string name);

  /**
   * Whether Infernal Robotics is installed.
   */
  bool available();

  /**
   * Whether Infernal Robotics API is ready.
   */
  bool ready();

  ::krpc::Stream<InfernalRobotics::ServoGroup> servo_group_with_name_stream(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::Stream<std::vector<InfernalRobotics::ServoGroup>> servo_groups_stream(SpaceCenter::Vessel vessel);

  ::krpc::Stream<InfernalRobotics::Servo> servo_with_name_stream(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::Stream<bool> available_stream();

  ::krpc::Stream<bool> ready_stream();

  ::krpc::schema::ProcedureCall servo_group_with_name_call(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::schema::ProcedureCall servo_groups_call(SpaceCenter::Vessel vessel);

  ::krpc::schema::ProcedureCall servo_with_name_call(SpaceCenter::Vessel vessel, std::string name);

  ::krpc::schema::ProcedureCall available_call();

  ::krpc::schema::ProcedureCall ready_call();

  /**
   * Represents a servo. Obtained using
   * InfernalRobotics::ServoGroup::servos,
   * InfernalRobotics::ServoGroup::servo_with_name
   * or InfernalRobotics::servo_with_name.
   */
  class Servo : public krpc::Object<Servo> {
   public:
    explicit Servo(Client* client = nullptr, uint64_t id = 0);

    /**
     * Moves the servo to the center.
     */
    void move_center();

    /**
     * Moves the servo to the left.
     */
    void move_left();

    /**
     * Moves the servo to the next preset.
     */
    void move_next_preset();

    /**
     * Moves the servo to the previous preset.
     */
    void move_prev_preset();

    /**
     * Moves the servo to the right.
     */
    void move_right();

    /**
     * Moves the servo to position and sets the
     * speed multiplier to speed.
     * @param position The position to move the servo to.
     * @param speed Speed multiplier for the movement.
     */
    void move_to(float position, float speed);

    /**
     * Stops the servo.
     */
    void stop();

    /**
     * The current speed multiplier set in the UI.
     */
    float acceleration();

    /**
     * The current speed multiplier set in the UI.
     */
    void set_acceleration(float value);

    /**
     * The speed multiplier of the servo, specified by the part configuration.
     */
    float config_speed();

    /**
     * The current speed at which the servo is moving.
     */
    float current_speed();

    /**
     * The current speed at which the servo is moving.
     */
    void set_current_speed(float value);

    /**
     * Whether the servo should be highlighted in-game.
     */
    void set_highlight(bool value);

    /**
     * Whether the servos axis is inverted.
     */
    bool is_axis_inverted();

    /**
     * Whether the servos axis is inverted.
     */
    void set_is_axis_inverted(bool value);

    /**
     * Whether the servo is freely moving.
     */
    bool is_free_moving();

    /**
     * Whether the servo is locked.
     */
    bool is_locked();

    /**
     * Whether the servo is locked.
     */
    void set_is_locked(bool value);

    /**
     * Whether the servo is moving.
     */
    bool is_moving();

    /**
     * The maximum position of the servo, specified by the part configuration.
     */
    float max_config_position();

    /**
     * The maximum position of the servo, specified by the in-game tweak menu.
     */
    float max_position();

    /**
     * The maximum position of the servo, specified by the in-game tweak menu.
     */
    void set_max_position(float value);

    /**
     * The minimum position of the servo, specified by the part configuration.
     */
    float min_config_position();

    /**
     * The minimum position of the servo, specified by the in-game tweak menu.
     */
    float min_position();

    /**
     * The minimum position of the servo, specified by the in-game tweak menu.
     */
    void set_min_position(float value);

    /**
     * The name of the servo.
     */
    std::string name();

    /**
     * The name of the servo.
     */
    void set_name(std::string value);

    /**
     * The part containing the servo.
     */
    SpaceCenter::Part part();

    /**
     * The position of the servo.
     */
    float position();

    /**
     * The speed multiplier of the servo, specified by the in-game tweak menu.
     */
    float speed();

    /**
     * The speed multiplier of the servo, specified by the in-game tweak menu.
     */
    void set_speed(float value);

    ::krpc::Stream<float> acceleration_stream();

    ::krpc::Stream<float> config_speed_stream();

    ::krpc::Stream<float> current_speed_stream();

    ::krpc::Stream<bool> is_axis_inverted_stream();

    ::krpc::Stream<bool> is_free_moving_stream();

    ::krpc::Stream<bool> is_locked_stream();

    ::krpc::Stream<bool> is_moving_stream();

    ::krpc::Stream<float> max_config_position_stream();

    ::krpc::Stream<float> max_position_stream();

    ::krpc::Stream<float> min_config_position_stream();

    ::krpc::Stream<float> min_position_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<SpaceCenter::Part> part_stream();

    ::krpc::Stream<float> position_stream();

    ::krpc::Stream<float> speed_stream();

    ::krpc::schema::ProcedureCall move_center_call();

    ::krpc::schema::ProcedureCall move_left_call();

    ::krpc::schema::ProcedureCall move_next_preset_call();

    ::krpc::schema::ProcedureCall move_prev_preset_call();

    ::krpc::schema::ProcedureCall move_right_call();

    ::krpc::schema::ProcedureCall move_to_call(float position, float speed);

    ::krpc::schema::ProcedureCall stop_call();

    ::krpc::schema::ProcedureCall acceleration_call();

    ::krpc::schema::ProcedureCall set_acceleration_call(float value);

    ::krpc::schema::ProcedureCall config_speed_call();

    ::krpc::schema::ProcedureCall current_speed_call();

    ::krpc::schema::ProcedureCall set_current_speed_call(float value);

    ::krpc::schema::ProcedureCall set_highlight_call(bool value);

    ::krpc::schema::ProcedureCall is_axis_inverted_call();

    ::krpc::schema::ProcedureCall set_is_axis_inverted_call(bool value);

    ::krpc::schema::ProcedureCall is_free_moving_call();

    ::krpc::schema::ProcedureCall is_locked_call();

    ::krpc::schema::ProcedureCall set_is_locked_call(bool value);

    ::krpc::schema::ProcedureCall is_moving_call();

    ::krpc::schema::ProcedureCall max_config_position_call();

    ::krpc::schema::ProcedureCall max_position_call();

    ::krpc::schema::ProcedureCall set_max_position_call(float value);

    ::krpc::schema::ProcedureCall min_config_position_call();

    ::krpc::schema::ProcedureCall min_position_call();

    ::krpc::schema::ProcedureCall set_min_position_call(float value);

    ::krpc::schema::ProcedureCall name_call();

    ::krpc::schema::ProcedureCall set_name_call(std::string value);

    ::krpc::schema::ProcedureCall part_call();

    ::krpc::schema::ProcedureCall position_call();

    ::krpc::schema::ProcedureCall speed_call();

    ::krpc::schema::ProcedureCall set_speed_call(float value);
  };

  /**
   * A group of servos, obtained by calling InfernalRobotics::servo_groups
   * or InfernalRobotics::servo_group_with_name. Represents the "Servo Groups"
   * in the InfernalRobotics UI.
   */
  class ServoGroup : public krpc::Object<ServoGroup> {
   public:
    explicit ServoGroup(Client* client = nullptr, uint64_t id = 0);

    /**
     * Moves all of the servos in the group to the center.
     */
    void move_center();

    /**
     * Moves all of the servos in the group to the left.
     */
    void move_left();

    /**
     * Moves all of the servos in the group to the next preset.
     */
    void move_next_preset();

    /**
     * Moves all of the servos in the group to the previous preset.
     */
    void move_prev_preset();

    /**
     * Moves all of the servos in the group to the right.
     */
    void move_right();

    /**
     * Returns the servo with the given name from this group,
     * or null if none exists.
     * @param name Name of servo to find.
     */
    InfernalRobotics::Servo servo_with_name(std::string name);

    /**
     * Stops the servos in the group.
     */
    void stop();

    /**
     * Whether the group is expanded in the InfernalRobotics UI.
     */
    bool expanded();

    /**
     * Whether the group is expanded in the InfernalRobotics UI.
     */
    void set_expanded(bool value);

    /**
     * The key assigned to be the "forward" key for the group.
     */
    std::string forward_key();

    /**
     * The key assigned to be the "forward" key for the group.
     */
    void set_forward_key(std::string value);

    /**
     * The name of the group.
     */
    std::string name();

    /**
     * The name of the group.
     */
    void set_name(std::string value);

    /**
     * The parts containing the servos in the group.
     */
    std::vector<SpaceCenter::Part> parts();

    /**
     * The key assigned to be the "reverse" key for the group.
     */
    std::string reverse_key();

    /**
     * The key assigned to be the "reverse" key for the group.
     */
    void set_reverse_key(std::string value);

    /**
     * The servos that are in the group.
     */
    std::vector<InfernalRobotics::Servo> servos();

    /**
     * The speed multiplier for the group.
     */
    float speed();

    /**
     * The speed multiplier for the group.
     */
    void set_speed(float value);

    ::krpc::Stream<InfernalRobotics::Servo> servo_with_name_stream(std::string name);

    ::krpc::Stream<bool> expanded_stream();

    ::krpc::Stream<std::string> forward_key_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<std::vector<SpaceCenter::Part>> parts_stream();

    ::krpc::Stream<std::string> reverse_key_stream();

    ::krpc::Stream<std::vector<InfernalRobotics::Servo>> servos_stream();

    ::krpc::Stream<float> speed_stream();

    ::krpc::schema::ProcedureCall move_center_call();

    ::krpc::schema::ProcedureCall move_left_call();

    ::krpc::schema::ProcedureCall move_next_preset_call();

    ::krpc::schema::ProcedureCall move_prev_preset_call();

    ::krpc::schema::ProcedureCall move_right_call();

    ::krpc::schema::ProcedureCall servo_with_name_call(std::string name);

    ::krpc::schema::ProcedureCall stop_call();

    ::krpc::schema::ProcedureCall expanded_call();

    ::krpc::schema::ProcedureCall set_expanded_call(bool value);

    ::krpc::schema::ProcedureCall forward_key_call();

    ::krpc::schema::ProcedureCall set_forward_key_call(std::string value);

    ::krpc::schema::ProcedureCall name_call();

    ::krpc::schema::ProcedureCall set_name_call(std::string value);

    ::krpc::schema::ProcedureCall parts_call();

    ::krpc::schema::ProcedureCall reverse_key_call();

    ::krpc::schema::ProcedureCall set_reverse_key_call(std::string value);

    ::krpc::schema::ProcedureCall servos_call();

    ::krpc::schema::ProcedureCall speed_call();

    ::krpc::schema::ProcedureCall set_speed_call(float value);
  };
};

}  // namespace services

namespace services {

inline InfernalRobotics::InfernalRobotics(Client* client):
  Service(client) {
}

inline InfernalRobotics::ServoGroup InfernalRobotics::servo_group_with_name(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroupWithName", _args);
  InfernalRobotics::ServoGroup _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<InfernalRobotics::ServoGroup> InfernalRobotics::servo_groups(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroups", _args);
  std::vector<InfernalRobotics::ServoGroup> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline InfernalRobotics::Servo InfernalRobotics::servo_with_name(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoWithName", _args);
  InfernalRobotics::Servo _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::available() {
  std::string _data = this->_client->invoke("InfernalRobotics", "get_Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::ready() {
  std::string _data = this->_client->invoke("InfernalRobotics", "get_Ready");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<InfernalRobotics::ServoGroup> InfernalRobotics::servo_group_with_name_stream(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<InfernalRobotics::ServoGroup>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroupWithName", _args));
}

inline ::krpc::Stream<std::vector<InfernalRobotics::ServoGroup>> InfernalRobotics::servo_groups_stream(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  return ::krpc::Stream<std::vector<InfernalRobotics::ServoGroup>>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroups", _args));
}

inline ::krpc::Stream<InfernalRobotics::Servo> InfernalRobotics::servo_with_name_stream(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<InfernalRobotics::Servo>(this->_client, this->_client->build_call("InfernalRobotics", "ServoWithName", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "get_Available"));
}

inline ::krpc::Stream<bool> InfernalRobotics::ready_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "get_Ready"));
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::servo_group_with_name_call(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("InfernalRobotics", "ServoGroupWithName", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::servo_groups_call(SpaceCenter::Vessel vessel) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  return this->_client->build_call("InfernalRobotics", "ServoGroups", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::servo_with_name_call(SpaceCenter::Vessel vessel, std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vessel));
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("InfernalRobotics", "ServoWithName", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::available_call() {
  return this->_client->build_call("InfernalRobotics", "get_Available");
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ready_call() {
  return this->_client->build_call("InfernalRobotics", "get_Ready");
}

inline InfernalRobotics::Servo::Servo(Client* client, uint64_t id):
  Object(client, "InfernalRobotics::Servo", id) {}

inline void InfernalRobotics::Servo::move_center() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveCenter", _args);
}

inline void InfernalRobotics::Servo::move_left() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveLeft", _args);
}

inline void InfernalRobotics::Servo::move_next_preset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveNextPreset", _args);
}

inline void InfernalRobotics::Servo::move_prev_preset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MovePrevPreset", _args);
}

inline void InfernalRobotics::Servo::move_right() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_MoveRight", _args);
}

inline void InfernalRobotics::Servo::move_to(float position, float speed) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(speed));
  this->_client->invoke("InfernalRobotics", "Servo_MoveTo", _args);
}

inline void InfernalRobotics::Servo::stop() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "Servo_Stop", _args);
}

inline float InfernalRobotics::Servo::acceleration() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Acceleration", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_acceleration(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Acceleration", _args);
}

inline float InfernalRobotics::Servo::config_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_ConfigSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::current_speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_CurrentSpeed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_current_speed(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_CurrentSpeed", _args);
}

inline void InfernalRobotics::Servo::set_highlight(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Highlight", _args);
}

inline bool InfernalRobotics::Servo::is_axis_inverted() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsAxisInverted", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_is_axis_inverted(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_IsAxisInverted", _args);
}

inline bool InfernalRobotics::Servo::is_free_moving() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsFreeMoving", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool InfernalRobotics::Servo::is_locked() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsLocked", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_is_locked(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_IsLocked", _args);
}

inline bool InfernalRobotics::Servo::is_moving() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_IsMoving", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::max_config_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxConfigPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::max_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MaxPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_max_position(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_MaxPosition", _args);
}

inline float InfernalRobotics::Servo::min_config_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MinConfigPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::min_position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_MinPosition", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_min_position(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_MinPosition", _args);
}

inline std::string InfernalRobotics::Servo::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Name", _args);
}

inline SpaceCenter::Part InfernalRobotics::Servo::part() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Part", _args);
  SpaceCenter::Part _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Position", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::Servo::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "Servo_get_Speed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::Servo::set_speed(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "Servo_set_Speed", _args);
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::acceleration_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Acceleration", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::config_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_ConfigSpeed", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::current_speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_CurrentSpeed", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_axis_inverted_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsAxisInverted", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_free_moving_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsFreeMoving", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_locked_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsLocked", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::Servo::is_moving_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_IsMoving", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_config_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxConfigPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::max_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MaxPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::min_config_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MinConfigPosition", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::min_position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_MinPosition", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::Servo::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Name", _args));
}

inline ::krpc::Stream<SpaceCenter::Part> InfernalRobotics::Servo::part_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Part>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Part", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Position", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::Servo::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "Servo_get_Speed", _args));
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_center_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveCenter", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_left_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveLeft", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_next_preset_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveNextPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_prev_preset_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MovePrevPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_right_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveRight", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::move_to_call(float position, float speed) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(speed));
  return this->_client->build_call("InfernalRobotics", "Servo_MoveTo", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::stop_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_Stop", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::acceleration_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Acceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_acceleration_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Acceleration", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::config_speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_ConfigSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::current_speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_CurrentSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_current_speed_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_CurrentSpeed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_highlight_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Highlight", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_axis_inverted_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsAxisInverted", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_is_axis_inverted_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_IsAxisInverted", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_free_moving_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsFreeMoving", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_locked_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsLocked", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_is_locked_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_IsLocked", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::is_moving_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_IsMoving", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_config_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxConfigPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::max_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MaxPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_max_position_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_MaxPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::min_config_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MinConfigPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::min_position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_MinPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_min_position_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_MinPosition", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::name_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_name_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::part_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Part", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Position", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "Servo_get_Speed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::Servo::set_speed_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "Servo_set_Speed", _args);
}

inline InfernalRobotics::ServoGroup::ServoGroup(Client* client, uint64_t id):
  Object(client, "InfernalRobotics::ServoGroup", id) {}

inline void InfernalRobotics::ServoGroup::move_center() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveCenter", _args);
}

inline void InfernalRobotics::ServoGroup::move_left() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveLeft", _args);
}

inline void InfernalRobotics::ServoGroup::move_next_preset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveNextPreset", _args);
}

inline void InfernalRobotics::ServoGroup::move_prev_preset() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MovePrevPreset", _args);
}

inline void InfernalRobotics::ServoGroup::move_right() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_MoveRight", _args);
}

inline InfernalRobotics::Servo InfernalRobotics::ServoGroup::servo_with_name(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_ServoWithName", _args);
  InfernalRobotics::Servo _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::stop() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("InfernalRobotics", "ServoGroup_Stop", _args);
}

inline bool InfernalRobotics::ServoGroup::expanded() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Expanded", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_expanded(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_Expanded", _args);
}

inline std::string InfernalRobotics::ServoGroup::forward_key() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_ForwardKey", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_forward_key(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_ForwardKey", _args);
}

inline std::string InfernalRobotics::ServoGroup::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_Name", _args);
}

inline std::vector<SpaceCenter::Part> InfernalRobotics::ServoGroup::parts() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Parts", _args);
  std::vector<SpaceCenter::Part> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string InfernalRobotics::ServoGroup::reverse_key() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_ReverseKey", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_reverse_key(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_ReverseKey", _args);
}

inline std::vector<InfernalRobotics::Servo> InfernalRobotics::ServoGroup::servos() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Servos", _args);
  std::vector<InfernalRobotics::Servo> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline float InfernalRobotics::ServoGroup::speed() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("InfernalRobotics", "ServoGroup_get_Speed", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void InfernalRobotics::ServoGroup::set_speed(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("InfernalRobotics", "ServoGroup_set_Speed", _args);
}

inline ::krpc::Stream<InfernalRobotics::Servo> InfernalRobotics::ServoGroup::servo_with_name_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<InfernalRobotics::Servo>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_ServoWithName", _args));
}

inline ::krpc::Stream<bool> InfernalRobotics::ServoGroup::expanded_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Expanded", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::ServoGroup::forward_key_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_ForwardKey", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::ServoGroup::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Name", _args));
}

inline ::krpc::Stream<std::vector<SpaceCenter::Part>> InfernalRobotics::ServoGroup::parts_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<SpaceCenter::Part>>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Parts", _args));
}

inline ::krpc::Stream<std::string> InfernalRobotics::ServoGroup::reverse_key_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_ReverseKey", _args));
}

inline ::krpc::Stream<std::vector<InfernalRobotics::Servo>> InfernalRobotics::ServoGroup::servos_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<InfernalRobotics::Servo>>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Servos", _args));
}

inline ::krpc::Stream<float> InfernalRobotics::ServoGroup::speed_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("InfernalRobotics", "ServoGroup_get_Speed", _args));
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_center_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveCenter", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_left_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveLeft", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_next_preset_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveNextPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_prev_preset_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MovePrevPreset", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::move_right_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_MoveRight", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::servo_with_name_call(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_ServoWithName", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::stop_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_Stop", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::expanded_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Expanded", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_expanded_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_Expanded", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::forward_key_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_ForwardKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_forward_key_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_ForwardKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::name_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_name_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_Name", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::parts_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Parts", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::reverse_key_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_ReverseKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_reverse_key_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_ReverseKey", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::servos_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Servos", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::speed_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_get_Speed", _args);
}

inline ::krpc::schema::ProcedureCall InfernalRobotics::ServoGroup::set_speed_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("InfernalRobotics", "ServoGroup_set_Speed", _args);
}
}  // namespace services

}  // namespace krpc
