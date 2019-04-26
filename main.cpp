#include <any>
#include <iostream>

struct point {
  point(float x, float y) : x_(x), y_(y) {}
  float x_;
  float y_;
};

std::ostream& operator<<(std::ostream& out, const point& p)
{
  out << "[x,y] = (" << p.x_ << ", " << p.y_ << ")";
  return out;
}

int main()
{
  std::cout << std::boolalpha;

  // #01 @any_cast
  std::any a = 1;
  std::cout << a.type().name() << " : " << std::any_cast<int>(a) << '\n';
  a = 3.14;
  std::cout << a.type().name() << " : " << std::any_cast<double>(a) << '\n';
  a = true;
  std::cout << a.type().name() << " : " << std::any_cast<bool>(a) << '\n';
  
  // #02 @bad_any_cast
  try {
    a = 1;
    std::cout << std::any_cast<float>(a) << '\n';
  } catch (const std::bad_any_cast& e) {
    std::cout << e.what() << '\n';
  }

  // #03 @has_value
  a = 1;
  if (a.has_value()){
    std::cout << a.type().name() << '\n';
  }

  // #04 @reset
  a.reset();
  if (!a.has_value()) {
    std::cout << "no value\n";
  }

  // #05
  a = 1;
  int* p = std::any_cast<int>(&a);
  std::cout << *p << '\n';

  // #06 @make_any
  a = std::make_any<point>(10.0f, 20.0f);
  std::cout << a.type().name() << " : " << std::any_cast<point>(a) << '\n';

  // #07 @emplace
  a.emplace<point>(20.0f, 30.0f);
  std::cout << a.type().name() << " : " << std::any_cast<point>(a) << '\n';

  return 0;
}