#include "TBSMap.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
// TBSLocation functions

std::string TBSLocation::ToString(){
  std::string long_string (long_name_);

  long_string.append(" (");
  long_string.append(short_name_);
  if (type_ == _UNPASSABLE)
  {
    long_string.append(") Type: Unpassable \nConnected to: ");
  }
  else if (type_ == _WATER)
  {
    long_string.append(") Type: Water \nConnected to: ");
  }
  else 
  {
    long_string.append(") Type: Ground \nConnected to: ");
  }
  for (auto path : paths_){
    long_string.append(path.second->get_long_name());
    long_string.append(" (");
    long_string.append(path.first);
    long_string.append(") -");
  }

  return long_string;
}

void TBSLocation::InsertPathTo(TBSLocation *location, bool recursive){
  paths_[location->get_short_name()] = location;
  if (recursive) location->InsertPathTo(this, false);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
// TBSMap functions

void TBSMap::InitNumLocations(int num_locations){
  locations_.reserve(num_locations); 
}

void TBSMap::InsertLocation(TBSLocation *new_location){
  auto location_id = location_ids_.find(new_location->get_short_name());

  if (location_id != location_ids_.end())
  {
    // Handle if the location already exists
  }
  else
  {
    // Insert location
    location_ids_[new_location->get_short_name()] = locations_.size();
    locations_.push_back(std::shared_ptr<TBSLocation>(new_location));
  }
}

std::shared_ptr < TBSLocation > TBSMap::GetLocation(std::string location_name){
  std::shared_ptr < TBSLocation > location_ptr = nullptr; 
  
  auto location_id = location_ids_.find(location_name);
  
  if (location_id != location_ids_.end()){
    location_ptr = locations_[location_id->second];
  }
  return location_ptr;
}

std::shared_ptr < TBSLocation > TBSMap::GetLocation(unsigned int id){
  std::shared_ptr < TBSLocation > location_ptr = nullptr;
  if (id > 0 && id < locations_.size()){
    location_ptr = locations_[id];
  }
  return location_ptr;
}
