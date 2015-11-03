// @author juanmi.huertas
// 
// @brief This file contains the structure of a TBSMap and TBSLocation
// A TBSMap will contain a graph of TBSLocation and an "image" 
#include <vector>
#include <memory>

//TEMPORARY
#include <string> //I want to use "atoms" instead of strings
#include <unordered_map> // I want to use sparse_hash instead of unordered_map

// @brief Contains all the info for a location of the game
class TBSLocation{
  enum TBSLocationType{ _UNPASSABLE, _WATER, _GROUND };
  // Complete name of the location
  // implement atoms_ as OCTET does, and use an atom to hold the name of the location
  // TEMPORARY using string on the meantime
  std::string long_name_;

  // Shorten name of the location
  // TEMPORARY using string until I have atoms into functioning
  std::string short_name_;

  // List of connected locations
  std::vector< std::weak_ptr< TBSLocation > > links_;

  // Type of the location
  TBSLocationType type_;

  // Index of player controling location
  unsigned char owner_;

  

};

// @brief Contains all the info for a map of the game
class TBSMap{
  // Array with all the locations, to keep them packed together.
  std::vector < std::shared_ptr< TBSLocation > > array_locations_;

  // Hash table with pointers to each of the locations (by name), to keep an inmediate access to them.
  // here I will use a better container than those offered by the stl
  // TEMPORARY using unordered_map (the best that the stl can offer)
  std::unordered_map< std::string, std::weak_ptr< TBSLocation > > hash_locations_;

  // Image of the map
  // here I will have probably the reference to the image 
  // TEMPORARY still using text based version, so no image needed
  // image variable



};
