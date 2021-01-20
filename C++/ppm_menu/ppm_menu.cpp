#include <iostream>
#include <cstdlib>
#include "ActionData.h"
#include "image_menu.h"
int main( ) {
  std::srand(std::time(0));
  return imageMenu( std::cin, std::cout );
}
