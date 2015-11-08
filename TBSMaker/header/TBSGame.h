// @author juanmi.huertas
// 
// @brief This file contains the core TBSGame application
// A TBSGame will contain a TBSMap and a set of TBSPlayer 
// (later on it will contain as well set of TBSRule)
// (later on we may want to have a "log" or "history" of the game)

#include "TBSPlayer.h"
#include "TBSMap.h"

// @brief Contains all the info for a game
class TBSGame{};



// Some test functions to be sure that everything is going well!

bool TestTBSMap(std::string input){
  TBSMap GameMap;

  GameMap.InitNumLocations(10);

  auto loc1 = new TBSLocation("GRA", "Granada");
  auto loc2 = new TBSLocation("JAE", "Jaen");
  auto loc3 = new TBSLocation("ALM", "Almeria");
  auto loc4 = new TBSLocation("MAL", "Malaga");
  auto loc5 = new TBSLocation("HUE", "Huelva");
  auto loc6 = new TBSLocation("CAD", "Cadiz");
  auto loc7 = new TBSLocation("SEV", "Sevilla");
  auto loc8 = new TBSLocation("MED", "Mediterraneo", _WATER);
  auto loc9 = new TBSLocation("ATL", "Atlantico", _WATER);
  auto loc10 = new TBSLocation("COR", "Cordoba");

  loc1->InsertPathTo(loc2);
  loc1->InsertPathTo(loc3);
  loc1->InsertPathTo(loc4);
  loc1->InsertPathTo(loc8);

  loc2->InsertPathTo(loc1);
  loc2->InsertPathTo(loc4);
  loc2->InsertPathTo(loc10);

  loc3->InsertPathTo(loc8);

  loc4->InsertPathTo(loc8);
  loc4->InsertPathTo(loc6);
  loc4->InsertPathTo(loc10);

  loc5->InsertPathTo(loc9);
  loc5->InsertPathTo(loc9);

  loc6->InsertPathTo(loc5);
  loc6->InsertPathTo(loc7);
  loc6->InsertPathTo(loc4);
  loc6->InsertPathTo(loc9);

  loc7->InsertPathTo(loc10);

  GameMap.InsertLocation(loc1);
  GameMap.InsertLocation(loc2);
  GameMap.InsertLocation(loc3);
  GameMap.InsertLocation(loc4);
  GameMap.InsertLocation(loc5);
  GameMap.InsertLocation(loc6);
  GameMap.InsertLocation(loc7);
  GameMap.InsertLocation(loc8);
  GameMap.InsertLocation(loc9);

  auto loc = GameMap.GetLocation(input);
  if (loc == nullptr)
  {
    printf("ERROR! I wasn´t able to find %s.", &input[0]);
  }
  else{
    printf("\n%s", loc->get_long_name());

    printf("\nPrinting eveything:\n%s", &loc->ToString()[0]);
  }

  return true;
}