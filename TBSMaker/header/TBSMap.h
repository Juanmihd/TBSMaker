// @author juanmi.huertas
// 
// @brief This file contains the structure of a TBSMap and TBSLocation
// A TBSMap will contain a graph of TBSLocation and an "image" 
#include <vector>
#include <memory>

//TEMPORARY
#include <string> //I want to use "atoms" instead of strings
#include <unordered_map> // I want to use sparse_hash instead of unordered_map  

// @brief Contains all the info for a location of the game (all this info will be const, and will not change throughout the game
class TBSLocation{
  enum TBSLocationType{ _UNPASSABLE, _WATER, _GROUND };
  // Complete name of the location
  // implement atoms_ as OCTET does, and use an atom to hold the name of the location
  // TEMPORARY using string on the meantime
  std::string long_name_;

  // Shorten name of the location
  // TEMPORARY using string until I have atoms into functioning
  std::string short_name_;

  // Hash table of connected locations
  std::unordered_map < std::string, std::shared_ptr< TBSLocation > > links_;

  // Type of the location
  TBSLocationType type_;
};

// @brief Contains all the info for a map of the game
class TBSMap{
  // Array with all the locations, to keep them packed together.
  std::vector < std::shared_ptr< TBSLocation > > locations_;

  // Hash table with pointers to each of the locations (by name), to keep an inmediate access to them.
  // here I will use a better container than those offered by the stl
  // TEMPORARY using unordered_map (the best that the stl can offer)
  std::unordered_map< std::string, int > location_ids_;  //This could be simplified by having an atom structure for Locations (matching a STRING with an ID)

  // Image of the map
  // here I will have probably the reference to the image 
  // TEMPORARY still using text based version, so no image needed
  // image variable

  
public:

  TBSMap();


  // @brief This function reserves the number of locations we are going to use
  void InitNumLocations(int num_locations){
    locations_.reserve(num_locations);
  }

  // @brief This functions get a pointer to a location from the short name
  // @param location_name String with the abreviation of the location
  // @return If the location exist, will return a pointer to the location with location_name as name
  //         if it doesn�t exist will return nullptr
  std::shared_ptr < TBSLocation > get_location(std::string location_name);



};
