#include "TBSMap.h"


char ToUpper(char &c){
  if (c >= 'a' && c <= 'z')
    return c + ('A' - 'a');
  return c;
}

void StringToUpper(std::string &s){
  for (auto& c : s){
    c = ToUpper(c);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// TBSLocation functions

std::string TBSLocation::ToString(){
  std::string long_string (long_name_);

  long_string.append(" (");
  long_string.append(short_name_);
  if (init_ownership_id_ != 0){
    long_string.append(") - initial ownership id: (");
    long_string.append(std::to_string(init_ownership_id_));
  }
  long_string.append(") \nType: ");
  if (type_ == _GROUND)
  {
    long_string.append("Ground \nConnected to: ");
  }
  else if (type_ == _COAST)
  {
    long_string.append("Ground (coast) \nConnected to: ");
  }
  else if (type_ == _WATER)
  {
    long_string.append("Water \nConnected to: ");
  }
  else 
  {
    long_string.append("Unpassable \nConnected to: ");
  }
  for (auto path : paths_){
    long_string.append(path.second->get_long_name());
    long_string.append(" (");
    long_string.append(path.first);
    long_string.append(") - ");
  }

  return long_string;
}

void TBSLocation::InsertPathTo(TBSLocation *location, bool reciprocal){
  paths_[location->get_short_name()] = location;
  if (location->is_water() && this->is_ground())
  {
    this->set_as_coast();
  }
  if (reciprocal) location->InsertPathTo(this, false);
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

  StringToUpper(location_name);

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

void TBSMap::PrintfMapToConsole(){
  printf("\n\nPrinting map info!");
  for (auto location : locations_)
  {
    printf("\n\n%s", &location->ToString()[0]);
  }
}
