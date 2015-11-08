// @author juanmi.huertas
// 
// @brief This file contains the structure of a TBSMap and TBSLocation
// A TBSMap will contain a graph of TBSLocation and an "image" 
#ifndef _TBSMAP_H_INCLUDE_
#define _TBSMAP_H_INCLUDE_

#include <vector>
#include <memory>

//TEMPORARY?
#include <string> //I want to use "atoms" instead of strings
#include <unordered_map> // I want to use sparse_hash instead of unordered_map  

enum TBSLocationType{ _UNPASSABLE, _WATER, _GROUND, _COAST };

// @brief Contains all the info for a location of the game (all this info will be const, and will not change throughout the game)
class TBSLocation{
  // Complete name of the location
  // implement atoms_ as OCTET does, and use an atom to hold the name of the location
  // TEMPORARY using string on the meantime
  std::string long_name_;

  // Shorten name of the location
  // TEMPORARY using string until I have atoms into functioning
  std::string short_name_;

  // Hash table of connected locations
  // TO DO - Does this really need to be like this?? Couldnt it be just a dictionary?
  std::unordered_map< std::string, TBSLocation* > paths_;

  // Type of the location
  TBSLocationType type_;

  // Position relative to the map 
  //STILL NOT NEEDED
  std::pair<float, float> position;

  // Game related info:
  // This is the initial ownership of the location 
  int init_ownership_id_;

  // Current owner
  int ownership_id_;

  // Units un current location
  ///INFO REGARDING THE UNITS TODO

public:
  // @brief Constructor with initialization of names and type
  TBSLocation(std::string short_name, std::string long_name, TBSLocationType type = _GROUND, float x = 0, float y = 0, int init_ownership_id = 0) :
    short_name_(short_name), long_name_(long_name), type_(type), position(x, y), init_ownership_id_(init_ownership_id), ownership_id_(init_ownership_id) {}

  // @brief Set the short name 
  // TEMPORARY TO BE REPLACED WITH ATOMS
  void set_short_name(std::string short_name){
    short_name_ = short_name;
  }

  // @brief Set the long name 
  // TEMPORARY TO BE REPLACED WITH ATOMS
  void set_long_name(std::string long_name){
    long_name_ = long_name;
  }

  // @brief Set the position to two values x, and y
  // @param x Float with the x relative to the map
  // @param y Float with the y relative to the map
  void set_position(float x, float y){
    position.first = x;
    position.second = y;
  }

  // @brief Set the position to a pair of two values x, and y
  // @param pos Pair of Float with the x and y relative to the map
  void set_position(std::pair<float,float> &pos){
    position = pos;
  }

  // @brief Set the initial ownership id
  // @param init_ownership_id the initial ownership id for this location
  void set_init_ownership_id(int init_ownership_id){
    init_ownership_id_ = init_ownership_id;
  }

  // @brief Get the position relative to the map
  // @return The position of the location relative to the map
  std::pair<float, float> & get_position(){
    return position;
  }

  // @brief Gets the short name
  // TEMPORARY using strings until I have atoms into functioning
  inline  char* get_short_name() {
    return &short_name_[0];
  }

  // @brief Gets the Long name
  // TEMPORARY using strings until I have atoms into functioning
  inline char* get_long_name() {
    return &long_name_[0];
  }

  // @brief Get the player id of the initial ownership
  inline int get_init_ownership_id(){
    return init_ownership_id_;
  }

  // @brief Check if the location is water
  // @return True if is water, false if it is not water
  inline bool is_water(){
    return type_ == _WATER;
  }

  // @brief Check if the location is ground (coast is ground!)
  // @return True if is ground, false if it is not ground
  inline bool is_ground(){
    return type_ >= _GROUND;
  }

  // @brief Check if the location is only ground
  // @return True if is ground, false if it is not ground
  inline bool is_only_ground(){
    return type_ == _GROUND;
  }

  // @brief Check if the location is coast
  // @return True if is coast, false if it is not coast
  inline bool is_coast(){
    return type_ == _COAST;
  }

  // @brief Set the current location as coast
  inline void set_as_coast(){
    type_ = _COAST;
  }

  // @brief This function gets all the info of the TBSLocation and return it as a string
  // @return A String with all the info of the TBSLocation
  std::string ToString();

  // @brief This function will add a new path to the given shortened location
  // @param Location is a pointer to the location we want to insert as a path from this location
  // @param Reciprocal is a boolean to test if we want to create a reciprocal insertion of the connection (default true)
  void InsertPathTo(TBSLocation *location, bool reciprocal = true);

  // @brief Check if the location has a path connecting to another location
  // If the location that we give as parameter is water, we will set the current location as coast
  // @param name The string of the shorten name of the location we want to find
  // @return True if it has a path to that location
  inline bool has_path_to(std::string name){
    return paths_.count(name) > 0;
  }
};


// @brief Contains all the info for a map of the game
class TBSMap{
  // Array with all the locations, to keep them packed together.
  std::vector< std::shared_ptr<TBSLocation> > locations_;

  // Hash table with pointers to each of the locations (by name), to keep an inmediate access to them.
  // here I will use a better container than those offered by the stl
  // TEMPORARY using unordered_map (the best that the stl can offer)
  std::unordered_map< std::string, unsigned int > location_ids_;  //This could be simplified by having an atom structure for Locations (matching a STRING with an ID)

  // Image of the map
  // here I will have probably the reference to the image 
  // TEMPORARY still using text based version, so no image needed
  // image variable

public:
  // @brief Constructor of TBSMap 
  TBSMap() {}

  // @brief This function reserves the number of locations we are going to use
  void InitNumLocations(int num_locations);

  // @brief This lets insert a new location to the map
  void InsertLocation(TBSLocation *new_location);

  int GetLocationId(std::string name){
    return location_ids_[name];
  }

  // @brief This functions get a pointer to a location from the short name
  // @param location_name String with the abreviation of the location
  // @return If the location exist, will return a pointer to the location with location_name as name
  //         if it doesn´t exist will return nullptr
  std::shared_ptr<TBSLocation> GetLocation(std::string location_name);

  // @brief This functions get a pointer to a location from the short name
  // @param id Id of the location that we want to obtain
  // @return If the location exist, will return a pointer to the location with location_name as name
  //         if it doesn´t exist will return nullptr
  std::shared_ptr<TBSLocation> GetLocation(unsigned int id);

  // @brief FOR DEBUG ONLY. This prints the map information on the console with printf
  void PrintfMapToConsole();

  // @brief Function to Load the Map - currently empty TO DO
  void LoadMap(/*some resource*/);

  // @brief Function to Save the Map - currently empty TO DO
  void SaveMap(/*some resource*/);

};


#endif