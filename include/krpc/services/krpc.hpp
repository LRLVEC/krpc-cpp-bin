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

class KRPC : public Service {
 public:
  explicit KRPC(Client* client);

  // Class forward declarations
  class Expression;
  class Type;

  /**
   * A method was invoked where at least one of the passed arguments does not
   * meet the parameter specification of the method.
   */
  class ArgumentException : public ::krpc::RPCError {
   public:
    inline explicit ArgumentException(const std::string& msg) : ::krpc::RPCError(msg) {}
  };

  /**
   * A null reference was passed to a method that does not accept it as a valid argument.
   */
  class ArgumentNullException : public ::krpc::RPCError {
   public:
    inline explicit ArgumentNullException(const std::string& msg) : ::krpc::RPCError(msg) {}
  };

  /**
   * The value of an argument is outside the allowable range of values as defined by the invoked method.
   */
  class ArgumentOutOfRangeException : public ::krpc::RPCError {
   public:
    inline explicit ArgumentOutOfRangeException(const std::string& msg) : ::krpc::RPCError(msg) {}
  };

  /**
   * A method call was made to a method that is invalid
   * given the current state of the object.
   */
  class InvalidOperationException : public ::krpc::RPCError {
   public:
    inline explicit InvalidOperationException(const std::string& msg) : ::krpc::RPCError(msg) {}
  };

  /**
   * The game scene. See KRPC::current_game_scene.
   */
  enum struct GameScene {
    /**
     * The game scene showing the Kerbal Space Center buildings.
     */
    space_center = 0,
    /**
     * The game scene showing a vessel in flight (or on the launchpad/runway).
     */
    flight = 1,
    /**
     * The tracking station.
     */
    tracking_station = 2,
    /**
     * The Vehicle Assembly Building.
     */
    editor_vab = 3,
    /**
     * The Space Plane Hangar.
     */
    editor_sph = 4
  };

  /**
   * Create an event from a server side expression.
   */
  ::krpc::Event add_event(KRPC::Expression expression);

  /**
   * Add a streaming request and return its identifier.
   */
  krpc::schema::Stream add_stream(krpc::schema::ProcedureCall call, bool start);

  /**
   * Returns the identifier for the current client.
   */
  std::string get_client_id();

  /**
   * Returns the name of the current client.
   * This is an empty string if the client has no name.
   */
  std::string get_client_name();

  /**
   * Returns information on all services, procedures, classes, properties etc. provided by the server.
   * Can be used by client libraries to automatically create functionality such as stubs.
   */
  krpc::schema::Services get_services();

  /**
   * Returns some information about the server, such as the version.
   */
  krpc::schema::Status get_status();

  /**
   * Remove a streaming request.
   */
  void remove_stream(uint64_t id);

  /**
   * Set the update rate for a stream in Hz.
   */
  void set_stream_rate(uint64_t id, float rate);

  /**
   * Start a previously added streaming request.
   */
  void start_stream(uint64_t id);

  /**
   * A list of RPC clients that are currently connected to the server.
   * Each entry in the list is a clients identifier, name and address.
   */
  std::vector<std::tuple<std::string, std::string, std::string> > clients();

  /**
   * Get the current game scene.
   */
  KRPC::GameScene current_game_scene();

  /**
   * Whether the game is paused.
   */
  bool paused();

  /**
   * Whether the game is paused.
   */
  void set_paused(bool value);

  ::krpc::Stream<::krpc::Event> add_event_stream(KRPC::Expression expression);

  ::krpc::Stream<krpc::schema::Stream> add_stream_stream(krpc::schema::ProcedureCall call, bool start);

  ::krpc::Stream<std::string> get_client_id_stream();

  ::krpc::Stream<std::string> get_client_name_stream();

  ::krpc::Stream<krpc::schema::Services> get_services_stream();

  ::krpc::Stream<krpc::schema::Status> get_status_stream();

  ::krpc::Stream<std::vector<std::tuple<std::string, std::string, std::string> >> clients_stream();

  ::krpc::Stream<KRPC::GameScene> current_game_scene_stream();

  ::krpc::Stream<bool> paused_stream();

  ::krpc::schema::ProcedureCall add_event_call(KRPC::Expression expression);

  ::krpc::schema::ProcedureCall add_stream_call(krpc::schema::ProcedureCall call, bool start);

  ::krpc::schema::ProcedureCall get_client_id_call();

  ::krpc::schema::ProcedureCall get_client_name_call();

  ::krpc::schema::ProcedureCall get_services_call();

  ::krpc::schema::ProcedureCall get_status_call();

  ::krpc::schema::ProcedureCall remove_stream_call(uint64_t id);

  ::krpc::schema::ProcedureCall set_stream_rate_call(uint64_t id, float rate);

  ::krpc::schema::ProcedureCall start_stream_call(uint64_t id);

  ::krpc::schema::ProcedureCall clients_call();

  ::krpc::schema::ProcedureCall current_game_scene_call();

  ::krpc::schema::ProcedureCall paused_call();

  ::krpc::schema::ProcedureCall set_paused_call(bool value);

  /**
   * A server side expression.
   */
  class Expression : public krpc::Object<Expression> {
   public:
    explicit Expression(Client* client = nullptr, uint64_t id = 0);

    /**
     * Numerical addition.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression add(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Applies an accumulator function over a sequence.
     * @return The accumulated value.
     * @param arg The collection.
     * @param func The accumulator function.
     */
    static KRPC::Expression aggregate(Client& client, KRPC::Expression arg, KRPC::Expression func);

    /**
     * Applies an accumulator function over a sequence, with a given seed.
     * @return The accumulated value.
     * @param arg The collection.
     * @param seed The seed value.
     * @param func The accumulator function.
     */
    static KRPC::Expression aggregate_with_seed(Client& client, KRPC::Expression arg, KRPC::Expression seed, KRPC::Expression func);

    /**
     * Determine whether all items in a collection satisfy a boolean predicate.
     * @return Whether all items satisfy the predicate.
     * @param arg The collection.
     * @param predicate The predicate function.
     */
    static KRPC::Expression all(Client& client, KRPC::Expression arg, KRPC::Expression predicate);

    /**
     * Boolean and operator.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression and_(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Determine whether any item in a collection satisfies a boolean predicate.
     * @return Whether any item satisfies the predicate.
     * @param arg The collection.
     * @param predicate The predicate function.
     */
    static KRPC::Expression any(Client& client, KRPC::Expression arg, KRPC::Expression predicate);

    /**
     * Minimum of all elements in a collection.
     * @return The minimum elements in the collection.
     * @param arg The list or set.
     */
    static KRPC::Expression average(Client& client, KRPC::Expression arg);

    /**
     * An RPC call.
     * @param call
     */
    static KRPC::Expression call(Client& client, krpc::schema::ProcedureCall call);

    /**
     * Perform a cast to the given type.
     * @param arg
     * @param type Type to cast the argument to.
     */
    static KRPC::Expression cast(Client& client, KRPC::Expression arg, KRPC::Type type);

    /**
     * Concatenate two sequences.
     * @return The first sequence followed by the second sequence.
     * @param arg1 The first sequence.
     * @param arg2 The second sequence.
     */
    static KRPC::Expression concat(Client& client, KRPC::Expression arg1, KRPC::Expression arg2);

    /**
     * A constant value of boolean type.
     * @param value
     */
    static KRPC::Expression constant_bool(Client& client, bool value);

    /**
     * A constant value of double precision floating point type.
     * @param value
     */
    static KRPC::Expression constant_double(Client& client, double value);

    /**
     * A constant value of single precision floating point type.
     * @param value
     */
    static KRPC::Expression constant_float(Client& client, float value);

    /**
     * A constant value of integer type.
     * @param value
     */
    static KRPC::Expression constant_int(Client& client, int32_t value);

    /**
     * A constant value of string type.
     * @param value
     */
    static KRPC::Expression constant_string(Client& client, std::string value);

    /**
     * Determine if a collection contains a value.
     * @return Whether the collection contains a value.
     * @param arg The collection.
     * @param value The value to look for.
     */
    static KRPC::Expression contains(Client& client, KRPC::Expression arg, KRPC::Expression value);

    /**
     * Number of elements in a collection.
     * @return The number of elements in the collection.
     * @param arg The list, set or dictionary.
     */
    static KRPC::Expression count(Client& client, KRPC::Expression arg);

    /**
     * Construct a dictionary, from a list of corresponding keys and values.
     * @return The dictionary.
     * @param keys The keys. Should all be of the same type.
     * @param values The values. Should all be of the same type.
     */
    static KRPC::Expression create_dictionary(Client& client, std::vector<KRPC::Expression> keys, std::vector<KRPC::Expression> values);

    /**
     * Construct a list.
     * @return The list.
     * @param values The value. Should all be of the same type.
     */
    static KRPC::Expression create_list(Client& client, std::vector<KRPC::Expression> values);

    /**
     * Construct a set.
     * @return The set.
     * @param values The values. Should all be of the same type.
     */
    static KRPC::Expression create_set(Client& client, std::set<KRPC::Expression> values);

    /**
     * Construct a tuple.
     * @return The tuple.
     * @param elements The elements.
     */
    static KRPC::Expression create_tuple(Client& client, std::vector<KRPC::Expression> elements);

    /**
     * Numerical division.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression divide(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Equality comparison.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression equal(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Boolean exclusive-or operator.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression exclusive_or(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * A function.
     * @return A function.
     * @param parameters The parameters of the function.
     * @param body The body of the function.
     */
    static KRPC::Expression function(Client& client, std::vector<KRPC::Expression> parameters, KRPC::Expression body);

    /**
     * Access an element in a tuple, list or dictionary.
     * @return The element.
     * @param arg The tuple, list or dictionary.
     * @param index The index of the element to access.
     * A zero indexed integer for a tuple or list, or a key for a dictionary.
     */
    static KRPC::Expression get(Client& client, KRPC::Expression arg, KRPC::Expression index);

    /**
     * Greater than numerical comparison.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression greater_than(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Greater than or equal numerical comparison.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression greater_than_or_equal(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * A function call.
     * @return A function call.
     * @param function The function to call.
     * @param args The arguments to call the function with.
     */
    static KRPC::Expression invoke(Client& client, KRPC::Expression function, std::map<std::string, KRPC::Expression> args);

    /**
     * Bitwise left shift.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression left_shift(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Less than numerical comparison.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression less_than(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Less than or equal numerical comparison.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression less_than_or_equal(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Maximum of all elements in a collection.
     * @return The maximum elements in the collection.
     * @param arg The list or set.
     */
    static KRPC::Expression max(Client& client, KRPC::Expression arg);

    /**
     * Minimum of all elements in a collection.
     * @return The minimum elements in the collection.
     * @param arg The list or set.
     */
    static KRPC::Expression min(Client& client, KRPC::Expression arg);

    /**
     * Numerical modulo operator.
     * @param arg0
     * @param arg1
     * @return The remainder of arg0 divided by arg1
     */
    static KRPC::Expression modulo(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Numerical multiplication.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression multiply(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Boolean negation operator.
     * @param arg
     */
    static KRPC::Expression not_(Client& client, KRPC::Expression arg);

    /**
     * Inequality comparison.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression not_equal(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Boolean or operator.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression or_(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Order a collection using a key function.
     * @return The ordered collection.
     * @param arg The collection to order.
     * @param key A function that takes a value from the collection and generates a key to sort on.
     */
    static KRPC::Expression order_by(Client& client, KRPC::Expression arg, KRPC::Expression key);

    /**
     * A named parameter of type double.
     * @return A named parameter.
     * @param name The name of the parameter.
     * @param type The type of the parameter.
     */
    static KRPC::Expression parameter(Client& client, std::string name, KRPC::Type type);

    /**
     * Numerical power operator.
     * @param arg0
     * @param arg1
     * @return arg0 raised to the power of arg1, with type of arg0
     */
    static KRPC::Expression power(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Bitwise right shift.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression right_shift(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Run a function on every element in the collection.
     * @return The modified collection.
     * @param arg The list or set.
     * @param func The function.
     */
    static KRPC::Expression select(Client& client, KRPC::Expression arg, KRPC::Expression func);

    /**
     * Numerical subtraction.
     * @param arg0
     * @param arg1
     */
    static KRPC::Expression subtract(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    /**
     * Sum all elements of a collection.
     * @return The sum of the elements in the collection.
     * @param arg The list or set.
     */
    static KRPC::Expression sum(Client& client, KRPC::Expression arg);

    /**
     * Convert a collection to a list.
     * @return The collection as a list.
     * @param arg The collection.
     */
    static KRPC::Expression to_list(Client& client, KRPC::Expression arg);

    /**
     * Convert a collection to a set.
     * @return The collection as a set.
     * @param arg The collection.
     */
    static KRPC::Expression to_set(Client& client, KRPC::Expression arg);

    /**
     * Run a function on every element in the collection.
     * @return The modified collection.
     * @param arg The list or set.
     * @param func The function.
     */
    static KRPC::Expression where(Client& client, KRPC::Expression arg, KRPC::Expression func);

    static ::krpc::Stream<KRPC::Expression> add_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> aggregate_stream(Client& client, KRPC::Expression arg, KRPC::Expression func);

    static ::krpc::Stream<KRPC::Expression> aggregate_with_seed_stream(Client& client, KRPC::Expression arg, KRPC::Expression seed, KRPC::Expression func);

    static ::krpc::Stream<KRPC::Expression> all_stream(Client& client, KRPC::Expression arg, KRPC::Expression predicate);

    static ::krpc::Stream<KRPC::Expression> and__stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> any_stream(Client& client, KRPC::Expression arg, KRPC::Expression predicate);

    static ::krpc::Stream<KRPC::Expression> average_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> call_stream(Client& client, krpc::schema::ProcedureCall call);

    static ::krpc::Stream<KRPC::Expression> cast_stream(Client& client, KRPC::Expression arg, KRPC::Type type);

    static ::krpc::Stream<KRPC::Expression> concat_stream(Client& client, KRPC::Expression arg1, KRPC::Expression arg2);

    static ::krpc::Stream<KRPC::Expression> constant_bool_stream(Client& client, bool value);

    static ::krpc::Stream<KRPC::Expression> constant_double_stream(Client& client, double value);

    static ::krpc::Stream<KRPC::Expression> constant_float_stream(Client& client, float value);

    static ::krpc::Stream<KRPC::Expression> constant_int_stream(Client& client, int32_t value);

    static ::krpc::Stream<KRPC::Expression> constant_string_stream(Client& client, std::string value);

    static ::krpc::Stream<KRPC::Expression> contains_stream(Client& client, KRPC::Expression arg, KRPC::Expression value);

    static ::krpc::Stream<KRPC::Expression> count_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> create_dictionary_stream(Client& client, std::vector<KRPC::Expression> keys, std::vector<KRPC::Expression> values);

    static ::krpc::Stream<KRPC::Expression> create_list_stream(Client& client, std::vector<KRPC::Expression> values);

    static ::krpc::Stream<KRPC::Expression> create_set_stream(Client& client, std::set<KRPC::Expression> values);

    static ::krpc::Stream<KRPC::Expression> create_tuple_stream(Client& client, std::vector<KRPC::Expression> elements);

    static ::krpc::Stream<KRPC::Expression> divide_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> equal_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> exclusive_or_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> function_stream(Client& client, std::vector<KRPC::Expression> parameters, KRPC::Expression body);

    static ::krpc::Stream<KRPC::Expression> get_stream(Client& client, KRPC::Expression arg, KRPC::Expression index);

    static ::krpc::Stream<KRPC::Expression> greater_than_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> greater_than_or_equal_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> invoke_stream(Client& client, KRPC::Expression function, std::map<std::string, KRPC::Expression> args);

    static ::krpc::Stream<KRPC::Expression> left_shift_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> less_than_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> less_than_or_equal_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> max_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> min_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> modulo_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> multiply_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> not__stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> not_equal_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> or__stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> order_by_stream(Client& client, KRPC::Expression arg, KRPC::Expression key);

    static ::krpc::Stream<KRPC::Expression> parameter_stream(Client& client, std::string name, KRPC::Type type);

    static ::krpc::Stream<KRPC::Expression> power_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> right_shift_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> select_stream(Client& client, KRPC::Expression arg, KRPC::Expression func);

    static ::krpc::Stream<KRPC::Expression> subtract_stream(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::Stream<KRPC::Expression> sum_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> to_list_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> to_set_stream(Client& client, KRPC::Expression arg);

    static ::krpc::Stream<KRPC::Expression> where_stream(Client& client, KRPC::Expression arg, KRPC::Expression func);

    static ::krpc::schema::ProcedureCall add_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall aggregate_call(Client& client, KRPC::Expression arg, KRPC::Expression func);

    static ::krpc::schema::ProcedureCall aggregate_with_seed_call(Client& client, KRPC::Expression arg, KRPC::Expression seed, KRPC::Expression func);

    static ::krpc::schema::ProcedureCall all_call(Client& client, KRPC::Expression arg, KRPC::Expression predicate);

    static ::krpc::schema::ProcedureCall and__call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall any_call(Client& client, KRPC::Expression arg, KRPC::Expression predicate);

    static ::krpc::schema::ProcedureCall average_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall call_call(Client& client, krpc::schema::ProcedureCall call);

    static ::krpc::schema::ProcedureCall cast_call(Client& client, KRPC::Expression arg, KRPC::Type type);

    static ::krpc::schema::ProcedureCall concat_call(Client& client, KRPC::Expression arg1, KRPC::Expression arg2);

    static ::krpc::schema::ProcedureCall constant_bool_call(Client& client, bool value);

    static ::krpc::schema::ProcedureCall constant_double_call(Client& client, double value);

    static ::krpc::schema::ProcedureCall constant_float_call(Client& client, float value);

    static ::krpc::schema::ProcedureCall constant_int_call(Client& client, int32_t value);

    static ::krpc::schema::ProcedureCall constant_string_call(Client& client, std::string value);

    static ::krpc::schema::ProcedureCall contains_call(Client& client, KRPC::Expression arg, KRPC::Expression value);

    static ::krpc::schema::ProcedureCall count_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall create_dictionary_call(Client& client, std::vector<KRPC::Expression> keys, std::vector<KRPC::Expression> values);

    static ::krpc::schema::ProcedureCall create_list_call(Client& client, std::vector<KRPC::Expression> values);

    static ::krpc::schema::ProcedureCall create_set_call(Client& client, std::set<KRPC::Expression> values);

    static ::krpc::schema::ProcedureCall create_tuple_call(Client& client, std::vector<KRPC::Expression> elements);

    static ::krpc::schema::ProcedureCall divide_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall equal_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall exclusive_or_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall function_call(Client& client, std::vector<KRPC::Expression> parameters, KRPC::Expression body);

    static ::krpc::schema::ProcedureCall get_call(Client& client, KRPC::Expression arg, KRPC::Expression index);

    static ::krpc::schema::ProcedureCall greater_than_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall greater_than_or_equal_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall invoke_call(Client& client, KRPC::Expression function, std::map<std::string, KRPC::Expression> args);

    static ::krpc::schema::ProcedureCall left_shift_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall less_than_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall less_than_or_equal_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall max_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall min_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall modulo_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall multiply_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall not__call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall not_equal_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall or__call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall order_by_call(Client& client, KRPC::Expression arg, KRPC::Expression key);

    static ::krpc::schema::ProcedureCall parameter_call(Client& client, std::string name, KRPC::Type type);

    static ::krpc::schema::ProcedureCall power_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall right_shift_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall select_call(Client& client, KRPC::Expression arg, KRPC::Expression func);

    static ::krpc::schema::ProcedureCall subtract_call(Client& client, KRPC::Expression arg0, KRPC::Expression arg1);

    static ::krpc::schema::ProcedureCall sum_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall to_list_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall to_set_call(Client& client, KRPC::Expression arg);

    static ::krpc::schema::ProcedureCall where_call(Client& client, KRPC::Expression arg, KRPC::Expression func);
  };

  /**
   * A server side expression.
   */
  class Type : public krpc::Object<Type> {
   public:
    explicit Type(Client* client = nullptr, uint64_t id = 0);

    /**
     * Bool type.
     */
    static KRPC::Type bool_(Client& client);

    /**
     * Double type.
     */
    static KRPC::Type double_(Client& client);

    /**
     * Float type.
     */
    static KRPC::Type float_(Client& client);

    /**
     * Int type.
     */
    static KRPC::Type int_(Client& client);

    /**
     * String type.
     */
    static KRPC::Type string(Client& client);

    static ::krpc::Stream<KRPC::Type> bool__stream(Client& client);

    static ::krpc::Stream<KRPC::Type> double__stream(Client& client);

    static ::krpc::Stream<KRPC::Type> float__stream(Client& client);

    static ::krpc::Stream<KRPC::Type> int__stream(Client& client);

    static ::krpc::Stream<KRPC::Type> string_stream(Client& client);

    static ::krpc::schema::ProcedureCall bool__call(Client& client);

    static ::krpc::schema::ProcedureCall double__call(Client& client);

    static ::krpc::schema::ProcedureCall float__call(Client& client);

    static ::krpc::schema::ProcedureCall int__call(Client& client);

    static ::krpc::schema::ProcedureCall string_call(Client& client);
  };
};

}  // namespace services

namespace encoder {

  inline std::string encode(const services::KRPC::GameScene& value) {
    return krpc::encoder::encode(static_cast<int32_t>(value));
  }

}  // namespace encoder

namespace decoder {

  inline void decode(services::KRPC::GameScene& value, const std::string& data, Client* client) {
    int32_t x;
    decode(x, data, client);
    value = static_cast<services::KRPC::GameScene>(x);
  }

}  // namespace decoder

namespace services {

inline KRPC::KRPC(Client* client):
  Service(client) {
  client->add_exception_thrower(
    "KRPC", "ArgumentException",
    [] (const std::string& msg) { throw ArgumentException(msg); });
  client->add_exception_thrower(
    "KRPC", "ArgumentNullException",
    [] (const std::string& msg) { throw ArgumentNullException(msg); });
  client->add_exception_thrower(
    "KRPC", "ArgumentOutOfRangeException",
    [] (const std::string& msg) { throw ArgumentOutOfRangeException(msg); });
  client->add_exception_thrower(
    "KRPC", "InvalidOperationException",
    [] (const std::string& msg) { throw InvalidOperationException(msg); });
}

inline ::krpc::Event KRPC::add_event(KRPC::Expression expression) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(expression));
  std::string _data = this->_client->invoke("KRPC", "AddEvent", _args);
  ::krpc::Event _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline krpc::schema::Stream KRPC::add_stream(krpc::schema::ProcedureCall call, bool start = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(call));
  _args.push_back(encoder::encode(start));
  std::string _data = this->_client->invoke("KRPC", "AddStream", _args);
  krpc::schema::Stream _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string KRPC::get_client_id() {
  std::string _data = this->_client->invoke("KRPC", "GetClientID");
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::string KRPC::get_client_name() {
  std::string _data = this->_client->invoke("KRPC", "GetClientName");
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline krpc::schema::Services KRPC::get_services() {
  std::string _data = this->_client->invoke("KRPC", "GetServices");
  krpc::schema::Services _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline krpc::schema::Status KRPC::get_status() {
  std::string _data = this->_client->invoke("KRPC", "GetStatus");
  krpc::schema::Status _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KRPC::remove_stream(uint64_t id) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  this->_client->invoke("KRPC", "RemoveStream", _args);
}

inline void KRPC::set_stream_rate(uint64_t id, float rate) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  _args.push_back(encoder::encode(rate));
  this->_client->invoke("KRPC", "SetStreamRate", _args);
}

inline void KRPC::start_stream(uint64_t id) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  this->_client->invoke("KRPC", "StartStream", _args);
}

inline std::vector<std::tuple<std::string, std::string, std::string> > KRPC::clients() {
  std::string _data = this->_client->invoke("KRPC", "get_Clients");
  std::vector<std::tuple<std::string, std::string, std::string> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline KRPC::GameScene KRPC::current_game_scene() {
  std::string _data = this->_client->invoke("KRPC", "get_CurrentGameScene");
  KRPC::GameScene _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool KRPC::paused() {
  std::string _data = this->_client->invoke("KRPC", "get_Paused");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void KRPC::set_paused(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  this->_client->invoke("KRPC", "set_Paused", _args);
}

inline ::krpc::Stream<::krpc::Event> KRPC::add_event_stream(KRPC::Expression expression) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(expression));
  return ::krpc::Stream<::krpc::Event>(this->_client, this->_client->build_call("KRPC", "AddEvent", _args));
}

inline ::krpc::Stream<krpc::schema::Stream> KRPC::add_stream_stream(krpc::schema::ProcedureCall call, bool start = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(call));
  _args.push_back(encoder::encode(start));
  return ::krpc::Stream<krpc::schema::Stream>(this->_client, this->_client->build_call("KRPC", "AddStream", _args));
}

inline ::krpc::Stream<std::string> KRPC::get_client_id_stream() {
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("KRPC", "GetClientID"));
}

inline ::krpc::Stream<std::string> KRPC::get_client_name_stream() {
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("KRPC", "GetClientName"));
}

inline ::krpc::Stream<krpc::schema::Services> KRPC::get_services_stream() {
  return ::krpc::Stream<krpc::schema::Services>(this->_client, this->_client->build_call("KRPC", "GetServices"));
}

inline ::krpc::Stream<krpc::schema::Status> KRPC::get_status_stream() {
  return ::krpc::Stream<krpc::schema::Status>(this->_client, this->_client->build_call("KRPC", "GetStatus"));
}

inline ::krpc::Stream<std::vector<std::tuple<std::string, std::string, std::string> >> KRPC::clients_stream() {
  return ::krpc::Stream<std::vector<std::tuple<std::string, std::string, std::string> >>(this->_client, this->_client->build_call("KRPC", "get_Clients"));
}

inline ::krpc::Stream<KRPC::GameScene> KRPC::current_game_scene_stream() {
  return ::krpc::Stream<KRPC::GameScene>(this->_client, this->_client->build_call("KRPC", "get_CurrentGameScene"));
}

inline ::krpc::Stream<bool> KRPC::paused_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("KRPC", "get_Paused"));
}

inline ::krpc::schema::ProcedureCall KRPC::add_event_call(KRPC::Expression expression) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(expression));
  return this->_client->build_call("KRPC", "AddEvent", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::add_stream_call(krpc::schema::ProcedureCall call, bool start = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(call));
  _args.push_back(encoder::encode(start));
  return this->_client->build_call("KRPC", "AddStream", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::get_client_id_call() {
  return this->_client->build_call("KRPC", "GetClientID");
}

inline ::krpc::schema::ProcedureCall KRPC::get_client_name_call() {
  return this->_client->build_call("KRPC", "GetClientName");
}

inline ::krpc::schema::ProcedureCall KRPC::get_services_call() {
  return this->_client->build_call("KRPC", "GetServices");
}

inline ::krpc::schema::ProcedureCall KRPC::get_status_call() {
  return this->_client->build_call("KRPC", "GetStatus");
}

inline ::krpc::schema::ProcedureCall KRPC::remove_stream_call(uint64_t id) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  return this->_client->build_call("KRPC", "RemoveStream", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::set_stream_rate_call(uint64_t id, float rate) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  _args.push_back(encoder::encode(rate));
  return this->_client->build_call("KRPC", "SetStreamRate", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::start_stream_call(uint64_t id) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(id));
  return this->_client->build_call("KRPC", "StartStream", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::clients_call() {
  return this->_client->build_call("KRPC", "get_Clients");
}

inline ::krpc::schema::ProcedureCall KRPC::current_game_scene_call() {
  return this->_client->build_call("KRPC", "get_CurrentGameScene");
}

inline ::krpc::schema::ProcedureCall KRPC::paused_call() {
  return this->_client->build_call("KRPC", "get_Paused");
}

inline ::krpc::schema::ProcedureCall KRPC::set_paused_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("KRPC", "set_Paused", _args);
}

inline KRPC::Expression::Expression(Client* client, uint64_t id):
  Object(client, "KRPC::Expression", id) {}

inline KRPC::Expression KRPC::Expression::add(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Add", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::aggregate(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  std::string _data = _client.invoke("KRPC", "Expression_static_Aggregate", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::aggregate_with_seed(Client& _client, KRPC::Expression arg, KRPC::Expression seed, KRPC::Expression func) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(seed));
  _args.push_back(encoder::encode(func));
  std::string _data = _client.invoke("KRPC", "Expression_static_AggregateWithSeed", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::all(Client& _client, KRPC::Expression arg, KRPC::Expression predicate) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(predicate));
  std::string _data = _client.invoke("KRPC", "Expression_static_All", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::and_(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_And", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::any(Client& _client, KRPC::Expression arg, KRPC::Expression predicate) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(predicate));
  std::string _data = _client.invoke("KRPC", "Expression_static_Any", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::average(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_Average", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::call(Client& _client, krpc::schema::ProcedureCall call) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(call));
  std::string _data = _client.invoke("KRPC", "Expression_static_Call", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::cast(Client& _client, KRPC::Expression arg, KRPC::Type type) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(type));
  std::string _data = _client.invoke("KRPC", "Expression_static_Cast", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::concat(Client& _client, KRPC::Expression arg1, KRPC::Expression arg2) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg1));
  _args.push_back(encoder::encode(arg2));
  std::string _data = _client.invoke("KRPC", "Expression_static_Concat", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::constant_bool(Client& _client, bool value) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  std::string _data = _client.invoke("KRPC", "Expression_static_ConstantBool", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::constant_double(Client& _client, double value) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  std::string _data = _client.invoke("KRPC", "Expression_static_ConstantDouble", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::constant_float(Client& _client, float value) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  std::string _data = _client.invoke("KRPC", "Expression_static_ConstantFloat", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::constant_int(Client& _client, int32_t value) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  std::string _data = _client.invoke("KRPC", "Expression_static_ConstantInt", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::constant_string(Client& _client, std::string value) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  std::string _data = _client.invoke("KRPC", "Expression_static_ConstantString", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::contains(Client& _client, KRPC::Expression arg, KRPC::Expression value) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(value));
  std::string _data = _client.invoke("KRPC", "Expression_static_Contains", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::count(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_Count", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::create_dictionary(Client& _client, std::vector<KRPC::Expression> keys, std::vector<KRPC::Expression> values) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(keys));
  _args.push_back(encoder::encode(values));
  std::string _data = _client.invoke("KRPC", "Expression_static_CreateDictionary", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::create_list(Client& _client, std::vector<KRPC::Expression> values) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(values));
  std::string _data = _client.invoke("KRPC", "Expression_static_CreateList", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::create_set(Client& _client, std::set<KRPC::Expression> values) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(values));
  std::string _data = _client.invoke("KRPC", "Expression_static_CreateSet", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::create_tuple(Client& _client, std::vector<KRPC::Expression> elements) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(elements));
  std::string _data = _client.invoke("KRPC", "Expression_static_CreateTuple", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::divide(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Divide", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::equal(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Equal", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::exclusive_or(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_ExclusiveOr", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::function(Client& _client, std::vector<KRPC::Expression> parameters, KRPC::Expression body) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(parameters));
  _args.push_back(encoder::encode(body));
  std::string _data = _client.invoke("KRPC", "Expression_static_Function", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::get(Client& _client, KRPC::Expression arg, KRPC::Expression index) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(index));
  std::string _data = _client.invoke("KRPC", "Expression_static_Get", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::greater_than(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_GreaterThan", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::greater_than_or_equal(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_GreaterThanOrEqual", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::invoke(Client& _client, KRPC::Expression function, std::map<std::string, KRPC::Expression> args) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(function));
  _args.push_back(encoder::encode(args));
  std::string _data = _client.invoke("KRPC", "Expression_static_Invoke", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::left_shift(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_LeftShift", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::less_than(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_LessThan", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::less_than_or_equal(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_LessThanOrEqual", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::max(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_Max", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::min(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_Min", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::modulo(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Modulo", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::multiply(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Multiply", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::not_(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_Not", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::not_equal(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_NotEqual", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::or_(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Or", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::order_by(Client& _client, KRPC::Expression arg, KRPC::Expression key) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(key));
  std::string _data = _client.invoke("KRPC", "Expression_static_OrderBy", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::parameter(Client& _client, std::string name, KRPC::Type type) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(type));
  std::string _data = _client.invoke("KRPC", "Expression_static_Parameter", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::power(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Power", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::right_shift(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_RightShift", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::select(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  std::string _data = _client.invoke("KRPC", "Expression_static_Select", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::subtract(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  std::string _data = _client.invoke("KRPC", "Expression_static_Subtract", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::sum(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_Sum", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::to_list(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_ToList", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::to_set(Client& _client, KRPC::Expression arg) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  std::string _data = _client.invoke("KRPC", "Expression_static_ToSet", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Expression KRPC::Expression::where(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
    std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  std::string _data = _client.invoke("KRPC", "Expression_static_Where", _args);
    KRPC::Expression _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::add_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Add", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::aggregate_stream(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Aggregate", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::aggregate_with_seed_stream(Client& _client, KRPC::Expression arg, KRPC::Expression seed, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(seed));
  _args.push_back(encoder::encode(func));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_AggregateWithSeed", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::all_stream(Client& _client, KRPC::Expression arg, KRPC::Expression predicate) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(predicate));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_All", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::and__stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_And", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::any_stream(Client& _client, KRPC::Expression arg, KRPC::Expression predicate) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(predicate));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Any", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::average_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Average", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::call_stream(Client& _client, krpc::schema::ProcedureCall call) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(call));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Call", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::cast_stream(Client& _client, KRPC::Expression arg, KRPC::Type type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(type));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Cast", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::concat_stream(Client& _client, KRPC::Expression arg1, KRPC::Expression arg2) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg1));
  _args.push_back(encoder::encode(arg2));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Concat", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::constant_bool_stream(Client& _client, bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ConstantBool", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::constant_double_stream(Client& _client, double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ConstantDouble", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::constant_float_stream(Client& _client, float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ConstantFloat", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::constant_int_stream(Client& _client, int32_t value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ConstantInt", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::constant_string_stream(Client& _client, std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ConstantString", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::contains_stream(Client& _client, KRPC::Expression arg, KRPC::Expression value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(value));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Contains", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::count_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Count", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::create_dictionary_stream(Client& _client, std::vector<KRPC::Expression> keys, std::vector<KRPC::Expression> values) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(keys));
  _args.push_back(encoder::encode(values));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_CreateDictionary", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::create_list_stream(Client& _client, std::vector<KRPC::Expression> values) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(values));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_CreateList", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::create_set_stream(Client& _client, std::set<KRPC::Expression> values) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(values));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_CreateSet", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::create_tuple_stream(Client& _client, std::vector<KRPC::Expression> elements) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(elements));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_CreateTuple", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::divide_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Divide", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::equal_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Equal", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::exclusive_or_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ExclusiveOr", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::function_stream(Client& _client, std::vector<KRPC::Expression> parameters, KRPC::Expression body) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(parameters));
  _args.push_back(encoder::encode(body));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Function", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::get_stream(Client& _client, KRPC::Expression arg, KRPC::Expression index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(index));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Get", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::greater_than_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_GreaterThan", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::greater_than_or_equal_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_GreaterThanOrEqual", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::invoke_stream(Client& _client, KRPC::Expression function, std::map<std::string, KRPC::Expression> args) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(function));
  _args.push_back(encoder::encode(args));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Invoke", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::left_shift_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_LeftShift", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::less_than_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_LessThan", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::less_than_or_equal_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_LessThanOrEqual", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::max_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Max", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::min_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Min", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::modulo_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Modulo", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::multiply_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Multiply", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::not__stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Not", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::not_equal_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_NotEqual", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::or__stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Or", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::order_by_stream(Client& _client, KRPC::Expression arg, KRPC::Expression key) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(key));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_OrderBy", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::parameter_stream(Client& _client, std::string name, KRPC::Type type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(type));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Parameter", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::power_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Power", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::right_shift_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_RightShift", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::select_stream(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Select", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::subtract_stream(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Subtract", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::sum_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Sum", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::to_list_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ToList", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::to_set_stream(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_ToSet", _args));
}

inline ::krpc::Stream<KRPC::Expression> KRPC::Expression::where_stream(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  return ::krpc::Stream<KRPC::Expression>(&_client, _client.build_call("KRPC", "Expression_static_Where", _args));
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::add_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Add", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::aggregate_call(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  return _client.build_call("KRPC", "Expression_static_Aggregate", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::aggregate_with_seed_call(Client& _client, KRPC::Expression arg, KRPC::Expression seed, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(seed));
  _args.push_back(encoder::encode(func));
  return _client.build_call("KRPC", "Expression_static_AggregateWithSeed", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::all_call(Client& _client, KRPC::Expression arg, KRPC::Expression predicate) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(predicate));
  return _client.build_call("KRPC", "Expression_static_All", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::and__call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_And", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::any_call(Client& _client, KRPC::Expression arg, KRPC::Expression predicate) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(predicate));
  return _client.build_call("KRPC", "Expression_static_Any", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::average_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_Average", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::call_call(Client& _client, krpc::schema::ProcedureCall call) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(call));
  return _client.build_call("KRPC", "Expression_static_Call", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::cast_call(Client& _client, KRPC::Expression arg, KRPC::Type type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(type));
  return _client.build_call("KRPC", "Expression_static_Cast", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::concat_call(Client& _client, KRPC::Expression arg1, KRPC::Expression arg2) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg1));
  _args.push_back(encoder::encode(arg2));
  return _client.build_call("KRPC", "Expression_static_Concat", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::constant_bool_call(Client& _client, bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return _client.build_call("KRPC", "Expression_static_ConstantBool", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::constant_double_call(Client& _client, double value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return _client.build_call("KRPC", "Expression_static_ConstantDouble", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::constant_float_call(Client& _client, float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return _client.build_call("KRPC", "Expression_static_ConstantFloat", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::constant_int_call(Client& _client, int32_t value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return _client.build_call("KRPC", "Expression_static_ConstantInt", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::constant_string_call(Client& _client, std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(value));
  return _client.build_call("KRPC", "Expression_static_ConstantString", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::contains_call(Client& _client, KRPC::Expression arg, KRPC::Expression value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(value));
  return _client.build_call("KRPC", "Expression_static_Contains", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::count_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_Count", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::create_dictionary_call(Client& _client, std::vector<KRPC::Expression> keys, std::vector<KRPC::Expression> values) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(keys));
  _args.push_back(encoder::encode(values));
  return _client.build_call("KRPC", "Expression_static_CreateDictionary", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::create_list_call(Client& _client, std::vector<KRPC::Expression> values) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(values));
  return _client.build_call("KRPC", "Expression_static_CreateList", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::create_set_call(Client& _client, std::set<KRPC::Expression> values) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(values));
  return _client.build_call("KRPC", "Expression_static_CreateSet", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::create_tuple_call(Client& _client, std::vector<KRPC::Expression> elements) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(elements));
  return _client.build_call("KRPC", "Expression_static_CreateTuple", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::divide_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Divide", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::equal_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Equal", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::exclusive_or_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_ExclusiveOr", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::function_call(Client& _client, std::vector<KRPC::Expression> parameters, KRPC::Expression body) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(parameters));
  _args.push_back(encoder::encode(body));
  return _client.build_call("KRPC", "Expression_static_Function", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::get_call(Client& _client, KRPC::Expression arg, KRPC::Expression index) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(index));
  return _client.build_call("KRPC", "Expression_static_Get", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::greater_than_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_GreaterThan", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::greater_than_or_equal_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_GreaterThanOrEqual", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::invoke_call(Client& _client, KRPC::Expression function, std::map<std::string, KRPC::Expression> args) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(function));
  _args.push_back(encoder::encode(args));
  return _client.build_call("KRPC", "Expression_static_Invoke", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::left_shift_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_LeftShift", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::less_than_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_LessThan", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::less_than_or_equal_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_LessThanOrEqual", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::max_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_Max", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::min_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_Min", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::modulo_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Modulo", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::multiply_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Multiply", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::not__call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_Not", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::not_equal_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_NotEqual", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::or__call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Or", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::order_by_call(Client& _client, KRPC::Expression arg, KRPC::Expression key) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(key));
  return _client.build_call("KRPC", "Expression_static_OrderBy", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::parameter_call(Client& _client, std::string name, KRPC::Type type) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(name));
  _args.push_back(encoder::encode(type));
  return _client.build_call("KRPC", "Expression_static_Parameter", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::power_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Power", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::right_shift_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_RightShift", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::select_call(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  return _client.build_call("KRPC", "Expression_static_Select", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::subtract_call(Client& _client, KRPC::Expression arg0, KRPC::Expression arg1) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg0));
  _args.push_back(encoder::encode(arg1));
  return _client.build_call("KRPC", "Expression_static_Subtract", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::sum_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_Sum", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::to_list_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_ToList", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::to_set_call(Client& _client, KRPC::Expression arg) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  return _client.build_call("KRPC", "Expression_static_ToSet", _args);
}

inline ::krpc::schema::ProcedureCall KRPC::Expression::where_call(Client& _client, KRPC::Expression arg, KRPC::Expression func) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(arg));
  _args.push_back(encoder::encode(func));
  return _client.build_call("KRPC", "Expression_static_Where", _args);
}

inline KRPC::Type::Type(Client* client, uint64_t id):
  Object(client, "KRPC::Type", id) {}

inline KRPC::Type KRPC::Type::bool_(Client& _client) {
  std::string _data = _client.invoke("KRPC", "Type_static_Bool");
    KRPC::Type _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Type KRPC::Type::double_(Client& _client) {
  std::string _data = _client.invoke("KRPC", "Type_static_Double");
    KRPC::Type _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Type KRPC::Type::float_(Client& _client) {
  std::string _data = _client.invoke("KRPC", "Type_static_Float");
    KRPC::Type _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Type KRPC::Type::int_(Client& _client) {
  std::string _data = _client.invoke("KRPC", "Type_static_Int");
    KRPC::Type _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline KRPC::Type KRPC::Type::string(Client& _client) {
  std::string _data = _client.invoke("KRPC", "Type_static_String");
    KRPC::Type _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<KRPC::Type> KRPC::Type::bool__stream(Client& _client) {
  return ::krpc::Stream<KRPC::Type>(&_client, _client.build_call("KRPC", "Type_static_Bool"));
}

inline ::krpc::Stream<KRPC::Type> KRPC::Type::double__stream(Client& _client) {
  return ::krpc::Stream<KRPC::Type>(&_client, _client.build_call("KRPC", "Type_static_Double"));
}

inline ::krpc::Stream<KRPC::Type> KRPC::Type::float__stream(Client& _client) {
  return ::krpc::Stream<KRPC::Type>(&_client, _client.build_call("KRPC", "Type_static_Float"));
}

inline ::krpc::Stream<KRPC::Type> KRPC::Type::int__stream(Client& _client) {
  return ::krpc::Stream<KRPC::Type>(&_client, _client.build_call("KRPC", "Type_static_Int"));
}

inline ::krpc::Stream<KRPC::Type> KRPC::Type::string_stream(Client& _client) {
  return ::krpc::Stream<KRPC::Type>(&_client, _client.build_call("KRPC", "Type_static_String"));
}

inline ::krpc::schema::ProcedureCall KRPC::Type::bool__call(Client& _client) {
  return _client.build_call("KRPC", "Type_static_Bool");
}

inline ::krpc::schema::ProcedureCall KRPC::Type::double__call(Client& _client) {
  return _client.build_call("KRPC", "Type_static_Double");
}

inline ::krpc::schema::ProcedureCall KRPC::Type::float__call(Client& _client) {
  return _client.build_call("KRPC", "Type_static_Float");
}

inline ::krpc::schema::ProcedureCall KRPC::Type::int__call(Client& _client) {
  return _client.build_call("KRPC", "Type_static_Int");
}

inline ::krpc::schema::ProcedureCall KRPC::Type::string_call(Client& _client) {
  return _client.build_call("KRPC", "Type_static_String");
}
}  // namespace services

}  // namespace krpc
