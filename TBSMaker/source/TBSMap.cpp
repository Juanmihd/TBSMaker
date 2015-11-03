#include "TBSMap.h"




std::shared_ptr < TBSLocation > TBSMap::get_location(std::string location_name){
  auto location_id = location_ids_.find(location_name);

  std::shared_ptr < TBSLocation > location_ptr = nullptr;
  if (location_id != location_ids_.end()){
    return locations_[location_id->second];
  }
  return nullptr;
}
