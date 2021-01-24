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

class Drawing : public Service {
 public:
  explicit Drawing(Client* client);

  // Class forward declarations
  class Line;
  class Polygon;
  class Text;

  /**
   * Draw a direction vector in the scene, from the center of mass of the active vessel.
   * @param direction Direction to draw the line in.
   * @param referenceFrame Reference frame that the direction is in.
   * @param length The length of the line.
   * @param visible Whether the line is visible.
   */
  Drawing::Line add_direction(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length, bool visible);

  /**
   * Draw a line in the scene.
   * @param start Position of the start of the line.
   * @param end Position of the end of the line.
   * @param referenceFrame Reference frame that the positions are in.
   * @param visible Whether the line is visible.
   */
  Drawing::Line add_line(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  /**
   * Draw a polygon in the scene, defined by a list of vertices.
   * @param vertices Vertices of the polygon.
   * @param referenceFrame Reference frame that the vertices are in.
   * @param visible Whether the polygon is visible.
   */
  Drawing::Polygon add_polygon(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  /**
   * Draw text in the scene.
   * @param text The string to draw.
   * @param referenceFrame Reference frame that the text position is in.
   * @param position Position of the text.
   * @param rotation Rotation of the text, as a quaternion.
   * @param visible Whether the text is visible.
   */
  Drawing::Text add_text(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible);

  /**
   * Remove all objects being drawn.
   * @param clientOnly If true, only remove objects created by the calling client.
   */
  void clear(bool client_only);

  ::krpc::Stream<Drawing::Line> add_direction_stream(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length, bool visible);

  ::krpc::Stream<Drawing::Line> add_line_stream(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  ::krpc::Stream<Drawing::Polygon> add_polygon_stream(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  ::krpc::Stream<Drawing::Text> add_text_stream(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible);

  ::krpc::schema::ProcedureCall add_direction_call(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length, bool visible);

  ::krpc::schema::ProcedureCall add_line_call(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  ::krpc::schema::ProcedureCall add_polygon_call(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible);

  ::krpc::schema::ProcedureCall add_text_call(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible);

  ::krpc::schema::ProcedureCall clear_call(bool client_only);

  /**
   * A line. Created using Drawing::add_line.
   */
  class Line : public krpc::Object<Line> {
   public:
    explicit Line(Client* client = nullptr, uint64_t id = 0);

    /**
     * Remove the object.
     */
    void remove();

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    /**
     * End position of the line.
     */
    std::tuple<double, double, double> end();

    /**
     * End position of the line.
     */
    void set_end(std::tuple<double, double, double> value);

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    std::string material();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    void set_material(std::string value);

    /**
     * Reference frame for the positions of the object.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * Reference frame for the positions of the object.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * Start position of the line.
     */
    std::tuple<double, double, double> start();

    /**
     * Start position of the line.
     */
    void set_start(std::tuple<double, double, double> value);

    /**
     * Set the thickness
     */
    float thickness();

    /**
     * Set the thickness
     */
    void set_thickness(float value);

    /**
     * Whether the object is visible.
     */
    bool visible();

    /**
     * Whether the object is visible.
     */
    void set_visible(bool value);

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<std::tuple<double, double, double>> end_stream();

    ::krpc::Stream<std::string> material_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double>> start_stream();

    ::krpc::Stream<float> thickness_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::schema::ProcedureCall remove_call();

    ::krpc::schema::ProcedureCall color_call();

    ::krpc::schema::ProcedureCall set_color_call(std::tuple<double, double, double> value);

    ::krpc::schema::ProcedureCall end_call();

    ::krpc::schema::ProcedureCall set_end_call(std::tuple<double, double, double> value);

    ::krpc::schema::ProcedureCall material_call();

    ::krpc::schema::ProcedureCall set_material_call(std::string value);

    ::krpc::schema::ProcedureCall reference_frame_call();

    ::krpc::schema::ProcedureCall set_reference_frame_call(SpaceCenter::ReferenceFrame value);

    ::krpc::schema::ProcedureCall start_call();

    ::krpc::schema::ProcedureCall set_start_call(std::tuple<double, double, double> value);

    ::krpc::schema::ProcedureCall thickness_call();

    ::krpc::schema::ProcedureCall set_thickness_call(float value);

    ::krpc::schema::ProcedureCall visible_call();

    ::krpc::schema::ProcedureCall set_visible_call(bool value);
  };

  /**
   * A polygon. Created using Drawing::add_polygon.
   */
  class Polygon : public krpc::Object<Polygon> {
   public:
    explicit Polygon(Client* client = nullptr, uint64_t id = 0);

    /**
     * Remove the object.
     */
    void remove();

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    std::string material();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    void set_material(std::string value);

    /**
     * Reference frame for the positions of the object.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * Reference frame for the positions of the object.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * Set the thickness
     */
    float thickness();

    /**
     * Set the thickness
     */
    void set_thickness(float value);

    /**
     * Vertices for the polygon.
     */
    std::vector<std::tuple<double, double, double> > vertices();

    /**
     * Vertices for the polygon.
     */
    void set_vertices(std::vector<std::tuple<double, double, double> > value);

    /**
     * Whether the object is visible.
     */
    bool visible();

    /**
     * Whether the object is visible.
     */
    void set_visible(bool value);

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<std::string> material_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<float> thickness_stream();

    ::krpc::Stream<std::vector<std::tuple<double, double, double> >> vertices_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::schema::ProcedureCall remove_call();

    ::krpc::schema::ProcedureCall color_call();

    ::krpc::schema::ProcedureCall set_color_call(std::tuple<double, double, double> value);

    ::krpc::schema::ProcedureCall material_call();

    ::krpc::schema::ProcedureCall set_material_call(std::string value);

    ::krpc::schema::ProcedureCall reference_frame_call();

    ::krpc::schema::ProcedureCall set_reference_frame_call(SpaceCenter::ReferenceFrame value);

    ::krpc::schema::ProcedureCall thickness_call();

    ::krpc::schema::ProcedureCall set_thickness_call(float value);

    ::krpc::schema::ProcedureCall vertices_call();

    ::krpc::schema::ProcedureCall set_vertices_call(std::vector<std::tuple<double, double, double> > value);

    ::krpc::schema::ProcedureCall visible_call();

    ::krpc::schema::ProcedureCall set_visible_call(bool value);
  };

  /**
   * Text. Created using Drawing::add_text.
   */
  class Text : public krpc::Object<Text> {
   public:
    explicit Text(Client* client = nullptr, uint64_t id = 0);

    /**
     * Remove the object.
     */
    void remove();

    /**
     * A list of all available fonts.
     */
    static std::vector<std::string> available_fonts(Client& client);

    /**
     * Alignment.
     */
    UI::TextAlignment alignment();

    /**
     * Alignment.
     */
    void set_alignment(UI::TextAlignment value);

    /**
     * Anchor.
     */
    UI::TextAnchor anchor();

    /**
     * Anchor.
     */
    void set_anchor(UI::TextAnchor value);

    /**
     * Character size.
     */
    float character_size();

    /**
     * Character size.
     */
    void set_character_size(float value);

    /**
     * Set the color
     */
    std::tuple<double, double, double> color();

    /**
     * Set the color
     */
    void set_color(std::tuple<double, double, double> value);

    /**
     * The text string
     */
    std::string content();

    /**
     * The text string
     */
    void set_content(std::string value);

    /**
     * Name of the font
     */
    std::string font();

    /**
     * Name of the font
     */
    void set_font(std::string value);

    /**
     * Line spacing.
     */
    float line_spacing();

    /**
     * Line spacing.
     */
    void set_line_spacing(float value);

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    std::string material();

    /**
     * Material used to render the object.
     * Creates the material from a shader with the given name.
     */
    void set_material(std::string value);

    /**
     * Position of the text.
     */
    std::tuple<double, double, double> position();

    /**
     * Position of the text.
     */
    void set_position(std::tuple<double, double, double> value);

    /**
     * Reference frame for the positions of the object.
     */
    SpaceCenter::ReferenceFrame reference_frame();

    /**
     * Reference frame for the positions of the object.
     */
    void set_reference_frame(SpaceCenter::ReferenceFrame value);

    /**
     * Rotation of the text as a quaternion.
     */
    std::tuple<double, double, double, double> rotation();

    /**
     * Rotation of the text as a quaternion.
     */
    void set_rotation(std::tuple<double, double, double, double> value);

    /**
     * Font size.
     */
    int32_t size();

    /**
     * Font size.
     */
    void set_size(int32_t value);

    /**
     * Font style.
     */
    UI::FontStyle style();

    /**
     * Font style.
     */
    void set_style(UI::FontStyle value);

    /**
     * Whether the object is visible.
     */
    bool visible();

    /**
     * Whether the object is visible.
     */
    void set_visible(bool value);

    static ::krpc::Stream<std::vector<std::string>> available_fonts_stream(Client& client);

    ::krpc::Stream<UI::TextAlignment> alignment_stream();

    ::krpc::Stream<UI::TextAnchor> anchor_stream();

    ::krpc::Stream<float> character_size_stream();

    ::krpc::Stream<std::tuple<double, double, double>> color_stream();

    ::krpc::Stream<std::string> content_stream();

    ::krpc::Stream<std::string> font_stream();

    ::krpc::Stream<float> line_spacing_stream();

    ::krpc::Stream<std::string> material_stream();

    ::krpc::Stream<std::tuple<double, double, double>> position_stream();

    ::krpc::Stream<SpaceCenter::ReferenceFrame> reference_frame_stream();

    ::krpc::Stream<std::tuple<double, double, double, double>> rotation_stream();

    ::krpc::Stream<int32_t> size_stream();

    ::krpc::Stream<UI::FontStyle> style_stream();

    ::krpc::Stream<bool> visible_stream();

    ::krpc::schema::ProcedureCall remove_call();

    static ::krpc::schema::ProcedureCall available_fonts_call(Client& client);

    ::krpc::schema::ProcedureCall alignment_call();

    ::krpc::schema::ProcedureCall set_alignment_call(UI::TextAlignment value);

    ::krpc::schema::ProcedureCall anchor_call();

    ::krpc::schema::ProcedureCall set_anchor_call(UI::TextAnchor value);

    ::krpc::schema::ProcedureCall character_size_call();

    ::krpc::schema::ProcedureCall set_character_size_call(float value);

    ::krpc::schema::ProcedureCall color_call();

    ::krpc::schema::ProcedureCall set_color_call(std::tuple<double, double, double> value);

    ::krpc::schema::ProcedureCall content_call();

    ::krpc::schema::ProcedureCall set_content_call(std::string value);

    ::krpc::schema::ProcedureCall font_call();

    ::krpc::schema::ProcedureCall set_font_call(std::string value);

    ::krpc::schema::ProcedureCall line_spacing_call();

    ::krpc::schema::ProcedureCall set_line_spacing_call(float value);

    ::krpc::schema::ProcedureCall material_call();

    ::krpc::schema::ProcedureCall set_material_call(std::string value);

    ::krpc::schema::ProcedureCall position_call();

    ::krpc::schema::ProcedureCall set_position_call(std::tuple<double, double, double> value);

    ::krpc::schema::ProcedureCall reference_frame_call();

    ::krpc::schema::ProcedureCall set_reference_frame_call(SpaceCenter::ReferenceFrame value);

    ::krpc::schema::ProcedureCall rotation_call();

    ::krpc::schema::ProcedureCall set_rotation_call(std::tuple<double, double, double, double> value);

    ::krpc::schema::ProcedureCall size_call();

    ::krpc::schema::ProcedureCall set_size_call(int32_t value);

    ::krpc::schema::ProcedureCall style_call();

    ::krpc::schema::ProcedureCall set_style_call(UI::FontStyle value);

    ::krpc::schema::ProcedureCall visible_call();

    ::krpc::schema::ProcedureCall set_visible_call(bool value);
  };
};

}  // namespace services

namespace services {

inline Drawing::Drawing(Client* client):
  Service(client) {
}

inline Drawing::Line Drawing::add_direction(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length = 10.0, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(length));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddDirection", _args);
  Drawing::Line _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline Drawing::Line Drawing::add_line(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(start));
  _args.push_back(encoder::encode(end));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddLine", _args);
  Drawing::Line _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline Drawing::Polygon Drawing::add_polygon(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vertices));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddPolygon", _args);
  Drawing::Polygon _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline Drawing::Text Drawing::add_text(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(text));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(visible));
  std::string _data = this->_client->invoke("Drawing", "AddText", _args);
  Drawing::Text _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::clear(bool client_only = false) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(client_only));
  this->_client->invoke("Drawing", "Clear", _args);
}

inline ::krpc::Stream<Drawing::Line> Drawing::add_direction_stream(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length = 10.0, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(length));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Line>(this->_client, this->_client->build_call("Drawing", "AddDirection", _args));
}

inline ::krpc::Stream<Drawing::Line> Drawing::add_line_stream(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(start));
  _args.push_back(encoder::encode(end));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Line>(this->_client, this->_client->build_call("Drawing", "AddLine", _args));
}

inline ::krpc::Stream<Drawing::Polygon> Drawing::add_polygon_stream(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vertices));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Polygon>(this->_client, this->_client->build_call("Drawing", "AddPolygon", _args));
}

inline ::krpc::Stream<Drawing::Text> Drawing::add_text_stream(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(text));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(visible));
  return ::krpc::Stream<Drawing::Text>(this->_client, this->_client->build_call("Drawing", "AddText", _args));
}

inline ::krpc::schema::ProcedureCall Drawing::add_direction_call(std::tuple<double, double, double> direction, SpaceCenter::ReferenceFrame reference_frame, float length = 10.0, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(direction));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(length));
  _args.push_back(encoder::encode(visible));
  return this->_client->build_call("Drawing", "AddDirection", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::add_line_call(std::tuple<double, double, double> start, std::tuple<double, double, double> end, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(start));
  _args.push_back(encoder::encode(end));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  return this->_client->build_call("Drawing", "AddLine", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::add_polygon_call(std::vector<std::tuple<double, double, double> > vertices, SpaceCenter::ReferenceFrame reference_frame, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(vertices));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(visible));
  return this->_client->build_call("Drawing", "AddPolygon", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::add_text_call(std::string text, SpaceCenter::ReferenceFrame reference_frame, std::tuple<double, double, double> position, std::tuple<double, double, double, double> rotation, bool visible = true) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(text));
  _args.push_back(encoder::encode(reference_frame));
  _args.push_back(encoder::encode(position));
  _args.push_back(encoder::encode(rotation));
  _args.push_back(encoder::encode(visible));
  return this->_client->build_call("Drawing", "AddText", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::clear_call(bool client_only = false) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(client_only));
  return this->_client->build_call("Drawing", "Clear", _args);
}

inline Drawing::Line::Line(Client* client, uint64_t id):
  Object(client, "Drawing::Line", id) {}

inline void Drawing::Line::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("Drawing", "Line_Remove", _args);
}

inline std::tuple<double, double, double> Drawing::Line::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Color", _args);
}

inline std::tuple<double, double, double> Drawing::Line::end() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_End", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_end(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_End", _args);
}

inline std::string Drawing::Line::material() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Material", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_material(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Material", _args);
}

inline SpaceCenter::ReferenceFrame Drawing::Line::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_ReferenceFrame", _args);
}

inline std::tuple<double, double, double> Drawing::Line::start() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Start", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_start(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Start", _args);
}

inline float Drawing::Line::thickness() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Thickness", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_thickness(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Thickness", _args);
}

inline bool Drawing::Line::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Line_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Line::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Line_set_Visible", _args);
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Line::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->build_call("Drawing", "Line_get_Color", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Line::end_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->build_call("Drawing", "Line_get_End", _args));
}

inline ::krpc::Stream<std::string> Drawing::Line::material_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("Drawing", "Line_get_Material", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> Drawing::Line::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->build_call("Drawing", "Line_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Line::start_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->build_call("Drawing", "Line_get_Start", _args));
}

inline ::krpc::Stream<float> Drawing::Line::thickness_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("Drawing", "Line_get_Thickness", _args));
}

inline ::krpc::Stream<bool> Drawing::Line::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("Drawing", "Line_get_Visible", _args));
}

inline ::krpc::schema::ProcedureCall Drawing::Line::remove_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_Remove", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::color_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_Color", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_color_call(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_Color", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::end_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_End", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_end_call(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_End", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::material_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_Material", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_material_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_Material", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::reference_frame_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_ReferenceFrame", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_reference_frame_call(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_ReferenceFrame", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::start_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_Start", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_start_call(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_Start", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::thickness_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_Thickness", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_thickness_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_Thickness", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::visible_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Line_get_Visible", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Line::set_visible_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Line_set_Visible", _args);
}

inline Drawing::Polygon::Polygon(Client* client, uint64_t id):
  Object(client, "Drawing::Polygon", id) {}

inline void Drawing::Polygon::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("Drawing", "Polygon_Remove", _args);
}

inline std::tuple<double, double, double> Drawing::Polygon::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Color", _args);
}

inline std::string Drawing::Polygon::material() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Material", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_material(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Material", _args);
}

inline SpaceCenter::ReferenceFrame Drawing::Polygon::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_ReferenceFrame", _args);
}

inline float Drawing::Polygon::thickness() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Thickness", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_thickness(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Thickness", _args);
}

inline std::vector<std::tuple<double, double, double> > Drawing::Polygon::vertices() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Vertices", _args);
  std::vector<std::tuple<double, double, double> > _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_vertices(std::vector<std::tuple<double, double, double> > value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Vertices", _args);
}

inline bool Drawing::Polygon::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Polygon_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Polygon::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Polygon_set_Visible", _args);
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Polygon::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->build_call("Drawing", "Polygon_get_Color", _args));
}

inline ::krpc::Stream<std::string> Drawing::Polygon::material_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("Drawing", "Polygon_get_Material", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> Drawing::Polygon::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->build_call("Drawing", "Polygon_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<float> Drawing::Polygon::thickness_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("Drawing", "Polygon_get_Thickness", _args));
}

inline ::krpc::Stream<std::vector<std::tuple<double, double, double> >> Drawing::Polygon::vertices_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::vector<std::tuple<double, double, double> >>(this->_client, this->_client->build_call("Drawing", "Polygon_get_Vertices", _args));
}

inline ::krpc::Stream<bool> Drawing::Polygon::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("Drawing", "Polygon_get_Visible", _args));
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::remove_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_Remove", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::color_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_get_Color", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::set_color_call(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Polygon_set_Color", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::material_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_get_Material", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::set_material_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Polygon_set_Material", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::reference_frame_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_get_ReferenceFrame", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::set_reference_frame_call(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Polygon_set_ReferenceFrame", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::thickness_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_get_Thickness", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::set_thickness_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Polygon_set_Thickness", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::vertices_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_get_Vertices", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::set_vertices_call(std::vector<std::tuple<double, double, double> > value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Polygon_set_Vertices", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::visible_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Polygon_get_Visible", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Polygon::set_visible_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Polygon_set_Visible", _args);
}

inline Drawing::Text::Text(Client* client, uint64_t id):
  Object(client, "Drawing::Text", id) {}

inline void Drawing::Text::remove() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  this->_client->invoke("Drawing", "Text_Remove", _args);
}

inline UI::TextAlignment Drawing::Text::alignment() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Alignment", _args);
  UI::TextAlignment _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_alignment(UI::TextAlignment value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Alignment", _args);
}

inline UI::TextAnchor Drawing::Text::anchor() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Anchor", _args);
  UI::TextAnchor _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_anchor(UI::TextAnchor value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Anchor", _args);
}

inline float Drawing::Text::character_size() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_CharacterSize", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_character_size(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_CharacterSize", _args);
}

inline std::tuple<double, double, double> Drawing::Text::color() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Color", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_color(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Color", _args);
}

inline std::string Drawing::Text::content() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Content", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_content(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Content", _args);
}

inline std::string Drawing::Text::font() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Font", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_font(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Font", _args);
}

inline float Drawing::Text::line_spacing() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_LineSpacing", _args);
  float _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_line_spacing(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_LineSpacing", _args);
}

inline std::string Drawing::Text::material() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Material", _args);
  std::string _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_material(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Material", _args);
}

inline std::tuple<double, double, double> Drawing::Text::position() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Position", _args);
  std::tuple<double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_position(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Position", _args);
}

inline SpaceCenter::ReferenceFrame Drawing::Text::reference_frame() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_ReferenceFrame", _args);
  SpaceCenter::ReferenceFrame _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_reference_frame(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_ReferenceFrame", _args);
}

inline std::tuple<double, double, double, double> Drawing::Text::rotation() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Rotation", _args);
  std::tuple<double, double, double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_rotation(std::tuple<double, double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Rotation", _args);
}

inline int32_t Drawing::Text::size() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Size", _args);
  int32_t _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_size(int32_t value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Size", _args);
}

inline UI::FontStyle Drawing::Text::style() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Style", _args);
  UI::FontStyle _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_style(UI::FontStyle value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Style", _args);
}

inline bool Drawing::Text::visible() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  std::string _data = this->_client->invoke("Drawing", "Text_get_Visible", _args);
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline void Drawing::Text::set_visible(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  this->_client->invoke("Drawing", "Text_set_Visible", _args);
}

inline std::vector<std::string> Drawing::Text::available_fonts(Client& _client) {
  std::string _data = _client.invoke("Drawing", "Text_static_AvailableFonts");
    std::vector<std::string> _result;
  decoder::decode(_result, _data, &_client);
  return _result;
}

inline ::krpc::Stream<UI::TextAlignment> Drawing::Text::alignment_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::TextAlignment>(this->_client, this->_client->build_call("Drawing", "Text_get_Alignment", _args));
}

inline ::krpc::Stream<UI::TextAnchor> Drawing::Text::anchor_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::TextAnchor>(this->_client, this->_client->build_call("Drawing", "Text_get_Anchor", _args));
}

inline ::krpc::Stream<float> Drawing::Text::character_size_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("Drawing", "Text_get_CharacterSize", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Text::color_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->build_call("Drawing", "Text_get_Color", _args));
}

inline ::krpc::Stream<std::string> Drawing::Text::content_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("Drawing", "Text_get_Content", _args));
}

inline ::krpc::Stream<std::string> Drawing::Text::font_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("Drawing", "Text_get_Font", _args));
}

inline ::krpc::Stream<float> Drawing::Text::line_spacing_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<float>(this->_client, this->_client->build_call("Drawing", "Text_get_LineSpacing", _args));
}

inline ::krpc::Stream<std::string> Drawing::Text::material_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::string>(this->_client, this->_client->build_call("Drawing", "Text_get_Material", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double>> Drawing::Text::position_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double>>(this->_client, this->_client->build_call("Drawing", "Text_get_Position", _args));
}

inline ::krpc::Stream<SpaceCenter::ReferenceFrame> Drawing::Text::reference_frame_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<SpaceCenter::ReferenceFrame>(this->_client, this->_client->build_call("Drawing", "Text_get_ReferenceFrame", _args));
}

inline ::krpc::Stream<std::tuple<double, double, double, double>> Drawing::Text::rotation_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<std::tuple<double, double, double, double>>(this->_client, this->_client->build_call("Drawing", "Text_get_Rotation", _args));
}

inline ::krpc::Stream<int32_t> Drawing::Text::size_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<int32_t>(this->_client, this->_client->build_call("Drawing", "Text_get_Size", _args));
}

inline ::krpc::Stream<UI::FontStyle> Drawing::Text::style_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<UI::FontStyle>(this->_client, this->_client->build_call("Drawing", "Text_get_Style", _args));
}

inline ::krpc::Stream<bool> Drawing::Text::visible_stream() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("Drawing", "Text_get_Visible", _args));
}

inline ::krpc::Stream<std::vector<std::string>> Drawing::Text::available_fonts_stream(Client& _client) {
  return ::krpc::Stream<std::vector<std::string>>(&_client, _client.build_call("Drawing", "Text_static_AvailableFonts"));
}

inline ::krpc::schema::ProcedureCall Drawing::Text::remove_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_Remove", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::alignment_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Alignment", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_alignment_call(UI::TextAlignment value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Alignment", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::anchor_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Anchor", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_anchor_call(UI::TextAnchor value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Anchor", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::character_size_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_CharacterSize", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_character_size_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_CharacterSize", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::color_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Color", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_color_call(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Color", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::content_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Content", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_content_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Content", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::font_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Font", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_font_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Font", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::line_spacing_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_LineSpacing", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_line_spacing_call(float value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_LineSpacing", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::material_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Material", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_material_call(std::string value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Material", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::position_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Position", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_position_call(std::tuple<double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Position", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::reference_frame_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_ReferenceFrame", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_reference_frame_call(SpaceCenter::ReferenceFrame value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_ReferenceFrame", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::rotation_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Rotation", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_rotation_call(std::tuple<double, double, double, double> value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Rotation", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::size_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Size", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_size_call(int32_t value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Size", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::style_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Style", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_style_call(UI::FontStyle value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Style", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::visible_call() {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  return this->_client->build_call("Drawing", "Text_get_Visible", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::set_visible_call(bool value) {
  std::vector<std::string> _args;
  _args.push_back(encoder::encode(*this));
  _args.push_back(encoder::encode(value));
  return this->_client->build_call("Drawing", "Text_set_Visible", _args);
}

inline ::krpc::schema::ProcedureCall Drawing::Text::available_fonts_call(Client& _client) {
  return _client.build_call("Drawing", "Text_static_AvailableFonts");
}
}  // namespace services

}  // namespace krpc
