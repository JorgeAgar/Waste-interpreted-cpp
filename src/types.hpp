#ifndef TYPES_HPP
#define TYPES_HPP

enum class Type {
  INT

};

Type fromString(std::string input) {
  switch (input) {
    case "int": return Type::INT;
  }
}

#endif //TYPES_HPP
