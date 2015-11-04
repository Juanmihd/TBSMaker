#include "TBSMap.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
// TBSLocation functions

std::string TBSLocation::ToString(){
  std::string long_string;

  long_string = long_name_;
  long_string.append(" (");
  long_string.append(short_name_);
  if (type_ == _UNPASSABLE)
  {
    long_string.append(") Type: Unpassable \nConnected to : ");
  }
  else if (type_ == _WATER)
  {
    long_string.append(") Type: Water \nConnected to : ");
  }
  else 
  {
    long_string.append(") Type: Ground \nConnected to : ");
  }
  for (auto link : links_){
    long_string.append(link.second->get_long_name());
    long_string.append(" (");
    long_string.append(link.second->get_short_name());
    long_string.append("), ");
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
// TBSMap functions


std::shared_ptr < TBSLocation > TBSMap::get_location(std::string location_name){
  auto location_id = location_ids_.find(location_name);

  std::shared_ptr < TBSLocation > location_ptr = nullptr;
  if (location_id != location_ids_.end()){
    return locations_[location_id->second];
  }
  return nullptr;
}
