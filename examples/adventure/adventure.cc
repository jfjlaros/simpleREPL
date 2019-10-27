#include "../../src/simpleREPL.h"


class Adventure {
  public:
    Adventure(void) {}
    string walk(string),
           look(void);
  private:
    int _location = 0;
};


string Adventure::walk(string direction) {
  if (direction == "north") {
    _location++;
  }
  else if (direction == "south") {
    _location--;
  }
  else {
    return "You can not go there.";
  }

  return "You went " + direction + ".";
}

string Adventure::look(void) {
  string message = "Location " + to_string(_location) + ".";

  switch (_location) {
    case 0:
      message += "\n\nThis is a dimly lit forest, with large trees all "
        "around.";
      break;
    case -1:
      message += "\n\nIt is pitch black, you are likely to be eaten by a "
        "grue.";
      break;
    case 1:
      message += "\n\nYou are standing in an open field west of a white "
        "house, with a boarded front door.";
  }

  return message;
}


int main(void) {
  Adventure adventure;

  while (interface(
    pack(&adventure, &Adventure::walk), "walk", "Walk in a direction.",
    pack(&adventure, &Adventure::look), "look", "Look around."));

  return 0;
}
