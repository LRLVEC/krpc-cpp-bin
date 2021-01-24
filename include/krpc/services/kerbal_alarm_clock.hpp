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

class KerbalAlarmClock : public Service {
 public:
  explicit KerbalAlarmClock(Client* client);

  // Class forward declarations
  class Alarm;

  /**
   * The action performed by an alarm when it fires.
   */
  enum struct AlarmAction {
    /**
     * Don't do anything at all...
     */
    do_nothing = 0,
    /**
     * Don't do anything, and delete the alarm.
     */
    do_nothing_delete_when_passed = 1,
    /**
     * Drop out of time warp.
     */
    kill_warp = 2,
    /**
     * Drop out of time warp.
     */
    kill_warp_only = 3,
    /**
     * Display a message.
     */
    message_only = 4,
    /**
     * Pause the game.
     */
    pause_game = 5
  };

  /**
   * The type of an alarm.
   */
  enum struct AlarmType {
    /**
     * An alarm for a specific date/time or a specific period in the future.
     */
    raw = 0,
    /**
     * An alarm based on the next maneuver node on the current ships flight path.
     * This node will be stored and can be restored when you come back to the ship.
     */
    maneuver = 1,
    /**
     * See KerbalAlarmClock::AlarmType::maneuver.
     */
    maneuver_auto = 2,
    /**
     * An alarm for furthest part of the orbit from the planet.
     */
    apoapsis = 3,
    /**
     * An alarm for nearest part of the orbit from the planet.
     */
    periapsis = 4,
    /**
     * Ascending node for the targeted object, or equatorial ascending node.
     */
    ascending_node = 5,
    /**
     * Descending node for the targeted object, or equatorial descending node.
     */
    descending_node = 6,
    /**
     * An alarm based on the closest approach of this vessel to the targeted
     * vessel, some number of orbits into the future.
     */
    closest = 7,
    /**
     * An alarm based on the expiry or deadline of contracts in career modes.
     */
    contract = 8,
    /**
     * See KerbalAlarmClock::AlarmType::contract.
     */
    contract_auto = 9,
    /**
     * An alarm that is attached to a crew member.
     */
    crew = 10,
    /**
     * An alarm that is triggered when a selected target comes within a chosen distance.
     */
    distance = 11,
    /**
     * An alarm based on the time in the "Earth" alternative Universe (aka the Real World).
     */
    earth_time = 12,
    /**
     * An alarm that fires as your landed craft passes under the orbit of your target.
     */
    launch_rendevous = 13,
    /**
     * An alarm manually based on when the next SOI point is on the flight path
     * or set to continually monitor the active flight path and add alarms as it
     * detects SOI changes.
     */
    soi_change = 14,
    /**
     * See KerbalAlarmClock::AlarmType::soi_change.
     */
    soi_change_auto = 15,
    /**
     * An alarm based on Interplanetary Transfer Phase Angles, i.e. when should
     * I launch to planet X? Based on Kosmo Not's post and used in Olex's
     * Calculator.
     */
    transfer = 16,
    /**
     * See KerbalAlarmClock::AlarmType::transfer.
     */
    transfer_modelled = 17
  };

  /**
   * Get the alarm with the given name, or null
   * if no alarms have that name. If more than one alarm has the name,
   * only returns one of them.
   * @param name Name of the alarm to search for.
   */
  KerbalAlarmClock::Alarm alarm_with_name(std::string name);

  /**
   * Get a list of alarms of the specified type.
   * @param type Type of alarm to return.
   */
  std::vector<KerbalAlarmClock::Alarm> alarms_with_type(KerbalAlarmClock::AlarmType type);

  /**
   * Create a new alarm and return it.
   * @param type Type of the new alarm.
   * @param name Name of the new alarm.
   * @param ut Time at which the new alarm should trigger.
   */
  KerbalAlarmClock::Alarm create_alarm(KerbalAlarmClock::AlarmType type, std::string name, double ut);

  /**
   * A list of all the alarms.
   */
  std::vector<KerbalAlarmClock::Alarm> alarms();

  /**
   * Whether Kerbal Alarm Clock is available.
   */
  bool available();

  ::krpc::Stream<KerbalAlarmClock::Alarm> alarm_with_name_stream(std::string name);

  ::krpc::Stream<std::vector<KerbalAlarmClock::Alarm>> alarms_with_type_stream(KerbalAlarmClock::AlarmType type);

  ::krpc::Stream<KerbalAlarmClock::Alarm> create_alarm_stream(KerbalAlarmClock::AlarmType type, std::string name, double ut);

  ::krpc::Stream<std::vector<KerbalAlarmClock::Alarm>> alarms_stream();

  ::krpc::Stream<bool> available_stream();

  ::krpc::schema::ProcedureCall alarm_with_name_call(std::string name);

  ::krpc::schema::ProcedureCall alarms_with_type_call(KerbalAlarmClock::AlarmType type);

  ::krpc::schema::ProcedureCall create_alarm_call(KerbalAlarmClock::AlarmType type, std::string name, double ut);

  ::krpc::schema::ProcedureCall alarms_call();

  ::krpc::schema::ProcedureCall available_call();

  /**
   * Represents an alarm. Obtained by calling
   * KerbalAlarmClock::alarms,
   * KerbalAlarmClock::alarm_with_name or
   * KerbalAlarmClock::alarms_with_type.
   */
  class Alarm : public krpc::Object<Alarm> {
   public:
    explicit Alarm(Client* client = nullptr, uint64_t id = 0);

    /**
     * Removes the alarm.
     */
    void remove();

    /**
     * The action that the alarm triggers.
     */
    KerbalAlarmClock::AlarmAction action();

    /**
     * The action that the alarm triggers.
     */
    void set_action(KerbalAlarmClock::AlarmAction value);

    /**
     * The unique identifier for the alarm.
     */
    std::string id();

    /**
     * The number of seconds before the event that the alarm will fire.
     */
    double margin();

    /**
     * The number of seconds before the event that the alarm will fire.
     */
    void set_margin(double value);

    /**
     * The short name of the alarm.
     */
    std::string name();

    /**
     * The short name of the alarm.
     */
    void set_name(std::string value);

    /**
     * The long description of the alarm.
     */
    std::string notes();

    /**
     * The long description of the alarm.
     */
    void set_notes(std::string value);

    /**
     * The number of seconds until the alarm will fire.
     */
    double remaining();

    /**
     * Whether the alarm will be repeated after it has fired.
     */
    bool repeat();

    /**
     * Whether the alarm will be repeated after it has fired.
     */
    void set_repeat(bool value);

    /**
     * The time delay to automatically create an alarm after it has fired.
     */
    double repeat_period();

    /**
     * The time delay to automatically create an alarm after it has fired.
     */
    void set_repeat_period(double value);

    /**
     * The time at which the alarm will fire.
     */
    double time();

    /**
     * The time at which the alarm will fire.
     */
    void set_time(double value);

    /**
     * The type of the alarm.
     */
    KerbalAlarmClock::AlarmType type();

    /**
     * The vessel that the alarm is attached to.
     */
    SpaceCenter::Vessel vessel();

    /**
     * The vessel that the alarm is attached to.
     */
    void set_vessel(SpaceCenter::Vessel value);

    /**
     * The celestial body the vessel is departing from.
     */
    SpaceCenter::CelestialBody xfer_origin_body();

    /**
     * The celestial body the vessel is departing from.
     */
    void set_xfer_origin_body(SpaceCenter::CelestialBody value);

    /**
     * The celestial body the vessel is arriving at.
     */
    SpaceCenter::CelestialBody xfer_target_body();

    /**
     * The celestial body the vessel is arriving at.
     */
    void set_xfer_target_body(SpaceCenter::CelestialBody value);

    ::krpc::Stream<KerbalAlarmClock::AlarmAction> action_stream();

    ::krpc::Stream<std::string> id_stream();

    ::krpc::Stream<double> margin_stream();

    ::krpc::Stream<std::string> name_stream();

    ::krpc::Stream<std::string> notes_stream();

    ::krpc::Stream<double> remaining_stream();

    ::krpc::Stream<bool> repeat_stream();

    ::krpc::Stream<double> repeat_period_stream();

    ::krpc::Stream<double> time_stream();

    ::krpc::Stream<KerbalAlarmClock::AlarmType> type_stream();

    ::krpc::Stream<SpaceCenter::Vessel> vessel_stream();

    ::krpc::Stream<SpaceCenter::CelestialBody> xfer_origin_body_stream();

    ::krpc::Stream<SpaceCenter::CelestialBody> xfer_target_body_stream();

    ::krpc::schema::ProcedureCall remove_call();

    ::krpc::schema::ProcedureCall action_call();

    ::krpc::schema::ProcedureCall set_action_call(KerbalAlarmClock::AlarmAction value);

    ::krpc::schema::ProcedureCall id_call();

    ::krpc::schema::ProcedureCall margin_call();

    ::krpc::schema::ProcedureCall set_margin_call(double value);

    ::krpc::schema::ProcedureCall name_call();

    ::krpc::schema::ProcedureCall set_name_call(std::string value);

    ::krpc::schema::ProcedureCall notes_call();

    ::krpc::schema::ProcedureCall set_notes_call(std::string value);

    ::krpc::schema::ProcedureCall remaining_call();

    ::krpc::schema::ProcedureCall repeat_call();

    ::krpc::schema::ProcedureCall set_repeat_call(bool value);

    ::krpc::schema::ProcedureCall repeat_period_call();

    ::krpc::schema::ProcedureCall set_repeat_period_call(double value);

    ::krpc::schema::ProcedureCall time_call();

    ::krpc::schema::ProcedureCall set_time_call(double value);

    ::krpc::schema::ProcedureCall type_call();

    ::krpc::schema::ProcedureCall vessel_call();

    ::krpc::schema::ProcedureCall set_vessel_call(SpaceCenter::Vessel value);

    ::krpc::schema::ProcedureCall xfer_origin_body_call();

    ::krpc::schema::ProcedureCall set_xfer_origin_body_call(SpaceCenter::CelestialBody value);

    ::krpc::schema::ProcedureCall xfer_target_body_call();

    ::krpc::schema::ProcedureCall set_xfer_target_body_call(SpaceCenter::CelestialBody value);
  };
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::KerbalAlarmClock::AlarmAction& value) {
    return krpc::encoder::encode(static_cast<int32_t>(value));
  }

  inline std::string encode(const services::KerbalAlarmClock::AlarmType& value) {
    return krpc::encoder::encode(static_cast<int32_t>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::KerbalAlarmClock::AlarmAction& value, const std::string& data, Client* client) {
    int32_t x;
    decode(x, data, client);
    value = static_cast<services::KerbalAlarmClock::AlarmAction>(x);
  }

  inline void decode(services::KerbalAlarmClock::AlarmType& value, const std::string& data, Client* client) {
    int32_t x;
    decode(x, data, client);
    value = static_cast<services::KerbalAlarmClock::AlarmType>(x);
  }

}  // namespace decoder

namespace services {

inline KerbalAlarmClock::KerbalAlarmClock(Client* client):
  Service(client) {
}

inline KerbalAlarmClock::Alarm KerbalAlarmClock::alarm_with_name(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "AlarmWithName", _args);
  KerbalAlarmClock::Alarm _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<KerbalAlarmClock::Alarm> KerbalAlarmClock::alarms_with_type(KerbalAlarmClock::AlarmType type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(type));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "AlarmsWithType", _args);
  std::vector<KerbalAlarmClock::Alarm> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline KerbalAlarmClock::Alarm KerbalAlarmClock::create_alarm(KerbalAlarmClock::AlarmType type, std::string name, double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(type));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(ut));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "CreateAlarm", _args);
  KerbalAlarmClock::Alarm _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::vector<KerbalAlarmClock::Alarm> KerbalAlarmClock::alarms() {
  std::string _data = this->_client->invoke("KerbalAlarmClock", "get_Alarms");
  std::vector<KerbalAlarmClock::Alarm> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool KerbalAlarmClock::available() {
  std::string _data = this->_client->invoke("KerbalAlarmClock", "get_Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<KerbalAlarmClock::Alarm> KerbalAlarmClock::alarm_with_name_stream(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  return ::krpc::Stream<KerbalAlarmClock::Alarm>(this->_client, this->_client->build_call("KerbalAlarmClock", "AlarmWithName", _args));
}

inline ::krpc::Stream<std::vector<KerbalAlarmClock::Alarm>> KerbalAlarmClock::alarms_with_type_stream(KerbalAlarmClock::AlarmType type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(type));
  return ::krpc::Stream<std::vector<KerbalAlarmClock::Alarm>>(this->_client, this->_client->build_call("KerbalAlarmClock", "AlarmsWithType", _args));
}

inline ::krpc::Stream<KerbalAlarmClock::Alarm> KerbalAlarmClock::create_alarm_stream(KerbalAlarmClock::AlarmType type, std::string name, double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(type));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(ut));
  return ::krpc::Stream<KerbalAlarmClock::Alarm>(this->_client, this->_client->build_call("KerbalAlarmClock", "CreateAlarm", _args));
}

inline ::krpc::Stream<std::vector<KerbalAlarmClock::Alarm>> KerbalAlarmClock::alarms_stream() {
  return ::krpc::Stream<std::vector<KerbalAlarmClock::Alarm>>(this->_client, this->_client->build_call("KerbalAlarmClock", "get_Alarms"));
}

inline ::krpc::Stream<bool> KerbalAlarmClock::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("KerbalAlarmClock", "get_Available"));
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::alarm_with_name_call(std::string name) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  return this->_client->build_call("KerbalAlarmClock", "AlarmWithName", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::alarms_with_type_call(KerbalAlarmClock::AlarmType type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(type));
  return this->_client->build_call("KerbalAlarmClock", "AlarmsWithType", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::create_alarm_call(KerbalAlarmClock::AlarmType type, std::string name, double ut) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(type));
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(ut));
  return this->_client->build_call("KerbalAlarmClock", "CreateAlarm", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::alarms_call() {
  return this->_client->build_call("KerbalAlarmClock", "get_Alarms");
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::available_call() {
  return this->_client->build_call("KerbalAlarmClock", "get_Available");
}

inline KerbalAlarmClock::Alarm::Alarm(Client* client, uint64_t id):
  Object(client, "KerbalAlarmClock::Alarm", id) {}

inline void KerbalAlarmClock::Alarm::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("KerbalAlarmClock", "Alarm_Remove", _args);
}

inline KerbalAlarmClock::AlarmAction KerbalAlarmClock::Alarm::action() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Action", _args);
  KerbalAlarmClock::AlarmAction _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_action(KerbalAlarmClock::AlarmAction value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Action", _args);
}

inline std::string KerbalAlarmClock::Alarm::id() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_ID", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline double KerbalAlarmClock::Alarm::margin() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Margin", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_margin(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Margin", _args);
}

inline std::string KerbalAlarmClock::Alarm::name() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Name", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_name(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Name", _args);
}

inline std::string KerbalAlarmClock::Alarm::notes() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Notes", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_notes(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Notes", _args);
}

inline double KerbalAlarmClock::Alarm::remaining() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Remaining", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool KerbalAlarmClock::Alarm::repeat() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Repeat", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_repeat(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Repeat", _args);
}

inline double KerbalAlarmClock::Alarm::repeat_period() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_RepeatPeriod", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_repeat_period(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_RepeatPeriod", _args);
}

inline double KerbalAlarmClock::Alarm::time() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Time", _args);
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_time(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Time", _args);
}

inline KerbalAlarmClock::AlarmType KerbalAlarmClock::Alarm::type() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Type", _args);
  KerbalAlarmClock::AlarmType _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline SpaceCenter::Vessel KerbalAlarmClock::Alarm::vessel() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_Vessel", _args);
  SpaceCenter::Vessel _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_vessel(SpaceCenter::Vessel value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_Vessel", _args);
}

inline SpaceCenter::CelestialBody KerbalAlarmClock::Alarm::xfer_origin_body() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_XferOriginBody", _args);
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_xfer_origin_body(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_XferOriginBody", _args);
}

inline SpaceCenter::CelestialBody KerbalAlarmClock::Alarm::xfer_target_body() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("KerbalAlarmClock", "Alarm_get_XferTargetBody", _args);
  SpaceCenter::CelestialBody _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KerbalAlarmClock::Alarm::set_xfer_target_body(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KerbalAlarmClock", "Alarm_set_XferTargetBody", _args);
}

inline ::krpc::Stream<KerbalAlarmClock::AlarmAction> KerbalAlarmClock::Alarm::action_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<KerbalAlarmClock::AlarmAction>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Action", _args));
}

inline ::krpc::Stream<std::string> KerbalAlarmClock::Alarm::id_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_ID", _args));
}

inline ::krpc::Stream<double> KerbalAlarmClock::Alarm::margin_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Margin", _args));
}

inline ::krpc::Stream<std::string> KerbalAlarmClock::Alarm::name_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Name", _args));
}

inline ::krpc::Stream<std::string> KerbalAlarmClock::Alarm::notes_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Notes", _args));
}

inline ::krpc::Stream<double> KerbalAlarmClock::Alarm::remaining_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Remaining", _args));
}

inline ::krpc::Stream<bool> KerbalAlarmClock::Alarm::repeat_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Repeat", _args));
}

inline ::krpc::Stream<double> KerbalAlarmClock::Alarm::repeat_period_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_RepeatPeriod", _args));
}

inline ::krpc::Stream<double> KerbalAlarmClock::Alarm::time_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<double>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Time", _args));
}

inline ::krpc::Stream<KerbalAlarmClock::AlarmType> KerbalAlarmClock::Alarm::type_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<KerbalAlarmClock::AlarmType>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Type", _args));
}

inline ::krpc::Stream<SpaceCenter::Vessel> KerbalAlarmClock::Alarm::vessel_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::Vessel>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_Vessel", _args));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> KerbalAlarmClock::Alarm::xfer_origin_body_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_XferOriginBody", _args));
}

inline ::krpc::Stream<SpaceCenter::CelestialBody> KerbalAlarmClock::Alarm::xfer_target_body_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::CelestialBody>(this->_client, this->_client->build_call("KerbalAlarmClock", "Alarm_get_XferTargetBody", _args));
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::remove_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_Remove", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::action_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Action", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_action_call(KerbalAlarmClock::AlarmAction value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Action", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::id_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_ID", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::margin_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Margin", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_margin_call(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Margin", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::name_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Name", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_name_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Name", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::notes_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Notes", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_notes_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Notes", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::remaining_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Remaining", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::repeat_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Repeat", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_repeat_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Repeat", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::repeat_period_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_RepeatPeriod", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_repeat_period_call(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_RepeatPeriod", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::time_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Time", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_time_call(double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Time", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::type_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Type", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::vessel_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_Vessel", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_vessel_call(SpaceCenter::Vessel value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_Vessel", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::xfer_origin_body_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_XferOriginBody", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_xfer_origin_body_call(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_XferOriginBody", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::xfer_target_body_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_get_XferTargetBody", _args);
}

inline ::krpc::schema::ProcedureCall KerbalAlarmClock::Alarm::set_xfer_target_body_call(SpaceCenter::CelestialBody value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KerbalAlarmClock", "Alarm_set_XferTargetBody", _args);
}
}  // namespace services

}  // namespace krpc
